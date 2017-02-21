#include "UniqueId.hpp"

namespace oe
{

template<> UniqueIdManager* Singleton<UniqueIdManager>::mSingleton = nullptr;

UniqueIdManager::UniqueIdManager()
{
}

UniqueIdManager::~UniqueIdManager()
{
}

UniqueIdManager& UniqueIdManager::getSingleton()
{
	ASSERT(mSingleton != nullptr);
	return *mSingleton;
}

UniqueIdManager* UniqueIdManager::getSingletPtr()
{
	return mSingleton;
}

UID UniqueIdManager::createUID(U32 group)
{
	return ++mIdTables[group];
}

} // namespace oe
