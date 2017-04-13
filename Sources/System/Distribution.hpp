#ifndef OE_DISTRIBUTION_HPP
#define OE_DISTRIBUTION_HPP

#include <functional>
#include <type_traits>

#include <SFML/Graphics/Rect.hpp>

#include "../Math/Random.hpp"
#include "../Math/Vector2.hpp"
#include "Time.hpp"
#include "Color.hpp"

namespace oe
{

namespace priv
{
	template <typename T>
	struct Constant
	{
		explicit Constant(T value)
			: value(value)
		{
		}

		T operator()() const
		{
			return value;
		}

		T value;
	};
} // namespace priv

template <typename T>
class Distribution
{
	public:
        Distribution(T constant)
        : mFactory(priv::Constant<T>(constant))
		{
		}

        Distribution(std::function<T()> function)
		: mFactory(function)
		{
		}

		T operator()() const
		{
			return mFactory();
		}

	private:
		std::function<T()> mFactory;
};

namespace Distributions
{

Distribution<I32> uniform(I32 min, I32 max);
Distribution<U32> uniform(U32 min, U32 max);
Distribution<F32> uniform(F32 min, F32 max);
Distribution<Time> uniform(Time min, Time max);
Distribution<Vector2> rect(const Vector2& center, const Vector2& halfSize);
Distribution<Vector2> rect(F32 x, F32 y, F32 w, F32 h);
Distribution<Vector2> circle(const Vector2& center, F32 radius);
Distribution<Vector2> deflect(const Vector2& direction, F32 maxRotation);
Distribution<Vector2> project(const Vector2& direction, F32 maxRotation, F32 minVel, F32 maxVel);
Distribution<Color> colorGrade(const Color& color, F32 min, F32 max);
Distribution<Color> colorGrey(const Color& color, U8 min, U8 max);

template <typename T>
Distribution<T> uniformT(T min, T max)
{
	ASSERT(min <= max);
    return Distribution<T>([=] () -> T
    {
        return Random::get(min, max);
    });
}

} // namespace Distributions

} // namespace oe

#endif // OE_DISTRIBUTION_HPP
