#ifndef OE_COMPONENTLIST_HPP
#define OE_COMPONENTLIST_HPP

#include "../System/List.hpp"

namespace oe
{

class Component;
class SceneComponent;
class RenderableComponent;
class ParticleComponent;
class AnimatorComponent;

using ComponentList = List<Component*>;
using SceneComponentList = List<SceneComponent*>;
using RenderableComponentList = List<RenderableComponent*>;
using ParticleComponentList = List<ParticleComponent*>;
using AnimatorComponentList = List<AnimatorComponent*>;

} // namespace oe

#endif // OE_COMPONENTLIST_HPP
