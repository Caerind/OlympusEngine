#ifndef OE_MATRIX_HPP
#define OE_MATRIX_HPP

#include "Vector.hpp"

namespace oe 
{

template <class T, U8 rows, U8 columns = rows>
class Matrix;

template <class T, U8 rows, U8 columns>
inline Matrix<T, rows, columns> identityHelper();

template <bool check_invertible, class T, U8 rows, U8 columns>
inline bool inverseHelper(const Matrix<T, rows, columns>& m, Matrix<T, rows, columns>* const inverse);

template <class T, U8 rows, U8 columns>
inline void timesHelper(const Matrix<T, rows, columns>& m1, const Matrix<T, rows, columns>& m2, Matrix<T, rows, columns>* out_m);

template <class T, U8 rows, U8 columns>
static inline Matrix<T, rows, columns> outerProductHelper(const Vector<T, rows>& v1, const Vector<T, columns>& v2);

template <class T>
inline Matrix<T, 4, 4> perspectiveHelper(T fovy, T aspect, T znear, T zfar, T handedness);

template <class T>
static inline Matrix<T, 4, 4> orthoHelper(T left, T right, T bottom, T top, T znear, T zfar, T handedness);

template <class T>
static inline Matrix<T, 4, 4> lookAtHelper(const Vector<T, 3>& at, const Vector<T, 3>& eye, const Vector<T, 3>& up, T handedness);

template <class T>
static inline bool unProjectHelper(const Vector<T, 3>& window_coord, const Matrix<T, 4, 4>& model_view, const Matrix<T, 4, 4>& projection, const F32 window_width, const F32 window_height, Vector<T, 3>& result);

template <class T, U8 rows, U8 columns>
class OE_API Matrix 
{
	public:
		inline Matrix()
			: mData()
		{
		}

		inline Matrix(const Matrix<T, rows, columns>& m)
		{
			for (U8 i = 0; i < columns; i++) 
			{
				mData[i] = m.mData[i];
			}
		}

		explicit inline Matrix(const T& s) 
		{
			for (U8 i = 0; i < columns; i++) 
			{
				mData[i] = Vector<T, rows>(s);
			}
		}

		inline Matrix(const T& s00, const T& s10, const T& s01, const T& s11) 
		{
			ASSERT(rows == 2 && columns == 2);
			mData[0] = Vector<T, rows>(s00, s10);
			mData[1] = Vector<T, rows>(s01, s11);
		}

		inline Matrix(const T& s00, const T& s10, const T& s20, const T& s01, const T& s11, const T& s21, const T& s02, const T& s12, const T& s22) 
		{
			ASSERT(rows == 3 && columns == 3);
			mData[0] = Vector<T, rows>(s00, s10, s20);
			mData[1] = Vector<T, rows>(s01, s11, s21);
			mData[2] = Vector<T, rows>(s02, s12, s22);
		}

		inline Matrix(const T& s00, const T& s10, const T& s20, const T& s30, const T& s01, const T& s11, const T& s21, const T& s31, const T& s02, const T& s12, const T& s22, const T& s32) 
		{
			ASSERT(rows == 4 && columns == 3);
			mData[0] = Vector<T, rows>(s00, s10, s20, s30);
			mData[1] = Vector<T, rows>(s01, s11, s21, s31);
			mData[2] = Vector<T, rows>(s02, s12, s22, s32);
		}

		inline Matrix(const T& s00, const T& s10, const T& s20, const T& s30, const T& s01, const T& s11, const T& s21, const T& s31, const T& s02, const T& s12, const T& s22, const T& s32, const T& s03, const T& s13, const T& s23, const T& s33) 
		{
			ASSERT(rows == 4 && columns == 4);
			mData[0] = Vector<T, rows>(s00, s10, s20, s30);
			mData[1] = Vector<T, rows>(s01, s11, s21, s31);
			mData[2] = Vector<T, rows>(s02, s12, s22, s32);
			mData[3] = Vector<T, rows>(s03, s13, s23, s33);
		}

		inline Matrix(const Vector<T, 4>& column0, const Vector<T, 4>& column1, const Vector<T, 4>& column2, const Vector<T, 4>& column3) 
		{
			ASSERT(rows == 4 && columns == 4);
			mData[0] = column0;
			mData[1] = column1;
			mData[2] = column2;
			mData[3] = column3;
		}

		explicit inline Matrix(const T* const a) 
		{
			for (U8 i = 0; i < columns; i++) 
			{
				mData[i] = Vector<T, rows>(&a[i * columns]);
			}
		}

		explicit inline Matrix(const VectorPacked<T, rows>* const vectors) 
		{
			for (U8 i = 0; i < columns; i++) 
			{
				mData[i] = Vector<T, rows>(vectors[i]);
			}
		}

		inline const T& operator()(const U8 row, const U8 column) const 
		{
			return mData[column][row];
		}

		inline T& operator()(const U8 row, const U8 column) 
		{
			return mData[column][row];
		}

		inline const T& operator()(const U8 i) const
		{ 
			return operator[](i); 
		}

		inline T& operator()(const U8 i) 
		{
			return operator[](i); 
		}

		inline const T& operator[](const U8 i) const 
		{
			return const_cast<Matrix<T, rows, columns>*>(this)->operator[](i);
		}

		inline T& operator[](const U8 i) 
		{
			return reinterpret_cast<T*>(mData)[i];
		}

		inline void pack(VectorPacked<T, rows>* const vector) const 
		{
			for (U8 i = 0; i < columns; i++) 
			{
				getColumn(i).pack(&vector[i]);
			}
		}

		inline Vector<T, rows>& getColumn(const U8 i)
		{ 
			return mData[i]; 
		}

		inline const Vector<T, rows>& getColumn(const U8 i) const 
		{
			return mData[i];
		}

		inline Matrix<T, rows, columns> operator-() const 
		{
			Matrix<T, rows, columns> result;
			for (U8 i = 0; i < columns; i++)
			{
				result.mData[i] = -mData[i];
			}
			return result;   
		}

		inline Matrix<T, rows, columns> operator+(const Matrix<T, rows, columns>& m) const 
		{
			Matrix<T, rows, columns> result;
			for (U8 i = 0; i < columns; i++)
			{
				result.mData[i] = mData[i] + m.mData[i];
			}
			return result; 
		}

		inline Matrix<T, rows, columns> operator-(const Matrix<T, rows, columns>& m) const 
		{
			Matrix<T, rows, columns> result;
			for (U8 i = 0; i < columns; i++)
			{
				result.mData[i] = mData[i] - m.mData[i];
			}
			return result;
		}

		inline Matrix<T, rows, columns> operator+(const T& s) const 
		{
			Matrix<T, rows, columns> result;
			for (U8 i = 0; i < columns; i++)
			{
				result.mData[i] = mData[i] + s;
			}
			return result;
		}

		inline Matrix<T, rows, columns> operator-(const T& s) const 
		{
			Matrix<T, rows, columns> result;
			for (U8 i = 0; i < columns; i++)
			{
				result.mData[i] = mData[i] - s;
			}
			return result;
		}

		inline Matrix<T, rows, columns> operator*(const T& s) const 
		{
			Matrix<T, rows, columns> result;
			for (U8 i = 0; i < columns; i++)
			{
				result.mData[i] = mData[i] * s;
			}
			return result;
		}

		inline Matrix<T, rows, columns> operator/(const T& s) const 
		{
			return (*this) * (1 / s);
		}

		inline Matrix<T, rows, columns> operator*(const Matrix<T, rows, columns>& m) const 
		{
			Matrix<T, rows, columns> result;
			timesHelper(*this, m, &result);
			return result;
		}

		inline Matrix<T, rows, columns>& operator+=(const Matrix<T, rows, columns>& m) 
		{
			for (U8 i = 0; i < columns; i++)
			{
				mData[i] += m.mData[i];
			}
			return *this;
		}

		inline Matrix<T, rows, columns>& operator-=(const Matrix<T, rows, columns>& m) 
		{
			for (U8 i = 0; i < columns; i++)
			{
				mData[i] -= m.mData[i];
			}
			return *this;
		}

		inline Matrix<T, rows, columns>& operator+=(const T& s) 
		{
			for (U8 i = 0; i < columns; i++)
			{
				mData[i] += s;
			}
			return *this;
		}

		inline Matrix<T, rows, columns>& operator-=(const T& s) 
		{
			for (U8 i = 0; i < columns; i++)
			{
				mData[i] -= s;
			}
			return *this;
		}

		inline Matrix<T, rows, columns>& operator*=(const T& s) 
		{
			for (U8 i = 0; i < columns; i++)
			{
				mData[i] *= s;
			}
			return *this;
		}

		inline Matrix<T, rows, columns>& operator/=(const T& s) 
		{
			return (*this) *= (1 / s);
		}

		inline Matrix<T, rows, columns>& operator*=(const Matrix<T, rows, columns>& m) 
		{
			const Matrix<T, rows, columns> copy_of_this(*this);
			timesHelper(copy_of_this, m, this);
			return *this;
		}

		inline Matrix<T, rows, columns> inverse() const 
		{
			Matrix<T, rows, columns> inverse;
			inverseHelper<false>(*this, &inverse);
			return inverse;
		}

		inline bool inverseWithDeterminantCheck(Matrix<T, rows, columns>* const inverse) const 
		{
			return inverseHelper<true>(*this, inverse);
		}

		inline Matrix<T, columns, rows> transpose() const 
		{
			Matrix<T, columns, rows> transpose;
			for (U8 i = 0; i < columns; i++)
			{
				for (U8 j = 0; j < rows; j++)
				{
					transpose.getColumn(j)[i] = getColumn(i)[j];
				}
			}
			return transpose;
		}

		inline Vector<T, 2> translationVector2D() const 
		{
			ASSERT(rows == 3 && columns == 3);
			return Vector<T, 2>(mData[2][0], mData[2][1]);
		}

		inline Vector<T, 3> translationVector3D() const 
		{
			ASSERT(rows == 4 && columns == 4);
			return Vector<T, 3>(mData[3][0], mData[3][1], mData[3][2]);
		}

		static inline Matrix<T, rows, columns> outerProduct(const Vector<T, rows>& v1, const Vector<T, columns>& v2) 
		{
			return outerProductHelper(v1, v2);
		}

		static inline Matrix<T, rows, columns> hadamardProduct(const Matrix<T, rows, columns>& m1, const Matrix<T, rows, columns>& m2) 
		{
			Matrix<T, rows, columns> result;
			for (U8 i = 0; i < columns; i++)
			{
				result.mData[i] = m1[i] * m2[i];
			}
			return result;
		}

		static inline Matrix<T, rows, columns> identity() 
		{
			return identityHelper<T, rows, columns>();
		}

		static inline Matrix<T, 3> fromTranslationVector(const Vector<T, 2>& v) 
		{
			return Matrix<T, 3>(1, 0, 0, 0, 1, 0, v[0], v[1], 1);
		}

		static inline Matrix<T, 4> fromTranslationVector(const Vector<T, 3>& v) 
		{
			return Matrix<T, 4>(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, v[0], v[1], v[2], 1);
		}

		static inline Matrix<T, rows> fromScaleVector(const Vector<T, rows - 1>& v) 
		{
			// TODO OPT: Use a helper function in a similar way to Identity to
			// construct the matrix for the specialized cases 2, 3, 4, and only run
			// this method in the general case. This will also allow you to use the
			// helper methods from specialized classes like Matrix<T, 4, 4>.
			Matrix<T, rows> return_matrix(identity());
			for (U8 i = 0; i < rows - 1; ++i)
			{
				return_matrix(i, i) = v[i];
			}
			return return_matrix;
		}

		static inline Matrix<T, 4> fromRotationMatrix(const Matrix<T, 3>& m) 
		{
			return Matrix<T, 4>(m[0], m[1], m[2], 0, m[3], m[4], m[5], 0, m[6], m[7], m[8], 0, 0, 0, 0, 1);
		}

		static inline Matrix<T, 4> fromAffineTransform(const Matrix<T, 4, 3>& affine) 
		{
			return Matrix<T, 4>(affine[0], affine[4], affine[8], static_cast<T>(0), affine[1], affine[5], affine[9], static_cast<T>(0), affine[2], affine[6], affine[10], static_cast<T>(0), affine[3], affine[7], affine[11], static_cast<T>(1));
		}

		static inline Matrix<T, 4, 3> toAffineTransform(const Matrix<T, 4>& m) 
		{
			return Matrix<T, 4, 3>(m[0], m[4], m[8], m[12], m[1], m[5], m[9], m[13], m[2], m[6], m[10], m[14]);
		}

		static inline Matrix<T, 3> rotationX(const Vector<T, 2>& v) 
		{
			return Matrix<T, 3>(1, 0, 0, 0, v.x(), v.y(), 0, -v.y(), v.x());
		}

		static inline Matrix<T, 3> rotationY(const Vector<T, 2>& v) 
		{
			return Matrix<T, 3>(v.x(), 0, -v.y(), 0, 1, 0, v.y(), 0, v.x());
		}

		static inline Matrix<T, 3> rotationZ(const Vector<T, 2>& v) 
		{
			return Matrix<T, 3>(v.x(), v.y(), 0, -v.y(), v.x(), 0, 0, 0, 1);
		}

		static inline Matrix<T, 3> rotationX(T angle) 
		{
			return rotationX(Vector<T, 2>(cosf(angle), sinf(angle)));
		}

		static inline Matrix<T, 3> rotationY(T angle) 
		{
			return rotationY(Vector<T, 2>(cosf(angle), sinf(angle)));
		}

		static inline Matrix<T, 3> rotationZ(T angle) 
		{
			return rotationZ(Vector<T, 2>(cosf(angle), sinf(angle)));
		}

		static inline Matrix<T, 4, 4> perspective(T fovy, T aspect, T znear, T zfar, T handedness = 1) 
		{
			return perspectiveHelper(fovy, aspect, znear, zfar, handedness);
		}

		static inline Matrix<T, 4, 4> ortho(T left, T right, T bottom, T top, T znear, T zfar, T handedness = 1) 
		{
			return orthoHelper(left, right, bottom, top, znear, zfar, handedness);
		}

		static inline Matrix<T, 4, 4> lookAt(const Vector<T, 3>& at, const Vector<T, 3>& eye, const Vector<T, 3>& up, T handedness = -1) 
		{
			return lookAtHelper(at, eye, up, handedness);
		}

		static inline Vector<T, 3> unProject(const Vector<T, 3>& window_coord, const Matrix<T, 4, 4>& model_view, const Matrix<T, 4, 4>& projection, const F32 window_width, const F32 window_height) 
		{
			Vector<T, 3> result;
			unProjectHelper(window_coord, model_view, projection, window_width, window_height, result);
			return result;
		}

		friend inline Vector<T, columns> operator*(const Vector<T, rows>& v, const Matrix<T, rows, columns>& m) 
		{
			const U8 d = columns;
			Vector<T, d> result;
			for (U8 i = 0; i < d; i++)
			{
				result[i] = Vector<T, rows>::dotProduct(m.mData[i], v); 
			}
			return result;
		}

		static const U8 rows = rows;
		static const U8 columns = columns;
		static const U8 elements = rows * columns;

	private:
		Vector<T, rows> mData[columns];
};

template <class T, U8 rows, U8 columns>
inline Matrix<T, rows, columns> operator*(const T& s, const Matrix<T, columns, rows>& m) 
{
	return m * s;
}

template <class T, U8 rows, U8 columns>
inline Vector<T, rows> operator*(const Matrix<T, rows, columns>& m, const Vector<T, columns>& v) 
{
	const Vector<T, rows> result(0);
	U8 offset = 0;
	for (U8 column = 0; column < columns; column++) 
	{
		for (U8 row = 0; row < rows; row++) 
		{
			result[row] += m[offset + row] * v[column];
		}
		offset += rows;
	}
	return result;
}

template <class T>
inline Vector<T, 2> operator*(const Matrix<T, 2, 2>& m, const Vector<T, 2>& v) 
{
	return Vector<T, 2>(m[0] * v[0] + m[2] * v[1], m[1] * v[0] + m[3] * v[1]);
}

template <class T>
inline Vector<T, 3> operator*(const Matrix<T, 3, 3>& m, const Vector<T, 3>& v) 
{
	const F32 d1 = &m[0][0] * v[0] + &m[0][3] * v[1] + &m[0][6] * v[2];
	const F32 d2 = &m[0][1] * v[0] + &m[0][4] * v[1] + &m[0][7] * v[2];
	const F32 d3 = &m[0][2] * v[0] + &m[0][5] * v[1] + &m[0][8] * v[2];
	return Vector<F32, 3>(d1, d2, d3);
}

template <class T>
inline Vector<T, 4> operator*(const Matrix<T, 4, 4>& m, const Vector<T, 4>& v) 
{
	const F32 d1 = &m[0][0] * v[0] + &m[0][4] * v[1] + &m[0][8] * v[2] + &m[0][12] * v[3];
	const F32 d2 = &m[0][1] * v[0] + &m[0][5] * v[1] + &m[0][9] * v[2] + &m[0][13] * v[3];
	const F32 d3 = &m[0][2] * v[0] + &m[0][6] * v[1] + &m[0][10] * v[2] + &m[0][14] * v[3];
	const F32 d4 = &m[0][3] * v[0] + &m[0][7] * v[1] + &m[0][11] * v[2] + &m[0][15] * v[3];
	return Vector<T, 4>(d1, d2, d3, d4);
}

template <class T>
inline Vector<T, 3> operator*(const Matrix<T, 4, 4>& m, const Vector<T, 3>& v) 
{
	Vector<T, 4> v4(v[0], v[1], v[2], 1);
	v4 = m * v4;
	return Vector<T, 3>(v4[0] / v4[3], v4[1] / v4[3], v4[2] / v4[3]);
}

template <class T, U8 size1, U8 size2, U8 size3>
inline void timesHelper(const Matrix<T, size1, size2>& m1, const Matrix<T, size2, size3>& m2, Matrix<T, size1, size3>* out_m) 
{
	for (U8 i = 0; i < size1; i++) 
	{
		for (U8 j = 0; j < size3; j++) 
		{
			Vector<T, size2> row;
			for (U8 k = 0; k < size2; k++) 
			{
				row[k] = m1(i, k);
			}
			(*out_m)(i, j) = Vector<T, size2>::DotProduct(m2.GetColumn(j), row);
		}
	}
}

template <class T>
inline void timesHelper(const Matrix<T, 2, 2>& m1, const Matrix<T, 2, 2>& m2, Matrix<T, 2, 2>* out_m) 
{
	Matrix<T, 2, 2>& out = *out_m;
	out[0] = m1[0] * m2[0] + m1[2] * m2[1];
	out[1] = m1[1] * m2[0] + m1[3] * m2[1];
	out[2] = m1[0] * m2[2] + m1[2] * m2[3];
	out[3] = m1[1] * m2[2] + m1[3] * m2[3];
}

template <typename T>
inline void timesHelper(const Matrix<T, 3, 3>& m1, const Matrix<T, 3, 3>& m2, Matrix<T, 3, 3>* out_m)
{
	Matrix<T, 3, 3>& out = *out_m;
	{
		Vector<T, 3> row(m1[0], m1[3], m1[6]);
		out[0] = Vector<T, 3>::dotProduct(m2.getColumn(0), row);
		out[3] = Vector<T, 3>::dotProduct(m2.getColumn(1), row);
		out[6] = Vector<T, 3>::dotProduct(m2.getColumn(2), row);
	}
	{
		Vector<T, 3> row(m1[1], m1[4], m1[7]);
		out[1] = Vector<T, 3>::dotProduct(m2.getColumn(0), row);
		out[4] = Vector<T, 3>::dotProduct(m2.getColumn(1), row);
		out[7] = Vector<T, 3>::dotProduct(m2.getColumn(2), row);
	}
	{
		Vector<T, 3> row(m1[2], m1[5], m1[8]);
		out[2] = Vector<T, 3>::dotProduct(m2.getColumn(0), row);
		out[5] = Vector<T, 3>::dotProduct(m2.getColumn(1), row);
		out[8] = Vector<T, 3>::dotProduct(m2.getColumn(2), row);
	}
}

template <class T>
inline void timesHelper(const Matrix<T, 4, 4>& m1, const Matrix<T, 4, 4>& m2, Matrix<T, 4, 4>* out_m)
{
	Matrix<T, 4, 4>& out = *out_m;
	{
		Vector<T, 4> row(m1[0], m1[4], m1[8], m1[12]);
		out[0] = Vector<T, 4>::dotProduct(m2.getColumn(0), row);
		out[4] = Vector<T, 4>::dotProduct(m2.getColumn(1), row);
		out[8] = Vector<T, 4>::dotProduct(m2.getColumn(2), row);
		out[12] = Vector<T, 4>::dotProduct(m2.getColumn(3), row);
	}
	{
		Vector<T, 4> row(m1[1], m1[5], m1[9], m1[13]);
		out[1] = Vector<T, 4>::dotProduct(m2.getColumn(0), row);
		out[5] = Vector<T, 4>::dotProduct(m2.getColumn(1), row);
		out[9] = Vector<T, 4>::dotProduct(m2.getColumn(2), row);
		out[13] = Vector<T, 4>::dotProduct(m2.getColumn(3), row);
	}
	{
		Vector<T, 4> row(m1[2], m1[6], m1[10], m1[14]);
		out[2] = Vector<T, 4>::dotProduct(m2.getColumn(0), row);
		out[6] = Vector<T, 4>::dotProduct(m2.getColumn(1), row);
		out[10] = Vector<T, 4>::dotProduct(m2.getColumn(2), row);
		out[14] = Vector<T, 4>::dotProduct(m2.getColumn(3), row);
	}
	{
		Vector<T, 4> row(m1[3], m1[7], m1[11], m1[15]);
		out[3] = Vector<T, 4>::dotProduct(m2.getColumn(0), row);
		out[7] = Vector<T, 4>::dotProduct(m2.getColumn(1), row);
		out[11] = Vector<T, 4>::dotProduct(m2.getColumn(2), row);
		out[15] = Vector<T, 4>::dotProduct(m2.getColumn(3), row);
	}
}

template <class T, U8 rows, U8 columns>
inline Matrix<T, rows, columns> identityHelper() 
{
	Matrix<T, rows, columns> return_matrix(0.f);
	U8 min_d = rows < columns ? rows : columns;
	for (U8 i = 0; i < min_d; ++i) 
	{
		return_matrix(i, i) = 1;
	}
	return return_matrix;
}

template <class T>
inline Matrix<T, 2, 2> identityHelper() 
{
	return Matrix<T, 2, 2>(1, 0, 0, 1);
}

template <class T>
inline Matrix<T, 3, 3> identityHelper() 
{
	return Matrix<T, 3, 3>(1, 0, 0, 0, 1, 0, 0, 0, 1);
}

template <class T>
inline Matrix<T, 4, 4> identityHelper() 
{
	return Matrix<T, 4, 4>(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

template <class T, U8 rows, U8 columns>
static inline Matrix<T, rows, columns> outerProductHelper(const Vector<T, rows>& v1, const Vector<T, columns>& v2) 
{
	Matrix<T, rows, columns> result(0);
	U8 offset = 0;
	for (U8 column = 0; column < columns; column++) 
	{
		for (U8 row = 0; row < rows; row++) 
		{
			result[row + offset] = v1[row] * v2[column];
		}
		offset += rows;
	}
	return result;
}

template <class T>
static inline Matrix<T, 2, 2> outerProductHelper(const Vector<T, 2>& v1, const Vector<T, 2>& v2) 
{
	return Matrix<T, 2, 2>(v1[0] * v2[0], v1[1] * v2[0], v1[0] * v2[1], v1[1] * v2[1]);
}

template <class T>
static inline Matrix<T, 3, 3> outerProductHelper(const Vector<T, 3>& v1, const Vector<T, 3>& v2)
{
	return Matrix<T, 3, 3>(v1[0] * v2[0], v1[1] * v2[0], v1[2] * v2[0], v1[0] * v2[1], v1[1] * v2[1], v1[2] * v2[1], v1[0] * v2[2], v1[1] * v2[2], v1[2] * v2[2]);
}

template <class T>
static inline Matrix<T, 4, 4> outerProductHelper(const Vector<T, 4>& v1, const Vector<T, 4>& v2) 
{
	return Matrix<T, 4, 4>(v1[0] * v2[0], v1[1] * v2[0], v1[2] * v2[0], v1[3] * v2[0], v1[0] * v2[1], v1[1] * v2[1], v1[2] * v2[1], v1[3] * v2[1], v1[0] * v2[2], v1[1] * v2[2], v1[2] * v2[2], v1[3] * v2[2], v1[0] * v2[3], v1[1] * v2[3], v1[2] * v2[3], v1[3] * v2[3]);
}

template <class T>
class Constants 
{
	public:
		static T getDeterminantThreshold() 
		{
			ASSERT(false);
			return 0;
		}
};

template <>
class Constants<F32> 
{
	public:
		static F32 getDeterminantThreshold() 
		{ 
			return (1e-7f); 
		}
};

template <bool check_invertible, class T, U8 rows, U8 columns>
inline bool inverseHelper(const Matrix<T, rows, columns>& m, Matrix<T, rows, columns>* const inverse) 
{
	ASSERT(false);
	(void)m;
	*inverse = T::identity();
	return false;
}

template <bool check_invertible, class T>
inline bool inverseHelper(const Matrix<T, 2, 2>& m, Matrix<T, 2, 2>* const inverse) 
{
	T determinant = m[0] * m[3] - m[1] * m[2];
	if (check_invertible && fabs(determinant) < Constants<T>::getDeterminantThreshold()) 
	{
		return false;
	}
	T inverseDeterminant = 1 / determinant;
	(*inverse)[0] = inverseDeterminant * m[3];
	(*inverse)[1] = -inverseDeterminant * m[1];
	(*inverse)[2] = -inverseDeterminant * m[2];
	(*inverse)[3] = inverseDeterminant * m[0];
	return true;
}

template <bool check_invertible, class T>
inline bool inverseHelper(const Matrix<T, 3, 3>& m, Matrix<T, 3, 3>* const inverse) 
{
	// Find determinant of matrix.
	T sub11 = m[4] * m[8] - m[5] * m[7];
	T sub12 = -m[1] * m[8] + m[2] * m[7];
	T sub13 = m[1] * m[5] - m[2] * m[4];
	T determinant = m[0] * sub11 + m[3] * sub12 + m[6] * sub13;
	if (check_invertible && fabs(determinant) < Constants<T>::getDeterminantThreshold()) 
	{
		return false;
	}
	// Find determinants of 2x2 submatrices for the elements of the inverse.
	*inverse = Matrix<T, 3, 3>(
	sub11, sub12, sub13, m[6] * m[5] - m[3] * m[8], m[0] * m[8] - m[6] * m[2],
	m[3] * m[2] - m[0] * m[5], m[3] * m[7] - m[6] * m[4],
	m[6] * m[1] - m[0] * m[7], m[0] * m[4] - m[3] * m[1]);
	*(inverse) *= 1 / determinant;
	return true;
}

template <class T>
inline U8 findLargestPivotElem(const Matrix<T, 4, 4>& m) 
{
	Vector<T, 4> fabs_column(fabs(m[0]), fabs(m[1]), fabs(m[2]), fabs(m[3]));
	if (fabs_column[0] > fabs_column[1]) 
	{
		if (fabs_column[0] > fabs_column[2]) 
		{
			if (fabs_column[0] > fabs_column[3]) 
			{
				return 0;
			} 
			else 
			{
				return 3;
			}
		} 
		else if (fabs_column[2] > fabs_column[3]) 
		{
			return 2;
		} 
		else 
		{
			return 3;
		}
	} 
	else if (fabs_column[1] > fabs_column[2]) 
	{
		if (fabs_column[1] > fabs_column[3]) 
		{
			return 1;
		}
		else 
		{
		return 3;
		}
	} 
	else if (fabs_column[2] > fabs_column[3]) 
	{
		return 2;
	} 
	else 
	{
		return 3;
	}
}

template <bool check_invertible, class T>
bool inverseHelper(const Matrix<T, 4, 4>& m, Matrix<T, 4, 4>* const inverse) 
{
	// This will find the pivot element.
	U8 pivot_elem = findLargestPivotElem(m);
	// This will perform the pivot and find the row, column, and 3x3 submatrix for this pivot.
	Vector<T, 3> row;
	Vector<T, 3> column;
	Matrix<T, 3> matrix;
	if (pivot_elem == 0) 
	{
		row = Vector<T, 3>(m[4], m[8], m[12]);
		column = Vector<T, 3>(m[1], m[2], m[3]);
		matrix = Matrix<T, 3>(m[5], m[6], m[7], m[9], m[10], m[11], m[13], m[14], m[15]);
	} 
	else if (pivot_elem == 1) 
	{
		row = Vector<T, 3>(m[5], m[9], m[13]);
		column = Vector<T, 3>(m[0], m[2], m[3]);
		matrix = Matrix<T, 3>(m[4], m[6], m[7], m[8], m[10], m[11], m[12], m[14], m[15]);
	} 
	else if (pivot_elem == 2) 
	{
		row = Vector<T, 3>(m[6], m[10], m[14]);
		column = Vector<T, 3>(m[0], m[1], m[3]);
		matrix = Matrix<T, 3>(m[4], m[5], m[7], m[8], m[9], m[11], m[12], m[13], m[15]);
	} 
	else 
	{
		row = Vector<T, 3>(m[7], m[11], m[15]);
		column = Vector<T, 3>(m[0], m[1], m[2]);
		matrix = Matrix<T, 3>(m[4], m[5], m[6], m[8], m[9], m[10], m[12], m[13], m[14]);
	}
	T pivot_value = m[pivot_elem];
	if (check_invertible && fabs(pivot_value) < Constants<T>::getDeterminantThreshold()) 
	{
		return false;
	}
	// This will compute the inverse using the row, column, and 3x3 submatrix.
	T inv = -1 / pivot_value;
	row *= inv;
	matrix += Matrix<T, 3>::outerProduct(column, row);
	Matrix<T, 3> mat_inverse;
	if (!inverseHelper<check_invertible>(matrix, &mat_inverse) && check_invertible) 
	{
		return false;
	}
	Vector<T, 3> col_inverse = mat_inverse * (column * inv);
	Vector<T, 3> row_inverse = row * mat_inverse;
	T pivot_inverse = Vector<T, 3>::dotProduct(row, col_inverse) - inv;
	if (pivot_elem == 0) 
	{
		*inverse = Matrix<T, 4, 4>(pivot_inverse, col_inverse[0], col_inverse[1], col_inverse[2], row_inverse[0], mat_inverse[0], mat_inverse[1], mat_inverse[2], row_inverse[1], mat_inverse[3], mat_inverse[4], mat_inverse[5], row_inverse[2], mat_inverse[6], mat_inverse[7], mat_inverse[8]);
	} 
	else if (pivot_elem == 1) 
	{
		*inverse = Matrix<T, 4, 4>(row_inverse[0], mat_inverse[0], mat_inverse[1], mat_inverse[2], pivot_inverse, col_inverse[0], col_inverse[1], col_inverse[2], row_inverse[1], mat_inverse[3], mat_inverse[4], mat_inverse[5], row_inverse[2], mat_inverse[6], mat_inverse[7], mat_inverse[8]);
	} 
	else if (pivot_elem == 2) 
	{
		*inverse = Matrix<T, 4, 4>(row_inverse[0], mat_inverse[0], mat_inverse[1], mat_inverse[2], row_inverse[1], mat_inverse[3], mat_inverse[4], mat_inverse[5], pivot_inverse, col_inverse[0], col_inverse[1], col_inverse[2], row_inverse[2], mat_inverse[6], mat_inverse[7], mat_inverse[8]);
	} 
	else 
	{
		*inverse = Matrix<T, 4, 4>(row_inverse[0], mat_inverse[0], mat_inverse[1], mat_inverse[2], row_inverse[1], mat_inverse[3], mat_inverse[4], mat_inverse[5], row_inverse[2], mat_inverse[6], mat_inverse[7], mat_inverse[8], pivot_inverse, col_inverse[0], col_inverse[1], col_inverse[2]);
	}
	return true;
}

template <class T>
inline Matrix<T, 4, 4> perspectiveHelper(T fovy, T aspect, T znear, T zfar, T handedness) 
{
	const T y = 1 / tan(static_cast<T>(fovy) * static_cast<T>(.5));
	const T x = y / aspect;
	const T zdist = (znear - zfar);
	const T zfar_per_zdist = zfar / zdist;
	return Matrix<T, 4, 4>(x, 0, 0, 0, 0, y, 0, 0, 0, 0, zfar_per_zdist * handedness, -1 * handedness, 0, 0, 2.0f * znear * zfar_per_zdist, 0);
}

template <class T>
static inline Matrix<T, 4, 4> orthoHelper(T left, T right, T bottom, T top, T znear, T zfar, T handedness) 
{
	return Matrix<T, 4, 4>(static_cast<T>(2) / (right - left), 0, 0, 0, 0, static_cast<T>(2) / (top - bottom), 0, 0, 0, 0, -handedness * static_cast<T>(2) / (zfar - znear), 0, -(right + left) / (right - left), -(top + bottom) / (top - bottom), -(zfar + znear) / (zfar - znear), static_cast<T>(1));
}

template <class T>
static void lookAtHelperCalculateAxes(const Vector<T, 3>& at, const Vector<T, 3>& eye, const Vector<T, 3>& up, T handedness, Vector<T, 3>* const axes)
{
	axes[2] = (at - eye).normalized();
	axes[0] = Vector<T, 3>::crossProduct(up, axes[2]).Normalized();
	axes[1] = Vector<T, 3>::crossProduct(axes[2], axes[0]);
	axes[3] = Vector<T, 3>(handedness * Vector<T, 3>::DotProduct(axes[0], eye), -Vector<T, 3>::dotProduct(axes[1], eye), handedness * Vector<T, 3>::dotProduct(axes[2], eye));
	// Default calculation is left-handed (i.e. handedness=-1).
	// Negate x and z axes for right-handed (i.e. handedness=+1) case.
	const T neg = -handedness;
	axes[0] *= neg;
	axes[2] *= neg;
}

template <class T>
static inline Matrix<T, 4, 4> lookAtHelper(const Vector<T, 3>& at, const Vector<T, 3>& eye, const Vector<T, 3>& up, T handedness)
{
	Vector<T, 3> axes[4];
	lookAtHelperCalculateAxes(at, eye, up, handedness, axes);
	const Vector<T, 4> column0(axes[0][0], axes[1][0], axes[2][0], 0);
	const Vector<T, 4> column1(axes[0][1], axes[1][1], axes[2][1], 0);
	const Vector<T, 4> column2(axes[0][2], axes[1][2], axes[2][2], 0);
	const Vector<T, 4> column3(axes[3], 1);
	return Matrix<T, 4, 4>(column0, column1, column2, column3);
}

template <class T>
static inline bool unProjectHelper(const Vector<T, 3>& window_coord, const Matrix<T, 4, 4>& model_view, const Matrix<T, 4, 4>& projection, const F32 window_width, const F32 window_height, Vector<T, 3>& result) 
{
	if (window_coord.z() < static_cast<T>(0) || window_coord.z() > static_cast<T>(1))
	{
		// window_coord.z should be with in [0, 1]
		// 0: near plane
		// 1: far plane
		return false;
	}
	Matrix<T, 4, 4> matrix = (projection * model_view).inverse();
	Vector<T, 4> standardized = Vector<T, 4>(static_cast<T>(2) * (window_coord.x() - window_width) / window_width + static_cast<T>(1), static_cast<T>(2) * (window_coord.y() - window_height) / window_height + static_cast<T>(1), static_cast<T>(2) * window_coord.z() - static_cast<T>(1), static_cast<T>(1));
	Vector<T, 4> multiply = matrix * standardized;
	if (multiply.w() == static_cast<T>(0)) 
	{
		return false;
	}
	result = multiply.xyz() / multiply.w();
	return true;
}

using Matrix2 = Matrix<F32, 2, 2>; // Sizeof 16
using Matrix3 = Matrix<F32, 3, 3>; // Sizeof 36
using Matrix4 = Matrix<F32, 4, 4>; // Sizeof 64
using Matrix2i = Matrix<I32, 2, 2>; // Sizeof 16
using Matrix3i = Matrix<I32, 3, 3>; // Sizeof 36
using Matrix4i = Matrix<I32, 4, 4>; // Sizeof 64
using Matrix2u = Matrix<U32, 2, 2>; // Sizeof 16
using Matrix3u = Matrix<U32, 3, 3>; // Sizeof 36
using Matrix4u = Matrix<U32, 4, 4>; // Sizeof 64

using AffineMatrix = Matrix<F32, 4, 3>;

static const AffineMatrix AffineIdentity(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

// Be compatible with GLSL
using mat2 = Matrix<F32, 2, 2>;
using mat3 = Matrix<F32, 3, 3>;
using mat4 = Matrix<F32, 4, 4>;

} // namespace oe

#endif // OE_MATRIX_HPP
