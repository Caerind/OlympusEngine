#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

namespace oe
{

VectorPacked4::VectorPacked4()
{
	data[0] = 0.f;
	data[1] = 0.f;
	data[2] = 0.f;
	data[3] = 0.f;
}

VectorPacked4::VectorPacked4(const Vector4& vector)
{
	vector.pack(this);
}

VectorPacked4& VectorPacked4::operator=(const Vector4& vector)
{
	vector.pack(this);
	return *this;
}

Vector4::Vector4()
{
	mData[0] = 0.f;
	mData[1] = 0.f;
	mData[2] = 0.f;
	mData[3] = 0.f;
}

Vector4::Vector4(const Vector4& v)
{
	mData[0] = v.mData[0];
	mData[1] = v.mData[1];
	mData[2] = v.mData[2];
	mData[3] = v.mData[3];
}

Vector4::Vector4(F32 s)
{
	mData[0] = s;
	mData[1] = s;
	mData[2] = s;
	mData[3] = s;
}

Vector4::Vector4(const F32* const a)
{
	mData[0] = a[0];
	mData[1] = a[1];
	mData[2] = a[2];
	mData[3] = a[3];
}

Vector4::Vector4(F32 x, F32 y, F32 z, F32 w)
{
	mData[0] = x;
	mData[1] = y;
	mData[2] = z;
	mData[3] = w;
}

Vector4::Vector4(const Vector2& v, F32 z, F32 w)
{
	mData[0] = v[0];
	mData[1] = v[1];
	mData[2] = z;
	mData[3] = w;
}

Vector4::Vector4(const Vector3& v, F32 w)
{
	mData[0] = v[0];
	mData[1] = v[1];
	mData[2] = v[2];
	mData[3] = w;
}

Vector4::Vector4(const VectorPacked4& vector)
{
	mData[0] = vector.data[0];
	mData[1] = vector.data[1];
	mData[2] = vector.data[2];
	mData[3] = vector.data[3];
}

F32& Vector4::operator()(const U8 i)
{
	return mData[i];
}

const F32& Vector4::operator()(const U8 i) const
{
	return mData[i];
}

F32& Vector4::operator[](const U8 i)
{
	return mData[i];
}

const F32& Vector4::operator[](const U8 i) const
{
	return mData[i];
}

F32& Vector4::x()
{
	return mData[0];
}

F32& Vector4::y()
{
	return mData[1];
}

F32& Vector4::z()
{
	return mData[2];
}

F32& Vector4::w()
{
	return mData[3];
}

const F32& Vector4::x() const
{
	return mData[0];
}

const F32& Vector4::y() const
{
	return mData[1];
}

const F32& Vector4::z() const
{
	return mData[2];
}

const F32& Vector4::w() const
{
	return mData[3];
}

Vector2 Vector4::xy() 
{
	return Vector2(mData[0], mData[1]);
}

Vector2 Vector4::yz() 
{
	return Vector2(mData[1], mData[2]);
}

Vector2 Vector4::xz() 
{
	return Vector2(mData[0], mData[2]);
}

Vector2 Vector4::zw() 
{
	return Vector2(mData[2], mData[3]);
}

Vector3 Vector4::xyz()
{
	return Vector3(mData[0], mData[1], mData[2]);
}

const Vector2 Vector4::xy() const 
{
	return Vector2(mData[0], mData[1]);
}

const Vector2 Vector4::yz() const 
{
	return Vector2(mData[1], mData[2]);
}

const Vector2 Vector4::xz() const 
{
	return Vector2(mData[0], mData[2]);
}

const Vector2 Vector4::zw() const
{
	return Vector2(mData[2], mData[3]);
}

const Vector3 Vector4::xyz() const
{
	return Vector3(mData[0], mData[1], mData[2]);
}

void Vector4::pack(VectorPacked4* vector) const
{
	vector->data[0] = mData[0];
	vector->data[1] = mData[1];
	vector->data[2] = mData[2];
	vector->data[3] = mData[3];
}

Vector4& Vector4::operator=(const Vector4& v)
{
	mData[0] = v.mData[0];
	mData[1] = v.mData[1];
	mData[2] = v.mData[2];
	mData[3] = v.mData[3];
	return *this;
}

bool Vector4::operator==(const Vector4& v) const
{
	return Math::equals(mData[0], v.mData[0]) && Math::equals(mData[1], v.mData[1]) && Math::equals(mData[2], v.mData[2]) && Math::equals(mData[3], v.mData[3]);
}

bool Vector4::operator!=(const Vector4& v) const
{
	return !operator==(v);
}

Vector4 Vector4::operator-() const
{
	return Vector4(-mData[0], -mData[1], -mData[2], -mData[3]);
}

Vector4 Vector4::operator*(const Vector4& v) const
{
	return hadamardProduct(*this, v);
}

Vector4 Vector4::operator/(const Vector4& v) const
{
	return Vector4(mData[0] / v.mData[0], mData[1] / v.mData[1], mData[2] / v.mData[2], mData[3] / v.mData[3]);
}

Vector4 Vector4::operator+(const Vector4& v) const
{
	return Vector4(mData[0] + v.mData[0], mData[1] + v.mData[1], mData[2]+ v.mData[2], mData[3] + v.mData[3]);
}

Vector4 Vector4::operator-(const Vector4& v) const
{
	return Vector4(mData[0] - v.mData[0], mData[1] - v.mData[1], mData[2] - v.mData[2], mData[3] - v.mData[3]);
}

Vector4 Vector4::operator*(F32 s) const
{
	return Vector4(mData[0] * s, mData[1] * s, mData[2] * s, mData[3] * s);
}

Vector4 Vector4::operator/(F32 s) const
{
	return Vector4(mData[0] / s, mData[1] / s, mData[2] / s, mData[3] / s);
}

Vector4 Vector4::operator+(F32 s) const
{
	return Vector4(mData[0] + s, mData[1] + s, mData[2] + s, mData[3] + s);
}

Vector4 Vector4::operator-(F32 s) const
{
	return Vector4(mData[0] - s, mData[1] - s, mData[2] - s, mData[3] - s);
}

Vector4& Vector4::operator*=(const Vector4& v)
{
	mData[0] *= v.mData[0];
	mData[1] *= v.mData[1];
	mData[2] *= v.mData[2];
	mData[3] *= v.mData[3];
	return *this;
}

Vector4& Vector4::operator/=(const Vector4& v)
{
	mData[0] /= v.mData[0];
	mData[1] /= v.mData[1];
	mData[2] /= v.mData[2];
	mData[3] /= v.mData[3];
	return *this;
}

Vector4& Vector4::operator+=(const Vector4& v)
{
	mData[0] += v.mData[0];
	mData[1] += v.mData[1];
	mData[2] += v.mData[2];
	mData[3] += v.mData[3];
	return *this;
}

Vector4& Vector4::operator-=(const Vector4& v)
{
	mData[0] -= v.mData[0];
	mData[1] -= v.mData[1];
	mData[2] -= v.mData[2];
	mData[3] -= v.mData[3];
	return *this;
}

Vector4& Vector4::operator*=(F32 s)
{
	mData[0] *= s;
	mData[1] *= s;
	mData[2] *= s;
	mData[3] *= s;
	return *this;
}

Vector4& Vector4::operator/=(F32 s)
{
	mData[0] /= s;
	mData[1] /= s;
	mData[2] /= s;
	mData[3] /= s;
	return *this;
}

Vector4& Vector4::operator+=(F32 s)
{
	mData[0] += s;
	mData[1] += s;
	mData[2] += s;
	mData[3] += s;
	return *this;
}

Vector4& Vector4::operator-=(F32 s)
{
	mData[0] -= s;
	mData[1] -= s;
	mData[2] -= s;
	mData[3] -= s;
	return *this;
}

Vector2 Vector4::toVector2() const
{
	return Vector2(mData[0], mData[1]);
}

Vector3 Vector4::toVector3() const
{
	return Vector3(mData[0], mData[1], mData[2]);
}

Vector4 Vector4::toVector4() const
{
	return *this;
}

bool Vector4::isZero() const
{
	return Math::equals(mData[0], 0.f) && Math::equals(mData[1], 0.f) && Math::equals(mData[2], 0.f) && Math::equals(mData[3], 0.f);
}

F32 Vector4::getLengthSquared() const
{
	return dotProduct(*this, *this);
}

F32 Vector4::getLength() const
{
	return Math::sqrt(getLengthSquared());
}

void Vector4::setLength(F32 length)
{
	ASSERT(!isZero());
	const F32 actualLength = getLength();
	*this *= (length / actualLength);
}

F32 Vector4::normalize()
{
	const F32 length = getLength();
	ASSERT(length > 0.f);
	*this *= (1.f / length);
	return length;
}

Vector4 Vector4::normalized() const
{
	const F32 length = getLength();
	ASSERT(length > 0.f);
	return *this / length;
}

F32 Vector4::dotProduct(const Vector4& v1, const Vector4& v2)
{
	return v1.mData[0] * v2.mData[0] + v1.mData[1] * v2.mData[1] + v1.mData[2] * v2.mData[2] + v1.mData[3] * v2.mData[3];
}

Vector4 Vector4::hadamardProduct(const Vector4& v1, const Vector4& v2)
{
	return Vector4(v1.mData[0] * v2.mData[0], v1.mData[1] * v2.mData[1], v1.mData[2] * v2.mData[2], v1.mData[3] * v2.mData[3]);
}

F32 Vector4::distance(const Vector4& v1, const Vector4& v2)
{
	return (v1 - v2).getLength();
}

Vector4 Vector4::lerp(const Vector4& v1, const Vector4& v2, F32 percent)
{
	const F32 omp = 1.f - percent;
	return Vector4(omp * v1.mData[0] + percent * v2.mData[0], omp * v1.mData[1] + percent * v2.mData[1], omp * v1.mData[2] + percent * v2.mData[2], omp * v1.mData[3] + percent * v2.mData[3]);
}

const U8 Vector4::dim()
{
	return 4;
}

const Vector4 Vector4::zeros()
{
	return Vector4(0.f, 0.f, 0.f, 0.f);
}

const Vector4 Vector4::ones()
{
	return Vector4(1.f, 1.f, 1.f, 1.f);
}

const Vector4 Vector4::axisX()
{
	return Vector4(1.f, 0.f, 0.f, 0.f);
}

const Vector4 Vector4::axisY()
{
	return Vector4(0.f, 1.f, 0.f, 0.f);
}

const Vector4 Vector4::axisZ()
{
	return Vector4(0.f, 0.f, 1.f, 0.f);
}

const Vector4 Vector4::axisW()
{
	return Vector4(0.f, 0.f, 0.f, 1.f);
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

F32 dot(const Vector4& v1, const Vector4& v2)
{
	return Vector4::dotProduct(v1, v2);
}

Vector4 normalize(const Vector4& v)
{
	return v.normalized();
}

} // namespace oe
