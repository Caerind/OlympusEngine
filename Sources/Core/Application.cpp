#include "Application.hpp"

namespace oe
{

template <> Application* Singleton<Application>::mSingleton = nullptr;

Application::Application()
	: mRunning(true)
{
}

bool Application::run() const
{
	return mRunning;
}

void Application::stop()
{
	mRunning = false;
}

Application& Application::getSingleton()
{
	ASSERT(mSingleton != nullptr);
	return *mSingleton;
}

Application* Application::getSingletonPtr()
{
	return mSingleton;
}

} // namespace oe