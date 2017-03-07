#ifndef OE_PROFILER_HPP
#define OE_PROFILER_HPP

#include "Prerequisites.hpp"
#include "Time.hpp"
#include "../Math/Math.hpp"
#include "Singleton.hpp"
#include <map>
#include <vector>
#include <set>

#if !(defined(NPROFILING) || defined(_NPROFILING))
#define Profile(a) oe::Profiler::ProfileIndividual mProfile(a);
#define ProfileBegin(a) oe::Profiler::getSingleton().beginProfile((a));
#define ProfileEnd(a) oe::Profiler::getSingleton().endProfile((a));
#else
#define Profile(a)
#define ProfileBegin(a)
#define ProfileEnd(a)
#endif

namespace oe
{

class Profiler : public Singleton<Profiler>
{
	public:
		Profiler();
		~Profiler();

		void beginProfile(const std::string& profileName);
		void endProfile(const std::string& profileName);

		void display();

		static Profiler* getSingletonPtr();
		static Profiler& getSingleton();

		class ProfileIndividual
		{
			public:
				ProfileIndividual(const std::string& profileName);
				~ProfileIndividual();

			private:
				std::string mName;
		};

	private:
		class ProfileInstance
		{
			public:
				ProfileInstance(const std::string& profileName);

				void display();

				std::string mName;
				U32 mCalls;
				Time mStart;
				Time mMin;
				Time mMax;
				Time mSumm;
		};

		std::vector<ProfileInstance> mProfiles;
};

} // namespace oe

#endif // OE_PROFILER_HPP
