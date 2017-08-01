#include "World.hpp"

namespace oe
{

World::World(Application& application)
	: mApplication(application)
	, mPlaying(false)
	, mUpdateTime(Time::Zero)
	, mTextures(application.getTextures(), TextureManager::Child)
	, mFonts(application.getFonts(), FontManager::Child)
	, mEntityManager(*this)
	, mRenderSystem(*this)
{
}

Application& World::getApplication()
{
	return mApplication;
}

TextureManager& World::getTextures()
{
	return mTextures;
}

FontManager& World::getFonts()
{
	return mFonts;
}

void World::handleEvent(const sf::Event& event)
{
	OE_PROFILE_FUNCTION("World::handleEvent");

	mActionSystem.addEvent(event);
}

void World::update(Time dt)
{
	OE_PROFILE_FUNCTION("World::update");

	mRenderSystem.clearDebugDraw(); // Clear DebugDraw
	mEntityManager.update(); // Will add/remove entities

	if (isPlaying())
	{
		// Apply speed factor
		mUpdateTime = dt * mTimeSystem.getSpeedFactor();

		// Update input from the user
		mActionSystem.update();

		// Update timers
		mTimeSystem.update(mUpdateTime);

		// Update entities
		mEntityManager.update(mUpdateTime);

		// Update particles
		mParticleSystem.update(mUpdateTime);

		// Update animatioons
		mAnimationSystem.update(mUpdateTime);
	}
}

void World::render(sf::RenderTarget& target)
{
	OE_PROFILE_FUNCTION("World::render");

	mRenderSystem.render(target);
}

void World::play()
{
	mPlaying = true;
	onWorldPlay(this);
}

void World::pause()
{
	mPlaying = false;
	onWorldPause(this);
}

bool World::isPlaying() const
{
	return mPlaying;
}

void World::clear()
{

}

EntityManager& World::getEntityManager()
{
	return mEntityManager;
}

RenderSystem& World::getRenderSystem()
{
	return mRenderSystem;
}

ActionSystem& World::getActionSystem()
{
	return mActionSystem;
}

TimeSystem& World::getTimeSystem()
{
	return mTimeSystem;
}

ParticleSystem& World::getParticleSystem()
{
	return mParticleSystem;
}

AnimationSystem& World::getAnimationSystem()
{
	return mAnimationSystem;
}

const Time& World::getUpdateTime() const
{
	return mUpdateTime;
}

} // namespace oe