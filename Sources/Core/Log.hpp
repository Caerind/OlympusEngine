#ifndef OE_LOG_HPP
#define OE_LOG_HPP

#include "Prerequisites.hpp"
#include "Singleton.hpp"
#include "File.hpp"

namespace oe
{

class Log : public Singleton<Log>
{
	public:
		enum Type
		{
			Info,
			Warning,
			Error
		};

		Log();
		~Log();

		static Log& getSingleton();
		static Log* getSingletonPtr();

		void useConsole(bool use);
		void useFile(bool use, const std::string& filename = "output.log");

		static std::string stringFromType(Type type);

		void log(const std::string& message, Type type = Type::Info);
		void info(const std::string& message);
		void warning(const std::string& message);
		void error(const std::string& message);

	private:
		bool mUseConsole;
		bool mUseFile;
		OFile mFile;
};

void log(const std::string& message, Log::Type type = Log::Type::Info);
void info(const std::string& message);
void warning(const std::string& message);
void error(const std::string& message);

} // namespace oe

#endif // OE_LOG_HPP
