#ifndef OE_DEBUGDRAW_HPP
#define OE_DEBUGDRAW_HPP

#include "Prerequisites.hpp"
#include "Singleton.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Color.hpp"

namespace oe
{

class DebugDraw : public Singleton<DebugDraw>
{
	public:
		DebugDraw();
		
		static DebugDraw& getSingleton();
		static DebugDraw* getSingletonPtr();

		static bool instanced();

		static void clear();

		static void drawPoint(F32 x, F32 y, const Color& color = Color::Red, F32 r = 2.0f);
		static void drawRect(F32 x, F32 y, F32 w, F32 h, const Color& c1 = Color::Red, const Color& c2 = Color::Transparent);
		
		static void render(sf::RenderTarget& target);
		
	private:
		std::vector<sf::Drawable*> mDrawables;
};

} // namespace oe

#endif // OE_DEBUGDRAW_HPP