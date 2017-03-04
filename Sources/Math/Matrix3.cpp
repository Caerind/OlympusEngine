#include "Matrix3.hpp"
#include "Matrix4.hpp"

namespace oe
{

Matrix3::Matrix3()
	: mData()
{
}

Matrix3::Matrix3(const Matrix3& m)
{
	mData[0] = m.mData[0];
	mData[1] = m.mData[1];
	mData[2] = m.mData[2];
}

Matrix3::Matrix3(F32 s)
{
	mData[0] = Vector3(s);
	mData[1] = Vector3(s);
	mData[2] = Vector3(s);
}

Matrix3::Matrix3(F32 s00, F32 s10, F32 s20, F32 s01, F32 s11, F32 s21, F32 s02, F32 s12, F32 s22)
{
	mData[0] = Vector3(s00, s10, s20);
	mData[1] = Vector3(s01, s11, s21);
	mData[2] = Vector3(s02, s12, s22);
}

Matrix3::Matrix3(const Vector3& column0, const Vector3& column1, const Vector3& column2)
{
	mData[0] = column0;
	mData[1] = column1;
	mData[2] = column2;
}

Matrix3::Matrix3(const F32* const a)
{
	mData[0] = Vector3(&a[0]);
	mData[1] = Vector3(&a[3]);
	mData[2] = Vector3(&a[6]);
}

Matrix3::Matrix3(const VectorPacked3* vectors)
{
	mData[0] = Vector3(vectors[0]);
	mData[1] = Vector3(vectors[1]);
	mData[2] = Vector3(vectors[2]);
}

F32& Matrix3::operator()(const U8 row, const U8 column)
{
	return mData[column][row];
}

const F32& Matrix3::operator()(const U8 row, const U8 column) const
{
	return mData[column][row];
}

F32& Matrix3::operator()(const U8 i)
{
	return operator[](i);
}

const F32& Matrix3::operator()(const U8 i) const
{
	return operator[](i);
}

F32& Matrix3::operator[](const U8 i)
{
	return reinterpret_cast<F32*>(mData)[i];
}

const F32& Matrix3::operator[](const U8 i) const
{
	return const_cast<Matrix3*>(this)->operator[](i);
}

void Matrix3::pack(VectorPacked3* vector) const
{
	getColumn(0).pack(&vector[0]);
	getColumn(1).pack(&vector[1]);
	getColumn(2).pack(&vector[2]);
}

Vector3& Matrix3::getColumn(const U8 i)
{
	return mData[i];
}

const Vector3& Matrix3::getColumn(const U8 i) const
{
	return mData[i];
}

Vector3 Matrix3::getRow(const U8 i) const
{
	return Vector3(mData[0][i], mData[1][i], mData[2][i]);
}

Matrix3& Matrix3::operator=(const Matrix3& m)
{
	for (U8 i = 0; i < 3; i++)
	{
		mData[i] = m.mData[i];
	}
	return *this;
}

bool Matrix3::operator==(const Matrix3& m) const
{
	for (U8 i = 0; i < 3; i++)
	{
		if (mData[i] != m.mData[i])
		{
			return false;
		}
	}
	return true;
}

bool Matrix3::operator!=(const Matrix3 & m) const
{
	return !operator==(m);
}

Matrix3 Matrix3::operator-() const
{
	Matrix3 result;
	for (U8 i = 0; i < 3; i++)
	{
		result.mData[i] = -mData[i];
	}
	return result;
}

Matrix3 Matrix3::operator+(const Matrix3& m) const
{
	Matrix3 result;
	for (U8 i = 0; i < 3; i++)
	{
		result.mData[i] = mData[i] + m.mData[i];
	}
	return result;
}

Matrix3 Matrix3::operator-(const Matrix3& m) const
{
	Matrix3 result;
	for (U8 i = 0; i < 3; i++)
	{
		result.mData[i] = mData[i] - m.mData[i];
	}
	return result;
}

Matrix3 Matrix3::operator+(const F32& s) const
{
	Matrix3 result;
	for (U8 i = 0; i < 3; i++)
	{
		result.mData[i] = mData[i] + s;
	}
	return result;
}

Matrix3 Matrix3::operator-(const F32& s) const
{
	Matrix3 result;
	for (U8 i = 0; i < 3; i++)
	{
		result.mData[i] = mData[i] - s;
	}
	return result;
}

Matrix3 Matrix3::operator*(const F32& s) const
{
	Matrix3 result;
	for (U8 i = 0; i < 3; i++)
	{
		result.mData[i] = mData[i] * s;
	}
	return result;
}

Matrix3 Matrix3::operator/(const F32& s) const
{
	return (*this) * (1.f / s);
}

Matrix3 Matrix3::operator*(const Matrix3& m) const
{
	Matrix3 out;
	{
		Vector3 row(getRow(0));
		out[0] = Vector3::dotProduct(m.getColumn(0), row);
		out[3] = Vector3::dotProduct(m.getColumn(1), row);
		out[6] = Vector3::dotProduct(m.getColumn(2), row);
	}
	{
		Vector3 row(getRow(1));
		out[1] = Vector3::dotProduct(m.getColumn(0), row);
		out[4] = Vector3::dotProduct(m.getColumn(1), row);
		out[7] = Vector3::dotProduct(m.getColumn(2), row);
	}
	{
		Vector3 row(getRow(2));
		out[2] = Vector3::dotProduct(m.getColumn(0), row);
		out[5] = Vector3::dotProduct(m.getColumn(1), row);
		out[8] = Vector3::dotProduct(m.getColumn(2), row);
	}
	return out;
}

Matrix3& Matrix3::operator+=(const Matrix3& m)
{
	for (U8 i = 0; i < 3; i++)
	{
		mData[i] += m.mData[i];
	}
	return *this;
}

Matrix3& Matrix3::operator-=(const Matrix3& m)
{
	for (U8 i = 0; i < 3; i++)
	{
		mData[i] -= m.mData[i];
	}
	return *this;
}

Matrix3& Matrix3::operator+=(const F32& s)
{
	for (U8 i = 0; i < 3; i++)
	{
		mData[i] += s;
	}
	return *this;
}

Matrix3& Matrix3::operator-=(const F32& s)
{
	for (U8 i = 0; i < 3; i++)
	{
		mData[i] -= s;
	}
	return *this;
}

Matrix3& Matrix3::operator*=(const F32& s)
{
	for (U8 i = 0; i < 3; i++)
	{
		mData[i] *= s;
	}
	return *this;
}

Matrix3& Matrix3::operator/=(const F32& s)
{
	return (*this) *= (1.f / s);
}

Matrix3& Matrix3::operator*=(const Matrix3& m)
{
	Matrix3 temp(*this * m);
	return *this = temp;
}

Matrix3 Matrix3::inversed() const
{
	// Find determinant of matrix.
	F32 sub11 = (*this)[4] * (*this)[8] - (*this)[5] * (*this)[7];
	F32 sub12 = -(*this)[1] * (*this)[8] + (*this)[2] * (*this)[7];
	F32 sub13 = (*this)[1] * (*this)[5] - (*this)[2] * (*this)[4];
	F32 determinant = (*this)[0] * sub11 + (*this)[3] * sub12 + (*this)[6] * sub13;
	if (fabs(determinant) < 1e-7f)
	{
		return Matrix3(0.f);
	}
	// Find determinants of 2x2 submatrices for the elements of the inverse.
	Matrix3 ret(sub11, sub12, sub13, (*this)[6] * (*this)[5] - (*this)[3] * (*this)[8], (*this)[0] * (*this)[8] - (*this)[6] * (*this)[2], (*this)[3] * (*this)[2] - (*this)[0] * (*this)[5], (*this)[3] * (*this)[7] - (*this)[6] * (*this)[4], (*this)[6] * (*this)[1] - (*this)[0] * (*this)[7], (*this)[0] * (*this)[4] - (*this)[3] * (*this)[1]);
	ret *= 1.f / determinant;
	return ret;
}

Matrix3 Matrix3::transposed() const
{
	Matrix3 transpose;
	for (U8 i = 0; i < 3; i++)
	{
		for (U8 j = 0; j < 3; j++)
		{
			transpose.getColumn(j)[i] = getColumn(i)[j];
		}
	}
	return transpose;
}

Matrix4 Matrix3::toMatrix4() const
{
	return Matrix4::fromRotationMatrix(*this);
}

Matrix3 Matrix3::outerProduct(const Vector3& v1, const Vector3& v2)
{
	return Matrix3(v1[0] * v2[0], v1[1] * v2[0], v1[2] * v2[0], v1[0] * v2[1], v1[1] * v2[1], v1[2] * v2[1], v1[0] * v2[2], v1[1] * v2[2], v1[2] * v2[2]);
}

Matrix3 Matrix3::hadamardProduct(const Matrix3& m1, const Matrix3& m2)
{
	Matrix3 result;
	for (U8 i = 0; i < 3; i++)
	{
		result.mData[i] = m1.mData[i] * m2.mData[i];
	}
	return result;
}

Matrix3 Matrix3::identity()
{
	return Matrix3(1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f);
}

Matrix3 Matrix3::rotationX(const Vector2& v)
{
	return Matrix3(1.f, 0.f, 0.f, 0.f, v.x(), v.y(), 0.f, -v.y(), v.x());
}

Matrix3 Matrix3::rotationY(const Vector2& v)
{
	return Matrix3(v.x(), 0.f, -v.y(), 0.f, 1.f, 0.f, v.y(), 0.f, v.x());
}

Matrix3 Matrix3::rotationZ(const Vector2& v)
{
	return Matrix3(v.x(), v.y(), 0.f, -v.y(), v.x(), 0.f, 0.f, 0.f, 1.f);
}

Matrix3 Matrix3::rotationX(F32 angle)
{
	return rotationX(Vector2(Math::cos(angle), Math::sin(angle)));
}

Matrix3 Matrix3::rotationY(F32 angle)
{
	return rotationY(Vector2(Math::cos(angle), Math::sin(angle)));
}

Matrix3 Matrix3::rotationZ(F32 angle)
{
	return rotationZ(Vector2(Math::cos(angle), Math::sin(angle)));
}

const U8 Matrix3::rows()
{
	return 3;
}

const U8 Matrix3::columns()
{
	return 3;
}

const U8 Matrix3::elements()
{
	return 9;
}

Vector3 operator*(const Vector3& v, const Matrix3& m)
{
	Vector3 result;
	for (U8 i = 0; i < 3; i++)
	{
		result[i] = Vector3::dotProduct(m.mData[i], v);
	}
	return result;
}

Matrix3 operator*(const F32& s, const Matrix3& m)
{
	return m * s;
}

Vector3 operator*(const Matrix3& m, const Vector3& v)
{
	Vector3 result(0.f);
	U8 offset = 0;
	for (U8 column = 0; column < 3; column++)
	{
		for (U8 row = 0; row < 3; row++)
		{
			result[row] += m[offset + row] * v[column];
		}
		offset += 3;
	}
	return result;
}

} // namespace oe