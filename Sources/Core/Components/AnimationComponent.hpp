#ifndef OE_ANIMATIONCOMPONENT_HPP
#define OE_ANIMATIONCOMPONENT_HPP

#include "../../Graphics/Animation.hpp"
#include "SpriteComponent.hpp"

namespace oe
{

class AnimationComponent : public SpriteComponent
{
	public:
		AnimationComponent(Entity& entity, bool attachedToEntity = true);

		bool isPlaying() const;
		bool isPlaying(Animation* animation) const;
		void play(Animation* animation);
		void stop();

		Time getElapsedTime() const;
		void setElapsedTime(Time elapsed);

		void update(Time dt);

		virtual void onSpawn(); // register to the AnimationSystem
		virtual void onDestroy(); // unregister to the AnimationSystem

	private:
		void applyFrame(U32 frameIndex);
		void nextFrame();

		void setTexture(ResourceId texture) {}
		void setTexture(sf::Texture& texture) {}
		const sf::Texture* getTexture() const { return mSprite.getTexture(); }

		void setTextureRect(const sf::IntRect& textureRect) {}
		const sf::IntRect& getTextureRect() const { return mSprite.getTextureRect(); }

	private:
		bool mPlaying;
		Animation* mAnimation;
		U32 mFrame;
		ResourceId mTexture;
		Time mTimeElapsed;
};

} // namespace oe

#endif // OE_ANIMATIORCOMPONENT_HPP
