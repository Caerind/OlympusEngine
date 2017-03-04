#include "../Sources/Core/Prerequisites.hpp"
#include "../Sources/Core/UnitTest.hpp"
#include "../Sources/Core/Profiler.hpp"

#include "../Sources/Core/Color.hpp"
#include "../Sources/Core/Compression.hpp"
#include "../Sources/Core/Connection.hpp"
#include "../Sources/Core/Date.hpp"
#include "../Sources/Core/File.hpp"
#include "../Sources/Core/Id.hpp"
#include "../Sources/Core/Localization.hpp"
#include "../Sources/Core/Log.hpp"
#include "../Sources/Core/NonCopyable.hpp"
#include "../Sources/Core/ParserCsv.hpp"
#include "../Sources/Core/ParserIni.hpp"
#include "../Sources/Core/ParserIni.hpp"
#include "../Sources/Core/ParserPure.hpp"
#include "../Sources/Core/ParserXml.hpp"
#include "../Sources/Core/PoolAllocator.hpp"
#include "../Sources/Core/Profiler.hpp"
#include "../Sources/Core/ResourceHolder.hpp"
#include "../Sources/Core/Singleton.hpp"
#include "../Sources/Core/StackAllocator.hpp"
#include "../Sources/Core/String.hpp"
#include "../Sources/Core/Thread.hpp"
#include "../Sources/Core/Time.hpp"
#include "../Sources/Core/UnitTest.hpp"
#include "../Sources/Core/Updatable.hpp"


BEGIN_TEST(Core)
{

	TEST("Config")
	{
		// Start test

		CHECK(sizeof(I8) == 1);
		CHECK(sizeof(U8) == 1);
		CHECK(sizeof(I16) == 2);
		CHECK(sizeof(U16) == 2);
		CHECK(sizeof(I32) == 4);
		CHECK(sizeof(U32) == 4);
		CHECK(sizeof(I64) == 8);
		CHECK(sizeof(U64) == 8);
		CHECK(sizeof(F32) == 4);
		CHECK(oe::getPlatformName() == "Windows");

		// End test
	}

	TEST("Color")
	{
		oe::Color color;
		// TODO : Test color
	}

	TEST("Compression")
	{
		// TODO : Test Compression
	}

	TEST("Date")
	{
		// Start test

		oe::Date currentDate;
		oe::info("Current date : " + currentDate.toString());
		oe::Date d;
		d.setDay(currentDate.getDay() - 10);
		CHECK(d.passed());

		oe::Date d2("23-02-1996 12-46-12");
		CHECK(d2.getDay() == 23);
		CHECK(d2.getMonth() == 2);
		CHECK(d2.getYear() == 1996);
		CHECK(d2.getHours() == 12);
		CHECK(d2.getMinutes() == 46);
		CHECK(d2.getSeconds() == 12);
		d2 += oe::seconds(10.f);
		CHECK(d2.getSeconds() == 22);

		oe::Date birth; // 23 jan 1996 - 3:33:34
		birth.setDay(23);
		birth.setMonth(1);
		birth.setYear(1996);
		birth.setHours(3);
		birth.setMinutes(33);
		birth.setSeconds(34);
		CHECK("23-01-1996 03-33-34" == birth.toString());
		CHECK("23-01-1996 03-33-34" == toString(birth));

		oe::Date b2("23-01-1996 03-33-34");
		CHECK(b2 == birth);
		b2.setYear(1995);
		CHECK(b2 < birth);
		b2.setYear(1996);
		b2.setMonth(2);
		CHECK(b2 > birth);

		// TODO : Improve Date test

		// End test
	}

	TEST("File")
	{
		// Start test

		oe::OFile ofile("test.txt", true);
		if (ofile.isOpen())
		{
			ofile << "Test" << '\n';
			ofile << 3.14f << '\n';
			ofile << true << '\n';
			ofile << 10 << '\n';
			ofile.close();
		}

		oe::IFile ifile("test.txt");
		if (ifile.isOpen())
		{
			std::string line;
			U32 i = 0;
			while (ifile.read(line))
			{
				switch (i)
				{
				case 0: CHECK(line == "Test"); break;
				case 1: CHECK(oe::Math::equals(oe::fromString<F32>(line), 3.14f)); break;
				case 2: CHECK(oe::fromString<bool>(line) == true); break;
				case 3: CHECK(oe::fromString<I32>(line) == 10); break;
				default: CHECK(false);
				}
				i++;
			}
			ifile.close();
		}

		// TODO : Test Path
		// TODO : Test File
		CHECK(oe::File::remove("test.txt"));
		// TODO : Improve test

		// End test
	}

	TEST("Id")
	{
		// Start test

		oe::UID id1 = oe::Id::generate<I32>();
		oe::UID id2 = oe::Id::generate<I32>();
		oe::UID id3 = oe::Id::generate<U32>();
		CHECK(id1 != id2);
		CHECK(id1 != 0);
		CHECK(id2 != 0);
		CHECK(id3 != 0);
		CHECK(id1 == id3);

		// End test
	}

	TEST("Localization")
	{
		// Start test

		oe::Localization localization;

		// Define the identifiers
		enum class LangId : U32
		{
			Test1 = 0,
			Test2 = 1
		};

		// Add languages
		oe::Localization::getSingleton().addLanguage(oe::Localization::Language::English, [](oe::Localization::LanguageTable& table)
		{
			table.add("EnglishTest1");
			table.add("EnglishTest2");
			return true;
		});
		oe::Localization::getSingleton().addLanguage(oe::Localization::Language::French, [](oe::Localization::LanguageTable& table)
		{
			table.add("FrancaisTest1");
			table.add("FrancaisTest2");
			return true;
		});

		// Use english
		CHECK(oe::Localization::getSingleton().useLanguage(oe::Localization::Language::English) == true);
		CHECK(oe::Localization::getSingleton().getToken((U32)LangId::Test1) == "EnglishTest1");
		CHECK(oe::Localization::getSingleton().getToken((U32)LangId::Test2) == "EnglishTest2");

		// Use french
		CHECK(oe::Localization::getSingleton().useLanguage(oe::Localization::Language::French) == true);
		CHECK(oe::Localization::getSingleton().getToken((U32)LangId::Test1) == "FrancaisTest1");
		CHECK(oe::Localization::getSingleton().getToken((U32)LangId::Test2) == "FrancaisTest2");

		/* Load spanish from INI file
		// 1- check that spanish is defined in the enum in localization
		// 2- create your ini in the same order as the other language
		// 3- use this pre-defnied function :
		oe::Localization::getSingleton().addLanguage(oe::Localization::Language::Spanish, [](oe::Localization::LanguageTable& table)
		{
			return oe::Localization::loadLanguageFromFile(table, "spanish.lang");
		});
		// 4- CHECK(oe::Localization::getSingleton().useLanguage(oe::Localization::Language::Spanish) == true);
		// 5- CHECK(oe::Localization::getSingleton().getToken((U32)LangId::Test1) == "SpanolTest1");
		// 6- CHECK(oe::Localization::getSingleton().getToken((U32)LangId::Test2) == "SpanolTest2");
		*/

		// End test
	}

	TEST("Log")
	{
		// Start test

		oe::log("pretest");

		oe::Log log;

		oe::Log::getSingleton().log("test1");
		oe::log("test2");

		oe::info("i");
		oe::warning("w");
		oe::error("e");

		// End test
	}

	TEST("ParserCsv")
	{
		U32 elementsPerLine(10);
		oe::ParserCsv p(elementsPerLine);
	}

	TEST("ParserIni")
	{
		oe::ParserIni p;
	}

	TEST("ParserPure")
	{
		oe::ParserPure p;
	}

	TEST("ParserXml")
	{
		oe::ParserXml p;
	}

	TEST("PoolAllocator")
	{
		oe::PoolAllocator<1024> a;
	}

	TEST("Profiler")
	{
		// Start test

		oe::Profiler p;

		for (U32 i = 0; i < 30; i++)
		{
			ProfileBegin("MainLoop");
			{
				Profile("Render");
				std::vector<U32> a;
				for (U32 j = 0; j < 10000; j++)
				{
					a.push_back(j);
				}

				{
					Profile("RenderDebug");
					for (U32 j = 0; j < a.size(); j++)
					{
						for (U32 k = 0; k < 10; k++)
						{
							a[k] *= j * k;
						}
					}
				}
			}
			ProfileEnd("MainLoop");
		}
		oe::Profiler::getSingleton().display();

		// End test
	}

	TEST("ResourceHolder")
	{
		oe::ResourceHolder<oe::ParserXml> parsers;
		CHECK(!parsers.has("test"));
		oe::ResourceId r = parsers.create("test", "test.xml");
		CHECK(parsers.has(r));
		CHECK(parsers.has("test"));
		CHECK(parsers.size() == 1);
		{
			oe::ParserXml& x1 = parsers.get(r);
			oe::ParserXml& x2 = parsers.get("test");
		}
		parsers.release(r);
		CHECK(!parsers.has(r));
		CHECK(!parsers.has("test"));
		CHECK(parsers.size() == 0);
	}

	TEST("Serialization")
	{
		// Start test

		// Nothing to test yet

		// End test
	}

	TEST("StackAllocator")
	{
		oe::StackAllocator<1024> a;
	}

	TEST("String")
	{
		// Start test

		// TODO : Conversion

		// TODO : Tools

		// Hashing
		std::vector<oe::StringId> hashes;
		for (U32 i = 0; i < 100; i++)
		{
			std::string t = "Test" + std::to_string(i);
			oe::StringId id = oe::StringHash::hash(t);
			bool found = false;
			for (U32 j = 0; j < hashes.size(); j++)
			{
				CHECK(id != hashes[j]);
				if (id == hashes[j])
				{
					printf("Hash : %s & %s give the same id\n", t.c_str(), oe::StringHash::get(hashes[j]).c_str());
				}
			}
			hashes.push_back(id);
		}
		for (U32 i = 0; i < hashes.size(); i++)
		{
			CHECK(hashes[i] == oe::StringHash::hash(oe::StringHash::get(hashes[i])));
		}

		// End test
	}

	TEST("Thread")
	{
		oe::Thread thread;
	}

	TEST("Time")
	{
		// Start test

		// Test Time

		// Test Clock
		oe::Clock c;
		oe::Thread::sleep(oe::milliseconds(100));
		oe::Time t = c.getElapsedTime();
		printf("Time : %d\n", t.asMilliseconds());
		CHECK(t.asMilliseconds() == (I32)100 || t.asMilliseconds() == (I32)101);

		// Test StopWatch

		// Test Timer

		// Test CallbackTimer


		// End test
	}
}
END_TEST;