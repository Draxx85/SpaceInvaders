#include "MathHelper.h"

float MathHelper::Lerp(float from, float to, float time)
{
		return (1 - time) * from + time * to;
}

float MathHelper::clamp(float x, float upper, float lower)
{
	return fmin(upper, fmax(x, lower));
}
