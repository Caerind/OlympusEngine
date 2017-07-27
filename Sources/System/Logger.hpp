#ifndef OE_LOG_HPP
#define OE_LOG_HPP

#include <fstream>

#include "Prerequisites.hpp"
#include "Singleton.hpp"

namespace oe
{

struct Log
{
	Log(const std::string& pDate, const std::string& pType, const std::string& pMessage) : date(pDate), type(pType), message(pMessage) {}

	std::string date;
	std::string type;
	std::string message;
};

class LogReceiver
{	
	public:
		LogReceiver();
		virtual ~LogReceiver();

		void connect();
		void disconnect();
		bool isConnected() const;

		virtual void onReceive(const Log& log) = 0;

	private:
		bool mConnected;
};

class ConsoleLogger : public LogReceiver
{
	public:
		ConsoleLogger();
		virtual ~ConsoleLogger();

		virtual void onReceive(const Log& log);
};

class FileLogger : public LogReceiver
{
	public:
		FileLogger(const std::string& filename = "");
		virtual ~FileLogger();

		void setFilename(const std::string& filename);
		const std::string& getFilename() const;

		virtual void onReceive(const Log& log);

	private:
		std::ofstream mFile;
		std::string mFilename;
};

class Logger : public Singleton<Logger>
{
	public:
		enum Type
		{
			Info,
			Warning,
			Error
		};

		Logger();
		~Logger();

		static Logger& getSingleton();
		static Logger* getSingletonPtr();

		static std::string stringFromType(Type type);

		void log(const std::string& message, Type type = Type::Info);
		void info(const std::string& message);
		void warning(const std::string& message);
		void error(const std::string& message);

		void connectReceiver(LogReceiver* receiver);
		void disconnectReceiver(LogReceiver* receiver);

		void useConsoleLogger(bool consoleLogger = true);
		void useFileLogger(const std::string& filename); // "" = false, else true

	private:
		std::vector<Log> mLogs;
		std::vector<LogReceiver*> mLogReceivers;

		ConsoleLogger* mConsoleLogger;
		FileLogger* mFileLogger;
};

void log(const std::string& message, Logger::Type type = Logger::Type::Info);
void info(const std::string& message);
void warning(const std::string& message);
void error(const std::string& message);

} // namespace oe

#endif // OE_LOGGER_HPP
