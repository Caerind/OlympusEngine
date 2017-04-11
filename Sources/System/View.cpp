#include "View.hpp"

namespace oe
{

View::View()
	: mView(sf::FloatRect(0.0f, 0.0f, 0.0f, 0.0f))
	, mZoomFactor(1.0f)
{
}

View::View(F32 x, F32 y, F32 w, F32 h)
	: mView(sf::FloatRect(x, y, w, h))
	, mZoomFactor(1.0f)
{
}

View::View(const Vector2& center, const Vector2& size)
	: mView(toSF(center), toSF(size))
	, mZoomFactor(1.0f)
{
}

View::View(const sf::View& view)
{
	setHandle(view);
}

void View::setCenter(F32 x, F32 y)
{
	mView.setCenter(x, y);
}

void View::setCenter(const Vector2& center)
{
	mView.setCenter(center.x, center.y);
}

Vector2 View::getCenter() const
{
	return toOE(mView.getCenter());
}

void View::setSize(F32 w, F32 h)
{
	mView.setSize(w, h);
}

void View::setSize(const Vector2& size)
{
	mView.setSize(size.x, size.y);
}

Vector2 View::getSize() const
{
	return toOE(mView.getSize());
}

void View::setZoom(F32 factor)
{
	F32 x = factor / mZoomFactor;
	mZoomFactor *= x;
	mView.zoom(x);
}

F32 View::getZoom() const
{
	return mZoomFactor;
}

void View::move(F32 x, F32 y)
{
	mView.move(x, y);
}

void View::move(const Vector2& offset)
{
	mView.move(offset.x, offset.y);
}

void View::zoom(F32 factor)
{
	mZoomFactor *= factor;
	mView.zoom(factor);
}

void View::reset(F32 x, F32 y, F32 w, F32 h)
{
	mView.reset(sf::FloatRect(x, y, w, h));
}

sf::FloatRect View::getBounds() const
{
	return sf::FloatRect(mView.getCenter() - mView.getSize() * 0.5f, mView.getSize());
}

const sf::View& View::getHandle() const
{
	return mView;
}

void View::setHandle(const sf::View& view)
{
	mView = view;
	mZoomFactor = 1.0f;
}

} // namespace oe
