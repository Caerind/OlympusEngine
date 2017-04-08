#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

namespace oe
{

Vector4::Vector4()
	: x(0.0f)
	, y(0.0f)
	, z(0.0f)
	, w(0.0f)
{
}

Vector4::Vector4(const Vector2& v, F32 z, F32 w)
{
	set(v, z, w);
}

Vector4::Vector4(const Vector3& v, F32 w)
{
	set(v, w);
}

Vector4::Vector4(const Vector4& v)
{
	set(v);
}

Vector4::Vector4(const F32 v[4])
{
	set(v);
}

Vector4::Vector4(F32 x, F32 y, F32 z, F32 w)
{
	set(x, y, z, w);
}

Vector4::Vector4(F32 s)
{
	set(s);
}

Vector4& Vector4::set(const Vector2& v, F32 z, F32 w)
{
	x = v.x;
	y = v.y;
	this->z = z;
	this->w = w;
	return *this;
}

Vector4& Vector4::set(const Vector3& v, F32 w)
{
	x = v.x;
	y = v.y;
	z = v.z;
	this->w = w;
	return *this;
}

Vector4& Vector4::set(const Vector4& v)
{
	std::memcpy(this, &v, sizeof(Vector4));
	return *this;
}

Vector4& Vector4::set(const F32 v[4])
{
	std::memcpy(&x, v, 4 * sizeof(F32));
	return *this;
}

Vector4& Vector4::set(F32 x, F32 y, F32 z, F32 w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	return *this;
}

Vector4& Vector4::set(F32 s)
{
	x = s;
	y = s;
	z = s;
	w = s;
	return *this;
}

Vector4& Vector4::operator=(const Vector4& v)
{
	set(v);
	return *this;
}

bool Vector4::operator==(const Vector4& v) const
{
	return Math::equals(x, v.x) && Math::equals(y, v.y) && Math::equals(z, v.z) && Math::equals(w, v.w);
}

bool Vector4::operator!=(const Vector4& v) const
{
	return !operator==(v);
}

const Vector4& Vector4::operator+() const
{
	return *this;
}

Vector4 Vector4::operator-() const
{
	return Vector4(-x, -y, -z, -w);
}

Vector4 Vector4::operator*(const Vector4& v) const
{
	return hadamardProduct(*this, v);
}

Vector4 Vector4::operator/(const Vector4& v) const
{
	return Vector4(x / v.x, y / v.y, z / v.z, w / v.w);
}

Vector4 Vector4::operator+(const Vector4& v) const
{
	return Vector4(x + v.x, y + v.y, z+ v.z, w + v.w);
}

Vector4 Vector4::operator-(const Vector4& v) const
{
	return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
}

Vector4 Vector4::operator*(F32 s) const
{
	return Vector4(x * s, y * s, z * s, w * s);
}

Vector4 Vector4::operator/(F32 s) const
{
	return Vector4(x / s, y / s, z / s, w / s);
}

Vector4 Vector4::operator+(F32 s) const
{
	return Vector4(x + s, y + s, z + s, w + s);
}

Vector4 Vector4::operator-(F32 s) const
{
	return Vector4(x - s, y - s, z - s, w - s);
}

Vector4& Vector4::operator*=(const Vector4& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w *= v.w;
	return *this;
}

Vector4& Vector4::operator/=(const Vector4& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	w /= v.w;
	return *this;
}

Vector4& Vector4::operator+=(const Vector4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

Vector4& Vector4::operator-=(const Vector4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

Vector4& Vector4::operator*=(F32 s)
{
	x *= s;
	y *= s;
	z *= s;
	w *= s;
	return *this;
}

Vector4& Vector4::operator/=(F32 s)
{
	x /= s;
	y /= s;
	z /= s;
	w /= s;
	return *this;
}

Vector4& Vector4::operator+=(F32 s)
{
	x += s;
	y += s;
	z += s;
	w += s;
	return *this;
}

Vector4& Vector4::operator-=(F32 s)
{
	x -= s;
	y -= s;
	z -= s;
	w -= s;
	return *this;
}

bool Vector4::operator<(const Vector4& vec) const
{
	if (!Math::equals(x, vec.x))
	{
		return x < vec.x;
	}
	else if (!Math::equals(x, vec.x))
	{
		return y < vec.y;
	}
	else if (!Math::equals(z, vec.z))
	{
		return z < vec.z;
	}
	else
	{
		return w < vec.w;
	}
}

bool Vector4::operator<=(const Vector4& vec) const
{
	if (Math::equals(x, vec.x))
	{
		if (Math::equals(y, vec.y))
		{
			if (Math::equals(z, vec.z))
			{
				return Math::equals(w, vec.w) || w < vec.w;
			}
			else
			{
				return z < vec.z;
			}
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

bool Vector4::operator>(const Vector4& vec) const
{
	return !operator<=(vec);
}

bool Vector4::operator>=(const Vector4& vec) const
{
	return !operator<(vec);
}

Vector4::operator F32*()
{
	return &x;
}

Vector4::operator const F32*() const
{
	return &x;
}

Vector2 Vector4::toVector2() const
{
	return Vector2(x, y);
}

Vector3 Vector4::toVector3() const
{
	return Vector3(x, y, z);
}

Vector4 Vector4::toVector4() const
{
	return *this;
}

Vector2 Vector4::xy()
{
	return Vector2(x, y);
}

Vector2 Vector4::yz()
{
	return Vector2(y, z);
}

Vector2 Vector4::xz()
{
	return Vector2(x, z);
}

Vector3 Vector4::xyz()
{
	return Vector3(x, y, z);
}

const Vector2 Vector4::xy() const
{
	return Vector2(x, y);
}

const Vector2 Vector4::yz() const
{
	return Vector2(y, z);
}

const Vector2 Vector4::xz() const
{
	return Vector2(x, z);
}

const Vector3 Vector4::xyz() const
{
	return Vector3(x, y, z);
}

bool Vector4::isZero() const
{
	return Math::equals(x, 0.0f) && Math::equals(y, 0.0f) && Math::equals(z, 0.0f) && Math::equals(w, 0.0f);
}

F32 Vector4::getSquaredLength() const
{
	return x * x + y * y + z * z + w * w;
}

F32 Vector4::getLength() const
{
	return Math::sqrt(getSquaredLength());
}

Vector4& Vector4::setLength(F32 length, F32* oldLength)
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

Vector4& Vector4::normalize(F32* oldLength)
{
	return setLength(1.0f, oldLength);
}

Vector4 Vector4::getNormal(F32* oldLength) const
{
	return Vector4(*this).normalize(oldLength);
}

Vector4& Vector4::makeZero()
{
	set(0.0f, 0.0f, 0.0f, 0.0f);
	return *this;
}

Vector4& Vector4::makeOne()
{
	set(1.0f, 1.0f, 1.0f, 1.0f);
	return *this;
}

Vector4& Vector4::makeAxisX()
{
	set(1.0f, 0.0f, 0.0f, 0.0f);
	return *this;
}

Vector4& Vector4::makeAxisY()
{
	set(0.0f, 1.0f, 0.0f, 0.0f);
	return *this;
}

Vector4& Vector4::makeAxisZ()
{
	set(0.0f, 0.0f, 1.0f, 0.0f);
	return *this;
}

Vector4& Vector4::makeAxisW()
{
	set(0.0f, 0.0f, 0.0f, 1.0f);
	return *this;
}

Vector4& Vector4::minimize(const Vector4& min)
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
	if (min.w < w)
	{
		w = min.w;
	}
	return *this;
}

Vector4& Vector4::maximize(const Vector4& max)
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
	if (max.w > w)
	{
		w = max.w;
	}
	return *this;
}

F32 Vector4::dotProduct(const Vector4& v) const
{
	return x * v.x + y * v.y + z * v.z + w * v.w;
}

F32 Vector4::absDotProduct(const Vector4& v) const
{
	return Math::abs(x * v.x) + Math::abs(y * v.y) + Math::abs(z * v.z) + Math::abs(w * v.w);
}

F32 Vector4::squaredDistance(const Vector4& v) const
{
	return (*this - v).getSquaredLength();
}

F32 Vector4::distance(const Vector4& v) const
{
	return Math::sqrt(squaredDistance(v));
}

Vector4 Vector4::hadamardProduct(const Vector4& v) const
{
	return Vector4(x * v.x, y * v.y, z * v.z, w * v.w);
}

F32 Vector4::dotProduct(const Vector4& v1, const Vector4& v2)
{
	return v1.dotProduct(v2);
}

F32 Vector4::absDotProduct(const Vector4& v1, const Vector4& v2)
{
	return v1.absDotProduct(v2);
}

F32 Vector4::squaredDistance(const Vector4& v1, const Vector4& v2)
{
	return v1.squaredDistance(v2);
}

F32 Vector4::distance(const Vector4& v1, const Vector4& v2)
{
	return v1.distance(v2);
}

Vector4 Vector4::hadamardProduct(const Vector4& v1, const Vector4& v2)
{
	return v1.hadamardProduct(v2);
}

Vector4 Vector4::lerp(const Vector4& start, const Vector4& end, F32 percent)
{
	const F32 omp = 1.f - percent;
	return Vector4(omp * start.x + percent * end.x, omp * start.y + percent * end.y, omp * start.z + percent * end.z, omp * start.w + percent * end.w);
}

const U8 Vector4::dim()
{
	return 4;
}

const Vector4 Vector4::zero()
{
	return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
}

const Vector4 Vector4::one()
{
	return Vector4(1.0f, 1.0f, 1.0f, 1.0f);
}

const Vector4 Vector4::axisX()
{
	return Vector4(1.0f, 0.0f, 0.0f, 0.0f);
}

const Vector4 Vector4::axisY()
{
	return Vector4(0.0f, 1.0f, 0.0f, 0.0f);
}

const Vector4 Vector4::axisZ()
{
	return Vector4(0.0f, 0.0f, 1.0f, 0.0f);
}

const Vector4 Vector4::axisW()
{
	return Vector4(0.0f, 0.0f, 0.0f, 1.0f);
}

Vector4 operator*(F32 s, const Vector4& v)
{
	return v * s;
}

Vector4 operator+(F32 s, const Vector4& v)
{
	return v + s;
}

Vector4 operator-(F32 s, const Vector4& v)
{
	return v - s;
}

} // namespace oe
