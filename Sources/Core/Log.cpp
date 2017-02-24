#include "Log.hpp"
#include "Date.hpp"
#include <iostream>

namespace oe
{

template <> Log* Singleton<Log>::mSingleton = nullptr;

Log::Log()
	: mUseConsole(true)
	, mUseFile(false)
{
}

Log::~Log()
{
}

Log& Log::getSingleton()
{
	ASSERT(mSingleton != nullptr);
	return *mSingleton;
}

Log* Log::getSingletonPtr()
{
	return mSingleton;
}

void Log::useConsole(bool use)
{
	mUseConsole = use;
}

void Log::useFile(bool use, const std::string& filename)
{
	mUseFile = false;
	mFile.close();
	if (use && !filename.empty())
	{
		mFile.open(filename);
		if (mFile.isOpen())
		{
			mUseFile = true;
		}
		else
		{
			warning("Can't open log file ! " + filename);
		}
	}
}

std::string Log::stringFromType(Type type)
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

void Log::log(const std::string& message, Type type)
{
	std::string typeString = stringFromType(type);

	// Console
	if (mUseConsole)
	{
		printf("[%s]: %s\n", typeString.c_str(), message.c_str());
	}

	// File
	if (mUseFile && mFile.isOpen())
	{
		Date currentDate;
		mFile << "[" << currentDate.toString() << "][" << typeString << "]: " << message << "\n";
	}
}

void Log::info(const std::string& message)
{
	log(message, Type::Info);
}

void Log::warning(const std::string& message)
{
	log(message, Type::Warning);
}

void Log::error(const std::string& message)
{
	log(message, Type::Error);
}

void log(const std::string& message, Log::Type type)
{
	if (Log::getSingletonPtr() != nullptr)
	{
		Log::getSingleton().log(message, type);
	}
	else
	{
		printf("[%s]: %s\n", Log::stringFromType(type).c_str(), message.c_str());
	}
}

void info(const std::string& message)
{
	oe::log(message, Log::Type::Info);
}

void warning(const std::string& message)
{
	oe::log(message, Log::Type::Warning);
}

void error(const std::string& message)
{
	oe::log(message, Log::Type::Error);
}

} // namespace oe
