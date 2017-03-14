#include "Entity.hpp"
#include "World.hpp"

namespace oe
{

Entity::Entity(World& world)
	: mWorld(world)
	, mId(Id::generate<Entity>())
{
}

World& Entity::getWorld()
{
	return mWorld;
}

UID Entity::getId() const
{
	return mId;
}

void Entity::onCreate()
{
}

void Entity::onSpawn()
{
}

void Entity::onKill()
{
}

void Entity::onDestroy()
{
}

void Entity::update(Time dt)
{
}

void Entity::kill()
{
}

} // namespace oe