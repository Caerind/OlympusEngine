#include "ViewComponent.hpp"
#include "../World.hpp"

namespace oe
{

ViewComponent::ViewComponent(Entity& entity, bool attachedToEntity)
	: SceneComponent(entity, attachedToEntity)
{
}

void ViewComponent::onCreate()
{
	mInvalidationSlot.connect(onNodeInvalidation, this, &ViewComponent::onNodeInvalidated);
}

void ViewComponent::onNodeInvalidated(const oe::Node* node)
{
	getWorld().getRenderSystem().getView().setCenter(getGlobalPosition());
}

} // namespace oe
