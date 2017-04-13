#include "Distribution.hpp"

namespace oe
{

namespace Distributions
{

Distribution<I32> uniform(I32 min, I32 max)
{
    return uniformT(min, max);
}

Distribution<U32> uniform(U32 min, U32 max)
{
    return uniformT(min, max);
}

Distribution<F32> uniform(F32 min, F32 max)
{
    return uniformT(min, max);
}

Distribution<Time> uniform(Time min, Time max)
{
	ASSERT(min <= max);
    const F32 floatMin = min.asSeconds();
    const F32 floatMax = max.asSeconds();
    return Distribution<Time>([=] () -> Time
    {
        return seconds(Random::get(floatMin, floatMax));
    });
}

Distribution<Vector2> rect(const Vector2& center, const Vector2& halfSize)
{
    return Distribution<Vector2>([=] () -> Vector2
    {
        return Vector2(Random::getDev(center.x, halfSize.x), Random::getDev(center.y, halfSize.y));
    });
}

Distribution<Vector2> rect(F32 x, F32 y, F32 w, F32 h)
{
	return Distribution<Vector2>([=]() -> Vector2
	{
		return Vector2(x + Random::get(0.0f, w), y + Random::get(0.0f, h));
	});
}

Distribution<Vector2> circle(const Vector2& center, F32 radius)
{
    return Distribution<Vector2>([=] () -> Vector2
    {
        return center + Vector2::polarVector(Random::get(0.0f, 360.0f), radius * Random::get(0.0f, 1.0f));
    });
}

Distribution<Vector2> deflect(const Vector2& direction, F32 maxRotation)
{
    return Distribution<Vector2>([=] () -> Vector2
    {
        return direction.getRotated(Random::getDev(0.0f, maxRotation));
    });
}

Distribution<Vector2> project(const Vector2& direction, F32 maxRotation, F32 minVel, F32 maxVel)
{
	return Distribution<Vector2>([=]() -> Vector2
	{
		return (direction * Random::get(minVel, maxVel)).getRotated(Random::getDev(0.f, maxRotation));
	});
}

Distribution<Color> colorGrade(const Color& color, F32 min, F32 max)
{
	return Distribution<Color>([=]() -> Color
	{
		F32 r = color.r * Random::get(min, max);
		F32 g = color.g * Random::get(min, max);
		F32 b = color.b * Random::get(min, max);
		return Color((U8)r, (U8)g, (U8)b);
	});
}

Distribution<Color> colorGrey(const Color& color, U8 min, U8 max)
{
	return Distribution<Color>([=]() -> Color
	{
		U8 c = Random::get(min, max);
		return Color(c, c, c);
	});
}

} // namespace Distributions

} // namespace ke