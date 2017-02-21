#ifndef OE_CONFIG_HPP
#define OE_CONFIG_HPP

////////////////////////////////////////////////////
// Version
////////////////////////////////////////////////////
#define OE_VERSION_MAJOR 0
#define OE_VERSION_MINOR 1

////////////////////////////////////////////////////
// Debug
////////////////////////////////////////////////////
#if !(defined(NDEBUG) || defined(_NDEBUG))
	#define OE_DEBUG
#endif

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

#include <string>

namespace oe
{

// TODO : Move to another file
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

#ifdef OE_DYNAMIC
	#if OE_PLATFORM_WINDOWS
		#ifdef OE_EXPORTS
			#define OE_API __declspec(dllexport)
		#else
			#define OE_API __declspec(dllimport)
		#endif
	#else
		#if __GNUC__ >= 4
			#define OE_API __attribute__((__visibility__("default")))
		#else
			#define OE_API
		#endif
	#endif
#else
	#define OE_API
#endif

////////////////////////////////////////////////////
// Assertions
////////////////////////////////////////////////////
#include <cstdio>
#if !(defined(NASSERT) || defined(_NASSERT))
#define ASSERT(expr) \
	if (expr) {} \
	else \
	{ \
		printf("Assertion !\n Expr : %s\n File : %s\n Line : %d\n", #expr, __FILE__, __LINE__); \
		for (;;) {} \
	}
#else
#define ASSERT(expr)
#endif

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


#include <sstream>

#endif // OE_CONFIG_HPP