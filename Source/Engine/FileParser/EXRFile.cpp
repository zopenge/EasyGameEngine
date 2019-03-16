//! @file     EXRFile.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// EXRFile Implementation
//----------------------------------------------------------------------------

EXRFile::EXRFile( )
{
}

EXRFile::~EXRFile( )
{
	Unload( );
}

_FILE_FORMAT EXRFile::GetFileID( ) const
{
	return _FF_EXR;
}

_ubool EXRFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	return _true;
}

_void EXRFile::Unload( )
{
	BaseClass::Unload( );
}