#ifndef DigitalIOPacket_h
#define DigitalIOPacket_h

class DigitalIOPacket
{
	int direction[8], state[8];
	public:	
		DigitalIOPacket();
		void update(char directionByte, char stateByte);
		void SetBitsFromByte(int data[8], char byte);
		int getDirection(int AX) const;
		int getState(int AX) const;
};

#endif