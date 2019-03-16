//! @file     winPlatformVersion.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform Version Implementation
//----------------------------------------------------------------------------

_dword Platform::GetFileVersionInfoSize( const _charw* filename )
{
	if ( filename == _null )
		return 0;

	return ::GetFileVersionInfoSizeW( filename, _null );
}

_ubool Platform::GetFileVersionInfo( const _charw* filename, _dword buffersize, _void* bufferdata )
{
	if ( filename == _null )
		return _false;

	return EGE_BOOLEAN( ::GetFileVersionInfoW( filename, _null, buffersize, bufferdata ) );
}

_ubool Platform::VerQueryBuffer( _void* block, const _charw* subblock, _void*& bufferdata, _dword& buffersize )
{
	if ( bufferdata == _null )
		return _false;

	return EGE_BOOLEAN( ::VerQueryValueW( block, subblock, &bufferdata, (PUINT) &buffersize ) );
}