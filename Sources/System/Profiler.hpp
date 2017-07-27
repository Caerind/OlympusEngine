#ifndef OE_PROFILER_HPP
#define OE_PROFILER_HPP

#include "Prerequisites.hpp"
#include "Time.hpp"
#include "Singleton.hpp"

namespace oe
{

class ProfilerFunctionCall
{
	public:
		ProfilerFunctionCall(const std::string& name, U32 id, U32 parent = 0);

		void begin(U32 level);
		void end();

		U32 getId() const;
		const std::string& getName() const;
		U32 getParent() const;
		const Time& getBegin() const;
		const Time& getEnd() const;
		Time getDuration() const;
		F32 getPercent(const Time& frameDuration) const;
		U32 getLevel() const;

		void addChild(U32 childId);
		const std::vector<U32>& getChilren() const;
		bool hasChildren() const;
		bool isChild(U32 id) const;

	private:
		U32 mId;
		std::string mName;
		U32 mParent;
		Time mBegin;
		Time mEnd;
		U32 mLevel;
		std::vector<U32> mChildren;
};

class ProfilerFrame
{
	public:
		ProfilerFrame();

		void begin(U32 frameNumber);
		void end(bool important);

		void beginFunction(const std::string& name);
		void endFunction();

		const Time& getBegin() const;
		const Time& getEnd() const;
		Time getDuration() const;
		const std::vector<ProfilerFunctionCall>& getCalls() const;
		U32 getFrameNumber() const;
		bool isImportant() const;

	private:
		Time mBegin;
		Time mEnd;
		U32 mLevel;
		U32 mFrameNumber;
		bool mImportant;

		U32 mIdCounter;

		ProfilerFunctionCall* mCurrent;
		std::vector<ProfilerFunctionCall> mCalls;
};

class ProfilerDisplay
{
	public:
		ProfilerDisplay();
		virtual ~ProfilerDisplay();

		void connect();
		void disconnect();
		bool isConnected() const;

		virtual void displayFrame(const ProfilerFrame& frame) = 0;

	private:
		bool mConnected;
};

// TODO : Separate to another thread because it slow the run quite a lot
class ConsoleProfiler : public ProfilerDisplay
{
	public:
		ConsoleProfiler();
		virtual ~ConsoleProfiler();

		virtual void displayFrame(const ProfilerFrame& frame);
};

class Profiler : public Singleton<Profiler>
{
	public:
		Profiler();
		~Profiler();

		void beginFrame();
		void endFrame(bool keepFrame = true);

		void beginFunction(const std::string& name);
		void endFunction();

		void connectDisplay(ProfilerDisplay* display);
		void disconnectDisplay(ProfilerDisplay* display);

		static Profiler* getSingletonPtr();
		static Profiler& getSingleton();

	private:
		U32 mFrameNumber;
		ProfilerFrame mProfilerFrame;
		std::vector<ProfilerDisplay*> mProfilerDisplays;
};

class Profile
{
	public:
		Profile(const std::string& functionName);
		~Profile();
};

#define OE_PROFILE_FUNCTION(functionName) oe::Profile functionProfile(functionName);

} // namespace oe

#endif // OE_PROFILER_HPP
