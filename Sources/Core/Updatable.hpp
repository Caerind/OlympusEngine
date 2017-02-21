#ifndef OE_SERIALIZATION_HPP
#define OE_SERIALIZATION_HPP

#include "../Config.hpp"

namespace oe
{

class OE_API Updatable
{
	public:
		Updatable() = default;
		virtual ~Updatable() {}
		
		virtual void update() = 0;
}

} // namespace oe

#endif // OE_SERIALIZATION_HPP
