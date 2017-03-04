#ifndef OE_VECTOR2_HPP
#define OE_VECTOR2_HPP

#include "../Core/Prerequisites.hpp"
#include "Math.hpp"

namespace oe 
{

class Vector2;
class Vector3;
class Vector4;

struct VectorPacked2
{
	VectorPacked2();
	explicit VectorPacked2(const Vector2& vector);
	VectorPacked2& operator=(const Vector2& vector);
  
	F32 data[2];
};

class Vector2
{
	public:
		Vector2();
		Vector2(const Vector2& v);
		explicit Vector2(F32 s);
		explicit Vector2(const F32* const a);
		Vector2(F32 x, F32 y);
		explicit Vector2(const VectorPacked2& vector);

		F32& operator()(const U8 i);
		const F32& operator()(const U8 i) const;

		F32& operator[](const U8 i);
		const F32& operator[](const U8 i) const;

		F32& x();
		F32& y();
		const F32& x() const;
		const F32& y() const;

		void pack(VectorPacked2* vector) const;

		Vector2& operator=(const Vector2& v);

		bool operator==(const Vector2& v) const;
		bool operator!=(const Vector2& v) const;
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

		Vector2 toVector2() const;
		Vector3 toVector3() const;
		Vector4 toVector4() const;
		
		bool isZero() const;
		F32 getLengthSquared() const;
		F32 getLength() const;
		void setLength(F32 length);
		F32 normalize();
		Vector2 normalized() const;

		F32 getPolarAngle() const;
		void setPolarAngle(F32 angle);
		void rotate(F32 angle);
		Vector2 rotated(F32 angle);
		
		static Vector2 normalized(F32 angle);
		static Vector2 polarVector(F32 angle, F32 length);
		static F32 polarAngle(const Vector2& v1, const Vector2& v2);

		static F32 dotProduct(const Vector2& v1, const Vector2& v2);
		static Vector2 hadamardProduct(const Vector2& v1, const Vector2& v2);
		static F32 crossProduct(const Vector2& v1, const Vector2& v2);
		static F32 distance(const Vector2& v1, const Vector2& v2);

		static Vector2 lerp(const Vector2& v1, const Vector2& v2, F32 percent);
		
		static const U8 dim();

		static const Vector2 zeros();
		static const Vector2 ones();
		static const Vector2 axisX();
		static const Vector2 axisY();

	private:
		F32 mData[2];
};

// Operators
Vector2 operator*(F32 s, const Vector2& v);
Vector2 operator+(F32 s, const Vector2& v);
Vector2 operator-(F32 s, const Vector2& v);


// Be compatible with GLSL
using vec2 = Vector2;
using vec2_packed = VectorPacked2;

F32 dot(const Vector2& v1, const Vector2& v2);
Vector2 normalize(const Vector2& v);


// To String / From String conversions
template <>
inline std::string toString<Vector2>(const Vector2& value)
{
	std::ostringstream oss;
	oss << toString(value.x()) << ',' << toString(value.y());
	return oss.str();
}

template <>
inline Vector2 fromString<Vector2>(const std::string& string)
{
	std::string str(string);
	Vector2 vector;
	vector.x() = fromString<F32>(split(str, ','));
	vector.y() = fromString<F32>(str);
	return vector;
}

} // namespace oe

#endif // OE_VECTOR2_HPP
