#ifndef OE_MACROS_HPP
#define OE_MACROS_HPP

#include "Platform.hpp"

#define OE_PREPROCESSOR_TOSTRING(x) OE_PREPROCESSOR_TOSTRING_IMPL(x)
#define OE_PREPROCESSOR_TOSTRING_IMPL(x) #x

#define OE_NON_COPYABLE(Type) \
	Type(const Type&) = delete; \
	void operator=(const Type&) = delete;

#define OE_NON_MOVABLE(Type) \
	Type(Type&&) = delete; \
	void operator=(Type&&) = delete;

#define OE_ALIGN(x) __declspec(align(x))
#define OE_ALIGN16 OE_ALIGN(16)
#define OE_ALIGN32 OE_ALIGN(32)
#define OE_ALIGN64 OE_ALIGN(64)
#define OE_ALIGN128 OE_ALIGN(128)

#if OE_BUILD_ENABLE_ASSERT
	#define ASSERT(expr) \
		if (expr) {} \
		else \
		{ \
			printf("Assertion failed!\nExpr : %s\n File : %s\n Line : %d\n", #expr, __FILE__, __LINE__); \
			for (;;) {} \
		}
#else
	#define ASSERT
#endif

#if defined(OE_COMPILER_MSVC)
	// Note: On newer MSVC versions, using deprecated functions causes a compiler error. In order to
	// trigger a warning instead of an error, the compiler flag /sdl- (instead of /sdl) must be specified.
	#define OE_DEPRECATED __declspec(deprecated)
#elif defined(OE_COMPILER_GCC) || defined(OE_COMPILER_CLANG)
	#define OE_DEPRECATED __attribute__ ((deprecated))
#else
	// Other compilers are not supported, leave class or function as-is.
	// With a bit of luck, the #pragma directive works, otherwise users get a warning (no error!) for unrecognized #pragma.
	#pragma message("OE_DEPRECATED is not supported for this compiler")
	#define OE_DEPRECATED
#endif

#endif // OE_MACROS_HPP
