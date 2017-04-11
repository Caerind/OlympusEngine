#include "RenderableComponent.hpp"
#include "Systems/RenderSystem.hpp"
#include "World.hpp"

namespace oe
{

RenderableComponent::RenderableComponent(Entity* entity)
	: SceneComponent(entity)
	, mLocalAABB()
	, mGlobalAABB()
	, mGlobalAABBUpdated(false)
	, mVisible(true)
{
}

void RenderableComponent::render(sf::RenderTarget& target)
{
}

const sf::FloatRect& RenderableComponent::getLocalAABB() const
{
	return mLocalAABB;
}

const sf::FloatRect& RenderableComponent::getGlobalAABB() const
{
	if (!mGlobalAABBUpdated)
	{
		mGlobalAABB = getGlobalTransform().transformRect(mLocalAABB);
		mGlobalAABBUpdated = true;
	}
	return mGlobalAABB;
}

bool RenderableComponent::isVisible() const
{
	return mVisible;
}

void RenderableComponent::setVisible(bool visible)
{
	mVisible = visible;
}

RenderSystem& RenderableComponent::getRenderSystem()
{
	return getWorld().getRenderSystem();
}

void RenderableComponent::onCreate()
{
	mInvalidationSlot.connect(onNodeInvalidation, this, &RenderableComponent::onNodeInvalidated);
	mInvalidationZSlot.connect(onNodeInvalidationZ, this, &RenderableComponent::onNodeInvalidatedZ);
}

void RenderableComponent::onSpawn()
{
	getRenderSystem().registerRenderable(this);
}

void RenderableComponent::onDestroy()
{
	getRenderSystem().unregisterRenderable(this);
}

void RenderableComponent::onNodeInvalidated(const Node* node)
{
	getRenderSystem().needUpdateOrderY();
	mGlobalAABBUpdated = false;
}

void RenderableComponent::onNodeInvalidatedZ(const Node* node)
{
	getRenderSystem().needUpdateOrderZ();
}

} // namespace oe