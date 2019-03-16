//! @file     StdAllocator.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

// --------------------------------------------------------------------------------------------------------------
// StdAllocator Implementation
// --------------------------------------------------------------------------------------------------------------

StdAllocator::StdAllocator( _dword arrange_size ) : BaseClass( arrange_size )
{
}

StdAllocator::~StdAllocator( )
{
}

_void StdAllocator::Cleanup( )
{
}

_ubool StdAllocator::CanAlloc( _dword size ) const
{
	return _true;
}

_byte* StdAllocator::Alloc( _dword size )
{
	// Arrange size
	size = Math::UpperArrange( size, mArrangeSize );

	// Check size
	if ( size == 0 )
		return _null;

	_byte* buffer = (_byte*) ::malloc( size );
	return buffer;
}

_byte* StdAllocator::ReAlloc( _void* pointer, _dword size )
{
	// Arrange size
	size = Math::UpperArrange( size, mArrangeSize );

	// Check size
	if ( size == 0 )
		return _null;

	return (_byte*) ::realloc( pointer, size );
}

_void StdAllocator::Free( _void* pointer )
{
	if ( pointer == _null )
		return;

	::free( pointer );
}

_void StdAllocator::FreeAll( )
{
}