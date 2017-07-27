#ifndef OE_HASH_HPP
#define OE_HASH_HPP

#include "String.hpp"

namespace oe
{

using StringId = U32;

// Hash running time
inline const StringId hash(const std::string& str, U32 i = 0)
{
	return 17 * ((i != str.size()) ? hash(str, i + 1) ^ char(str[i]) : 23);
}

class StringHash
{
	public:
		static const StringId hash(const std::string& str)
		{
			StringId id = oe::hash(str, 0);
			std::map<StringId, std::string>& strings = getStrings();
			if (strings.find(id) == strings.end())
			{
				strings[id] = str;
			}
			return id;
		}

		static const std::string& get(const StringId& id)
		{
			return getStrings()[id];
		}

	private:
		static std::map<StringId, std::string>& getStrings()
		{
			static std::map<StringId, std::string> mStrings;
			return mStrings;
		}
};

// Hash compile time
namespace priv
{

template<unsigned int N, unsigned int I = 0>
struct hash_calc
{
	static constexpr StringId apply(const char(&s)[N])
	{
		return (hash_calc<N, I + 1>::apply(s) ^ s[I]) * 17;
	};
};

template<unsigned int N>
struct hash_calc<N, N>
{
	static constexpr StringId apply(const char(&s)[N])
	{
		return 23;
	};
};

} // namespace priv

template<unsigned int N>
constexpr StringId hashCompile(const char(&s)[N])
{
	return priv::hash_calc<N>::apply(s);
}

} // namespace oe

#endif // OE_HASH_HPP