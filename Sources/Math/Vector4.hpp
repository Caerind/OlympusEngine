#ifndef OE_VECTOR4_HPP
#define OE_VECTOR4_HPP

#include "../Core/Prerequisites.hpp"
#include "Math.hpp"

namespace oe 
{

class Vector2;
class Vector3;
class Vector4;

struct VectorPacked4
{
	VectorPacked4();
	explicit VectorPacked4(const Vector4& vector);
	VectorPacked4& operator=(const Vector4& vector);
  
	F32 data[4];
};

class Vector4
{
	public:
		Vector4();
		Vector4(const Vector4& v);
		explicit Vector4(F32 s);
		explicit Vector4(F32* a);
		Vector4(F32 x, F32 y, F32 z = 0.f, F32 w = 0.f);
		Vector4(const Vector2& v, F32 z = 0.f, F32 w = 0.f);
		Vector4(const Vector3& v, F32 w = 0.f);
		explicit Vector4(const VectorPacked4& vector);

		F32& operator()(const U8 i);
		const F32& operator()(const U8 i) const;

		F32& operator[](const U8 i);
		const F32& operator[](const U8 i) const;

		F32& x();
		F32& y();
		F32& z();
		F32& w();
		const F32& x() const;
		const F32& y() const;
		const F32& z() const;
		const F32& w() const;
		
		Vector2 xy();
		Vector2 yz();
		Vector2 xz();
		Vector2 zw();
		Vector3 xyz();
		const Vector2 xy() const;
		const Vector2 yz() const;
		const Vector2 xz() const;
		const Vector2 zw() const;
		const Vector3 xyz() const;

		void pack(VectorPacked4* vector) const;

		Vector4& operator=(const Vector4& v);

		bool operator==(const Vector4& v) const;
		bool operator!=(const Vector4& v) const;
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
		
		bool isZero() const;
		F32 getLengthSquared() const;
		F32 getLength() const;
		void setLength(F32 length);
		F32 normalize();
		Vector4 normalized() const;

		static F32 dotProduct(const Vector4& v1, const Vector4& v2);
		static Vector4 hadamardProduct(const Vector4& v1, const Vector4& v2);
		static F32 distance(const Vector4& v1, const Vector4& v2);

		static Vector4 lerp(const Vector4& v1, const Vector4& v2, F32 percent);
		
		static const U8 dim();

		static const Vector4 zeros();
		static const Vector4 ones();
		static const Vector4 axisX();
		static const Vector4 axisY();
		static const Vector4 axisZ();
		static const Vector4 axisW();

	private:
		F32 mData[4];
};

// Operators
Vector4 operator*(F32 s, const Vector4& v);
Vector4 operator+(F32 s, const Vector4& v);
Vector4 operator-(F32 s, const Vector4& v);


// Be compatible with GLSL
using vec4 = Vector4;
using vec4_packed = VectorPacked4;

F32 dot(const Vector4& v1, const Vector4& v2);
Vector4 normalize(const Vector4& v);


// To String / From String conversions
template <>
inline std::string toString<Vector4>(const Vector4& value)
{
	std::ostringstream oss;
	oss << toString(value.x()) << ',' << toString(value.y()) << ',' << toString(value.z()) << ',' << toString(value.w());
	return oss.str();
}

template <>
inline Vector4 fromString<Vector4>(const std::string& string)
{
	std::string str(string);
	Vector4 vector;
	vector.x() = fromString<F32>(split(str, ','));
	vector.y() = fromString<F32>(split(str, ','));
	vector.z() = fromString<F32>(split(str, ','));
	vector.w() = fromString<F32>(str);
	return vector;
}

} // namespace oe

#endif // OE_VECTOR4_HPP
