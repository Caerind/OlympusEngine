#include "../Sources/Core/Prerequisites.hpp"
#include "../Sources/Core/UnitTest.hpp"
#include "../Sources/Core/Profiler.hpp"

#include "../Sources/Math/Math.hpp"
#include "../Sources/Math/Matrix.hpp"
#include "../Sources/Math/Quaternion.hpp"
#include "../Sources/Math/Random.hpp"
#include "../Sources/Math/Vector.hpp"

BEGIN_TEST(Math)
{
	TEST("Matrix")
	{
		oe::Matrix4 m;
	}

	TEST("Vector")
	{
		oe::Vector3 v;
	}
	
}
END_TEST;