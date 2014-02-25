#ifndef QuaternionPacket_h
#define QuaternionPacket_h

class QuaternionPacket {
	float w, x, y, z;
	public:
		QuaternionPacket(void);
		void update(float newW, float newX, float newY, float newZ);
		float getW(void) const;
		float getX(void) const;
		float getY(void) const;
		float getZ(void) const;
		// float* getQuaternion(void);
};


#endif