#include "State.hpp"

#include "Application.hpp"

namespace oe
{

State::State()
{
}

State::~State()
{
}

void State::onActivate()
{
}

void State::onDeactivate()
{
}

bool State::handleEvent(const sf::Event& event)
{
	return false;
}

bool State::update(Time dt)
{
	return false;
}

void State::render(sf::RenderTarget& target)
{
}

void State::popState()
{
	Application::getSingleton().popState();
}

void State::clearStates()
{
	Application::getSingleton().clearStates();
}

} // namespace oe