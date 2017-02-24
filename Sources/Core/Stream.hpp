#ifndef OE_STREAM_HPP
#define OE_STREAM_HPP

#include "../Config.hpp"
#include "Singleton.hpp"

namespace oe
{

class OE_API OStream
{
	public:
		OStream();
	
		virtual void write(const std::string& value) = 0;
};

class OE_API IStream
{
	public:
		IStream();

		virtual bool read(std::string& value) = 0;
};

class OE_API OConsole : public OStream
{
	public:
		OConsole();

		virtual void write(const std::string& value);

		template <typename T>
		friend OConsole& operator<<(OConsole& console, const T& value)
		{
			std::cout << value;
			return file;
		}
};

class OE_API IConsole : public IStream
{
	public:
		IConsole();

		virtual bool read(std::string& line);
};

} // namespace oe

#endif // OE_STREAM_HPP
