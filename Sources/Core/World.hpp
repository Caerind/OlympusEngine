#ifndef OE_WORLD_HPP
#define OE_WORLD_HPP

#include "Entity.hpp"
#include "EntityHandle.hpp"
#include "EntityList.hpp"

#include "../System/Singleton.hpp"
#include "../System/Time.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

namespace oe
{

class World : public Singleton<World>
{
	public:
		World();

		static World& getSingleton();
		static World* getSingletonPtr();

		void handleEvent(const sf::Event& event);
		void update(Time dt);
		void update();
		void render(sf::RenderTarget& target);

		EntityHandle createEntity();
		void killEntity(const EntityHandle& handle);
		U32 getEntitiesCount() const; // Spawning & Playing
		U32 getEntitiesPlaying() const; // Playing only

	private:
		U32 getFreeHandleIndex() const;

		void destroyEntities();
		void spawnEntities();

		friend class EntityHandle;
		Entity* getEntityFromHandleIndex(U32 handleIndex) const;

	private:
		static const U32 mMaxEntities = 1024;
		Entity* mEntities[mMaxEntities];
		EntityList mEntitiesSpawning;
		EntityList mEntitiesPlaying;
		EntityList mEntitiesKilled;
};

} // namespace oe

#endif // OE_WORLD_HPP
