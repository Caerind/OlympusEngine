#ifndef OE_COMPONENTLIST_HPP
#define OE_COMPONENTLIST_HPP

#include "Component.hpp"

#include <vector>

namespace oe
{

class ComponentList
{
	public:
		using Container = std::vector<Component*>;

		ComponentList();

		void clear();

		bool has(Component* component);
		bool insert(Component* component);
		bool remove(Component* component);

		// Remove invalid component
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
		Container mComponents;
};

} // namespace oe

#endif // OE_COMPONENT_HPP
