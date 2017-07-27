#include "EntityQuery.hpp"

namespace oe
{

EntityQuery::EntityQuery()
{
	resetSelector();
}

EntityQuery::EntityQuery(Selector selector)
{
	setSelector(selector);
}

void EntityQuery::resetSelector()
{
	mEntities.clear();
	mSelector = [](Entity* entity) -> bool { return true; }; // Take every entity by default
	mUpdated = false;
}

void EntityQuery::setSelector(Selector selector)
{
	mEntities.clear();
	mSelector = selector;
	mUpdated = false;
}

U32 EntityQuery::getEntitiesCount() const
{
	return mEntities.size();
}

List<Entity*>& EntityQuery::getEntities()
{
	return mEntities;
}

bool EntityQuery::isUpdated() const
{
	return mUpdated;
}

} // namespace oe