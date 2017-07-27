#ifndef OE_RENDERSYSTEM_HPP
#define OE_RENDERSYSTEM_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include "../../Graphics/DebugDraw.hpp"
#include "../../Graphics/View.hpp"

#include "../EntityQuery.hpp"

namespace oe
{

class RenderSystem
{
	public:
		RenderSystem(World& world);
		~RenderSystem();

		void clearDebugDraw();
		void render(sf::RenderTarget& target);

		View& getView();
		void setView(const View& view);

		void setBackgroundColor(const Color& color);
		const Color& getBackgroundColor() const;

		void setQuerySelector(EntityQuery::Selector selector);

		void setDebugVisible(bool visible);
		bool isDebugVisible() const;

	private:
		void preRender(const sf::Vector2u& size);
		void render();
		void postRender(sf::RenderTarget& target);

		static bool sortEntities(const Entity* a, const Entity* b);

	private:
		World& mWorld;

		sf::RenderTexture mTexture;

		EntityQuery mQuery;

		DebugDraw mDebugDraw;

		View mView;

		Color mBackgroundColor;
};

} // namespace oe

#endif // OE_RENDERSYSTEM_HPP
