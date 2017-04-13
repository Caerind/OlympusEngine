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

		// Remove invalid handle
		void update();
};

} // namespace oe

#endif // OE_ENTITYLIST_HPP
