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
		State();
		virtual ~State();

		using Ptr = std::shared_ptr<State>;

		virtual std::string getName() = 0;

		virtual void onActivate();
		virtual void onDeactivate();

		virtual bool handleEvent(const sf::Event& event);
		virtual bool update(Time dt);
		virtual void render(sf::RenderTarget& target);

		template <typename T, typename ... Args>
		void pushState(Args&& ... args);
		void popState();
		void clearStates();
};

template <typename T, typename ... Args>
void State::pushState(Args&& ... args)
{
	Application::getSingleton().pushState<T>(std::forward<Args>(args)...);
}

} // namespace oe

#endif // OE_STATE_HPP
