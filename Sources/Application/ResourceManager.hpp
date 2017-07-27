#ifndef OE_RESOURCEMANAGER_HPP
#define OE_RESOURCEMANAGER_HPP

#include <functional>
#include <map>
#include <vector>

#include "../System/NonCopyable.hpp"

namespace oe
{

using ResourceId = U32;

template <typename T>
class ResourceManager : private NonCopyable
{
	public:
		enum LevelFlag
		{
			Child,
			Friend,
			None
		};

		// Create a main manager
		ResourceManager();

		// Create a manager. It might be a child or a friend.
		ResourceManager(ResourceManager& other, LevelFlag flag = LevelFlag::Child);
		~ResourceManager();

		ResourceId create(const std::string& name, std::function<void(T& r)> loader);
		bool has(const std::string& name) const;
		bool has(ResourceId resource) const;
		T& get(const std::string& name);
		T& get(ResourceId resource);
		void release(const std::string& name);
		void release(ResourceId resource);
		void releaseAll();
		bool isMain() const;

	private:
		// Used from the lower to the upper to add it to the others
		void add(ResourceManager* other);

		// Used from the lower to the upper to remove it from the others
		void remove(ResourceManager* other);

		// Used to remove a resource from the list, from the upper to the lower
		void remove(ResourceId resource);

	private:
		std::map<ResourceId, T> mResources;
		std::vector<ResourceId> mList;
		std::vector<ResourceManager*> mOthers;
		ResourceManager* mOther;
		LevelFlag mLevelFlag;
};

} // namespace oe

#include "ResourceManager.inl"

#endif // OE_RESOURCEMANAGER_HPP
