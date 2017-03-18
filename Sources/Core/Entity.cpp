#include "Entity.hpp"
#include "World.hpp"

namespace oe
{

Entity::Entity(World& world)
	: mWorld(world)
	, mId(Id::generate<Entity>())
{
}

Entity::~Entity()
{
	clearComponents();
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

void Entity::attachComponent(Component* component)
{
	if (component != nullptr && !component->hasParent())
	{
		if (mComponents.insert(component))
		{
			component->setParent(this);
			component->onAttach();

			SceneComponent* sc = fast_dynamic_cast<SceneComponent*>(component);
			if (sc != nullptr)
			{
				mSceneComponents.insert(sc);
			}
		}
	}
}

void Entity::detachComponent(Component* component)
{
	if (component != nullptr && component->hasParent())
	{
		if (mComponents.remove(component))
		{
			SceneComponent* sc = fast_dynamic_cast<SceneComponent*>(component);
			if (sc != nullptr)
			{
				mSceneComponents.remove(sc);
			}

			component->onDetach();
			component->setParent(nullptr);
		}
	}
}

void Entity::clearComponents()
{
	mSceneComponents.clear();
	for (auto itr = mComponents.begin(); itr != mComponents.end(); ++itr)
	{
		(*itr)->onDetach();
		(*itr)->setParent(nullptr);
	}
	mComponents.clear();
}

const ComponentList& Entity::getComponents() const
{
	return mComponents;
}

const ComponentList& Entity::getSceneComponents() const
{
	return mSceneComponents;
}

} // namespace oe