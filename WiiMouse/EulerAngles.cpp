#include "stdafx.h"
#include "EulerAngles.h"
#include "Quaternion.h"
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

EulerAngles& EulerAngles::operator+(EulerAngles& that) {
	float thatPitch = that.getPitch(),
			thatRoll = that.getRoll(),
			thatYaw = that.getYaw();
	EulerAngles sum(
		pitch + thatPitch,
		roll + thatRoll,
		yaw + thatYaw
	);

	return sum;
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

Quaternion& EulerAngles::toQuaternion() {
	Quaternion quat(
		cos(roll / 2.0) * cos(pitch / 2.0) * cos(yaw / 2.0) + sin(roll / 2.0) * sin(pitch / 2.0) * sin(yaw / 2.0),
		sin(roll / 2.0) * cos(pitch / 2.0) * cos(yaw / 2.0) - cos(roll / 2.0) * sin(pitch / 2.0) * sin(yaw / 2.0),
		cos(roll / 2.0) * sin(pitch / 2.0) * cos(yaw / 2.0) + sin(roll / 2.0) * cos(pitch / 2.0) * sin(yaw / 2.0),
		cos(roll / 2.0) * cos(pitch / 2.0) * sin(yaw / 2.0) - sin(roll / 2.0) * sin(pitch / 2.0) * cos(yaw / 2.0)
	);

	return quat;
}