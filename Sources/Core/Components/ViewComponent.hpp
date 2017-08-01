#ifndef OE_VIEWCOMPONENT_HPP
#define OE_VIEWCOMPONENT_HPP

#include "../SceneComponent.hpp"

namespace oe
{
	
// TODO : Choose the view

class ViewComponent : public SceneComponent
{
    public:
		ViewComponent(Entity& entity, bool attachedToEntity = true, bool focus = true);

		virtual void onCreate();

		void onNodeInvalidated(const oe::Node* node);

		OeSlot(oe::Node, onNodeInvalidation, mInvalidationSlot);

		void setFocus(bool focus);
		bool isFocusing() const;

	private:
		bool mFocusing;
};

} // namespace oe

#endif // OE_VIEWCOMPONENT_HPP
