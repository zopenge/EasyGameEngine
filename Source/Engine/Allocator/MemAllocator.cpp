//! @file     MemAllocator.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

// --------------------------------------------------------------------------------------------------------------
// MemAllocator Implementation
// --------------------------------------------------------------------------------------------------------------

MemAllocator::MemAllocator( _dword arrange_size ) : BaseClass( arrange_size )
{
}

MemAllocator::~MemAllocator( )
{
}

_byte* MemAllocator::OnAllocate( _dword size )
{
	EGE_ASSERT( size > 0 );

	return new _byte[ size ];
}

_void MemAllocator::OnFree( _byte* address )
{
	delete[] address;
}

_ubool MemAllocator::Create( _dword page_size, _dword min_chunk_size )
{
	return mPageAllocator.Create( page_size, min_chunk_size, OnAllocate, OnFree );
}

_void MemAllocator::Cleanup( )
{
	mPageAllocator.Cleanup( );
}

_ubool MemAllocator::CanAlloc( _dword size ) const
{
	// Arrange size
	size = Math::UpperArrange( size, mArrangeSize );

	// Check size
	if ( size + sizeof( _dword ) > mPageAllocator.GetPageSize( ) )
		return _false;

	return _true;
}

_byte* MemAllocator::Alloc( _dword size )
{
	// Arrange size
	size = Math::UpperArrange( size, mArrangeSize );

	// Check size
	if ( size == 0 )
		return _null;

	// We put a chunk ID before the address what feedback, so need to exceed the size
	_dword size_with_chunk_id = size + sizeof( _dword );

	// The chunk unique ID
	_dword chunkid = -1;

	// The allocated address
	_byte* address = _null;

	// Allocate chunk
	PageAllocator::Chunk* chunk = mPageAllocator.Allocate( size_with_chunk_id, chunkid, address );
	if ( chunk == _null )
		return _null;

	// Put chunk ID with allocated address
	( *(_dword*) address ) = chunkid;

	// Feedback the allocated address by jumping the chunk ID 
	_byte* buffer = ( (_byte*) address ) + sizeof( _dword );
	return buffer;
}

_void MemAllocator::Free( _void* pointer )
{
	if ( pointer == _null )
		return;

	// Get the chunk ID
	_dword chunkid = *(_dword*) ( ( (_byte*) pointer ) - sizeof( _dword ) );

	// Free chunk
	mPageAllocator.Free( chunkid );
}

_void MemAllocator::FreeAll( )
{
	mPageAllocator.Clear( );
}