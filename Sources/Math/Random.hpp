#ifndef OE_RANDOM_HPP
#define OE_RANDOM_HPP

#include <random>

#include "Math.hpp"

namespace oe
{

class Random
{
    public:
		template<typename T>
		static T get(T min, T max)
		{
			return T();
		}

		template<>
		static I32 get(I32 min, I32 max)
		{
			ASSERT(min <= max);
			std::uniform_int_distribution<I32> distribution(min, max);
			return distribution(mRandom.mGenerator);
		}

		template<>
        static U32 get(U32 min, U32 max)
		{
			ASSERT(min <= max);
			std::uniform_int_distribution<U32> distribution(min, max);
			return distribution(mRandom.mGenerator);
		}

		template<>
        static F32 get(F32 min, F32 max)
		{
			ASSERT(min <= max);
			std::uniform_real_distribution<F32> distribution(min, max);
			return distribution(mRandom.mGenerator);
		}

		template<typename T>
		static T getDev(T middle, T deviation)
		{
			return T();
		}

		template<>
		static I32 getDev(I32 middle, I32 deviation)
		{
			ASSERT(deviation >= 0);
			return get(middle - deviation, middle + deviation);
		}

		template<>
		static U32 getDev(U32 middle, U32 deviation)
		{
			return get(middle - deviation, middle + deviation);
		}

		template<>
		static F32 getDev(F32 middle, F32 deviation)
		{
			ASSERT(deviation >= 0.f);
			return get(middle - deviation, middle + deviation);
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
		RandomTable() : mTable(), mSum(0.f) 
		{
		}

		void add(F32 percent, const T& value) 
		{ 
			mTable.push_back(std::make_pair(percent, value)); 
			mSum += percent; 
		}

		T get()
		{
			float value = Random::getFloat(0, mSum);
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
