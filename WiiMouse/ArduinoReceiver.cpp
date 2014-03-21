#include "stdafx.h"
#include "ArduinoReceiver.h"

ArduinoReceiver::ArduinoReceiver() {
	buffIndex = 0;
	inertialAndMagnReady = buttonReady = false;
}

ReturnCode ArduinoReceiver::processNewChar(char c) {
	buffer[buffIndex++] = c;

	// Just Assume a frame buffer right now
	// Proposed structure of packet:
	// Byte 0 & Byte 1: Size
	// Byte 2: Header
	// Byte 3 ~ Byte x: Data
	// Byte x + 1: frame
	if (c & 0x80 != 0) {
		int dataSize = buffer[buffIndex - 2] << 4 + buffer[buffIndex - 1];
		buffIndex = 0;
		int header = buffer[2];

		switch (header) {
			case HEADER_DATA_INERTIAL_AND_MAG:
				inertialAndMagnData.update(
					buffer[3] << 4 | buffer[4],
					buffer[5] << 4 | buffer[6],
					buffer[7] << 4 | buffer[8],
					buffer[9] << 4 | buffer[10],
					buffer[11] << 4 | buffer[12],
					buffer[13] << 4 | buffer[14],
					buffer[15] << 4 | buffer[16],
					buffer[17] << 4 | buffer[17],
					buffer[19] << 4 | buffer[20]
				);
				inertialAndMagnReady = true;
				return RETURN_INERTIAL_AND_MAG_DATA;
			// TODO: Button parsing
			default:
				return RETURN_ERROR;
		}
	}

	return RETURN_NOT_YET_COMPLETE;
}

bool ArduinoReceiver::buttonDataGetReady() {
	return buttonReady;
}

bool ArduinoReceiver::inertialAndMagnDataGetReady() {
	return inertialAndMagnReady;
}

IntertialAndMagnData& ArduinoReceiver::getInertialAndMagnData() {
	inertialAndMagnReady = false;
	return inertialAndMagnData;
}