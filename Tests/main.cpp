#include "../Sources/Config.hpp"
#include "../Sources/Core/Log.hpp"
#include "../Sources/Core/UnitTest.hpp"
#include "../Sources/Core/Profiler.hpp"

#include "TestCore.hpp"
#include "TestMath.hpp"

int main()
{
	
	RUN_TEST(Core);
	RUN_TEST(Math);

	getchar();
	return 0;
}