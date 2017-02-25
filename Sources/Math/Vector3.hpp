#ifndef OE_VECTOR3_HPP
#define OE_VECTOR3_HPP

#include "../Core/Prerequisites.hpp"
#include "Math.hpp"

namespace oe 
{

class Vector2;
class Vector3;
class Vector4;

struct VectorPacked3
{
	VectorPacked3();
	explicit VectorPacked3(const Vector3& vector);
	VectorPacked3& operator=(const Vector3& vector);
  
	F32 data[3];
};

class Vector3
{
	public:
		Vector3();
		Vector3(const Vector3& v);
		explicit Vector3(F32 s);
		explicit Vector3(F32* a);
		Vector3(F32 x, F32 y, F32 z = 0.f);
		Vector3(const Vector2& v, F32 z = 0.f);
		explicit Vector3(const VectorPacked3& vector);

		F32& operator()(const U8 i);
		const F32& operator()(const U8 i) const;

		F32& operator[](const U8 i);
		const F32& operator[](const U8 i) const;

		F32& x();
		F32& y();
		F32& z();
		const F32& x() const;
		const F32& y() const;
		const F32& z() const;
		
		Vector2 xy();
		Vector2 yz();
		Vector2 xz();
		const Vector2 xy() const;
		const Vector2 yz() const;
		const Vector2 xz() const;

		void pack(VectorPacked3* vector) const;

		Vector3& operator=(const Vector3& v);

		bool operator==(const Vector3& v) const;
		bool operator!=(const Vector3& v) const;
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
		
		bool isZero() const;
		F32 getLengthSquared() const;
		F32 getLength() const;
		void setLength(F32 length);
		F32 normalize();
		Vector3 normalized() const;

		static F32 dotProduct(const Vector3& v1, const Vector3& v2);
		static Vector3 hadamardProduct(const Vector3& v1, const Vector3& v2);
		static Vector3 crossProduct(const Vector3& v1, const Vector3& v2);
		static F32 distance(const Vector3& v1, const Vector3& v2);

		static Vector3 lerp(const Vector3& v1, const Vector3& v2, F32 percent);
		
		static const U8 dim();

		static const Vector3 zeros();
		static const Vector3 ones();
		static const Vector3 axisX();
		static const Vector3 axisY();
		static const Vector3 axisZ();

	private:
		F32 mData[3];
};

// Operators
Vector3 operator*(F32 s, const Vector3& v);
Vector3 operator+(F32 s, const Vector3& v);
Vector3 operator-(F32 s, const Vector3& v);


// Be compatible with GLSL
using vec3 = Vector3;
using vec3_packed = VectorPacked3;

F32 dot(const Vector3& v1, const Vector3& v2);
Vector3 normalize(const Vector3& v);


// To String / From String conversions
template <>
inline std::string toString<Vector3>(const Vector3& value)
{
	std::ostringstream oss;
	oss << toString(value.x()) << ',' << toString(value.y()) << ',' << toString(value.z());
	return oss.str();
}

template <>
inline Vector3 fromString<Vector3>(const std::string& string)
{
	std::string str(string);
	Vector3 vector;
	vector.x() = fromString<F32>(split(str, ','));
	vector.y() = fromString<F32>(split(str, ','));
	vector.z() = fromString<F32>(str);
	return vector;
}

} // namespace oe

#endif // OE_VECTOR3_HPP
