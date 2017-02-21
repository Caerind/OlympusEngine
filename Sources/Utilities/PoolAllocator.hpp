#ifndef OE_POOLALLOCATOR_HPP
#define OE_POOLALLOCATOR_HPP

#include "../Config.hpp"
#include "NonCopyable.hpp"

#define MAXBLOCKSIZE 640
#define BLOCKSIZES 14
#define CHUNKARRAYINCREMENT 128

// TODO : Fix bugs
// TODO : Move const define as const static 
// TODO : Move maxBytes as member

namespace oe
{

template <U32 chunkSize>
class OE_API PoolAllocator : private NonCopyable
{
	public:
		PoolAllocator()
		{
			ASSERT(BLOCKSIZES < UCHAR_MAX);
			mChunkSpace = CHUNKARRAYINCREMENT;
			mChunkCount = 0;
			mChunks = (Chunk*)oe::alloc(mChunkSpace * sizeof(Chunk));
			memset(mChunks, 0, mChunkSpace * sizeof(Chunk));
			memset(mFreeLists, 0, sizeof(mFreeLists));

			static bool mBlockSizeLookupInitialized = false;
			if (!mBlockSizeLookupInitialized)
			{
				U32 j = 0;
				for (U32 i = 1; i <= MAXBLOCKSIZE; i++)
				{
					if (i <= mBlockSizes[j])
					{
						mBlockSizeLookup[i] = (U8)j;
					}
					else
					{
						j++;
						ASSERT(j < BLOCKSIZES);
						mBlockSizeLookup[i] = (U8)j;
					}
				}
				mBlockSizeLookupInitialized = true;
			}
		}

		~PoolAllocator()
		{
			for (U32 i = 0; i < mChunkCount; i++)
			{
				oe::free(mChunks[i].blocks);
			}
			oe::free(mChunks);
		}

		/// Allocate memory. This will use alloc if the size is larger than MAXBLOCKSIZE.
		template <typename T, typename ... Args>
		T* alloc(Args&& ... args)
		{
			const U32 size = sizeof(T);
			ASSERT(size > 0);
			if (size > MAXBLOCKSIZE)
			{
				return new (oe::alloc(size)) T(std::forward<Args>(args)...);
			}
			U32 index = mBlockSizeLookup[size];
			ASSERT(0 <= index && index < BLOCKSIZES);
			if (mFreeLists[index] != nullptr)
			{
				Block* block = mFreeLists[index];
				mFreeLists[index] = block->next;
				return new (block) T(std::forward<Args>(args)...);
			}
			else
			{
				if (mChunkCount == mChunkSpace)
				{
					Chunk* oldChunks = mChunks;
					mChunkSpace += CHUNKARRAYINCREMENT;
					mChunks = (Chunk*)oe::alloc(mChunkSpace * sizeof(Chunk));
					memcpy(mChunks, oldChunks, mChunkCount * sizeof(Chunk));
					memset(mChunks + mChunkCount, 0, CHUNKARRAYINCREMENT * sizeof(Chunk));
					oe::free(oldChunks);
				}
				Chunk* chunk = mChunks + mChunkCount;
				chunk->blocks = (Block*)oe::alloc(chunkSize);
				#if defined(OE_DEBUG)
					memset(chunk->blocks, 0xcd, chunkSize);
				#endif
				U32 blockSize = mBlockSizes[index];
				chunk->blockSize = blockSize;
				U32 blockCount = chunkSize / blockSize;
				for (U32 i = 0; i < blockCount - 1; i++)
				{
					Block* block = (Block*)((I8*)chunk->blocks + blockSize * i);
					Block* next = (Block*)((I8*)chunk->blocks + blockSize * (i + 1));
					block->next = next;
				}
				Block* last = (Block*)((I8*)chunk->blocks + blockSize * (blockCount - 1));
				last->next = nullptr;
				mFreeLists[index] = chunk->blocks->next;
				mChunkCount++;
				return new (chunk->blocks) T(std::forward<Args>(args)...);
			}
		}

		/// Free memory. This will use free if the size is larger than MAXBLOCKSIZE.
		template <typename T>
		void free(void* p)
		{
			const U32 size = sizeof(T);
			ASSERT(size > 0);
			if (size > MAXBLOCKSIZE)
			{
				oe::free(p);
				return;
			}
			U32 index = mBlockSizeLookup[size];
			ASSERT(0 <= index && index < BLOCKSIZES);
			#ifdef OE_DEBUG
				// Verify the memory address and size is valid.
				U32 blockSize = mBlockSizes[index];
				bool found = false;
				for (U32 i = 0; i < mChunkCount; i++)
				{
					Chunk* chunk = mChunks + i;
					if (chunk->blockSize != blockSize)
					{
						ASSERT((I8*)p + blockSize <= (I8*)chunk->blocks || (I8*)chunk->blocks + chunkSize <= (I8*)p);
					}
					else
					{
						if ((I8*)chunk->blocks <= (I8*)p && (I8*)p + blockSize <= (I8*)chunk->blocks + chunkSize)
						{
							found = true;
						}
					}
				}
				ASSERT(found);
				memset(p, 0xfd, blockSize);
			#endif
			Block* block = (Block*)p;
			block->next = mFreeLists[index];
			mFreeLists[index] = block;
		}

		void clear()
		{
			for (U32 i = 0; i < mChunkCount; i++)
			{
				oe::free(mChunks[i].blocks);
			}
			mChunkCount = 0;
			memset(mChunks, 0, mChunkSpace * sizeof(Chunk));
			memset(mFreeLists, 0, sizeof(mFreeLists));
		}
		
	private:
		struct Block
		{
			Block* next;
		};

		struct Chunk
		{
			U32 blockSize;
			Block* blocks;
		};

	private:
		Chunk* mChunks;
		U32 mChunkCount;
		U32 mChunkSpace;

		Block* mFreeLists[BLOCKSIZES];

		static U32 mBlockSizes[BLOCKSIZES];
		static U8 mBlockSizeLookup[MAXBLOCKSIZE + 1];
};

template <U32 chunkSize>
U32 PoolAllocator<chunkSize>::mBlockSizes[BLOCKSIZES] =
{
	16,		// 0
	32,		// 1
	64,		// 2
	96,		// 3
	128,	// 4
	160,	// 5
	192,	// 6
	224,	// 7
	256,	// 8
	320,	// 9
	384,	// 10
	448,	// 11
	512,	// 12
	640,	// 13
};

template <U32 chunkSize>
U8 PoolAllocator<chunkSize>::mBlockSizeLookup[MAXBLOCKSIZE + 1];

using DefaultPoolAllocator = PoolAllocator<16 * 1024>;

#undef MAXBLOCKSIZE
#undef BLOCKSIZES
#undef CHUNKARRAYINCREMENT

} // namespace oe

#endif // OE_POOLALLOCATOR_HPP