#include "ComponentList.hpp"
#include "../System/Prerequisites.hpp"

namespace oe
{

ComponentList::ComponentList()
{
}

ComponentList::Container::iterator ComponentList::begin()
{
	return mComponents.begin();
}

ComponentList::Container::const_iterator ComponentList::begin() const
{
	return mComponents.begin();
}

ComponentList::Container::iterator ComponentList::end()
{
	return mComponents.end();
}

ComponentList::Container::const_iterator ComponentList::end() const
{
	return mComponents.end();
}

ComponentList::Container::const_iterator ComponentList::cbegin() const
{
	return mComponents.cbegin();
}

ComponentList::Container::const_iterator ComponentList::cend() const
{
	return mComponents.cend();
}

ComponentList::Container::const_reverse_iterator ComponentList::crbegin() const
{
	return mComponents.crbegin();
}

ComponentList::Container::const_reverse_iterator ComponentList::crend() const
{
	return mComponents.crend();
}

ComponentList::Container::reverse_iterator ComponentList::rbegin()
{
	return mComponents.rbegin();
}

ComponentList::Container::const_reverse_iterator ComponentList::rbegin() const
{
	return mComponents.rbegin();
}

ComponentList::Container::reverse_iterator ComponentList::rend()
{
	return mComponents.rend();
}

ComponentList::Container::const_reverse_iterator ComponentList::rend() const
{
	return mComponents.rend();
}


SceneComponentList::SceneComponentList()
{
}

SceneComponentList::Container::iterator SceneComponentList::begin()
{
	return mComponents.begin();
}

SceneComponentList::Container::const_iterator SceneComponentList::begin() const
{
	return mComponents.begin();
}

SceneComponentList::Container::iterator SceneComponentList::end()
{
	return mComponents.end();
}

SceneComponentList::Container::const_iterator SceneComponentList::end() const
{
	return mComponents.end();
}

SceneComponentList::Container::const_iterator SceneComponentList::cbegin() const
{
	return mComponents.cbegin();
}

SceneComponentList::Container::const_iterator SceneComponentList::cend() const
{
	return mComponents.cend();
}

SceneComponentList::Container::const_reverse_iterator SceneComponentList::crbegin() const
{
	return mComponents.crbegin();
}

SceneComponentList::Container::const_reverse_iterator SceneComponentList::crend() const
{
	return mComponents.crend();
}

SceneComponentList::Container::reverse_iterator SceneComponentList::rbegin()
{
	return mComponents.rbegin();
}

SceneComponentList::Container::const_reverse_iterator SceneComponentList::rbegin() const
{
	return mComponents.rbegin();
}

SceneComponentList::Container::reverse_iterator SceneComponentList::rend()
{
	return mComponents.rend();
}

SceneComponentList::Container::const_reverse_iterator SceneComponentList::rend() const
{
	return mComponents.rend();
}


RenderableComponentList::RenderableComponentList()
{
}

RenderableComponentList::Container::iterator RenderableComponentList::begin()
{
	return mComponents.begin();
}

RenderableComponentList::Container::const_iterator RenderableComponentList::begin() const
{
	return mComponents.begin();
}

RenderableComponentList::Container::iterator RenderableComponentList::end()
{
	return mComponents.end();
}

RenderableComponentList::Container::const_iterator RenderableComponentList::end() const
{
	return mComponents.end();
}

RenderableComponentList::Container::const_iterator RenderableComponentList::cbegin() const
{
	return mComponents.cbegin();
}

RenderableComponentList::Container::const_iterator RenderableComponentList::cend() const
{
	return mComponents.cend();
}

RenderableComponentList::Container::const_reverse_iterator RenderableComponentList::crbegin() const
{
	return mComponents.crbegin();
}

RenderableComponentList::Container::const_reverse_iterator RenderableComponentList::crend() const
{
	return mComponents.crend();
}

RenderableComponentList::Container::reverse_iterator RenderableComponentList::rbegin()
{
	return mComponents.rbegin();
}

RenderableComponentList::Container::const_reverse_iterator RenderableComponentList::rbegin() const
{
	return mComponents.rbegin();
}

RenderableComponentList::Container::reverse_iterator RenderableComponentList::rend()
{
	return mComponents.rend();
}

RenderableComponentList::Container::const_reverse_iterator RenderableComponentList::rend() const
{
	return mComponents.rend();
}

} // namespace oe