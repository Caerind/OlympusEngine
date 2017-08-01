#include "ViewComponent.hpp"
#include "../World.hpp"

namespace oe
{

ViewComponent::ViewComponent(Entity& entity, bool attachedToEntity, bool focus)
	: SceneComponent(entity, attachedToEntity)
	, mFocusing(focus)
{
}

void ViewComponent::onCreate()
{
	mInvalidationSlot.connect(onNodeInvalidation, this, &ViewComponent::onNodeInvalidated);
}

void ViewComponent::onNodeInvalidated(const oe::Node* node)
{
	if (mFocusing)
	{
		getWorld().getRenderSystem().getView().setCenter(getGlobalPosition());
	}
}

void ViewComponent::setFocus(bool focus)
{
	mFocusing = focus;
}

bool ViewComponent::isFocusing() const
{
	return mFocusing;
}

} // namespace oe
