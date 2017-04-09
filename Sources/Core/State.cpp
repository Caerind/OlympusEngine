#include "State.hpp"

#include "Application.hpp"

namespace oe
{

State::State(Application& application)
	: mApplication(application)
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
	mApplication.popState();
}

void State::clearStates()
{
	mApplication.clearStates();
}

} // namespace oe