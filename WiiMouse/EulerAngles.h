#ifndef EulerAngles_h
#define EulerAngles_h

#include "Quaternion.h"

class EulerAngles {
	float pitch, roll, yaw;
	public:
		EulerAngles();
		EulerAngles(float pitch, float roll, float yaw);
		float getPitch() const;
		float getRoll() const;
		float getYaw() const;
		void update(Quaternion& quaternion);
};

#endif