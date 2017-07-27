#include "AudioListenerComponent.hpp"

namespace oe
{

AudioListenerComponent::AudioListenerComponent(Entity& entity, bool attachedToEntity)
	: SceneComponent(entity, attachedToEntity)
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

void AudioListenerComponent::onCreate()
{
	mInvalidationSlot.connect(onNodeInvalidation, this, &AudioListenerComponent::onNodeInvalidated);
}

void AudioListenerComponent::onNodeInvalidated(const oe::Node* node)
{
	// TODO : If 3D change this
	const oe::Vector2& pos = getGlobalPosition();
	sf::Listener::setPosition(pos.x, 0.0f, pos.y);
}

} // namespace oe
