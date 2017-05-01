#ifndef OE_ENTITYLIST_HPP
#define OE_ENTITYLIST_HPP

#include "EntityHandle.hpp"
#include "../System/List.hpp"

namespace oe
{

class EntityList : public List<EntityHandle>
{
	public:
		EntityList();

		const EntityHandle& get(U32 index);
		Entity* getEntity(U32 index);
		template <typename T>
		T* getAs(U32 index);

		// Remove invalid handle
		void update();
};

template<typename T>
T* EntityList::getAs(U32 index)
{
	return get(index).getAs<T>();
}

} // namespace oe

#endif // OE_ENTITYLIST_HPP
