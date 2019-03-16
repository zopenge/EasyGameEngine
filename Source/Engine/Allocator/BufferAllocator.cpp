//! @file     BufferAllocator.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

// --------------------------------------------------------------------------------------------------------------
// BufferAllocator Implementation
// --------------------------------------------------------------------------------------------------------------

BufferAllocator::BufferAllocator( )
{
}

BufferAllocator::~BufferAllocator( )
{
}

_ubool BufferAllocator::Create( _dword size, _dword arrange_size )
{
	IStackAllocatorRef allocator = GetInterfaceFactory( )->CreateStackAllocator( size, arrange_size );
	if ( allocator.IsNull( ) )
		return _false;

	mStackAllocators.Append( allocator );

	return _true;
}

_void BufferAllocator::Reset( )
{
	for ( _dword i = 0; i < mStackAllocators.Number( ); i ++ )
		mStackAllocators[i]->FreeAll( );
}

_byte* BufferAllocator::Alloc( _dword size )
{
	if ( size == 0 )
		return _null;

	// Try to allocate from existing allocators
	for ( _dword i = 0; i < mStackAllocators.Number( ); i ++ )
	{
		_byte* buffer = mStackAllocators[i]->Alloc( size );
		if ( buffer != _null )
			return buffer;
	}

	// Get the arrange size
	_dword arrange_size = mStackAllocators[0]->GetArrangeSize( );

	// Get the stack size
	_dword stack_size = Math::UpperArrange( Math::Max( mStackAllocators[0]->GetStackSize( ), size ), arrange_size );
	EGE_ASSERT( stack_size != 0 );

	// Create new allocator to alloc it
	IStackAllocatorRef allocator = GetInterfaceFactory( )->CreateStackAllocator( stack_size, arrange_size );
	if ( allocator.IsNull( ) )
		return _null;

	mStackAllocators.Append( allocator );

	// Allocate it
	return allocator->Alloc( size );
}
