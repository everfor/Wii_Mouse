/*
	Quaternion Object
*/
#ifndef Quaternion_h
#define Quaternion_h

class EulerAngles;

class Quaternion {
	float w, x, y, z;
	public:
		Quaternion();
		Quaternion(float w, float x, float y, float z);
		float getW() const;
		float getX() const;
		float getY() const;
		float getZ() const;
		void update(float w, float x, float y, float z);
		EulerAngles& toEulerAngles();
};

#endif