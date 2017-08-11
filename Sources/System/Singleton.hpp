#ifndef OE_SINGLETON_HPP
#define OE_SINGLETON_HPP

#include "Macros.hpp" // NonCopyable & NonMovable

#ifdef OE_COMPILER_MSVC
	#pragma warning (disable: 4661)
#endif

#define OE_SINGLETON_GETSINGLETON_DEF(Type) \
		inline static Type& getSingleton() \
		{ \
			ASSERT(mSingleton); \
			return *mSingleton; \
		} \
		inline static Type* getSingletonPtr() \
		{ \
			return mSingleton; \
		} \

namespace oe
{

template <typename T>
class Singleton
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

		OE_NON_COPYABLE(Singleton);
		OE_NON_MOVABLE(Singleton);

		OE_SINGLETON_GETSINGLETON_DEF(T);

	protected:
		static T* mSingleton;
};

} // namespace oe

#endif // OE_SINGLETON_HPP