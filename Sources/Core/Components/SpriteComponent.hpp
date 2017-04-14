#ifndef OE_SPRITECOMPONENT_HPP
#define OE_SPRITECOMPONENT_HPP

#include "../RenderableComponent.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace oe
{

class SpriteComponent : public RenderableComponent
{
	public:
		SpriteComponent(Entity& entity);

		void setTexture(ResourceId texture);
		void setTexture(sf::Texture& texture);
		const sf::Texture* getTexture() const;

		void setTextureRect(const sf::IntRect& textureRect);
		const sf::IntRect& getTextureRect() const;

		void setColor(const Color& color);
		Color getColor() const;

		virtual void render(sf::RenderTarget& target);

	protected:
		sf::Sprite mSprite;
};

} // namespace oe

#endif // OE_SPRITECOMPONENT_HPP
