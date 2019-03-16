//! @file     winPlatformResource.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform Resource Helpful Functions Implementation
//----------------------------------------------------------------------------

static BOOL CALLBACK OnEnumResNameCallback( HMODULE module, LPCWSTR type, LPWSTR name, LONG_PTR parameter )
{
 EventEnumResFile* enum_res_file_event = (EventEnumResFile*)parameter;
 EGE_ASSERT( enum_res_file_event != _null );

 // Check resource name
 if ( IS_INTRESOURCE( name ) == _false )
  return _false;

 // Convert resource name from ID to string
 WString res_name = WString( ).FromValue( (_dword)name, 10 );

 // Notify outside
 return (*enum_res_file_event->mEnumResNameProc)( type, res_name.Str( ), enum_res_file_event->mParameter );
}

//----------------------------------------------------------------------------
// Platform Resource Implementation
//----------------------------------------------------------------------------

_handle Platform::FindResource( _handle module, const _charw* name, const _charw* type )
{
 return ::FindResourceW( (HMODULE) module, name, type );
}

_handle Platform::LoadResource( _handle module, _handle resinfo )
{
 return ::LoadResource( (HMODULE) module, (HRSRC) resinfo );
}

_void Platform::FreeResource( _handle module, _handle resinfo )
{
 ::FreeResource( resinfo );
}

const _byte* Platform::LockResource( _handle resdata )
{
 return (const _byte*) ::LockResource( resdata );
}

_dword Platform::SizeOfResource( _handle module, _handle resinfo )
{
 return ::SizeofResource( (HMODULE) module, (HRSRC) resinfo );
}

_ubool Platform::EnumResourceNames( _handle module, const _charw* type, OnEnumResNameProc funcpointer, _void* parameter )
{
 if ( type == _null )
  return _false;

 EventEnumResFile enum_res_file_event;
 enum_res_file_event.mEnumResNameProc = funcpointer;
 enum_res_file_event.mParameter   = parameter;

 return EGE_BOOLEAN( ::EnumResourceNamesW( (HMODULE) module, type, OnEnumResNameCallback, (LONG_PTR) &enum_res_file_event ) );
}