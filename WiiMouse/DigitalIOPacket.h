/*
	Stores the data for decoded packets for Digital IO data
	Each port of AX0 ~ AX1 contains a direction and a state, where
	Direction:	1 for input, 0 for output
	State:	1 for high, 0 for low
*/
#ifndef DigitalIOPacket_h
#define DigitalIOPacket_h

class DigitalIOPacket
{
	int direction[8], state[8];
	public:	
		DigitalIOPacket();
		// Update the information of digital IO based on bytes received from Ximu
		void update(char directionByte, char stateByte);
		// Helper method that parses the incoming bytes
		void SetBitsFromByte(int data[8], char byte);
		int getDirection(int AX) const;
		int getState(int AX) const;
};

#endif