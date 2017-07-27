#include "ParticleSystem.hpp"

namespace oe
{

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
	mParticleComponents.clear();
}

void ParticleSystem::update(Time dt)
{
	for (auto itr = mParticleComponents.begin(); itr != mParticleComponents.end(); ++itr)
	{
		(*itr)->update(dt);
	}
}

void ParticleSystem::registerParticleComponent(ParticleComponent * particles)
{
	mParticleComponents.insert(particles);
}

void ParticleSystem::unregisterParticleComponent(ParticleComponent * particles)
{
	mParticleComponents.remove(particles);
}

} // namespace oe