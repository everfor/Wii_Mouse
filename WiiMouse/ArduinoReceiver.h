#ifndef ArduinoReceiver_h
#define ArduinoReceiver_h

#include "InertialAndMagnData.h"
// #include "ButtonData.h"

enum DataHeader {
	HEADER_DATA_INERTIAL_AND_MAG,
	HEADER_DATA_BUTTON
};

enum ReturnCode {
	RETURN_INERTIAL_AND_MAG_DATA,
	RETURN_BUTTON_DATA,
	RETURN_NOT_YET_COMPLETE,
	RETURN_ERROR
};

class ArduinoReceiver {
	char buffer[256];
	int buffIndex;
	bool inertialAndMagnReady, buttonReady;
	IntertialAndMagnData inertialAndMagnData;
	// ButtonData buttonData;
	public:
		ArduinoReceiver();
		ReturnCode processNewChar(char c);
		bool inertialAndMagnDataGetReady();
		bool buttonDataGetReady();
		IntertialAndMagnData& getInertialAndMagnData();
		// buttonData& getButtonData();
};

#endif