#ifndef OE_MATH
#define OE_MATH

#include "../Config.hpp"

namespace oe
{

template <class T>
T min(const T& a, const T& b)
{
	return std::min<T>(a, b);
}

template <class T>
T max(const T& a, const T& b)
{
	return std::max<T>(a, b);
}

template <class T>
T clamp(const T& value, const T& lower, const T& upper)
{
	return std::max<T>(lower, std::min<T>(value, upper));
}

template <class T, class T2>
T lerp(const T& start, const T& end, const T2& percent) 
{
	const T2 one_minus_percent = static_cast<T2>(1.0) - percent;
	return start * one_minus_percent + end * percent;
}

template <class T>
T lerp(const T& start, const T& end, const T& percent) 
{
	return Lerp<T, T>(start, end, percent);
}

template <class T>
bool inRange(const T& value, const T& start, const T& end)
{
	return value >= start && value < end;
}

F32 floor(F32 value);
F32 ceil(F32 value);
F32 abs(F32 value);
F32 sqrt(F32 value);
bool equals(F32 a, F32 b, F32 epsilon = 0.f);

template <class T>
T roundUpToPowerOf2(T value)
{
	return static_cast<T>(pow(static_cast<T>(2), ceil(log(value) / log(static_cast<T>(2)))));
}

template <>
inline I32 roundUpToPowerOf2(I32 value) 
{
	value--;
	value |= value >> 1;
	value |= value >> 2;
	value |= value >> 4;
	value |= value >> 8;
	value |= value >> 16;
	value++;
	return value;
}

template <typename T>
U32 roundUpToTypeBoundary(U32 v) 
{
	return (v + sizeof(T) - 1) & ~(sizeof(T) - 1);
}

F32 pi();
F32 halfPi();
F32 radToDeg(F32 rad);
F32 degToRad(F32 deg);
F32 cos(F32 deg);
F32 sin(F32 deg);
F32 tan(F32 deg);
F32 acos(F32 value);
F32 asin(F32 value);
F32 atan(F32 value);
F32 atan2(F32 valY, F32 valX);

template <typename T>
class Average
{
	public:
		Average()
			: mAverage(T())
			, mCount(0)
		{
		}

		T add(T term)
		{
			mAverage = ((mAverage * mCount) + term);
			//*1.f / (mCount + 1);
			mCount++;
			return mAverage;
		}

		T get() const
		{
			return mAverage;
		}

		U32 getCount() const
		{
			return mCount;
		}

	private:
		T mAverage;
		U32 mCount;
};

} // namespace oe

#endif // OE_MATH
