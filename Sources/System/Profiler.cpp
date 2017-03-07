#include "Profiler.hpp"

namespace oe
{

template<> Profiler* Singleton<Profiler>::mSingleton = nullptr;

Profiler::Profiler()
{
}

Profiler::~Profiler()
{
}

void Profiler::beginProfile(const std::string& profileName)
{
	ASSERT(!profileName.empty());
	
	U32 index = 0;
	bool found = false;
	for (U32 i = 0; i < mProfiles.size(); i++)
	{
		if (mProfiles[i].mName == profileName)
		{
			found = true;
			index = i;
		}
	}
	if (!found)
	{
		mProfiles.emplace_back(profileName);
		index = mProfiles.size() - 1;
	}
	mProfiles[index].mStart = Time::getCurrentTime();
}

void Profiler::endProfile(const std::string& profileName)
{
	const Time end = Time::getCurrentTime();
	ASSERT(!profileName.empty());
	U32 index = 0;
	bool found = false;
	for (U32 i = 0; i < mProfiles.size(); i++)
	{
		if (mProfiles[i].mName == profileName)
		{
			found = true;
			index = i;
		}
	}
	ASSERT(found);
	ProfileInstance& profile = mProfiles[index];
	const Time duration = end - profile.mStart;
	if (duration < profile.mMin)
	{
		profile.mMin = duration;
	}
	if (duration > profile.mMax)
	{
		profile.mMax = duration;
	}
	profile.mSumm += duration;
	profile.mCalls++;
}

void Profiler::display()
{
	printf("----------------------------------------\n");
	for (U32 i = 0; i < mProfiles.size(); i++)
	{
		mProfiles[i].display();
	}
	printf("----------------------------------------\n");
}

Profiler* Profiler::getSingletonPtr()
{
	return mSingleton;
}

Profiler& Profiler::getSingleton()
{
	ASSERT(mSingleton != nullptr);
	return (*mSingleton);
}

Profiler::ProfileIndividual::ProfileIndividual(const std::string& profileName) : mName(profileName)
{
	Profiler::getSingleton().beginProfile(profileName);
}

Profiler::ProfileIndividual::~ProfileIndividual()
{
	Profiler::getSingleton().endProfile(mName);
}

Profiler::ProfileInstance::ProfileInstance(const std::string& profileName)
	: mName(profileName)
	, mCalls(0)
	, mStart(Time::Zero)
	, mMin(seconds(100))
	, mMax(Time::Zero)
	, mSumm(Time::Zero)
{
}

void Profiler::ProfileInstance::display()
{
	printf("[%s] c:%u -:%d +:%d ~:%u\n", mName.c_str(), mCalls, mMin.asMilliseconds(), mMax.asMilliseconds(), (mSumm.asMilliseconds()/mCalls));
}

} // namespace oe