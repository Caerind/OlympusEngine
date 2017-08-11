#include "String.hpp"

#include <algorithm> // std::transform

namespace oe
{

std::map<U32, std::string> StringId::gStrings;

void toLower(std::string& string)
{
	std::transform(string.begin(), string.end(), string.begin(), ::tolower);
}

void toUpper(std::string& string)
{
	std::transform(string.begin(), string.end(), string.begin(), ::toupper);
}

void toLower(const std::string& string, std::string& result)
{
	result = string;
	toLower(result);
}

void toUpper(const std::string& string, std::string& result)
{
	result = string;
	toUpper(result);
}

bool split(std::string& base, std::string& result, char separator)
{
	U32 found = base.find_first_of(separator);
	if (found != std::string::npos)
	{
		result = base.substr(0, found);
		base = base.substr(found + 1);
		return true;
	}
	return false;
}

bool split(std::string& base, std::string& result, const std::string& separator)
{
	U32 found = base.find_first_of(separator);
	if (found != std::string::npos)
	{
		result = base.substr(0, found);
		base = base.substr(found + separator.size());
		return true;
	}
	return false;
}

bool contains(const std::string& string, char c)
{
	return string.find(c) != std::string::npos;
}

bool contains(const std::string& string, const std::string& c)
{
	return string.find(c) != std::string::npos;
}

bool limitSize(std::string& string, U32 size)
{
	if (string.size() > size)
	{
		string = string.substr(0, size);
		return true;
	}
	return false;
}

bool limitSize(const std::string& string, std::string& result, U32 size)
{
	if (string.size() > size)
	{
		result = string.substr(0, size);
		return true;
	}
	else
	{
		result = string;
		return false;
	}
}

void trimWhitespace(std::string& string)
{
	string = string.substr(0, string.find_last_not_of(" \t") + 1).substr(string.find_first_not_of(" \t"));
}

bool StringId::getString(std::string& string) const
{
	auto itr = gStrings.find(mStringId);
	if (itr != gStrings.end())
	{
		string = itr->second;
		return true;
	}
	return false;
}

U32 StringId::hash(const std::string& string, bool store)
{
	U32 h = StringId::hashRuntime(string, 0);
	if (store && gStrings.find(h) == gStrings.end())
	{
		gStrings[h] = string;
	}
	return h;
}

} // namespace oe
