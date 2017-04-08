#ifndef OE_COMPONENTLIST_HPP
#define OE_COMPONENTLIST_HPP

#include "Component.hpp"
#include "SceneComponent.hpp"
#include "RenderableComponent.hpp"

#include <vector>

namespace oe
{

namespace priv
{

template <typename T>
class ComponentListBase
{
	public:
		using Container = std::vector<T*>;

		ComponentListBase() : mComponents() {}

		void clear() { mComponents.clear(); }

		bool has(T* component)
		{
			for (U32 i = 0; i < mComponents.size(); i++)
			{
				if (mComponents[i] == component)
				{
					return true;
				}
			}
			return false;
		}

		bool insert(T* component)
		{
			if (!has(component))
			{
				mComponents.emplace_back(component);
				return true;
			}
			return false;
		}

		bool remove(T* component)
		{
			for (auto itr = mComponents.begin(); itr != mComponents.end(); ++itr)
			{
				if (component == *itr)
				{
					mComponents.erase(itr);
					return true;
				}
			}
			return false;
		}

		// Remove invalid component
		void update()
		{
			for (auto itr = mComponents.begin(); itr != mComponents.end(); )
			{
				if (*itr == nullptr)
				{
					itr = mComponents.erase(itr);
				}
				else
				{
					++itr;
				}
			}
		}

		U32 size() const { return mComponents.size(); }
		bool empty() const { return mComponents.empty(); }

	protected:
		Container mComponents;
};

} // namespace priv

class ComponentList : public priv::ComponentListBase<Component>
{
	public:
		ComponentList();

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
};

class SceneComponentList : public priv::ComponentListBase<SceneComponent>
{
	public:
		SceneComponentList();

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
};

class RenderableComponentList : public priv::ComponentListBase<RenderableComponent>
{
	public:
		RenderableComponentList();

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
};

} // namespace oe

#endif // OE_COMPONENTLIST_HPP
