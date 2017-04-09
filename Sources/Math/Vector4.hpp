#ifndef OE_VECTOR4_HPP
#define OE_VECTOR4_HPP

#include "Math.hpp"

namespace oe 
{

class Vector2;
class Vector3;

class Vector4
{
	public:
		Vector4();
		Vector4(const Vector2& v, F32 z = 0.0f, F32 w = 1.0f);
		Vector4(const Vector3& v, F32 w = 1.0f);
		Vector4(const Vector4& v);
		Vector4(const F32 v[4]);
		Vector4(F32 x, F32 y, F32 z, F32 w = 1.0f);
		Vector4(F32 s);
		~Vector4() = default;

		Vector4& set(const Vector2& v, F32 z = 0.0f, F32 w = 1.0f);
		Vector4& set(const Vector3& v, F32 w = 1.0f);
		Vector4& set(const Vector4& v);
		Vector4& set(const F32 v[4]);
		Vector4& set(F32 x, F32 y, F32 z, F32 w = 1.0f);
		Vector4& set(F32 s);

		Vector4& operator=(const Vector4& v);
		bool operator==(const Vector4& v) const;
		bool operator!=(const Vector4& v) const;
		const Vector4& operator+() const;
		Vector4 operator-() const;
		Vector4 operator*(const Vector4& v) const;
		Vector4 operator/(const Vector4& v) const;
		Vector4 operator+(const Vector4& v) const;
		Vector4 operator-(const Vector4& v) const;
		Vector4 operator*(F32 s) const;
		Vector4 operator/(F32 s) const;
		Vector4 operator+(F32 s) const;
		Vector4 operator-(F32 s) const;
		Vector4& operator*=(const Vector4& v);
		Vector4& operator/=(const Vector4& v);
		Vector4& operator+=(const Vector4& v);
		Vector4& operator-=(const Vector4& v);
		Vector4& operator*=(F32 s);
		Vector4& operator/=(F32 s);
		Vector4& operator+=(F32 s);
		Vector4& operator-=(F32 s);
		bool operator<(const Vector4& vec) const;
		bool operator<=(const Vector4& vec) const;
		bool operator>(const Vector4& vec) const;
		bool operator>=(const Vector4& vec) const; 
		operator F32* ();
		operator const F32* () const;

		Vector2 toVector2() const;
		Vector3 toVector3() const;
		Vector4 toVector4() const;

		Vector2 xy();
		Vector2 yz();
		Vector2 xz();
		Vector3 xyz();
		const Vector2 xy() const;
		const Vector2 yz() const;
		const Vector2 xz() const;
		const Vector3 xyz() const;
		
		bool isZero() const;
		F32 getSquaredLength() const;
		F32 getLength() const;
		Vector4& setLength(F32 length, F32* oldLength = nullptr);
		Vector4& normalize(F32* oldLength = nullptr);
		Vector4 getNormal(F32* oldLength = nullptr) const;

		Vector4& makeZero();
		Vector4& makeOne();
		Vector4& makeAxisX();
		Vector4& makeAxisY();
		Vector4& makeAxisZ();
		Vector4& makeAxisW();

		Vector4& minimize(const Vector4& min);
		Vector4& maximize(const Vector4& max);

		F32 dotProduct(const Vector4& v) const;
		F32 absDotProduct(const Vector4& v) const;
		F32 squaredDistance(const Vector4& v) const;
		F32 distance(const Vector4& v) const;
		Vector4 hadamardProduct(const Vector4& v) const;
		
		static F32 dotProduct(const Vector4& v1, const Vector4& v2);
		static F32 absDotProduct(const Vector4& v1, const Vector4& v2);
		static F32 squaredDistance(const Vector4& v1, const Vector4& v2);
		static F32 distance(const Vector4& v1, const Vector4& v2);
		static Vector4 hadamardProduct(const Vector4& v1, const Vector4& v2);

		static Vector4 lerp(const Vector4& start, const Vector4& end, F32 percent);
		
		static const U8 dim();

		static const Vector4 zero();
		static const Vector4 one();
		static const Vector4 axisX();
		static const Vector4 axisY();
		static const Vector4 axisZ();
		static const Vector4 axisW();

		F32 x, y, z, w;
};

// Operators
Vector4 operator*(F32 s, const Vector4& v);
Vector4 operator+(F32 s, const Vector4& v);
Vector4 operator-(F32 s, const Vector4& v);

// Be compatible with GLSL
using vec4 = Vector4;

// To String / From String conversions
template <>
inline std::string toString<Vector4>(const Vector4& v)
{
	std::ostringstream oss;
	oss << toString<F32>(v.x) << ',' << toString<F32>(v.y) << ',' << toString<F32>(v.z) << ',' << toString<F32>(v.w);
	return oss.str();
}

template <>
inline Vector4 fromString<Vector4>(const std::string& string)
{
	std::string str(string);
	Vector4 vector;
	vector.x = fromString<F32>(split(str, ','));
	vector.y = fromString<F32>(split(str, ','));
	vector.z = fromString<F32>(split(str, ','));
	vector.w = fromString<F32>(str);
	return vector;
}

} // namespace oe

#endif // OE_VECTOR4_HPP
