#ifndef OE_RENDERSYSTEM_HPP
#define OE_RENDERSYSTEM_HPP

#include "../Components/SpriteComponent.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

namespace oe
{

class RenderSystem
{
	public:
		RenderSystem();

		void registerSprite(SpriteComponent* sprite);
		void unregisterSprite(SpriteComponent* sprite);

		void preRender();
		void render();
		void postRender(sf::RenderTarget& target);

	private:
		sf::RenderTexture mTexture;

		std::vector<SpriteComponent*> mSprites;
};

} // namespace oe

#endif // OE_RENDERSYSTEM_HPP
