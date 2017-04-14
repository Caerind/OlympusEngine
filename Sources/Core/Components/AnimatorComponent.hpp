#ifndef OE_ANIMATORCOMPONENT_HPP
#define OE_ANIMATORCOMPONENT_HPP

#include "../../System/Animation.hpp"
#include "../../System/List.hpp"
#include "SpriteComponent.hpp"

namespace oe
{

class AnimatorComponent : public SpriteComponent
{
	public:
		AnimatorComponent(Entity& entity);

		bool isPlaying() const;
		bool isPlaying(Animation* animation) const;
		void play(Animation* animation);
		void stop();

		Time getElapsedTime() const;
		void setElapsedTime(Time elapsed);


		void update(Time dt);

		virtual void onSpawn(); // override RenderableComponent::onSpawn to register as AnimatorComponent
		virtual void onDestroy(); // override RenderableComponent::onDestrop to unregister as AnimatorComponent

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
