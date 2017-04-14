#ifndef OE_SCENECOMPONENT_HPP
#define OE_SCENECOMPONENT_HPP

#include "Component.hpp"
#include "../System/Node.hpp"

#include "../System/SFMLResources.hpp"

namespace oe
{

class SceneComponent : public Component, public Node
{
	public:
		SceneComponent(Entity& entity);
};

} // namespace oe

#endif // OE_SCENECOMPONENT_HPP
