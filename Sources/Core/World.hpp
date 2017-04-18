#ifndef OE_WORLD_HPP
#define OE_WORLD_HPP

#include "Application.hpp"

#include "Entity.hpp"
#include "EntityHandle.hpp"
#include "EntityList.hpp"

#include "Systems/RenderSystem.hpp"
#include "Systems/AudioSystem.hpp"
#include "Systems/ActionSystem.hpp"
#include "Systems/TimeSystem.hpp"

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
		World(Application& application);

		Application& getApplication();

		void handleEvent(const sf::Event& event);
		void update(Time dt);
		void update();
		void render(sf::RenderTarget& target);

		const Time& getUpdateTime() const;

		template <typename T = Entity>
		EntityHandle createEntity();
		void killEntity(const EntityHandle& handle);
		void killEntity(const Entity* entity);
		U32 getEntitiesCount() const; // Spawning & Playing
		U32 getEntitiesPlaying() const; // Playing only

		RenderSystem& getRenderSystem();
		AudioSystem& getAudioSystem();
		ActionSystem& getActionSystem();
		TimeSystem& getTimeSystem();

		TextureHolder& getTextures();
		FontHolder& getFonts();

		void play();
		void pause();
		void stop();
		bool isPlaying() const;

		void clear();

	private:
		U32 getFreeHandleIndex() const;
		EntityHandle createEntity(Entity* entity);

		void destroyEntities();
		void spawnEntities();

		friend class EntityHandle;
		Entity* getEntityFromHandleIndex(U32 handleIndex) const;

	private:
		static const U32 mMaxEntities = 1024;

		OeSlot(oe::Window, onWindowLostFocus, mWindowLostFocus);
		OeSlot(oe::Window, onWindowGainedFocus, mWindowGainedFocus);

	private:
		Application& mApplication;
		Entity* mEntities[mMaxEntities];
		EntityList mEntitiesSpawning;
		EntityList mEntitiesPlaying;
		EntityList mEntitiesKilled;

		bool mPlaying;
		Time mUpdateTime;

		RenderSystem mRenderSystem;
		AudioSystem mAudioSystem;
		ActionSystem mActionSystem;
		TimeSystem mTimeSystem;

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
