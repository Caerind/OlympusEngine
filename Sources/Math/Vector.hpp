#ifndef OE_VECTOR_HPP
#define OE_VECTOR_HPP

#include "../Config.hpp"
#include "../Core/String.hpp"
#include "Math.hpp"

namespace oe 
{

template <class T, U8 d>
class Vector;

template <class T, U8 d>
static inline T dotProductHelper(const Vector<T, d>& v1, const Vector<T, d>& v2);
template <class T>
static inline T dotProductHelper(const Vector<T, 2>& v1, const Vector<T, 2>& v2);
template <class T>
static inline T dotProductHelper(const Vector<T, 3>& v1, const Vector<T, 3>& v2);
template <class T>
static inline T dotProductHelper(const Vector<T, 4>& v1, const Vector<T, 4>& v2);

template <class T, U8 d>
struct OE_API VectorPacked 
{
	VectorPacked() 
	{
	}
  
	explicit VectorPacked(const Vector<T, d>& vector) 
	{ 
		vector.pack(this); 
	}
  
	VectorPacked& operator=(const Vector<T, d>& vector) 
	{
		vector.pack(this);
		return *this;
	}
  
	T data[d];
};

template <class T, U8 d>
class OE_API Vector 
{
	public:
		using Scalar = T;
	
		inline Vector() 
		{
			for (U8 i = 0; i < d; i++)
			{
				mData[i] = 0;
			}
		}
		
		inline Vector(const Vector<T, d>& v) 
		{
			for (U8 i = 0; i < d; i++)
			{
				mData[i] = v.mData[i];
			}
		}
		
		template <typename U>
		explicit inline Vector(const Vector<U, d>& v)
		{
			for (U8 i = 0; i < d; i++)
			{
				mData[i] = static_cast<T>(v[i]);
			}
		}
		
		explicit inline Vector(const T& s) 
		{ 
			for (U8 i = 0; i < d; i++)
			{
				mData[i] = s;
			}
		}
		
		explicit inline Vector(const T* a) 
		{
			for (U8 i = 0; i < d; i++)
			{
				mData[i] = a[i];
			}
		}
		
		template <typename U>
		explicit inline Vector(const U* a) 
		{
			for (U8 i = 0; i < d; i++)
			{
				mData[i] = static_cast<T>(a[i]);
			}
		}
		
		inline Vector(const T& s1, const T& s2) 
		{
			ASSERT(d == 2);
			mData[0] = s1;
			mData[1] = s2;
		}

		inline Vector(const T& s1, const T& s2, const T& s3) 
		{
			ASSERT(d == 3);
			mData[0] = s1;
			mData[1] = s2;
			mData[2] = s3;
		}
		
		inline Vector(const Vector<T, 2>& v12, const T& s3) 
		{
			ASSERT(d == 3);
			mData[0] = v12.x();
			mData[1] = v12.y();
			mData[2] = s3;
		}
		
		inline Vector(const T& s1, const T& s2, const T& s3, const T& s4) 
		{
			ASSERT(d == 4);
			mData[0] = s1;
			mData[1] = s2;
			mData[2] = s3;
			mData[3] = s4;
		}

		inline Vector(const Vector<T, 3>& vector3, const T& value) 
		{
			ASSERT(d == 4);
			mData[0] = vector3[0];
			mData[1] = vector3[1];
			mData[2] = vector3[2];
			mData[3] = value;
		}

		explicit inline Vector(const VectorPacked<T, d>& vector) 
		{
			for (U8 i = 0; i < d; i++)
			{
				mData[i] = vector.data[i];
			}
		}
		
		template <typename U>
		explicit inline Vector(const VectorPacked<U, d>& vector) 
		{
			for (U8 i = 0; i < d; i++)
			{
				mData[i] = static_cast<T>(vector.data[i]);
			}
		}

		inline T& operator()(const U8 i) 
		{ 
			return mData[i]; 
		}

		inline const T& operator()(const U8 i) const 
		{ 
			return mData[i]; 
		}

		inline T& operator[](const U8 i) 
		{ 
			return mData[i]; 
		}

		inline const T& operator[](const U8 i) const 
		{ 
			return mData[i]; 
		}

		inline T& x() 
		{
			ASSERT(d > 0);
			return mData[0];
		}

		inline T& y() 
		{
			ASSERT(d > 1);
			return mData[1];
		}

		inline T& z() 
		{
			ASSERT(d > 2);
			return mData[2];
		}

		inline T& w() 
		{
			ASSERT(d > 3);
			return mData[3];
		}

		inline const T& x() const 
		{
			ASSERT(d > 0);
			return mData[0];
		}

		inline const T& y() const 
		{
			ASSERT(d > 1);
			return mData[1];
		}

		inline const T& z() const 
		{
			ASSERT(d > 2);
			return mData[2];
		}

		inline const T& w() const 
		{
			ASSERT(d > 3);
			return mData[3];
		}

		inline Vector<T, 3> xyz() 
		{
			ASSERT(d > 3);
			return Vector<T, 3>(x(), y(), z());
		}

		inline const Vector<T, 3> xyz() const 
		{
			ASSERT(d > 3);
			return Vector<T, 3>(x(), y(), z());
		}

		inline Vector<T, 2> xy() 
		{
			ASSERT(d > 2);
			return Vector<T, 2>(x(), y());
		}

		inline const Vector<T, 2> xy() const 
		{
			ASSERT(d > 2);
			return Vector<T, 2>(x(), y());
		}

		inline Vector<T, 2> zw() 
		{
			ASSERT(d == 4);
			return Vector<T, 2>(z(), w());
		}

		inline const Vector<T, 2> zw() const 
		{
			ASSERT(d == 4);
			return Vector<T, 2>(z(), w());
		}

		inline void pack(const VectorPacked<T, d>* vector) const 
		{
			for (U8 i = 0; i < d; i++)
			{
				vector->data[i] = mData[i];
			}
		}

		inline bool operator==(const Vector<T, d>& v) const 
		{
			for (U8 i = 0; i < d; i++) 
			{
				if (mData[i] != v[i])
				{
					return false;
				}
			}
			return true;
		}

		inline bool operator!=(const Vector<T, d>& v) const 
		{ 
			return !operator==(v); 
		}

		inline Vector<T, d> operator-() const 
		{ 
			Vector<T, d> result;
			for (U8 i = 0; i < d; i++) 
			{
				result[i] = -mData[i];
			}
			return result; 
		}

		inline Vector<T, d> operator*(const Vector<T, d>& v) const 
		{
			return hadamardProduct(*this, v);
		}

		inline Vector<T, d> operator/(const Vector<T, d>& v) const 
		{
			Vector<T, d> result;
			for (U8 i = 0; i < d; i++) 
			{
				result[i] = mData[i] / v[i];
			}
			return result; 
		}

		inline Vector<T, d> operator+(const Vector<T, d>& v) const 
		{
			Vector<T, d> result;
			for (U8 i = 0; i < d; i++) 
			{
				result[i] = mData[i] + v[i];
			}
			return result; 
		}

		inline Vector<T, d> operator-(const Vector<T, d>& v) const 
		{
			Vector<T, d> result;
			for (U8 i = 0; i < d; i++) 
			{
				result[i] = mData[i] - v[i];
			}
			return result; 
		}

		inline Vector<T, d> operator*(const T& s) const 
		{
			Vector<T, d> result;
			for (U8 i = 0; i < d; i++) 
			{
				result[i] = mData[i] * s;
			}
			return result; 
		}

		inline Vector<T, d> operator/(const T& s) const 
		{
			Vector<T, d> result;
			for (U8 i = 0; i < d; i++) 
			{
				result[i] = mData[i] / s;
			}
			return result; 
		}

		inline Vector<T, d> operator+(const T& s) const 
		{
			Vector<T, d> result;
			for (U8 i = 0; i < d; i++) 
			{
				result[i] = mData[i] + s;
			}
			return result;
		}

		inline Vector<T, d> operator-(const T& s) const 
		{
			Vector<T, d> result;
			for (U8 i = 0; i < d; i++) 
			{
				result[i] = mData[i] - s;
			}
			return result;
		}

		inline Vector<T, d>& operator*=(const Vector<T, d>& v) 
		{
			for (U8 i = 0; i < d; i++)
			{
				mData[i] *= v[i];
			}
			return *this;
		}

		inline Vector<T, d>& operator/=(const Vector<T, d>& v) 
		{
			for (U8 i = 0; i < d; i++)
			{
				mData[i] /= v[i];
			}
			return *this;
		}

		inline Vector<T, d>& operator+=(const Vector<T, d>& v) 
		{
			for (U8 i = 0; i < d; i++)
			{
				mData[i] += v[i];
			}
			return *this;
		}

		inline Vector<T, d>& operator-=(const Vector<T, d>& v) 
		{
			for (U8 i = 0; i < d; i++)
			{
				mData[i] -= v[i];
			}
			return *this;
		}

		inline Vector<T, d>& operator*=(const T& s) 
		{
			for (U8 i = 0; i < d; i++)
			{
				mData[i] *= s;
			}
			return *this;
		}

		inline Vector<T, d>& operator/=(const T& s) 
		{
			for (U8 i = 0; i < d; i++)
			{
				mData[i] /= s;
			}
			return *this;
		}

		inline Vector<T, d>& operator+=(const T& s) 
		{
			for (U8 i = 0; i < d; i++)
			{
				mData[i] += s;
			}
			return *this;
		}

		inline Vector<T, d>& operator-=(const T& s) 
		{
			for (U8 i = 0; i < d; i++)
			{
				mData[i] -= s;
			}
			return *this;
		}
		
		inline bool isZero() const
		{
			for (U8 i = 0; i < d; i++)
			{
				if (mData[i] != 0)
				{
					return false;
				}
			}
			return true;
		}

		inline T getLengthSquared() const 
		{ 
			return dotProduct(*this, *this); 
		}

		inline T getLength() const 
		{ 
			return sqrt(getLengthSquared()); 
		}
		
		inline void setLength(T length)
		{
			ASSERT(!isZero());
			const T actualLength = getLength();
			*this = *this * (length / actualLength);
		}

		inline void normalize() 
		{
			const F32 length = getLength();
			ASSERT(length > 0);
			*this /= length;
		}

		inline Vector<T, d> normalized() const 
		{ 
			const F32 length = getLength();
			ASSERT(length > 0);
			return *this / length;
		}

		static inline T dotProduct(const Vector<T, d>& v1, const Vector<T, d>& v2) 
		{
			return dotProductHelper(v1, v2);
		}

		static inline Vector<T, d> hadamardProduct(const Vector<T, d>& v1, const Vector<T, d>& v2) 
		{
			Vector<T, d> result;        
			for (U8 i = 0; i < d; i++)
			{
				result[i] = v1[i] * v2[i];
			}
			return result;  
		}
		
		static inline T distance(const Vector<T, d>& v1, const Vector<T, d>& v2)
		{
			return Vector<T, d>(v1 - v2).getLength();
		}
		
		static inline T crossProduct(const Vector<T, 2>& v1, const Vector<T, 2>& v2)
		{
			return v1.x() * v2.y() - v1.y() * v2.x();
		}

		static inline Vector<T, 3> crossProduct(const Vector<T, 3>& v1, const Vector<T, 3>& v2) 
		{
			return Vector<T, 3>(v1[1] * v2[2] - v1[2] * v2[1], v1[2] * v2[0] - v1[0] * v2[2], v1[0] * v2[1] - v1[1] * v2[0]);
		}
		
		static inline F32 getPolarAngle(const Vector<F32, 2>& vector)
		{
			return atan2(vector.y(), vector.x());
		}

		static inline void setPolarAngle(Vector<F32, 2>& vector, F32 angle)
		{
			const F32 length = vector.getLength();
			vector.x() = cos(angle);
			vector.y() = sin(angle);
			vector *= length;
		}

		static inline void rotate(Vector<F32, 2>& vector, F32 angle)
		{
			const F32 c = cos(angle);
			const F32 s = sin(angle);
			const F32 tx = c * vector.x() - s * vector.y();
			vector.y() = s * vector.x() + c * vector.y();
			vector.x() = tx;
		}
		
		static inline Vector<F32, 2> rotated(const Vector<F32, 2>& vector, F32 angle)
		{
			const F32 c = cos(angle);
			const F32 s = sin(angle);
			return Vector<F32, 2>(c * vector.x() - s * vector.y(), s * vector.x() + c * vector.y());
		}

		static inline Vector<F32, 2> normalized(F32 angle)
		{
			return Vector<F32, 2>(cos(angle), sin(angle));
		}

		static inline Vector<F32, 2> polarVector(F32 angle, F32 length)
		{
			return length * Vector<F32, 2>(cos(angle), sin(angle));
		}

		static inline F32 polarAngle(const Vector<F32, 2>& v1, const Vector<F32, 2>& v2)
		{
			return atan2(crossProduct(v1, v2), dotProduct(v1, v2));
		}

		static inline Vector<T, d> lerp(const Vector<T, d>& v1, const Vector<T, d>& v2, const T& percent) 
		{
			const T one_minus_percent = static_cast<T>(1.0) - percent;
			Vector<T, d> result;
			for (U8 i = 0; i < d; i++)
			{
				result[i] = one_minus_percent * v1[i] + percent * v2[i];
			}
			return result;  
		}
		
		static inline Vector<T, d> slerp(const Vector<T, d>& v1, const Vector<T, d>& v2, const T& percent)
		{
			// TODO : Slerp
			return lerp(v1, v2, percent);
		}
		
		static const U8 Dimension = d;

	private:
		T mData[d];
};

template <class T, U8 d>
inline Vector<T, d> operator*(const T& s, const Vector<T, d>& v) 
{
	return v * s;
}

template <class T, U8 d>
inline Vector<T, d> operator/(const Vector<T, d>& v, const T& s) 
{
	return v / s;
}

template <class T, U8 d>
inline Vector<T, d> operator+(const T& s, const Vector<T, d>& v) 
{
	return v + s;
}

template <class T, U8 d>
inline Vector<T, d> operator-(const T& s, const Vector<T, d>& v) 
{
	return v - s;
}

template <class T, U8 d>
static inline T dotProductHelper(const Vector<T, d>& v1, const Vector<T, d>& v2) 
{
	T result = 0;
	for (U8 i = 0; i < d; i++)
	{
		result += v1[i]* v2[i];
	}
	return result;
}

template <class T>
static inline T dotProductHelper(const Vector<T, 2>& v1, const Vector<T, 2>& v2) 
{
	return v1[0] * v2[0] + v1[1] * v2[1];
}

template <class T>
static inline T dotProductHelper(const Vector<T, 3>& v1, const Vector<T, 3>& v2) 
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

template <class T>
static inline T dotProductHelper(const Vector<T, 4>& v1, const Vector<T, 4>& v2) 
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3];
}

using Vector2 = Vector<F32, 2>; // Sizeof 8
using Vector3 = Vector<F32, 3>; // Sizeof 12
using Vector4 = Vector<F32, 4>; // Sizeof 16
using Vector2i = Vector<I32, 2>; // Sizeof 8
using Vector3i = Vector<I32, 3>; // Sizeof 12
using Vector4i = Vector<I32, 4>; // Sizeof 16
using Vector2u = Vector<U32, 2>; // Sizeof 8
using Vector3u = Vector<U32, 3>; // Sizeof 12
using Vector4u = Vector<U32, 4>; // Sizeof 16

static const Vector2 Zeros2(0.0f, 0.0f);
static const Vector2 Ones2(1.0f, 1.0f);
static const Vector2 AxisX2(1.0f, 0.0f);
static const Vector2 AxisY2(0.0f, 1.0f);
static const Vector3 Zeros3(0.0f, 0.0f, 0.0f);
static const Vector3 Ones3(1.0f, 1.0f, 1.0f);
static const Vector3 AxisX3(1.0f, 0.0f, 0.0f);
static const Vector3 AxisY3(0.0f, 1.0f, 0.0f);
static const Vector3 AxisZ3(0.0f, 0.0f, 1.0f);
static const Vector4 Zeros4(0.0f, 0.0f, 0.0f, 0.0f);
static const Vector4 Ones4(1.0f, 1.0f, 1.0f, 1.0f);
static const Vector4 AxisX4(1.0f, 0.0f, 0.0f, 0.0f);
static const Vector4 AxisY4(0.0f, 1.0f, 0.0f, 0.0f);
static const Vector4 AxisZ4(0.0f, 0.0f, 1.0f, 0.0f);
static const Vector4 AxisW4(0.0f, 0.0f, 0.0f, 1.0f);

static const Vector2i Ones2i(1, 1);
static const Vector2i Zeros2i(0, 0);
static const Vector2i AxisX2i(1, 0);
static const Vector2i AxisY2i(0, 1);
static const Vector3i Zeros3i(0, 0, 0);
static const Vector3i Ones3i(1, 1, 1);
static const Vector3i AxisX3i(1, 0, 0);
static const Vector3i AxisY3i(0, 1, 0);
static const Vector3i AxisZ3i(0, 0, 1);
static const Vector4i Zeros4i(0, 0, 0, 0);
static const Vector4i Ones4i(1, 1, 1 ,1);
static const Vector4i AxisX4i(1, 0, 0, 0);
static const Vector4i AxisY4i(0, 1, 0, 0);
static const Vector4i AxisZ4i(0, 0, 1, 0);
static const Vector4i AxisW4i(0, 0, 0, 1);

static const Vector2u Ones2u(1, 1);
static const Vector2u Zeros2u(0, 0);
static const Vector2u AxisX2u(1, 0);
static const Vector2u AxisY2u(0, 1);
static const Vector3u Zeros3u(0, 0, 0);
static const Vector3u Ones3u(1, 1, 1);
static const Vector3u AxisX3u(1, 0, 0);
static const Vector3u AxisY3u(0, 1, 0);
static const Vector3u AxisZ3u(0, 0, 1);
static const Vector4u Zeros4u(0, 0, 0, 0);
static const Vector4u Ones4u(1, 1, 1 ,1);
static const Vector4u AxisX4u(1, 0, 0, 0);
static const Vector4u AxisY4u(0, 1, 0, 0);
static const Vector4u AxisZ4u(0, 0, 1, 0);
static const Vector4u AxisW4u(0, 0, 0, 1);


// Be compatible with GLSL

using vec2 = Vector<F32, 2>;
using vec3 = Vector<F32, 3>;
using vec4 = Vector<F32, 4>;
using vec2i = Vector<I32, 2>;
using vec3i = Vector<I32, 3>;
using vec4i = Vector<I32, 4>;

using vec2_packed = VectorPacked<F32, 2>;
using vec3_packed = VectorPacked<F32, 3>;
using vec4_packed = VectorPacked<F32, 4>;
using vec2i_packed = VectorPacked<I32, 2>;
using vec3i_packed = VectorPacked<I32, 3>;
using vec4i_packed = VectorPacked<I32, 4>;

template <class T>
inline Vector<T, 3> cross(const Vector<T, 3>& v1, const Vector<T, 3>& v2) 
{
	return Vector<T, 3>::CrossProduct(v1,v2);
}

template <class T>
inline typename T::Scalar dot(const T& v1, const T& v2) 
{
	return T::DotProduct(v1,v2);
}

template <class T>
inline T normalize(const T& v1) 
{
	return v.normalized();
}

template <class T, U8 d>
std::string toString(const Vector<T,d>& value)
{
	std::ostringstream oss;
	for (U8 i = 0; i < d; i++)
	{
		oss << toString<T>(value[i]);
		if (i < d - 1)
		{
			oss << ',';
		}
	}
	return oss.str();
}

template <class T, U8 d> 
Vector<T,d> fromString(const std::string& string)
{
	Vector<T,d> vector;
	std::size_t found = string.find_first_of(',');
	if (found != std::string::npos)
	{
		std::istringstream iss(string.substr(0, found));
		iss >> vector.x;
		iss.clear();
		iss.str(string.substr(found + 1));
		iss >> vector.y;
	}
	return vector;
}

} // namespace oe

#endif  // OE_VECTOR_HPP
