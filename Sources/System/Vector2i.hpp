#ifndef OE_VECTOR2I_HPP
#define OE_VECTOR2I_HPP

#include "Prerequisites.hpp"

namespace oe
{
	
class Vector2;

class Vector2i
{
	public:
		Vector2i();
		Vector2i(I32 s);
		Vector2i(I32 x, I32 y);
		Vector2i(const I32 v[2]);
		Vector2i(const Vector2& v);
		Vector2i(const Vector2i& v);
		
		Vector2i& set(I32 s);
		Vector2i& set(I32 x, I32 y);
		Vector2i& set(const I32 v[2]);
		Vector2i& set(const Vector2& v);
		Vector2i& set(const Vector2i& v);
		
		Vector2i& operator=(const Vector2& v);
		Vector2i& operator=(const Vector2i& v);
		bool operator==(const Vector2i& v) const;
		bool operator!=(const Vector2i& v) const;
		const Vector2i& operator+() const;
		Vector2i operator-() const;
		Vector2i operator*(const Vector2i& v) const;
		Vector2i operator/(const Vector2i& v) const;
		Vector2i operator+(const Vector2i& v) const;
		Vector2i operator-(const Vector2i& v) const;
		Vector2i operator*(I32 s) const;
		Vector2i operator/(I32 s) const;
		Vector2i operator+(I32 s) const;
		Vector2i operator-(I32 s) const;
		Vector2i& operator*=(const Vector2i& v);
		Vector2i& operator/=(const Vector2i& v);
		Vector2i& operator+=(const Vector2i& v);
		Vector2i& operator-=(const Vector2i& v);
		Vector2i& operator*=(I32 s);
		Vector2i& operator/=(I32 s);
		Vector2i& operator+=(I32 s);
		Vector2i& operator-=(I32 s); 
		bool operator<(const Vector2i& vec) const;
		bool operator<=(const Vector2i& vec) const;
		bool operator>(const Vector2i& vec) const;
		bool operator>=(const Vector2i& vec) const;
		operator I32* ();
		operator const I32* () const;

		Vector2& makeZero();
		Vector2& makeOne();
		Vector2& makeAxisX();
		Vector2& makeAxisY();

		Vector2i& minimize(const Vector2i& min);
		Vector2i& maximize(const Vector2i& max);
		
		static const U8 dim();

		static const Vector2i zero();
		static const Vector2i one();
		static const Vector2i axisX();
		static const Vector2i axisY();
		
		I32 x, y;
};

} // namespace oe

#endif // OE_VECTOR2I_HPP
