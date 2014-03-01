#include "stdafx.h"
#include "Quaternion.h"
#include "Utils.h"

Quaternion::Quaternion() {
	w = 1.0f;
	x = y = z = 0.0f;
}

Quaternion::Quaternion(float w, float x, float y, float z) {
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}

float Quaternion::getW() const {
	return w;
}

float Quaternion::getX() const {
	return x;
}

float Quaternion::getY() const {
	return y;
}

float Quaternion::getZ() const {
	return z;
}

void Quaternion::update(float w, float x, float y, float z) {
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}
