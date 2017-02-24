#include "Math.hpp"

#include <cmath>

namespace oe
{

F32 pi()
{
	return 3.141592653589793f;
}

F32 halfPi()
{
	return 1.57079632679f;
}

F32 radToDeg(F32 rad)
{
	float angle = 57.29577951308233f * rad;
	while (angle < 0.f)
	{
		angle += 360.f;
	}
	while (angle > 360.f)
	{
		angle -= 360.f;
	}
	return angle;
}

F32 degToRad(F32 deg)
{
	return 0.01745329251994f * deg;
}

F32 cos(F32 deg)
{
	return std::cos(degToRad(deg));
}

F32 sin(F32 deg)
{
	return std::sin(degToRad(deg));
}

F32 tan(F32 deg)
{
	return std::tan(degToRad(deg));
}

F32 acos(F32 value)
{
	return radToDeg(std::acos(value));
}

F32 asin(F32 value)
{
	return radToDeg(std::asin(value));
}

F32 atan(F32 value)
{
	return radToDeg(std::atan(value));
}

F32 atan2(F32 valY, F32 valX)
{
	return radToDeg(std::atan2(valY, valX));
}

} // namespace oe