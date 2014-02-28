#include "stdafx.h"
#include "DigitalIOPacket.h"

#include <iostream>

DigitalIOPacket::DigitalIOPacket() {
	for (int i = 0; i < 8; i++) {
		direction[i] = 0;
		state[i] = 0;
	}
}

void DigitalIOPacket::update(char directionByte, char stateByte) {
	this->SetBitsFromByte(direction, directionByte);
	this->SetBitsFromByte(state, stateByte);
}

void DigitalIOPacket::SetBitsFromByte(int data[8], char byteValue) {
    data[7] = (byteValue & 0x80) == 0x80;
    data[6] = (byteValue & 0x40) == 0x40;
    data[5] = (byteValue & 0x20) == 0x20;
    data[4] = (byteValue & 0x10) == 0x10;
    data[3] = (byteValue & 0x08) == 0x08;
    data[2] = (byteValue & 0x04) == 0x04;
    data[1] = (byteValue & 0x02) == 0x02;
    data[0] = (byteValue & 0x01) == 0x01;
}

int DigitalIOPacket::getDirection(int AX) const {
	for (int i = 0; i < 8; i++) {
		// std::cout<<direction[0]<<" "<<direction[1]<<" "<<direction[2]<<" "<<direction[3]<<" "<<direction[4]<<" "<<direction[5]<<" "<<direction[6]<<" "<<direction[7]<<" "<<std::endl;
		// std::cout<<state[0]<<" "<<state[1]<<" "<<state[2]<<" "<<state[3]<<" "<<state[4]<<" "<<state[5]<<" "<<state[6]<<" "<<state[7]<<" "<<std::endl;
	}
	return direction[AX];
}

int DigitalIOPacket::getState(int AX) const {
	return state[AX];
}