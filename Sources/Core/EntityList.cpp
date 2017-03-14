#include "EntityList.hpp"

namespace oe
{

EntityList::EntityList()
{
}

void EntityList::clear()
{
	mEntities.clear();
}

bool EntityList::has(const EntityHandle& handle)
{
	if (handle.isValid())
	{
		for (U32 i = 0; i < mEntities.size(); i++)
		{
			if (mEntities[i] == handle)
			{
				return true;
			}
		}
	}
	return false;
}

void EntityList::insert(const EntityHandle& handle)
{
	if (!has(handle))
	{
		mEntities.emplace_back(handle);
	}
}

void EntityList::remove(const EntityHandle& handle)
{
	if (handle.isValid())
	{
		for (auto itr = mEntities.begin(); itr != mEntities.end(); )
		{
			if ((*itr) == handle)
			{
				itr = mEntities.erase(itr);
			}
			else
			{
				++itr;
			}
		}
	}
}

void EntityList::update()
{
	for (auto itr = mEntities.begin(); itr != mEntities.end(); )
	{
		if (!(*itr).isValid())
		{
			itr = mEntities.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

EntityList::Container::iterator EntityList::begin()
{
	return mEntities.begin();
}

EntityList::Container::const_iterator EntityList::begin() const
{
	return mEntities.begin();
}

EntityList::Container::iterator EntityList::end()
{
	return mEntities.end();
}

EntityList::Container::const_iterator EntityList::end() const
{
	return mEntities.end();
}

EntityList::Container::const_iterator EntityList::cbegin() const
{
	return mEntities.cbegin();
}

EntityList::Container::const_iterator EntityList::cend() const
{
	return mEntities.cend();
}

EntityList::Container::const_reverse_iterator EntityList::crbegin() const
{
	return mEntities.crbegin();
}

EntityList::Container::const_reverse_iterator EntityList::crend() const
{
	return mEntities.crend();
}

EntityList::Container::reverse_iterator EntityList::rbegin()
{
	return mEntities.rbegin();
}

EntityList::Container::const_reverse_iterator EntityList::rbegin() const
{
	return mEntities.rbegin();
}

EntityList::Container::reverse_iterator EntityList::rend()
{
	return mEntities.rend();
}

EntityList::Container::const_reverse_iterator EntityList::rend() const
{
	return mEntities.rend();
}

EntityList::Container::size_type EntityList::size() const
{
	return mEntities.size();
}

bool EntityList::empty() const
{
	return mEntities.empty();
}

} // namespace oe