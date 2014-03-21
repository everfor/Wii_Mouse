#include "stdafx.h"
#include "InertialAndMagnData.h"

IntertialAndMagnData::IntertialAndMagnData() {
	gyroX = gyroY = gyroZ = accX = accY = accZ = magX = magY = magZ = 0.0f;
}

float IntertialAndMagnData::getGyroX() const {
	return gyroX;
}

float IntertialAndMagnData::getGyroY() const {
	return gyroY;
}

float IntertialAndMagnData::getGyroZ() const {
	return gyroZ;
}

float IntertialAndMagnData::getAccX() const {
	return accX;
}

float IntertialAndMagnData::getAccY() const {
	return accY;
}

float IntertialAndMagnData::getAccZ() const {
	return accZ;
}

float IntertialAndMagnData::getMagX() const {
	return magX;
}

float IntertialAndMagnData::getMagY() const {
	return magY;
}

float IntertialAndMagnData::getMagZ() const {
	return magZ;
}

void IntertialAndMagnData::updateGyro(float x, float y, float z) {
	gyroX = x;
	gyroY = y;
	gyroZ = z;
}

void IntertialAndMagnData::updateAcc(float x, float y, float z) {
	accX = x;
	accY = y;
	accZ = z;
}

void IntertialAndMagnData::updateMag(float x, float y, float z) {
	magX = x;
	magY = y;
	magZ = z;
}

void IntertialAndMagnData::update(float gyroX, float gyroY, float gyroZ, float accX, float accY, float accZ, float magX, float magY, float magZ) {
	updateGyro(gyroX, gyroY, gyroZ);
	updateAcc(accX, accY, accZ);
	updateMag(magX, magY, magZ);
}