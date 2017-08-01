#ifndef OE_ENTITY_HPP
#define OE_ENTITY_HPP

#include "../System/Id.hpp"
#include "../System/Type.hpp"

#include "../ExtLibs/FastDynamicCast/fast_dynamic_cast.h"

#include "Component.hpp"
#include "ComponentList.hpp"
#include "SceneComponent.hpp"
#include "RenderableComponent.hpp"
#include "Node.hpp"

namespace oe
{

class Application;
class World;
class EntityManager;
class EntityHandle;

class Entity : public Node
{
	public:
		enum State
		{
			Constructed,
			Created,
			Playing,
			Killed,
			Destroyed
		};

		TYPE(Entity);

	public:
		Entity(EntityManager& manager);
		virtual ~Entity();

		Application& getApplication();
		World& getWorld();
		EntityManager& getManager();

		const UID& getId() const;

		void setName(char* name);
		const char* getName() const;
		bool hasName() const;

		const Entity::State& getState() const;

		EntityHandle getHandle() const;
		void kill() const;

		const ComponentList& getComponents() const;
		const SceneComponentList& getSceneComponents() const;
		const RenderableComponentList& getRenderableComponents() const;

		const Rect& getAABB() const;
		void updateAABB() const;
		void invalidateAABB();
		bool isAABBUpdated() const;

		bool isVisible() const;
		void setVisible(bool visible);

		void render(sf::RenderTarget& target, const Rect& viewAABB);

		virtual void update(oe::Time dt);

		template <typename T>
		T* getAs();

	private:
		friend class EntityManager;
		virtual void onCreate(); // Call after the entity creation
		void createComponents(); // Call onCreate for each components
		virtual void onSpawn(); // Call after the entity spawn
		void spawnComponents(); // Call onSpawn for each components
		virtual void onDestroy(); // Call before being destroyed
		void destroyComponents(); // Call onDestory for each components
		void setState(const Entity::State& state);

	private:
		friend class Component;
		void registerComponent(Component* component);
		void unregisterComponent(Component* component);

	private:
		friend class SceneComponent;
		void registerSceneComponent(SceneComponent* sceneComponent);
		void unregisterSceneComponent(SceneComponent* sceneComponent);

	private:
		friend class RenderableComponent;
		void registerRenderableComponent(RenderableComponent* renderableComponent);
		void unregisterRenderableComponent(RenderableComponent* renderableComponent);
		void invalidateComponentsOrder();
		static bool sortComponents(const RenderableComponent* a, const RenderableComponent* b);

	private:
		EntityManager& mManager;
		UID mId;
		char* mName;
		Entity::State mState;
		ComponentList mComponents;
		SceneComponentList mSceneComponents;
		RenderableComponentList mRenderableComponents;
		bool mVisible;

		mutable bool mAABBUpdated;
		mutable Rect mAABB;

		mutable bool mNeedOrderComponents;
};

template <typename T>
inline T* Entity::getAs()
{
	return fast_dynamic_cast<T*>(this);
}

} // namespace oe

#endif // OE_ENTITY_HPP
