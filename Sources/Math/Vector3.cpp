#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

namespace oe
{

VectorPacked3::VectorPacked3()
{
	data[0] = 0.f;
	data[1] = 0.f;
	data[2] = 0.f;
}

VectorPacked3::VectorPacked3(const Vector3& vector)
{
	vector.pack(this);
}

VectorPacked3& VectorPacked3::operator=(const Vector3& vector)
{
	vector.pack(this);
	return *this;
}

Vector3::Vector3()
{
	mData[0] = 0.f;
	mData[1] = 0.f;
	mData[2] = 0.f;
}

Vector3::Vector3(const Vector3& v)
{
	mData[0] = v.mData[0];
	mData[1] = v.mData[1];
	mData[2] = v.mData[2];
}

Vector3::Vector3(F32 s)
{
	mData[0] = s;
	mData[1] = s;
	mData[2] = s;
}

Vector3::Vector3(const F32* const a)
{
	mData[0] = a[0];
	mData[1] = a[1];
	mData[2] = a[2];
}

Vector3::Vector3(F32 x, F32 y, F32 z)
{
	mData[0] = x;
	mData[1] = y;
	mData[2] = z;
}

Vector3::Vector3(const Vector2& v, F32 z)
{
	mData[0] = v[0];
	mData[1] = v[1];
	mData[2] = z;
}

Vector3::Vector3(const VectorPacked3& vector)
{
	mData[0] = vector.data[0];
	mData[1] = vector.data[1];
	mData[2] = vector.data[2];
}

F32& Vector3::operator()(const U8 i)
{
	return mData[i];
}

const F32& Vector3::operator()(const U8 i) const
{
	return mData[i];
}

F32& Vector3::operator[](const U8 i)
{
	return mData[i];
}

const F32& Vector3::operator[](const U8 i) const
{
	return mData[i];
}

F32& Vector3::x()
{
	return mData[0];
}

F32& Vector3::y()
{
	return mData[1];
}

F32& Vector3::z()
{
	return mData[2];
}

const F32& Vector3::x() const
{
	return mData[0];
}

const F32& Vector3::y() const
{
	return mData[1];
}

const F32& Vector3::z() const
{
	return mData[2];
}

Vector2 Vector3::xy() 
{
	return Vector2(mData[0], mData[1]);
}

Vector2 Vector3::yz() 
{
	return Vector2(mData[1], mData[2]);
}

Vector2 Vector3::xz() 
{
	return Vector2(mData[0], mData[2]);
}

const Vector2 Vector3::xy() const 
{
	return Vector2(mData[0], mData[1]);
}

const Vector2 Vector3::yz() const 
{
	return Vector2(mData[1], mData[2]);
}

const Vector2 Vector3::xz() const 
{
	return Vector2(mData[0], mData[2]);
}

void Vector3::pack(VectorPacked3* vector) const
{
	vector->data[0] = mData[0];
	vector->data[1] = mData[1];
	vector->data[2] = mData[2];
}

Vector3& Vector3::operator=(const Vector3& v)
{
	mData[0] = v.mData[0];
	mData[1] = v.mData[1];
	mData[2] = v.mData[2];
	return *this;
}

bool Vector3::operator==(const Vector3& v) const
{
	return Math::equals(mData[0], v.mData[0]) && Math::equals(mData[1], v.mData[1]) && Math::equals(mData[2], v.mData[2]);
}

bool Vector3::operator!=(const Vector3& v) const
{
	return !operator==(v);
}

Vector3 Vector3::operator-() const
{
	return Vector3(-mData[0], -mData[1], -mData[2]);
}

Vector3 Vector3::operator*(const Vector3& v) const
{
	return hadamardProduct(*this, v);
}

Vector3 Vector3::operator/(const Vector3& v) const
{
	return Vector3(mData[0] / v.mData[0], mData[1] / v.mData[1], mData[2] / v.mData[2]);
}

Vector3 Vector3::operator+(const Vector3& v) const
{
	return Vector3(mData[0] + v.mData[0], mData[1] + v.mData[1], mData[2]+ v.mData[2]);
}

Vector3 Vector3::operator-(const Vector3& v) const
{
	return Vector3(mData[0] - v.mData[0], mData[1] - v.mData[1], mData[2] - v.mData[2]);
}

Vector3 Vector3::operator*(F32 s) const
{
	return Vector3(mData[0] * s, mData[1] * s, mData[2] * s);
}

Vector3 Vector3::operator/(F32 s) const
{
	return Vector3(mData[0] / s, mData[1] / s, mData[2] / s);
}

Vector3 Vector3::operator+(F32 s) const
{
	return Vector3(mData[0] + s, mData[1] + s, mData[2] + s);
}

Vector3 Vector3::operator-(F32 s) const
{
	return Vector3(mData[0] - s, mData[1] - s, mData[2] - s);
}

Vector3& Vector3::operator*=(const Vector3& v)
{
	mData[0] *= v.mData[0];
	mData[1] *= v.mData[1];
	mData[2] *= v.mData[2];
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& v)
{
	mData[0] /= v.mData[0];
	mData[1] /= v.mData[1];
	mData[2] /= v.mData[2];
	return *this;
}

Vector3& Vector3::operator+=(const Vector3& v)
{
	mData[0] += v.mData[0];
	mData[1] += v.mData[1];
	mData[2] += v.mData[2];
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
	mData[0] -= v.mData[0];
	mData[1] -= v.mData[1];
	mData[2] -= v.mData[2];
	return *this;
}

Vector3& Vector3::operator*=(F32 s)
{
	mData[0] *= s;
	mData[1] *= s;
	mData[2] *= s;
	return *this;
}

Vector3& Vector3::operator/=(F32 s)
{
	mData[0] /= s;
	mData[1] /= s;
	mData[2] /= s;
	return *this;
}

Vector3& Vector3::operator+=(F32 s)
{
	mData[0] += s;
	mData[1] += s;
	mData[2] += s;
	return *this;
}

Vector3& Vector3::operator-=(F32 s)
{
	mData[0] -= s;
	mData[1] -= s;
	mData[2] -= s;
	return *this;
}

Vector2 Vector3::toVector2() const
{
	return Vector2(mData[0], mData[1]);
}

Vector3 Vector3::toVector3() const
{
	return *this;
}

Vector4 Vector3::toVector4() const
{
	return Vector4(mData[0], mData[1], mData[2], 1.f);
}

bool Vector3::isZero() const
{
	return Math::equals(mData[0], 0.f) && Math::equals(mData[1], 0.f) && Math::equals(mData[2], 0.f);
}

F32 Vector3::getLengthSquared() const
{
	return dotProduct(*this, *this);
}

F32 Vector3::getLength() const
{
	return Math::sqrt(getLengthSquared());
}

void Vector3::setLength(F32 length)
{
	ASSERT(!isZero());
	const F32 actualLength = getLength();
	*this *= (length / actualLength);
}

F32 Vector3::normalize()
{
	const F32 length = getLength();
	ASSERT(length > 0.f);
	*this *= (1.f / length);
	return length;
}

Vector3 Vector3::normalized() const
{
	const F32 length = getLength();
	ASSERT(length > 0.f);
	return *this / length;
}

F32 Vector3::dotProduct(const Vector3& v1, const Vector3& v2)
{
	return v1.mData[0] * v2.mData[0] + v1.mData[1] * v2.mData[1] + v1.mData[2] * v2.mData[2];
}

Vector3 Vector3::hadamardProduct(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.mData[0] * v2.mData[0], v1.mData[1] * v2.mData[1], v1.mData[2] * v2.mData[2]);
}

Vector3 Vector3::crossProduct(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.mData[1] * v2.mData[2] - v1.mData[2] * v2.mData[1], v1.mData[2] * v2.mData[0] - v1.mData[0] * v2.mData[2], v1.mData[0] * v2.mData[1] - v1.mData[1] * v2.mData[0]);
}

F32 Vector3::distance(const Vector3& v1, const Vector3& v2)
{
	return (v1 - v2).getLength();
}

Vector3 Vector3::lerp(const Vector3& v1, const Vector3& v2, F32 percent)
{
	const F32 omp = 1.f - percent;
	return Vector3(omp * v1.mData[0] + percent * v2.mData[0], omp * v1.mData[1] + percent * v2.mData[1], omp * v1.mData[2] + percent * v2.mData[2]);
}

const U8 Vector3::dim()
{
	return 3;
}

const Vector3 Vector3::zeros()
{
	return Vector3(0.f, 0.f, 0.f);
}

const Vector3 Vector3::ones()
{
	return Vector3(1.f, 1.f, 1.f);
}

const Vector3 Vector3::axisX()
{
	return Vector3(1.f, 0.f, 0.f);
}

const Vector3 Vector3::axisY()
{
	return Vector3(0.f, 1.f, 0.f);
}

const Vector3 Vector3::axisZ()
{
	return Vector3(0.f, 0.f, 1.f);
}

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

F32 dot(const Vector3& v1, const Vector3& v2)
{
	return Vector3::dotProduct(v1, v2);
}

Vector3 normalize(const Vector3& v)
{
	return v.normalized();
}

} // namespace oe
