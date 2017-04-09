#include "AudioListenerComponent.hpp"

namespace oe
{

AudioListenerComponent::AudioListenerComponent(Entity* entity)
	: SceneComponent(entity)
{
}

void AudioListenerComponent::setGlobalVolume(float volume)
{
	sf::Listener::setGlobalVolume(volume);
}

float AudioListenerComponent::getGlobalVolume() const
{
	return sf::Listener::getGlobalVolume();
}

void AudioListenerComponent::setDirection(F32 x, F32 y, F32 z)
{
	sf::Listener::setDirection(x, y, z);
}

void AudioListenerComponent::setDirection(const Vector3& dir)
{
	sf::Listener::setDirection(toSF(dir));
}

Vector3 AudioListenerComponent::getDirection() const
{
	return toOE(sf::Listener::getDirection());
}

void AudioListenerComponent::setUpVector(F32 x, F32 y, F32 z)
{
	sf::Listener::setUpVector(x, y, z);
}

void AudioListenerComponent::setUpVector(const Vector3& up)
{
	sf::Listener::setUpVector(toSF(up));
}

Vector3 AudioListenerComponent::getUpVector() const
{
	return toOE(sf::Listener::getUpVector());
}

void AudioListenerComponent::onSpawn()
{
	mInvalidationSlot.connect(onNodeInvalidation, [this](const Node* node)
	{
		sf::Listener::setPosition(toSF(getGlobalPosition()));
	});
	mInvalidationZSlot.connect(onNodeInvalidationZ, [this](const Node* node)
	{
		sf::Listener::setPosition(toSF(getGlobalPosition()));
	});
}

void AudioListenerComponent::onDestroy()
{
	mInvalidationSlot.disconnect();
	mInvalidationZSlot.disconnect();
}

} // namespace oe
