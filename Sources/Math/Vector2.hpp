#ifndef OE_VECTOR2_HPP
#define OE_VECTOR2_HPP

#include "Math.hpp"

namespace oe 
{

class Vector2i;
class Vector3;
class Vector4;

class Vector2
{
	public:
		Vector2();
		Vector2(const Vector2i& v);
		Vector2(const Vector2& v);
		Vector2(const Vector3& v);
		Vector2(const Vector4& v);
		Vector2(const F32 v[2]);
		Vector2(F32 x, F32 y);
		Vector2(F32 s);
		~Vector2() = default;

		Vector2& set(const Vector2i& v);
		Vector2& set(const Vector2& v);
		Vector2& set(const Vector3& v);
		Vector2& set(const Vector4& v);
		Vector2& set(const F32 v[2]);
		Vector2& set(F32 x, F32 y);
		Vector2& set(F32 s);

		Vector2& operator=(const Vector2i& v);
		Vector2& operator=(const Vector2& v);
		bool operator==(const Vector2& v) const;
		bool operator!=(const Vector2& v) const;
		const Vector2& operator+() const;
		Vector2 operator-() const;
		Vector2 operator*(const Vector2& v) const;
		Vector2 operator/(const Vector2& v) const;
		Vector2 operator+(const Vector2& v) const;
		Vector2 operator-(const Vector2& v) const;
		Vector2 operator*(F32 s) const;
		Vector2 operator/(F32 s) const;
		Vector2 operator+(F32 s) const;
		Vector2 operator-(F32 s) const;
		Vector2& operator*=(const Vector2& v);
		Vector2& operator/=(const Vector2& v);
		Vector2& operator+=(const Vector2& v);
		Vector2& operator-=(const Vector2& v);
		Vector2& operator*=(F32 s);
		Vector2& operator/=(F32 s);
		Vector2& operator+=(F32 s);
		Vector2& operator-=(F32 s); 
		bool operator<(const Vector2& vec) const;
		bool operator<=(const Vector2& vec) const;
		bool operator>(const Vector2& vec) const;
		bool operator>=(const Vector2& vec) const;
		operator F32* ();
		operator const F32* () const;

		Vector2 toVector2() const;
		Vector3 toVector3() const;
		Vector4 toVector4() const;

		bool isZero() const;
		F32 getSquaredLength() const;
		F32 getLength() const;
		F32 getPolarAngle() const;
		Vector2& setLength(F32 length, F32* oldLength = nullptr);
		Vector2& normalize(F32* oldLength = nullptr);
		Vector2& setPolarAngle(F32 angle);
		Vector2& rotate(F32 angle);
		Vector2 getNormal(F32* oldLength = nullptr) const;
		Vector2 getRotated(F32 angle) const;

		Vector2& makeZero();
		Vector2& makeOne();
		Vector2& makeAxisX();
		Vector2& makeAxisY();

		Vector2& minimize(const Vector2& min);
		Vector2& maximize(const Vector2& max);

		F32 dotProduct(const Vector2& v) const;
		F32 absDotProduct(const Vector2& v) const;
		F32 squaredDistance(const Vector2& v) const;
		F32 distance(const Vector2& v) const;
		F32 angleBetween(const Vector2& v) const;
		F32 crossProduct(const Vector2& v) const;
		Vector2 hadamardProduct(const Vector2& v) const;
		
		static Vector2 polarVector(F32 angle, F32 length = 1.0f);
		static F32 dotProduct(const Vector2& v1, const Vector2& v2);
		static F32 absDotProduct(const Vector2& v1, const Vector2& v2);
		static F32 squaredDistance(const Vector2& v1, const Vector2& v2);
		static F32 distance(const Vector2& v1, const Vector2& v2);
		static F32 angleBetween(const Vector2& v1, const Vector2& v2);
		static F32 crossProduct(const Vector2& v1, const Vector2& v2);
		static Vector2 hadamardProduct(const Vector2& v1, const Vector2& v2);

		static Vector2 lerp(const Vector2& start, const Vector2& end, F32 percent);
		
		static const U8 dim();

		static const Vector2 zero();
		static const Vector2 one();
		static const Vector2 axisX();
		static const Vector2 axisY();

		F32 x, y;
};

// Operators
Vector2 operator*(F32 s, const Vector2& v);
Vector2 operator+(F32 s, const Vector2& v);
Vector2 operator-(F32 s, const Vector2& v);

// Be compatible with GLSL
using vec2 = Vector2;

// To String / From String conversions
template <>
inline std::string toString<Vector2>(const Vector2& v)
{
	std::ostringstream oss;
	oss << toString<F32>(v.x) << ',' << toString<F32>(v.y);
	return oss.str();
}

template <>
inline Vector2 fromString<Vector2>(const std::string& string)
{
	std::string str(string);
	Vector2 vector;
	vector.x = fromString<F32>(split(str, ','));
	vector.y = fromString<F32>(str);
	return vector;
}

} // namespace oe

#endif // OE_VECTOR2_HPP
