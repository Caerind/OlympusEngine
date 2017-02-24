#include "UnitTest.hpp"

namespace oe
{

UnitTest::UnitTest(char* name)
	: mName(name)
	, mTests()
{
	printf("===== Starting the test of %s =====\n", mName);
}

UnitTest::~UnitTest()
{
}

void UnitTest::start(char* title)
{
	mTests.emplace_back(title);
}

void UnitTest::check(bool passed, const char* expr, const char* file, int line)
{
	if (passed)
	{
		mTests.back().passed++;
	}
	else
	{
		mTests.back().failed++;
		printf("%s : Check failed : %s (in %s line %d)\n", mTests.back().title, expr, file, line);
	}
}

void UnitTest::print()
{
	U32 success = 0;
	U32 failed = 0;
	printf("===== Finished the test of %s =====\n", mName);
	for (U32 i = 0; i < mTests.size(); i++)
	{
		printf("%s : %u passed | %u failed ---> ", mTests[i].title, mTests[i].passed, mTests[i].failed);
		if (mTests[i].failed == 0)
		{
			printf("SUCCESS\n");
			success++;
		}
		else
		{
			printf("FAILED\n");
			failed++;
		}
	}
	printf("===== Final result of %s =====\n", mName);
	printf("%u tests : %u passed | %u failed ---> ", success + failed, success, failed);
	if (failed == 0)
	{
		printf("SUCCESS\n");
	}
	else
	{
		printf("FAILED\n");
	}
	printf("====================================\n\n\n");
}

UnitTest::Test::Test(char* pTitle)
	: title(pTitle)
	, passed(0)
	, failed(0)
{
}

} // namespace oe
