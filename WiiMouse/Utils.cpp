#include "stdafx.h"

float radiansToDegrees (float radians) {
    return 57.2957795130823f * radians;
}

float angleCorrect(float angle) {
	if (angle > 180.0f) {
		return angle - 360.0f;
	}

	if (angle < -180.0f) {
		return angle + 360.0f;
	}

	return angle;
}
