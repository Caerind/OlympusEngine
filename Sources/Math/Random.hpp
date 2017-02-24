#ifndef OE_RANDOM_HPP
#define OE_RANDOM_HPP

#include <random>

#include "../Core/Prerequisites.hpp"

namespace oe
{

class Random
{
    public:
        static I32 getI32(I32 min, I32 max);
        static U32 getU32(U32 min, U32 max);
        static F32 getF32(F32 min, F32 max);
		static F32 getF32Dev(F32 middle, F32 deviation);
		static bool getBool();
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
		}

	private:
		std::vector<std::pair<F32, T>> mTable;
		F32 mSum;
};

} // namespace oe

#endif // OE_RANDOM_HPP
