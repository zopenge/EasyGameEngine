//! @file     SpeexFile.cpp
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// SpeexFile Implementation
//----------------------------------------------------------------------------

SpeexFile::SpeexFile( )
{
	EGE_INIT( mOGGSyncState );

//	EGE_INIT( mSPXBits );
}

SpeexFile::~SpeexFile( )
{
}

_FILE_FORMAT SpeexFile::GetFileID( ) const
{
	return _FF_SPEEX;
}

_ubool SpeexFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	_ubool ret = _true;

	// Check the open result
	if ( ret == _false )
		return _false;

	// Save the stream reader
	mStreamReader = stream_reader;

	// Build the sound header info

	return _true;
}

_void SpeexFile::Unload( )
{
	EGE_INIT( mOGGSyncState );

//	EGE_INIT( mSPXBits );

	BaseClass::Unload( );
}

_double SpeexFile::TimeSeek( _SEEK flag, _double time )
{
	// Change time to offset in bytes

	switch ( flag )
	{
		case _SEEK_BEGIN:
		{
		}
		break;

		case _SEEK_CURRENT:
		{
		}
		break;

		case _SEEK_END:
		{
		}
		break;

		default:
			return -1.0;
	}

	return 0.0;
}

_double SpeexFile::GetCurTime( ) const
{
	return 0.0;
}

_dword SpeexFile::Decode( _byte* buffer, _dword size )
{
	if ( buffer == _null || size == 0 )
		return 0;

	return 0;
}