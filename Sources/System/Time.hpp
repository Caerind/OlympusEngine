#ifndef OE_TIME_HPP
#define OE_TIME_HPP

#include "Connection.hpp"

namespace oe
{

class Time
{
	public:
		static Time getCurrentTime();
	
		Time();

		F32 asSeconds() const;
		I32 asMilliseconds() const;
		I64 asMicroseconds() const;

		static const Time Zero;

	private:
		friend Time seconds(F32);
		friend Time milliseconds(I32);
		friend Time microseconds(I64);
		explicit Time(I64 microseconds);

	private:
		I64 mMicroseconds;
};

Time seconds(F32 amount);
Time milliseconds(I32 amount);
Time microseconds(I64 amount);

bool operator ==(Time left, Time right);
bool operator !=(Time left, Time right);
bool operator <(Time left, Time right);
bool operator >(Time left, Time right);
bool operator <=(Time left, Time right);
bool operator >=(Time left, Time right);
Time operator -(Time right);
Time operator +(Time left, Time right);
Time& operator +=(Time& left, Time right);
Time operator -(Time left, Time right);
Time& operator -=(Time& left, Time right);
Time operator *(Time left, F32 right);
Time operator *(Time left, I64 right);
Time operator *(Time left, U32 right);
Time operator *(F32 left, Time right);
Time operator *(I64 left, Time right);
Time operator *(U32 left, Time right);
Time& operator *=(Time& left, F32 right);
Time& operator *=(Time& left, I64 right);
Time& operator *=(Time& left, U32 right);
Time operator /(Time left, F32 right);
Time operator /(Time left, I64 right);
Time operator /(Time left, U32 right);
Time& operator /=(Time& left, F32 right);
Time& operator /=(Time& left, I64 right);
Time& operator /=(Time& left, U32 right);
F32 operator /(Time left, Time right);
Time operator %(Time left, Time right);
Time& operator %=(Time& left, Time right);

class Clock
{
	public:
		Clock();

		Time getElapsedTime() const;
		Time restart();

	private:
		Time mStart;
};

class StopWatch
{
	public:
		StopWatch();

		Time getElapsedTime() const;
		bool isRunning() const;
		void start();
		void stop();
		void reset(); // Reset and stop
		void restart(); // Reset and start

	private:
		Clock mClock;
		Time mTimeBuffer;
		bool mRunning;
};

class Timer
{
	public:
		Timer();
		virtual ~Timer();

		Time getRemainingTime() const;
		bool isRunning() const;
		bool isExpired() const;
		void start();
		void stop();
		virtual void reset(Time timeLimit); // Reset and stop
		virtual void restart(Time timeLimit); // Reset and restart

	private:
		StopWatch mStopWatch;
		Time mLimit;
};

class CallbackTimer : public Timer
{
	public:
		CallbackTimer();

		virtual void reset(Time timeLimit);
		virtual void restart(Time timeLimit);

		void update();
		Connection connect(std::function<void(CallbackTimer&)> unaryListener);
		Connection connect0(std::function<void()> nullaryListener);
		void clearConnections();

	private:
		using ListenerCtr = priv::ListenerSequence<CallbackTimer&>;

	private:
		ListenerCtr mListeners;
		bool mJustExpired;
};

} // namespace oe

#endif // OE_TIME_HPP