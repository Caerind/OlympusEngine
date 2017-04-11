#include "Vector2i.hpp"
#include "../Math/Vector2.hpp"

namespace oe
{

Vector2i::Vector2i()
{
	set(0);
}

Vector2i::Vector2i(I32 s)
{
	set(s);
}

Vector2i::Vector2i(I32 x, I32 y)
{
	set(x, y);
}

Vector2i::Vector2i(const I32 v[2])
{
	set(v);
}

Vector2i::Vector2i(const Vector2& v)
{
	set(v);
}

Vector2i::Vector2i(const Vector2i& v)
{
	set(v);
}

Vector2i& Vector2i::set(I32 s)
{
	x = s;
	y = s;
	return *this;
}

Vector2i& Vector2i::set(I32 x, I32 y)
{
	this->x = x;
	this->y = y;
	return *this;
}

Vector2i& Vector2i::set(const I32 v[2])
{
	std::memcpy(&x, v, 2 * sizeof(I32));
	return *this;
}

Vector2i& Vector2i::set(const Vector2& v)
{
	x = (I32)v.x;
	y = (I32)v.y;
	return *this;
}

Vector2i& Vector2i::set(const Vector2i& v)
{
	std::memcpy(this, &v, sizeof(Vector2i));
	return *this;
}

Vector2i& Vector2i::operator=(const Vector2& v)
{
	return set(v);
}

Vector2i& Vector2i::operator=(const Vector2i& v)
{
	return set(v);
}

bool Vector2i::operator==(const Vector2i& v) const
{
	return x == v.x && y == v.y;
}

bool Vector2i::operator!=(const Vector2i& v) const
{
	return !operator==(v);
}

const Vector2i& Vector2i::operator+() const
{
	return *this;
}

Vector2i Vector2i::operator-() const
{
	return Vector2i(-x, -y);
}

Vector2i Vector2i::operator*(const Vector2i& v) const
{
	return Vector2i(x * v.x, y * v.y);
}

Vector2i Vector2i::operator/(const Vector2i& v) const
{
	return Vector2i(x / v.x, y / v.y);
}

Vector2i Vector2i::operator+(const Vector2i& v) const
{
	return Vector2i(x + v.x, y + v.y);
}

Vector2i Vector2i::operator-(const Vector2i& v) const
{
	return Vector2i(x - v.x, y - v.y);
}

Vector2i Vector2i::operator*(I32 s) const
{
	return Vector2i(x * s, y * s);
}

Vector2i Vector2i::operator/(I32 s) const
{
	return Vector2i(x / s, y / s);
}

Vector2i Vector2i::operator+(I32 s) const
{
	return Vector2i(x + s, y + s);
}

Vector2i Vector2i::operator-(I32 s) const
{
	return Vector2i(x - s, y - s);
}

Vector2i& Vector2i::operator*=(const Vector2i& v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}

Vector2i& Vector2i::operator/=(const Vector2i& v)
{
	x /= v.x;
	y /= v.y;
	return *this;
}

Vector2i& Vector2i::operator+=(const Vector2i& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2i& Vector2i::operator-=(const Vector2i& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2i& Vector2i::operator*=(I32 s)
{
	x *= s;
	y *= s;
	return *this;
}

Vector2i& Vector2i::operator/=(I32 s)
{
	x /= s;
	y /= s;
	return *this;
}

Vector2i& Vector2i::operator+=(I32 s)
{
	x += s;
	y += s;
	return *this;
}

Vector2i& Vector2i::operator-=(I32 s)
{
	x -= s;
	y -= s;
	return *this;
}

bool Vector2i::operator<(const Vector2i& vec) const
{
	return (x == vec.x) ? y < vec.y : x < vec.x;
}

bool Vector2i::operator<=(const Vector2i& vec) const
{
	return (x == vec.x) ? y <= vec.y : x < vec.x;
}

bool Vector2i::operator>(const Vector2i& vec) const
{
	return !operator<=(vec);
}

bool Vector2i::operator>=(const Vector2i& vec) const
{
	return !operator<(vec);
}

Vector2i::operator I32*()
{
	return &x;
}

Vector2i::operator const I32*() const
{
	return &x;
}

Vector2i& Vector2i::makeZero()
{
	return set(0, 0);
}

Vector2i& Vector2i::makeOne()
{
	return set(1, 1);
}

Vector2i& Vector2i::makeAxisX()
{
	return set(1, 0);
}

Vector2i& Vector2i::makeAxisY()
{
	return set(0, 1);
}

Vector2i& Vector2i::minimize(const Vector2i& min)
{
	if (min.x < x)
	{
		x = min.x;
	}
	if (min.y < y)
	{
		y = min.y;
	}
	return *this;
}

Vector2i& Vector2i::maximize(const Vector2i& max)
{
	if (max.x > x)
	{
		x = max.x;
	}
	if (max.y > y)
	{
		y = max.y;
	}
	return *this;
}

const U8 Vector2i::dim()
{
	return 2;
}

const Vector2i Vector2i::zero()
{
	return Vector2i(0, 0);
}

const Vector2i Vector2i::one()
{
	return Vector2i(1, 1);
}

const Vector2i Vector2i::axisX()
{
	return Vector2i(1, 0);
}

const Vector2i Vector2i::axisY()
{
	return Vector2i(0, 1);
}

} // namespace oe