#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

namespace oe
{

VectorPacked2::VectorPacked2()
{
	data[0] = 0.f;
	data[1] = 0.f;
}

VectorPacked2::VectorPacked2(const Vector2& vector)
{
	vector.pack(this);
}

VectorPacked2& VectorPacked2::operator=(const Vector2& vector)
{
	vector.pack(this);
	return *this;
}

Vector2::Vector2()
{
	mData[0] = 0.f;
	mData[1] = 0.f;
}

Vector2::Vector2(const Vector2& v)
{
	mData[0] = v.mData[0];
	mData[1] = v.mData[1];
}

Vector2::Vector2(F32 s)
{
	mData[0] = s;
	mData[1] = s;
}

Vector2::Vector2(const F32* const a)
{
	mData[0] = a[0];
	mData[1] = a[1];
}

Vector2::Vector2(F32 x, F32 y)
{
	mData[0] = x;
	mData[1] = y;
}

Vector2::Vector2(const VectorPacked2& vector)
{
	mData[0] = vector.data[0];
	mData[1] = vector.data[1];
}

F32& Vector2::operator()(const U8 i)
{
	return mData[i];
}

const F32& Vector2::operator()(const U8 i) const
{
	return mData[i];
}

F32& Vector2::operator[](const U8 i)
{
	return mData[i];
}

const F32& Vector2::operator[](const U8 i) const
{
	return mData[i];
}

F32& Vector2::x()
{
	return mData[0];
}

F32& Vector2::y()
{
	return mData[1];
}

const F32& Vector2::x() const
{
	return mData[0];
}

const F32& Vector2::y() const
{
	return mData[1];
}

void Vector2::pack(VectorPacked2* vector) const
{
	vector->data[0] = mData[0];
	vector->data[1] = mData[1];
}

Vector2& Vector2::operator=(const Vector2& v)
{
	mData[0] = v.mData[0];
	mData[1] = v.mData[1];
	return *this;
}

bool Vector2::operator==(const Vector2& v) const
{
	return Math::equals(mData[0], v.mData[0]) && Math::equals(mData[1], v.mData[1]);
}

bool Vector2::operator!=(const Vector2& v) const
{
	return !operator==(v);
}

Vector2 Vector2::operator-() const
{
	return Vector2(-mData[0], -mData[1]);
}

Vector2 Vector2::operator*(const Vector2& v) const
{
	return hadamardProduct(*this, v);
}

Vector2 Vector2::operator/(const Vector2& v) const
{
	return Vector2(mData[0] / v.mData[0], mData[1] / v.mData[1]);
}

Vector2 Vector2::operator+(const Vector2& v) const
{
	return Vector2(mData[0] + v.mData[0], mData[1] + v.mData[1]);
}

Vector2 Vector2::operator-(const Vector2& v) const
{
	return Vector2(mData[0] - v.mData[0], mData[1] - v.mData[1]);
}

Vector2 Vector2::operator*(F32 s) const
{
	return Vector2(mData[0] * s, mData[1] * s);
}

Vector2 Vector2::operator/(F32 s) const
{
	return Vector2(mData[0] / s, mData[1] / s);
}

Vector2 Vector2::operator+(F32 s) const
{
	return Vector2(mData[0] + s, mData[1] + s);
}

Vector2 Vector2::operator-(F32 s) const
{
	return Vector2(mData[0] - s, mData[1] - s);
}

Vector2& Vector2::operator*=(const Vector2& v)
{
	mData[0] *= v.mData[0];
	mData[1] *= v.mData[1];
	return *this;
}

Vector2& Vector2::operator/=(const Vector2& v)
{
	mData[0] /= v.mData[0];
	mData[1] /= v.mData[1];
	return *this;
}

Vector2& Vector2::operator+=(const Vector2& v)
{
	mData[0] += v.mData[0];
	mData[1] += v.mData[1];
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
	mData[0] -= v.mData[0];
	mData[1] -= v.mData[1];
	return *this;
}

Vector2& Vector2::operator*=(F32 s)
{
	mData[0] *= s;
	mData[1] *= s;
	return *this;
}

Vector2& Vector2::operator/=(F32 s)
{
	mData[0] /= s;
	mData[1] /= s;
	return *this;
}

Vector2& Vector2::operator+=(F32 s)
{
	mData[0] += s;
	mData[1] += s;
	return *this;
}

Vector2& Vector2::operator-=(F32 s)
{
	mData[0] -= s;
	mData[1] -= s;
	return *this;
}

Vector2 Vector2::toVector2() const
{
	return *this;
}

Vector3 Vector2::toVector3() const
{
	return Vector3(mData[0], mData[1], 0.f);
}

Vector4 Vector2::toVector4() const
{
	return Vector4(mData[0], mData[1], 0.f, 1.f);
}

bool Vector2::isZero() const
{
	return Math::equals(mData[0], 0.f) && Math::equals(mData[1], 0.f);
}

F32 Vector2::getLengthSquared() const
{
	return dotProduct(*this, *this);
}

F32 Vector2::getLength() const
{
	return Math::sqrt(getLengthSquared());
}

void Vector2::setLength(F32 length)
{
	ASSERT(!isZero());
	const F32 actualLength = getLength();
	*this *= (length / actualLength);
}

F32 Vector2::normalize()
{
	const F32 length = getLength();
	ASSERT(length > 0.f);
	*this *= (1.f / length);
	return length;
}

Vector2 Vector2::normalized() const
{
	const F32 length = getLength();
	ASSERT(length > 0.f);
	return *this / length;
}

F32 Vector2::getPolarAngle() const
{
	return Math::atan2(mData[1], mData[0]);
}

void Vector2::setPolarAngle(F32 angle)
{
	const F32 length = getLength();
	mData[0] = Math::cos(angle) * length;
	mData[1] = Math::sin(angle) * length;
}

void Vector2::rotate(F32 angle)
{
	const F32 c = Math::cos(angle);
	const F32 s = Math::sin(angle);
	const F32 tx = c * mData[0] - s * mData[1];
	mData[1] = s * mData[0] + c * mData[1];
	mData[0] = tx;
}

Vector2 Vector2::rotated(F32 angle)
{
	const F32 c = Math::cos(angle);
	const F32 s = Math::sin(angle);
	return Vector2(c * mData[0] - s * mData[1], s * mData[0] + c * mData[1]);
}

Vector2 Vector2::normalized(F32 angle)
{
	return Vector2(Math::cos(angle), Math::sin(angle));
}

Vector2 Vector2::polarVector(F32 angle, F32 length)
{
	return Vector2(Math::cos(angle) * length, Math::sin(angle) * length);
}

F32 Vector2::polarAngle(const Vector2& v1, const Vector2& v2)
{
	return Math::atan2(crossProduct(v1, v2), dotProduct(v1, v2));
}

F32 Vector2::dotProduct(const Vector2& v1, const Vector2& v2)
{
	return v1.mData[0] * v2.mData[0] + v1.mData[1] * v2.mData[1];
}

Vector2 Vector2::hadamardProduct(const Vector2& v1, const Vector2& v2)
{
	return Vector2(v1.mData[0] * v2.mData[0], v1.mData[1] * v2.mData[1]);
}

F32 Vector2::crossProduct(const Vector2& v1, const Vector2& v2)
{
	return v1.mData[0] * v2.mData[1] - v1.mData[1] * v2.mData[0];
}

F32 Vector2::distance(const Vector2& v1, const Vector2& v2)
{
	return (v1 - v2).getLength();
}

Vector2 Vector2::lerp(const Vector2& v1, const Vector2& v2, F32 percent)
{
	const F32 omp = 1.f - percent;
	return Vector2(omp * v1.mData[0] + percent * v2.mData[0], omp * v1.mData[1] + percent * v2.mData[1]);
}

const U8 Vector2::dim()
{
	return 2;
}

const Vector2 Vector2::zeros()
{
	return Vector2(0.f, 0.f);
}

const Vector2 Vector2::ones()
{
	return Vector2(1.f, 1.f);
}

const Vector2 Vector2::axisX()
{
	return Vector2(1.f, 0.f);
}

const Vector2 Vector2::axisY()
{
	return Vector2(0.f, 1.f);
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

F32 dot(const Vector2& v1, const Vector2& v2)
{
	return Vector2::dotProduct(v1, v2);
}

Vector2 normalize(const Vector2& v)
{
	return v.normalized();
}

} // namespace oe
