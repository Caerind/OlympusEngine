#ifndef OE_STRING_HPP
#define OE_STRING_HPP

#include "Macros.hpp"

#include <map>
#include <sstream>
#include <string>

namespace oe
{

void toLower(std::string& string);
void toUpper(std::string& string);
void toLower(const std::string& string, std::string& result);
void toUpper(const std::string& string, std::string& result);

bool split(std::string& base, std::string& result, char separator);
bool split(std::string& base, std::string& result, const std::string& separator);

bool contains(const std::string& string, char c);
bool contains(const std::string& string, const std::string& c);

bool limitSize(std::string& string, U32 size);
bool limitSize(const std::string& string, std::string& result, U32 size);

void trimWhitespace(std::string& string);

inline bool empty(const std::string& string) { return string.size() == 0; } // Faster than the std::string::empty

inline std::string toBoolString(bool value) { return (value) ? "true" : "false"; }

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
	return false;
}

template <> inline char fromString<char>(const std::string& string)
{
	if (string.size() >= 1)
	{
		return string[0];
	}
	return '\0';
}

class StringId
{
	public:
		inline StringId() : mStringId(InvalidU32) { }
		inline StringId(U32 stringId) : mStringId(stringId) { }
		inline StringId(const StringId& stringId) : mStringId(stringId.mStringId) { }
		inline StringId(StringId&& stringId) : mStringId(stringId.mStringId) { stringId.mStringId = InvalidU32; }

		inline StringId& operator=(U32 stringId) { mStringId = stringId; return *this; }
		inline StringId& operator=(const StringId& stringId) { mStringId = stringId.mStringId; return *this; }
		inline StringId& operator=(StringId&& stringId) { if (this != &stringId) { mStringId = stringId.mStringId; stringId.mStringId = InvalidU32; } return *this; }

		inline bool operator==(U32 stringId) const { return mStringId == stringId; }
		inline bool operator==(const StringId& stringId) const { return mStringId == stringId.mStringId; }

		inline bool operator!=(U32 stringId) const { return !operator==(stringId); }
		inline bool operator!=(const StringId& stringId) const { return !operator==(stringId); }

		inline operator bool() const { return mStringId != InvalidU32; }
		inline bool isValid() const { return mStringId != InvalidU32; }
		inline bool isStored() const { return gStrings.find(mStringId) != gStrings.end(); }

		bool getString(std::string& string) const;

		static U32 hash(const std::string& string, bool store = false);
		inline static U32 hashRuntime(const std::string& string, U32 i = 0) { return 17 * ((i != string.size()) ? hashRuntime(string, i + 1) ^ char(string[i]) : 23); }
		template <U32 N> inline static constexpr U32 hashCompile(const char(&string)[N]) { return hashCompil<N>::apply(string); }

	private:
		template <U32 N, U32 I = 0>
		struct hashCompil
		{
			static constexpr U32 apply(const char(&s)[N]) { return (hashCompil<N, I + 1>::apply(s) ^ s[I]) * 17; };
		};

		template <U32 N>
		struct hashCompil<N, N>
		{
			static constexpr U32 apply(const char(&s)[N]) { return 23; };
		};

	private:
		static std::map<U32, std::string> gStrings;

	private:
		U32 mStringId;
};

inline bool operator==(U32 id, const StringId& stringId)
{
	return stringId == id;
}

} // namespace oe

#endif // OE_STRING_HPP