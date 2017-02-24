#ifndef OE_SINGLETON_HPP
#define OE_SINGLETON_HPP

#include "NonCopyable.hpp"

#ifdef _MSC_VER
#pragma warning (disable: 4661)
#endif

namespace oe
{

template <typename T> 
class Singleton : private NonCopyable
{
	public:
		Singleton()
		{
			ASSERT(mSingleton == nullptr);
			mSingleton = static_cast<T*>(this);
		}
		
		~Singleton()
		{  
			ASSERT(mSingleton != nullptr);  
			mSingleton = nullptr;  
		}
		
		static T& getSingleton()
		{   
		    ASSERT(mSingleton);  
			return *mSingleton; 
		}
		
		static T* getSingletonPtr()
		{ 
			return mSingleton; 
		}

	protected:
		static T* mSingleton;	
};

} // namespace oe

#endif // OE_SINGLETON_HPP