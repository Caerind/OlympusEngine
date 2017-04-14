#ifndef OE_ACTIONSYSTEM_HPP
#define OE_ACTIONSYSTEM_HPP

#include "../../System/Prerequisites.hpp"

#include <map>
#include <vector>
#include <functional>

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

namespace oe
{
	
using ActionId = U32;

using ActionOutput = std::function<void()>;

enum class ActionType
{
	Hold,
	Pressed,
	Released,
};

class ActionSystem;

class ActionInput
{
	public:
		ActionInput();
		
		U32 getId() const;
		bool isActive() const;
		
	private:
		friend class ActionSystem;
		virtual void update();
		void reset();
		void setSystem(ActionSystem& system);
		
	private:
		U32 mId;
		static U32 mIdCounter;
		ActionSystem* mSystem;
		
	protected:
		ActionSystem* getSystem();
		bool mActive;
};

class ActionInputVariable : public ActionInput
{
	public:
		ActionInputVariable();
		ActionInputVariable(bool* variable);
		ActionInputVariable(bool& variable);
		
		void setVariable(bool* variable);
		void setVariable(bool& variable);
		
	private:
		friend class ActionSystem;
		virtual void update();
		
	private:
		bool* mVariable;
};

class ActionInputFunction : public ActionInput
{
	public:
		ActionInputFunction();
		ActionInputFunction(std::function<bool()> function);
		
		void setFunction(std::function<bool()> function);
		
	private:
		friend class ActionSystem;
		virtual void update();
		
	private:
		std::function<bool()> mFunction;
};

class ActionInputEvent : public ActionInput
{
	public:
		ActionInputEvent();
		ActionInputEvent(std::function<bool(const sf::Event& event)> validation);
		
		void setEventValidation(std::function<bool(const sf::Event& event)> validation);
		
	private:
		friend class ActionSystem;
		virtual void update();
		
	private:
		std::function<bool(const sf::Event& event)> mValidation;
	
};

class ActionInputKey : public ActionInput
{
	public:
		ActionInputKey(sf::Keyboard::Key key = sf::Keyboard::Unknown, ActionType type = ActionType::Hold);
		
		void setKey(sf::Keyboard::Key key);
		void setType(ActionType type);
		
	private:
		friend class ActionSystem;
		virtual void update();

		void updateValidation();
		
	private:
		sf::Keyboard::Key mKey;
		ActionType mType;

		std::function<bool(const sf::Event& event)> mValidation;
};

class ActionInputMouse : public ActionInput
{
	public:
		ActionInputMouse(sf::Mouse::Button button = sf::Mouse::Left, ActionType type = ActionType::Released);
		
		void setButton(sf::Mouse::Button button);
		void setType(ActionType type);
		
	private:
		friend class ActionSystem;
		virtual void update();

		void updateValidation();

	private:
		sf::Mouse::Button mButton;
		ActionType mType;

		std::function<bool(const sf::Event& event)> mValidation;
};

class ActionSystem
{
    public:
		ActionSystem();
		
		void addEvent(const sf::Event& event);

		void update();
		
		bool hasEvent(std::function<bool(const sf::Event& event)> eventValidation);
		
		ActionId addAction(const std::string& name);

		void setInput(ActionId id, ActionInput* input);
		void setInput(const std::string& name, ActionInput* input);

		void addOutput(ActionId id, const ActionOutput& output);
		void addOutput(const std::string& name, const ActionOutput& output);

		bool isActive(ActionId id) const;
		bool isActive(const std::string& name) const;

	private:
		class Action
		{
			public:
				Action();

				void setInput(ActionInput* input);

				bool isActive() const;

				void update();

				void addOutput(const ActionOutput& output);

			private:
				ActionInput* mInput;
				std::vector<ActionOutput> mOutputs;
		};
		
	private:
		std::vector<sf::Event> mEvents;
		std::map<U32, ActionInput*> mInputs;
		std::map<ActionId, Action> mActions;
};

} // namespace oe

#endif // OE_ACTIONSYSTEM_HPP
