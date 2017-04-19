#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "../System/Vector2i.hpp"

namespace oe
{

Vector2::Vector2()
	: x(0.0f)
	, y(0.0f)
{
}

Vector2::Vector2(const Vector2i& v)
{
	set(v);
}

Vector2::Vector2(const Vector2& v)
{
	set(v);
}

Vector2::Vector2(const Vector3& v)
{
	set(v);
}

Vector2::Vector2(const Vector4& v)
{
	set(v);
}

Vector2::Vector2(const F32 v[2])
{
	set(v);
}

Vector2::Vector2(F32 x, F32 y)
{
	set(x, y);
}

Vector2::Vector2(F32 s)
{
	set(s);
}

Vector2& Vector2::set(const Vector2i& v)
{
	x = (F32)v.x;
	y = (F32)v.y;
	return *this;
}

Vector2& Vector2::set(const Vector2& v)
{
	std::memcpy(this, &v, sizeof(Vector2));
	return *this;
}

Vector2& Vector2::set(const Vector3& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

Vector2& Vector2::set(const Vector4& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

Vector2& Vector2::set(const F32 v[2])
{
	std::memcpy(&x, v, 2 * sizeof(F32));
	return *this;
}

Vector2& Vector2::set(F32 x, F32 y)
{
	this->x = x;
	this->y = y;
	return *this;
}

Vector2& Vector2::set(F32 s)
{
	x = s;
	y = s;
	return *this;
}

Vector2& Vector2::operator=(const Vector2i& v)
{
	return set(v);
}

Vector2& Vector2::operator=(const Vector2& v)
{
	set(v);
	return *this;
}

bool Vector2::operator==(const Vector2& v) const
{
	return Math::equals(x, v.x) && Math::equals(y, v.y);
}

bool Vector2::operator!=(const Vector2& v) const
{
	return !operator==(v);
}

const Vector2& Vector2::operator+() const
{
	return *this;
}

Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator*(const Vector2& v) const
{
	return Vector2(x * v.x, y * v.y);
}

Vector2 Vector2::operator/(const Vector2& v) const
{
	return Vector2(x / v.x, y / v.y);
}

Vector2 Vector2::operator+(const Vector2& v) const
{
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2& v) const
{
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator*(F32 s) const
{
	return Vector2(x * s, y * s);
}

Vector2 Vector2::operator/(F32 s) const
{
	return Vector2(x / s, y / s);
}

Vector2 Vector2::operator+(F32 s) const
{
	return Vector2(x + s, y + s);
}

Vector2 Vector2::operator-(F32 s) const
{
	return Vector2(x - s, y - s);
}

Vector2& Vector2::operator*=(const Vector2& v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}

Vector2& Vector2::operator/=(const Vector2& v)
{
	x /= v.x;
	y /= v.y;
	return *this;
}

Vector2& Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2& Vector2::operator*=(F32 s)
{
	x *= s;
	y *= s;
	return *this;
}

Vector2& Vector2::operator/=(F32 s)
{
	x /= s;
	y /= s;
	return *this;
}

Vector2& Vector2::operator+=(F32 s)
{
	x += s;
	y += s;
	return *this;
}

Vector2& Vector2::operator-=(F32 s)
{
	x -= s;
	y -= s;
	return *this;
}

bool Vector2::operator<(const Vector2& vec) const
{
	return (Math::equals(x, vec.x)) ? y < vec.y : x < vec.x;
}

bool Vector2::operator<=(const Vector2& vec) const
{
	return (Math::equals(x, vec.x)) ? y <= vec.y : x < vec.x;
}

bool Vector2::operator>(const Vector2& vec) const
{
	return !operator<=(vec);
}

bool Vector2::operator>=(const Vector2& vec) const
{
	return !operator<(vec);
}

Vector2::operator F32*()
{
	return &x;
}

Vector2::operator const F32*() const
{
	return &x;
}

Vector2 Vector2::toVector2() const
{
	return *this;
}

Vector3 Vector2::toVector3() const
{
	return Vector3(x, y, 0.0f);
}

Vector4 Vector2::toVector4() const
{
	return Vector4(x, y, 0.0f, 1.0f);
}

bool Vector2::isZero() const
{
	return Math::equals(x, 0.0f) && Math::equals(y, 0.0f);
}

F32 Vector2::getSquaredLength() const
{
	return x * x + y * y;
}

F32 Vector2::getLength() const
{
	return Math::sqrt(getSquaredLength());
}

F32 Vector2::getPolarAngle() const
{
	return Math::atan2(y, x);
}

Vector2& Vector2::setLength(F32 length, F32* oldLength)
{
	const F32 actualLength = getLength();
	ASSERT(actualLength > 0.0f);
	*this *= (length / actualLength);

	if (oldLength != nullptr)
	{
		*oldLength = actualLength;
	}

	return *this;
}

Vector2& Vector2::normalize(F32* oldLength)
{
	return setLength(1.0f, oldLength);
}

Vector2& Vector2::setPolarAngle(F32 angle)
{
	const F32 length = getLength();
	x = Math::cos(angle) * length;
	y = Math::sin(angle) * length;
	return *this;
}

Vector2& Vector2::rotate(F32 angle)
{
	const F32 c = Math::cos(angle);
	const F32 s = Math::sin(angle);
	const F32 tx = c * x - s * y;
	y = s * x + c * y;
	x = tx;
	return *this;
}

Vector2 Vector2::getNormal(F32* oldLength) const
{
	return Vector2(*this).normalize(oldLength);
}

Vector2 Vector2::getRotated(F32 angle) const
{
	const F32 c = Math::cos(angle);
	const F32 s = Math::sin(angle);
	return Vector2(c * x - s * y, s * x + c * y);
}

Vector2& Vector2::makeZero()
{
	set(0.0f, 0.0f);
	return *this;
}

Vector2& Vector2::makeOne()
{
	set(1.0f, 1.0f);
	return *this;
}

Vector2& Vector2::makeAxisX()
{
	set(1.0f, 0.0f);
	return *this;
}

Vector2& Vector2::makeAxisY()
{
	set(0.0f, 1.0f);
	return *this;
}

Vector2& Vector2::minimize(const Vector2& min)
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

Vector2& Vector2::maximize(const Vector2& max)
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

F32 Vector2::dotProduct(const Vector2& v) const
{
	return x * v.x + y * v.y;
}

F32 Vector2::absDotProduct(const Vector2& v) const
{
	return Math::abs(x * v.x) + Math::abs(y * v.y);
}

F32 Vector2::squaredDistance(const Vector2& v) const
{
	return (*this - v).getSquaredLength();
}

F32 Vector2::distance(const Vector2& v) const
{
	return Math::sqrt(squaredDistance(v));
}

F32 Vector2::angleBetween(const Vector2& v) const
{
	return v.getPolarAngle() - getPolarAngle();
}

F32 Vector2::crossProduct(const Vector2& v) const
{
	return x * v.y - y * v.x;
}

Vector2 Vector2::hadamardProduct(const Vector2& v) const
{
	return Vector2(x * v.x, y * v.y);
}

Vector2 Vector2::polarVector(F32 angle, F32 length)
{
	return Vector2(Math::cos(angle) * length, Math::sin(angle) * length);
}

F32 Vector2::dotProduct(const Vector2& v1, const Vector2& v2)
{
	return v1.dotProduct(v2);
}

F32 Vector2::absDotProduct(const Vector2& v1, const Vector2& v2)
{
	return v1.absDotProduct(v2);
}

F32 Vector2::squaredDistance(const Vector2& v1, const Vector2& v2)
{
	return v1.squaredDistance(v2);
}

F32 Vector2::distance(const Vector2& v1, const Vector2& v2)
{
	return v1.distance(v2);
}

F32 Vector2::angleBetween(const Vector2& v1, const Vector2& v2)
{
	return v1.angleBetween(v2);
}

F32 Vector2::crossProduct(const Vector2& v1, const Vector2& v2)
{
	return v1.crossProduct(v2);
}

Vector2 Vector2::hadamardProduct(const Vector2& v1, const Vector2& v2)
{
	return v1.hadamardProduct(v2);
}

Vector2 Vector2::lerp(const Vector2& start, const Vector2& end, F32 percent)
{
	const F32 omp = 1.f - percent;
	return Vector2(omp * start.x + percent * end.x, omp * start.y + percent * end.y);
}

const U8 Vector2::dim()
{
	return 2;
}

const Vector2 Vector2::zero()
{
	return Vector2(0.0f, 0.0f);
}

const Vector2 Vector2::one()
{
	return Vector2(1.0f, 1.0f);
}

const Vector2 Vector2::axisX()
{
	return Vector2(1.0f, 0.0f);
}

const Vector2 Vector2::axisY()
{
	return Vector2(0.0f, 1.0f);
}

Vector2 operator*(F32 s, const Vector2& v)
{
	return v * s;
}

Vector2 operator+(F32 s, const Vector2& v)
{
	return v + s;
}

Vector2 operator-(F32 s, const Vector2& v)
{
	return v - s;
}

} // namespace oe
