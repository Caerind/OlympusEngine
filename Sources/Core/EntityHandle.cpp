#include "EntityHandle.hpp"
#include "EntityManager.hpp"

namespace oe
{

EntityHandle::EntityHandle()
	: mManager(nullptr)
	, mEntityId(0)
	, mHandleIndex(0)
{
}

EntityHandle::EntityHandle(EntityManager* manager, const Entity& entity, U32 handleIndex)
	: mManager(manager)
	, mEntityId(entity.getId())
	, mHandleIndex(handleIndex)
{
}

EntityHandle::EntityHandle(const EntityHandle& handle)
	: mManager(handle.mManager)
	, mEntityId(handle.mEntityId)
    , mHandleIndex(handle.mHandleIndex)
{
}

void EntityHandle::operator=(const EntityHandle& handle)
{
	mManager = handle.mManager;
	mEntityId = handle.mEntityId;
	mHandleIndex = handle.mHandleIndex;
}

Entity* EntityHandle::get() const
{
	if (mManager == nullptr)
	{
		return nullptr;
	}
	Entity* entity = mManager->getEntityFromHandleIndex(mHandleIndex);
	if (entity != nullptr && entity->getId() == mEntityId)
	{
		return entity;
	}
	return nullptr;
}

Entity* EntityHandle::operator->() const
{
	return get();
}

bool EntityHandle::isValid() const
{
	if (mEntityId == 0 || mManager == nullptr)
	{
		return false;
	}
	Entity* entity = mManager->getEntityFromHandleIndex(mHandleIndex);
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

void EntityHandle::invalidate()
{
	mEntityId = 0;
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