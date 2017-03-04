#ifndef OE_MATRIX4_HPP
#define OE_MATRIX4_HPP

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

namespace oe 
{

class Matrix3;
class MatrixAffine;
	
class Matrix4
{
	public:
		Matrix4();
		Matrix4(const Matrix4& m);
		explicit Matrix4(F32 s);
		Matrix4(F32 s00, F32 s10, F32 s20, F32 s30, F32 s01, F32 s11, F32 s21, F32 s31, F32 s02, F32 s12, F32 s22, F32 s32, F32 s03, F32 s13, F32 s23, F32 s33);
		Matrix4(const Vector4& column0, const Vector4& column1, const Vector4& column2, const Vector4& column3);
		explicit Matrix4(const F32* const a);
		explicit Matrix4(const VectorPacked4* vectors);

		F32& operator()(const U8 row, const U8 column);
		const F32& operator()(const U8 row, const U8 column) const;

		F32& operator()(const U8 i);
		const F32& operator()(const U8 i) const;

		F32& operator[](const U8 i);
		const F32& operator[](const U8 i) const;

		void pack(VectorPacked4* vector) const;

		Vector4& getColumn(const U8 i);
		const Vector4& getColumn(const U8 i) const;

		Vector4 getRow(const U8 i) const;

		Matrix4& operator=(const Matrix4& m);

		bool operator==(const Matrix4& m) const;
		bool operator!=(const Matrix4& m) const;
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

		Matrix4 inversed() const;

		Matrix4 transposed() const;

		Vector2 translationVector2D() const;
		Vector3 translationVector3D() const;
		Vector4 translationVector4D() const;

		static Matrix4 outerProduct(const Vector4& v1, const Vector4& v2);
		static Matrix4 hadamardProduct(const Matrix4& m1, const Matrix4& m2);

		static Matrix4 identity();

		static Matrix4 fromTranslationVector(const Vector2& v);
		static Matrix4 fromTranslationVector(const Vector3& v);
		static Matrix4 fromTranslationVector(const Vector4& v);
		static Matrix4 fromScaleVector(const Vector3& v);

		static Matrix4 fromRotationMatrix(const Matrix3& m);

		// TODO : MatrixAffine
		//static Matrix4 fromAffineTransform(const MatrixAffine& affine);
		//static MatrixAffine toAffineTransform(const Matrix4& m);

		static Matrix4 rotationX(const Vector2& v);
		static Matrix4 rotationY(const Vector2& v);
		static Matrix4 rotationZ(const Vector2& v);
		static Matrix4 rotationX(F32 angle);
		static Matrix4 rotationY(F32 angle);
		static Matrix4 rotationZ(F32 angle);

		static Matrix4 perspective(F32 fovy, F32 aspect, F32 znear, F32 zfar, F32 handedness = 1.f);
		static Matrix4 ortho(F32 left, F32 right, F32 bottom, F32 top, F32 znear, F32 zfar, F32 handedness = 1.f);
		static Matrix4 lookAt(const Vector3& at, const Vector3& eye, const Vector3& up, F32 handedness = -1.f);
		static Vector3 unProject(const Vector3& window_coord, const Matrix4& model_view, const Matrix4& projection, const F32 window_width, const F32 window_height);

		friend Vector4 operator*(const Vector4& v, const Matrix4& m);

		static const U8 rows();
		static const U8 columns();
		static const U8 elements();

	private:
		Vector4 mData[4];
};

Matrix4 operator*(const F32& s, const Matrix4& m);
Vector4 operator*(const Matrix4& m, const Vector4& v);
Vector3 operator*(const Matrix4& m, const Vector3& v);
Vector2 operator*(const Matrix4& m, const Vector2& v);

// Be compatible with GLSL
using mat4 = Matrix4;

} // namespace oe

#endif // OE_MATRIX4_HPP
