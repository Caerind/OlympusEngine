#include "Console.hpp"
#include "Logger.hpp"

#include <iostream>

namespace oe
{

template <> Console* Singleton<Console>::mSingleton = nullptr;

ConsoleInstance::ConsoleInstance()
{
	if (!isConnected())
	{
		connect();
	}
}

ConsoleInstance::~ConsoleInstance()
{
	if (isConnected())
	{
		disconnect();
	}
}

void ConsoleInstance::connect()
{
	if (isConnected())
	{
		return;
	}
	if (Console::getSingletonPtr() != nullptr)
	{
		Console::getSingleton().setInstance(this);
	}
	else
	{
		error("Can't connect ConsoleInstance if Console hasn't been created");
	}
}

void ConsoleInstance::disconnect()
{
	if (!isConnected())
	{
		return;
	}
	if (Console::getSingletonPtr() != nullptr)
	{
		Console::getSingleton().setInstance(nullptr);
	}
	else
	{
		error("Can't disconnect ConsoleInstance if Console hasn't been created");
	}
}

bool ConsoleInstance::isConnected() const
{
	if (Console::getSingletonPtr() != nullptr)
	{
		return Console::getSingleton().getInstance() == this;
	}
	else
	{
		return false;
	}
}

void ConsoleInstance::sendCommand(const std::string& command)
{
	if (isConnected())
	{
		Console::getSingleton().receiveCommand(command);
	}
}

DebugConsole::DebugConsole()
	: ConsoleInstance()
	, mThread(&DebugConsole::run, this)
{
}

DebugConsole::~DebugConsole()
{
	if (isConnected())
	{
		disconnect();
	}
	mRunning = false;
	mThread.join();
}

void DebugConsole::addLine(const std::string& line)
{
	printf("%s\n", line.c_str());
}

void DebugConsole::run()
{
	mRunning = true;
	while (mRunning)
	{
		printf("-> ");

		std::string cmd;
		std::getline(std::cin, cmd);

		sendCommand(cmd); // TODO : Thread safety

		if (mRunning)
		{
			printf("\n");
		}
	}
}

Console::Console()
	: mInstance(nullptr)
{
	Command help;
	help.setName("help");
	help.setHelp("See the list of commands with short description");
	help.setManual("help\nSee the list of commands with short description\nNo options available\nEx : help");
	help.setFunction([this](Command::OptionSplit options)
	{
		for (auto command : mCommands)
		{
			addLine(command.getName() + " : " + command.getHelp());
		}
	});
	addCommand(help);

	Command man;
	man.setName("man");
	man.setHelp("See detailed information for a command");
	man.setManual("man\nSee detailed information for a command\nOptions : commandName\nEx : man help");
	man.setFunction([this](Command::OptionSplit options)
	{
		if (options["param"].size() >= 1)
		{
			std::string commandName = options["param"][0];
			for (auto command : mCommands)
			{
				if (command.getName() == commandName)
				{
					addLine(command.getManual());
				}
			}
		}
		else
		{
			addLine("Error with the options, ex : man help");
		}
	});
	addCommand(man);
}

Console::~Console()
{
}

Console& Console::getSingleton()
{
	ASSERT(mSingleton != nullptr);
	return *mSingleton;
}

Console* Console::getSingletonPtr()
{
	return mSingleton;
}

void Console::addLine(const std::string& line)
{
	if (mInstance != nullptr)
	{
		mInstance->addLine(line);
	}
}

void Console::receiveCommand(const std::string& command)
{
	addLine("# " + command + '\n');

	std::string name;
	std::string options;
	Command::read(command, name, options);
	
	for (U32 i = 0; i < mCommands.size(); i++)
	{
		if (mCommands[i].getName() == name)
		{
			mCommands[i].execute(options);
		}
	}
}

void Console::setInstance(ConsoleInstance* instance)
{
	mInstance = instance;
}

ConsoleInstance* Console::getInstance() const
{
	return mInstance;
}

void Console::addCommand(const Command& command)
{
	mCommands.push_back(command);
}

Console::Command::Command()
	: mName("")
	, mHelp("")
	, mManual("")
{
}

const std::string& Console::Command::getName() const
{
	return mName;
}

const std::string& Console::Command::getHelp() const
{
	return mHelp;
}

const std::string& Console::Command::getManual() const
{
	return mManual;
}

void Console::Command::execute(const std::string& options)
{
	if (mFunction)
	{
		mFunction(splitOptions(options));
	}
	else
	{
		error("Command not properly set\n");
	}
}

void Console::Command::setName(const std::string& name)
{
	mName = name;
}

void Console::Command::setHelp(const std::string& help)
{
	mHelp = help;
}

void Console::Command::setManual(const std::string& manual)
{
	mManual = manual;
}

void Console::Command::setFunction(CommandFunction function)
{
	mFunction = function;
}

void Console::Command::read(const std::string& command, std::string& name, std::string& options)
{
	std::size_t found = command.find_first_of(" ");
	if (found != std::string::npos)
	{
		name = command.substr(0, found);
		options = command.substr(found + 1);
	}
	else
	{
		name = command;
		options.clear();
	}
}

Console::Command::OptionSplit Console::Command::splitOptions(const std::string& options)
{
	OptionSplit split;
	if (options.size() > 0)
	{
		bool open = false;
		bool readParam = true;
		bool readOption = false;
		bool readArgs = false;
		std::size_t readPos = 0;
		std::string actualOption("");
		for (std::size_t i = 0; i < options.size(); i++)
		{
			if (options[i] == ' ' && readParam)
			{
				if (readPos == 0)
				{
					split["param"].push_back(options.substr(readPos, i - readPos));
				}
				else
				{
					split["param"].push_back(options.substr(readPos + 1, i - readPos - 1));
				}
				readPos = i;
			}
			else if (options[i] == '-' && !open)
			{
				readArgs = false;
				readParam = false;
				readOption = true;
				readPos = i;
			}
			else if (options[i] == ' ' && readOption == true)
			{
				actualOption = options.substr(readPos + 1, i - readPos - 1);
				split[actualOption] = {};
				readOption = false;
				readArgs = true;
				readPos = i;
			}
			else if (options[i] == ' ' && readArgs && !open)
			{
				std::string arg = options.substr(readPos + 1, i - readPos - 1);
				if (arg != "")
				{
					if (arg[0] == '\"' && arg[arg.size() - 1] == '\"')
					{
						arg = arg.substr(1, arg.size() - 2);
					}
					split[actualOption].push_back(arg);
				}
				readPos = i;
			}
			else if (options[i] == '\"' && readArgs)
			{
				open = !open;
			}
		}
		if (readParam)
		{
			split["param"].push_back(options.substr(readPos + ((readPos == 0) ? 0 : 1)));
		}
		else if (readOption)
		{
			split[options.substr(readPos + 1)] = {};
		}
		else if (readArgs)
		{
			std::string arg = options.substr(readPos + 1);
			if (arg != "")
			{
				if (arg[0] == '\"' && arg[arg.size() - 1] == '\"')
				{
					arg = arg.substr(1, arg.size() - 2);
				}
				split[actualOption].push_back(arg);
			}
		}
	}
	return split;
}

} // namespace oe
