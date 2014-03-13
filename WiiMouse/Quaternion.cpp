#include "stdafx.h"
#include "Quaternion.h"
#include "EulerAngles.h"
#include "Utils.h"

#include <math.h>

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

Quaternion& Quaternion::operator*(Quaternion& that) {
	float thatW = that.getW(),
			thatX = that.getX(),
			thatY = that.getY(),
			thatZ = that.getZ();
	Quaternion product(
		w * thatW - x * thatX - y * thatY - z * thatZ,
		w * thatX + x * thatW + y * thatZ - z * thatY,
		w * thatY - x * thatZ + y * thatW + z * thatX,
		w * thatZ + x * thatY - y * thatX + z * thatW
	);

	return product;
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

EulerAngles& Quaternion::toEulerAngles() {
	EulerAngles angles(
		radiansToDegrees(-atan((2.0f * (x * z + w * y)) / sqrt(1.0f - pow((2.0f * x * z + 2.0f * w * y), 2.0f)))),
		radiansToDegrees(atan2(2.0f * (y * z - w * x), 2.0f * w * w - 1.0f + 2.0f * z * z)),
		radiansToDegrees(atan2(2.0f * (x * y - w * z), 2.0f * w * w - 1.0f + 2.0f * x * x))
	);

	return angles;
}
