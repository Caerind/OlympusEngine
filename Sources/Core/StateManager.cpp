#include "StateManager.hpp"
#include "Application.hpp"

namespace oe
{

State::State(StateManager& manager)
	: mManager(manager)
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
	mManager.popState();
}

void State::clearStates()
{
	mManager.clearStates();
}

Application& State::getApplication()
{
	return mManager.getApplication();
}

StateManager::StateManager(Application& application)
	: mApplication(application)
{
}

StateManager::~StateManager()
{
	// TODO : How to close properly ?
	//for (auto itr = mStates.begin(); itr != mStates.end(); ++itr)
	//{
	//	(*itr)->onDeactivate();
	//}
	//mStates.clear();
}

bool StateManager::handleEvent(const sf::Event& event)
{
	for (auto itr = mStates.rbegin(); itr != mStates.rend(); ++itr)
	{
		if (!(*itr)->handleEvent(event))
		{
			break;
		}
	}
	return applyPendingChanges();
}

bool StateManager::update(Time dt)
{
	for (auto itr = mStates.rbegin(); itr != mStates.rend(); ++itr)
	{
		if (!(*itr)->update(dt))
		{
			break;
		}
	}
	return applyPendingChanges();
}

void StateManager::render(sf::RenderTarget& target)
{
	for (auto itr = mStates.begin(); itr != mStates.end(); ++itr)
	{
		(*itr)->render(target);
	}
}

void StateManager::popState()
{
	mChanges.emplace_back(Action::Pop, nullptr);
}

void StateManager::clearStates()
{
	mChanges.emplace_back(Action::Clear, nullptr);
}

U32 StateManager::getStateCount() const
{
	return mStates.size();
}

Application& StateManager::getApplication()
{
	return mApplication;
}

bool StateManager::applyPendingChanges()
{
	for (const PendingChange& change : mChanges)
	{
		switch (change.action)
		{
			case Action::Push:
				if (mStates.size() > 0)
				{
					mStates.back()->onDeactivate();
				}
				mStates.push_back(change.state);
				mStates.back()->onActivate();
				break;

			case Action::Pop:
				if (mStates.size() > 0)
				{
					mStates.back()->onDeactivate();
					mStates.pop_back();
				}
				if (mStates.size() > 0)
				{
					mStates.back()->onActivate();
				}
				break;

			case Action::Clear:
				if (mStates.size() > 0)
				{
					mStates.back()->onDeactivate();
				}
				mStates.clear();
				break;
		}
	}
	mChanges.clear();
	return mStates.size() > 0;
}

StateManager::PendingChange::PendingChange(Action action, State::Ptr state)
	: action(action)
	, state(state)
{
}

} // namespace oe