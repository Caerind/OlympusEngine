#ifndef OE_ENTITY_HPP
#define OE_ENTITY_HPP

#include "../System/Id.hpp"
#include "../System/Time.hpp"

namespace oe
{

class World;

class Entity
{
	public:
		Entity(World& world);

		World& getWorld();
		UID getId() const;

		virtual void onCreate();
		virtual void onSpawn();
		virtual void onKill();
		virtual void onDestroy();

		virtual void update(Time dt);

		void kill();

	private:
		World& mWorld;
		UID mId;
};

} // namespace oe

#endif // OE_ENTITY_HPP
