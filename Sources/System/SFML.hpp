#ifndef OE_SFML_HPP
#define OE_SFML_HPP

#include "Color.hpp"
#include "Time.hpp"
#include "../Math/Matrix4.hpp"
#include "../Math/Vector2.hpp"
#include "../Math/Vector3.hpp"
#include "Vector2i.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>

#include "DebugDraw.hpp"

namespace oe
{

inline Color toOE(const sf::Color& color)
{
	return Color(color.r, color.g, color.b, color.a);
}
inline sf::Color toSF(const Color& color)
{
	return sf::Color(color.r, color.g, color.b, color.a);
}

inline Matrix4 toOE(const sf::Transform& transform)
{
	return Matrix4(transform.getMatrix()[0], transform.getMatrix()[1], transform.getMatrix()[2],  transform.getMatrix()[3],
	               transform.getMatrix()[4], transform.getMatrix()[5], transform.getMatrix()[6],  transform.getMatrix()[7],
			       transform.getMatrix()[8], transform.getMatrix()[9], transform.getMatrix()[10], transform.getMatrix()[11],
			       transform.getMatrix()[12], transform.getMatrix()[13], transform.getMatrix()[14], transform.getMatrix()[15]);
}
inline sf::Transform toSF(const Matrix4& transform)
{
	return sf::Transform(transform(0, 0), transform(0, 1), transform(0, 3),
	                     transform(1, 0), transform(1, 1), transform(1, 3),
						 transform(3, 0), transform(3, 1), transform(3, 3));
}

inline Vector2i toOE(const sf::Vector2u& vector)
{
	return Vector2i((I32)vector.x, (I32)vector.y);
}
inline Vector2i toOE(const sf::Vector2i& vector)
{
	return Vector2i(vector.x, vector.y);
}
inline sf::Vector2i toSF(const Vector2i& vector)
{
	return sf::Vector2i(vector.x, vector.y);
}
	
inline Vector2 toOE(const sf::Vector2f& vector)
{
	return Vector2(vector.x, vector.y);
}
inline sf::Vector2f toSF(const Vector2& vector)
{
	return sf::Vector2f(vector.x, vector.y);
}

inline Vector3 toOE(const sf::Vector3f& vector)
{
	return Vector3(vector.x, vector.y, vector.z);
}	
inline sf::Vector3f toSF(const Vector3& vector)
{
	return sf::Vector3f(vector.x, vector.y, vector.z);
}

inline oe::Time toOE(const sf::Time& time)
{
	return oe::microseconds(time.asMicroseconds());
}
inline sf::Time toSF(const oe::Time& time)
{
	return sf::microseconds(time.asMicroseconds());
}

} // namespace oe

#endif // OE_SFML_HPP
