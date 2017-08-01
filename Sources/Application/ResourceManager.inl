
#include "../System/Hash.hpp"

namespace oe
{

template<typename T>
inline ResourceManager<T>::ResourceManager()
	: mResources()
	, mList()
	, mOthers()
	, mOther(nullptr)
	, mLevelFlag(LevelFlag::None)
{
}

template<typename T>
inline ResourceManager<T>::ResourceManager(ResourceManager& other, LevelFlag flag)
	: mResources()
	, mList()
	, mOthers()
	, mOther(&other)
	, mLevelFlag(flag)
{
	other.add(this);
}

template<typename T>
inline ResourceManager<T>::~ResourceManager()
{
	if (!isMain())
	{
		mOther->remove(this);
		mOther = nullptr;
		mList.clear();
	}
	else
	{
		releaseAll();
	}
}

template<typename T>
inline ResourceId ResourceManager<T>::create(const std::string& name, std::function<void(T& r)> loader)
{
	if (!isMain())
	{
		ResourceId index(oe::hash(name));
		if (!mOther->has(index))
		{
			mOther->create(name, loader);
			mList.push_back(index);
		}
		return index;
	}
	else
	{
		ResourceId index(oe::hash(name));
		if (!has(index))
		{
			loader(mResources[index]);
		}
		return index;
	}
}

template<typename T>
inline bool ResourceManager<T>::has(const std::string& name) const
{
	return has(hash(name));
}

template<typename T>
inline bool ResourceManager<T>::has(ResourceId resource) const
{
	if (!isMain())
	{
		return mOther->has(resource);
	}
	else
	{
		return (mResources.find(resource) != mResources.end());
	}
}

template<typename T>
inline T& ResourceManager<T>::get(const std::string& name)
{
	return get(oe::hash(name));
}

template<typename T>
inline T& ResourceManager<T>::get(ResourceId resource)
{
	if (!isMain())
	{
		return mOther->get(resource);
	}
	else
	{
		return mResources[resource];
	}
}

template<typename T>
inline void ResourceManager<T>::release(const std::string& name)
{
	release(oe::hash(name));
}

template<typename T>
inline void ResourceManager<T>::release(ResourceId resource)
{
	if (isMain())
	{
		auto itr = mResources.find(resource);
		if (itr != mResources.end())
		{
			for (auto& o : mOthers)
			{
				o->remove(resource);
			}
			mResources.erase(itr);
		}
	}
	else if (mLevelFlag == LevelFlag::Friend)
	{
		mOther->release(resource);
	}
	else if (mLevelFlag == LevelFlag::Child)
	{
		for (U32 i = 0; i < mList.size(); i++)
		{
			if (mList[i] == resource)
			{
				mOther->release(resource);
				return;
			}
		}
	}
}

template<typename T>
inline void ResourceManager<T>::releaseAll()
{
	if (isMain())
	{
		for (auto itr = mResources.begin(); itr != mResources.end(); ++itr)
		{
			for (auto& o : mOthers)
			{
				o->remove(itr->first);
			}
		}
		mResources.clear();
	}
	else if (mLevelFlag == LevelFlag::Friend)
	{
		mOther->releaseAll();
	}
	else if (mLevelFlag == LevelFlag::Child)
	{
		for (auto itr = mList.begin(); itr != mList.end(); ++itr)
		{
			mOther->release(*itr);
		}
		mList.clear();
	}
}

template<typename T>
inline bool ResourceManager<T>::isMain() const
{
	return mOther == nullptr;
}

template<typename T>
inline void ResourceManager<T>::add(ResourceManager* other)
{
	if (std::find(mOthers.begin(), mOthers.end(), other) == mOthers.end())
	{
		mOthers.push_back(other);
	}
}

template<typename T>
inline void ResourceManager<T>::remove(ResourceManager* other)
{
	for (U32 i = 0; i < mOthers.size(); i++)
	{
		if (mOthers[i] == other)
		{
			mOthers.erase(mOthers.begin() + i);
			return;
		}
	}
}

template<typename T>
inline void ResourceManager<T>::remove(ResourceId resource)
{
	for (auto& o : mOthers)
	{
		o->remove(resource);
	}

	for (U32 i = 0; i < mList.size(); i++)
	{
		if (mList[i] == resource)
		{
			mList.erase(mList.begin() + i);
			return;
		}
	}
}

} // namespace oe
