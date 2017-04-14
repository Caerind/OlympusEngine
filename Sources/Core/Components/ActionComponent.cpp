#include "ActionComponent.hpp"
#include "../World.hpp"

namespace oe
{

ActionComponent::ActionComponent(Entity& entity)
	: Component(entity)
{
}

ActionId ActionComponent::addAction(const std::string& name)
{
	return getActionSystem().addAction(name);
}

void ActionComponent::setInput(ActionId id, ActionInput* input)
{
	getActionSystem().setInput(id, input);
}

void ActionComponent::setInput(const std::string& name, ActionInput* input)
{
	getActionSystem().setInput(name, input);
}

void ActionComponent::addOutput(ActionId id, const ActionOutput& output)
{
	getActionSystem().addOutput(id, output);
}

void ActionComponent::addOutput(const std::string& name, const ActionOutput& output)
{
	getActionSystem().addOutput(name, output);
}

bool ActionComponent::isActive(ActionId id)
{
	return getActionSystem().isActive(id);
}

bool ActionComponent::isActive(const std::string& name)
{
	return getActionSystem().isActive(name);
}

ActionSystem& ActionComponent::getActionSystem()
{
	return getWorld().getActionSystem();
}

} // namespace oe