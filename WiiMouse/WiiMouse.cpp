// WiiMouse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "XimuReceiver.h"
#include "Quaternion.h"
#include "EulerAngles.h"
#include <boost/asio/serial_port.hpp> 
#include <boost/asio.hpp>
#include <windows.h>

using namespace boost;

float angleCorrect(float angle) {
	if (angle > 180.0f) {
		return angle - 360.0f;
	}

	if (angle < -180.0f) {
		return angle + 360.0f;
	}

	return angle;
}

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD command = MOUSEEVENTF_MOVE;
	DWORD xOffset = 0;
	DWORD yOffset = 0;
	float yawDiff = 0.0f;
	float pitchDiff = 0.0f;
	
	QuaternionPacket quaternionPacket;
	Quaternion quaternion;
	EulerAngles eulerAngles;
	EulerAngles lastEulerAngles;
	XimuReceiver receiver;

	// Open Serial Port
	asio::io_service io;
	asio::serial_port port(io);

	port.open("COM12");
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
			receiver.resetFlags();

			if (packetCounter == 1) {
				packetCounter = 0;
				quaternionPacket = receiver.getQuaternion();

				quaternion.update(quaternionPacket.getW(), quaternionPacket.getX(),
									quaternionPacket.getY(), quaternionPacket.getZ());
				eulerAngles.update(quaternion);

				yawDiff = angleCorrect(lastEulerAngles.getYaw() - eulerAngles.getYaw());
				pitchDiff = angleCorrect(eulerAngles.getPitch() - lastEulerAngles.getPitch());

				xOffset = (DWORD)(yawDiff * 10.0f);
				yOffset = (DWORD)(pitchDiff * 10.0f);

				lastEulerAngles = eulerAngles;

				mouse_event(command, xOffset, yOffset, 0, 0);
			}
		}
	}

	return 0;
}

