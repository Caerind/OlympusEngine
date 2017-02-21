#include "Thread.hpp"

namespace oe
{

U32 Thread::mMainThreadId = 0;

Thread::Thread()
{
	mId = std::hash<std::thread::id>()(mThread.get_id());
	initMainThreadId();
}

Thread::Thread(Thread&& x)
{
	x.mThread.swap(mThread);
	mId = std::hash<std::thread::id>()(mThread.get_id());
}

void Thread::operator=(Thread&& x)
{
	x.mThread.swap(mThread);
	mId = std::hash<std::thread::id>()(mThread.get_id());
}

U32 Thread::getMainId()
{
	initMainThreadId();
	return mMainThreadId;
}

U32 Thread::getThisId()
{
	return std::hash<std::thread::id>()(std::this_thread::get_id());
}

void Thread::terminate()
{
	std::terminate();
}

void Thread::sleep(Time duration)
{
	std::this_thread::sleep_for(std::chrono::microseconds(duration.asMicroseconds()));
}

U32 Thread::getId() const
{
	return mId;
}

void Thread::wait()
{
	mThread.join();
}

void Thread::initMainThreadId()
{
	if (mMainThreadId == 0)
	{
		mMainThreadId = Thread::getThisId();
	}
}

Mutex::Mutex()
{
}

void Mutex::lock()
{
	mMutex.lock();
}

void Mutex::unlock()
{
	mMutex.unlock();
}

Lock::Lock(Mutex& mutex)
	: mMutex(mutex)
{
	mMutex.lock();
}

Lock::~Lock()
{
	mMutex.unlock();
}

} // namespace oe