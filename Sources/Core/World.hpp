#ifndef OE_WORLD_HPP
#define OE_WORLD_HPP

#include "Entity.hpp"
#include "EntityHandle.hpp"
#include "EntityList.hpp"

#include "Systems/RenderSystem.hpp"
#include "Systems/AudioSystem.hpp"

#include "../System/ResourceHolder.hpp"
#include "../System/SFMLResources.hpp"
#include "../System/Time.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

namespace oe
{

class World
{
	public:
		World();

		void handleEvent(const sf::Event& event);
		void update(Time dt);
		void update();
		void render(sf::RenderTarget& target);

		template <typename T = Entity>
		EntityHandle createEntity();
		void killEntity(const EntityHandle& handle);
		U32 getEntitiesCount() const; // Spawning & Playing
		U32 getEntitiesPlaying() const; // Playing only

		RenderSystem& getRenderSystem();
		AudioSystem& getAudioSystem();

		TextureHolder& getTextures();
		FontHolder& getFonts();

	private:
		U32 getFreeHandleIndex() const;
		EntityHandle createEntity(Entity* entity);

		void destroyEntities();
		void spawnEntities();

		friend class EntityHandle;
		Entity* getEntityFromHandleIndex(U32 handleIndex) const;

	private:
		static const U32 mMaxEntities = 1024;

	private:
		Entity* mEntities[mMaxEntities];
		EntityList mEntitiesSpawning;
		EntityList mEntitiesPlaying;
		EntityList mEntitiesKilled;

		RenderSystem mRenderSystem;
		AudioSystem mAudioSystem;

		TextureHolder mTextures;
		FontHolder mFonts;
};

template <typename T>
EntityHandle World::createEntity()
{
	Entity* entity = new T(*this); // TODO : Allocator
	return createEntity(entity);
}

} // namespace oe

#endif // OE_WORLD_HPP
