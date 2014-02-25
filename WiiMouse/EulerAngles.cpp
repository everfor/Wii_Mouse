#include "stdafx.h"
#include "EulerAngles.h"
#include "Utils.h"

#include<math.h>


EulerAngles::EulerAngles() {
	pitch = roll = yaw = 0.0f;
}

EulerAngles::EulerAngles(float pitch, float roll, float yaw) {
	this->pitch = pitch;
	this->roll = roll;
	this->yaw = yaw;
}

float EulerAngles::getPitch() const {
	return pitch;
}

float EulerAngles::getRoll() const {
	return roll;
}

float EulerAngles::getYaw() const {
	return yaw;
}

void EulerAngles::update(Quaternion& quaternion) {
	pitch = radiansToDegrees(-atan((2.0f * (quaternion.getX() * quaternion.getZ() + quaternion.getW() * quaternion.getY())) / sqrt(1.0f - pow((2.0f * quaternion.getX() * quaternion.getZ() + 2.0f * quaternion.getW() * quaternion.getY()), 2.0f))));
	roll = radiansToDegrees(atan2(2.0f * (quaternion.getY() * quaternion.getZ() - quaternion.getW() * quaternion.getX()), 2.0f * quaternion.getW() * quaternion.getW() - 1.0f + 2.0f * quaternion.getZ() * quaternion.getZ()));
	yaw = radiansToDegrees(atan2(2.0f * (quaternion.getX() * quaternion.getY() - quaternion.getW() * quaternion.getZ()), 2.0f * quaternion.getW() * quaternion.getW() - 1.0f + 2.0f * quaternion.getX() * quaternion.getX()));
}