#include "Application.hpp"

#include <SFML/Window/Event.hpp>

namespace oe
{

Application::Application()
	: mLogger()
	, mStates(*this)
	, mWindow(sf::VideoMode(800,600), "OlympusEngine")
	, mLocalization()
	, mConsole()
	, mFpsAccumulator(Time::Zero)
	, mFpsTemp(0)
	, mFps(0)
	, mRunning(true)
{
	#ifdef OE_IMGUI
	ImGuiWrapper::init();
	#endif
}

Application::~Application()
{
	#ifdef OE_IMGUI
	ImGuiWrapper::shutdown();
	#endif

	mFps = 0;

	if (mWindow.isOpen())
	{
		mWindow.close();
	}

	#ifdef OE_PLATFORM_ANDROID
	std::exit(0);
	#endif
}

Logger& Application::getLogger()
{
	return mLogger;
}

Window& Application::getWindow()
{
	return mWindow;
}

Localization& Application::getLocalization()
{
	return mLocalization;
}

Console& Application::getConsole()
{
	return mConsole;
}

AudioSystem& Application::getAudio()
{
	return mAudioSystem;
}

TextureManager& Application::getTextures()
{
	return mTextureManager;
}

FontManager& Application::getFonts()
{
	return mFontManager;
}

void Application::stop()
{
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

const U32& Application::getFPS() const
{
	return mFps;
}

void Application::run()
{
	const Time TimePerFrame = seconds(1.0f / 60.0f);
	Time accumulator = Time::Zero;
	Clock clock;

	// Running loop
	while (mRunning)
	{
		// Time
		Time dt = clock.restart();
		accumulator += dt;
		mFpsAccumulator += dt;

		// Usefull when using Breakpoints on Debugging
		#ifdef OE_DEBUG
		if (accumulator > Time::Second)
		{
			accumulator = TimePerFrame;
		}
		#endif

		bool importantFrame = false;
		mProfiler.beginFrame();

		// Update
		while (accumulator >= TimePerFrame)
		{
			importantFrame = true;

			accumulator -= TimePerFrame;

			mProfiler.beginFunction("Events");
			events();
			mProfiler.endFunction();

			mProfiler.beginFunction("PreUpdate");
			preUpdate();
			mProfiler.endFunction();

			mProfiler.beginFunction("Update");
			update(TimePerFrame);
			mProfiler.endFunction();

			mProfiler.beginFunction("PostUpdate");
			postUpdate();
			mProfiler.endFunction();
		}

		// Rendering
		mProfiler.beginFunction("Render");
		render();
		mProfiler.endFunction();

		mProfiler.endFrame(importantFrame);

		// FPS
		mFpsTemp++;
		if (mFpsAccumulator > Time::Second)
		{
			mFpsAccumulator -= Time::Second;
			mFps = mFpsTemp;
			mFpsTemp = 0;

			mWindow.setTitle("FPS : " + toString(mFps));
		}

		// Stop ?
		if (!mWindow.isOpen() || mStates.getStateCount() == 0)
		{
			stop();
		}
	}
}

void Application::events()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		// Might have used Signal of the Window, but clearer like this
		if (event.type == sf::Event::GainedFocus)
		{
			mAudioSystem.play();
		}
		if (event.type == sf::Event::LostFocus)
		{
			mAudioSystem.pause();
		}

		#ifdef OE_IMGUI
		ImGuiWrapper::handleEvent(mWindow.getHandle(), event);
		#endif

		mStates.handleEvent(event);
	}
}

void Application::preUpdate()
{
	mAudioSystem.update();
}

void Application::update(Time dt)
{
	#ifdef OE_IMGUI
	ImGuiWrapper::update(mWindow.getHandle(), toSF(dt));
	#endif

	mStates.update(dt);
}

void Application::postUpdate()
{
	#ifdef OE_IMGUI
	ImGuiWrapper::updateRender();
	#endif
}

void Application::render()
{
	mWindow.clear();

	mStates.render(mWindow.getHandle());

	#ifdef OE_IMGUI
	mWindow.draw(sf::RectangleShape()); // This fix a bug when rendering with the World
	ImGuiWrapper::render();
	#endif 

	mWindow.display();
}

} // namespace oe
