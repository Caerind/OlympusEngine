#ifndef OE_RECT_HPP
#define OE_RECT_HPP

#include "../Math/Vector2.hpp"

namespace oe
{

class Rect
{
	public:
		Rect();
		Rect(const Vector2& min, const Vector2& max);
		Rect(F32 x, F32 y, F32 w, F32 h);

		Rect& set(const Vector2& min, const Vector2& max);
		Rect& set(F32 x, F32 y, F32 w, F32 h);

		Vector2 getMin() const;
		Vector2 getMax() const;

		Vector2 getCenter() const;
		Rect& setCenter(const Vector2& center);
		Rect& setCenter(F32 x, F32 y);

		Vector2 getSize() const;
		Rect& setSize(const Vector2& size);
		Rect& setSize(F32 width, F32 height);

		F32 getArea() const;

		bool isValid() const;

		Vector2 getCorner(U32 index); // 0 = Min, 2 = Max, Clock-wise

		Rect& merge(const Vector2& point);
		Rect& merge(const Rect& rect);

		bool intersects(const Vector2& point) const;
		bool intersects(const Rect& rect) const;

		Rect intersection(const Rect& rect) const;

		bool contains(const Rect& rect) const; // rect is inside this

		bool operator==(const Rect& rect) const;
		bool operator!=(const Rect& rect) const;
		
		F32 x, y, w, h;
};

template <>
inline std::string toString<Rect>(const Rect& r)
{
	std::ostringstream oss;
	oss << toString<F32>(r.x) << ',' << toString<F32>(r.y) << ',' << toString<F32>(r.w) << ',' << toString<F32>(r.h);
	return oss.str();
}

template <>
inline Rect fromString<Rect>(const std::string& string)
{
	std::string str(string);
	Rect rect;
	rect.x = fromString<F32>(split(str, ','));
	rect.y = fromString<F32>(split(str, ','));
	rect.w = fromString<F32>(split(str, ','));
	rect.h = fromString<F32>(str);
	return rect;
}

} // namespace oe

#endif // OE_RECT_HPP
