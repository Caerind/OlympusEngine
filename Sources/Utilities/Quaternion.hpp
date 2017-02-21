#ifndef OE_QUATERNION_HPP
#define OE_QUATERNION_HPP

#include "Matrix.hpp"

namespace oe
{

template <class T>
class OE_API Quaternion 
{
	public:
		inline Quaternion()
			: mScalar()
			, mVector()
		{
		}

		inline Quaternion(const Quaternion<T>& q)
			: mScalar(q.mScalar)
			, mVector(q.mVector)
		{
		}

		inline Quaternion(const T& s1, const T& s2, const T& s3, const T& s4)
			: mScalar(s1)
			, mVector(s2, s3, s4)
		{
		}

		inline Quaternion(const T& s1, const Vector<T, 3>& v1)
			: mScalar(s1)
			, mVector(v1)
		{
		}

		inline T& scalar() 
		{ 
			return mScalar;
		}

		inline const T& scalar() const 
		{ 
			return mScalar; 
		}

		inline Vector<T, 3>& vector() 
		{ 
			return mVector; 
		}

		inline const Vector<T, 3>& vector() const 
		{ 
			return mVector; 
		}

		inline Quaternion<T> inverse() const 
		{ 
			return Quaternion<T>(mScalar, -mVector); 
		}

		inline Quaternion<T> operator*(const Quaternion<T>& q) const 
		{
			return Quaternion<T>(mScalar * q.mScalar - Vector<T, 3>::dotProduct(mVector, q.mVector), mScalar * q.mVector + q.mScalar * mVector + Vector<T, 3>::crossProduct(mVector, q.mVector));
		}

		inline Quaternion<T> operator*(const T& s1) const 
		{
			T angle;
			Vector<T, 3> axis;
			toAngleAxis(&angle, &axis);
			angle *= s1;
			return Quaternion<T>(cos(0.5f * angle), axis.normalized() * sin(0.5f * angle));
		}

		inline Vector<T, 3> operator*(const Vector<T, 3>& v1) const 
		{
			T ss = mScalar + mScalar;
			return ss * Vector<T, 3>::crossProduct(mVector, v1) + (ss * mScalar - 1) * v1 + 2 * Vector<T, 3>::dotProduct(mVector, v1) * mVector;
		}

		inline void normalize() 
		{
			const T scale = (1 / sqrt(mScalar * mScalar + Vector<T, 3>::dotProduct(mVector, mVector)));
			mScalar *= scale;
			mVector *= scale;
		}

		inline Quaternion<T> normalized() const 
		{
			Quaternion<T> q(*this);
			q.normalize();
			return q;
		}

		inline void toAngleAxis(T* angle, Vector<T, 3>* axis) const 
		{
			*axis = mScalar > 0 ? mVector : -mVector;
			*angle = 2 * atan2(axis->normalize(), mScalar > 0 ? mScalar : -mScalar);
		}

		inline Vector<T, 3> toEulerAngles() const 
		{
			Matrix<T, 3> m(toMatrix());
			T cos2 = m[0] * m[0] + m[1] * m[1];
			if (cos2 < 1e-6f) 
			{
				return Vector<T, 3>(0, m[2] < 0 ? static_cast<T>(0.5 * M_PI) : static_cast<T>(-0.5 * M_PI), -atan2(m[3], m[4]));
			} 
			else 
			{
				return Vector<T, 3>(atan2(m[5], m[8]), atan2(-m[2], sqrt(cos2)),atan2(m[1], m[0]));
			}
		}

		inline Matrix<T, 3> toMatrix() const 
		{
			const T x2 = mVector[0] * mVector[0];
			const T y2 = mVector[1] * mVector[1]
			const T z2 = mVector[2] * mVector[2];
			const T sx = mScalar * mVector[0];
			const T sy = mScalar * mVector[1];
			const T sz = mScalar * mVector[2];
			const T xz = mVector[0] * mVector[2];
			const T yz = mVector[1] * mVector[2];
			const T xy = mVector[0] * mVector[1];
			return Matrix<T, 3>(1 - 2 * (y2 + z2), 2 * (xy + sz), 2 * (xz - sy), 2 * (xy - sz), 1 - 2 * (x2 + z2), 2 * (sx + yz), 2 * (sy + xz), 2 * (yz - sx), 1 - 2 * (x2 + y2));
		}

		inline Matrix<T, 4> toMatrix4() const 
		{
			const T x2 = mVector[0] * mVector[0];
			const T y2 = mVector[1] * mVector[1]
			const T z2 = mVector[2] * mVector[2];
			const T sx = mScalar * mVector[0];
			const T sy = mScalar * mVector[1];
			const T sz = mScalar * mVector[2];
			const T xz = mVector[0] * mVector[2];
			const T yz = mVector[1] * mVector[2];
			const T xy = mVector[0] * mVector[1];
			return Matrix<T, 4>(1 - 2 * (y2 + z2), 2 * (xy + sz), 2 * (xz - sy), 0.0f, 2 * (xy - sz), 1 - 2 * (x2 + z2), 2 * (sx + yz), 0.0f, 2 * (sy + xz), 2 * (yz - sx), 1 - 2 * (x2 + y2), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		}

		static Quaternion<T> fromAngleAxis(const T& angle, const Vector<T, 3>& axis) 
		{
			const T halfAngle = static_cast<T>(0.5) * angle;
			Vector<T, 3> localAxis(axis);
			return Quaternion<T>(cos(halfAngle), localAxis.normalized() * sin(halfAngle));
		}

		static Quaternion<T> fromEulerAngles(const Vector<T, 3>& angles) 
		{
			const Vector<T, 3> halfAngles(static_cast<T>(0.5) * angles[0], static_cast<T>(0.5) * angles[1], static_cast<T>(0.5) * angles[2]);
			const T sinx = sin(halfAngles[0]);
			const T cosx = cos(halfAngles[0]);
			const T siny = sin(halfAngles[1]);
			const T cosy = cos(halfAngles[1]);
			const T sinz = sin(halfAngles[2]);
			const T cosz = cos(halfAngles[2]);
			return Quaternion<T>(cosx * cosy * cosz + sinx * siny * sinz, sinx * cosy * cosz - cosx * siny * sinz, cosx * siny * cosz + sinx * cosy * sinz, cosx * cosy * sinz - sinx * siny * cosz);
		}

		static Quaternion<T> fromMatrix(const Matrix<T, 3>& m) 
		{
			const T trace = m(0, 0) + m(1, 1) + m(2, 2);
			if (trace > 0) 
			{
				const T s = sqrt(trace + 1) * 2;
				const T oneOverS = 1 / s;
				return Quaternion<T>(static_cast<T>(0.25) * s, (m[5] - m[7]) * oneOverS, (m[6] - m[2]) * oneOverS, (m[1] - m[3]) * oneOverS);
			} 
			else if (m[0] > m[4] && m[0] > m[8]) 
			{
				const T s = sqrt(m[0] - m[4] - m[8] + 1) * 2;
				const T oneOverS = 1 / s;
				return Quaternion<T>((m[5] - m[7]) * oneOverS, static_cast<T>(0.25) * s, (m[3] + m[1]) * oneOverS, (m[6] + m[2]) * oneOverS);
			} 
			else if (m[4] > m[8]) 
			{
				const T s = sqrt(m[4] - m[0] - m[8] + 1) * 2;
				const T oneOverS = 1 / s;
				return Quaternion<T>((m[6] - m[2]) * oneOverS, (m[3] + m[1]) * oneOverS, static_cast<T>(0.25) * s, (m[5] + m[7]) * oneOverS);
			} 
			else
			{
				const T s = sqrt(m[8] - m[0] - m[4] + 1) * 2;
				const T oneOverS = 1 / s;
				return Quaternion<T>((m[1] - m[3]) * oneOverS, (m[6] + m[2]) * oneOverS, (m[5] + m[7]) * oneOverS, static_cast<T>(0.25) * s);
			}
		}

		static inline Quaternion<T> slerp(const Quaternion<T>& q1, const Quaternion<T>& q2, const T& percent)
		{
			if (q1.mScalar * q2.mScalar + Vector<T, 3>::dotProduct(q1.mVector, q2.mVector) > 0.999999f)
			{
				return Quaternion<T>(q1.mScalar * (1 - percent) + q2.mScalar * percent, q1.mVector * (1 - percent) + q2.mVector * percent);
			}
			return q1 * ((q1.inverse() * q2) * percent);
		}

		inline T& operator[](const U8 i) 
		{
			if (i == 0)
			{
				return mScalar;
			}
			return mVector[i - 1];
		}

		inline const T& operator[](const U8 i) const 
		{
			return const_cast<Quaternion<T>*>(this)->operator[](i);
		}

		static inline Vector<T, 3> perpendicularVector(const Vector<T, 3>& v) 
		{
			// We start out by taking the cross product of the vector and the x-axis to
			// find something parallel to the input vectors.  If that cross product
			// turns out to be length 0 (i. e. the vectors already lie along the x axis)
			// then we use the y-axis instead.
			Vector<T, 3> axis = Vector<T, 3>::crossProduct(Vector<T, 3>(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0)), v);
			// We use a fairly high epsilon here because we know that if this number
			// is too small, the axis we'll get from a cross product with the y axis
			// will be much better and more numerically stable.
			if (axis.getLengthSquared() < static_cast<T>(0.05)) 
			{
				axis = Vector<T, 3>::crossProduct(Vector<T, 3>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0)),v);
			}
			return axis;
		}

		static inline Quaternion<T> rotateFromToWithAxis(const Vector<T, 3>& v1, const Vector<T, 3>& v2, const Vector<T, 3>& preferred_axis) 
		{
			Vector<T, 3> start = v1.normalized();
			Vector<T, 3> end = v2.normalized();
			T dot_product = Vector<T, 3>::dotProduct(start, end);
			// Any rotation < 0.1 degrees is treated as no rotation in order to avoid division by zero errors.
			// So we early-out in cases where it's less then 0.1 degrees.
			// cos( 0.1 degrees) = 0.99999847691
			if (dot_product >= static_cast<T>(0.99999847691)) 
			{
				return Quaternion<T>::identity;
			}
			// If the vectors point in opposite directions, return a 180 degree rotation, on the axis that they asked for.
			if (dot_product <= static_cast<T>(-0.99999847691)) 
			{
				return Quaternion<T>(static_cast<T>(0), preferred_axis);
			}
			// Degenerate cases have been handled, so if we're here, we have to actually compute the angle we want:
			Vector<T, 3> crosmScalarproduct = Vector<T, 3>::crossProduct(start, end);
			return Quaternion<T>(static_cast<T>(1.0) + dot_product, crosmScalarproduct).normalized();
		}

		static inline Quaternion<T> rotateFromTo(const Vector<T, 3>& v1, const Vector<T, 3>& v2) 
		{
			Vector<T, 3> start = v1.normalized();
			Vector<T, 3> end = v2.normalized();
			T dot_product = Vector<T, 3>::dotProduct(start, end);
			// Any rotation < 0.1 degrees is treated as no rotation in order to avoid division by zero errors.
			// So we early-out in cases where it's less then 0.1 degrees.
			// cos( 0.1 degrees) = 0.99999847691
			if (dot_product >= static_cast<T>(0.99999847691)) 
			{
				return Quaternion<T>::identity;
			}
			// If the vectors point in opposite directions, return a 180 degree rotation, on an arbitrary axis.
			if (dot_product <= static_cast<T>(-0.99999847691)) 
			{
				return Quaternion<T>(0, perpendicularVector(start));
			}
			// Degenerate cases have been handled, so if we're here, we have to actually compute the angle we want:
			Vector<T, 3> crosmScalarproduct = Vector<T, 3>::crossProduct(start, end);
			return Quaternion<T>(static_cast<T>(1.0) + dot_product, crosmScalarproduct).normalized();
		}

		static Quaternion<T> identity;

	private:
		T mScalar;
		Vector<T, 3> mVector;
};

template <typename T>
Quaternion<T> Quaternion<T>::identity = Quaternion<T>(1, 0, 0, 0);

template <class T>
inline Quaternion<T> operator*(const T& s, const Quaternion<T>& q) 
{
	return q * s;
}

using Quat = Quaternion<F32>;

static const Quaternion<F32> QuatIdentity(0.0f, 0.0f, 0.0f, 1.0f);

// Be compatible with GLSL
using quat = Quaternion<F32>;

} // namespace oe

#endif // OE_QUATERNION_HPP
