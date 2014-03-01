/*
	Stores the decoded packet for Gyroscope, Accelerometer andMagnetometer readings
*/
#ifndef InertialandMagPacket_h
#define InertialandMagPacket_h

class InertialandMagPacket {
	float gyroX, gyroY, gyroZ, accX, accY, accZ, magX, magY, magZ;
	public:
		InertialandMagPacket();
		void update(float gyroX, float gyroY, float gyroZ, float accX, float accY, float accZ, float magX, float magY, float magZ);
		float getGyroX();
		float getGyroY();
		float getGyroZ();
		float getAccX();
		float getAccY();
		float getAccZ();
		float getMagX();
		float getMagY();
		float getMagZ();
		float* getGyro();
		float* getAcc();
		float* getMag();
		float* getInertial();
		float* getInertialandMag();
};

#endif