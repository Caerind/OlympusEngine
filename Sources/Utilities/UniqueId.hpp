#ifndef OE_UNIQUEID_HPP
#define OE_UNIQUEID_HPP

#include "../Config.hpp"
#include "Singleton.hpp"
#include <map>

namespace oe
{
	
using UID = U32;

class UniqueIdManager : Singleton<UniqueIdManager>
{
	public:
		UniqueIdManager();
		~UniqueIdManager();

		static UniqueIdManager& getSingleton();
		static UniqueIdManager* getSingletPtr();

		UID createUID(U32 group = 0);

	private:
		std::map<U32, UID> mIdTables;
};

} // namespace oe

#endif // OE_UNIQUEID_HPP
