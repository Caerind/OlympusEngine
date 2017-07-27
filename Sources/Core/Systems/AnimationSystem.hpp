#ifndef OE_ANIMATIONSYSTEM_HPP
#define OE_ANIMATIONSYSTEM_HPP

#include "../../System/Prerequisites.hpp"

#include "../../System/List.hpp"

#include "../Components/AnimationComponent.hpp"

namespace oe
{

class AnimationSystem
{
	public:
		AnimationSystem();
		~AnimationSystem();

		void update(Time dt);

		void registerAnimationComponent(AnimationComponent* animations);
		void unregisterAnimationComponent(AnimationComponent* animations);

	private:
		List<AnimationComponent*> mAnimationComponents;
};

} // namespace oe

#endif // OE_ANIMATIONSYSTEM_HPP
