#include "Logger.hpp"
#include "Date.hpp"


namespace oe
{

template <> Logger* Singleton<Logger>::mSingleton = nullptr;

LogReceiver::LogReceiver() : mConnected(false)
{
	if (!isConnected())
	{
		connect();
	}
}

LogReceiver::~LogReceiver()
{
	if (isConnected())
	{
		disconnect();
	}
}

void LogReceiver::connect()
{
	if (mConnected)
	{
		return;
	}
	if (Logger::getSingletonPtr() != nullptr)
	{
		mConnected = true;
		Logger::getSingleton().connectReceiver(this);
	}
	else
	{
		error("Can't connect LogReceiver if Logger hasn't been created");
	}
}

void LogReceiver::disconnect()
{
	if (!mConnected)
	{
		return;
	}
	if (Logger::getSingletonPtr() != nullptr)
	{
		mConnected = false;
		Logger::getSingleton().disconnectReceiver(this);
	}
	else
	{
		error("Can't disconnect LogReceiver if Logger hasn't been created");
	}
}

bool LogReceiver::isConnected() const
{
	return mConnected;
}

ConsoleLogger::ConsoleLogger()
	: LogReceiver()
{
}

ConsoleLogger::~ConsoleLogger()
{
	if (isConnected())
	{
		disconnect();
	}
}

void ConsoleLogger::onReceive(const Log& log)
{
	printf("[%s]: %s\n", log.type.c_str(), log.message.c_str());
}

FileLogger::FileLogger(const std::string& filename)
	: LogReceiver()
{
	setFilename(filename);
}

FileLogger::~FileLogger()
{
	if (isConnected())
	{
		disconnect();
	}
	mFile.close();
}

void FileLogger::setFilename(const std::string& filename)
{
	mFile.open(filename);
	if (mFile.is_open())
	{
		mFilename = filename;
	}
	else
	{
		mFilename = "";
	}
}

const std::string& FileLogger::getFilename() const
{
	return mFilename;
}

void FileLogger::onReceive(const Log& log)
{
	if (mFile.is_open())
	{
		mFile << "[" << log.date << "][" << log.type << "]: " << log.message << "\n";
		mFile.flush();
	}
}

Logger::Logger()
	: mConsoleLogger(nullptr)
	, mFileLogger(nullptr)
{
}

Logger::~Logger()
{
	if (mConsoleLogger != nullptr)
	{
		delete mConsoleLogger;
	}
	if (mFileLogger != nullptr)
	{
		delete mFileLogger;
	}
}

Logger& Logger::getSingleton()
{
	ASSERT(mSingleton != nullptr);
	return *mSingleton;
}

Logger* Logger::getSingletonPtr()
{
	return mSingleton;
}

std::string Logger::stringFromType(Type type)
{
	switch (type)
	{
		case Type::Error:
			return "ERROR";
			break;
		case Type::Warning:
			return "WARNING";
			break;
		case Type::Info:
		default:
			break;
	}
	return "INFO";
}

void Logger::log(const std::string& message, Type type)
{
	std::string dateString = Date().toString();
	std::string typeString = stringFromType(type);

	mLogs.emplace_back(dateString, typeString, message);

	for (LogReceiver* receiver : mLogReceivers)
	{
		if (receiver != nullptr)
		{
			receiver->onReceive(mLogs.back());
		}
	}
}

void Logger::info(const std::string& message)
{
	log(message, Type::Info);
}

void Logger::warning(const std::string& message)
{
	log(message, Type::Warning);
}

void Logger::error(const std::string& message)
{
	log(message, Type::Error);
}

void Logger::connectReceiver(LogReceiver* receiver)
{
	if (receiver == nullptr)
	{
		return;
	}
	bool found = false;
	for (U32 i = 0; i < mLogReceivers.size(); i++)
	{
		if (mLogReceivers[i] == receiver)
		{
			found = true;
		}
	}
	if (!found)
	{
		for (const auto& log : mLogs)
		{
			receiver->onReceive(log);
		}
		mLogReceivers.push_back(receiver);
	}
}

void Logger::disconnectReceiver(LogReceiver* receiver)
{
	for (auto itr = mLogReceivers.begin(); itr != mLogReceivers.end(); ++itr)
	{
		if (receiver == *itr)
		{
			mLogReceivers.erase(itr);
			return;
		}
	}
}

void Logger::useConsoleLogger(bool consoleLogger)
{
	if (mConsoleLogger == nullptr && consoleLogger)
	{
		mConsoleLogger = new ConsoleLogger();
	}
	else if (mConsoleLogger != nullptr && !consoleLogger)
	{
		delete mConsoleLogger;
		mConsoleLogger = nullptr;
	}
}

void Logger::useFileLogger(const std::string& filename)
{
	if (mFileLogger == nullptr && filename.size() > 0)
	{
		mFileLogger = new FileLogger(filename);
	}
	else if (mFileLogger != nullptr && filename.size() == 0)
	{
		delete mFileLogger;
		mFileLogger = nullptr;
	}
}

void log(const std::string& message, Logger::Type type)
{
	if (Logger::getSingletonPtr() != nullptr)
	{
		Logger::getSingleton().log(message, type);
	}
	else
	{
		printf("[%s]: %s\n", Logger::stringFromType(type).c_str(), message.c_str());
	}
}

void info(const std::string& message)
{
	oe::log(message, Logger::Type::Info);
}

void warning(const std::string& message)
{
	oe::log(message, Logger::Type::Warning);
}

void error(const std::string& message)
{
	oe::log(message, Logger::Type::Error);
}

} // namespace oe
