#ifndef OE_VIEW_HPP
#define OE_VIEW_HPP

#include <SFML/Graphics/View.hpp>
#include "SFML.hpp"

namespace oe
{

// TODO : Add rotation
// TODO : Add viewport

class View
{
	public:
		View();
		View(F32 x, F32 y, F32 w, F32 h);
		View(const Vector2& center, const Vector2& size);
		View(const sf::View& view);

		void setCenter(F32 x, F32 y);
		void setCenter(const Vector2& center);
		Vector2 getCenter() const;

		void setSize(F32 w, F32 h);
		void setSize(const Vector2& size);
		Vector2 getSize() const;

		void setZoom(F32 factor);
		F32 getZoom() const;

		void move(F32 x, F32 y);
		void move(const Vector2& offset);

		void zoom(F32 factor);

		void reset(F32 x, F32 y, F32 w, F32 h);

		sf::FloatRect getBounds() const;

		const sf::View& getHandle() const;
		void setHandle(const sf::View& view);

	private:
		sf::View mView;
		F32 mZoomFactor;
};

} // namespace oe

#endif // OE_VIEW_HPP