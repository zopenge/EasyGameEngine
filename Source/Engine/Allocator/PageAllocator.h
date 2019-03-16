//! @file     PageAllocator.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// PageAllocator
//----------------------------------------------------------------------------

class PageAllocator
{
public:
	//!	When allocate buffer.
	//!	@param		size		The allocated size.
	//!	@return		The buffer address.
	typedef _byte* (*OnAllocate)( _dword size );
	//!	When release buffer.
	//!	@param		address		The buffer address.
	//!	@return		none.
	typedef _void (*OnFree)( _byte* address );

private:
	//!	The empty chunk link
	enum { _EMPTY_CHUNK_LINK = _ENUM_VALUE_16384 };

public:
	//!	The chunk
	struct Chunk
	{
		//!	The chunk offset in bytes
		_dword	mOffset;
		//!	The chunk size in bytes
		_dword	mSize;

		//!	The page index
		_dword	mPageIndex;

		//!	True indicates it's free chunk
		_word	mIsFree;
		//!	The previous chunk index
		_word	mPrevChunkIndex;
		//!	The next chunk index
		_word	mNextChunkIndex;
		//!	The chunk index of heap
		_word	mChunkIndexOfHeap;

		Chunk( ) 
		{
			mOffset				= -1;
			mSize				= 0;

			mPageIndex			= -1;

			mIsFree				= 1;
			mPrevChunkIndex		= _EMPTY_CHUNK_LINK;
			mNextChunkIndex		= _EMPTY_CHUNK_LINK;
			mChunkIndexOfHeap	= -1;
		}
	};

	//!	The chunk compare function
	struct ChunkCompare : public BinaryFunction< const Chunk*, const Chunk* >
	{
		//!	Process compare operation.
		_int operator( ) ( const Chunk* v1, const Chunk* v2 ) const
		{
			if ( v1 != _null )
			{
				if ( v2 != _null )
					return v1->mSize < v2->mSize; // Put the biggest chunk to the top
				else
					return _false; // v1 != _null && v2 == _null
			}

			// v1 == _null && v2 == _null
			return _true;
		}
	};

	//!	The chunk pool
	typedef Pool< Chunk, _ENUM_VALUE_16384 > ChunkPool;

	//!	The binary heap for speed up the free chunk matching
	typedef BinaryHeap< _ENUM_VALUE_16384, Chunk*, ChunkCompare > ChunkHeap;

	//!	The page
	struct Page
	{
		//!	The page index
		_dword		mPageIndex;
		//!	The base address of chunks
		_qword		mBaseAddressOfChunks;
		//!	The total size in bytes
		_dword		mSize;

		//!	The chunk heap ( from big -> small )
		ChunkHeap	mFreeChunks;
		//!	The chunk pool
		ChunkPool	mChunkPool;

		//!	The swap chunk callback function.
		static _void OnSwapElement( _dword index1, Chunk*& chunk1, _dword index2, Chunk*& chunk2 )
		{
			chunk1->mChunkIndexOfHeap = (_word) index2;
			chunk2->mChunkIndexOfHeap = (_word) index1;
		}

		//!	Get the max free chunk size in bytes
		_dword GetMaxFreeChunkSize( ) const
		{
			const Chunk* const* chunk = mFreeChunks.GetTopElement( );
			if ( chunk == _null )
				return 0;

			return (*chunk)->mSize;
		}

		//!	Get the chunk ID by address.
		_word GetChunkIDByAddress( const Chunk* chunk ) const
		{
			return chunk - (const Chunk*) mChunkPool.GetNodeBuffer( );
		}

		//!	Get the base allocated address
		_byte* GetAllocatedAddress( ) const
		{
			return (_byte*)( mBaseAddressOfChunks - sizeof( Page ) );
		}

		//!	Insert a free chunk into heap.
		_void InsertFreeChunk( Chunk* chunk )
		{
			chunk->mChunkIndexOfHeap = (_word) mFreeChunks.Insert( chunk );
		}

		//! Remove the free chunk
		_void RemoveFreeChunk( Chunk* chunk )
		{
			if ( chunk->mChunkIndexOfHeap == 0xFFFF )
				return;

			chunk->mSize	= 0;
			chunk->mOffset	= -1;
			mFreeChunks.Remove( chunk->mChunkIndexOfHeap );
		}

		//!	Remove the chunk and reset index of heap
		_void RemoveChunk( Chunk* chunk )
		{
			mChunkPool.Remove( GetChunkIDByAddress( chunk ) );
		}
	};

	//!	The Page pool
	typedef Pool< Page*, _ENUM_VALUE_256 > PagePool;

private:
	//!	The page size
	_dword		mPageSize;
	//!	The minimal chunk size
	_dword		mMinChunkSize;

	//!	The pages
	PagePool	mPagePool;

	//!	The callback functions
	OnAllocate	mAllocateFunc;
	OnFree		mFreeFunc;

private:
#ifdef _DEBUG
	//!	Validate chunk.
	_void ValidateChunk( const Chunk* chunk ) const;
	//!	Validate page.
	_void ValidatePage( const Page* page ) const;
#endif

	//!	Build the chunk unique ID.
	//!	@param		chunk_index		The chunk index.
	//!	@param		page_index		The page index.
	//!	@return		The chunk unique ID.
	_dword BuildChunkID( _dword chunk_index, _dword page_index ) const;

	//!	Get the previous chunk index.
	//!	@param		page			The page.
	//!	@param		index			The chunk index.
	//!	@return		The previous chunk index.
	_dword PrevChunkIndex( const Page* page, _dword index ) const;
	//!	Get the next chunk index.
	//!	@param		page			The page.
	//!	@param		index			The chunk index.
	//!	@return		The next chunk index.
	_dword NextChunkIndex( const Page* page, _dword index ) const;

	//!	Get the previous chunk.
	//!	@param		chunk			The chunk.
	//!	@return		The previous chunk.
	Chunk* PrevChunk( const Chunk* chunk );
	//!	Get the next chunk.
	//!	@param		chunk			The chunk.
	//!	@return		The next chunk.
	Chunk* NextChunk( const Chunk* chunk );

	//!	Create chunk.
	//!	@param		page			The page.
	//!	@param		size			The allocated size.
	//!	@param		index			The chunk index.
	//!	@param		address			The chunk address.
	//!	@return		The chunk pointer, null indicates failure.
	Chunk* CreateChunk( Page* page, _dword size, _dword* index, _byte*& address );
	//!	Release chunk.
	//!	@param		chunk			The chunk.
	//!	@return		none.
	_void ReleaseChunk( Chunk* chunk );

	//!	Combine previous chunks.
	_ubool CombinePrevChunks( Page* page, Chunk*& chunk );
	//!	Combine next chunks.
	_ubool CombineNextChunks( Page* page, Chunk*& chunk );

	//!	Get page by index.
	//!	@param		index			The page index.
	//!	@return		The page pointer, null indicates failure.
	Page* GetPage( _dword index );
	//!	Get page by index.
	//!	@param		index			The page index.
	//!	@return		The page pointer, null indicates failure.
	const Page* GetPage( _dword index ) const;
	//!	Create page.
	//!	@param		size			The page size in bytes.
	//!	@param		index			The page index.
	//!	@return		The page pointer, null indicates failure.
	Page* CreatePage( _dword size, _dword* index );
	//!	Release page.
	//!	@param		page			The page.
	//!	@return		none.
	_void ReleasePage( Page* page );

public:
	PageAllocator( );
	~PageAllocator( );

public:
	//!	Get page size.
	EGE_GET_ACCESSOR_CONST( _dword, PageSize )

public:
	//!	Create.
	//!	@param		page_size		The page size.
	//!	@param		min_chunk_size	The minimal chunk size.
	//!	@param		allocate_func	The allocate callback function.
	//!	@param		free_func		The free callback function.
	//!	@return		True indicates successful, otherwise indicates failure.
	_ubool Create( _dword page_size, _dword min_chunk_size, OnAllocate allocate_func, OnFree free_func );
	//!	Clear.
	//!	@param		none.
	//!	@return		none.
	_void Clear( );

	//!	Cleanup pages.
	//!	@param		none.
	//!	@return		none.
	_void Cleanup( );

	//!	Search the chunk data by unique ID.
	//!	@param		id				The chunk unique ID.
	//!	@return		The chunk data pointer, null indicates it's not in used state or invalid unique ID.
	const Chunk* SearchChunkByID( _dword id ) const;
	//!	Search the page data by unique ID.
	//!	@param		id				The page unique ID.
	//!	@return		The page data pointer, null indicates it's not in used state or invalid unique ID.
	const Page* SearchPageByID( _dword id ) const;

	//!	Allocate chunk.
	//!	@param		size			The buffer size in bytes.
	//!	@param		id				The chunk unique ID.
	//!	@param		address			The chunk address.
	//!	@return		The chunk pointer, null indicates failure.
	Chunk* Allocate( _dword size, _dword& id, _byte*& address );
	//!	Free chunk.
	//!	@param		id				The chunk unique ID.
	//!	@return		none.
	_void Free( _dword id );
};

//----------------------------------------------------------------------------
// PageAllocator Implementation
//----------------------------------------------------------------------------

}