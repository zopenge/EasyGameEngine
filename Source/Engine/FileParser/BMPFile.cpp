//! @file     BMPFile.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// BMPFile Implementation
//----------------------------------------------------------------------------

BMPFile::BMPFile( )
{
}

BMPFile::~BMPFile( )
{
}

_FILE_FORMAT BMPFile::GetFileID( ) const
{
	return _FF_BMP;
}

_ubool BMPFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	return _true;
}

_void BMPFile::Unload( )
{
	BaseClass::Unload( );
}