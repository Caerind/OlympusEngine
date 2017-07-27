#include "Rect.hpp"
#include <algorithm> // std::min, std::max

namespace oe
{

Rect::Rect()
{
	set(0.0f, 0.0f, 0.0f, 0.0f);
}

Rect::Rect(const Vector2& min, const Vector2& max)
{
	set(min, max);
}

Rect::Rect(F32 x, F32 y, F32 w, F32 h)
{
	set(x, y, w, h);
}

Rect& Rect::set(const Vector2& min, const Vector2& max)
{
	x = min.x;
	y = min.y;
	w = max.x - min.x;
	h = max.y - min.y;
	return *this;
}

Rect& Rect::set(F32 x, F32 y, F32 w, F32 h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	return *this;
}

Vector2 Rect::getMin() const
{
	return Vector2(x, y);
}

Vector2 Rect::getMax() const
{
	return Vector2(w + x, h + y);
}

Vector2 Rect::getCenter() const
{
	return Vector2(x + w * 0.5f, y + h * 0.5f);
}

Rect& Rect::setCenter(const Vector2& center)
{
	x = center.x - w * 0.5f;
	y = center.y - h * 0.5f;
	return *this;
}

Rect& Rect::setCenter(F32 x, F32 y)
{
	return setCenter(Vector2(x, y));
}

Vector2 Rect::getSize() const
{
	return Vector2(w, h);
}

Rect& Rect::setSize(const Vector2& size)
{
	w = size.x;
	h = size.y;
	return *this;
}

Rect& Rect::setSize(F32 width, F32 height)
{
	return setSize(Vector2(width, height));
}

F32 Rect::getArea() const
{
	return w * h;
}

bool Rect::isValid() const
{
	return (*this) != Rect();
}

Vector2 Rect::getCorner(U32 index)
{
	switch (index)
	{
		case 0: return getMin();
		case 1: return Vector2(x + w, y);
		case 2: return getMax();
		case 3: return Vector2(x, y + h);
		default: return Vector2();
	}
}

Rect& Rect::merge(const Vector2& point)
{
	return set(getMin().minimize(point), getMax().maximize(point));
}

Rect& Rect::merge(const Rect& rect)
{
	return set(getMin().minimize(rect.getMin()), getMax().maximize(rect.getMax()));
}

bool Rect::intersects(const Vector2& point) const
{
	return Math::inRange(point.x, x, x + w) && Math::inRange(point.y, y, y + h);
}

bool Rect::intersects(const Rect& rect) const
{
	F32 interLeft = std::max(std::min(x, x + w), std::min(rect.x, rect.x + rect.w));
	F32 interTop = std::max(std::min(y, y + h), std::min(rect.y, rect.y + rect.h));
	F32 interRight = std::min(std::max(x, x + w), std::max(rect.x, rect.x + rect.w));
	F32 interBottom = std::min(std::max(y, y + h), std::max(rect.y, rect.y + rect.h));
	return ((interLeft < interRight) && (interTop < interBottom));
}

Rect Rect::intersection(const Rect& rect) const
{
	F32 interLeft = std::max(std::min(x, x + w), std::min(rect.x, rect.x + rect.w));
	F32 interTop = std::max(std::min(y, y + h), std::min(rect.y, rect.y + rect.h));
	F32 interRight = std::min(std::max(x, x + w), std::max(rect.x, rect.x + rect.w));
	F32 interBottom = std::min(std::max(y, y + h), std::max(rect.y, rect.y + rect.h));
	if ((interLeft < interRight) && (interTop < interBottom))
	{
		return Rect(interLeft, interTop, interRight - interLeft, interBottom - interTop);
	}
	else
	{
		return Rect();
	}
}

bool Rect::contains(const Rect& rect) const
{
	return x <= rect.x && y <= rect.y && rect.w <= w && rect.h <= h;
}

bool Rect::operator==(const Rect& rect) const
{
	return Math::equals(x, rect.x) && Math::equals(y, rect.y) && Math::equals(w, rect.w) && Math::equals(h, rect.h);
}

bool Rect::operator!=(const Rect& rect) const
{
	return !operator==(rect);
}

} // namespace oe