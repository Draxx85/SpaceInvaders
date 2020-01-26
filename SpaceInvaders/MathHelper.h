#pragma once
#include <cmath>

class MathHelper
{
public:
	static float Lerp(float from, float to, float time);
	static float clamp(float x, float upper, float lower);
private:
	MathHelper();
};
