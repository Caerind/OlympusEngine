#ifndef OE_MATRIX3_HPP
#define OE_MATRIX3_HPP

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

namespace oe 
{

class Matrix4;
	
class Matrix3
{
	public:
		Matrix3();
		Matrix3(const Matrix3& m);
		explicit Matrix3(F32 s);
		Matrix3(F32 s00, F32 s10, F32 s20, F32 s01, F32 s11, F32 s21, F32 s02, F32 s12, F32 s22);
		Matrix3(const Vector3& column0, const Vector3& column1, const Vector3& column2);
		explicit Matrix3(const F32* const a);
		explicit Matrix3(const VectorPacked3* vectors);

		F32& operator()(const U8 row, const U8 column);
		const F32& operator()(const U8 row, const U8 column) const;

		F32& operator()(const U8 i);
		const F32& operator()(const U8 i) const;

		F32& operator[](const U8 i);
		const F32& operator[](const U8 i) const;

		void pack(VectorPacked3* vector) const;

		Vector3& getColumn(const U8 i);
		const Vector3& getColumn(const U8 i) const;

		Vector3 getRow(const U8 i) const;

		Matrix3& operator=(const Matrix3& m);

		bool operator==(const Matrix3& m) const;
		bool operator!=(const Matrix3& m) const;
		Matrix3 operator-() const;
		Matrix3 operator+(const Matrix3& m) const;
		Matrix3 operator-(const Matrix3& m) const;
		Matrix3 operator+(const F32& s) const;
		Matrix3 operator-(const F32& s) const;
		Matrix3 operator*(const F32& s) const;
		Matrix3 operator/(const F32& s) const;
		Matrix3 operator*(const Matrix3& m) const;
		Matrix3& operator+=(const Matrix3& m);
		Matrix3& operator-=(const Matrix3& m);
		Matrix3& operator+=(const F32& s);
		Matrix3& operator-=(const F32& s);
		Matrix3& operator*=(const F32& s);
		Matrix3& operator/=(const F32& s);
		Matrix3& operator*=(const Matrix3& m);

		Matrix3 inversed() const;

		Matrix3 transposed() const;

		Matrix4 toMatrix4() const;

		static Matrix3 outerProduct(const Vector3& v1, const Vector3& v2);
		static Matrix3 hadamardProduct(const Matrix3& m1, const Matrix3& m2);

		static Matrix3 identity();

		static Matrix3 rotationX(const Vector2& v);
		static Matrix3 rotationY(const Vector2& v);
		static Matrix3 rotationZ(const Vector2& v);
		static Matrix3 rotationX(F32 angle);
		static Matrix3 rotationY(F32 angle);
		static Matrix3 rotationZ(F32 angle);

		friend Vector3 operator*(const Vector3& v, const Matrix3& m);

		static const U8 rows();
		static const U8 columns();
		static const U8 elements();

	private:
		Vector3 mData[3];
};

Matrix3 operator*(const F32& s, const Matrix3& m);
Vector3 operator*(const Matrix3& m, const Vector3& v);

// Be compatible with GLSL
using mat3 = Matrix3;

} // namespace oe

#endif // OE_MATRIX3_HPP
