//! @file     PageAllocator.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

// --------------------------------------------------------------------------------------------------------------
// PageAllocator Implementation
// --------------------------------------------------------------------------------------------------------------

PageAllocator::PageAllocator( )
{
	mMinChunkSize	= 0;
	mPageSize		= 0;

	mAllocateFunc	= _null;
	mFreeFunc		= _null;
}

PageAllocator::~PageAllocator( )
{
	Clear( );
}

#ifdef _DEBUG

_void PageAllocator::ValidateChunk( const Chunk* chunk ) const
{
	EGE_ASSERT( chunk != _null );

	// Get the page
	const Page* page = GetPage( chunk->mPageIndex );
	EGE_ASSERT( page != _null );

	// The previous link of chunk must be valid
	if ( chunk->mPrevChunkIndex != _EMPTY_CHUNK_LINK )
		EGE_ASSERT( page->mChunkPool.Index( chunk->mPrevChunkIndex ) != _null );

	// The next link of chunk must be valid
	if ( chunk->mNextChunkIndex != _EMPTY_CHUNK_LINK )
		EGE_ASSERT( page->mChunkPool.Index( chunk->mNextChunkIndex ) != _null );

	// The chunk must have at least one linkable target when we have more than 1 chunks
	if ( page->mChunkPool.Number( ) > 1 )
		EGE_ASSERT( chunk->mPrevChunkIndex != _EMPTY_CHUNK_LINK || chunk->mNextChunkIndex != _EMPTY_CHUNK_LINK );
}

_void PageAllocator::ValidatePage( const Page* page ) const
{
	// Check the free chunks number with pool
	_dword free_chunks_number = 0;
	for ( ChunkPool::ConstIterator it = page->mChunkPool.GetHeadIterator( ); it.IsValid( ); it ++ )
	{
		const Chunk& chunk = it;

		// Check whether it's free chunk
		if ( chunk.mIsFree )
			free_chunks_number ++;
	}

	EGE_ASSERT( page->mFreeChunks.Number( ) == free_chunks_number );
}

#endif

_dword PageAllocator::BuildChunkID( _dword chunk_index, _dword page_index ) const
{
	// Build the unique ID with page ID
	return ( chunk_index << 16 ) | page_index;
}

_dword PageAllocator::PrevChunkIndex( const Page* page, _dword index ) const
{
	const Chunk* chunk = page->mChunkPool.Index( index );
	if ( chunk == _null )
		return _EMPTY_CHUNK_LINK;

	return chunk->mPrevChunkIndex;
}

_dword PageAllocator::NextChunkIndex( const Page* page, _dword index ) const
{
	const Chunk* chunk = page->mChunkPool.Index( index );
	if ( chunk == _null )
		return _EMPTY_CHUNK_LINK;

	return chunk->mNextChunkIndex;
}

PageAllocator::Chunk* PageAllocator::PrevChunk( const Chunk* chunk )
{
	if ( chunk->mPrevChunkIndex == _EMPTY_CHUNK_LINK )
		return _null;

	// Get the page
	Page* page = GetPage( chunk->mPageIndex );
	if ( page == _null )
		return _null;

	return page->mChunkPool.Index( chunk->mPrevChunkIndex );
}

PageAllocator::Chunk* PageAllocator::NextChunk( const Chunk* chunk )
{
	if ( chunk->mNextChunkIndex == _EMPTY_CHUNK_LINK )
		return _null;

	// Get the page
	Page* page = GetPage( chunk->mPageIndex );
	if ( page == _null )
		return _null;

	return page->mChunkPool.Index( chunk->mNextChunkIndex );
}

PageAllocator::Chunk* PageAllocator::CreateChunk( Page* page, _dword size, _dword* index, _byte*& address )
{
	// Get the biggest free chunk
	Chunk* chunk = _null;
	if ( page->mFreeChunks.ExtractTopElement( chunk ) == _false )
		return _null;

	// The free chunk's size must bigger than allocated size
	EGE_ASSERT( chunk->mSize >= size );

	// This chunk has been used
	chunk->mIsFree				= _false;
	chunk->mChunkIndexOfHeap	= 0xFFFF;

	// If the chunk has enough space to allocated another block then we will split it
	if ( chunk->mSize - size >= mMinChunkSize )
	{
		_dword new_chunk_id = -1;

		// Insert it into pool
		Chunk* new_chunk = page->mChunkPool.Create( &new_chunk_id );
		if ( new_chunk == _null )
			return _null;

		// Build another new free chunk
		new_chunk->mOffset			= chunk->mOffset + size;
		new_chunk->mSize			= chunk->mSize - size;
		new_chunk->mPageIndex		= page->mPageIndex;
		new_chunk->mIsFree			= _true;
		new_chunk->mPrevChunkIndex	= page->GetChunkIDByAddress( chunk );
		new_chunk->mNextChunkIndex	= chunk->mNextChunkIndex;

		// The next chunk change its previous link
		if ( new_chunk->mNextChunkIndex != _EMPTY_CHUNK_LINK )
			NextChunk( new_chunk )->mPrevChunkIndex = _word( new_chunk_id );

		// Cut the size of allocated chunk
		chunk->mSize			= size;
		// Change the next link of allocated chunk
		chunk->mNextChunkIndex	= (_word) new_chunk_id;

		// Validate chunks
#ifdef _DEBUG
		ValidateChunk( chunk );
		ValidateChunk( new_chunk );
#endif
		// Insert it into free chunks heap
		page->InsertFreeChunk( new_chunk );
	}

	// Feedback the chunk unique ID
	if ( index != _null )
		*index = page->GetChunkIDByAddress( chunk );

	// Feedback the allocated address in this page by chunk's offset
	address = (_byte*)( page->mBaseAddressOfChunks + chunk->mOffset );

	return chunk;
}

_void PageAllocator::ReleaseChunk( Chunk* chunk )
{
	// Get the page
	Page* page = GetPage( chunk->mPageIndex );
	if ( page == _null )
		return;

	// Free the chunk
	EGE_ASSERT( !chunk->mIsFree );
	chunk->mIsFree = _true;

	// Try to combine chunks
	_ubool has_combine = _false;
	has_combine |= CombinePrevChunks( page, chunk );
	has_combine |= CombineNextChunks( page, chunk );

	// If we combine failed then add it to free chunks
	if ( has_combine == _false )
		page->InsertFreeChunk( chunk );

	// Validate page
#ifdef _DEBUG
	ValidatePage( page );
#endif
}

_ubool PageAllocator::CombinePrevChunks( Page* page, Chunk*& chunk )
{
	_ubool has_combine = _false;

	for ( _dword prev_chunkid = chunk->mPrevChunkIndex; prev_chunkid != _EMPTY_CHUNK_LINK; prev_chunkid = PrevChunkIndex( page, prev_chunkid ) )
	{
		Chunk* prev_chunk = page->mChunkPool.Index( prev_chunkid );
		EGE_ASSERT( prev_chunk != _null );

		// The previous chunk must be free
		if ( !prev_chunk->mIsFree )
			break;

		// Check whether it can be combined or not
		if ( prev_chunk->mOffset + prev_chunk->mSize != chunk->mOffset )
			break;

		// Increase the chunk size
		prev_chunk->mSize += chunk->mSize;

		// Rebuild the link
		prev_chunk->mNextChunkIndex	= chunk->mNextChunkIndex;
		if ( prev_chunk->mNextChunkIndex != _EMPTY_CHUNK_LINK )
			NextChunk( prev_chunk )->mPrevChunkIndex = (_word) prev_chunkid;

		// Remove free chunk
		page->RemoveFreeChunk( chunk );

		// Remove chunk
		page->RemoveChunk( chunk );

		// Update the current chunk to continue combination
		chunk = prev_chunk;

		// Set the combine flag
		has_combine = _true;
	}

	return has_combine;
}

_ubool PageAllocator::CombineNextChunks( Page* page, Chunk*& chunk )
{
	_ubool has_combine = _false;

	for ( _dword next_chunkid = chunk->mNextChunkIndex; next_chunkid != _EMPTY_CHUNK_LINK; next_chunkid = NextChunkIndex( page, next_chunkid ) )
	{
		Chunk* next_chunk = page->mChunkPool.Index( next_chunkid );
		EGE_ASSERT( next_chunk != _null );

		// The next chunk must be free
		if ( !next_chunk->mIsFree )
			break;

		// Check whether it can be combined or not
		if ( chunk->mOffset + chunk->mSize != next_chunk->mOffset )
			break;

		// Increase the chunk size
		next_chunk->mOffset -= chunk->mSize;
		next_chunk->mSize	+= chunk->mSize;

		// Rebuild link
		next_chunk->mPrevChunkIndex	 = chunk->mPrevChunkIndex;
		if ( next_chunk->mPrevChunkIndex != _EMPTY_CHUNK_LINK )
			PrevChunk( next_chunk )->mNextChunkIndex = (_word) next_chunkid;

		// Remove free chunk
		page->RemoveFreeChunk( chunk );

		// Remove chunk
		page->RemoveChunk( chunk );

		// Update the current chunk to continue combination
		chunk = next_chunk;

		// Validate chunk
#ifdef _DEBUG
		ValidateChunk( chunk );
#endif
		// Set the combine flag
		has_combine = _true;
	}

	return has_combine;
}

PageAllocator::Page* PageAllocator::GetPage( _dword index )
{
	Page** page = mPagePool.Index( index );
	if ( page == _null )
		return _null;

	return *page;
}

const PageAllocator::Page* PageAllocator::GetPage( _dword index ) const
{
	const Page* const * page = mPagePool.Index( index );
	if ( page == _null )
		return _null;

	return *page;
}

PageAllocator::Page* PageAllocator::CreatePage( _dword size, _dword* index )
{
	// Find the empty page
	_dword page_index = -1;
	Page** page_slot_in_pool = mPagePool.Create( &page_index );
	if ( page_slot_in_pool == _null )
		return _null;

	// Create page
	*page_slot_in_pool = (Page*) (*mAllocateFunc)( sizeof( Page ) + size );
	if ( *page_slot_in_pool == _null )
		return _null;

	// Initialize page
	Page* page					= *page_slot_in_pool;
	page->mPageIndex			= page_index;
	page->mBaseAddressOfChunks	= ( (_qword) page ) + sizeof( Page );
	page->mSize					= size;
	page->mFreeChunks.SetSwapElementCallbackFunc( Page::OnSwapElement );
	page->mFreeChunks.Clear( );
	page->mChunkPool.Clear( );

	// We make the first whole free chunk of this page
	Chunk* new_chunk = page->mChunkPool.Create( );
	if ( new_chunk == _null )
		return _null;

	// Build the first free chunk
	new_chunk->mOffset			= 0;
	new_chunk->mSize			= size;
	new_chunk->mPageIndex		= page_index;
	new_chunk->mIsFree			= _true;
	new_chunk->mPrevChunkIndex	= _EMPTY_CHUNK_LINK;
	new_chunk->mNextChunkIndex	= _EMPTY_CHUNK_LINK;

	// Insert it into free chunk heap
	page->InsertFreeChunk( new_chunk );

	// Feedback the page index
	if ( index != _null )
		*index = page_index;

	return page;
}

_void PageAllocator::ReleasePage( Page* page )
{
	if ( page == _null )
		return;

	// Remove it from pool
	mPagePool.Remove( page->mPageIndex );

	// Free the page buffer
	if ( mFreeFunc != _null )
		(*mFreeFunc)( page->GetAllocatedAddress( ) );
}

_ubool PageAllocator::Create( _dword page_size, _dword min_chunk_size, OnAllocate allocate_func, OnFree free_func )
{
	Clear( );

	// Set the pages and chunks configures
	mPageSize		= page_size;
	mMinChunkSize	= min_chunk_size;

	// Set callback functions
	mAllocateFunc	= allocate_func;
	mFreeFunc		= free_func;

	return _true;
}

_void PageAllocator::Clear( )
{
	// Release all pages
	for ( PagePool::Iterator it = mPagePool.GetHeadIterator( ); it.IsValid( ); it ++ )
	{
		Page* page = it;

		// Free the page buffer
		if ( mFreeFunc != _null )
			(*mFreeFunc)( page->GetAllocatedAddress( ) );
	}

	mPagePool.Clear( );
}

_void PageAllocator::Cleanup( )
{
}

const PageAllocator::Chunk* PageAllocator::SearchChunkByID( _dword id ) const
{
	// Get page by index
	const Page* page = SearchPageByID( id );
	if ( page == _null )
		return _null;

	// Get chunk by index
	return page->mChunkPool.Index( id >> 16 );
}

const PageAllocator::Page* PageAllocator::SearchPageByID( _dword id ) const
{
	return GetPage( id & 0x0000FFFF );
}

PageAllocator::Chunk* PageAllocator::Allocate( _dword size, _dword& id, _byte*& address )
{
	if ( size > mPageSize )
		return _null;

	// The allocated chunk
	Chunk* chunk = _null;

	// Try to allocate from all existing pages
	for ( PagePool::Iterator it = mPagePool.GetHeadIterator( ); it.IsValid( ); it ++ )
	{
		Page* page = it;

		// Check whether you have enough space
		if ( page->GetMaxFreeChunkSize( ) < size )
			continue;

		// Try to allocate it from this page
		chunk = CreateChunk( page, size, &id, address );
		if ( chunk != _null )
			break;
	}

	// If we can't allocated from any existing pages then we need to allocated from a new page
	if ( chunk == _null )
	{
		// All the pages failed to allocate chunk, so we need to create a page to allocate it
		Page* page = CreatePage( mPageSize, _null );
		if ( page == _null )
			return _null;

		// Try to allocate it from this page
		chunk = CreateChunk( page, size, &id, address );
		if ( chunk == _null )
			return _null;
	}

	// Feedback the chunk unique ID
	id = BuildChunkID( id, chunk->mPageIndex );

	return chunk;
}

_void PageAllocator::Free( _dword id )
{
	// Get chunk by ID
	Chunk* chunk = (Chunk*) SearchChunkByID( id );
	if ( chunk == _null )
		return;

	// Release chunk
	ReleaseChunk( chunk );
}