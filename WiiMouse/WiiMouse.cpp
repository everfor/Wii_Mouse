// WiiMouse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "XimuReceiver.h"
#include "Quaternion.h"
#include "EulerAngles.h"
#include "Utils.h"
#include <boost/asio/serial_port.hpp> 
#include <boost/asio.hpp>
#include <windows.h>

using namespace boost;

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD command = MOUSEEVENTF_MOVE;
	DWORD xOffset = 0;
	DWORD yOffset = 0;
	DWORD scrollAmount = 0;
	float yawDiff = 0.0f;
	float pitchDiff = 0.0f;
	float rollDiff = 0.0f;
	
	QuaternionPacket quaternionPacket;
	DigitalIOPacket digitalPacket;
	Quaternion quaternion;
	EulerAngles eulerAngles;
	EulerAngles lastEulerAngles;
	XimuReceiver receiver;

	bool leftButtonDown = false;
	bool rightButtonDown = false;

	// Open Serial Port
	asio::io_service io;
	asio::serial_port port(io);

	port.open("COM16");
	port.set_option(asio::serial_port_base::baud_rate(115200));

	// Read buffer character
	char c;
	// Count the packets
	int packetCounter = 0;

	while (true) {
		// Read 1 character into c, this will block
		// forever if no character arrives.
		asio::read(port, asio::buffer(&c,1));
		receiver.processNewChar(c);

		if (receiver.isQuaternionGetReady()) {
			++packetCounter;

			if (packetCounter == 1) {
				packetCounter = 0;
				quaternionPacket = receiver.getQuaternion();

				quaternion.update(quaternionPacket.getW(), quaternionPacket.getX(),
									quaternionPacket.getY(), quaternionPacket.getZ());
				eulerAngles.update(quaternion);

				yawDiff = angleCorrect(lastEulerAngles.getYaw() - eulerAngles.getYaw());
				pitchDiff = angleCorrect(eulerAngles.getPitch() - lastEulerAngles.getPitch());
				// Introduce symmetry for right-handed users (lefthanded comming in a bit)
				// Because right-handed people tend to tilt the mouse right-wards a bit
				rollDiff = angleCorrect(eulerAngles.getRoll()) - 10.0f;

				xOffset = (DWORD)(yawDiff * 15.0f);
				yOffset = (DWORD)(pitchDiff * 15.0f);

				lastEulerAngles = eulerAngles;

				mouse_event(MOUSEEVENTF_MOVE, xOffset, yOffset, scrollAmount, 0);

				if (abs(rollDiff) > 20.0) {
					scrollAmount = (DWORD)(rollDiff * -1.6f);
					mouse_event(MOUSEEVENTF_WHEEL, 0, 0, scrollAmount, 0);
					scrollAmount = 0;
				}
			}
		}

		if (receiver.isDigitalGetReady()) {
			digitalPacket = receiver.getDigitalReading();

			if (digitalPacket.getState(0) == 1) {
				if(!leftButtonDown) {
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					leftButtonDown = true;
				}
			}
			if (digitalPacket.getState(0) == 0) {
				if (leftButtonDown) {
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					leftButtonDown = false;
				}
			}
			if (digitalPacket.getState(2) == 1) {
				if(!rightButtonDown) {
					mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
					rightButtonDown = true;
				}
			}
			if (digitalPacket.getState(2) == 0) {
				if (rightButtonDown) {
					mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
					rightButtonDown = false;
				}
			}
		}
	}

	return 0;
}

