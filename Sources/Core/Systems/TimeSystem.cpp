#include "TimeSystem.hpp"

namespace oe
{

TimeSystem::TimeSystem()
	: mSpeedFactor(1.0f)
{
}

void TimeSystem::setSpeedFactor(F32 factor)
{
	mSpeedFactor = factor;
}

F32 TimeSystem::getSpeedFactor() const
{
	return mSpeedFactor;
}

void TimeSystem::update(Time dt)
{
	for (auto itr = mTimers.begin(); itr != mTimers.end(); )
	{
		itr->second.elapsed += dt;
		if (itr->second.elapsed >= itr->second.duration)
		{
			itr->second.onExpire(itr->second.duration);
			itr = mTimers.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

TimeSystem::CTimer* TimeSystem::getTimer(TimerId id)
{
	auto itr = mTimers.find(id);
	if (itr != mTimers.end())
	{
		return &itr->second;
	}
	return nullptr;
}

void TimeSystem::removeTimer(TimerId id)
{
	auto itr = mTimers.find(id);
	if (itr != mTimers.end())
	{
		mTimers.erase(itr);
	}
}

} // namespace oe