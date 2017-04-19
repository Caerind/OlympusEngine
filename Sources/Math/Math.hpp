#ifndef OE_MATH
#define OE_MATH

#include "../System/Prerequisites.hpp"

#include <cmath>
#include <cstring>

namespace oe
{

class Math
{
	public:
		static inline F32 abs(F32 x)
		{
			return std::abs(x);
		}

		static inline F32 lerp(F32 start, F32 end, F32 percent)
		{
			return start * (1.f - percent) + end * percent;
		}

		static inline bool inRange(F32 value, F32 start, F32 end)
		{
			return start <= value && value < end;
		}

		static inline bool equals(F32 a, F32 b, F32 epsilon = 1e-5f)
		{
			return fabs(a - b) < epsilon;
		}

		static inline F32 sqrt(F32 value)
		{
			return std::sqrt(value);
		}

		static inline F32 pi()
		{
			return 3.141592653589793f;
		}

		static inline F32 halfPi()
		{
			return 1.57079632679f;
		}

		static inline F32 radToDeg(F32 rad)
		{
			F32 angle = 57.29577951308233f * rad;
			while (angle < 0.f)
			{
				angle += 360.f;
			}
			while (angle > 360.f)
			{
				angle -= 360.f;
			}
			return angle;
		}

		static inline F32 degToRad(F32 deg)
		{
			return 0.01745329251994f * deg;
		}

		static inline F32 cos(F32 deg)
		{
			return std::cos(degToRad(deg));
		}

		static inline F32 sin(F32 deg)
		{
			return std::sin(degToRad(deg));
		}

		static inline F32 tan(F32 deg)
		{
			return std::tan(degToRad(deg));
		}

		static inline F32 acos(F32 value)
		{
			return radToDeg(std::acos(value));
		}

		static inline F32 asin(F32 value)
		{
			return radToDeg(std::asin(value));
		}

		static inline F32 atan(F32 value)
		{
			return radToDeg(std::atan(value));
		}

		static inline F32 atan2(F32 valueY, F32 valueX)
		{
			return radToDeg(std::atan2(valueY, valueX));
		}

		class Average
		{
			public:
				Average()
					: mAverage()
					, mCount(0)
				{
				}

				template <typename T>
				inline F32 add(const T& term)
				{
					mAverage = ((mAverage * mCount) + static_cast<F32>(term)) * (1.f / (mCount + 1));
					mCount++;
					return mAverage;
				}

				inline F32 get() const
				{
					return mAverage;
				}

				inline U32 getCount() const
				{
					return mCount;
				}

			private:
				F32 mAverage;
				U32 mCount;
		};
};

} // namespace oe

#endif // OE_MATH
