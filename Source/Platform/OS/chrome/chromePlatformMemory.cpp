//! @file     chromePlatformMemory.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform Memory Implementation
//----------------------------------------------------------------------------

_chara* Platform::HeapAllocStr( const _chara* string, _handle heaphandle )
{
	_dword  size	= AStringPtr( string ).SizeOfBytes( );
	_chara* buffer	= (_chara*) Platform::HeapAlloc( size );
	EGE_MEM_CPY( buffer, AStringPtr( string ).Str( ), size );

	return buffer;
}

_charw* Platform::HeapAllocStr( const _charw* string, _handle heaphandle )
{
	_dword  size	= WStringPtr( string ).SizeOfBytes( );
	_charw* buffer	= (_charw*) Platform::HeapAlloc( size );
	EGE_MEM_CPY( buffer, WStringPtr( string ).Str( ), size );

	return buffer;
}

_void* Platform::HeapAlloc( _dword size, _handle heaphandle )
{
	EGE_ASSERT( size > 0 );

	return malloc( size );
}

_void* Platform::HeapReAlloc( _void* pointer, _dword size, _handle heaphandle )
{
	EGE_ASSERT( size > 0 );

	if ( pointer == _null )
		return malloc( size );
	else
		return realloc( pointer, size );
}

_void Platform::HeapFree( _void* pointer, _handle heaphandle )
{
	if ( pointer == _null )
		return;

	free( pointer );
}

_void* Platform::GlobalAlloc( _dword size )
{
	return HeapAlloc( size );
}

_void* Platform::GlobalReAlloc( _void* pointer, _dword size )
{
	return HeapReAlloc( pointer, size, 0 );
}

_void Platform::GlobalFree( _void* pointer )
{
	HeapFree( pointer );
}

_void* Platform::ComAlloc( _dword size )
{
	EGE_ASSERT( size > 0 );

	return _null;
}

_charw* Platform::ComAllocString( const _chara* string )
{
	if ( string == _null )
		return _null;

	return _null;
}

_charw* Platform::ComAllocString( const _charw* string )
{
	if ( string == _null )
		return _null;

	return _null;
}

_void* Platform::ComReAlloc( _void* pointer, _dword size )
{
	EGE_ASSERT( size > 0 );

	return _null;
}

_void Platform::ComFree( _void* pointer )
{
	if ( pointer == _null )
		return;
}

_charw* Platform::AllocString( const _charw* string )
{
	if ( string == _null )
		return _null;

	_dword length	= Platform::StringLength( string ) + 1;
	_dword size		= length * sizeof( _charw );
	_void* buffer	= Platform::HeapAlloc( size );
	EGE_MEM_CPY( buffer, string, size );

	return (_charw*) buffer;
}

_void Platform::FreeString( _charw* string )
{
	if ( string == _null )
		return;

	Platform::HeapFree( string );
}

_void* Platform::VirtualAlloc( _dword size )
{
	if ( size == 0 )
		return _null;

	return _null;
}

_void Platform::VirtualFree( _void* pointer )
{
	if ( pointer == _null )
		return;
}