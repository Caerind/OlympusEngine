#ifndef OE_ENTITY_HPP
#define OE_ENTITY_HPP

#include "Component.hpp"
#include "SceneComponent.hpp"
#include "ComponentList.hpp"
#include "Transformable.hpp"

#include "../System/Id.hpp"
#include "../System/Time.hpp"

#include "../ExtLibs/FastDynamicCast/fast_dynamic_cast.h"

namespace oe
{

class World;

class Entity : public Transformable
{
	public:
		Entity(World& world);
		virtual ~Entity();

		World& getWorld();
		UID getId() const;

		void attachComponent(Component* component);
		void detachComponent(Component* component);
		void clearComponents();

		const ComponentList& getComponents() const;
		const ComponentList& getSceneComponents() const;

	private:
		friend class World;
		virtual void onCreate();
		virtual void onSpawn();
		virtual void onKill();
		virtual void onDestroy();
		virtual void update(Time dt);

	private:
		ComponentList mComponents;
		ComponentList mSceneComponents;
		World& mWorld;
		UID mId;
};

} // namespace oe

#endif // OE_ENTITY_HPP
