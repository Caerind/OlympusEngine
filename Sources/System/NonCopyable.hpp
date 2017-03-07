#ifndef OE_NONCOPYABLE_HPP
#define OE_NONCOPYABLE_HPP

#include "Prerequisites.hpp"

namespace oe
{

class NonCopyable
{
	protected:
		NonCopyable() {}
		~NonCopyable() {}

	private:
		NonCopyable(const NonCopyable&); // Remove copy
		NonCopyable& operator=(const NonCopyable&); // Remove assignement
};

} // namespace oe

#endif // OE_NONCOPYABLE_HPP
