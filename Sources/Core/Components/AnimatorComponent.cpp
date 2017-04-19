#include "AnimatorComponent.hpp"
#include "../World.hpp"

namespace oe
{

AnimatorComponent::AnimatorComponent(Entity& entity)
	: SpriteComponent(entity)
	, mPlaying(false)
	, mAnimation(nullptr)
	, mFrame(0)
	, mTexture(0)
	, mTimeElapsed()
{
}

bool AnimatorComponent::isPlaying() const
{
	return mPlaying;
}

bool AnimatorComponent::isPlaying(Animation* animation) const
{
	return mPlaying && mAnimation == animation;
}

void AnimatorComponent::play(Animation* animation)
{
	mAnimation = animation;
	mTimeElapsed = Time::Zero;
	if (mAnimation != nullptr)
	{
		applyFrame(0);
		mPlaying = true;
	}
}

void AnimatorComponent::stop()
{
	mPlaying = false;
}

Time AnimatorComponent::getElapsedTime() const
{
	return mTimeElapsed;
}

void AnimatorComponent::setElapsedTime(Time elapsed)
{
	mTimeElapsed = elapsed;
	Time frameDuration = mAnimation->getFrame(mFrame).duration;
	while (mTimeElapsed >= frameDuration)
	{
		nextFrame();
		mTimeElapsed -= frameDuration;
	}
}

void AnimatorComponent::update(Time dt)
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

void AnimatorComponent::onSpawn()
{
	getRenderSystem().registerAnimator(this);
}

void AnimatorComponent::onDestroy()
{
	getRenderSystem().unregisterAnimator(this);
}

void AnimatorComponent::applyFrame(U32 frameIndex)
{
	mFrame = frameIndex;
	const Animation::Frame& newFrame = mAnimation->getFrame(mFrame);
	if (mTexture != newFrame.texture)
	{
		mTexture = newFrame.texture;
		SpriteComponent::setTexture(mTexture);
	}
	SpriteComponent::setTextureRect(newFrame.rect);
}

void AnimatorComponent::nextFrame()
{
	applyFrame((mFrame + 1) % mAnimation->getFrameCount());
}

} // namespace oe
