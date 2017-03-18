#include "String.hpp"

namespace oe
{

std::map<StringId, std::string> StringHash::mStrings;

const StringId StringHash::hash(const std::string& str)
{
	StringId id = hashCalc(str, 0);
	if (mStrings.find(id) == mStrings.end())
	{
		mStrings[id] = str;
	}
	return id;
}

const std::string& StringHash::get(const StringId& id)
{
	return mStrings[id];
}

const U32 StringHash::hashCalc(const std::string& str, U32 i)
{
	return 17 * ((i != str.size()) ? hashCalc(str, i + 1) ^ char(str[i]) : 23);
}

void toLower(std::string& str)
{
}

void toUpper(std::string& str)
{
}

std::string split(std::string& base, char separator)
{
	U32 found = base.find_first_of(separator);
	if (found != std::string::npos)
	{
		std::string ret = base.substr(0, found);
		base = base.substr(found + 1);
		return ret;
	}
	return "";
}

std::string split(std::string& base, const std::string& separator)
{
	U32 found = base.find_first_of(separator);
	if (found != std::string::npos)
	{
		std::string ret = base.substr(0, found);
		base = base.substr(found + separator.size());
		return ret;
	}
	return "";
}

std::vector<std::string> splitVector(const std::string& str, char separator)
{
	std::vector<std::string> vector;
	std::string temp = str;
	U32 found;
	do
	{
		found = temp.find_first_of(separator);
		if (found != std::string::npos)
		{
			vector.push_back(temp.substr(0, found));
			temp = temp.substr(found + 1);
		}
	} while (found != std::string::npos);
	vector.push_back(temp);
	return vector;
}

std::vector<std::string> splitVector(const std::string& str, const std::string& separator)
{
	std::vector<std::string> vector;
	std::string temp = str;
	U32 found;
	U32 sepSize = separator.size();
	do
	{
		found = temp.find_first_of(separator);
		if (found != std::string::npos)
		{
			vector.push_back(temp.substr(0, found));
			temp = temp.substr(found + sepSize);
		}
	} while (found != std::string::npos);
	vector.push_back(temp);
	return vector;
}

bool contains(const std::string& str, char c)
{
	return str.find(c) != std::string::npos;
}

bool contains(const std::string& str, const std::string& c)
{
	return str.find(c) != std::string::npos;
}

std::string limitSize(const std::string& str, U32 size)
{
	if (str.size() <= size)
	{
		return str;
	}
	else
	{
		return str.substr(0, size);
	}
}

std::string toBoolString(const bool& value)
{
	return (value) ? "true" : "false";
}

bool fromBoolString(const std::string & string)
{
	if (string == "true")
	{
		return true;
	}
	else if (string == "false")
	{
		return false;
	}
	else
	{
		return fromString<bool>(string);
	}
}

} // namespace oe
