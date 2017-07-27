#ifndef OE_PARTICLESYSTEM_HPP
#define OE_PARTICLESYSTEM_HPP

#include "../../System/Prerequisites.hpp"

#include "../../System/List.hpp"

#include "../Components/ParticleComponent.hpp"

namespace oe
{

class ParticleSystem
{
	public:
		ParticleSystem();
		~ParticleSystem();

		void update(Time dt);

		void registerParticleComponent(ParticleComponent* particles);
		void unregisterParticleComponent(ParticleComponent* particles);

	private:
		List<ParticleComponent*> mParticleComponents;
};

} // namespace oe

#endif // OE_PARTICLESYSTEM_HPP
