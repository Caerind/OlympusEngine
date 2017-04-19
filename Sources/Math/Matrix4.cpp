#include "Matrix4.hpp"
#include "Quaternion.hpp"

// TODO : Speed up all calculation for Affine Matrix

namespace oe
{

Matrix4::Matrix4()
	: m11(0.0f)
	, m12(0.0f)
	, m13(0.0f)
	, m14(0.0f)
	, m21(0.0f)
	, m22(0.0f)
	, m23(0.0f)
	, m24(0.0f)
	, m31(0.0f)
	, m32(0.0f)
	, m33(0.0f)
	, m34(0.0f)
	, m41(0.0f)
	, m42(0.0f)
	, m43(0.0f)
	, m44(0.0f)
{
}

Matrix4::Matrix4(const F32 m[16])
{
	set(m);
}

Matrix4::Matrix4(const Matrix4& m)
{
	set(m);
}

Matrix4::Matrix4(F32 a11, F32 a12, F32 a13, F32 a14, F32 a21, F32 a22, F32 a23, F32 a24, F32 a31, F32 a32, F32 a33, F32 a34, F32 a41, F32 a42, F32 a43, F32 a44)
{
	set(a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44);
}

Matrix4::Matrix4(F32 s)
{
	set(s);
}

Matrix4& Matrix4::set(const F32 m[16])
{
	std::memcpy(&m11, m, 16 * sizeof(F32));
	return *this;
}

Matrix4& Matrix4::set(const Matrix4& m)
{
	std::memcpy(this, &m, sizeof(Matrix4));
	return *this;
}

Matrix4& Matrix4::set(F32 a11, F32 a12, F32 a13, F32 a14, F32 a21, F32 a22, F32 a23, F32 a24, F32 a31, F32 a32, F32 a33, F32 a34, F32 a41, F32 a42, F32 a43, F32 a44)
{
	m11 = a11;
	m12 = a12;
	m13 = a13;
	m14 = a14;
	m21 = a21;
	m22 = a22;
	m23 = a23;
	m24 = a24;
	m31 = a31;
	m32 = a32;
	m33 = a33;
	m34 = a34;
	m41 = a41;
	m42 = a42;
	m43 = a43;
	m44 = a44;
	return *this;
}

Matrix4& Matrix4::set(F32 s)
{
	m11 = s;
	m12 = s;
	m13 = s;
	m14 = s;
	m21 = s;
	m22 = s;
	m23 = s;
	m24 = s;
	m31 = s;
	m32 = s;
	m33 = s;
	m34 = s;
	m41 = s;
	m42 = s;
	m43 = s;
	m44 = s;
	return *this;
}

Matrix4::operator F32*()
{
	return &m11;
}

Matrix4::operator const F32*() const
{
	return &m11;
}

F32& Matrix4::operator()(const U8 i, const U8 j)
{
	return (&m11)[j * 4 + i];
}

const F32& Matrix4::operator()(const U8 i, const U8 j) const
{
	return (&m11)[j * 4 + i];
}

Vector4 Matrix4::getColumn(const U8 i) const
{
	ASSERT(i <= 3);
	return Vector4((&m11)[i], (&m11)[i + 4], (&m11)[i + 8], (&m11)[i + 12]);
}

Vector4 Matrix4::getRow(const U8 j) const
{
	ASSERT(j <= 3);
	return Vector4((&m11) + j * 4);
}

Matrix4& Matrix4::operator=(const Matrix4& m)
{
	set(m);
	return *this;
}

bool Matrix4::operator==(const Matrix4& m) const
{
	for (U8 i = 0; i < 16; i++)
	{
		if (!Math::equals((&m11)[i], (&m.m11)[i]))
		{
			return false;
		}
	}
	return true;
}

bool Matrix4::operator!=(const Matrix4 & m) const
{
	return !operator==(m);
}

const Matrix4& Matrix4::operator+() const
{
	return *this;
}

Matrix4 Matrix4::operator-() const
{
	Matrix4 result;
	for (U8 i = 0; i < 16; i++)
	{
		(&result.m11)[i] = -(&m11)[i];
	}
	return result;
}

Matrix4 Matrix4::operator+(const Matrix4& m) const
{
	Matrix4 result;
	for (U8 i = 0; i < 16; i++)
	{
		(&result.m11)[i] = (&m11)[i] + (&m.m11)[i];
	}
	return result;
}

Matrix4 Matrix4::operator-(const Matrix4& m) const
{
	Matrix4 result;
	for (U8 i = 0; i < 16; i++)
	{
		(&result.m11)[i] = (&m11)[i] - (&m.m11)[i];
	}
	return result;
}

Matrix4 Matrix4::operator+(const F32& s) const
{
	Matrix4 result;
	for (U8 i = 0; i < 16; i++)
	{
		(&result.m11)[i] = (&m11)[i] + s;
	}
	return result;
}

Matrix4 Matrix4::operator-(const F32& s) const
{
	Matrix4 result;
	for (U8 i = 0; i < 16; i++)
	{
		(&result.m11)[i] = (&m11)[i] - s;
	}
	return result;
}

Matrix4 Matrix4::operator*(const F32& s) const
{
	Matrix4 result;
	for (U8 i = 0; i < 16; i++)
	{
		(&result.m11)[i] = (&m11)[i] * s;
	}
	return result;
}

Matrix4 Matrix4::operator/(const F32& s) const
{
	return (*this) * (1.0f / s);
}

Matrix4 Matrix4::operator*(const Matrix4& m) const
{
	return Matrix4(m11 * m.m11 + m12 * m.m21 + m13 * m.m31 + m14 * m.m41,
		           m11 * m.m12 + m12 * m.m22 + m13 * m.m32 + m14 * m.m42,
		           m11 * m.m13 + m12 * m.m23 + m13 * m.m33 + m14 * m.m43,
		           m11 * m.m14 + m12 * m.m24 + m13 * m.m34 + m14 * m.m44,
		           m21 * m.m11 + m22 * m.m21 + m23 * m.m31 + m24 * m.m41,
		           m21 * m.m12 + m22 * m.m22 + m23 * m.m32 + m24 * m.m42,
		           m21 * m.m13 + m22 * m.m23 + m23 * m.m33 + m24 * m.m43,
		           m21 * m.m14 + m22 * m.m24 + m23 * m.m34 + m24 * m.m44,
		           m31 * m.m11 + m32 * m.m21 + m33 * m.m31 + m34 * m.m41,
		           m31 * m.m12 + m32 * m.m22 + m33 * m.m32 + m34 * m.m42,
		           m31 * m.m13 + m32 * m.m23 + m33 * m.m33 + m34 * m.m43,
		           m31 * m.m14 + m32 * m.m24 + m33 * m.m34 + m34 * m.m44,
		           m41 * m.m11 + m42 * m.m21 + m43 * m.m31 + m44 * m.m41,
		           m41 * m.m12 + m42 * m.m22 + m43 * m.m32 + m44 * m.m42,
		           m41 * m.m13 + m42 * m.m23 + m43 * m.m33 + m44 * m.m43,
		           m41 * m.m14 + m42 * m.m24 + m43 * m.m34 + m44 * m.m44);
}

Matrix4& Matrix4::operator+=(const Matrix4& m)
{
	for (U8 i = 0; i < 16; i++)
	{
		(&m11)[i] += (&m.m11)[i];
	}
	return *this;
}

Matrix4& Matrix4::operator-=(const Matrix4& m)
{
	for (U8 i = 0; i < 16; i++)
	{
		(&m11)[i] -= (&m.m11)[i];
	}
	return *this;
}

Matrix4& Matrix4::operator+=(const F32& s)
{
	for (U8 i = 0; i < 16; i++)
	{
		(&m11)[i] += s;
	}
	return *this;
}

Matrix4& Matrix4::operator-=(const F32& s)
{
	for (U8 i = 0; i < 16; i++)
	{
		(&m11)[i] -= s;
	}
	return *this;
}

Matrix4& Matrix4::operator*=(const F32& s)
{
	for (U8 i = 0; i < 16; i++)
	{
		(&m11)[i] *= s;
	}
	return *this;
}

Matrix4& Matrix4::operator/=(const F32& s)
{
	return (*this) *= (1.0f / s);
}

Matrix4& Matrix4::operator*=(const Matrix4& m)
{
	Matrix4 temp(*this * m);
	return set(temp);
}

Vector4 Matrix4::operator*(const Vector4& v) const
{
	return transform(v);
}

Vector3 Matrix4::operator*(const Vector3& v) const
{
	return transform(v);
}

Vector2 Matrix4::operator*(const Vector2& v) const
{
	return transform(v);
}

Vector4 Matrix4::transform(const Vector4& v) const
{
	return Vector4(m11 * v.x + m12 * v.y + m13 * v.z + m14 * v.w,
		           m21 * v.x + m22 * v.y + m23 * v.z + m24 * v.w,
		           m31 * v.x + m32 * v.y + m33 * v.z + m34 * v.w,
		           m41 * v.x + m42 * v.y + m43 * v.z + m44 * v.w);
}

Vector3 Matrix4::transform(const Vector3& v, F32 w) const
{
	return Vector3(m11 * v.x + m12 * v.y + m13 * v.z + m14 * w,
		           m21 * v.x + m22 * v.y + m23 * v.z + m24 * w,
		           m31 * v.x + m32 * v.y + m33 * v.z + m34 * w);
}

Vector2 Matrix4::transform(const Vector2& v, F32 z, F32 w) const
{
	return Vector2(m11 * v.x + m12 * v.y + m13 * z + m14 * w,
		           m21 * v.x + m22 * v.y + m23 * z + m24 * w);
}

Quaternion Matrix4::getRotation() const
{
	F32 trace = m11 + m22 + m33;
	if (trace > 0.0f)
	{
		const F32 s = 0.5f / Math::sqrt(trace + 1.0f);
		return Quaternion((m32 - m23) * s, (m13 - m31) * s, (m21 - m12) * s, 0.25f / s);
	}
	else if (m11 > m22 && m11 > m33)
	{
		const F32 s = 2.0f * Math::sqrt(1.0f + m11 - m22 - m33);
		return Quaternion(0.25f * s, (m12 + m21) / s, (m13 + m31) / s, (m32 - m23) / s);
	}
	else if (m22 > m33)
	{
		const F32 s = 2.0f * Math::sqrt(1.0f + m22 - m11 - m33);
		return Quaternion((m12 + m21) / s, 0.25f * s, (m23 + m32) / s, (m13 - m31) / s);
	}
	else
	{
		const F32 s = 2.0f * Math::sqrt(1.0f + m33 - m11 - m22);
		return Quaternion((m13 + m31) / s, (m23 + m32) / s, 0.25f * s, (m21 - m12) / s);
	}
}

Vector3 Matrix4::getSquaredScale() const
{
	return Vector3(m11 * m11 + m21 * m21 + m31 * m31,  m12 * m12 + m22 * m22 + m32 * m32, m13 * m13 + m23 * m23 + m33 * m33);
}

Vector3 Matrix4::getScale() const
{
	Vector3 squaredScale = getSquaredScale();
	return Vector3(Math::sqrt(squaredScale.x), Math::sqrt(squaredScale.y), Math::sqrt(squaredScale.z));
}

Vector3 Matrix4::getTranslation() const
{
	return Vector3(m14, m24, m34);
}

F32 Matrix4::getTrace() const
{
	return m11 + m22 + m33 + m44;
}

F32 Matrix4::getDeterminant() const
{
	// We will use the last row of the matrix
	// Because if the matrix is affine it will be faster

	// Compute det2x2
	const F32 m22m33 = m22 * m33 - m32 * m23;
	const F32 m21m33 = m21 * m33 - m31 * m23;
	const F32 m21m32 = m21 * m32 - m31 * m22;

	if (isAffine())
	{
		// If affine, the last row is full of zero except the last one
		// Return the det of the 3x3
		return m11 * m22m33 - m12 * m21m33 + m13 * m21m32;
	}
	else
	{
		// Compute det2x2, each det2x2 is used 2 times for the det3
		const F32 m21m34 = m21 * m34 - m31 * m24;
		const F32 m22m34 = m22 * m34 - m32 * m24;
		const F32 m23m34 = m23 * m24 - m33 * m24;

		// Compute det3x3
		const F32 a = m12 * m23m34 - m13 * m22m34 + m14 * m22m33;
		const F32 b = m11 * m23m34 - m13 * m21m34 + m14 * m21m33;
		const F32 c = m11 * m22m34 - m12 * m21m34 + m14 * m21m32;
		const F32 d = m11 * m22m33 - m12 * m21m33 + m13 * m21m32;

		// Return the det of the 4x4
		return a - b + c - d;
	}
}

bool Matrix4::getInverse(Matrix4* m) const
{
	// http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
	if (m == nullptr)
	{
		return false;
	}
	F32 det = m->getDeterminant();
	if (Math::equals(det, 0.0f))
	{
		return false;
	}
	F32 com[16];
	com[0] = m22 * m33 * m44 -
		m22 * m34 * m43 -
		m32 * m23 * m44 +
		m32 * m24 * m43 +
		m42 * m23 * m34 -
		m42 * m24 * m33;

	com[1] = -m12 * m33 * m44 +
		m12 * m34 * m43 +
		m32 * m13 * m44 -
		m32 * m14 * m43 -
		m42 * m13 * m34 +
		m42 * m14 * m33;

	com[2] = m12 * m23 * m44 -
		m12 * m24 * m43 -
		m22 * m13 * m44 +
		m22 * m14 * m43 +
		m42 * m13 * m24 -
		m42 * m14 * m23;

	com[3] = -m12 * m23 * m34 +
		m12 * m24 * m33 +
		m22 * m13 * m34 -
		m22 * m14 * m33 -
		m32 * m13 * m24 +
		m32 * m14 * m23;

	com[4] = -m21 * m33 * m44 +
		m21 * m34 * m43 +
		m31 * m23 * m44 -
		m31 * m24 * m43 -
		m41 * m23 * m34 +
		m41 * m24 * m33;

	com[5] = m11 * m33 * m44 -
		m11 * m34 * m43 -
		m31 * m13 * m44 +
		m31 * m14 * m43 +
		m41 * m13 * m34 -
		m41 * m14 * m33;

	com[6] = -m11 * m23 * m44 +
		m11 * m24 * m43 +
		m21 * m13 * m44 -
		m21 * m14 * m43 -
		m41 * m13 * m24 +
		m41 * m14 * m23;

	com[7] = m11 * m23 * m34 -
		m11 * m24 * m33 -
		m21 * m13 * m34 +
		m21 * m14 * m33 +
		m31 * m13 * m24 -
		m31 * m14 * m23;

	com[8] = m21 * m32 * m44 -
		m21 * m34 * m42 -
		m31 * m22 * m44 +
		m31 * m24 * m42 +
		m41 * m22 * m34 -
		m41 * m24 * m32;

	com[9] = -m11 * m32 * m44 +
		m11 * m34 * m42 +
		m31 * m12 * m44 -
		m31 * m14 * m42 -
		m41 * m12 * m34 +
		m41 * m14 * m32;

	com[10] = m11 * m22 * m44 -
		m11 * m24 * m42 -
		m21 * m12 * m44 +
		m21 * m14 * m42 +
		m41 * m12 * m24 -
		m41 * m14 * m22;

	com[11] = -m11 * m22 * m34 +
		m11 * m24 * m32 +
		m21 * m12 * m34 -
		m21 * m14 * m32 -
		m31 * m12 * m24 +
		m31 * m14 * m22;

	com[12] = -m21 * m32 * m43 +
		m21 * m33 * m42 +
		m31 * m22 * m43 -
		m31 * m23 * m42 -
		m41 * m22 * m33 +
		m41 * m23 * m32;

	com[13] = m11 * m32 * m43 -
		m11 * m33 * m42 -
		m31 * m12 * m43 +
		m31 * m13 * m42 +
		m41 * m12 * m33 -
		m41 * m13 * m32;

	com[14] = -m11 * m22 * m43 +
		m11 * m23 * m42 +
		m21 * m12 * m43 -
		m21 * m13 * m42 -
		m41 * m12 * m23 +
		m41 * m13 * m22;

	com[15] = m11 * m22 * m33 -
		m11 * m23 * m32 -
		m21 * m12 * m33 +
		m21 * m13 * m32 +
		m31 * m12 * m23 -
		m31 * m13 * m22;

	F32 invDet = 1.0f / det;
	for (U8 i = 0; i < 16; i++)
	{
		com[i] *= invDet;
	}
	m->set(com);
	return true;
}

Matrix4 Matrix4::getTransposed() const
{
	return Matrix4(m11, m21, m31, m41,
		           m12, m22, m32, m42,
		           m13, m23, m33, m43,
		           m14, m24, m34, m44);
}

bool Matrix4::hasNegativeScale() const
{
	return getDeterminant() < 0.0f;
}

bool Matrix4::hasScale() const
{
	return getSquaredScale() != Vector3::one();
}

bool Matrix4::isAffine() const
{
	return Math::equals(m41, 0.0f) && Math::equals(m42, 0.0f) && Math::equals(m43, 0.0f) && Math::equals(m44, 1.0f);
}

bool Matrix4::isIdentity() const
{
	return (Math::equals(m11, 1.0f) && Math::equals(m12, 0.0f) && Math::equals(m13, 0.0f) && Math::equals(m14, 0.0f) &&
		Math::equals(m21, 0.0f) && Math::equals(m22, 1.0f) && Math::equals(m23, 0.0f) && Math::equals(m24, 0.0f) &&
		Math::equals(m31, 0.0f) && Math::equals(m32, 0.0f) && Math::equals(m33, 1.0f) && Math::equals(m34, 0.0f) &&
		Math::equals(m41, 0.0f) && Math::equals(m42, 0.0f) && Math::equals(m43, 0.0f) && Math::equals(m44, 1.0f));
}

Matrix4& Matrix4::inverse(bool* succeeded)
{
	bool result = getInverse(this);
	if (succeeded != nullptr)
	{
		*succeeded = result;
	}
	return *this;
}

Matrix4& Matrix4::transpose()
{
	std::swap(m12, m21);
	std::swap(m13, m31);
	std::swap(m14, m41);
	std::swap(m23, m32);
	std::swap(m24, m42);
	std::swap(m34, m43);
	return *this;
}

Matrix4& Matrix4::setRotation(const Quaternion& rotation)
{
	const F32 x2 = rotation.x * rotation.x;
	const F32 y2 = rotation.y * rotation.y;
	const F32 z2 = rotation.z * rotation.z;
	const F32 sx = rotation.w * rotation.x;
	const F32 sy = rotation.w * rotation.y;
	const F32 sz = rotation.w * rotation.z;
	const F32 xz = rotation.x * rotation.z;
	const F32 yz = rotation.y * rotation.z;
	const F32 xy = rotation.x * rotation.y;

	m11 = 1.0f - 2.0f * (y2 + z2);
	m12 = 2.0f * (xy + sz);
	m13 = 2.0f * (xz - sy);

	m21 = 2.0f * (xy - sz);
	m22 = 1.0f - 2.0f * (x2 + z2);
	m23 = 2.0f * (sx + yz);

	m31 = 2.0f * (sy + xz);
	m32 = 2.0f * (yz - sx);
	m33 = 1.0f - 2.0f * (x2 + y2);

	return *this;
}

Matrix4& Matrix4::setScale(const Vector3& scale)
{
	m11 = scale.x;
	m22 = scale.y;
	m33 = scale.z;
	return *this;
}

Matrix4& Matrix4::setTranslation(const Vector3& translation)
{
	m14 = translation.x;
	m24 = translation.y;
	m34 = translation.z;
	return *this;
}

Matrix4& Matrix4::applyRotation(const Quaternion& rotation)
{
	return operator*=(Matrix4::rotate(rotation));
}

Matrix4& Matrix4::applyScale(const Vector3& scale)
{
	m11 *= scale.x;
	m21 *= scale.x;
	m31 *= scale.x;

	m12 *= scale.y;
	m22 *= scale.y;
	m32 *= scale.y;

	m13 *= scale.z;
	m23 *= scale.z;
	m33 *= scale.z;

	return *this;
}

Matrix4& Matrix4::applyTranslation(const Vector3& translation)
{
	m14 += translation.x;
	m24 += translation.y;
	m34 += translation.z;

	return *this;
}

Matrix4& Matrix4::makeRotation(const Quaternion& rotation)
{
	setRotation(rotation);
	m14 = 0.0f;
	m24 = 0.0f;
	m34 = 0.0f;
	m44 = 0.0f;
	m43 = 0.0f;
	m42 = 0.0f;
	m41 = 0.0f;
	return *this;
}

Matrix4& Matrix4::makeScale(const Vector3& scale)
{
	return set(scale.x, 0.0f, 0.0f, 0.0f, 0.0f, scale.y, 0.0f, 0.0f, 0.0f, 0.0f, scale.z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4& Matrix4::makeTranslation(const Vector3& translation)
{
	return set(1.0f, 0.0f, 0.0f, translation.x, 0.0f, 1.0f, 0.0f, translation.y, 0.0f, 0.0f, 1.0f, translation.z, 0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4& Matrix4::makeTransform(const Vector3& translation, const Quaternion& rotation)
{
	setTranslation(translation);
	setRotation(rotation);

	m41 = 0.0f;
	m42 = 0.0f;
	m43 = 0.0f;
	m44 = 1.0f;

	return *this;
}

Matrix4& Matrix4::makeTransform(const Vector3& translation, const Quaternion& rotation, const Vector3& scale)
{
	return makeTransform(translation, rotation).applyScale(scale);
}

Matrix4& Matrix4::makeViewMatrix(const Vector3& translation, const Quaternion& rotation)
{
	// A view matrix must apply an inverse transformation of the 'world' matrix
	Quaternion invRot = rotation.getConjugate(); // Inverse of the rotation
	return makeTransform(-(invRot * translation), invRot);
}

Matrix4& Matrix4::makeLookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
{
	Vector3 a((target - eye).getNormal());
	Vector3 b(a.crossProduct(up).getNormal());
	Vector3 c(a.crossProduct(b));
	Vector3 d(b.dotProduct(eye), -c.dotProduct(eye), a.dotProduct(eye));
	return set(-a.x, -b.x, c.x, d.x,
		       -a.y, -b.y, c.y, d.y,
		       -a.z, -b.z, c.z, d.z,
		       0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4& Matrix4::makeOrtho(F32 left, F32 right, F32 top, F32 bottom, F32 zNear, F32 zFar)
{
	return set(2.0f / (right - left), 0.0f, 0.0f, 0.0f,
		       0.0f, 2.0f / (top - bottom), 0.0f, 0.0f,
		       0.0f, 0.0f, 2.0f / (zNear - zFar), 0.0f,
		       (left + right) / (left - right), (top + bottom) / (bottom - top), (zFar + zNear) / (zNear - zFar), 1.0f);
}

Matrix4& Matrix4::makeOrtho(F32 width, F32 height, F32 zNear, F32 zFar)
{
	return makeOrtho(width * -0.5f, width * 0.5f, height * 0.5f, height * -0.5f, zNear, zFar);
}

Matrix4& Matrix4::makePerspective(F32 angle, F32 ratio, F32 zNear, F32 zFar)
{
	const F32 y = Math::tan(90.f - angle * 0.5f);
	const F32 x = y / ratio;
	const F32 zDist = (zNear - zFar);
	const F32 zFarzDist = zFar / zDist;
	return set(x, 0.0f, 0.0f, 0.0f,
		       0.0f, y, 0.0f, 0.0f,
		       0.0f, 0.0f, zFarzDist, -1.0f,
		       0.0f, 0.0f, 2.0f * zNear * zFarzDist, 0.0f);
}

Matrix4& Matrix4::makeZero()
{
	return set(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

Matrix4& Matrix4::makeIdentity()
{
	return set(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 Matrix4::rotate(const Quaternion& rotation)
{
	return Matrix4().makeRotation(rotation);
}

Matrix4 Matrix4::scale(const Vector3& scale)
{
	return Matrix4().makeScale(scale);
}

Matrix4 Matrix4::translate(const Vector3& translation)
{
	return Matrix4().makeTranslation(translation);
}

Matrix4 Matrix4::transform(const Vector3& translation, const Quaternion& rotation)
{
	return Matrix4().makeTransform(translation, rotation);
}

Matrix4 Matrix4::transform(const Vector3& translation, const Quaternion& rotation, const Vector3& scale)
{
	return Matrix4().makeTransform(translation, rotation, scale);
}

Matrix4 Matrix4::viewMatrix(const Vector3& translation, const Quaternion& rotation)
{
	return Matrix4().makeViewMatrix(translation, rotation);
}

Matrix4 Matrix4::lookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
{
	return Matrix4().makeLookAt(eye, target, up);
}

Matrix4 Matrix4::ortho(F32 left, F32 right, F32 top, F32 bottom, F32 zNear, F32 zFar)
{
	return Matrix4().makeOrtho(left, right, top, bottom, zNear, zFar);
}

Matrix4 Matrix4::ortho(F32 width, F32 height, F32 zNear, F32 zFar)
{
	return Matrix4().makeOrtho(width, height, zNear, zFar);
}

Matrix4 Matrix4::perspective(F32 angle, F32 ratio, F32 zNear, F32 zFar)
{
	return Matrix4().makePerspective(angle, ratio, zNear, zFar);
}

const Matrix4 Matrix4::zero()
{
	return Matrix4(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

const Matrix4 Matrix4::identity()
{
	return Matrix4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

const U8 Matrix4::rows()
{
	return 4;
}

const U8 Matrix4::columns()
{
	return 4;
}

const U8 Matrix4::elements()
{
	return 16;
}

Matrix4 operator*(F32 s, const Matrix4 & m)
{
	return m * s;
}

Matrix4 operator+(F32 s, const Matrix4& m)
{
	return m + s;
}

Matrix4 operator-(F32 s, const Matrix4& m)
{
	return (m - s) * 1.0f;
}

} // namespace oe
