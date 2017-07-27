#ifndef OE_ENTITYMANAGER_HPP
#define OE_ENTITYMANAGER_HPP

#include "Entity.hpp"
#include "EntityList.hpp"
#include "EntityHandle.hpp"
#include "EntityQuery.hpp"

namespace oe
{

class World;
class EntityManager
{
	public:
		EntityManager(World& world);

		World& getWorld();

		void update();

		template <typename T = Entity>
		EntityHandle createEntity();

		void killEntity(const EntityHandle& handle);
		void killEntity(const Entity* entity);

		U32 getEntitiesSpawning() const; // Spawning only
		U32 getEntitiesPlaying() const; // Playing only
		U32 getEntitiesKilled() const; // Destroying only

		void addQuery(EntityQuery* query);
		void removeQuery(EntityQuery* query);

		void clear();

	private:
		U32 spawnEntities();
		U32 destroyEntities();
		void updateQueries();

		U32 getFreeHandleIndex() const;
		EntityHandle createEntity(Entity* entity);

	private:
		friend class EntityHandle;
		Entity* getEntityFromHandleIndex(U32 handleIndex) const;

	private:
		friend class Entity;
		EntityHandle getHandleFromEntity(const Entity* entity);

	private:
		static const U32 mMaxEntities = 1024;

	private:
		World& mWorld;
		Entity* mEntities[mMaxEntities];
		EntityList mEntitiesSpawning;
		EntityList mEntitiesPlaying;
		EntityList mEntitiesKilled;
		List<EntityQuery*> mQueries;
};

template <typename T>
EntityHandle EntityManager::createEntity()
{
	Entity* entity = new T(*this); // TODO : Allocator
	return createEntity(entity);
}

} // namespace oe

#endif // OE_ENTITYMANAGER_HPP
