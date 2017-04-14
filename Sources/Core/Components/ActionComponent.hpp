#ifndef OE_ACTIONCOMPONENT_HPP
#define OE_ACTIONCOMPONENT_HPP

#include "../Systems/ActionSystem.hpp"
#include "../Component.hpp"

namespace oe
{

class ActionComponent : public Component
{
	public:
		ActionComponent(Entity& entity);

		ActionId addAction(const std::string& name);

		void setInput(ActionId id, ActionInput* input);
		void setInput(const std::string& name, ActionInput* input);

		void addOutput(ActionId id, const ActionOutput& output);
		void addOutput(const std::string& name, const ActionOutput& output);

		bool isActive(ActionId id);
		bool isActive(const std::string& name);

		ActionSystem& getActionSystem();
};

} // namespace oe

#endif // OE_ANIMATIORCOMPONENT_HPP
