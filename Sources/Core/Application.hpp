#ifndef OE_APPLICATION_HPP
#define OE_APPLICATION_HPP

#include "StateManager.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "../System/Singleton.hpp"
#include "../System/Time.hpp"

namespace oe
{

class Application : public Singleton<Application>
{
	public:
		Application();
		~Application();

		sf::RenderWindow& getWindow();

		void run();
		void stop();

		static Application& getSingleton();
		static Application* getSingletonPtr();

		template <typename T, typename ... Args>
		void pushState(Args&& ... args);
		void popState();
		void clearStates();

		const U32& getFPSCount() const;
		const U32& getUPSCount() const;

	private:	
		void processEvents();
		void update(Time dt);
		void render();

	private:
		sf::RenderWindow mWindow;
		StateManager mStates;
		U32 mFPSCounter;
		U32 mUPSCounter;
		bool mRunning;
};

template <typename T, typename ... Args>
void Application::pushState(Args&& ... args)
{
	mStates.pushState<T>(std::forward<Args>(args)...);
}

} // namespace oe

#endif // OE_APPLICATION_HPP
