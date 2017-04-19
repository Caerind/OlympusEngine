#ifndef OE_RANDOM_HPP
#define OE_RANDOM_HPP

#include <random>

#include "Math.hpp"

namespace oe
{

namespace priv
{

template<typename T>
inline T getRandom(std::mt19937& generator, T min, T max) { return T(); }

template<typename T>
inline T getRandomDev(std::mt19937& generator, T middle, T deviation) { return T(); }

template<>
inline I32 getRandom(std::mt19937& generator, I32 min, I32 max)
{
    ASSERT(min <= max);
    std::uniform_int_distribution<I32> distribution(min, max);
    return distribution(generator);
}

template<>
inline U32 getRandom(std::mt19937& generator, U32 min, U32 max)
{
    ASSERT(min <= max);
    std::uniform_int_distribution<U32> distribution(min, max);
    return distribution(generator);
}

template<>
inline F32 getRandom(std::mt19937& generator, F32 min, F32 max)
{
    ASSERT(min <= max);
    std::uniform_real_distribution<F32> distribution(min, max);
    return distribution(generator);
}

template<>
inline I32 getRandomDev(std::mt19937& generator, I32 middle, I32 deviation)
{
    ASSERT(deviation >= 0);
    return getRandom(generator, middle - deviation, middle + deviation);
}

template<>
inline U32 getRandomDev(std::mt19937& generator, U32 middle, U32 deviation)
{
    return getRandom(generator, middle - deviation, middle + deviation);
}

template<>
inline F32 getRandomDev(std::mt19937& generator, F32 middle, F32 deviation)
{
    ASSERT(deviation >= 0.0f);
    return getRandom(generator, middle - deviation, middle + deviation);
}

} // namespace priv

class Random
{
    public:
		template<typename T>
		static T get(T min, T max)
		{
            return priv::getRandom<T>(mRandom.mGenerator, min, max);
		}

		template<typename T>
		static T getDev(T middle, T deviation)
		{
		    return priv::getRandomDev<T>(mRandom.mGenerator, middle, deviation);
		}

		static bool getBool()
		{
			return get<I32>(0, 1) == 1;
		}

		static void setSeed(const std::string& seed);

		static const std::string& getSeed();

	private:
        Random();

    private:
        static Random mRandom;
        std::mt19937 mGenerator;
        std::string mSeed;
};

template <typename T>
class RandomTable
{
	public:
		RandomTable() : mTable(), mSum(0.0f)
		{
		}

		void add(F32 percent, const T& value)
		{
			mTable.push_back(std::make_pair(percent, value));
			mSum += percent;
		}

		T get()
		{
			F32 value = Random::get(0.0f, mSum);
			for (std::size_t i = 0; i < mTable.size(); i++)
			{
				value -= mTable[i].first;
				if (value <= 0.f)
				{
					return mTable[i].second;
				}
			}
			return T();
		}

	private:
		std::vector<std::pair<F32, T>> mTable;
		F32 mSum;
};

} // namespace oe

#endif // OE_RANDOM_HPP
