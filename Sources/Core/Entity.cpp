#include "Entity.hpp"
#include "World.hpp"

namespace oe
{

Entity::Entity(World& world)
	: mWorld(world)
	, mId(Id::generate<Entity>())
	, mComponents()
	, mSceneComponents()
{
}

Entity::~Entity()
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

void Entity::createComponents()
{
	for (auto itr = mComponents.begin(); itr != mComponents.end(); ++itr)
	{
		(*itr)->onCreate();
	}
}

void Entity::onSpawn()
{
}

void Entity::spawnComponents()
{
	for (auto itr = mComponents.begin(); itr != mComponents.end(); ++itr)
	{
		(*itr)->onSpawn();
	}
}

void Entity::onDestroy()
{
}

void Entity::destroyComponents()
{
	for (auto itr = mComponents.begin(); itr != mComponents.end(); ++itr)
	{
		(*itr)->onDestroy();
	}
}

void Entity::update(Time dt)
{
}

void Entity::registerComponent(Component* component)
{
	ASSERT(component != nullptr);
	if (mComponents.insert(component))
	{
		SceneComponent* sc = fast_dynamic_cast<SceneComponent*>(component);
		if (sc != nullptr)
		{
			mSceneComponents.insert(sc);
		}
	}
}

void Entity::unregisterComponent(Component* component)
{
	ASSERT(component != nullptr);
	if (mComponents.remove(component))
	{
		SceneComponent* sc = fast_dynamic_cast<SceneComponent*>(component);
		if (sc != nullptr)
		{
			mSceneComponents.remove(sc);
		}
	}
}

const ComponentList& Entity::getComponents() const
{
	return mComponents;
}

const SceneComponentList& Entity::getSceneComponents() const
{
	return mSceneComponents;
}

} // namespace oe