#include "stdafx.h"
#include "QuaternionPacket.h"

QuaternionPacket::QuaternionPacket(void) {
	this->w = 1.0f;
	this->x = this->y = this->z = 0.0f;
}

void QuaternionPacket::update(float newW, float newX, float newY, float newZ) {
	this->w = newW;
	this->x = newX;
	this->y = newY;
	this->z = newZ;
}

float QuaternionPacket::getW(void) const {
	return this->w;
}

float QuaternionPacket::getX(void) const {
	return this->x;
}

float QuaternionPacket::getY(void) const{
	return this->y;
}

float QuaternionPacket::getZ(void) const{
	return this->z;
}