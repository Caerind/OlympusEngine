#ifndef OE_PREREQUISITES_HPP
#define OE_PREREQUISITES_HPP

#include "Platform.hpp"
#include "Config.hpp"
#include "String.hpp"

////////////////////////////////////////////////////
// Assertions
////////////////////////////////////////////////////

#include <cstdio>
#if defined OE_ASSERT
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

#endif // OE_PREREQUISITES_HPP