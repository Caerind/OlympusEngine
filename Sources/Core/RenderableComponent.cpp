#include "RenderableComponent.hpp"
#include "Systems/RenderSystem.hpp"
#include "World.hpp"
#include "Entity.hpp"

namespace oe
{

RenderableComponent::RenderableComponent(Entity& entity, bool attachedToEntity)
	: SceneComponent(entity, attachedToEntity)
	, mVisible(true)
{
	mEntity.registerRenderableComponent(this);
}

void RenderableComponent::render(sf::RenderTarget& target)
{
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
	SceneComponent::onCreate();
	mRenderableComponentInvalidationSlot.connect(onNodeInvalidation, this, &RenderableComponent::onRenderableComponentInvalidated);
	mRenderableComponentInvalidationZSlot.connect(onNodeInvalidationZ, this, &RenderableComponent::onRenderableComponentInvalidatedZ);
}

void RenderableComponent::onRenderableComponentInvalidated(const Node* node)
{
	mEntity.invalidateComponentsOrder();
}

void RenderableComponent::onRenderableComponentInvalidatedZ(const Node* node)
{
	mEntity.invalidateComponentsOrder();
}

void RenderableComponent::registerComponent()
{
	SceneComponent::registerComponent();
	mEntity.registerRenderableComponent(this);
}

void RenderableComponent::unregisterComponent()
{
	mEntity.unregisterRenderableComponent(this);
	SceneComponent::unregisterComponent();
}

} // namespace oe