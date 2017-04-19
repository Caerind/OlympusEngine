#ifndef OE_STREAM_HPP
#define OE_STREAM_HPP

#include "Prerequisites.hpp"
#include "Singleton.hpp"

#include <iostream>

namespace oe
{

class OStream
{
	public:
		OStream();

		virtual void write(const std::string& value) = 0;
};

class IStream
{
	public:
		IStream();

		virtual bool read(std::string& value) = 0;
};

class OConsole : public OStream
{
	public:
		OConsole();

		virtual void write(const std::string& value);

		template <typename T>
		friend OConsole& operator<<(OConsole& console, const T& value)
		{
			std::cout << value;
			return console;
		}
};

class IConsole : public IStream
{
	public:
		IConsole();

		virtual bool read(std::string& line);
};

} // namespace oe

#endif // OE_STREAM_HPP
