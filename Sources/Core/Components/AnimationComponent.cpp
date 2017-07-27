#include "AnimationComponent.hpp"
#include "../World.hpp"

namespace oe
{

AnimationComponent::AnimationComponent(Entity& entity, bool attachedToEntity)
	: SpriteComponent(entity, attachedToEntity)
	, mPlaying(false)
	, mAnimation(nullptr)
	, mFrame(0)
	, mTexture(0)
	, mTimeElapsed()
{
}

bool AnimationComponent::isPlaying() const
{
	return mPlaying;
}

bool AnimationComponent::isPlaying(Animation* animation) const
{
	return mPlaying && mAnimation == animation;
}

void AnimationComponent::play(Animation* animation)
{
	mAnimation = animation;
	mTimeElapsed = Time::Zero;
	if (mAnimation != nullptr)
	{
		applyFrame(0);
		mPlaying = true;
	}
}

void AnimationComponent::stop()
{
	mPlaying = false;
}

Time AnimationComponent::getElapsedTime() const
{
	return mTimeElapsed;
}

void AnimationComponent::setElapsedTime(Time elapsed)
{
	mTimeElapsed = elapsed;
	Time frameDuration = mAnimation->getFrame(mFrame).duration;
	while (mTimeElapsed >= frameDuration)
	{
		nextFrame();
		mTimeElapsed -= frameDuration;
	}
}

void AnimationComponent::update(Time dt)
{
	if (mPlaying)
	{
		mTimeElapsed += dt;
		Time frameDuration = mAnimation->getFrame(mFrame).duration;
		if (mTimeElapsed >= frameDuration)
		{
			nextFrame();
			mTimeElapsed -= frameDuration;
		}
	}
}

void AnimationComponent::onSpawn()
{
	getWorld().getAnimationSystem().registerAnimationComponent(this);
}

void AnimationComponent::onDestroy()
{
	getWorld().getAnimationSystem().unregisterAnimationComponent(this);
}

void AnimationComponent::applyFrame(U32 frameIndex)
{
	mFrame = frameIndex;
	const Animation::Frame& newFrame = mAnimation->getFrame(mFrame);
	if (mTexture != newFrame.texture)
	{
		mTexture = newFrame.texture;
		SpriteComponent::setTexture(mTexture);
	}
	SpriteComponent::setTextureRect(static_cast<sf::IntRect>(toSF(newFrame.rect)));
}

void AnimationComponent::nextFrame()
{
	applyFrame((mFrame + 1) % mAnimation->getFrameCount());
}

} // namespace oe
