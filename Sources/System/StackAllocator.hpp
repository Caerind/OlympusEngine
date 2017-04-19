#ifndef OE_STACKALLOCATOR_HPP
#define OE_STACKALLOCATOR_HPP

#include "NonCopyable.hpp"

namespace oe
{

/*

template <U32 maxBytes>
class StackAllocator : private NonCopyable
{
	public:
		StackAllocator()
		{
			mIndex = 0;
			#ifdef OE_DEBUG
				mMaxAllocation = 0;
			#endif
		}

		~StackAllocator()
		{
			ASSERT(mIndex == 0);
		}

		template <typename T, typename ... Args>
		T* alloc(Args&& ... args)
		{
			const U32 bytes = sizeof(T);
			ASSERT(bytes > 0);
			ASSERT(mIndex + bytes <= maxBytes);
			U8* mem = mData + mIndex;
			mIndex += bytes;
			#ifdef OE_DEBUG
				if (mIndex > mMaxAllocation)
				{
					mMaxAllocation = mIndex;
				}
			#endif
			return new (mem) T(std::forward<Args>(args)...);
		}

		template <typename T>
		void free(void* p)
		{
			mIndex -= sizeof(T);
		}

		void clear()
		{
			mIndex = 0;
		}

		U32 getSize() const
		{
			return mIndex;
		}

		U32 getMaxSize() const
		{
			return maxBytes;
		}

		U32 getRemainingSize() const
		{
			return maxBytes - mIndex;
		}

		#ifdef OE_DEBUG
		U32 getMaxAllocation() const
		{
			return mMaxAllocation;
		}
		#endif

	private:
		char mData[maxBytes];
		U32 mIndex;

		#ifdef OE_DEBUG
		U32 mMaxAllocation;
		#endif
};

template <U32 maxBytes>
class DoubleBufferAllocator : private NonCopyable
{
	public:
		DoubleBufferAllocator()
			: mIndex(0)
		{
		}

		void swap()
		{
			mIndex = (U8)!mIndex;
		}

		void clear()
		{
			mStacks[mIndex].clear();
		}

		void* alloc(U32 bytes)
		{
			return mStacks[mIndex].alloc(bytes);
		}

		template <typename T, typename ... Args>
		T* alloc(Args&& ... args)
		{
			return new (alloc(sizeof(T))) T(std::forward<Args>(args)...);
		}

	private:
		StackAllocator<maxBytes> mStacks[2];
		U8 mIndex;
};

using DefaultStackAllocator = StackAllocator<100 * 1024>;
using DefaultDoubleBufferAllocator = DoubleBufferAllocator<100 * 1024>;

*/

} // namespace oe

#endif // OE_STACKALLOCATOR_HPP
