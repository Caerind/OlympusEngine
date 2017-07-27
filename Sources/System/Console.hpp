#ifndef OE_CONSOLE_HPP
#define OE_CONSOLE_HPP

#include <functional>
#include <thread>

#include "Prerequisites.hpp"
#include "Singleton.hpp"

namespace oe
{

class ConsoleInstance
{	
	public:
		ConsoleInstance();
		virtual ~ConsoleInstance();

		void connect();
		void disconnect();
		bool isConnected() const;

		void sendCommand(const std::string& command);

		virtual void addLine(const std::string& line) = 0;
};

class DebugConsole : public ConsoleInstance
{
	public:
		DebugConsole();
		virtual ~DebugConsole();

		void addLine(const std::string& line);

	private:
		void run();

	private:
		std::thread mThread;
		bool mRunning;
};

class Console : public Singleton<Console>
{
	public:
		Console();
		~Console();

		static Console& getSingleton();
		static Console* getSingletonPtr();

		void addLine(const std::string& line);
		void receiveCommand(const std::string& command);

		void setInstance(ConsoleInstance* instance);
		ConsoleInstance* getInstance() const;

		class Command
		{
			public:
				using OptionSplit = std::map<std::string, std::vector<std::string>>;
				using CommandFunction = std::function<void(OptionSplit options)>;

				Command();

				const std::string& getName() const;
				const std::string& getHelp() const;
				const std::string& getManual() const;

				void execute(const std::string& options = "");

				void setName(const std::string& name);
				void setHelp(const std::string& help);
				void setManual(const std::string& manual);
				void setFunction(CommandFunction function);

				static void read(const std::string& command, std::string& name, std::string& options);
				static OptionSplit splitOptions(const std::string& options);

			private:
				std::string mName;
				std::string mHelp;
				std::string mManual;
				CommandFunction mFunction;
		};

		void addCommand(const Command& command);

	private:
		ConsoleInstance* mInstance;
		std::vector<Command> mCommands;
};

} // namespace oe

#endif // OE_CONSOLE_HPP
