//! @file     RingAllocator.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

// --------------------------------------------------------------------------------------------------------------
// RingAllocator Implementation
// --------------------------------------------------------------------------------------------------------------

RingAllocator::RingAllocator( _dword arrange_size ) : BaseClass( arrange_size )
{
	mBuffer			= _null;
	mBufferSize		= 0;
	mBufferOffset	= 0;
}

RingAllocator::~RingAllocator( )
{
	EGE_DELETE_ARRAY( mBuffer );
}

_ubool RingAllocator::Create( _dword size )
{
	EGE_DELETE_ARRAY( mBuffer );

	mBuffer			= new _byte[ size ];
	mBufferSize		= size;
	mBufferOffset	= 0;

	return _true;
}

_void RingAllocator::Cleanup( )
{
}

_ubool RingAllocator::CanAlloc( _dword size ) const
{
	// Arrange size
	size = Math::UpperArrange( size, mArrangeSize );

	// Check the range
	if ( size > mBufferSize )
		return _false;

	return _true;
}

_byte* RingAllocator::Alloc( _dword size )
{
	// Check size
	if ( size == 0 )
		return _null;

	// Arrange size
	size = Math::UpperArrange( size, mArrangeSize );

	// Check the range
	if ( size > mBufferSize )
		return _null;

	// Check range
	if ( mBufferOffset + size > mBufferSize )
		mBufferOffset = 0; // Rollback

	// Get address pointer
	_byte* address = mBuffer + mBufferOffset;

	// Update buffer index
	mBufferOffset += size;

	return address;
}

_void RingAllocator::Free( _void* pointer )
{
}

_void RingAllocator::FreeAll( )
{
	mBufferOffset = 0;
}