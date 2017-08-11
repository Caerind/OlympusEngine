#ifndef OE_ENUM_HPP
#define OE_ENUM_HPP

#include <string> // Names
#include <unordered_map> // Store names
#include <vector> // List

#include "Platform.hpp" // Types

namespace oe
{

namespace Enum
{
	template <typename Name>
	std::string extractEntry(std::string& valuesString)
	{
		std::string result;
		U32 nextCommaPos = valuesString.find(',');
		if (nextCommaPos != std::string::npos)
		{
			std::string segment = valuesString.substr(0, nextCommaPos);
			valuesString.erase(0, nextCommaPos + 1);
			result = segment.substr(0, segment.find_last_not_of(" \t") + 1).substr(segment.find_first_not_of(" \t"));
		}
		else
		{
			result = valuesString.substr(0, valuesString.find_last_not_of(" \t") + 1).substr(valuesString.find_first_not_of(" \t"));
			valuesString.clear();
		}
		return result;
	}

	template <typename Name>
	std::unordered_map<I32, std::string> makeEnumStrings(std::string enumValuesString)
	{
		std::unordered_map<I32, std::string> strings;
		I32 currentEnumValue = 0;
		U32 equalSignPos = 0;
		while (enumValuesString != "")
		{
			std::string currentEnumEntry = extractEntry<Name>(enumValuesString);
			equalSignPos = currentEnumEntry.find('=');
			if (equalSignPos != std::string::npos)
			{
				currentEnumValue = std::stoi(currentEnumEntry.substr(equalSignPos + 1));
				currentEnumEntry.erase(equalSignPos);
			}
			currentEnumEntry = currentEnumEntry.substr(0, currentEnumEntry.find_last_not_of(" \t") + 1).substr(currentEnumEntry.find_first_not_of(" \t"));
			strings[currentEnumValue] = currentEnumEntry;
			currentEnumValue++;
		}
		return strings;
	}

	template <typename Name>
	std::vector<Name> makeEnumList(std::string enumValuesString)
	{
		std::vector<Name> list;
		I32 currentEnumValue = 0;
		U32 equalSignPos = 0;
		while (enumValuesString != "")
		{
			std::string currentEnumEntry = extractEntry<Name>(enumValuesString);
			equalSignPos = currentEnumEntry.find('=');
			if (equalSignPos != std::string::npos)
			{
				currentEnumValue = std::stoi(currentEnumEntry.substr(equalSignPos + 1));
				currentEnumEntry.erase(equalSignPos);
			}
			currentEnumEntry = currentEnumEntry.substr(0, currentEnumEntry.find_last_not_of(" \t") + 1).substr(currentEnumEntry.find_first_not_of(" \t"));
			list.push_back(static_cast<Name>(currentEnumValue));
			currentEnumValue++;
		}
		return list;
	}
}

#define Enum(Name, ...) enum class Name : I32 { __VA_ARGS__ }; \
	static const std::unordered_map<I32, std::string> g##Name##Strings = oe::Enum::makeEnumStrings<Name>(#__VA_ARGS__); \
	static const std::vector<Name> g##Name##List = oe::Enum::makeEnumList<Name>(#__VA_ARGS__); \
	inline const std::string& toString(const Name& value) \
	{ \
		return g##Name##Strings.at((I32)value); \
	} \

} // namespace oe

#endif // OE_ENUM_HPP
