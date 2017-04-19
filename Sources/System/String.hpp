#ifndef OE_STRING_HPP
#define OE_STRING_HPP

#include "Prerequisites.hpp"
#include <map>
#include <vector>
#include <sstream>
#include <cstring>

namespace oe
{

using StringId = U32;

class StringHash
{
	public:
		static const StringId hash(const std::string& str);

		static const std::string& get(const StringId& id);

	private:
		static std::map<StringId, std::string> mStrings;

	private:
		static const U32 hashCalc(const std::string& str, U32 i);
};

void toLower(std::string& str);
void toUpper(std::string& str);

std::string split(std::string& base, char separator);
std::string split(std::string& base, const std::string& separator);
std::vector<std::string> splitVector(const std::string& str, char separator);
std::vector<std::string> splitVector(const std::string& str, const std::string& separator);

bool contains(const std::string& str, char c);
bool contains(const std::string& str, const std::string& c);

std::string limitSize(const std::string& str, U32 size);

std::string toBoolString(const bool& value);
bool fromBoolString(const std::string& string);

template <typename T>
std::string toString(const T& value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

template <> inline std::string toString<std::string>(const std::string& value)
{
	return value;
}

template <> inline std::string toString<bool>(const bool& value)
{
	return (value) ? "1" : "0";
}

template <> inline std::string toString<char>(const char& value)
{
	return std::string(1, value);
}

template <typename T>
T fromString(const std::string& string)
{
	T value;
	std::istringstream iss(string);
	iss >> value;
	return value;
}

template <> inline std::string fromString<std::string>(const std::string& string)
{
	return string;
}

template <> inline bool fromString<bool>(const std::string& string)
{
	if (string == "true" || string == "1")
	{
		return true;
	}
	if (string == "false" || string == "0")
	{
		return false;
	}
	bool value;
	std::istringstream iss(string);
	iss >> value;
	return value;
}

template <> inline char fromString<char>(const std::string& string)
{
	if (string.size() >= 1)
	{
		return string[0];
	}
	return '\0';
}

} // namespace oe

#endif // OE_STRING_HPP
