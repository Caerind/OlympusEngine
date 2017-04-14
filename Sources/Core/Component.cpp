#include "Component.hpp"
#include "Entity.hpp"
#include "World.hpp"

namespace oe
{

Component::Component(Entity& entity)
	: mEntity(entity)
{
	registerComponent();
}

void Component::onCreate()
{
}

void Component::onSpawn()
{
}

void Component::onDestroy()
{
}

Entity& Component::getEntity()
{
	return mEntity;
}

World& Component::getWorld()
{
	return mEntity.getWorld();
}

void Component::registerComponent()
{
	mEntity.registerComponent(this);
}

void Component::unregisterComponent()
{
	mEntity.unregisterComponent(this);
}

} // namespace oe