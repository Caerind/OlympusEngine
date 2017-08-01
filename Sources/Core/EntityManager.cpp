#include "EntityManager.hpp"
#include "World.hpp"

namespace oe
{

EntityManager::EntityManager(World& world)
	: mWorld(world)
	, mEntities()
	, mEntitiesSpawning()
	, mEntitiesPlaying()
	, mEntitiesKilled()
{
	clear();
}

World& EntityManager::getWorld()
{
	return mWorld;
}

void EntityManager::update()
{
	// Destroy before to free slots
	I32 destroyed = (I32)destroyEntities();
	mEntitiesPlaying.update();
	I32 spawned = (I32)spawnEntities();
	updateQueries();

	I32 change = spawned - destroyed;
}

void EntityManager::update(oe::Time dt)
{
	for (auto itr = mEntitiesPlaying.begin(); itr != mEntitiesPlaying.end(); ++itr)
	{
		ASSERT((*itr).isValid());
		(*itr)->update(dt);
	}
}

void EntityManager::killEntity(const EntityHandle& handle)
{
	if (handle.isValid())
	{
		mEntitiesKilled.insert(handle);
		handle->setState(Entity::Killed);
	}
}

void EntityManager::killEntity(const Entity* entity)
{
	killEntity(getHandleFromEntity(entity));
}

U32 EntityManager::getEntitiesSpawning() const
{
	return mEntitiesSpawning.size();
}

U32 EntityManager::getEntitiesPlaying() const
{
	return mEntitiesPlaying.size();
}

U32 EntityManager::getEntitiesKilled() const
{
	return mEntitiesKilled.size();
}

void EntityManager::addQuery(EntityQuery* query)
{
	if (query != nullptr)
	{
		mQueries.insert(query);
	}
}

void EntityManager::removeQuery(EntityQuery* query)
{
	mQueries.remove(query);
}

void EntityManager::clear()
{
	for (U32 i = 0; i < mMaxEntities; i++)
	{
		// If entity exists remove it properly
		if (mEntities[i] != nullptr)
		{
			// Remove it depending on its current state
			switch (mEntities[i]->getState())
			{
				case Entity::Created:
				case Entity::Playing:
				case Entity::Killed:
					mEntities[i]->destroyComponents();
					mEntities[i]->onDestroy();
					break;
				case Entity::Constructed:
				case Entity::Destroyed: break;
				default: break;
			}

			// Release memory properly
			delete mEntities[i]; // TODO : Allocator
		}

		// Invalidate
		mEntities[i] = nullptr;
	}
}

U32 EntityManager::spawnEntities()
{
	OE_PROFILE_FUNCTION("EntityManager::spawnEntities");
	U32 spawned = 0;
	for (auto itr = mEntitiesSpawning.begin(); itr != mEntitiesSpawning.end(); ++itr)
	{
		Entity* entity = (*itr).get();
		if (entity != nullptr)
		{
			entity->onSpawn();
			entity->spawnComponents();
			entity->setState(Entity::Playing);
			mEntitiesPlaying.insert(*itr);
			spawned++;
		}
	}
	mEntitiesSpawning.clear();
	return spawned;
}

U32 EntityManager::destroyEntities()
{
	OE_PROFILE_FUNCTION("EntityManager::destroyEntities");
	U32 destroyed = 0;
	for (auto itr = mEntitiesKilled.begin(); itr != mEntitiesKilled.end(); itr++)
	{
		Entity* entity = (*itr).get();
		if (entity != nullptr)
		{
			entity->setState(Entity::Destroyed);
			entity->destroyComponents();
			entity->onDestroy();

			U32 index = (*itr).getHandleIndex();
			ASSERT(index < mMaxEntities);

			delete mEntities[index]; // TODO : Allocator
			mEntities[index] = nullptr;

			destroyed++;
		}
	}
	mEntitiesKilled.clear();
	return destroyed;
}

void EntityManager::updateQueries()
{
	OE_PROFILE_FUNCTION("EntityManager::updateQueries");
	for (EntityQuery* query : mQueries)
	{
		ASSERT(query != nullptr);
		query->mEntities.clear();
		query->mUpdated = true; // Not yet, but will be at the end so we can mark it now
	}

	// Doing it like that to avoid casting handle to entity too many times
	for (const EntityHandle& handle : mEntitiesPlaying)
	{
		Entity* entity = handle.get();
		for (EntityQuery* query : mQueries)
		{
			if (query->mSelector(entity))
			{
				query->mEntities.insert(entity);
			}
		}
	}
}

U32 EntityManager::getFreeHandleIndex() const
{
	for (U32 i = 0; i < mMaxEntities; i++)
	{
		if (mEntities[i] == nullptr)
		{
			return i;
		}
	}
	ASSERT(false); // Max entities reached
	return 0;
}

EntityHandle EntityManager::createEntity(Entity* entity)
{
	U32 index = getFreeHandleIndex();

	ASSERT(entity != nullptr);
	ASSERT(index < mMaxEntities);

	mEntities[index] = entity;
	entity->onCreate();
	entity->createComponents();
	entity->setState(Entity::Created);

	EntityHandle handle(this, *entity, index);
	mEntitiesSpawning.insert(handle);
	return handle;
}

Entity* EntityManager::getEntityFromHandleIndex(U32 handleIndex) const
{
	ASSERT(handleIndex < mMaxEntities);
	return mEntities[handleIndex];
}

EntityHandle EntityManager::getHandleFromEntity(const Entity* entity)
{
	for (const EntityHandle& h : mEntitiesPlaying)
	{
		if (h.getEntityId() == entity->getId())
		{
			return h;
		}
	}
	for (const EntityHandle& h : mEntitiesSpawning)
	{
		if (h.getEntityId() == entity->getId())
		{
			return h;
		}
	}
	ASSERT(false); // Not found
	return EntityHandle(); // Invalid handle
}

} // namespace oe
