#include "DebugDraw.hpp"
#include "SFML.hpp"

namespace oe
{

template<> DebugDraw* Singleton<DebugDraw>::mSingleton = nullptr;

DebugDraw::DebugDraw()
{
}

DebugDraw& DebugDraw::getSingleton()
{
	ASSERT(mSingleton != nullptr);
	return *mSingleton;
}

DebugDraw* DebugDraw::getSingletonPtr()
{
	return mSingleton;
}

bool DebugDraw::instanced()
{
	return mSingleton != nullptr;
}

void DebugDraw::clear()
{
	if (instanced())
	{
		U32 size = mSingleton->mDrawables.size();
		for (U32 i = 0; i < size; i++)
		{
			delete mSingleton->mDrawables[i];
			mSingleton->mDrawables[i] = nullptr;
		}
		mSingleton->mDrawables.clear();
	}
}

void DebugDraw::drawPoint(F32 x, F32 y, const Color& color, F32 r)
{
	if (instanced())
	{
		sf::CircleShape* point = new sf::CircleShape(r);
		point->setFillColor(toSF(color));
		point->setPosition(x - r * 0.5f, y - r * 0.5f);
		mSingleton->mDrawables.push_back(point);
	}
}

void DebugDraw::drawRect(F32 x, F32 y, F32 w, F32 h, const Color& c1, const Color& c2)
{
	if (instanced())
	{
		sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f(w, h));
		rect->setFillColor(toSF(c1));
		rect->setOutlineThickness(1.5f);
		rect->setOutlineColor(toSF(c2));
		rect->setPosition(x, y);
		mSingleton->mDrawables.push_back(rect);
	}
}

void DebugDraw::render(sf::RenderTarget& target)
{
	if (instanced())
	{
		U32 size = mSingleton->mDrawables.size();
		for (U32 i = 0; i < size; i++)
		{
			target.draw(*mSingleton->mDrawables[i]);
		}
	}
}

} // namespace oe