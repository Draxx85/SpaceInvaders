#include "MathHelper.h"

float MathHelper::Lerp(float from, float to, float time)
{
		return (1 - time) * from + time * to;
}
