#include "EntityHandle.hpp"
#include "World.hpp"

namespace oe
{

EntityHandle::EntityHandle()
	: mEntityId(0)
	, mHandleIndex(0)
	, mWorld(nullptr)
{
}

EntityHandle::EntityHandle(World* world, const Entity& entity, U32 handleIndex)
	: mEntityId(entity.getId())
	, mHandleIndex(handleIndex)
	, mWorld(world)
{
}

EntityHandle::EntityHandle(const EntityHandle& handle)
	: mEntityId(handle.mEntityId)
    , mHandleIndex(handle.mHandleIndex)
	, mWorld(handle.mWorld)
{
}

void EntityHandle::operator=(const EntityHandle& handle)
{
	mEntityId = handle.mEntityId;
	mHandleIndex = handle.mHandleIndex;
	mWorld = handle.mWorld;
}

Entity* EntityHandle::get() const
{
	ASSERT(mWorld != nullptr);
	Entity* entity = mWorld->getEntityFromHandleIndex(mHandleIndex);
	if (entity != nullptr && entity->getId() == mEntityId)
	{
		return entity;
	}
	return nullptr;
}

bool EntityHandle::isValid() const
{
	if (mEntityId == 0)
	{
		return false;
	}
	ASSERT(mWorld != nullptr);
	Entity* entity = mWorld->getEntityFromHandleIndex(mHandleIndex);
	return entity != nullptr && entity->getId() == mEntityId;
}

bool EntityHandle::operator==(const EntityHandle& handle) const
{
	return mEntityId == handle.mEntityId;
}

bool EntityHandle::operator!=(const EntityHandle& handle) const
{
	return mEntityId != handle.mEntityId;
}

UID EntityHandle::getEntityId() const
{
	return mEntityId;
}

U32 EntityHandle::getHandleIndex() const
{
	return mHandleIndex;
}

} // namespace oe