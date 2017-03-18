#ifndef OE_SCENECOMPONENT_HPP
#define OE_SCENECOMPONENT_HPP

#include "Component.hpp"
#include "Transformable.hpp"

namespace oe
{

class SceneComponent : public Component, public Transformable
{
	public:
		SceneComponent();

		Vector2 getGlobalPosition() const;
		Matrix4 getGlobalMatrix() const;
		sf::Transform getGlobalTransform() const;
};

} // namespace oe

#endif // OE_SCENECOMPONENT_HPP
