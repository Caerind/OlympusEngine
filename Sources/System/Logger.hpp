#ifndef OE_LOGGER_HPP
#define OE_LOGGER_HPP

#include <cstdarg>
#include <fstream>

#include "Enums.hpp"
#include "String.hpp"
#include "Version.hpp"

// TODO : Define how verbosity is used

namespace oe
{

class LogReceiver
{
	public:
		LogReceiver();
		virtual ~LogReceiver();

		void setChannelFilter(I32 channelFilter);
		I32 getChannelFilter() const;
		bool passChannelFilter(LogChannel channel) const;

		void setTypeFilter(I32 typeFilter);
		I32 getTypeFilter() const;
		bool passTypeFilter(LogType type) const;

		void setVerbosity(U32 verbosity);
		U32 getVerbosity() const;
		bool passVerbosityFilter(U32 v) const;

		virtual void onReceive(LogChannel channel, LogType type, U32 verbosity, const std::string& message) = 0;

	protected:
		void connect();
		void disconnect();

	private:
		I32 mChannelFilter;
		I32 mTypeFilter;
		U32 mVerbosity;
		bool mConnected;
};

class Logger
{
	public:
		Logger() = delete;
		~Logger() = delete;

	#if OE_BUILD_ENABLE_LOG

	public:
		static void error(LogChannel channel, U32 verbosity, const char* message, ...);
		static void warning(LogChannel channel, U32 verbosity, const char* message, ...);
		static void info(LogChannel channel, U32 verbosity, const char* message, ...);

	private:
		static void internalLog(LogChannel channel, LogType type, U32 verbosity, const char* message, va_list argList);

	private:
		friend class LogReceiver;
		static bool connectReceiver(LogReceiver* receiver);
		static bool disconnectReceiver(LogReceiver* receiver);

	private:
		static std::vector<LogReceiver*> mLogReceivers;

	#else // !OE_BUILD_ENABLE_LOG

	public:
		inline static void error(LogChannel channel, U32 verbosity, const char* message, ...) {}
		inline static void warning(LogChannel channel, U32 verbosity, const char* message, ...) {}
		inline static void info(LogChannel channel, U32 verbosity, const char* message, ...) {}
		
	#endif // OE_BUILD_ENABLE_LOG
};

// Try to only call these macros
#if OE_BUILD_ENABLE_LOG
	#define LoggerError(channel, verbosity, message, ...) Logger::error(channel, verbosity, message, __VA_ARGS__);
	#define LoggerWarning(channel, verbosity, message, ...) Logger::warning(channel, verbosity, message, __VA_ARGS__);
	#define LoggerInfo(channel, verbosity, message, ...) Logger::info(channel, verbosity, message, __VA_ARGS__);
#else
	#define LoggerError(channel, verbosity, message, ...)
	#define LoggerWarning(channel, verbosity, message, ...)
	#define LoggerInfo(channel, verbosity, message, ...)
#endif

class ConsoleLogger : public LogReceiver
{
	public:
		ConsoleLogger();
		virtual ~ConsoleLogger();

		virtual void onReceive(LogChannel channel, LogType type, U32 verbosity, const std::string& message);
};

class FileLogger : public LogReceiver
{
	public:
		FileLogger(const std::string& filename = "");
		virtual ~FileLogger();

		void setFilename(const std::string& filename);
		const std::string& getFilename() const;

		virtual void onReceive(LogChannel channel, LogType type, U32 verbosity, const std::string& message);

	private:
		std::ofstream mFile;
		std::string mFilename;
};

#if OE_COMPILER_MSVC

class VisualStudioLogger : public LogReceiver
{
	public:
		VisualStudioLogger();
		virtual ~VisualStudioLogger();

		virtual void onReceive(LogChannel channel, LogType type, U32 verbosity, const std::string& message);
};

#endif // OE_COMPILER_MSVC

} // namespace oe

#endif // OE_LOGGER_HPP