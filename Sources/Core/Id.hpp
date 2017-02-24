#ifndef OE_ID_HPP
#define OE_ID_HPP

#include "Prerequisites.hpp"

namespace oe
{
	
using UID = U32;

class Id
{
	public:
		template <typename T>
		static UID generate()
		{
			// UID = 0 represents a wrong value
			static UID sCurrentId = 0;
			return ++sCurrentId;
		}
};

} // namespace oe

#endif // OE_ID_HPP
