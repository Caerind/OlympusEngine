#include "EntityList.hpp"

namespace oe
{

EntityList::EntityList() : List<EntityHandle>()
{
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