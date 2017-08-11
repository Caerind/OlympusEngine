#ifndef OE_PLATFORM_HPP
#define OE_PLATFORM_HPP

// Android
#if defined(__ANDROID__)
	#define OE_PLATFORM_ANDROID 1
	#define OE_PLATFORM_POSIX 1
	#define OE_PLATFORM_NAME "Android"
    #define OE_PLATFORM_MOBILE 1

// macOS and iOS
#elif (defined(__APPLE__) && __APPLE__)
	#define OE_PLATFORM_APPLE 1
	#define OE_PLATFORM_POSIX 1
	#include <TargetConditionals.h>
	#if defined(__IPHONE__) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE) || (defined(TARGET_IPHONE_SIMULATOR) && TARGET_IPHONE_SIMULATOR)
		#define OE_PLATFORM_IOS 1
		#define OE_PLATFORM_NAME "iOS"
		#define OE_PLATFORM_MOBILE 1
	#elif defined(__MACH__)
		#define OE_PLATFORM_MACOS 1
		#define OE_PLATFORM_NAME "macOS"
		#define OE_PLATFORM_DESKTOP 1
	#else
		#error Unknown Apple Platform
	#endif

// Linux
#elif (defined(__linux__) || defined(__linux))
	#define OE_PLATFORM_LINUX 1
	#define OE_PLATFORM_POSIX 1
	#define OE_PLATFORM_NAME "Linux"
	#define OE_PLATFORM_DESKTOP 1
	#if defined(__raspberrypi__)
		#define OE_PLATFORM_LINUX_RASPBERRYPI 1
	#endif

// Windows
#elif defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
	#define OE_PLATFORM_WINDOWS 1
	#define OE_PLATFORM_NAME "Windows"
	#define OE_PLATFORM_DESKTOP 1

	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN 1
	#endif

// Unknown
#else
	#error Unknown platform
#endif


// Architecture details
#ifdef __SSE2__
	#define OE_ARCH_SSE2 1
#endif
#ifdef __SSE3__
	#define OE_ARCH_SSE3 1
#endif
#ifdef __SSE4_1__
	#define OE_ARCH_SSE4 1
#endif
#ifdef __ARM_NEON__
	#define OE_ARCH_NEON 1
#endif
#ifdef __thumb__
	#define OE_ARCH_THUMB 1
#endif


// Endian
#if !defined(OE_ARCH_ENDIAN_BIG) && !defined(OE_ARCH_ENDIAN_LITTLE)
	#if defined(__m68k__) || defined(mc68000) || defined(_M_M68K) || (defined(__MIPS__) && defined(__MISPEB__)) || \
			defined(__ppc__) || defined(__POWERPC__) || defined(_M_PPC) || defined(__sparc__) || defined(__hppa__)
		#define OE_ARCH_ENDIAN_BIG 1
	#elif defined(__i386__) || defined(__i386) || defined(__X86__) || defined (__x86_64) || defined(_M_I86) || \
			defined(_M_IX86) || defined(_M_X64)
		#define OE_ARCH_ENDIAN_LITTLE
	#else
		#error Failed to identify endianness, you must define either OE_ARCH_ENDIAN_LITTLE or OE_ARCH_ENDIAN_BIG
	#endif
#elif defined(OE_ARCH_ENDIAN_BIG) && defined(OE_ARCH_ENDIAN_BIG)
	#error You cannot define both OE_ARCH_ENDIAN_LITTLE and OE_ARCH_ENDIAN_BIG
#endif


// Clang
#ifdef __clang__ 
	#define OE_COMPILER_CLANG 1
	#define OE_COMPILER_NAME "clang"
	#define OE_COMPILER_DESCRIPTION OE_COMPILER_NAME " " OE_PREPROCESSOR_TOSTRING(__clang_major__) "." OE_PREPROCESSOR_TOSTRING(__clang_minor__)
	#define OE_COMPILER_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)

// GCC
#elif defined(__GNUC__)
	#define OE_COMPILER_GCC 1
	#define OE_COMPILER_NAME "gcc"
	#define OE_COMPILER_DESCRIPTION OE_COMPILER_NAME " " OE_PREPROCESSOR_TOSTRING(__GNUC__) "." OE_PREPROCESSOR_TOSTRING(__GNUC_MINOR__)
	#define OE_COMPILER_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

// Intel
#elif defined(__ICL ) || defined(__ICC ) || defined(__INTEL_COMPILER)
	#define OE_COMPILER_INTEL 1
	#define OE_COMPILER_NAME "intel"
	#if defined(__ICL)
		#define OE_COMPILER_DESCRIPTION OE_COMPILER_NAME " " OE_PREPROCESSOR_TOSTRING(__ICL)
		#define OE_COMPILER_VERSION OE_PREPROCESSOR_TOSTRING(__ICL)
	#elif defined(__ICC)
		#define OE_COMPILER_DESCRIPTION OE_COMPILER_NAME " " OE_PREPROCESSOR_TOSTRING(__ICC)
		#define OE_COMPILER_VERSION OE_PREPROCESSOR_TOSTRING(__ICC)
	#endif
	#include <intrin.h>

// Microsoft
#elif defined(_MSC_VER)
	#define OE_COMPILER_MSVC 1
	#define OE_COMPILER_NAME "msvc"
	#define OE_COMPILER_DESCRIPTION OE_COMPILER_NAME " " OE_PREPROCESSOR_TOSTRING(_MSC_VER)
	#define OE_COMPILER_VERSION OE_PREPROCESSOR_TOSTRING(_MSC_VER)
	#include <intrin.h>

// Unknown
#else
	#warning Unknown compiler
	#define OE_COMPILER_NAME "unknown"
	#define OE_COMPILER_DESCRIPTION "unknown"
#endif



//Export/import attribute
#if OE_BUILD_DYNAMIC_LINK && OE_PLATFORM_WINDOWS
	#define OE_EXPORT_LINK __declspec(dllexport)
	#define OE_IMPORT_LINK __declspec(dllimport)
#else
	#define OE_EXPORT_LINK
	#define OE_IMPORT_LINK
#endif


// Builds
#if !defined(OE_BUILD_DEBUG) && !defined(OE_BUILD_RELEASE) && !defined(OE_BUILD_PROFILE) && !defined(OE_BUILD_DEPLOY)
	#ifdef NDEBUG
		#define OE_BUILD_RELEASE 1
	#else
		#define OE_BUILD_DEBUG 1
	#endif
#endif

// Configurable choices
#if !defined(OE_BUILD_ENABLE_ASSERT) && (defined(OE_BUILD_DEBUG) || defined(OE_BUILD_RELEASE))
	#define OE_BUILD_ENABLE_ASSERT 1
#else
	#define OE_BUILD_ENABLE_ASSERT 0
#endif

#if !defined(OE_BUILD_ENABLE_LOG) && (defined(OE_BUILD_DEBUG) || defined(OE_BUILD_RELEASE))
	#define OE_BUILD_ENABLE_LOG 1
#else
	#define OE_BUILD_ENABLE_LOG 0
#endif

#if !defined(OE_BUILD_ENABLE_PROFILE) && (defined(OE_BUILD_DEBUG) || defined(OE_BUILD_RELEASE) || defined(OE_BUILD_PROFILE))
	#define OE_BUILD_ENABLE_PROFILE 1
#else
	#define OE_BUILD_ENABLE_PROFILE 0
#endif


#include <cstdint> // C++11 Types


// Declarations
using U8 = std::uint8_t;
using I8 = std::int8_t;
using U16 = std::uint16_t;
using I16 = std::int16_t;
using U32 = std::uint32_t;
using I32 = std::int32_t;
using U64 = std::uint64_t;
using I64 = std::int64_t;
using F32 = float;


// Constants Declarations
const U8 InvalidU8 = -1;
const U16 InvalidU16 = -1;
const U32 InvalidU32 = -1;
const U64 InvalidU64 = -1;


// Assertions
static_assert(sizeof(U8) == 1, "U8 != 8");
static_assert(sizeof(I8) == 1, "I8 != 8");
static_assert(sizeof(U16) == 2, "U16 != 16");
static_assert(sizeof(I16) == 2, "I16 != 16");
static_assert(sizeof(U32) == 4, "U32 != 32");
static_assert(sizeof(I32) == 4, "I32 != 32");
static_assert(sizeof(U64) == 8, "U64 != 64");
static_assert(sizeof(I64) == 8, "I64 != 64");
static_assert(sizeof(F32) == 4, "F32 != 32");


#include <utility> // std::swap

// Handle Endianness
namespace oe
{

inline void swapBytes(void* buffer, U32 size)
{
	U8* bytes = static_cast<U8*>(buffer);
	U32 i = 0;
	U32 j = size - 1;
	while (i < j)
	{
		std::swap(bytes[i++], bytes[j--]);
	}
}

template <typename T>
T swapBytes(T value)
{
	swapBytes(&value, sizeof(T));
	return value;
}

template <>
inline U16 swapBytes(U16 value)
{
	return ((value & 0x00FF) << 8) | ((value & 0xFF00) >> 8);
}

template <>
inline I16 swapBytes(I16 value)
{
	return ((value & 0x00FF) << 8) | ((value & 0xFF00) >> 8);
}

template <>
inline U32 swapBytes(U32 value)
{
	return ((value & 0x000000FF) << 24) | ((value & 0x0000FF00) << 8) | ((value & 0x00FF0000) >> 8) | ((value & 0xFF000000)) >> 24;
}

template <>
inline I32 swapBytes(I32 value)
{
	return ((value & 0x000000FF) << 24) | ((value & 0x0000FF00) << 8) | ((value & 0x00FF0000) >> 8) | ((value & 0xFF000000)) >> 24;
}

namespace priv
{
	union U32F32
	{
		U32 mAsU32;
		F32 mAsF32;
	};
}

template <>
inline F32 swapBytes(F32 value)
{
	priv::U32F32 u;
	u.mAsF32 = value;
	u.mAsU32 = swapBytes<U32>(u.mAsU32);
	return u.mAsF32;
}

} // namespace oe

#endif // OE_PLATFORM_HPP
