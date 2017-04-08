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
	onNodeInvalidation.connect([this](const Node* node)
	{
		getRenderSystem().needUpdateOrderY();
		mGlobalAABBUpdated = false;
	});
	onNodeInvalidationZ.connect([this](const Node* node)
	{
		getRenderSystem().needUpdateOrderZ();
	});
}

RenderableComponent::~RenderableComponent()
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

} // namespace oe