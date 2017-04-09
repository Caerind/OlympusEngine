#ifndef OE_STATEMANAGER_HPP
#define OE_STATEMANAGER_HPP

#include "State.hpp"

#include "../System/Time.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

namespace oe
{

class Application;

class StateManager
{
	public:
		StateManager(Application& application);
		~StateManager();

		bool handleEvent(const sf::Event& event);
		bool update(Time dt);
		void render(sf::RenderTarget& target);

		template <typename T, typename ... Args>
		void pushState(Args&& ... args);
		void popState();
		void clearStates();

		U32 getStateCount() const;

	private:
		enum Action
		{
			Push,
			Pop,
			Clear
		};

		struct PendingChange
		{
			PendingChange(Action action, State::Ptr state);

			Action action;
			State::Ptr state;
		};

		bool applyPendingChanges();

	private:
		Application& mApplication;
		std::vector<State::Ptr> mStates;
		std::vector<PendingChange> mChanges;
};

template <typename T, typename ... Args>
void StateManager::pushState(Args&& ... args)
{
	mChanges.emplace_back(Action::Push, std::make_shared<T>(mApplication, std::forward<Args>(args)...));
}

} // namespace oe

#endif // OE_STATEMANAGER_HPP
