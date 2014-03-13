/*
	Euler Angles Object
*/
#ifndef EulerAngles_h
#define EulerAngles_h

class Quaternion;

class EulerAngles {
	float pitch, roll, yaw;
	public:
		EulerAngles();
		EulerAngles(float pitch, float roll, float yaw);
		float getPitch() const;
		float getRoll() const;
		float getYaw() const;
		Quaternion& toQuaternion();
};

#endif