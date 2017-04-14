#ifndef OE_APPLICATION_HPP
#define OE_APPLICATION_HPP

#include "StateManager.hpp"

#include "../System/Singleton.hpp"
#include "../System/Time.hpp"
#include "../System/Window.hpp"

namespace oe
{

class Application
{
	public:
		Application();
		~Application();

		Window& getWindow();

		void run();
		void stop();

		template <typename T, typename ... Args>
		void pushState(Args&& ... args);
		void popState();
		void clearStates();

		const U32& getFPSCount() const;
		const U32& getUPSCount() const;

		OeSlot(oe::Window, onWindowClosed, mWindowClosedSlot);

	private:	
		void processEvents();
		void update(Time dt);
		void render();

	private:
		Window mWindow;
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
