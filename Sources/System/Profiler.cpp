#include "Profiler.hpp"
#include "Id.hpp"
#include "Logger.hpp"

namespace oe
{

template<> Profiler* Singleton<Profiler>::mSingleton = nullptr;

ProfilerFunctionCall::ProfilerFunctionCall(const std::string& name, U32 id, U32 parent)
	: mId(id)
	, mName(name)
	, mParent(parent)
{
}

void ProfilerFunctionCall::begin(U32 level)
{
	mLevel = level;
	mBegin = Time::getCurrentTime();
}

void ProfilerFunctionCall::end()
{
	mEnd = Time::getCurrentTime();
}

U32 ProfilerFunctionCall::getId() const
{
	return mId;
}

const std::string& ProfilerFunctionCall::getName() const
{
	return mName;
}

U32 ProfilerFunctionCall::getParent() const
{
	return mParent;
}

const Time& ProfilerFunctionCall::getBegin() const
{
	return mBegin;
}

const Time& ProfilerFunctionCall::getEnd() const
{
	return mEnd;
}

Time ProfilerFunctionCall::getDuration() const
{
	return mEnd - mBegin;
}

F32 ProfilerFunctionCall::getPercent(const Time& frameDuration) const
{
	return 100.f * getDuration() / frameDuration;
}

U32 ProfilerFunctionCall::getLevel() const
{
	return mLevel;
}

void ProfilerFunctionCall::addChild(U32 childId)
{
	mChildren.push_back(childId);
}

const std::vector<U32>& ProfilerFunctionCall::getChilren() const
{
	return mChildren;
}

bool ProfilerFunctionCall::hasChildren() const
{
	return !mChildren.empty();
}

bool ProfilerFunctionCall::isChild(U32 id) const
{
	for (U32 i = 0; i < mChildren.size(); i++)
	{
		if (mChildren[i] == id)
		{
			return true;
		}
	}
	return false;
}

ProfilerFrame::ProfilerFrame()
{
}

void ProfilerFrame::begin(U32 frameNumber)
{
	// Clear data
	mCalls.clear();
	mCurrent = nullptr;
	mLevel = 0;
	mIdCounter = 1;
	mFrameNumber = frameNumber;

	mBegin = Time::getCurrentTime();
}

void ProfilerFrame::end(bool importantFrame)
{
	ASSERT(mCurrent == nullptr); // A function hasn't been closed
	mImportant = importantFrame;
	mEnd = Time::getCurrentTime();
}

void ProfilerFrame::beginFunction(const std::string& name)
{
	if (mCurrent == nullptr)
	{
		mCalls.emplace_back(name, mIdCounter++);
		mLevel = 0;
	}
	else
	{
		U32 id = mIdCounter++;
		mCurrent->addChild(id);
		mCalls.emplace_back(name, id, mCurrent->getId());
		mLevel++;
	}

	mCurrent = &mCalls.back();

	ASSERT(mCurrent != nullptr);

	mCurrent->begin(mLevel);
}

void ProfilerFrame::endFunction()
{
	ASSERT(mCurrent != nullptr);

	mCurrent->end();

	UID parentId = mCurrent->getParent();
	if (parentId == 0)
	{
		mCurrent = nullptr;
		mLevel = 0;
	}
	else
	{
		for (U32 i = 0; i < mCalls.size(); i++)
		{
			if (mCalls[i].getId() == parentId)
			{
				mCurrent = &mCalls[i];
				mLevel--;
				return;
			}
		}
	}
}

const Time& ProfilerFrame::getBegin() const
{
	return mBegin;
}

const Time& ProfilerFrame::getEnd() const
{
	return mEnd;
}

Time ProfilerFrame::getDuration() const
{
	return mEnd - mBegin;
}

const std::vector<ProfilerFunctionCall>& ProfilerFrame::getCalls() const
{
	return mCalls;
}

U32 ProfilerFrame::getFrameNumber() const
{
	return mFrameNumber;
}

bool ProfilerFrame::isImportant() const
{
	return mImportant;
}

ProfilerDisplay::ProfilerDisplay()
	: mConnected(false)
{
	connect();
}

ProfilerDisplay::~ProfilerDisplay()
{
	if (isConnected())
	{
		disconnect();
	}
}

void ProfilerDisplay::connect()
{
	if (mConnected)
	{
		return;
	}
	if (Profiler::getSingletonPtr() != nullptr)
	{
		mConnected = true;
		Profiler::getSingleton().connectDisplay(this);
	}
	else
	{
		error("Can't connect ProfilerDisplay if Profiler hasn't been created");
	}
}

void ProfilerDisplay::disconnect()
{
	if (!mConnected)
	{
		return;
	}
	if (Profiler::getSingletonPtr() != nullptr)
	{
		mConnected = false;
		Profiler::getSingleton().disconnectDisplay(this);
	}
	else
	{
		error("Can't disconnect ProfilerDisplay if Profiler hasn't been created");
	}
}

bool ProfilerDisplay::isConnected() const
{
	return mConnected;
}

Profiler::Profiler()
	: mFrameNumber(0)
{
}

Profiler::~Profiler()
{
}

void Profiler::beginFrame()
{
	mProfilerFrame.begin(mFrameNumber++);
}

void Profiler::endFrame(bool importantFrame)
{
	mProfilerFrame.end(importantFrame);
	for (U32 i = 0; i < mProfilerDisplays.size(); i++)
	{
		mProfilerDisplays[i]->displayFrame(mProfilerFrame);
	}
}

void Profiler::beginFunction(const std::string& name)
{
	mProfilerFrame.beginFunction(name);
}

void Profiler::endFunction()
{
	mProfilerFrame.endFunction();
}

void Profiler::connectDisplay(ProfilerDisplay* display)
{
	if (display == nullptr)
	{
		return;
	}
	bool found = false;
	for (U32 i = 0; i < mProfilerDisplays.size(); i++)
	{
		if (mProfilerDisplays[i] == display)
		{
			found = true;
		}
	}
	if (!found)
	{
		mProfilerDisplays.push_back(display);
	}
}

void Profiler::disconnectDisplay(ProfilerDisplay* display)
{
	for (auto itr = mProfilerDisplays.begin(); itr != mProfilerDisplays.end(); ++itr)
	{
		if (display == *itr)
		{
			mProfilerDisplays.erase(itr);
			return;
		}
	}
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

Profile::Profile(const std::string& functionName)
{
	Profiler::getSingleton().beginFunction(functionName);
}

Profile::~Profile()
{
	Profiler::getSingleton().endFunction();
}

ConsoleProfiler::ConsoleProfiler()
	: ProfilerDisplay()
{
}

ConsoleProfiler::~ConsoleProfiler()
{
	if (isConnected())
	{
		disconnect();
	}
}

void ConsoleProfiler::displayFrame(const ProfilerFrame& frame)
{
    #ifdef _MSC_VER
        system("cls");
	#else
        printf("\e[1;1H\e[2J"); // Should work on ANSI
	#endif

	printf("Frame %u, duration : %I64dus\n", frame.getFrameNumber(), frame.getDuration().asMicroseconds());
	for (const auto& fu : frame.getCalls())
	{
		U32 level = fu.getLevel();
		for (U32 i = 0; i < level; i++)
		{
			printf(" ");
		}
		printf("-%s, duration : %I64dus, percent : %f\n", fu.getName().c_str(), fu.getDuration().asMicroseconds(), fu.getPercent(frame.getDuration()));

	}
}

} // namespace oe
