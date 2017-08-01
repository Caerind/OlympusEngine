#ifndef IMGUIWRAPPER_HPP
#define IMGUIWRAPPER_HPP

#include <SFML/Graphics.hpp>

#include "../ExtLibs/imgui/imgui.h"

#include "../System/Console.hpp"
#include "../System/Logger.hpp"
#include "../System/Profiler.hpp"
#include "../System/DataManager.hpp"

namespace oe
{

namespace ImGuiWrapper
{

void init();
void handleEvent(sf::RenderWindow& window, const sf::Event& event);
void update(sf::RenderWindow& window, sf::Time dt);
void updateRender();
void render();
void shutdown();

} // namespace ImGuiWrapper

class ImGuiWindow
{
	public:
		ImGuiWindow(const std::string& name, F32 x = -1.0f, F32 y = -1.0f, F32 w = -1.0f, F32 h = -1.0f);

		void show();
		void hide();
		bool isVisible() const;

		const std::string& getName() const;

		void Begin(F32 x, F32 y, F32 w, F32 h);

	private:
		std::string mName;
		bool mVisible;
		F32 mX, mY, mW, mH;
};

class ImGuiLogger : public ImGuiWindow, public LogReceiver
{
	public:
		ImGuiLogger(F32 x = -1.0f, F32 y = -1.0f, F32 w = -1.0f, F32 h = -1.0f);
		virtual ~ImGuiLogger();

		virtual void onReceive(const Log& log);

		void draw();

		void clear();

	private:
		std::vector<std::string> mLines;
};

class ImGuiConsole : public ImGuiWindow, public ConsoleInstance
{
	public:
		ImGuiConsole(F32 x = -1.0f, F32 y = -1.0f, F32 w = -1.0f, F32 h = -1.0f);
		virtual ~ImGuiConsole();

		void clearLines();

		virtual void addLine(const std::string& line);

		void draw();

	private:
		char mInputBuf[256];
		std::vector<std::string> mLines;
};

class ImGuiProfiler : public ImGuiWindow, public ProfilerDisplay
{
	public:
		ImGuiProfiler(F32 x = -1.0f, F32 y = -1.0f, F32 w = -1.0f, F32 h = -1.0f);
		virtual ~ImGuiProfiler();

		virtual void displayFrame(const ProfilerFrame& frame);

		void pause();
		void play();

		void draw();

	private:
		void drawFunctionCall(const ProfilerFunctionCall& fc);

	private:
		ProfilerFrame mFrame;
		bool mPaused;
		bool mImportant;
};

class ImGuiDataViewer : public ImGuiWindow, public DataViewer
{
	public:
		ImGuiDataViewer(F32 x = -1.0f, F32 y = -1.0f, F32 w = -1.0f, F32 h = -1.0f);
		virtual ~ImGuiDataViewer();

		virtual void setData(const std::string& key, const std::string& value);
		virtual void eraseData(const std::string& key);
		virtual void clear();

		void draw();

	private:
		std::vector<Data> mData;
};

} // namespace oe

#endif // IMGUIWRAPPER_HPP


