#ifndef OE_VERSION_HPP
#define OE_VERSION_HPP

#include "Macros.hpp" // Preprocessor

#define OE_VERSION_MAJOR 0
#define OE_VERSION_MINOR 3
#define OE_VERSION_PATCH 0
#define OE_VERSION_NAME OE_PREPROCESSOR_TOSTRING(OE_VERSION_MAJOR) "." OE_PREPROCESSOR_TOSTRING(OE_VERSION_MINOR) "." OE_PREPROCESSOR_TOSTRING(OE_VERSION_PATCH)

namespace oe
{

struct Version
{
	inline constexpr Version() 
		: major(OE_VERSION_MAJOR)
		, minor(OE_VERSION_MINOR)
		, patch(OE_VERSION_PATCH) 
	{
	}

	inline Version(U8 pMajor, U8 pMinor, U8 pPatch) 
		: major(pMajor)
		, minor(pMinor)
		, patch(pPatch) 
	{
	}

	U8 major;
	U8 minor;
	U8 patch;

	static inline constexpr const char* getName() 
	{ 
		return OE_VERSION_NAME; 
	}
};

inline bool operator==(const Version& v, const Version& version)
{
	return v.major == version.major && v.minor == version.minor && v.patch == version.patch;
}

inline bool operator!=(const Version& v, const Version& version)
{
	return !operator==(v, version);
}

inline bool operator<(const Version& v, const Version& version)
{
	if (v.major < version.major)
	{
		return true;
	}
	else if (v.major == version.major)
	{
		if (v.minor < version.minor)
		{
			return true;
		}
		else if (v.minor == version.minor)
		{
			return v.patch < version.patch;
		}
	}
	return false;
}

inline bool operator<=(const Version& v, const Version& version)
{
	return operator<(v, version) || operator==(v, version);
}

inline bool operator>(const Version& v, const Version& version)
{
	return !operator<=(v, version);
}

inline bool operator>=(const Version& v, const Version& version)
{
	return !operator<(v, version);
}

} // namespace oe

#endif // OE_VERSION_HPP
