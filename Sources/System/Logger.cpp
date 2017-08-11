#include "Logger.hpp"

#if OE_COMPILER_MSVC
	#include <windows.h>
#endif

namespace oe
{

LogReceiver::LogReceiver()
	: mChannelFilter((I32)LogChannel::All)
	, mTypeFilter((I32)LogType::All)
	, mVerbosity(100)
	, mConnected(false)
{
	connect();
}

LogReceiver::~LogReceiver()
{
	disconnect();
}

void LogReceiver::setChannelFilter(I32 channelFilter)
{
	mChannelFilter = channelFilter;
}

I32 LogReceiver::getChannelFilter() const
{
	return mChannelFilter;
}

bool LogReceiver::passChannelFilter(LogChannel channel) const
{
	return (mChannelFilter == (I32)LogType::All) || (((I32)channel & mChannelFilter) != 0);
}

void LogReceiver::setTypeFilter(I32 typeFilter)
{
	mTypeFilter = typeFilter;
}

I32 LogReceiver::getTypeFilter() const
{
	return mTypeFilter;
}

bool LogReceiver::passTypeFilter(LogType type) const
{
	return (mTypeFilter == (I32)LogType::All) || (((I32)type & mTypeFilter) != 0);
}

void LogReceiver::setVerbosity(U32 verbosity)
{
	mVerbosity = verbosity;
}

U32 LogReceiver::getVerbosity() const
{
	return mVerbosity;
}

bool LogReceiver::passVerbosityFilter(U32 v) const
{
	return mVerbosity >= v;
}

void LogReceiver::connect()
{
	#if OE_BUILD_ENABLE_LOG
	if (!mConnected && Logger::connectReceiver(this))
	{
		mConnected = true;
	}
	else
	{
		LoggerWarning(LogChannel::System, 2, "LogReceiver connection"); // TODO : Update verbosity
	}
	#endif
}

void LogReceiver::disconnect()
{
	#if OE_BUILD_ENABLE_LOG
	if (mConnected && Logger::disconnectReceiver(this))
	{
		mConnected = false;
	}
	else
	{
		LoggerWarning(LogChannel::System, 2, "LogReceiver disconnection"); // TODO : Update verbosity
	}
	#endif
}


#if OE_BUILD_ENABLE_LOG

std::vector<LogReceiver*> Logger::mLogReceivers;

void Logger::error(LogChannel channel, U32 verbosity, const char* message, ...)
{
	va_list argList;
	va_start(argList, message);
	internalLog(channel, LogType::Error, verbosity, message, argList);
	va_end(argList);
}

void Logger::warning(LogChannel channel, U32 verbosity, const char* message, ...)
{
	va_list argList;
	va_start(argList, message);
	internalLog(channel, LogType::Warning, verbosity, message, argList);
	va_end(argList);
}

void Logger::info(LogChannel channel, U32 verbosity, const char* message, ...)
{
	va_list argList;
	va_start(argList, message);
	internalLog(channel, LogType::Info, verbosity, message, argList);
	va_end(argList);
}

void Logger::internalLog(LogChannel channel, LogType type, U32 verbosity, const char* message, va_list argList)
{
	static const U32 mBufferSize = 256;
	static char mBuffer[mBufferSize];

	std::string output;
	U32 size = std::vsnprintf(mBuffer, mBufferSize, message, argList);
	if (size < mBufferSize)
	{
		output = { mBuffer, size };
	}
	else
	{
		output = { mBuffer, mBufferSize };
	}

	if (mLogReceivers.size() > 0)
	{
		for (const auto& receiver : mLogReceivers)
		{
			if (receiver->passChannelFilter(channel) && receiver->passTypeFilter(type) && receiver->passVerbosityFilter(verbosity))
			{
				receiver->onReceive(channel, type, verbosity, output);
			}
		}
	}
	else
	{
		printf("[%s][%s][V=%d] %s\n", logChannelToString(channel), logTypeToString(type), verbosity, output.c_str());
	}
}

bool Logger::connectReceiver(LogReceiver* receiver)
{
	mLogReceivers.push_back(receiver);
	return true;
}

bool Logger::disconnectReceiver(LogReceiver* receiver)
{
	U32 size = mLogReceivers.size();
	for (U32 i = 0; i < size; i++)
	{
		if (mLogReceivers[i] == receiver)
		{
			mLogReceivers.erase(mLogReceivers.begin() + i);
			return true;
		}
	}
	return false;
}

#endif // OE_BUILD_ENABLE_LOG

ConsoleLogger::ConsoleLogger()
	: LogReceiver()
{
}

ConsoleLogger::~ConsoleLogger()
{
	disconnect();
}

void ConsoleLogger::onReceive(LogChannel channel, LogType type, U32 verbosity, const std::string& message)
{
	printf("[%s][%s][V=%d] %s\n", logChannelToString(channel), logTypeToString(type), verbosity, message.c_str());
}

FileLogger::FileLogger(const std::string& filename)
	: LogReceiver()
{
	setFilename(filename);
}

FileLogger::~FileLogger()
{
	disconnect();
}

void FileLogger::setFilename(const std::string& filename)
{
	if (!empty(filename))
	{
		if (mFile.is_open())
		{
			mFile.close();
		}

		mFile.open(filename);

		if (mFile.is_open())
		{
			mFilename = filename;
		}
		else
		{
			mFilename.clear();
		}
	}
}

const std::string& FileLogger::getFilename() const
{
	return mFilename;
}

void FileLogger::onReceive(LogChannel channel, LogType type, U32 verbosity, const std::string& message)
{
	if (mFile.is_open())
	{
		mFile << "[" << logChannelToString(channel) << "][" << logTypeToString(type) << "][V=" << verbosity << "] " << message << '\n';
		mFile.flush();
	}
}

#if OE_COMPILER_MSVC

VisualStudioLogger::VisualStudioLogger()
	: LogReceiver()
{
}

VisualStudioLogger::~VisualStudioLogger()
{
	disconnect();
}

void VisualStudioLogger::onReceive(LogChannel channel, LogType type, U32 verbosity, const std::string& message)
{
	static const U32 mDebugBufferSize = 256;
	static char mDebugBuffer[mDebugBufferSize];

	U32 size = sprintf_s(mDebugBuffer, "[%s][%s][V=%d] %s\n", logChannelToString(channel), logTypeToString(type), verbosity, message.c_str());

	printf("t ?");

	OutputDebugStringA(mDebugBuffer);
}

#endif // OE_COMPILER_MSVC

} // namespace oe
