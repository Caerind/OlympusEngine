#include "../Sources/System/UnitTest.hpp"

#include "TestSystem.hpp"
#include "TestMath.hpp"
#include "TestCore.hpp"

int main()
{
	RUN_TEST(System);
	RUN_TEST(Math);
	RUN_TEST(Core);

	getchar();
	return 0;
}