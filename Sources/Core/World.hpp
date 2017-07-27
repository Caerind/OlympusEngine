#ifndef OE_WORLD_HPP
#define OE_WORLD_HPP

#include "../Application/Application.hpp"
#include "../System/Signal.hpp"

#include "EntityManager.hpp"
#include "Systems/RenderSystem.hpp"
#include "Systems/ActionSystem.hpp"
#include "Systems/TimeSystem.hpp"
#include "Systems/ParticleSystem.hpp"
#include "Systems/AnimationSystem.hpp"

namespace oe
{

class World
{
	public:
		World(Application& application);

		Application& getApplication();
		TextureManager& getTextures();
		FontManager& getFonts();

		void handleEvent(const sf::Event& event);
		void update(Time dt);
		void render(sf::RenderTarget& target);

		void play();
		void pause();
		bool isPlaying() const;
		OeSignal(onWorldPlay, const World*);
		OeSignal(onWorldPause, const World*);

		void clear();

		EntityManager& getEntityManager();
		RenderSystem& getRenderSystem();
		ActionSystem& getActionSystem();
		TimeSystem& getTimeSystem();
		ParticleSystem& getParticleSystem();
		AnimationSystem& getAnimationSystem();

		const Time& getUpdateTime() const;

	private:
		Application& mApplication;

		bool mPlaying;
		Time mUpdateTime;

		TextureManager mTextures;
		FontManager mFonts;

		EntityManager mEntityManager;
		RenderSystem mRenderSystem;
		ActionSystem mActionSystem;
		TimeSystem mTimeSystem;
		ParticleSystem mParticleSystem;
		AnimationSystem mAnimationSystem;
};

} // namespace oe

#endif // OE_WORLD_HPP
