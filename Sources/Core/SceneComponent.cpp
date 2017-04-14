#include "SceneComponent.hpp"
#include "Entity.hpp"

namespace oe
{

SceneComponent::SceneComponent(Entity& entity)
	: Component(entity)
	, Node()
{
	Node::setParent(&entity);
}

} // namespace oe