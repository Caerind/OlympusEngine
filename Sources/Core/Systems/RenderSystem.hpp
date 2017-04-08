#ifndef OE_RENDERSYSTEM_HPP
#define OE_RENDERSYSTEM_HPP

#include "../RenderableComponent.hpp"
#include "../ComponentList.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

namespace oe
{

class RenderSystem
{
	public:
		RenderSystem();

		void registerRenderable(RenderableComponent* renderable);
		void unregisterRenderable(RenderableComponent* renderable);

		void preRender();
		void render();
		void postRender(sf::RenderTarget& target);

		void needUpdateOrderZ();
		void needUpdateOrderY();

	private:
		static bool orderZ(RenderableComponent* a, RenderableComponent* b);
		static bool orderY(RenderableComponent* a, RenderableComponent* b);

	private:
		sf::RenderTexture mTexture;

		RenderableComponentList mRenderables;

		bool mNeedUpdateOrderZ;
		bool mNeedUpdateOrderY;
};

} // namespace oe

#endif // OE_RENDERSYSTEM_HPP
