#include "Matrix4.hpp"
#include "Matrix3.hpp"

namespace oe
{

Matrix4::Matrix4()
	: mData()
{
}

Matrix4::Matrix4(const Matrix4& m)
{
	mData[0] = m.mData[0];
	mData[1] = m.mData[1];
	mData[2] = m.mData[2];
	mData[3] = m.mData[3];
}

Matrix4::Matrix4(F32 s)
{
	mData[0] = Vector4(s);
	mData[1] = Vector4(s);
	mData[2] = Vector4(s);
	mData[3] = Vector4(s);
}

Matrix4::Matrix4(F32 s00, F32 s10, F32 s20, F32 s30, F32 s01, F32 s11, F32 s21, F32 s31, F32 s02, F32 s12, F32 s22, F32 s32, F32 s03, F32 s13, F32 s23, F32 s33)
{
	mData[0] = Vector4(s00, s10, s20, s30);
	mData[1] = Vector4(s01, s11, s21, s31);
	mData[2] = Vector4(s02, s12, s22, s32);
	mData[3] = Vector4(s03, s13, s23, s33);
}

Matrix4::Matrix4(const Vector4& column0, const Vector4& column1, const Vector4& column2, const Vector4& column3)
{
	mData[0] = column0;
	mData[1] = column1;
	mData[2] = column2;
	mData[3] = column3;
}

Matrix4::Matrix4(const F32* const a)
{
	mData[0] = Vector4(&a[0]);
	mData[1] = Vector4(&a[4]);
	mData[2] = Vector4(&a[8]);
	mData[3] = Vector4(&a[16]);
}

Matrix4::Matrix4(const VectorPacked4* vectors)
{
	mData[0] = Vector4(vectors[0]);
	mData[1] = Vector4(vectors[1]);
	mData[2] = Vector4(vectors[2]);
	mData[3] = Vector4(vectors[3]);
}

F32& Matrix4::operator()(const U8 row, const U8 column)
{
	return mData[column][row];
}

const F32& Matrix4::operator()(const U8 row, const U8 column) const
{
	return mData[column][row];
}

F32& Matrix4::operator()(const U8 i)
{
	return operator[](i);
}

const F32& Matrix4::operator()(const U8 i) const
{
	return operator[](i);
}

F32& Matrix4::operator[](const U8 i)
{
	return reinterpret_cast<F32*>(mData)[i];
}

const F32& Matrix4::operator[](const U8 i) const
{
	return const_cast<Matrix4*>(this)->operator[](i);
}

void Matrix4::pack(VectorPacked4* vector) const
{
	getColumn(0).pack(&vector[0]);
	getColumn(1).pack(&vector[1]);
	getColumn(2).pack(&vector[2]);
	getColumn(3).pack(&vector[3]);
}

Vector4& Matrix4::getColumn(const U8 i)
{
	return mData[i];
}

const Vector4& Matrix4::getColumn(const U8 i) const
{
	return mData[i];
}

Vector4 Matrix4::getRow(const U8 i) const
{
	return Vector4(mData[0][i], mData[1][i], mData[2][i], mData[3][i]);
}

Matrix4& Matrix4::operator=(const Matrix4& m)
{
	for (U8 i = 0; i < 4; i++)
	{
		mData[i] = m.mData[i];
	}
	return *this;
}

bool Matrix4::operator==(const Matrix4& m) const
{
	for (U8 i = 0; i < 4; i++)
	{
		if (mData[i] != m.mData[i])
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

Matrix4 Matrix4::operator-() const
{
	Matrix4 result;
	for (U8 i = 0; i < 4; i++)
	{
		result.mData[i] = -mData[i];
	}
	return result;
}

Matrix4 Matrix4::operator+(const Matrix4& m) const
{
	Matrix4 result;
	for (U8 i = 0; i < 4; i++)
	{
		result.mData[i] = mData[i] + m.mData[i];
	}
	return result;
}

Matrix4 Matrix4::operator-(const Matrix4& m) const
{
	Matrix4 result;
	for (U8 i = 0; i < 4; i++)
	{
		result.mData[i] = mData[i] - m.mData[i];
	}
	return result;
}

Matrix4 Matrix4::operator+(const F32& s) const
{
	Matrix4 result;
	for (U8 i = 0; i < 4; i++)
	{
		result.mData[i] = mData[i] + s;
	}
	return result;
}

Matrix4 Matrix4::operator-(const F32& s) const
{
	Matrix4 result;
	for (U8 i = 0; i < 4; i++)
	{
		result.mData[i] = mData[i] - s;
	}
	return result;
}

Matrix4 Matrix4::operator*(const F32& s) const
{
	Matrix4 result;
	for (U8 i = 0; i < 4; i++)
	{
		result.mData[i] = mData[i] * s;
	}
	return result;
}

Matrix4 Matrix4::operator/(const F32& s) const
{
	return (*this) * (1.f / s);
}

Matrix4 Matrix4::operator*(const Matrix4& m) const
{
	Matrix4 out;
	{
		Vector4 row(getRow(0));
		out[0] = Vector4::dotProduct(m.getColumn(0), row);
		out[4] = Vector4::dotProduct(m.getColumn(1), row);
		out[8] = Vector4::dotProduct(m.getColumn(2), row);
		out[12] = Vector4::dotProduct(m.getColumn(3), row);
	}
	{
		Vector4 row(getRow(1));
		out[1] = Vector4::dotProduct(m.getColumn(0), row);
		out[5] = Vector4::dotProduct(m.getColumn(1), row);
		out[9] = Vector4::dotProduct(m.getColumn(2), row);
		out[13] = Vector4::dotProduct(m.getColumn(3), row);
	}
	{
		Vector4 row(getRow(2));
		out[2] = Vector4::dotProduct(m.getColumn(0), row);
		out[6] = Vector4::dotProduct(m.getColumn(1), row);
		out[10] = Vector4::dotProduct(m.getColumn(2), row);
		out[14] = Vector4::dotProduct(m.getColumn(3), row);
	}
	{
		Vector4 row(getRow(3));
		out[3] = Vector4::dotProduct(m.getColumn(0), row);
		out[7] = Vector4::dotProduct(m.getColumn(1), row);
		out[11] = Vector4::dotProduct(m.getColumn(2), row);
		out[15] = Vector4::dotProduct(m.getColumn(3), row);
	}
	return out;
}

Matrix4& Matrix4::operator+=(const Matrix4& m)
{
	for (U8 i = 0; i < 4; i++)
	{
		mData[i] += m.mData[i];
	}
	return *this;
}

Matrix4& Matrix4::operator-=(const Matrix4& m)
{
	for (U8 i = 0; i < 4; i++)
	{
		mData[i] -= m.mData[i];
	}
	return *this;
}

Matrix4& Matrix4::operator+=(const F32& s)
{
	for (U8 i = 0; i < 4; i++)
	{
		mData[i] += s;
	}
	return *this;
}

Matrix4& Matrix4::operator-=(const F32& s)
{
	for (U8 i = 0; i < 4; i++)
	{
		mData[i] -= s;
	}
	return *this;
}

Matrix4& Matrix4::operator*=(const F32& s)
{
	for (U8 i = 0; i < 4; i++)
	{
		mData[i] *= s;
	}
	return *this;
}

Matrix4& Matrix4::operator/=(const F32& s)
{
	return (*this) *= (1.f / s);
}

Matrix4& Matrix4::operator*=(const Matrix4& m)
{
	Matrix4 temp(*this * m);
	return *this = temp;
}

Matrix4 Matrix4::inversed() const
{
	// This will find the pivot element.
	U8 pivot_elem;
	Vector4 fabs_column(getColumn(0));
	if (fabs_column[0] > fabs_column[1])
	{
		if (fabs_column[0] > fabs_column[2])
		{
			if (fabs_column[0] > fabs_column[3])
			{
				pivot_elem = 0;
			}
			else
			{
				pivot_elem = 3;
			}
		}
		else if (fabs_column[2] > fabs_column[3])
		{
			pivot_elem = 2;
		}
		else
		{
			pivot_elem = 3;
		}
	}
	else if (fabs_column[1] > fabs_column[2])
	{
		if (fabs_column[1] > fabs_column[3])
		{
			pivot_elem = 1;
		}
		else
		{
			pivot_elem = 3;
		}
	}
	else if (fabs_column[2] > fabs_column[3])
	{
		pivot_elem = 2;
	}
	else
	{
		pivot_elem = 3;
	}
	// This will perform the pivot and find the row, column, and 3x3 submatrix for this pivot.
	Vector3 row;
	Vector3 column;
	Matrix3 matrix;
	if (pivot_elem == 0)
	{
		row = Vector3((*this)[4], (*this)[8], (*this)[12]);
		column = Vector3((*this)[1], (*this)[2], (*this)[3]);
		matrix = Matrix3((*this)[5], (*this)[6], (*this)[7], (*this)[9], (*this)[10], (*this)[11], (*this)[13], (*this)[14], (*this)[15]);
	}
	else if (pivot_elem == 1)
	{
		row = Vector3((*this)[5], (*this)[9], (*this)[13]);
		column = Vector3((*this)[0], (*this)[2], (*this)[3]);
		matrix = Matrix3((*this)[4], (*this)[6], (*this)[7], (*this)[8], (*this)[10], (*this)[11], (*this)[12], (*this)[14], (*this)[15]);
	}
	else if (pivot_elem == 2)
	{
		row = Vector3((*this)[6], (*this)[10], (*this)[14]);
		column = Vector3((*this)[0], (*this)[1], (*this)[3]);
		matrix = Matrix3((*this)[4], (*this)[5], (*this)[7], (*this)[8], (*this)[9], (*this)[11], (*this)[12], (*this)[13], (*this)[15]);
	}
	else
	{
		row = Vector3((*this)[7], (*this)[11], (*this)[15]);
		column = Vector3((*this)[0], (*this)[1], (*this)[2]);
		matrix = Matrix3((*this)[4], (*this)[5], (*this)[6], (*this)[8], (*this)[9], (*this)[10], (*this)[12], (*this)[13], (*this)[14]);
	}
	F32 pivot_value = (*this)[pivot_elem];
	if (fabs(pivot_value) < (1e-7f))
	{
		return Matrix4(0.f);
	}
	// This will compute the inverse using the row, column, and 3x3 submatrix.
	F32 inv = -1.f / pivot_value;
	row *= inv;
	matrix += Matrix3::outerProduct(column, row);
	Matrix3 mat_inverse(matrix.inversed());
	Matrix3 error3(0.f);
	// TODO : Invert 3x3
	if (mat_inverse == error3)
	{
		return Matrix4(0.f);
	}
	Vector3 col_inverse = mat_inverse * (column * inv);
	Vector3 row_inverse = row * mat_inverse;
	F32 pivot_inverse = Vector3::dotProduct(row, col_inverse) - inv;
	if (pivot_elem == 0)
	{
		return Matrix4(pivot_inverse, col_inverse[0], col_inverse[1], col_inverse[2], row_inverse[0], mat_inverse[0], mat_inverse[1], mat_inverse[2], row_inverse[1], mat_inverse[3], mat_inverse[4], mat_inverse[5], row_inverse[2], mat_inverse[6], mat_inverse[7], mat_inverse[8]);
	}
	else if (pivot_elem == 1)
	{
		return Matrix4(row_inverse[0], mat_inverse[0], mat_inverse[1], mat_inverse[2], pivot_inverse, col_inverse[0], col_inverse[1], col_inverse[2], row_inverse[1], mat_inverse[3], mat_inverse[4], mat_inverse[5], row_inverse[2], mat_inverse[6], mat_inverse[7], mat_inverse[8]);
	}
	else if (pivot_elem == 2)
	{
		return Matrix4(row_inverse[0], mat_inverse[0], mat_inverse[1], mat_inverse[2], row_inverse[1], mat_inverse[3], mat_inverse[4], mat_inverse[5], pivot_inverse, col_inverse[0], col_inverse[1], col_inverse[2], row_inverse[2], mat_inverse[6], mat_inverse[7], mat_inverse[8]);
	}
	else
	{
		return Matrix4(row_inverse[0], mat_inverse[0], mat_inverse[1], mat_inverse[2], row_inverse[1], mat_inverse[3], mat_inverse[4], mat_inverse[5], row_inverse[2], mat_inverse[6], mat_inverse[7], mat_inverse[8], pivot_inverse, col_inverse[0], col_inverse[1], col_inverse[2]);
	}
	return Matrix4(0.f);
}

Matrix4 Matrix4::transposed() const
{
	Matrix4 transpose;
	for (U8 i = 0; i < 4; i++)
	{
		for (U8 j = 0; j < 4; j++)
		{
			transpose.getColumn(j)[i] = getColumn(i)[j];
		}
	}
	return transpose;
}

Vector2 Matrix4::translationVector2D() const
{
	return mData[3].toVector2();
}

Vector3 Matrix4::translationVector3D() const
{
	return mData[3].toVector3();
}

Vector4 Matrix4::translationVector4D() const
{
	return Vector4(mData[3]);
}

Matrix4 Matrix4::outerProduct(const Vector4& v1, const Vector4& v2)
{
	return Matrix4(v1[0] * v2[0], v1[1] * v2[0], v1[2] * v2[0], v1[3] * v2[0], v1[0] * v2[1], v1[1] * v2[1], v1[2] * v2[1], v1[3] * v2[1], v1[0] * v2[2], v1[1] * v2[2], v1[2] * v2[2], v1[3] * v2[2], v1[0] * v2[3], v1[1] * v2[3], v1[2] * v2[3], v1[3] * v2[3]);
}

Matrix4 Matrix4::hadamardProduct(const Matrix4& m1, const Matrix4& m2)
{
	Matrix4 result;
	for (U8 i = 0; i < 4; i++)
	{
		result.mData[i] = m1.mData[i] * m2.mData[i];
	}
	return result;
}

Matrix4 Matrix4::identity()
{
	return Matrix4(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f);
}

Matrix4 Matrix4::fromTranslationVector(const Vector2& v)
{
	return Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, v[0], v[1], 0, 1);
}

Matrix4 Matrix4::fromTranslationVector(const Vector3& v)
{
	return Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, v[0], v[1], v[2], 1);
}

Matrix4 Matrix4::fromTranslationVector(const Vector4& v)
{
	return Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, v[0], v[1], v[2], v[3]);
}

Matrix4 Matrix4::fromScaleVector(const Vector3& v)
{
	Matrix4 return_matrix(identity());
	for (U8 i = 0; i < 3; i++)
	{
		return_matrix(i, i) = v[i];
	}
	return return_matrix;
}

Matrix4 Matrix4::fromRotationMatrix(const Matrix3& m)
{
	return Matrix4(m[0], m[1], m[2], 0, m[3], m[4], m[5], 0, m[6], m[7], m[8], 0.f, 0.f, 0.f, 0.f, 1.f);
}

/*
Matrix4 Matrix4::fromAffineTransform(const MatrixAffine& affine)
{
	return Matrix4(affine[0], affine[4], affine[8], 0.f, affine[1], affine[5], affine[9], 0.f, affine[2], affine[6], affine[10], 0.f, affine[3], affine[7], affine[11], 1.f);
}

MatrixAffine Matrix4::toAffineTransform(const Matrix4& m)
{
	return MatrixAffine(m[0], m[4], m[8], m[12], m[1], m[5], m[9], m[13], m[2], m[6], m[10], m[14]);
}
*/

Matrix4 Matrix4::rotationX(const Vector2& v)
{
	return fromRotationMatrix(Matrix3(1.f, 0.f, 0.f, 0.f, v.x(), v.y(), 0.f, -v.y(), v.x()));
}

Matrix4 Matrix4::rotationY(const Vector2& v)
{
	return fromRotationMatrix(Matrix3(v.x(), 0.f, -v.y(), 0.f, 1.f, 0.f, v.y(), 0.f, v.x()));
}

Matrix4 Matrix4::rotationZ(const Vector2& v)
{
	return fromRotationMatrix(Matrix3(v.x(), v.y(), 0.f, -v.y(), v.x(), 0.f, 0.f, 0.f, 1.f));
}

Matrix4 Matrix4::rotationX(F32 angle)
{
	return rotationX(Vector2(Math::cos(angle), Math::sin(angle)));
}

Matrix4 Matrix4::rotationY(F32 angle)
{
	return rotationY(Vector2(Math::cos(angle), Math::sin(angle)));
}

Matrix4 Matrix4::rotationZ(F32 angle)
{
	return rotationZ(Vector2(Math::cos(angle), Math::sin(angle)));
}

Matrix4 Matrix4::perspective(F32 fovy, F32 aspect, F32 znear, F32 zfar, F32 handedness)
{
	const F32 y = 1.f / Math::tan(fovy * 0.5f);
	const F32 x = y / aspect;
	const F32 zdist = (znear - zfar);
	const F32 zfar_per_zdist = zfar / zdist;
	return Matrix4(x, 0.f, 0.f, 0.f, 0.f, y, 0.f, 0.f, 0.f, 0.f, zfar_per_zdist * handedness, -1.f * handedness, 0.f, 0.f, 2.f * znear * zfar_per_zdist, 0.f);
}

Matrix4 Matrix4::ortho(F32 left, F32 right, F32 bottom, F32 top, F32 znear, F32 zfar, F32 handedness)
{
	return Matrix4(2.f / (right - left), 0.f, 0.f, 0.f, 0.f, 2.f / (top - bottom), 0.f, 0.f, 0.f, 0.f, -handedness * 2.f / (zfar - znear), 0.f, -(right + left) / (right - left), -(top + bottom) / (top - bottom), -(zfar + znear) / (zfar - znear), 1.f);
}

Matrix4 Matrix4::lookAt(const Vector3& at, const Vector3& eye, const Vector3& up, F32 handedness)
{
	Vector3 axes[4];
	axes[2] = (at - eye).normalized();
	axes[0] = Vector3::crossProduct(up, axes[2]).normalized();
	axes[1] = Vector3::crossProduct(axes[2], axes[0]);
	axes[3] = Vector3(handedness * Vector3::dotProduct(axes[0], eye), -Vector3::dotProduct(axes[1], eye), handedness * Vector3::dotProduct(axes[2], eye));
	// Default calculation is left-handed (i.e. handedness=-1).
	// Negate x and z axes for right-handed (i.e. handedness=+1) case.
	const F32 neg = -handedness;
	axes[0] *= neg;
	axes[2] *= neg;
	const Vector4 column0(axes[0][0], axes[1][0], axes[2][0], 0.f);
	const Vector4 column1(axes[0][1], axes[1][1], axes[2][1], 0.f);
	const Vector4 column2(axes[0][2], axes[1][2], axes[2][2], 0.f);
	const Vector4 column3(axes[3], 1.f);
	return Matrix4(column0, column1, column2, column3);
}

Vector3 Matrix4::unProject(const Vector3& window_coord, const Matrix4& model_view, const Matrix4& projection, const F32 window_width, const F32 window_height)
{
	Vector3 result;
	if (window_coord.z() < 0.f || window_coord.z() > 1.f)
	{
		// window_coord.z should be with in [0, 1]
		// 0: near plane
		// 1: far plane
		return result;
	}
	Matrix4 matrix = (projection * model_view).inversed();
	Vector4 standardized = Vector4(2.f * (window_coord.x() - window_width) / window_width + 1.f, 2.f * (window_coord.y() - window_height) / window_height + 1.f, 2.f * window_coord.z() - 1.f, 1.f);
	Vector4 multiply = matrix * standardized;
	if (Math::equals(multiply.w(), 0.f))
	{
		return result;
	}
	result = multiply.xyz() / multiply.w();
	return result;
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

Vector4 operator*(const Vector4& v, const Matrix4& m)
{
	Vector4 result;
	for (U8 i = 0; i < 4; i++)
	{
		result[i] = Vector4::dotProduct(m.mData[i], v);
	}
	return result;
}

Matrix4 operator*(const F32& s, const Matrix4& m)
{
	return m * s;
}

Vector4 operator*(const Matrix4& m, const Vector4& v)
{
	Vector4 result(0.f);
	U8 offset = 0;
	for (U8 column = 0; column < 4; column++)
	{
		for (U8 row = 0; row < 4; row++)
		{
			result[row] += m[offset + row] * v[column];
		}
		offset += 4;
	}
	return result;
}

Vector3 operator*(const Matrix4& m, const Vector3& v)
{
	Vector4 v4(m * v.toVector4());
	return Vector3(v4[0] / v4[3], v4[1] / v4[3], v4[2] / v4[3]);
}

Vector2 operator*(const Matrix4& m, const Vector2& v)
{
	Vector4 v4(m * v.toVector4());
	return Vector2(v4[0] / v4[3], v4[1] / v4[3]);
}

} // namespace oe