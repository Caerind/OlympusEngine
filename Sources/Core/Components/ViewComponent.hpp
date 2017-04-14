#ifndef OE_AUDIOLISTENERCOMPONENT_HPP
#define OE_AUDIOLISTENERCOMPONENT_HPP

#include "../SceneComponent.hpp"

namespace oe
{

class ViewComponent : public SceneComponent
{
    public:
		ViewComponent(Entity& entity);

		virtual void onCreate();

		void onNodeInvalidated(const oe::Node* node);

		OeSlot(oe::Node, onNodeInvalidation, mInvalidationSlot);
};

} // namespace oe

#endif // OE_AUDIOLISTENERCOMPONENT_HPP
