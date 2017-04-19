#ifndef OE_ENTITYHANDLE_HPP
#define OE_ENTITYHANDLE_HPP

#include "Entity.hpp"

#include "../ExtLibs/FastDynamicCast/fast_dynamic_cast.h"

namespace oe
{

class World;

class EntityHandle
{
	public:
		EntityHandle();
		EntityHandle(World* world, const Entity& entity, U32 handleIndex);

		EntityHandle(const EntityHandle& handle);
		void operator=(const EntityHandle& handle);

		Entity* operator->() const
		{
			return get();
		}

		Entity* get() const;

		template <typename T>
		T* getAs() const;

		bool isValid() const;

		bool operator==(const EntityHandle& handle) const;
		bool operator!=(const EntityHandle& handle) const;

		// You should avoid using those two functions : Only used for debugging and internal management
		UID getEntityId() const;
		U32 getHandleIndex() const;

	private:
		UID mEntityId;
		U32 mHandleIndex;
		World* mWorld;
};

template <typename T>
T* EntityHandle::getAs() const
{
	ASSERT(mWorld != nullptr);
	return fast_dynamic_cast<T*>(get());
}

} // namespace oe

#endif // OE_ENTITYHANDLE_HPP
