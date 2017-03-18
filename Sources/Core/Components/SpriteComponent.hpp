#ifndef OE_SPRITECOMPONENT_HPP
#define OE_SPRITECOMPONENT_HPP

#include "../SceneComponent.hpp"
#include "../../System/Id.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace oe
{

class SpriteComponent : public SceneComponent
{
	public:
		SpriteComponent();

		void setTexture(sf::Texture& texture);
		const sf::Texture* getTexture() const;

		void setTextureRect(const sf::IntRect& textureRect);
		const sf::IntRect& getTextureRect() const;

		void setColor(const Color& color);
		const Color& getColor() const;

		void setVisible(bool visible);
		bool isVisible() const;

		void render(sf::RenderTarget& target) const;

	private:
		virtual void onAttach();
		virtual void onDetach();

	private:
		sf::Sprite mSprite;
		bool mVisible;
};

} // namespace oe

#endif // OE_SPRITECOMPONENT_HPP
