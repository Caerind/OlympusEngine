#include "SceneComponent.hpp"
#include "Entity.hpp"

namespace oe
{

SceneComponent::SceneComponent(Entity& entity, bool attachToEntity)
	: Component(entity)
	, Node()
{
	mEntity.registerSceneComponent(this);
	if (attachToEntity)
	{
		entity.attach(this);
	}
}

SceneComponent::~SceneComponent()
{
}

const Rect& SceneComponent::getLocalAABB() const
{
	return mLocalAABB;
}

const Rect& SceneComponent::getGlobalAABB() const
{
	if (!mGlobalAABBUpdated)
	{
		mGlobalAABB = toOE(getGlobalTransform().transformRect(toSF(mLocalAABB)));
		mGlobalAABBUpdated = true;
	}
	return mGlobalAABB;
}

void SceneComponent::onCreate()
{
	mSceneComponentInvalidationSlot.connect(onNodeInvalidation, this, &SceneComponent::onSceneComponentInvalidated);
}

void SceneComponent::setLocalAABB(const Rect& rect)
{
	mLocalAABB = rect;
	invalidateGlobalAABB();
}

void SceneComponent::invalidateGlobalAABB()
{
	mGlobalAABBUpdated = false;
	mEntity.invalidateAABB();
}

void SceneComponent::onSceneComponentInvalidated(const Node* node)
{
	invalidateGlobalAABB();
}

void SceneComponent::registerComponent()
{
	Component::registerComponent();
	mEntity.registerSceneComponent(this);
}

void SceneComponent::unregisterComponent()
{
	mEntity.unregisterSceneComponent(this);
	Component::unregisterComponent();
}

} // namespace oe