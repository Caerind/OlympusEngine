#ifndef OE_ENTITYLIST_HPP
#define OE_ENTITYLIST_HPP

#include "Entity.hpp"
#include "EntityHandle.hpp"

namespace oe
{

class EntityList
{
	public:
		using Container = std::vector<EntityHandle>;

		EntityList();

		void clear();

		bool has(const EntityHandle& entity);

		void insert(const EntityHandle& handle);

		void remove(const EntityHandle& handle);

		// Remove invalid handle
		void update();

		// STL API
		Container::iterator begin();
		Container::const_iterator begin() const;
		Container::iterator end();
		Container::const_iterator end() const;
		Container::const_iterator cbegin() const;
		Container::const_iterator cend() const;
		Container::const_reverse_iterator crbegin() const;
		Container::const_reverse_iterator crend() const;
		Container::reverse_iterator rbegin();
		Container::const_reverse_iterator rbegin() const;
		Container::reverse_iterator rend();
		Container::const_reverse_iterator rend() const;
		Container::size_type size() const;
		bool empty() const;

	private:
		std::vector<EntityHandle> mEntities;
};

} // namespace oe

#endif // OE_ENTITYLIST_HPP
