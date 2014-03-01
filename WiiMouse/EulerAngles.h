/*
	Euler Angles Object
*/
#ifndef EulerAngles_h
#define EulerAngles_h

#include "Quaternion.h"

class EulerAngles {
	float pitch, roll, yaw;
	public:
		EulerAngles();
		EulerAngles(float pitch, float roll, float yaw);
		EulerAngles(Quaternion& quaternion);
		float getPitch() const;
		float getRoll() const;
		float getYaw() const;
		// Convert a quaternion to euler angles
		void update(Quaternion& quaternion);
};

#endif