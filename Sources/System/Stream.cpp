#include "Stream.hpp"
#include <iostream>

namespace oe
{

OStream::OStream()
{
}

IStream::IStream()
{
}

OConsole::OConsole()
{
}

void OConsole::write(const std::string& value)
{
	printf("%s", value.c_str());
}

IConsole::IConsole()
{
}

bool IConsole::read(std::string& line)
{
	return static_cast<bool>(std::getline(std::cin, line));
}

} // namespace oe
