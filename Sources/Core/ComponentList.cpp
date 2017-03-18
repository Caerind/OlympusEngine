#include "ComponentList.hpp"
#include "../System/Prerequisites.hpp"

namespace oe
{

ComponentList::ComponentList()
{
}

void ComponentList::clear()
{
	mComponents.clear();
}

bool ComponentList::has(Component* component)
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

bool ComponentList::insert(Component* component)
{
	if (!has(component))
	{
		mComponents.emplace_back(component);
		return true;
	}
	return false;
}

bool ComponentList::remove(Component* component)
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

void ComponentList::update()
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

ComponentList::Container::iterator ComponentList::begin()
{
	return mComponents.begin();
}

ComponentList::Container::const_iterator ComponentList::begin() const
{
	return mComponents.begin();
}

ComponentList::Container::iterator ComponentList::end()
{
	return mComponents.end();
}

ComponentList::Container::const_iterator ComponentList::end() const
{
	return mComponents.end();
}

ComponentList::Container::const_iterator ComponentList::cbegin() const
{
	return mComponents.cbegin();
}

ComponentList::Container::const_iterator ComponentList::cend() const
{
	return mComponents.cend();
}

ComponentList::Container::const_reverse_iterator ComponentList::crbegin() const
{
	return mComponents.crbegin();
}

ComponentList::Container::const_reverse_iterator ComponentList::crend() const
{
	return mComponents.crend();
}

ComponentList::Container::reverse_iterator ComponentList::rbegin()
{
	return mComponents.rbegin();
}

ComponentList::Container::const_reverse_iterator ComponentList::rbegin() const
{
	return mComponents.rbegin();
}

ComponentList::Container::reverse_iterator ComponentList::rend()
{
	return mComponents.rend();
}

ComponentList::Container::const_reverse_iterator ComponentList::rend() const
{
	return mComponents.rend();
}

ComponentList::Container::size_type ComponentList::size() const
{
	return mComponents.size();
}

bool ComponentList::empty() const
{
	return mComponents.empty();
}

} // namespace oe