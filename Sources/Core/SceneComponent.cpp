#include "SceneComponent.hpp"
#include "Entity.hpp"

namespace oe
{

SceneComponent::SceneComponent()
{
}

Vector2 SceneComponent::getGlobalPosition() const
{
	return oe::SFML::toOE(getGlobalTransform() *  sf::Vector2f(0.f, 0.f));
}

Matrix4 SceneComponent::getGlobalMatrix() const
{
	return (hasParent()) ? mParent->getMatrix() * getMatrix() : getMatrix();
}

sf::Transform SceneComponent::getGlobalTransform() const
{
	return (hasParent()) ? mParent->getTransform() * getTransform() : getTransform();
}

} // namespace oe