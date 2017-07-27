#ifndef OE_COMPONENTLIST_HPP
#define OE_COMPONENTLIST_HPP

#include "../System/List.hpp"

namespace oe
{

class Component;
class SceneComponent;
class RenderableComponent;

using ComponentList = List<Component*>;
using SceneComponentList = List<SceneComponent*>;
using RenderableComponentList = List<RenderableComponent*>;

} // namespace oe

#endif // OE_COMPONENTLIST_HPP
