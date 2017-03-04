#ifndef OE_QUATERNION_HPP
#define OE_QUATERNION_HPP

#include "Matrix3.hpp"
#include "Matrix4.hpp"

namespace oe
{

class Quaternion 
{
	public:
		Quaternion();
		Quaternion(const Quaternion& q);
		Quaternion(F32 s1, F32 s2, F32 s3, F32 s4);
		Quaternion(F32 s, const Vector3& v);
		
		F32& scalar();
		const F32& scalar() const;

		Vector3& vector();
		const Vector3& vector() const;

		Quaternion inversed() const;

		Quaternion& operator=(const Quaternion& q);

		Quaternion operator*(const Quaternion& q) const;
		Quaternion operator*(F32 s) const;
		Vector3 operator*(const Vector3& v) const;

		F32 normalize();
		Quaternion normalized() const;

		void toAngleAxis(F32* angle, Vector3* axis) const;
		Vector3 toEulerAngles() const;
		Matrix3 toMatrix() const;
		Matrix4 toMatrix4() const;

		static Quaternion fromAngleAxis(F32 angle, const Vector3& axis);
		static Quaternion fromEulerAngles(const Vector3& angles);
		static Quaternion fromMatrix(const Matrix3& m);

		static Quaternion slerp(const Quaternion& q1, const Quaternion& q2, F32 percent);

		F32& operator[](const U8 i);
		const F32& operator[](const U8 i) const;

		static Vector3 perpendicularVector(const Vector3& v);

		static Quaternion rotateFromToWithAxis(const Vector3& v1, const Vector3& v2, const Vector3& preferred_axis);
		static Quaternion rotateFromTo(const Vector3& v1, const Vector3& v2);

		static Quaternion identity();

	private:
		F32 mScalar;
		Vector3 mVector;
};

Quaternion operator*(F32 s, const Quaternion& q);

// Be compatible with GLSL
using quat = Quaternion;

} // namespace oe

#endif // OE_QUATERNION_HPP