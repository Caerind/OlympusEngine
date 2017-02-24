#include "Core.hpp"

namespace oe
{

template <> Core* Singleton<Core>::mSingleton = nullptr;

Core::Core()
	: mOutputConsole(nullptr)
	, mInputConsole(nullptr)
	, mLog(nullptr)
	, mProfiler(nullptr)
	, mLocalization(nullptr)
	, mUniqueIdManager(nullptr)
{
	mOutputConsole = new OConsole();
	mInputConsole = new IConsole();
	mLog = new Log();
	mProfiler = new Profiler();
	mLocalization = new Localization();
	mUniqueIdManager = new UniqueIdManager();
}

Core::~Core()
{
	delete mUniqueIdManager;
	delete mLocalization;
	delete mProfiler;
	delete mLog;
	delete mInputConsole;
	delete mOutputConsole;
}

Core& Core::getSingleton()
{
	ASSERT(mSingleton != nullptr);
	return *mSingleton;
}

Core* Core::getSingletonPtr()
{
	return mSingleton;
}

} // namespace oe