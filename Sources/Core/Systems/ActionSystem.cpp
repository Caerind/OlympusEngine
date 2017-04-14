#include "ActionSystem.hpp"

namespace oe
{

U32 ActionInput::mIdCounter = 0;

ActionInput::ActionInput()
	: mId(++mIdCounter)
	, mSystem(nullptr)
	, mActive(false)
{
}

U32 ActionInput::getId() const
{
	return mId;
}

bool ActionInput::isActive() const
{
	return mActive;
}

void ActionInput::update()
{
}

void ActionInput::reset()
{
	mActive = false;
}

void ActionInput::setSystem(ActionSystem& system)
{
	mSystem = &system;
}

ActionSystem* ActionInput::getSystem()
{
	return mSystem;
}

ActionInputVariable::ActionInputVariable()
	: ActionInput()
	, mVariable(nullptr)
{
}

ActionInputVariable::ActionInputVariable(bool* variable)
	: ActionInput()
	, mVariable(variable)
{
}

ActionInputVariable::ActionInputVariable(bool& variable)
	: ActionInput()
	, mVariable(&variable)
{
}

void ActionInputVariable::setVariable(bool* variable)
{
	mVariable = variable;
}

void ActionInputVariable::setVariable(bool& variable)
{
	mVariable = &variable;
}

void ActionInputVariable::update()
{
	mActive = (mVariable != nullptr && *mVariable == true);
}

ActionInputFunction::ActionInputFunction()
	: ActionInput()
{
}

ActionInputFunction::ActionInputFunction(std::function<bool()> function)
	: ActionInput()
	, mFunction(function)
{
}

void ActionInputFunction::setFunction(std::function<bool()> function)
{
	mFunction = function;
}

void ActionInputFunction::update()
{
	mActive = (mFunction && mFunction());
}

ActionInputEvent::ActionInputEvent()
	: ActionInput()
{
}

ActionInputEvent::ActionInputEvent(std::function<bool(const sf::Event& event)> validation)
	: ActionInput()
	, mValidation(validation)
{
}

void ActionInputEvent::setEventValidation(std::function<bool(const sf::Event& event)> validation)
{
	mValidation = validation;
}

void ActionInputEvent::update()
{
	mActive = (getSystem() != nullptr && mValidation && getSystem()->hasEvent(mValidation));
}

ActionInputKey::ActionInputKey(sf::Keyboard::Key key, ActionType type)
	: ActionInput()
	, mKey(key)
	, mType(type)
{
	updateValidation();
}

void ActionInputKey::setKey(sf::Keyboard::Key key)
{
	mKey = key;
	updateValidation();
}

void ActionInputKey::setType(ActionType type)
{
	mType = type;
	updateValidation();
}

void ActionInputKey::update()
{
	if (mType == ActionType::Hold)
	{
		mActive = sf::Keyboard::isKeyPressed(mKey);
	}
	else
	{
		mActive = (getSystem() != nullptr && mValidation && getSystem()->hasEvent(mValidation));
	}
}

void ActionInputKey::updateValidation()
{
	mValidation = [this](const sf::Event& event) -> bool
	{
		return ((event.type == sf::Event::KeyPressed && mType == ActionType::Pressed) || (event.type == sf::Event::KeyReleased && mType == ActionType::Released)) && event.key.code == mKey;
	};
}

ActionInputMouse::ActionInputMouse(sf::Mouse::Button button, ActionType type)
	: ActionInput()
	, mButton(button)
	, mType(type)
{
	updateValidation();
}

void ActionInputMouse::setButton(sf::Mouse::Button button)
{
	mButton = button;
	updateValidation();
}

void ActionInputMouse::setType(ActionType type)
{
	mType = type;
	updateValidation();
}

void ActionInputMouse::update()
{
	if (mType == ActionType::Hold)
	{
		mActive = sf::Mouse::isButtonPressed(mButton);
	}
	else
	{
		mActive = (getSystem() != nullptr && mValidation && getSystem()->hasEvent(mValidation));
	}
}

void ActionInputMouse::updateValidation()
{
	mValidation = [this](const sf::Event& event) -> bool
	{
		return ((event.type == sf::Event::MouseButtonPressed && mType == ActionType::Pressed) || (event.type == sf::Event::MouseButtonReleased && mType == ActionType::Released)) && event.mouseButton.button == mButton;
	};
}

ActionSystem::ActionSystem()
{
}

void ActionSystem::addEvent(const sf::Event& event)
{
	mEvents.push_back(event);
}

void ActionSystem::update()
{
	for (auto itr = mInputs.begin(); itr != mInputs.end(); ++itr)
	{
		itr->second->reset();
		itr->second->update();
	}
	mEvents.clear();
	for (auto itr = mActions.begin(); itr != mActions.end(); ++itr)
	{
		itr->second.update();
	}
}

bool ActionSystem::hasEvent(std::function<bool(const sf::Event& event)> eventValidation)
{
	for (const sf::Event& event : mEvents)
	{
		if (eventValidation(event))
		{
			return true;
		}
	}
	return false;
}

ActionId ActionSystem::addAction(const std::string& name)
{
	ActionId id = StringHash::hash(name); 
	if (mActions.find(id) == mActions.end())
	{
		mActions[id] = Action();
	}
	return id;
}

void ActionSystem::setInput(ActionId id, ActionInput* input)
{
	mActions[id].setInput(input);
	mInputs[input->getId()] = input;
	input->setSystem(*this);
}

void ActionSystem::setInput(const std::string& name, ActionInput* input)
{
	setInput(StringHash::hash(name), input);
}

void ActionSystem::addOutput(ActionId id, const ActionOutput& output)
{
	mActions[id].addOutput(output);
}

void ActionSystem::addOutput(const std::string& name, const ActionOutput& output)
{
	addOutput(StringHash::hash(name), output);
}

bool ActionSystem::isActive(ActionId id) const
{
	return mActions.at(id).isActive();
}

bool ActionSystem::isActive(const std::string& name) const
{
	return isActive(StringHash::hash(name));
}

ActionSystem::Action::Action()
	: mInput(nullptr)
{
}

void ActionSystem::Action::setInput(ActionInput* input)
{
	mInput = input;
}

bool ActionSystem::Action::isActive() const
{
	return mInput != nullptr && mInput->isActive();
}

void ActionSystem::Action::update()
{
	if (isActive())
	{
		for (const ActionOutput& output : mOutputs)
		{
			output();
		}
	}
}

void ActionSystem::Action::addOutput(const ActionOutput& output)
{
	if (output)
	{
		mOutputs.push_back(output);
	}
}

} // namespace oe