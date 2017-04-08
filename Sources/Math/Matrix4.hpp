#ifndef OE_MATRIX4_HPP
#define OE_MATRIX4_HPP

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

namespace oe 
{

class Quaternion;
	
class Matrix4
{
	public:
		Matrix4();
		Matrix4(const F32 m[16]);
		Matrix4(const Matrix4& m);
		Matrix4(F32 a11, F32 a12, F32 a13, F32 a14, F32 a21, F32 a22, F32 a23, F32 a24, F32 a31, F32 a32, F32 a33, F32 a34, F32 a41, F32 a42, F32 a43, F32 a44);
		Matrix4(F32 s);
		~Matrix4() = default;

		Matrix4& set(const F32 m[16]);
		Matrix4& set(const Matrix4& m);
		Matrix4& set(F32 a11, F32 a12, F32 a13, F32 a14, F32 a21, F32 a22, F32 a23, F32 a24, F32 a31, F32 a32, F32 a33, F32 a34, F32 a41, F32 a42, F32 a43, F32 a44);
		Matrix4& set(F32 s);

		operator F32* ();
		operator const F32* () const;
		F32& operator()(const U8 i, const U8 j);
		const F32& operator()(const U8 i, const U8 j) const;

		Vector4 getColumn(const U8 i) const;
		Vector4 getRow(const U8 j) const;

		Matrix4& operator=(const Matrix4& m);
		bool operator==(const Matrix4& m) const;
		bool operator!=(const Matrix4& m) const;
		const Matrix4& operator+() const;
		Matrix4 operator-() const;
		Matrix4 operator+(const Matrix4& m) const;
		Matrix4 operator-(const Matrix4& m) const;
		Matrix4 operator+(const F32& s) const;
		Matrix4 operator-(const F32& s) const;
		Matrix4 operator*(const F32& s) const;
		Matrix4 operator/(const F32& s) const;
		Matrix4 operator*(const Matrix4& m) const;
		Matrix4& operator+=(const Matrix4& m);
		Matrix4& operator-=(const Matrix4& m);
		Matrix4& operator+=(const F32& s);
		Matrix4& operator-=(const F32& s);
		Matrix4& operator*=(const F32& s);
		Matrix4& operator/=(const F32& s);
		Matrix4& operator*=(const Matrix4& m);
		Vector4 operator*(const Vector4& v) const;
		Vector3 operator*(const Vector3& v) const;
		Vector2 operator*(const Vector2& v) const;

		Vector4 transform(const Vector4& v) const;
		Vector3 transform(const Vector3& v, F32 w = 1.0f) const;
		Vector2 transform(const Vector2& v, F32 z = 0.0f, F32 w = 1.0f) const;

		Quaternion getRotation() const;
		Vector3 getSquaredScale() const;
		Vector3 getScale() const;
		Vector3 getTranslation() const;
		F32 getTrace() const;
		F32 getDeterminant() const;
		bool getInverse(Matrix4* m) const;
		Matrix4 getTransposed() const; 
		
		bool hasNegativeScale() const;
		bool hasScale() const;
		bool isAffine() const;
		bool isIdentity() const;

		Matrix4& inverse(bool* succeeded = nullptr);
		Matrix4& transpose();

		Matrix4& setRotation(const Quaternion& rotation);
		Matrix4& setScale(const Vector3& scale);
		Matrix4& setTranslation(const Vector3& translation);

		Matrix4& applyRotation(const Quaternion& rotation);
		Matrix4& applyScale(const Vector3& scale);
		Matrix4& applyTranslation(const Vector3& translation);

		Matrix4& makeRotation(const Quaternion& rotation);
		Matrix4& makeScale(const Vector3& scale);
		Matrix4& makeTranslation(const Vector3& translation);
		Matrix4& makeTransform(const Vector3& translation, const Quaternion& rotation);
		Matrix4& makeTransform(const Vector3& translation, const Quaternion& rotation, const Vector3& scale);

		Matrix4& makeViewMatrix(const Vector3& translation, const Quaternion& rotation);
		Matrix4& makeLookAt(const Vector3& eye, const Vector3& target, const Vector3& up = Vector3::up());
		Matrix4& makeOrtho(F32 left, F32 right, F32 top, F32 bottom, F32 zNear, F32 zFar);
		Matrix4& makeOrtho(F32 width, F32 height, F32 zNear, F32 zFar);
		Matrix4& makePerspective(F32 angle, F32 ratio, F32 zNear, F32 zFar);

		Matrix4& makeZero();
		Matrix4& makeIdentity();

		static Matrix4 rotate(const Quaternion& rotation);
		static Matrix4 scale(const Vector3& scale);
		static Matrix4 translate(const Vector3& translation);
		static Matrix4 transform(const Vector3& translation, const Quaternion& rotation);
		static Matrix4 transform(const Vector3& translation, const Quaternion& rotation, const Vector3& scale);

		static Matrix4 viewMatrix(const Vector3& translation, const Quaternion& rotation);
		static Matrix4 lookAt(const Vector3& eye, const Vector3& target, const Vector3& up = Vector3::up());
		static Matrix4 ortho(F32 left, F32 right, F32 top, F32 bottom, F32 zNear, F32 zFar);
		static Matrix4 ortho(F32 width, F32 height, F32 zNear, F32 zFar);
		static Matrix4 perspective(F32 angle, F32 ratio, F32 zNear, F32 zFar);

		static const Matrix4 zero();
		static const Matrix4 identity();

		static const U8 rows();
		static const U8 columns();
		static const U8 elements();

		F32 m11, m12, m13, m14,
			m21, m22, m23, m24,
			m31, m32, m33, m34,
			m41, m42, m43, m44;
};

Matrix4 operator*(F32 s, const Matrix4& m);
Matrix4 operator+(F32 s, const Matrix4& m);
Matrix4 operator-(F32 s, const Matrix4& m);

// Be compatible with GLSL
using mat4 = Matrix4;

// To String / From String conversions
template <>
inline std::string toString<Matrix4>(const Matrix4& m)
{
	std::ostringstream oss;
	oss << toString<F32>(m.m11) << ',' << toString<F32>(m.m12) << ',' << toString<F32>(m.m13) << ',' << toString<F32>(m.m14) << ',';
	oss << toString<F32>(m.m21) << ',' << toString<F32>(m.m22) << ',' << toString<F32>(m.m23) << ',' << toString<F32>(m.m24) << ',';
	oss << toString<F32>(m.m31) << ',' << toString<F32>(m.m32) << ',' << toString<F32>(m.m33) << ',' << toString<F32>(m.m34) << ',';
	oss << toString<F32>(m.m41) << ',' << toString<F32>(m.m42) << ',' << toString<F32>(m.m43) << ',' << toString<F32>(m.m44);
	return oss.str();
}

template <>
inline Matrix4 fromString<Matrix4>(const std::string& string)
{
	std::string str(string);
	Matrix4 m;
	m[0] = fromString<F32>(split(str, ','));
	m[1] = fromString<F32>(split(str, ','));
	m[2] = fromString<F32>(split(str, ','));
	m[3] = fromString<F32>(split(str, ','));
	m[4] = fromString<F32>(split(str, ','));
	m[5] = fromString<F32>(split(str, ','));
	m[6] = fromString<F32>(split(str, ','));
	m[7] = fromString<F32>(split(str, ','));
	m[8] = fromString<F32>(split(str, ','));
	m[9] = fromString<F32>(split(str, ','));
	m[10] = fromString<F32>(split(str, ','));
	m[11] = fromString<F32>(split(str, ','));
	m[12] = fromString<F32>(split(str, ','));
	m[13] = fromString<F32>(split(str, ','));
	m[14] = fromString<F32>(split(str, ','));
	m[15] = fromString<F32>(str);
	return m;
}

} // namespace oe

#endif // OE_MATRIX4_HPP
