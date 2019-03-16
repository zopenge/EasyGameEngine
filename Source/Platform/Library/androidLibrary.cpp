//! @file     androidLibrary.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Library Implementation
//----------------------------------------------------------------------------

_ubool Library::LoadVersionInfo( const _void* address )
{
	return _true;
}

_ubool Library::LoadEmbeddedManifestInfo( const _void* address, _dword size )
{
	return _true;
}

_ubool Library::LoadResourceFromMemory( _dword virtualaddress, const _byte* base, const _byte* resource )
{
	return _true;
}

_ubool Library::Load( const _byte* buffer, _dword size, OnLoadDependentDLL funcpointer, const QwordParameters2& parameters )
{
	return _true;
}

_void Library::Free( )
{
}

_void* Library::GetFunction( AStringPtr functionname ) const
{
	return _null;
}