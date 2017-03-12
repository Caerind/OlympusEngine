#include "Application.hpp"

#include <SFML/Window/Event.hpp>

namespace oe
{

template <> Application* Singleton<Application>::mSingleton = nullptr;

Application::Application()
	: mStates()
	, mWindow(sf::VideoMode(800,600), "OlympusEngine")
	, mRunning(true)
	, mFPSCounter(0)
	, mUPSCounter(0)
{
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

			// FPS
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
}

Application& Application::getSingleton()
{
	ASSERT(mSingleton != nullptr);
	return *mSingleton;
}

Application* Application::getSingletonPtr()
{
	return mSingleton;
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
		if (event.type == sf::Event::Closed)
		{
			stop();
		}
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
	mStates.render(mWindow);
	mWindow.display();
}

sf::RenderWindow& Application::getWindow()
{
	return mWindow;
}

} // namespace oe