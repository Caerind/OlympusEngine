#include "Entity.hpp"
#include "World.hpp"
#include "EntityManager.hpp"

namespace oe
{

Entity::Entity(EntityManager& manager)
	: Node()
	, mManager(manager)
	, mId(Id::generate<Entity>())
	, mName(nullptr)
	, mState(Entity::Constructed)
	, mVisible(true)
{
}

Entity::~Entity()
{
}

Application& Entity::getApplication()
{
	return getWorld().getApplication();
}

World& Entity::getWorld()
{
	return mManager.getWorld();
}

EntityManager& Entity::getManager()
{
	return mManager;
}

const UID& Entity::getId() const
{
	return mId;
}

void Entity::setName(char* name)
{
	mName = name;
}

const char* Entity::getName() const
{
	return mName;
}

bool Entity::hasName() const
{
	return mName != nullptr;
}

const Entity::State& Entity::getState() const
{
	return mState;
}

EntityHandle Entity::getHandle() const
{
	return mManager.getHandleFromEntity(this);
}

void Entity::kill() const
{
	mManager.killEntity(this);
}

const ComponentList& Entity::getComponents() const
{
	return mComponents;
}

const SceneComponentList& Entity::getSceneComponents() const
{
	return mSceneComponents;
}

const RenderableComponentList& Entity::getRenderableComponents() const
{
	return mRenderableComponents;
}

const Rect& Entity::getAABB() const
{
	if (!mAABBUpdated)
	{
		updateAABB();
	}
	return mAABB;
}

void Entity::updateAABB() const
{
	bool set = false;
	for (auto itr = mSceneComponents.cbegin(); itr != mSceneComponents.cend(); ++itr)
	{
		Rect aabb = (*itr)->getGlobalAABB();
		if (set)
		{
			mAABB.merge(aabb);
		}
		else
		{
			if (aabb.isValid())
			{
				mAABB = aabb;
				set = true;
			}
		}
	}
	if (!set)
	{
		mAABB = Rect();
	}
	mAABBUpdated = true;
}

void Entity::invalidateAABB()
{
	mAABBUpdated = false;
}

bool Entity::isAABBUpdated() const
{
	return mAABBUpdated;
}

bool Entity::isVisible() const
{
	return mVisible;
}

void Entity::setVisible(bool visible)
{
	mVisible = visible;
}

void Entity::render(sf::RenderTarget& target, const Rect& viewAABB)
{
	if (isVisible())
	{
		if (mNeedOrderComponents)
		{
			mRenderableComponents.sort(Entity::sortComponents);
			mNeedOrderComponents = false;
		}

		for (RenderableComponent* renderable : mRenderableComponents)
		{
			if (renderable->isVisible() && renderable->getGlobalAABB().intersects(viewAABB))
			{
				renderable->render(target);
			}
		}
	}
}

void Entity::update(oe::Time dt)
{
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

void Entity::setState(const Entity::State& state)
{
	mState = state;
}

void Entity::registerComponent(Component* component)
{
	ASSERT(component != nullptr);
	mComponents.insert(component);
}

void Entity::unregisterComponent(Component* component)
{
	ASSERT(component != nullptr);
	mComponents.remove(component);
}

void Entity::registerSceneComponent(SceneComponent* sceneComponent)
{
	ASSERT(sceneComponent != nullptr);
	mSceneComponents.insert(sceneComponent);
	invalidateAABB();
}

void Entity::unregisterSceneComponent(SceneComponent* sceneComponent)
{
	ASSERT(sceneComponent != nullptr);
	mSceneComponents.remove(sceneComponent);
	invalidateAABB();
}

void Entity::registerRenderableComponent(RenderableComponent* renderableComponent)
{
	ASSERT(renderableComponent != nullptr);
	mRenderableComponents.insert(renderableComponent);
	invalidateAABB();
}

void Entity::unregisterRenderableComponent(RenderableComponent* renderableComponent)
{
	ASSERT(renderableComponent != nullptr);
	mRenderableComponents.remove(renderableComponent);
	invalidateAABB();
}

void Entity::invalidateComponentsOrder()
{
	mNeedOrderComponents = true;
}

bool Entity::sortComponents(const RenderableComponent* a, const RenderableComponent* b)
{
	ASSERT(a != nullptr);
	ASSERT(b != nullptr);
	if (Math::equals(a->getGlobalZ(), b->getGlobalZ()))
	{
		return a->getGlobalPosition().y < b->getGlobalPosition().y;
	}
	else
	{
		return a->getGlobalZ() < b->getGlobalZ();
	}
}

} // namespace oe