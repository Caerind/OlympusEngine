#ifndef OE_THREAD_HPP
#define OE_THREAD_HPP

#include "Prerequisites.hpp"
#include "Time.hpp"

#include <mutex>
#include <thread>

namespace oe
{

class Thread
{
	public:
		template <typename Fn, typename ... Args>
		Thread(Fn&& fn, Args&& ... args);

		// Default
		Thread();

		// Remove copy
		Thread(const Thread&) = delete;

		// Move
		Thread(Thread&& x);
		void operator=(Thread&& x);

		static U32 getMainId();
		static U32 getThisId();

		static void terminate();
		static void sleep(Time duration);

		U32 getId() const;
		void wait();

	private:
		static void initMainThreadId();

	private:
		std::thread mThread;
		U32 mId;
		static U32 mMainThreadId;
};

class Mutex
{
	public:
		Mutex();
		void lock();
		void unlock();

	private:
		std::mutex mMutex;
};

class Lock
{
	public:
		Lock(Mutex& mutex);
		~Lock();

	private:
		Mutex& mMutex;
};

template<typename Fn, typename ...Args>
Thread::Thread(Fn && fn, Args && ...args) : mThread(fn, std::forward<Args>(args)...)
{
	mId = std::hash<std::thread::id>()(mThread.get_id());
	initMainThreadId();
}

} // namespace oe

#endif // OE_THREAD_HPP
