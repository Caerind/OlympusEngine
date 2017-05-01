#include "Application.hpp"

#include <SFML/Window/Event.hpp>

namespace oe
{

Application::Application()
	: mLog()
	, mStates(*this)
	, mWindow(sf::VideoMode(800,600), "OlympusEngine")
	, mLocalization()
	, mFPSCounter(0)
	, mUPSCounter(0)
	, mRunning(true)
{
	mWindowClosedSlot.connect(mWindow.onWindowClosed, [this](const Window* window)
	{
		stop();
	});

	//ImGui::SFML::Init(mWindow.getHandle());
}

Application::~Application()
{
	if (mRunning)
	{
		stop();
	}

	//ImGui::SFML::Shutdown();

	#ifdef OE_PLATFORM_ANDROID
		std::exit(0);
	#endif
}

Window& Application::getWindow()
{
	return mWindow;
}

Localization& Application::getLocalization()
{
	return mLocalization;
}

AudioSystem& Application::getAudio()
{
	return mAudioSystem;
}

TextureHolder& Application::getTextures()
{
	return mTextureHolder;
}

FontHolder& Application::getFonts()
{
	return mFontHolder;
}

void Application::run()
{
	Clock clock;
	Clock clockFPS;
	Clock clockUPS;
	Time timePerFrame(seconds(1.0f / 60.0f));
	Time timeSinceLastUpdate(Time::Zero);
	Time second(seconds(1.0f));
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
	mWindow.close();

	mAudioSystem.stop();

	mRunning = false;
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
	if (!cont || !mWindow.isOpen())
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

} // namespace oe
