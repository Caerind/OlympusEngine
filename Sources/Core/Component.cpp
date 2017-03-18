#include "Component.hpp"
#include "Entity.hpp"

namespace oe
{

Component::Component()
	: mParent(nullptr)
{
}

Entity* Component::getParent()
{
	return mParent;
}

bool Component::hasParent() const
{
	return mParent != nullptr;
}

void Component::setParent(Entity* parent)
{
	mParent = parent;
}

void Component::onAttach()
{
}

void Component::onDetach()
{
}

} // namespace oe