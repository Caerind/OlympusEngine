#ifndef OE_COMPONENT_HPP
#define OE_COMPONENT_HPP

namespace oe
{

class Entity;
class World;
class Component
{
	public:
		Component(Entity& entity);

		virtual void onCreate();
		virtual void onSpawn();
		virtual void onDestroy();

		Entity& getEntity();
		World& getWorld();

	protected:
		void registerComponent();
		void unregisterComponent();

	protected:
		Entity& mEntity;
};

} // namespace oe

#endif // OE_COMPONENT_HPP
