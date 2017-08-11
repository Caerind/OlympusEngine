#ifndef OE_ENUMS_HPP
#define OE_ENUMS_HPP

#include "Enum.hpp" // Enum

namespace oe
{

// Platforms
Enum(Platform, Unknown = -1, Android, iOS, macOS, Linux, Windows);

inline constexpr Platform getPlatform()
{
	#ifdef OE_PLATFORM_ANDROID
		return Platform::Android;
	#elif defined OE_PLATFORM_IOS
		return Platform::iOS;
	#elif defined OE_PLATFORM_MACOS
		return Platform::macOS;
	#elif defined OE_PLATFORM_LINUX
		return Platform::Linux;
	#elif defined OE_PLATFORM_WINDOWS
		return Platform::Windows;
	#else
		#error Unknown platform
	#endif
}

// Compilers
Enum(Compiler, Unknown = -1, clang, gcc, intel, msvc);

inline constexpr Compiler getCompiler()
{
	#ifdef OE_COMPILER_CLANG
		return Compiler::clang;
	#elif defined OE_COMPILER_GCC
		return Compiler::gcc;
	#elif defined OE_COMPILER_INTEL
		return Compiler::intel;
	#elif defined OE_COMPILER_MSVC
		return Compiler::msvc;
	#else
		#error Unknown compiler
	#endif
}

// Endianness
Enum(Endianness, Unknown = -1, BigEndian, LittleEndian);

inline constexpr Endianness getEndianness()
{
	#ifdef OE_ARCH_ENDIAN_BIG
		return Endianness::BigEndian;
	#elif defined OE_ARCH_ENDIAN_LITTLE
		return Endianness::LittleEndian;
	#else
		#error Unknown endianness
	#endif
}

// Build
Enum(Build, Debug, Release, Profile, Deploy);

inline constexpr Build getBuild()
{
	#ifdef OE_BUILD_DEBUG
		return Build::Debug;
	#elif defined OE_BUILD_RELEASE
		return Build::Release;
	#elif defined OE_BUILD_PROFILE
		return Build::Profile;
	#elif defined OE_BUILD_DEPLOY
		return Build::Deploy;
	#else
		#error Unknown build
	#endif
}

// LogChannel
enum class LogChannel : I32 { Global = 0, System = 1 << 1, Math = 1 << 2, All = 1};
static const char* const gLogChannelStrings[] = { "Global", "System", "Math" };
inline const char* logChannelToString(LogChannel channel)
{
	switch (channel)
	{
		case LogChannel::System: return gLogChannelStrings[1];
		case LogChannel::Math: return gLogChannelStrings[2];
	}
	return gLogChannelStrings[0];
}

// LogType
enum class LogType : I32 { None = 0, Info = 1 << 1, Error = 1 << 2, Warning = 1 << 3, All = 1};
static const char* const gLogTypeStrings[] = { "None", "Info", "Error", "Warning" };
inline const char* logTypeToString(LogType type)
{
	switch (type)
	{
		case LogType::Info: return gLogTypeStrings[1];
		case LogType::Error: return gLogTypeStrings[2];
		case LogType::Warning: return gLogTypeStrings[3];
	}
	return gLogTypeStrings[0];
}

// ErrorType
Enum(ErrorType, Error, Warning, Deprecated, InternalError, SilentError);

// Prefix
Enum(Prefix, Unspecified = -1, Pico, Nano, Micro, Milli, Centi, Deci, Unit, Deca, Hecto, Kilo, Mega, Giga, Tera, Peta, Twice, Thrice, Semi, Half, Quarter);

// TimeUnit
Enum(TimeUnit, Unspecified = -1, Nanosecond, Microsecond, Millisecond, Tick, Second, Minute, Hour, Day, Week, Year, Century, Millennium);

// LengthUnit
Enum(LengthUnit, Unspecified = -1, Meter, Kilometer, Inch, Foot, Yard, Mile, NauticalMile, AstronomicalUnit);

// MassUnit
Enum(MassUnit, Unspecified = -1, Gram, Kilogram, Slug);





} // namespace oe

#endif // OE_ENUMS_HPP
