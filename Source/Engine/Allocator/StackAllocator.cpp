//! @file     StackAllocator.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

// --------------------------------------------------------------------------------------------------------------
// StackAllocator Implementation
// --------------------------------------------------------------------------------------------------------------

StackAllocator::StackAllocator( _dword arrange_size ) : BaseClass( arrange_size )
{
	mBuffer			= _null;
	mBufferSize		= 0;
	mBufferOffset	= 0;
}

StackAllocator::~StackAllocator( )
{
	EGE_DELETE_ARRAY( mBuffer );
}

_ubool StackAllocator::Create( _dword size )
{
	EGE_DELETE_ARRAY( mBuffer );

	mBuffer			= new _byte[ size ];
	mBufferSize		= size;
	mBufferOffset	= 0;

	return _true;
}

_void StackAllocator::Cleanup( )
{
}

_ubool StackAllocator::CanAlloc( _dword size ) const
{
	// Arrange size
	size = Math::UpperArrange( size, mArrangeSize );

	// Check the range
	if ( mBufferOffset + size > mBufferSize )
		return _false;

	return _true;
}

_byte* StackAllocator::Alloc( _dword size )
{
	// Check size
	if ( size == 0 )
		return _null;

	// Arrange size
	size = Math::UpperArrange( size, mArrangeSize );

	// Check range
	if ( mBufferOffset + size > mBufferSize )
		return _null;

	// Get address pointer
	_byte* address = mBuffer + mBufferOffset;

	// Update buffer index
	mBufferOffset += size;

	return address;
}

_void StackAllocator::Free( _void* pointer )
{
}

_void StackAllocator::FreeAll( )
{
	mBufferOffset = 0;
}

_dword StackAllocator::GetOffset( ) const
{
	return mBufferOffset;
}

_void StackAllocator::SetOffset( _dword offset ) 
{
	mBufferOffset = offset;
}

_dword StackAllocator::GetStackSize( ) const
{
	return mBufferSize;
}

_void StackAllocator::Pop( _dword size )
{
	// Arrange size
	size = Math::UpperArrange( size, mArrangeSize );

	// Check size
	if ( size == 0 )
		return;

	// Check range
	if ( mBufferOffset - size < mBufferSize )
		return;

	// Update buffer index
	mBufferOffset -= size;
}
