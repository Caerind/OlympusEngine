#include "../Sources/System/Prerequisites.hpp"
#include "../Sources/System/UnitTest.hpp"
#include "../Sources/System/Profiler.hpp"

#include "../Sources/Core/Application.hpp"

BEGIN_TEST(Core)
{
	TEST("Application")
	{
		oe::Application app;
		U8 i = 0;
		while (app.run())
		{
			if (i++ > 10)
			{
				app.stop();
			}
		}
	}
}
END_TEST;