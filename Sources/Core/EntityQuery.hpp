#ifndef OE_ENTITYQUERY_HPP
#define OE_ENTITYQUERY_HPP

#include "../ExtLibs/FastDynamicCast/fast_dynamic_cast.h"

#include "Entity.hpp"
#include "EntityList.hpp"

namespace oe
{

class EntityQuery
{
	public:
		using Selector = std::function<bool(Entity* entity)>;
	
		EntityQuery();
		EntityQuery(Selector selector);

		void resetSelector();
		void setSelector(Selector selector);

		U32 getEntitiesCount() const;
		List<Entity*>& getEntities();

		bool isUpdated() const;

	private:
		friend class EntityManager;
		
	private:
		List<Entity*> mEntities;
		Selector mSelector;
		bool mUpdated;
};

} // namespace oe

#endif // OE_ENTITYQUERY_HPP
