#include "../Sources/System/Prerequisites.hpp"
#include "../Sources/System/UnitTest.hpp"
#include "../Sources/System/Profiler.hpp"

#include "../Sources/Math/AABB.hpp"
#include "../Sources/Math/Math.hpp"
#include "../Sources/Math/Matrix3.hpp"
#include "../Sources/Math/Matrix4.hpp"
#include "../Sources/Math/Plane.hpp"
#include "../Sources/Math/Quaternion.hpp"
#include "../Sources/Math/Random.hpp"
#include "../Sources/Math/Ray.hpp"
#include "../Sources/Math/Sphere.hpp"
#include "../Sources/Math/Vector2.hpp"
#include "../Sources/Math/Vector3.hpp"
#include "../Sources/Math/Vector4.hpp"

BEGIN_TEST(Math)
{
	TEST("AABB")
	{
		oe::AABB box;
	}

	TEST("Math")
	{
		CHECK(oe::Math::inRange(3, 2, 5));
		CHECK(oe::Math::equals(1.f, 1.001f, 0.01f));
		CHECK(oe::Math::roundUpToPowerOf2(13) == 16);
		CHECK(oe::Math::equals(oe::Math::cos(0.f), 1.f));
		CHECK(oe::Math::equals(oe::Math::sin(0.f), 0.f));
		CHECK(oe::Math::equals(oe::Math::tan(0.f), 0.f));
		CHECK(oe::Math::equals(oe::Math::acos(1.f), 0.f));
		CHECK(oe::Math::equals(oe::Math::asin(0.f), 0.f));
		CHECK(oe::Math::equals(oe::Math::atan(1.f), 45.f));
		CHECK(oe::Math::equals(oe::Math::atan2(10.f, 10.f), 45.f));
		oe::Math::Average avg;
		avg.add(10);
		avg.add(20);
		avg.add(30);
		CHECK(oe::Math::equals(avg.get(), 20.f, 0.1f));
	}

	TEST("Matrix")
	{
		oe::Matrix3 m3;
		oe::Matrix4 m4;
	}

	TEST("Plane")
	{
		oe::Plane p;
	}

	TEST("Quaternion")
	{
		oe::Quaternion q;
	}

	TEST("Random")
	{
		oe::RandomTable<U32> t;
	}

	TEST("Ray")
	{
		oe::Ray ray;
	}

	TEST("Sphere")
	{
		oe::Sphere s;
	}

	TEST("Vector")
	{
		oe::Vector2 v2;
		oe::Vector3 v3;
		oe::Vector4 v4;
	}
	
}
END_TEST;