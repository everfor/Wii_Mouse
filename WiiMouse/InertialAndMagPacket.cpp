#include "stdafx.h"
#include "InertialAndMagPacket.h"

InertialandMagPacket::InertialandMagPacket() {
	gyroX = gyroY = gyroZ = accX = accY = accZ = magX = magY = magZ = 0.0f;
}

void InertialandMagPacket::update(float gyrX, float gyrY, float gyrZ, float acX, float acY, float acZ, float maX, float maY, float maZ) {
	gyroX = gyrX;
	gyroY = gyrY;
	gyroZ = gyrZ;
	accX = acX;
	accY = acY;
	accZ = acZ;
	magX = maX;
	magY = maY;
	magZ = maZ;
}

float InertialandMagPacket::getGyroX() {
	return gyroX;
}

float InertialandMagPacket::getGyroY() {
	return gyroY;
}

float InertialandMagPacket::getGyroZ() {
	return gyroZ;
}

float InertialandMagPacket::getAccX() {
	return accX;
}

float InertialandMagPacket::getAccY() {
	return accY;
}

float InertialandMagPacket::getAccZ() {
	return accZ;
}

float InertialandMagPacket::getMagX() {
	return magX;
}

float InertialandMagPacket::getMagY() {
	return magY;
}


float InertialandMagPacket::getMagZ() {
	return magZ;
}

float* InertialandMagPacket::getGyro() {
	float gyro[] = { gyroX, gyroY, gyroZ };
	return gyro;
}

float* InertialandMagPacket::getAcc() {
	float acc[] = { accX, accY, accZ };
	return acc;
}

float* InertialandMagPacket::getMag() {
	float mag[] = { magX, magY, magZ };
	return mag;
}

float* InertialandMagPacket::getInertialandMag() {
	float all[] = { gyroX, gyroY, gyroZ, accX, accY, accZ, magX, magY, magZ };
	return all;
}

