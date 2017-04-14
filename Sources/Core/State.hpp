#ifndef OE_STATE_HPP
#define OE_STATE_HPP

#include "../System/Time.hpp"

#include <memory>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

namespace oe
{

class Application;

class State
{
	public:
		State(Application& application);
		virtual ~State();

		using Ptr = std::shared_ptr<State>;

		virtual void onActivate();
		virtual void onDeactivate();

		virtual bool handleEvent(const sf::Event& event);
		virtual bool update(Time dt);
		virtual void render(sf::RenderTarget& target);

		template <typename T, typename ... Args>
		void pushState(Args&& ... args);
		void popState();
		void clearStates();

	protected:
		Application& mApplication;
};

template <typename T, typename ... Args>
void State::pushState(Args&& ... args)
{
	mApplication.pushState<T>(std::forward<Args>(args)...);
}

} // namespace oe

#endif // OE_STATE_HPP
