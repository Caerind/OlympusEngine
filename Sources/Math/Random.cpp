#include "Random.hpp"

#include "../Core/Time.hpp"

#include <sstream>

namespace oe
{

Random Random::mRandom;

I32 Random::getI32(I32 min, I32 max)
{
	ASSERT(min <= max);
	std::uniform_int_distribution<I32> distribution(min, max);
	return distribution(mRandom.mGenerator);
}

U32 Random::getU32(U32 min, U32 max)
{
	if (min > max)
	{
		U32 temp = min;
		max = min;
		min = temp;
	}
	std::uniform_int_distribution<U32> distribution(min, max);
	return distribution(mRandom.mGenerator);
}

F32 Random::getF32(F32 min, F32 max)
{
	ASSERT(min <= max);
	std::uniform_real_distribution<F32> distribution(min, max);
	return distribution(mRandom.mGenerator);
}

F32 Random::getF32Dev(F32 middle, F32 deviation)
{
	ASSERT(deviation >= 0.f);
	return getF32(middle - deviation, middle + deviation);
}

bool Random::getBool()
{
	return getI32(0, 1) == 1;
}

void Random::setSeed(const std::string& seed)
{
	mRandom.mSeed = seed;
	mRandom.mGenerator.seed(std::seed_seq(mRandom.mSeed.begin(), mRandom.mSeed.end()));
}

const std::string& Random::getSeed()
{
	return mRandom.mSeed;
}

Random::Random()
{
	std::ostringstream oss;
	oss << Time::getCurrentTime().asMicroseconds();
	setSeed(oss.str());
}

} // namespace oe