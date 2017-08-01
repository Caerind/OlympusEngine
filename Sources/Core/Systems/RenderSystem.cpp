#include "RenderSystem.hpp"
#include "../../System/Logger.hpp"
#include "../../Graphics/SFMLWrapper.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include "../World.hpp"

namespace oe
{

RenderSystem::RenderSystem(World& world)
	: mWorld(world)
	, mTexture()
	, mBackgroundColor(Color::Black)
{
	mWorld.getEntityManager().addQuery(&mQuery);
}

RenderSystem::~RenderSystem()
{
	mWorld.getEntityManager().removeQuery(&mQuery);
}

void RenderSystem::clearDebugDraw()
{
	mDebugDraw.clear();
}

void RenderSystem::render(sf::RenderTarget& target)
{
	preRender(target.getSize());
	render();
	postRender(target);
}

View& RenderSystem::getView()
{
	return mView;
}

void RenderSystem::setView(const View& view)
{
	mView = view;
}

void RenderSystem::setBackgroundColor(const Color& color)
{
	mBackgroundColor = color;
}

const Color& RenderSystem::getBackgroundColor() const
{
	return mBackgroundColor;
}

void RenderSystem::setQuerySelector(EntityQuery::Selector selector)
{
	mQuery.setSelector(selector);
}

void RenderSystem::setDebugVisible(bool visible)
{
	mDebugDraw.setVisible(visible);
}

bool RenderSystem::isDebugVisible() const
{
	return mDebugDraw.isVisible();
}

void RenderSystem::preRender(const sf::Vector2u& size)
{
	OE_PROFILE_FUNCTION("RenderSystem::preRender");

	// Resize texture
	if (size != mTexture.getSize())
	{
		if (!mTexture.create(size.x, size.y))
		{
			error("RenderSystem::postRender : Can't create sf::RenderTexture with size(" + toString(size.x) + ", " + toString(size.y) + ")");
		}
	}

	// Order entities
	mQuery.getEntities().sort(RenderSystem::sortEntities);
}

void RenderSystem::render()
{
	OE_PROFILE_FUNCTION("RenderSystem::render");

	mTexture.clear(toSF(mBackgroundColor));

	mTexture.setView(mView.getHandle());
	Rect viewAABB = mView.getBounds();

	for (Entity* entity : mQuery.getEntities())
	{
		if ((entity->isAABBUpdated() && entity->getAABB().intersects(viewAABB)) || !entity->isAABBUpdated())
		{
			entity->render(mTexture, viewAABB);
		}
	}

	mTexture.display();
}

void RenderSystem::postRender(sf::RenderTarget& target)
{
	OE_PROFILE_FUNCTION("RenderSystem::postRender");

	// TODO : Add advanced graphics (Lights/Shaders)

	static sf::Sprite sprite(mTexture.getTexture());

	target.draw(sprite);

	sf::View old = target.getView();
	target.setView(mView.getHandle());
	if (mDebugDraw.isVisible())
	{
		mDebugDraw.render(target);
	}
	target.setView(old);
}

bool RenderSystem::sortEntities(const Entity* a, const Entity* b)
{
	ASSERT(a != nullptr);
	ASSERT(b != nullptr);
	if (Math::equals(a->getPositionZ(), b->getPositionZ()))
	{
		return a->getPosition().y < b->getPosition().y;
	}
	return a->getPositionZ() < b->getPositionZ();
}

} // namespace oe