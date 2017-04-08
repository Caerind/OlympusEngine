#ifndef OE_QUATERNION_HPP
#define OE_QUATERNION_HPP

#include "Matrix4.hpp"

namespace oe
{

class Quaternion 
{
	public:
		Quaternion();
		Quaternion(const Quaternion& q);
		Quaternion(F32 x, F32 y, F32 z, F32 w);
		Quaternion(const Vector3& v, F32 w);
		Quaternion(F32 pitch, F32 yaw, F32 roll);
		Quaternion(const Vector3& eulerAngles);
		Quaternion(F32 angle, const Vector3& axis);
		Quaternion(const F32 q[4]);
		~Quaternion() = default;

		Quaternion& set(const Quaternion& q);
		Quaternion& set(F32 x, F32 y, F32 z, F32 w);
		Quaternion& set(const Vector3& v, F32 w);
		Quaternion& set(F32 pitch, F32 yaw, F32 roll);
		Quaternion& set(const Vector3& eulerAngles);
		Quaternion& set(F32 angle, const Vector3& axis);
		Quaternion& set(const F32 q[4]);

		Quaternion& operator=(const Quaternion& q);
		bool operator==(const Quaternion& q) const;
		bool operator!=(const Quaternion& q) const;
		Quaternion operator*(const Quaternion& q) const;
		Quaternion operator*(F32 scale) const;
		Quaternion& operator*=(const Quaternion& q);
		Quaternion& operator*=(F32 scale);
		Vector3 operator*(const Vector3& v) const;
		operator F32* ();
		operator const F32* () const;

		Quaternion& computeW();
		Quaternion& conjugate();
		Quaternion& inverse();
		Quaternion& normalize(F32* oldLength = nullptr);

		F32 dotProduct(const Quaternion& q) const;
		F32 getSquaredMagnitude() const;
		F32 getMagnitude() const;
		Quaternion getConjugate() const;
		Quaternion getInverse() const;
		Quaternion getNormal(F32* oldLength = nullptr) const;
		Vector3 getVector() const;
		Vector3 getEulerAngles() const;
		void getAngleAxis(F32* angle, Vector3* axis);

		Quaternion& makeRotation(const Vector3& from, const Vector3& to);
		Quaternion& makeZero();
		Quaternion& makeIdentity();

		static Quaternion normalize(const Quaternion& quat, F32* length = nullptr);
		static Quaternion rotation(const Vector3& from, const Vector3& to);
		static Quaternion lerp(const Quaternion& start, const Quaternion& end, F32 percent);
		static Quaternion slerp(const Quaternion& start, const Quaternion& end, F32 percent);
		static Quaternion zero();
		static Quaternion identity();

		static const U8 dim();

		F32 x, y, z, w;
};

Quaternion operator*(F32 scale, const Quaternion& q);

// Be compatible with GLSL
using quat = Quaternion;

} // namespace oe

#endif // OE_QUATERNION_HPP