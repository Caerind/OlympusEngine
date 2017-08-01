#ifndef OE_APPLICATION_HPP
#define OE_APPLICATION_HPP

#include "../System/Console.hpp"
#include "../System/Localization.hpp"
#include "../System/Logger.hpp"
#include "../System/Profiler.hpp"
#include "../System/Singleton.hpp"
#include "../System/Time.hpp"

#include "../Graphics/SFMLResources.hpp"

#include "Window.hpp"
#include "ResourceManager.hpp"
#include "AudioSystem.hpp"
#include "ImGuiWrapper.hpp"
#include "StateManager.hpp"

namespace oe
{

class Application
{
	public:
		Application();
		~Application();

		Logger& getLogger();
		Window& getWindow();
		Localization& getLocalization();
		Console& getConsole();
		AudioSystem& getAudio();
		TextureManager& getTextures();
		FontManager& getFonts();
		DataManager& getData();

		template <typename State, typename ... Args>
		void start(Args&& ... args);

		void stop();

		template <typename T, typename ... Args>
		void pushState(Args&& ... args);
		void popState();
		void clearStates();

		const U32& getFPS() const;

	private:
		void run();
		void events();
		void preUpdate();
		void update(Time dt);
		void postUpdate();
		void render();

	private:
		Logger mLogger;

		StateManager mStates;
		Window mWindow;

		Localization mLocalization;
		Profiler mProfiler;
		Console mConsole;
		DataManager mDataManager;

		AudioSystem mAudioSystem;

		TextureManager mTextureManager;
		FontManager mFontManager;

		Time mFpsAccumulator;
		U32 mFpsTemp;
		U32 mFps;
		bool mRunning;
};

template <typename State, typename ... Args>
void Application::start(Args&& ... args)
{
	pushState<State>(std::forward<Args>(args)...);

	mStates.applyPendingChanges();

	mRunning = true;

	run();
}

template <typename T, typename ... Args>
void Application::pushState(Args&& ... args)
{
	mStates.pushState<T>(std::forward<Args>(args)...);
}

} // namespace oe

#endif // OE_APPLICATION_HPP
