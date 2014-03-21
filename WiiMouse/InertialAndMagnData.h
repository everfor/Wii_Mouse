#ifndef InertialAndMagnData_h
#define IntertialAndMagnData_h

class IntertialAndMagnData {
	float gyroX, gyroY, gyroZ, accX, accY, accZ, magX, magY, magZ;
	public:
		IntertialAndMagnData();
		float getGyroX() const;
		float getGyroY() const;
		float getGyroZ() const;
		float getAccX() const;
		float getAccY() const;
		float getAccZ() const;
		float getMagX() const;
		float getMagY() const;
		float getMagZ() const;
		void updateGyro(float x, float y, float z);
		void updateAcc(float x, float y, float z);
		void updateMag(float x, float y, float z);
		void update(float gyroX, float gyroY, float gyroZ, float accX, float accY, float accZ, float magX, float magY, float magZ);
};

#endif