#ifndef OE_PLATFORM_HPP
#define OE_PLATFORM_HPP

////////////////////////////////////////////////////
// Platform Detection
////////////////////////////////////////////////////
#if defined(_WIN32) 
	#define OE_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
#elif defined(__APPLE__) && defined(__MACH__)
	#include "TargetConditionnals.h"
	#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
		#define OE_PLATFORM_IOS
	#elif TARGET_OS_MAC
		#define OE_PLATFORM_MACOS
	#else
		#error Unknown Apple Platform
	#endif
#elif defined(__unix__)
	#if defined(__ANDROID__)
		#define OE_PLATFORM_ANDROID
	#elif defined(__linux__)
		#define OE_PLATFORM_LINUX
	#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
		#define OE_PLATFORM_FREEBSD
	#else
		#error Unknown Unix Platform
	#endif
#else 
	#error Unknown Platform
#endif

#if defined(PLATFORM_IOS) || defined(PLATFORM_ANDROID)
	#define OE_MOBILE
#else
	#define OE_DESKTOP
#endif


////////////////////////////////////////////////////
// Platform Name
////////////////////////////////////////////////////

#include <string>

namespace oe
{

inline const std::string& getPlatformName()
{
	#if defined(OE_PLATFORM_WINDOWS)
		static const std::string platformString("Windows");
	#elif defined(OE_PLATFORM_IOS)
		static const std::string platformString("iOS");
	#elif defined(OE_PLATFORM_MACOS)
		static const std::string platformString("MacOS");
	#elif defined(OE_PLATFORM_ANDROID)
		static const std::string platformString("Android");
	#elif defined(OE_PLATFORM_LINUX)
		static const std::string platformString("Linux");
	#elif defined(OE_PLATFORM_FREEBSD)
		static const std::string platformString("FreeBSD");
	#else
		static const std::string platformString("Unknown");
	#endif
	return platformString;
}

} // namespace oe


////////////////////////////////////////////////////
// Atomic Data Types
////////////////////////////////////////////////////
using I8 = signed char;
using U8 = unsigned char;
using I16 = signed short;
using U16 = unsigned short;
using I32 = signed int;
using U32 = unsigned int;
using I64 = signed long long;
using U64 = unsigned long long;
using F32 = float;

#endif // OE_PLATFORM_HPP