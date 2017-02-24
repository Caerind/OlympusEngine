#ifndef OE_RESOURCEHOLDER_HPP
#define OE_RESOURCEHOLDER_HPP

#include "../Config.hpp"
#include "String.hpp"
#include <map>

namespace oe
{

using ResourceId = StringId;

template <typename T>
class ResourceHolder
{
	public:
		ResourceHolder();
		~ResourceHolder();

		template <typename ... Args>
		ResourceId create(const std::string& name, Args&& ... args);

		template <typename ... Args>
		T& get(const std::string& name, Args&& ... args);
		template <typename ... Args>
		T& get(ResourceId index, Args&& ... args);

		bool has(const std::string& name) const;
		bool has(ResourceId index) const;

		void release(const std::string& name);
		void release(ResourceId index);

		void releaseAll();

		U32 size() const;

	private:
		std::map<ResourceId, T> mResources;
};

template<typename T>
ResourceHolder<T>::ResourceHolder()
{
}

template<typename T>
ResourceHolder<T>::~ResourceHolder()
{
}

template<typename T>
template<typename ... Args>
ResourceId ResourceHolder<T>::create(const std::string& name, Args&& ... args)
{
	ResourceId index(StringHash::hash(name));
	if (!has(index))
	{
		mResources.try_emplace(index, std::forward<Args>(args)...);
	}
	return index;
}

template<typename T>
template<typename ... Args>
T& ResourceHolder<T>::get(const std::string& name, Args&& ... args)
{
	return get(StringHash::hash(name), std::forward<Args>(args)...);
}

template<typename T>
template<typename ... Args>
T& ResourceHolder<T>::get(ResourceId index, Args&& ... args)
{
	if (!has(index))
	{
		mResources.try_emplace(index, std::forward<Args>(args)...);
	}
	ASSERT(has(index));
	return mResources.find(index)->second;
}

template<typename T>
bool ResourceHolder<T>::has(const std::string& name) const
{
	return has(StringHash::hash(name));
}

template<typename T>
bool ResourceHolder<T>::has(ResourceId index) const
{
	return (mResources.find(index) != mResources.end());
}

template<typename T>
void ResourceHolder<T>::release(const std::string& name)
{
	release(StringHash::hash(name));
}

template<typename T>
void ResourceHolder<T>::release(ResourceId index)
{
	auto itr = mResources.find(index);
	if (itr != mResources.end())
	{
		mResources.erase(itr);
	}
}

template<typename T>
void ResourceHolder<T>::releaseAll()
{
	mResources.clear();
}

template<typename T>
U32 ResourceHolder<T>::size() const
{
	return mResources.size();
}

} // namespace oe

#endif // OE_RESOURCEMANAGER_HPP
