//! @file     OffsetAllocator.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

// --------------------------------------------------------------------------------------------------------------
// OffsetAllocator Implementation
// --------------------------------------------------------------------------------------------------------------

OffsetAllocator::OffsetAllocator( )
{
}

OffsetAllocator::~OffsetAllocator( )
{
}

_void OffsetAllocator::Cleanup( )
{
	mAllocator->Cleanup( );
}

_ubool OffsetAllocator::CanAlloc( _dword size ) const
{
	return mAllocator->CanAlloc( size );
}

_ubool OffsetAllocator::Create( _dword size, _dword arrange_size )
{
	mAllocator = GetInterfaceFactory( )->CreateLinearAllocator( (_byte*)_BASE_ADDRESS, size, arrange_size );
	if ( mAllocator.IsNull( ) )
		return _false;

	return _true;
}

_dword OffsetAllocator::Alloc( _dword size )
{
	if ( size == 0 )
		return -1;

	_byte* buffer = mAllocator->Alloc( size );
	if ( buffer == _null )
		return -1;

	_dword offset = (_dword)(size_t)buffer - _BASE_ADDRESS;
	return offset;
}

_dword OffsetAllocator::Free( _dword offset )
{
	return mAllocator->FreeByStartBytes( offset );
}

_void OffsetAllocator::FreeAll( )
{
	mAllocator->FreeAll( );
}

_dword OffsetAllocator::Reserve( _dword offset )
{
	return mAllocator->ReserveBufferByStartBytes( offset );
}