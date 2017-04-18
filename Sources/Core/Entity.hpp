#ifndef OE_ENTITY_HPP
#define OE_ENTITY_HPP

#include "Component.hpp"
#include "SceneComponent.hpp"
#include "ComponentList.hpp"

#include "../System/Id.hpp"
#include "../System/Node.hpp"
#include "../System/Time.hpp"

#include "../ExtLibs/FastDynamicCast/fast_dynamic_cast.h"

namespace oe
{

class World;
class Entity : public Node
{
	public:
		Entity(World& world);
		virtual ~Entity();

		World& getWorld();
		UID getId() const;

		const ComponentList& getComponents() const;
		const SceneComponentList& getSceneComponents() const;

		bool isPlaying() const;

		void kill();

	private:
		friend class World;
		virtual void onCreate();
		void createComponents();
		virtual void onSpawn();
		void spawnComponents();
		virtual void onDestroy();
		void destroyComponents();
		virtual void update(Time dt);
		void setPlaying(bool playing);

	private:
		friend class Component;
		void registerComponent(Component* component);
		void unregisterComponent(Component* component);

	private:
		World& mWorld;
		UID mId;
		bool mPlaying;
		ComponentList mComponents;
		SceneComponentList mSceneComponents;
};

} // namespace oe

#endif // OE_ENTITY_HPP
