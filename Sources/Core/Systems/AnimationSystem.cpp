#include "AnimationSystem.hpp"

namespace oe
{

AnimationSystem::AnimationSystem()
{
}

AnimationSystem::~AnimationSystem()
{
	mAnimationComponents.clear();
}

void AnimationSystem::update(Time dt)
{
	for (auto itr = mAnimationComponents.begin(); itr != mAnimationComponents.end(); ++itr)
	{
		(*itr)->update(dt);
	}
}

void AnimationSystem::registerAnimationComponent(AnimationComponent * animations)
{
	mAnimationComponents.insert(animations);
}

void AnimationSystem::unregisterAnimationComponent(AnimationComponent * animations)
{
	mAnimationComponents.remove(animations);
}

} // namespace oe