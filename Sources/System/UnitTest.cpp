#include "UnitTest.hpp"

namespace oe
{

UnitTest::UnitTest(char* name)
	: mName(name)
	, mCurrentTitle(nullptr)
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
	mCurrentTitle = title;
}

void UnitTest::check(bool passed, const char* expr, const char* file, I32 line)
{
	if (passed)
	{
		mTests.back().passed++;
	}
	else
	{
		mTests.back().failed++;
		printf("\n[ERROR][%s] Check failed : %s (%s:%d)\n\n", mCurrentTitle, expr, file, line);
	}
}

void UnitTest::print()
{
	U32 success = 0;
	U32 failed = 0;
	printf("\n===== Finished the test of %s =====\n", mName);
	for (U32 i = 0; i < mTests.size(); i++)
	{
		printf("%s : %u passed | %u failed", mTests[i].title, mTests[i].passed, mTests[i].failed);
		if (mTests[i].failed == 0 && mTests[i].passed > 0)
		{
			printf(" ---> SUCCESS");
			success++;
		}
		else if (mTests[i].passed > 0)
		{
			printf(" ---> FAILED");
			failed++;
		}
		printf("\n");
	}
	printf("====================================\n\n");
	printf("===== Final result of %s =====\n", mName);
	printf("%u tests : %u passed | %u failed", success + failed, success, failed);
	if (failed == 0 && success > 0)
	{
		printf(" ---> SUCCESS");
	}
	else if (success > 0)
	{
		printf(" ---> FAILED");
	}
	printf("\n====================================\n\n");
}

char* UnitTest::getName()
{
	return mName;
}

char* UnitTest::getTitle()
{
	ASSERT(mCurrentTitle != nullptr);
	return mCurrentTitle;
}

UnitTest::Test::Test(char* pTitle)
	: title(pTitle)
	, passed(0)
	, failed(0)
{
}

} // namespace oe