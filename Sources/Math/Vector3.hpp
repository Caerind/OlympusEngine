#ifndef OE_VECTOR3_HPP
#define OE_VECTOR3_HPP

#include "Math.hpp"

namespace oe 
{

class Vector2;
class Vector4;

class Vector3
{
	public:
		Vector3();
		Vector3(const Vector2& v, F32 z = 0.0f);
		Vector3(const Vector3& v);
		Vector3(const Vector4& v);
		Vector3(const F32 v[3]);
		Vector3(F32 x, F32 y, F32 z = 0.0f);
		Vector3(F32 s);
		~Vector3() = default;

		Vector3& set(const Vector2& v, F32 z = 0.0f);
		Vector3& set(const Vector3& v);
		Vector3& set(const Vector4& v);
		Vector3& set(const F32 v[3]);
		Vector3& set(F32 x, F32 y, F32 z = 0.0f);
		Vector3& set(F32 s);

		Vector3& operator=(const Vector3& v);
		bool operator==(const Vector3& v) const;
		bool operator!=(const Vector3& v) const;
		const Vector3& operator+() const;
		Vector3 operator-() const;
		Vector3 operator*(const Vector3& v) const;
		Vector3 operator/(const Vector3& v) const;
		Vector3 operator+(const Vector3& v) const;
		Vector3 operator-(const Vector3& v) const;
		Vector3 operator*(F32 s) const;
		Vector3 operator/(F32 s) const;
		Vector3 operator+(F32 s) const;
		Vector3 operator-(F32 s) const;
		Vector3& operator*=(const Vector3& v);
		Vector3& operator/=(const Vector3& v);
		Vector3& operator+=(const Vector3& v);
		Vector3& operator-=(const Vector3& v);
		Vector3& operator*=(F32 s);
		Vector3& operator/=(F32 s);
		Vector3& operator+=(F32 s);
		Vector3& operator-=(F32 s);
		bool operator<(const Vector3& vec) const;
		bool operator<=(const Vector3& vec) const;
		bool operator>(const Vector3& vec) const;
		bool operator>=(const Vector3& vec) const;
		operator F32* ();
		operator const F32* () const;

		Vector2 toVector2() const;
		Vector3 toVector3() const;
		Vector4 toVector4() const;

		Vector2 xy();
		Vector2 yz();
		Vector2 xz();
		const Vector2 xy() const;
		const Vector2 yz() const;
		const Vector2 xz() const;
		
		bool isZero() const;
		F32 getSquaredLength() const;
		F32 getLength() const;
		Vector3& setLength(F32 length, F32* oldLength = nullptr);
		Vector3& normalize(F32* oldLength = nullptr);
		Vector3 getNormal(F32* oldLength = nullptr) const;

		Vector3& makeForward();
		Vector3& makeBackward();
		Vector3& makeUp();
		Vector3& makeDown();
		Vector3& makeRight();
		Vector3& makeLeft();
		Vector3& makeZero();
		Vector3& makeOne();
		Vector3& makeAxisX();
		Vector3& makeAxisY();
		Vector3& makeAxisZ();

		Vector3& minimize(const Vector3& min);
		Vector3& maximize(const Vector3& max); 
		
		F32 dotProduct(const Vector3& v) const;
		F32 absDotProduct(const Vector3& v) const;
		F32 squaredDistance(const Vector3& v) const;
		F32 distance(const Vector3& v) const;
		Vector3 crossProduct(const Vector3& v) const;
		Vector3 hadamardProduct(const Vector3& v) const;

		static F32 dotProduct(const Vector3& v1, const Vector3& v2);
		static F32 absDotProduct(const Vector3& v1, const Vector3& v2);
		static F32 squaredDistance(const Vector3& v1, const Vector3& v2);
		static F32 distance(const Vector3& v1, const Vector3& v2);
		static Vector3 crossProduct(const Vector3& v1, const Vector3& v2);
		static Vector3 hadamardProduct(const Vector3& v1, const Vector3& v2);

		static Vector3 lerp(const Vector3& start, const Vector3& end, F32 percent);

		static const U8 dim();

		static const Vector3 forward();
		static const Vector3 backward();
		static const Vector3 up();
		static const Vector3 down();
		static const Vector3 right();
		static const Vector3 left();
		static const Vector3 zero();
		static const Vector3 one();
		static const Vector3 axisX();
		static const Vector3 axisY();
		static const Vector3 axisZ();

		F32 x, y, z;
};

// Operators
Vector3 operator*(F32 s, const Vector3& v);
Vector3 operator+(F32 s, const Vector3& v);
Vector3 operator-(F32 s, const Vector3& v);

// Be compatible with GLSL
using vec3 = Vector3;

// To String / From String conversions
template <>
inline std::string toString<Vector3>(const Vector3& v)
{
	std::ostringstream oss;
	oss << toString<F32>(v.x) << ',' << toString<F32>(v.y) << ',' << toString<F32>(v.z);
	return oss.str();
}

template <>
inline Vector3 fromString<Vector3>(const std::string& string)
{
	std::string str(string);
	Vector3 vector;
	vector.x = fromString<F32>(split(str, ','));
	vector.y = fromString<F32>(split(str, ','));
	vector.z = fromString<F32>(str);
	return vector;
}

} // namespace oe

#endif // OE_VECTOR3_HPP
