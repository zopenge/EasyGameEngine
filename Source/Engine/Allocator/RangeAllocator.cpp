//! @file     RangeAllocator.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

// --------------------------------------------------------------------------------------------------------------
// RangeAllocator Implementation
// --------------------------------------------------------------------------------------------------------------

RangeAllocator::RangeAllocator( )
{
}

RangeAllocator::~RangeAllocator( )
{
}

_ubool RangeAllocator::Create( _dword size, _dword arrange_size )
{
	// Create allocator
	mAllocator = GetInterfaceFactory( )->CreateLinearAllocator( (_byte*)_BASE_ADDRESS, size, arrange_size );
	if ( mAllocator.IsNull( ) )
		return _false;

	return _true;
}

_void RangeAllocator::Cleanup( )
{
	mAllocator->Cleanup( );
}

_ubool RangeAllocator::CanAlloc( _dword size ) const
{
	return mAllocator->CanAlloc( size );
}

_dword RangeAllocator::Alloc( _dword size )
{
	// Allocate buffer
	_byte* buffer = mAllocator->Alloc( size );
	if ( buffer == _null )
		return _null;

	// Feedback the start bytes
	_dword index = (_dword)(size_t)buffer - _BASE_ADDRESS;
	return index;
}

_dword RangeAllocator::Reserve( _dword index )
{
	return mAllocator->ReserveBufferByStartBytes( index );
}

_dword RangeAllocator::Free( _dword index )
{
	return mAllocator->FreeByStartBytes( index );
}
