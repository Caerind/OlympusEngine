#ifndef OE_SCENECOMPONENT_HPP
#define OE_SCENECOMPONENT_HPP

#include "Component.hpp"
#include "Node.hpp"
#include "../Graphics/Rect.hpp"

namespace oe
{

class SceneComponent : public Component, public Node
{
	public:
		SceneComponent(Entity& entity, bool attachToEntity = true);
		virtual ~SceneComponent();

		const Rect& getLocalAABB() const;
		const Rect& getGlobalAABB() const;

		virtual void onCreate();

		void setLocalAABB(const Rect& rect);
		void invalidateGlobalAABB();
		void onSceneComponentInvalidated(const Node* node);
		OeSlot(oe::Node, onNodeInvalidation, mSceneComponentInvalidationSlot);

		virtual void registerComponent();
		virtual void unregisterComponent();

	protected:
		Rect mLocalAABB;
		mutable Rect mGlobalAABB;
		mutable bool mGlobalAABBUpdated;
};

} // namespace oe

#endif // OE_SCENECOMPONENT_HPP
