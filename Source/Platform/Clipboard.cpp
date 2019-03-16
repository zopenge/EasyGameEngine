//! @file     Clipboard.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Clipboard Implementation
//----------------------------------------------------------------------------

_ubool Clipboard::Copy( WStringPtr string )
{
 if ( Platform::OpenClipboard( ) == _false )
  return _false;

 _ubool ret = Platform::WriteClipboard( _CLIPBOARD_UNICODETEXT, string.Str( ), string.SizeOfBytes( ) );

 Platform::CloseClipboard( );

 return ret;
}

_ubool Clipboard::Paste( WString& string )
{
 if ( Platform::OpenClipboard( ) == _false )
  return _false;

 _byte* buffer = _null;

 // Firstly we try to get the unicode text
 _handle handle = Platform::GetClipboardData( _CLIPBOARD_UNICODETEXT, buffer );
 if ( handle != _null )
 {
  string = (const _charw*) buffer;
 }
 // Secondly we try to get the normal text
 else
 {
  handle = Platform::GetClipboardData( _CLIPBOARD_TEXT, buffer );
  if ( handle != _null )
   string.FromString( _ENCODING_ANSI, (const _chara*) buffer );
 }

 Platform::CloseClipboardData( handle );
 Platform::CloseClipboard( );

 // Check the clipboard data handle to check whether paste procession is successful or failed
 return handle != _null;
}