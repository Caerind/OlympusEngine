#ifndef OE_ENTITYHANDLE_HPP
#define OE_ENTITYHANDLE_HPP

#include "../ExtLibs/FastDynamicCast/fast_dynamic_cast.h"

#include "Entity.hpp"

namespace oe
{

class EntityManager;
class EntityHandle
{
	public:
		EntityHandle();
		EntityHandle(EntityManager* manager, const Entity& entity, U32 handleIndex);

		EntityHandle(const EntityHandle& handle);
		void operator=(const EntityHandle& handle);

		Entity* get() const;
		Entity* operator->() const;

		template <typename T>
		T* getAs() const;

		bool isValid() const;

		bool operator==(const EntityHandle& handle) const;
		bool operator!=(const EntityHandle& handle) const;

		void invalidate();

		// You should avoid using those two functions : Only used for debugging and internal management
		UID getEntityId() const;
		U32 getHandleIndex() const;

	private:
		EntityManager* mManager;
		UID mEntityId;
		U32 mHandleIndex;
};

template <typename T>
T* EntityHandle::getAs() const
{
	return fast_dynamic_cast<T*>(get());
}

} // namespace oe

#endif // OE_ENTITYHANDLE_HPP
