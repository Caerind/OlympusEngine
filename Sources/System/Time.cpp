#include "Time.hpp"

#include <chrono>
#include <thread>

#if OE_PLATFORM_MACOS || OE_PLATFORM_IOS
#include <mach/mach_time.h>
#elif OE_PLATFORM_WINDOWS
#include <windows.h>
#else
#include <time.h>
#endif

#if OE_PLATFORM_WINDOWS
LARGE_INTEGER getFrequency()
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	return frequency;
}
#endif

namespace oe
{

const Time Time::Zero;
const Time Time::Second = seconds(1.0f);
const Time Time::Tick = ticks(1.0f);

Time Time::getCurrentTime()
{
	#if OE_PLATFORM_MACOS || OE_PLATFORM_IOS
		// Mac OS X specific implementation (it doesn't support clock_gettime)
		static mach_timebase_info_data_t frequency = { 0, 0 };
		if (frequency.denom == 0)
			mach_timebase_info(&frequency);
		U64 nanoseconds = mach_absolute_time() * frequency.numer / frequency.denom;
		return microseconds(nanoseconds / 1000);
	#elif OE_PLATFORM_WINDOWS
		HANDLE currentThread = GetCurrentThread(); // Force the following code to run on first core (see http://msdn.microsoft.com/en-us/library/windows/desktop/ms644904(v=vs.85).aspx)
		DWORD_PTR previousMask = SetThreadAffinityMask(currentThread, 1);
		static LARGE_INTEGER frequency = getFrequency(); // Get the frequency of the performance counter (it is constant across the program lifetime)
		LARGE_INTEGER time; // Get the current time
		QueryPerformanceCounter(&time);
		SetThreadAffinityMask(currentThread, previousMask); // Restore the thread affinity
		return microseconds(1000000 * time.QuadPart / frequency.QuadPart);
	#else
		// POSIX implementation
		timespec time;
		clock_gettime(CLOCK_MONOTONIC, &time);
		return microseconds(static_cast<U64>(time.tv_sec) * 1000000 + time.tv_nsec / 1000);
	#endif
}

Time::Time()
	: mMicroseconds(0)
{
}

float Time::asSeconds() const
{
	return mMicroseconds / 1000000.f;
}

I32 Time::asMilliseconds() const
{
	return static_cast<I32>(mMicroseconds / 1000);
}

I64 Time::asMicroseconds() const
{
	return mMicroseconds;
}

Time::Time(I64 microseconds) : mMicroseconds(microseconds)
{
}

Time hours(U32 amount)
{
	return seconds(amount * 3600.0f);
}

Time minutes(U32 amount)
{
	return seconds(amount * 60.0f);
}

Time seconds(F32 amount)
{
	return Time(static_cast<I64>(amount * 1000000));
}

Time ticks(F32 amount)
{
	return seconds(1.0f / 60.0f);
}

Time milliseconds(I32 amount)
{
	return Time(static_cast<I64>(amount) * 1000);
}

Time microseconds(I64 amount)
{
	return Time(amount);
}

bool operator ==(Time left, Time right)
{
	return left.asMicroseconds() == right.asMicroseconds();
}

bool operator !=(Time left, Time right)
{
	return left.asMicroseconds() != right.asMicroseconds();
}

bool operator <(Time left, Time right)
{
	return left.asMicroseconds() < right.asMicroseconds();
}

bool operator >(Time left, Time right)
{
	return left.asMicroseconds() > right.asMicroseconds();
}

bool operator <=(Time left, Time right)
{
	return left.asMicroseconds() <= right.asMicroseconds();
}

bool operator >=(Time left, Time right)
{
	return left.asMicroseconds() >= right.asMicroseconds();
}

Time operator -(Time right)
{
	return microseconds(-right.asMicroseconds());
}

Time operator +(Time left, Time right)
{
	return microseconds(left.asMicroseconds() + right.asMicroseconds());
}

Time& operator +=(Time& left, Time right)
{
	return left = left + right;
}

Time operator -(Time left, Time right)
{
	return microseconds(left.asMicroseconds() - right.asMicroseconds());
}

Time& operator -=(Time& left, Time right)
{
	return left = left - right;
}

Time operator *(Time left, F32 right)
{
	return seconds(left.asSeconds() * right);
}

Time operator *(Time left, I64 right)
{
	return microseconds(left.asMicroseconds() * right);
}

Time operator*(Time left, U32 right)
{
	return seconds(left.asSeconds() * right);
}

Time operator *(F32 left, Time right)
{
	return right * left;
}

Time operator *(I64 left, Time right)
{
	return right * left;
}

Time operator*(U32 left, Time right)
{
	return seconds(left * right.asSeconds());
}

Time& operator *=(Time& left, F32 right)
{
	return left = left * right;
}

Time& operator *=(Time& left, I64 right)
{
	return left = left * right;
}

Time& operator*=(Time& left, U32 right)
{
	return left = left * right;
}

Time operator /(Time left, F32 right)
{
	return seconds(left.asSeconds() / right);
}

Time operator /(Time left, I64 right)
{
	return microseconds(left.asMicroseconds() / right);
}

Time operator/(Time left, U32 right)
{
	return seconds(left.asSeconds() / right);
}

Time& operator /=(Time& left, F32 right)
{
	return left = left / right;
}

Time& operator /=(Time& left, I64 right)
{
	return left = left / right;
}

Time& operator/=(Time& left, U32 right)
{
	return left = left / right;
}

F32 operator /(Time left, Time right)
{
	return left.asSeconds() / right.asSeconds();
}

Time operator %(Time left, Time right)
{
	return microseconds(left.asMicroseconds() % right.asMicroseconds());
}

Time& operator %=(Time& left, Time right)
{
	return left = left % right;
}

void sleep(Time duration)
{
	std::this_thread::sleep_for(std::chrono::microseconds(duration.asMicroseconds()));
}

Clock::Clock() : mStart(Time::getCurrentTime())
{
}

Time Clock::getElapsedTime() const
{
	return Time::getCurrentTime() - mStart;
}

Time Clock::restart()
{
	Time now = Time::getCurrentTime();
	Time elapsed = now - mStart;
	mStart = now;
	return elapsed;
}

StopWatch::StopWatch()
	: mClock()
	, mTimeBuffer(Time::Zero)
	, mRunning(false)
{
}

Time StopWatch::getElapsedTime() const
{
	return mTimeBuffer + ((mRunning) ? mClock.getElapsedTime() : Time::Zero);
}

bool StopWatch::isRunning() const
{
	return mRunning;
}

void StopWatch::start()
{
	if (!mRunning)
	{
		mRunning = true;
		mClock.restart();
	}
}

void StopWatch::stop()
{
	if (mRunning)
	{
		mRunning = false;
		mTimeBuffer += mClock.getElapsedTime();
	}
}

void StopWatch::reset()
{
	mTimeBuffer = Time::Zero;
	mRunning = false;
}

void StopWatch::restart()
{
	reset();
	start();
}

Timer::Timer()
	: mStopWatch()
	, mLimit(Time::Zero)
{
}

Time Timer::getLimit() const
{
	return mLimit;
}

Time Timer::getRemainingTime() const
{
	Time t = mLimit - mStopWatch.getElapsedTime();
	if (t.asMicroseconds() > 0)
	{
		return t;
	}
	return Time::Zero;
}

bool Timer::isRunning() const
{
	return mStopWatch.isRunning() && !isExpired();
}

bool Timer::isExpired() const
{
	return mStopWatch.getElapsedTime() >= mLimit;
}

void Timer::start()
{
	mStopWatch.start();
}

void Timer::stop()
{
	mStopWatch.stop();
}

void Timer::reset(Time timeLimit)
{
	ASSERT(timeLimit > Time::Zero);

	mLimit = timeLimit;
	mStopWatch.reset();
}

void Timer::restart(Time timeLimit)
{
	reset(timeLimit);
	start();
}

CallbackTimer::CallbackTimer()
	: Timer()
	, mJustExpired(false)
{
}

void CallbackTimer::reset(Time timeLimit)
{
	Timer::reset(timeLimit);
	mJustExpired = false;
}

void CallbackTimer::restart(Time timeLimit)
{
	Timer::restart(timeLimit);
	mJustExpired = false;
}

void CallbackTimer::update()
{
	if (isExpired() && !mJustExpired)
	{
		mJustExpired = true;
		onExpire(Timer::getLimit());
	}
}

} // namespace oe