#include "Random.hpp"

#include "../System/Time.hpp"

#include <sstream>

namespace oe
{

Random Random::mRandom;

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