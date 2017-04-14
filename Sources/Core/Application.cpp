#include "Application.hpp"

#include <SFML/Window/Event.hpp>

namespace oe
{

Application::Application()
	: mStates(*this)
	, mWindow(sf::VideoMode(800,600), "OlympusEngine")
	, mRunning(true)
	, mFPSCounter(0)
	, mUPSCounter(0)
{
	mWindowClosedSlot.connect(mWindow.onWindowClosed, [this](const Window* window)
	{
		stop();
	});
}

Application::~Application()
{
	if (mWindow.isOpen())
	{
		mWindow.close();
	}
}

void Application::run()
{
	Clock clock;
	Clock clockFPS;
	Clock clockUPS;
	Time timePerFrame(seconds(1.f / 60.f));
	Time timeSinceLastUpdate(Time::Zero);
	Time second(seconds(1.f));
	U32 tempFPS = 0;
	mFPSCounter = 0;
	U32 tempUPS = 0;
	mUPSCounter = 0;
	while (mRunning)
	{
		Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate >= timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;

			// Handle event
			processEvents();

			// Update
			update(timePerFrame);

			// UPS
			tempUPS++;
			if (clockUPS.getElapsedTime() >= second)
			{
				clockUPS.restart();
				mUPSCounter = tempUPS;
				tempUPS = 0;
			}
		}

		// Render
		render();

		// FPS
		tempFPS++;
		if (clockFPS.getElapsedTime() >= second)
		{
			clockFPS.restart();
			mFPSCounter = tempFPS;
			tempFPS = 0;
		}
	}
}

void Application::stop()
{
	mRunning = false;
	#ifdef OE_PLATFORM_ANDROID
		// TODO : Android quit application
	#endif
}

void Application::popState()
{
	mStates.popState();
}

void Application::clearStates()
{
	mStates.clearStates();
}

const U32& Application::getFPSCount() const
{
	return mFPSCounter;
}

const U32& Application::getUPSCount() const
{
	return mUPSCounter;
}

void Application::processEvents()
{
	sf::Event event;
	bool cont = true;
	while (mWindow.pollEvent(event))
	{
		cont = mStates.handleEvent(event);
	}
	if (!cont)
	{
		stop();
	}
}

void Application::update(Time dt)
{
	if (!mStates.update(dt))
	{
		stop();
	}
}

void Application::render()
{
	mWindow.clear();

	mStates.render(mWindow.getHandle());

	mWindow.display();
}

Window& Application::getWindow()
{
	return mWindow;
}

} // namespace oe