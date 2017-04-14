#ifndef OE_TEXTCOMPONENT_HPP
#define OE_TEXTCOMPONENT_HPP

#include "../RenderableComponent.hpp"

#include "../../System/Color.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

namespace oe
{

class TextComponent : public RenderableComponent
{
	public:
		TextComponent(Entity& entity);

		void setFont(ResourceId font);
		void setFont(sf::Font& font);
		const sf::Font* getFont() const;

		void setString(const std::string& string);
		const std::string& getString() const;

		void setFillColor(const oe::Color& color);
		void setFillColor(const sf::Color& color);
		const sf::Color& getFillColor() const;

		void setOutlineColor(const oe::Color& color);
		void setOutlineColor(const sf::Color& color);
		const sf::Color& getOutlineColor() const;

		void setOutlineThickness(F32 thickness);
		F32 getOutlineThickness() const;

		void setCharacterSize(U32 size);
		U32 getCharacterSize() const;

		virtual void render(sf::RenderTarget& target);

	private:
		sf::Text mText;
		std::string mString;
};

} // namespace oe

#endif // OE_TEXTCOMPONENT_HPP
