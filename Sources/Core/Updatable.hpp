#ifndef OE_UPDATABLE_HPP
#define OE_UPDATABLE_HPP

#include "Prerequisites.hpp"

namespace oe
{

class Updatable
{
	public:
		Updatable() {}
		virtual ~Updatable() {}
		
		virtual void update() = 0;
};

} // namespace oe

#endif // OE_UPDATABLE_HPP
