//! @file     chromePlatformClipboard.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform-Clipboard Implementation
//----------------------------------------------------------------------------

_ubool Platform::OpenClipboard( )
{
	return _false;
}

_void Platform::CloseClipboard( )
{
}

_handle Platform::GetClipboardData( _CLIPBOARD_FLAG flag, _byte*& pointer, _dword* size )
{
	return _null;
}

_void Platform::CloseClipboardData( _handle handle )
{
}

_ubool Platform::ReadClipboard( _CLIPBOARD_FLAG flag, _byte* buffer, _dword size )
{
	if ( buffer == _null || size == 0 )
		return _false;

	_dword buffer_size = 0; _byte* pointer = _null;

	// Get the clipboard buffer data
	_handle handle = GetClipboardData( flag, pointer, &buffer_size );
	if ( handle == _null )
		return _false;

	// Copy the buffer data
	EGE_MEM_CPY( buffer, pointer, Math::Min( buffer_size, size ) );

	return _true;
}

_ubool Platform::WriteClipboard( _CLIPBOARD_FLAG flag, const _void* buffer, _dword size )
{
	if ( buffer == _null || size == 0 )
		return _false;

	return _true;
}