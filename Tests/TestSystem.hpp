#ifndef OE_TESTSYSTEM_HPP
#define OE_TESTSYSTEM_HPP

#include "../Sources/System/Enum.hpp"
#include "../Sources/System/Enums.hpp"
#include "../Sources/System/Logger.hpp"
#include "../Sources/System/Macros.hpp"
#include "../Sources/System/Platform.hpp"
#include "../Sources/System/Singleton.hpp"
#include "../Sources/System/String.hpp"
#include "../Sources/System/Time.hpp"
#include "../Sources/System/Version.hpp"

#include "../Sources/System/UnitTest.hpp"

#include <algorithm> // Sort versions

BEGIN_TEST(System)
{

TEST("Enum")
{
	// Access values and names
	for (auto itr = oe::gEndiannessStrings.begin(); itr != oe::gEndiannessStrings.end(); itr++)
	{
		ECHO("Name : %s, Value : %d", itr->second.c_str(), itr->first);
	}

	// Acces values and get their names
	for (const auto& build : oe::gBuildList)
	{
		ECHO("Name : %s, Value : %d", toString(build).c_str(), build);
	}
}

TEST("Enums")
{

}

TEST("Logger")
{

}

TEST("Macros")
{

}

TEST("Platform")
{
	// Platform
	oe::Platform platform = oe::getPlatform();
	ECHO("Platform : %s", toString(platform).c_str());
	#if defined(OE_PLATFORM_MOBILE)
		ECHO("Mobile platform");
	#elif defined(OE_PLATFORM_DESKTOP)
		ECHO("Desktop platform");
	#endif

	// Endianness
	oe::Endianness endian = oe::getEndianness();
	ECHO("Endian: %s", toString(endian).c_str());

	// Compiler
	oe::Compiler compiler = oe::getCompiler();
	ECHO("Compiler : %s", toString(compiler).c_str());
	ECHO("Compiler description : %s", OE_COMPILER_DESCRIPTION);

	// Build
	oe::Build build = oe::getBuild();
	ECHO("Build Mode : %s", toString(build).c_str());
	#if OE_BUILD_ENABLE_ASSERT
		ECHO("Assertions enabled");
	#else
		ECHO("Assertions disabled");
	#endif
	#if OE_BUILD_ENABLE_LOG
		ECHO("Logging enabled");
	#else
		ECHO("Logging disabled");
	#endif
	#if OE_BUILD_ENABLE_DEBUG_LOG
		ECHO("Debug logging enabled");
	#else
		ECHO("Debug logging disabled");
	#endif
	#if OE_BUILD_ENABLE_PROFILE
		ECHO("Profiling enabled");
	#else
		ECHO("Profiling disabled");
	#endif

	// Check size of types
	CHECK(sizeof(U8) == 1);
	CHECK(sizeof(I8) == 1);
	CHECK(sizeof(U16) == 2);
	CHECK(sizeof(I16) == 2);
	CHECK(sizeof(U32) == 4);
	CHECK(sizeof(I32) == 4);
	CHECK(sizeof(U64) == 8);
	CHECK(sizeof(I64) == 8);
	CHECK(sizeof(F32) == 4);

	// Endianness Swap Integers
	I32 startA = 234;
	I32 startB = -456;
	I32 a = startA;
	I32 b = startB;
	I32 c = oe::swapBytes(a);
	I32 d = oe::swapBytes(b);
	a = oe::swapBytes(c);
	b = oe::swapBytes(d);
	CHECK(a == startA);
	CHECK(b == startB);

	// Endianness Swap Integers
	U32 startE = 456;
	U16 startF = 234;
	U32 e = startE;
	U16 f = startF;
	U32 g = oe::swapBytes(e);
	U16 h = oe::swapBytes(f);
	e = oe::swapBytes(g);
	f = oe::swapBytes(h);
	CHECK(e == startE);
	CHECK(f == startF);

	// Endianness Swap Floating-Point
	F32 startX1 = 34567.345678f;
	F32 startX2 = -34567.345678f;
	F32 x1 = startX1;
	F32 x2 = startX2;
	F32 y1 = oe::swapBytes(x1);
	F32 y2 = oe::swapBytes(x2);
	x1 = oe::swapBytes(y1);
	x2 = oe::swapBytes(y2);
	CHECK(x1 == startX1);
	CHECK(x2 == startX2);
}

TEST("Singleton")
{

}

TEST("String")
{
	std::string testToLower = "Test of THE TOLOwer FUNctION";
	oe::toLower(testToLower);
	CHECK(testToLower == "test of the tolower function");
	std::string testToUpper = "Test of THE TOUPper FUNctION";
	oe::toUpper(testToUpper);
	CHECK(testToUpper == "TEST OF THE TOUPPER FUNCTION");

	std::string testSplit1 = "hello,world,itsme";
	std::string testSplit1Res;
	CHECK(oe::split(testSplit1, testSplit1Res, ','));
	CHECK(testSplit1Res == "hello");
	CHECK(testSplit1 == "world,itsme");
	CHECK(oe::split(testSplit1, testSplit1Res, ','));
	CHECK(testSplit1Res == "world");
	CHECK(testSplit1 == "itsme");
	CHECK(!oe::split(testSplit1, testSplit1Res, ','));
	std::string testSplit2 = "hello==world==itsme";
	std::string testSplit2Res;
	CHECK(oe::split(testSplit2, testSplit2Res, "=="));
	CHECK(testSplit2Res == "hello");
	CHECK(testSplit2 == "world==itsme");
	CHECK(oe::split(testSplit2, testSplit2Res, "=="));
	CHECK(testSplit2Res == "world");
	CHECK(testSplit2 == "itsme");
	CHECK(!oe::split(testSplit2, testSplit2Res, "=="));

	std::string testContains = "Hello world !";
	CHECK(oe::contains(testContains, 'd'));
	CHECK(!oe::contains(testContains, 'a'));
	CHECK(oe::contains(testContains, "o w"));
	CHECK(!oe::contains(testContains, "ed"));

	std::string giantString = "This is the test of this function called : limitSize";
	std::string smallString = "Hello !";
	std::string storeString1;
	std::string storeString2;
	CHECK(oe::limitSize(giantString, storeString1, 10));
	CHECK(!oe::limitSize(smallString, storeString2, 10));
	CHECK(storeString1 == "This is th");
	CHECK(storeString2 == "Hello !");
	CHECK(oe::limitSize(giantString, 10));
	CHECK(!oe::limitSize(smallString, 10));
	CHECK(giantString == "This is th");
	CHECK(smallString == "Hello !");

	std::string testTrimWhitespace = "   \t   \t Hello world !   \t   \t   ";
	oe::trimWhitespace(testTrimWhitespace);
	CHECK(testTrimWhitespace == "Hello world !");

	std::string testEmpty = "";
	std::string testNonEmpty = "a";
	CHECK(oe::empty(testEmpty));
	CHECK(!oe::empty(testNonEmpty));

	std::string testBoolString;
	testBoolString = oe::toBoolString(true);
	CHECK(testBoolString == "true");
	testBoolString = oe::toBoolString(false);
	CHECK(testBoolString == "false");

	std::string testToString;
	testToString = oe::toString("test");
	CHECK(testToString == "test");
	testToString = oe::toString(true);
	CHECK(testToString == "1");
	testToString = oe::toString(false);
	CHECK(testToString == "0");
	testToString = oe::toString('c');
	CHECK(testToString == "c");
	testToString = oe::toString(2.3f);
	CHECK(testToString == "2.3");
	testToString = oe::toString(234);
	CHECK(testToString == "234");
	testToString = oe::toString(-234);
	CHECK(testToString == "-234");

	std::string testFromString = oe::fromString<std::string>("test");
	CHECK(testFromString == "test");
	bool testFromStringBool = oe::fromString<bool>("true");
	CHECK(testFromStringBool == true);
	testFromStringBool = oe::fromString<bool>("false");
	CHECK(testFromStringBool == false);
	testFromStringBool = oe::fromString<bool>("1");
	CHECK(testFromStringBool == true);
	testFromStringBool = oe::fromString<bool>("0");
	CHECK(testFromStringBool == false);
	testFromStringBool = oe::fromString<bool>("x");
	CHECK(testFromStringBool == false);
	char testFromStringChar = oe::fromString<char>("t");
	CHECK(testFromStringChar == 't');
	F32 testFromStringF32 = oe::fromString<F32>("2.3");
	CHECK(testFromStringF32 == 2.3f);
	U32 testFromStringU32 = oe::fromString<U32>("234");
	CHECK(testFromStringU32 == 234);
	I32 testFromStringI32 = oe::fromString<I32>("-234");
	CHECK(testFromStringI32 == -234);

	oe::StringId id1 = oe::StringId::hash("Test", false);
	oe::StringId id2 = oe::StringId::hash("Test2", true);
	oe::StringId id3;

	U32 hRuntime = oe::StringId::hashRuntime("Test");
	U32 hCompile = oe::StringId::hashCompile("Test");

	CHECK(hRuntime == hCompile);

	CHECK(id1.isValid());
	CHECK(id2.isValid());
	CHECK(!id3.isValid());

	CHECK(id1 == hRuntime);
	CHECK(id1 == hCompile);

	CHECK(id1 != id2);
	CHECK(id1 != id3);
	CHECK(id2 != id3);

	CHECK(!id1.isStored());
	CHECK(id2.isStored());

	std::string testStorage;
	CHECK(!id1.getString(testStorage));
	CHECK(id2.getString(testStorage));
}

TEST("Time")
{

}

TEST("Version")
{
	oe::Version current;
	ECHO("Current : %u.%u.%u %s", current.major, current.minor, current.patch, oe::Version::getName());

	oe::Version old(0, 1, 0);
	oe::Version future(1, 0, 0);
	CHECK(old < current);
	CHECK(future > current);

	std::vector<oe::Version> vs;
	vs.emplace_back(1, 0, 0);
	vs.emplace_back(0, 1, 0);
	vs.emplace_back(0, 0, 1);
	vs.emplace_back(1, 2, 0);
	vs.emplace_back(0, 1, 2);
	vs.emplace_back(2, 0, 1);
	std::sort(vs.begin(), vs.end());
	for (const auto& v : vs)
	{
		ECHO("%d.%d.%d", v.major, v.minor, v.patch);
	}
}

}
END_TEST;

#endif // OE_TESTSYSTEM_HPP
