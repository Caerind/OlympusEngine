#include "EntityList.hpp"

namespace oe
{

EntityList::EntityList() 
	: List<EntityHandle>()
{
}

const EntityHandle& EntityList::get(U32 index)
{
	ASSERT(index < size());
	return *(begin() + index);
}

Entity* EntityList::getEntity(U32 index)
{
	return get(index).get();
}

void EntityList::update()
{
	for (auto itr = begin(); itr != end(); )
	{
		if (!(*itr).isValid())
		{
			itr = mList.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

} // namespace oe