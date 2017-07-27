#ifndef OE_RENDERABLECOMPONENT_HPP
#define OE_RENDERABLECOMPONENT_HPP

#include "SceneComponent.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace oe
{

class RenderSystem;
class RenderableComponent : public SceneComponent
{
	public:
		RenderableComponent(Entity& entity, bool attachedToEntity = true);
		
		virtual void render(sf::RenderTarget& target);

		bool isVisible() const;
		void setVisible(bool visible);

		RenderSystem& getRenderSystem();

		virtual void onCreate();

		void onRenderableComponentInvalidated(const Node* node);
		void onRenderableComponentInvalidatedZ(const Node* node);
		OeSlot(oe::Node, onNodeInvalidation, mRenderableComponentInvalidationSlot);
		OeSlot(oe::Node, onNodeInvalidationZ, mRenderableComponentInvalidationZSlot);

		virtual void registerComponent();
		virtual void unregisterComponent();

	protected:
		bool mVisible;
};

} // namespace oe

#endif // OE_RENDERABLECOMPONENT_HPP
