#include "World.hpp"

namespace oe
{

World::World(Application& application)
	: mApplication(application)
{
	for (U32 i = 0; i < mMaxEntities; i++)
	{
		mEntities[i] = nullptr;
	}

	#ifdef OE_PLATFORM_ANDROID
	mWindowLostFocus.connect(mApplication.getWindow().onWindowLostFocus, [this](const Window* window)
	{
		if (mAudioSystem.getStatus() != sf::SoundSource::Status::Paused)
		{
			mAudioSystem.pause();
		}
	});
	mWindowGainedFocus.connect(mApplication.getWindow().onWindowGainedFocus, [this](const Window* window)
	{
		if (mAudioSystem.getStatus() == sf::SoundSource::Status::Paused)
		{
			mAudioSystem.play();
		}
	});
	#endif

	mRenderSystem.getView().reset(0.0f, 0.0f, mApplication.getWindow().getSize().x, mApplication.getWindow().getSize().y);
}

Application& World::getApplication()
{
	return mApplication;
}

void World::handleEvent(const sf::Event& event)
{
}

void World::update(Time dt)
{
	mRenderSystem.update(dt);
	mAudioSystem.update();
}

void World::update()
{
	// Destroy entities that are killed
	destroyEntities();

	// When killed entities are destroyed, we update the playing list
	// Doing it here is benefic : 
	// - it's only done once, instead of being done in the destroyEntities loop
	// - it's before the spawnEntities so the update loop is faster
	mEntitiesPlaying.update(); // Remove dead entities from the list : do it once here instead of doing it

	// Then we spawn entities
	// Benefic here is that slot might have been freed
	spawnEntities();
}

void World::render(sf::RenderTarget& target)
{
	mRenderSystem.render(target);
}

void World::killEntity(const EntityHandle& handle)
{
	Entity* entity = handle.get();
	if (entity != nullptr)
	{
		mEntitiesKilled.insert(handle);
	}
}

U32 World::getEntitiesCount() const
{
	return mEntitiesSpawning.size() + mEntitiesPlaying.size();
}

U32 World::getEntitiesPlaying() const
{
	return mEntitiesPlaying.size();
}

RenderSystem& World::getRenderSystem()
{
	return mRenderSystem;
}

AudioSystem& World::getAudioSystem()
{
	return mAudioSystem;
}

TextureHolder& World::getTextures()
{
	return mTextures;
}

FontHolder& World::getFonts()
{
	return mFonts;
}

U32 World::getFreeHandleIndex() const
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

EntityHandle World::createEntity(Entity* entity)
{
	U32 index = getFreeHandleIndex();

	ASSERT(entity != nullptr);
	ASSERT(index < mMaxEntities);

	mEntities[index] = entity;
	entity->onCreate();
	entity->createComponents();

	EntityHandle handle(this, *entity, index);
	mEntitiesSpawning.insert(handle);
	return handle;
}

void World::destroyEntities()
{
	for (auto itr = mEntitiesKilled.begin(); itr != mEntitiesKilled.end(); itr++)
	{
		Entity* entity = (*itr).get();
		if (entity != nullptr)
		{
			entity->destroyComponents();
			entity->setPlaying(false);
			entity->onDestroy();

			U32 index = (*itr).getHandleIndex();
			ASSERT(index < mMaxEntities);

			delete mEntities[index]; // TODO : Allocator
			mEntities[index] = nullptr;
		}
	}
	mEntitiesKilled.clear();
}

void World::spawnEntities()
{
	for (auto itr = mEntitiesSpawning.begin(); itr != mEntitiesSpawning.end(); itr++)
	{
		Entity* entity = (*itr).get();
		if (entity != nullptr)
		{
			entity->onSpawn();
			entity->setPlaying(true);
			entity->spawnComponents();
			mEntitiesPlaying.insert(*itr);
		}
	}
	mEntitiesSpawning.clear();
}

Entity* World::getEntityFromHandleIndex(U32 handleIndex) const
{
	ASSERT(handleIndex < mMaxEntities);
	return mEntities[handleIndex];
}

} // namespace oe