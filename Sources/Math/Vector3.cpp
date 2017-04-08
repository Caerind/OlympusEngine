#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

namespace oe
{

Vector3::Vector3()
	: x(0.0f)
	, y(0.0f)
	, z(0.0f)
{
}

Vector3::Vector3(const Vector2& v, F32 z)
{
	set(v, z);
}

Vector3::Vector3(const Vector3& v)
{
	set(v);
}

Vector3::Vector3(const Vector4& v)
{
	set(v);
}

Vector3::Vector3(const F32 v[3])
{
	set(v);
}

Vector3::Vector3(F32 x, F32 y, F32 z)
{
	set(x, y, z);
}

Vector3::Vector3(F32 s)
{
	set(s);
}

Vector3& Vector3::set(const Vector2& v, F32 z)
{
	x = v.x;
	y = v.y;
	this->z = z;
	return *this;
}

Vector3& Vector3::set(const Vector3& v)
{
	std::memcpy(this, &v, sizeof(Vector3));
	return *this;
}

Vector3& Vector3::set(const Vector4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

Vector3& Vector3::set(const F32 v[3])
{
	std::memcpy(&x, v, 3 * sizeof(F32));
	return *this;
}

Vector3& Vector3::set(F32 x, F32 y, F32 z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	return *this;
}

Vector3& Vector3::set(F32 s)
{
	x = s;
	y = s;
	z = s;
	return *this;
}

Vector3& Vector3::operator=(const Vector3& v)
{
	set(v);
	return *this;
}

bool Vector3::operator==(const Vector3& v) const
{
	return Math::equals(x, v.x) && Math::equals(y, v.y) && Math::equals(z, v.z);
}

bool Vector3::operator!=(const Vector3& v) const
{
	return !operator==(v);
}

const Vector3& Vector3::operator+() const
{
	return *this;
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator*(const Vector3& v) const
{
	return Vector3(x * v.x, y * v.y, z * v.z);
}

Vector3 Vector3::operator/(const Vector3& v) const
{
	return Vector3(x / v.x, y / v.y, z / v.z);
}

Vector3 Vector3::operator+(const Vector3& v) const
{
	return Vector3(x + v.x, y + v.y, z+ v.z);
}

Vector3 Vector3::operator-(const Vector3& v) const
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator*(F32 s) const
{
	return Vector3(x * s, y * s, z * s);
}

Vector3 Vector3::operator/(F32 s) const
{
	return Vector3(x / s, y / s, z / s);
}

Vector3 Vector3::operator+(F32 s) const
{
	return Vector3(x + s, y + s, z + s);
}

Vector3 Vector3::operator-(F32 s) const
{
	return Vector3(x - s, y - s, z - s);
}

Vector3& Vector3::operator*=(const Vector3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

Vector3& Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3& Vector3::operator*=(F32 s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

Vector3& Vector3::operator/=(F32 s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

Vector3& Vector3::operator+=(F32 s)
{
	x += s;
	y += s;
	z += s;
	return *this;
}

Vector3& Vector3::operator-=(F32 s)
{
	x -= s;
	y -= s;
	z -= s;
	return *this;
}

bool Vector3::operator<(const Vector3& vec) const
{
	if (!Math::equals(x, vec.x))
	{
		return x < vec.x;
	}
	else if (!Math::equals(y, vec.y))
	{
		return y < vec.y;
	}
	else
	{
		return z < vec.z;
	}
}

bool Vector3::operator<=(const Vector3& vec) const
{
	if (Math::equals(x, vec.x))
	{
		if (Math::equals(y, vec.y))
		{
			return Math::equals(z, vec.z) || z < vec.z;
		}
		else
		{
			return y < vec.y;
		}
	}
	else
	{
		return x < vec.x;
	}
}

bool Vector3::operator>(const Vector3& vec) const
{
	return !operator<=(vec);
}

bool Vector3::operator>=(const Vector3& vec) const
{
	return !operator<(vec);
}

Vector3::operator F32*()
{
	return &x;
}

Vector3::operator const F32*() const
{
	return &x;
}

Vector2 Vector3::toVector2() const
{
	return Vector2(x, y);
}

Vector3 Vector3::toVector3() const
{
	return *this;
}

Vector4 Vector3::toVector4() const
{
	return Vector4(x, y, z, 1.0f);
}

Vector2 Vector3::xy()
{
	return Vector2(x, y);
}

Vector2 Vector3::yz()
{
	return Vector2(y, z);
}

Vector2 Vector3::xz()
{
	return Vector2(x, z);
}

const Vector2 Vector3::xy() const
{
	return Vector2(x, y);
}

const Vector2 Vector3::yz() const
{
	return Vector2(y, z);
}

const Vector2 Vector3::xz() const
{
	return Vector2(x, z);
}

bool Vector3::isZero() const
{
	return Math::equals(x, 0.0f) && Math::equals(y, 0.0f) && Math::equals(z, 0.0f);
}

F32 Vector3::getSquaredLength() const
{
	return x * x + y * y + z * z;
}

F32 Vector3::getLength() const
{
	return Math::sqrt(getSquaredLength());
}

Vector3& Vector3::setLength(F32 length, F32* oldLength)
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

Vector3& Vector3::normalize(F32* oldLength)
{
	return setLength(1.0f, oldLength);
}

Vector3 Vector3::getNormal(F32* oldLength) const
{
	return Vector3(*this).normalize(oldLength);
}

Vector3& Vector3::makeForward()
{
	return set(0.0f, 0.0f, -1.0f);
}

Vector3& Vector3::makeBackward()
{
	return set(0.0f, 0.0f, 1.0f);
}

Vector3& Vector3::makeUp()
{
	return set(0.0f, 1.0f, 0.0f);
}

Vector3& Vector3::makeDown()
{
	return set(0.0f, -1.0f, 0.0f);
}

Vector3& Vector3::makeRight()
{
	return set(1.0f, 0.0f, 0.0f);
}

Vector3& Vector3::makeLeft()
{
	return set(-1.0f, 0.0f, 0.0f);
}

Vector3& Vector3::makeZero()
{
	return set(0.0f, 0.0f, 0.0f);
}

Vector3& Vector3::makeOne()
{
	return set(1.0f, 1.0f, 1.0f);
}

Vector3& Vector3::makeAxisX()
{
	return set(1.0f, 0.0f, 0.0f);
}

Vector3& Vector3::makeAxisY()
{
	return set(0.0f, 1.0f, 0.0f);
}

Vector3& Vector3::makeAxisZ()
{
	return set(0.0f, 0.0f, 1.0f);
}

Vector3& Vector3::minimize(const Vector3& min)
{
	if (min.x < x)
	{
		x = min.x;
	}
	if (min.y < y)
	{
		y = min.y;
	}
	if (min.z < z)
	{
		z = min.z;
	}
	return *this;
}

Vector3& Vector3::maximize(const Vector3& max)
{
	if (max.x > x)
	{
		x = max.x;
	}
	if (max.y > y)
	{
		y = max.y;
	}
	if (max.z > z)
	{
		z = max.z;
	}
	return *this;
}

F32 Vector3::dotProduct(const Vector3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

F32 Vector3::absDotProduct(const Vector3& v) const
{
	return Math::abs(x * v.x) + Math::abs(y * v.y) + Math::abs(z * v.z);
}

F32 Vector3::squaredDistance(const Vector3& v) const
{
	return (*this - v).getSquaredLength();
}

F32 Vector3::distance(const Vector3& v) const
{
	return Math::sqrt(squaredDistance(v));
}

Vector3 Vector3::crossProduct(const Vector3& v) const
{
	return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

Vector3 Vector3::hadamardProduct(const Vector3 & v) const
{
	return Vector3(x * v.x, y * v.y, z * v.z);
}

F32 Vector3::dotProduct(const Vector3& v1, const Vector3& v2)
{
	return v1.dotProduct(v2);
}

F32 Vector3::absDotProduct(const Vector3& v1, const Vector3& v2)
{
	return v1.absDotProduct(v2);
}

F32 Vector3::squaredDistance(const Vector3& v1, const Vector3& v2)
{
	return v1.squaredDistance(v2);
}

F32 Vector3::distance(const Vector3& v1, const Vector3& v2)
{
	return v1.distance(v2);
}

Vector3 Vector3::crossProduct(const Vector3& v1, const Vector3& v2)
{
	return v1.crossProduct(v2);
}

Vector3 Vector3::hadamardProduct(const Vector3& v1, const Vector3& v2)
{
	return v1.hadamardProduct(v2);
}

Vector3 Vector3::lerp(const Vector3& start, const Vector3& end, F32 percent)
{
	const F32 omp = 1.f - percent;
	return Vector3(omp * start.x + percent * end.x, omp * start.y + percent * end.y, omp * start.z + percent * end.z);
}

const U8 Vector3::dim()
{
	return 3;
}

const Vector3 Vector3::forward()
{
	return Vector3(0.0f, 0.0f, -1.0f);
}

const Vector3 Vector3::backward()
{
	return Vector3(0.0f, 0.0f, 1.0f);
}

const Vector3 Vector3::up()
{
	return Vector3(0.0f, 1.0f, 0.0f);
}

const Vector3 Vector3::down()
{
	return Vector3(0.0f, -1.0f, 0.0f);
}

const Vector3 Vector3::right()
{
	return Vector3(1.0f, 0.0f, 0.0f);
}

const Vector3 Vector3::left()
{
	return Vector3(-1.0f, 0.0f, 0.0f);
}

const Vector3 Vector3::zero()
{
	return Vector3(0.0f, 0.0f, 0.0f);
}

const Vector3 Vector3::one()
{
	return Vector3(1.0f, 1.0f, 1.0f);
}

const Vector3 Vector3::axisX()
{
	return Vector3(1.0f, 0.0f, 0.0f);
}

const Vector3 Vector3::axisY()
{
	return Vector3(0.0f, 1.0f, 0.0f);
}

const Vector3 Vector3::axisZ()
{
	return Vector3(0.0f, 0.0f, 1.0f);
}

Vector3 operator*(F32 s, const Vector3& v)
{
	return v * s;
}

Vector3 operator+(F32 s, const Vector3& v)
{
	return v + s;
}

Vector3 operator-(F32 s, const Vector3& v)
{
	return v - s;
}

/*

Vector3 Vector3::min(const Vector3& a, const Vector3& b)
{
	Vector3 r;
	for (U8 i = 0; i < 3; i++)
	{
		r.mData[i] = (a.mData[i] < b.mData[i]) ? a.mData[i] : b.mData[i];
	}
	return r;
}

Vector3 Vector3::max(const Vector3& a, const Vector3& b)
{
	Vector3 r;
	for (U8 i = 0; i < 3; i++)
	{
		r.mData[i] = (a.mData[i] < b.mData[i]) ? b.mData[i] : a.mData[i];
	}
	return r;
}

*/

} // namespace oe
