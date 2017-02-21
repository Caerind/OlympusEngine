#include "../Sources/Config.hpp"
#include "../Sources/Utilities/Date.hpp"
#include "../Sources/Utilities/File.hpp"
#include "../Sources/Utilities/Localization.hpp"
#include "../Sources/Utilities/Log.hpp"
#include "../Sources/Utilities/Math.hpp"
#include "../Sources/Utilities/Matrix.hpp"
#include "../Sources/Utilities/ParserCsv.hpp"
#include "../Sources/Utilities/ParserIni.hpp"
#include "../Sources/Utilities/ParserPure.hpp"
#include "../Sources/Utilities/ParserXml.hpp"
#include "../Sources/Utilities/PoolAllocator.hpp"
#include "../Sources/Utilities/Profiler.hpp"
#include "../Sources/Utilities/Quaternion.hpp"
#include "../Sources/Utilities/Random.hpp"
#include "../Sources/Utilities/Serialization.hpp"
#include "../Sources/Utilities/StackAllocator.hpp"
#include "../Sources/Utilities/String.hpp"
#include "../Sources/Utilities/Thread.hpp"
#include "../Sources/Utilities/Time.hpp"
#include "../Sources/Utilities/UniqueId.hpp"
#include "../Sources/Utilities/UnitTest.hpp"
#include "../Sources/Utilities/Vector.hpp"

BEGIN_UNIT_TEST;

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

TEST("Date")
{
	// Start test

	oe::Date currentDate;
	oe::info("Current date : " + currentDate.toString());
	oe::Date d;
	d.setDay(currentDate.getDay() - 20);
	CHECK(d.passed());

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
				case 1: CHECK(oe::fromString<F32>(line) == 3.14f); break;
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

TEST("Localization")
{
	// Start test

	oe::Localization localization;

	// Add languages using instance and singleton
	localization.addLanguage(oe::Localization::Language::English, [](oe::Localization::LanguageTable& table)
	{
		table.push_back(oe::StringHash::hash("EnglishTest1"));
		table.push_back(oe::StringHash::hash("EnglishTest2"));
		return true;
	});
	oe::Localization::getSingleton().addLanguage(oe::Localization::Language::French, [](oe::Localization::LanguageTable& table)
	{
		table.push_back(oe::StringHash::hash("FrancaisTest1"));
		table.push_back(oe::StringHash::hash("FrancaisTest2"));
		return true;
	});

	// Use english using instance
	CHECK(localization.useLanguage(oe::Localization::Language::English) == true);
	CHECK(localization.getCurrentLanguage() == oe::Localization::getSingleton().getCurrentLanguage());
	CHECK(localization.getToken(0) == "EnglishTest1");
	CHECK(oe::Localization::getSingleton().getToken(1) == "EnglishTest2");

	// USe french using singleton
	CHECK(oe::Localization::getSingleton().useLanguage(oe::Localization::Language::French) == true);
	CHECK(localization.getCurrentLanguage() == oe::Localization::getSingleton().getCurrentLanguage());
	CHECK(localization.getToken(0) == "FrancaisTest1");
	CHECK(oe::Localization::getSingleton().getToken(1) == "FrancaisTest2");

	// End test
}

TEST("Log")
{
	// Start test

	oe::log("pretest");

	oe::Log log;
	log.useConsole(true);

	oe::Log::getSingleton().log("test1");
	oe::log("test2");
	log.log("test3");

	oe::info("i");
	oe::warning("w");
	oe::error("e");

	// TODO : Check ?

	// End test
}

TEST("Math")
{

}

TEST("Matrix")
{
	oe::Matrix4 m;
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
	//oe::PoolAllocator<1024> a;
}

TEST("Profiler")
{
	// Start test

	oe::Profiler pInstance;
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
	pInstance.display();

	// End test
}

TEST("Quaternion")
{
	oe::Quat q;
}

TEST("Random")
{
	// Start test
	U32 count = 100000;

	I32 sumU = 0;
	for (U32 i = 0; i < count; i++)
	{
		sumU += oe::Random::getI32(-1, 1);
	}

	F32 sumF = 0.f;
	for (U32 i = 0; i < count; i++)
	{
		sumF += oe::Random::getF32(-1.f, 1.f);
	}

	F32 cF = (F32)count;
	F32 avgU = ((F32)sumU) / cF;
	F32 avgF = sumF / cF;

	oe::info("AvgU : " + oe::toString(avgU));
	oe::info("AvgF : " + oe::toString(avgF));

	// End test
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

TEST("UniqueId")
{
	// Start test

	oe::UniqueIdManager idManager;
	oe::UID id1 = oe::UniqueIdManager::getSingleton().createUID();
	oe::UID id2 = oe::UniqueIdManager::getSingleton().createUID();
	oe::UID id3 = idManager.createUID(1);
	CHECK(id1 != id2);
	CHECK(id1 != 0);
	CHECK(id2 != 0);
	CHECK(id3 != 0);
	CHECK(id1 == id3);

	// End test
}

TEST("Vector")
{
	oe::Vector3 v;
}

END_UNIT_TEST;