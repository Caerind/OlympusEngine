#ifndef OE_TIMESYSTEM_HPP
#define OE_TIMESYSTEM_HPP

#include <functional>
#include <map>

#include "../../System/Time.hpp"

namespace oe
{
	
using TimerId = U32;

class TimeSystem
{
	public:
		TimeSystem();

		void setSpeedFactor(F32 factor);
		F32 getSpeedFactor() const;

		void update(Time dt);

		struct CTimer // Struct made to not use CallbackTimer : because it calls getElapsedTime too many times
		{
			Time elapsed;
			Time duration;
			OeSignal(onExpire, Time /* duration */);
		};
		
		template<typename... ConnectArgs>
		TimerId addTimer(Time duration, Signal<Time>::ConnectionGuard& slot, ConnectArgs&&... args);
		CTimer* getTimer(TimerId id);
		void removeTimer(TimerId id);

	private:
		F32 mSpeedFactor;
		std::map<U32, CTimer> mTimers;
};

template<typename... ConnectArgs>
TimerId TimeSystem::addTimer(Time duration, Signal<Time>::ConnectionGuard& slot, ConnectArgs&&... args)
{
	static TimerId counter = 0;
	counter++;
	mTimers[counter].elapsed = Time::Zero;
	mTimers[counter].duration = duration;
	slot.connect(mTimers[counter].onExpire, std::forward<ConnectArgs>(args)...);
	return counter;
}

} // namespace oe

#endif // OE_TIMESYSTEM_HPP
