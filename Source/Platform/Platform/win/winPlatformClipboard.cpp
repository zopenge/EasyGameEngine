//! @file     winPlatformClipboard.cpp
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
 return ::OpenClipboard( _null ) != 0;
}

_void Platform::CloseClipboard( )
{
 ::CloseClipboard( );
}

_handle Platform::GetClipboardData( _CLIPBOARD_FLAG flag, _byte*& pointer, _dword* size )
{
 HGLOBAL globalmem = ::GetClipboardData( flag );
 if ( globalmem == _null )
  return _null;

 // Get the buffer data pointer
 _byte* buffer = (_byte*) ::GlobalLock( globalmem );
 if ( buffer == _null )
  return _null;

 // Feedback the buffer data pinter ( jump the size info chunk )
 pointer = buffer + sizeof( _dword );

 // Feedback the buffer data size
 if ( size != _null )
  *size = *(_dword*) buffer;

 return globalmem;
}

_void Platform::CloseClipboardData( _handle handle )
{
 if ( handle == _null )
  return;

 ::GlobalUnlock( handle );
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

 // Allocate the buffer data of clipboard
 HGLOBAL globalmem = ::GlobalAlloc( GHND | GMEM_DDESHARE, size + sizeof( _dword ) );
 if ( globalmem == _null )
  return _false;

 // Get the buffer data pinter
 _byte* clipboard_buffer = (_byte*) ::GlobalLock( globalmem );
 if ( clipboard_buffer == _null )
  { ::GlobalFree( globalmem ); return _false; }

 // Write the buffer data size
 *(_dword*) clipboard_buffer = size;

 // Copy the buffer data
 EGE_MEM_CPY( clipboard_buffer + sizeof( _dword ), buffer, size );
 ::GlobalUnlock( globalmem );

 // Set the buffer data to clipboard
 ::EmptyClipboard( );
 ::SetClipboardData( flag, globalmem );

 // Free the buffer data
 ::GlobalFree( globalmem );

 return _true;
}