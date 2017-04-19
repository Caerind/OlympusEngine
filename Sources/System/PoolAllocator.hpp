#ifndef OE_POOLALLOCATOR_HPP
#define OE_POOLALLOCATOR_HPP

#include "Prerequisites.hpp"
#include "NonCopyable.hpp"

namespace oe
{

/*

template <U32 chunkSize>
class PoolAllocator : private NonCopyable
{
	public:
		PoolAllocator()
		{
			ASSERT(BlockSizes < UCHAR_MAX);
			mChunkSpace = ChunkArrayIncrement;
			mChunkCount = 0;
			mChunks = (Chunk*)std::malloc(mChunkSpace * sizeof(Chunk));
			std::memset(mChunks, 0, mChunkSpace * sizeof(Chunk)); //-V575
			std::memset(mFreeLists, 0, sizeof(mFreeLists));

			static bool mBlockSizeLookupInitialized = false;
			if (!mBlockSizeLookupInitialized)
			{
				U32 j = 0;
				for (U32 i = 1; i <= MaxBlockSize; i++)
				{
					if (i <= mBlockSizes[j])
					{
						mBlockSizeLookup[i] = (U8)j;
					}
					else
					{
						j++;
						ASSERT(j < BlockSizes);
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
				std::free(mChunks[i].blocks);
			}
			std::free(mChunks);
		}

		/// Allocate memory. This will use alloc if the size is larger than MaxBlockSize.
		template <typename T, typename ... Args>
		T* alloc(Args&& ... args)
		{
			const U32 size = sizeof(T);
			ASSERT(size > 0);
			if (size > MaxBlockSize)
			{
				return new (oe::alloc(size)) T(std::forward<Args>(args)...);
			}
			U32 index = mBlockSizeLookup[size];
			ASSERT(index < BlockSizes);
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
					mChunkSpace += ChunkArrayIncrement;
					mChunks = (Chunk*)oe::alloc(mChunkSpace * sizeof(Chunk));
					memcpy(mChunks, oldChunks, mChunkCount * sizeof(Chunk));
					memset(mChunks + mChunkCount, 0, ChunkArrayIncrement * sizeof(Chunk));
					::free(oldChunks);
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

		/// Free memory. This will use free if the size is larger than MaxBlockSize.
		template <typename T>
		void free(void* p)
		{
			const U32 size = sizeof(T);
			ASSERT(size > 0);
			if (size > MaxBlockSize)
			{
				::free(p);
				return;
			}
			U32 index = mBlockSizeLookup[size];
			ASSERT(index < BlockSizes);
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
				::free(mChunks[i].blocks);
			}
			mChunkCount = 0;
			std::memset(mChunks, 0, mChunkSpace * sizeof(Chunk));
			std::memset(mFreeLists, 0, sizeof(mFreeLists));
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

		static const U32 MaxBlockSize = 640;
		static const U32 BlockSizes = 14;
		static const U32 ChunkArrayIncrement = 128;
		static U32 mBlockSizes[BlockSizes];
		static U8 mBlockSizeLookup[MaxBlockSize + 1];

	private:
		Chunk* mChunks;
		U32 mChunkCount;
		U32 mChunkSpace;

		Block* mFreeLists[BlockSizes];
};

template <U32 chunkSize>
U32 PoolAllocator<chunkSize>::mBlockSizes[BlockSizes] =
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
U8 PoolAllocator<chunkSize>::mBlockSizeLookup[MaxBlockSize + 1];

using DefaultPoolAllocator = PoolAllocator<16 * 1024>;

*/

} // namespace oe

#endif // OE_POOLALLOCATOR_HPP
