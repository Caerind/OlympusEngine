#ifndef OE_UNITTEST_HPP
#define OE_UNITTEST_HPP

#include "../Config.hpp"

#include "Time.hpp"

#define BEGIN_UNIT_TEST int main() { oe::UnitTest unitTest;
#define END_UNIT_TEST unitTest.print(); system("pause"); return 0; }

#define TEST(title) unitTest.start(title);
#define CHECK(expr) unitTest.check(expr, #expr, __FILE__, __LINE__);

namespace oe
{

class UnitTest
{
	public:
		UnitTest();
		~UnitTest();

		void start(char* title);

		void check(bool passed, const char* expr, const char* file, int line);

		void print();

	private:
		struct Test
		{
			Test(char* pTitle);

			char* title;
			U32 passed;
			U32 failed;
		};

		std::vector<Test> mTests;
};

} // namespace oe

#endif // OE_UNITTEST_HPP
