//! @file     MIDIFile.cpp
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

#ifndef _EGE_DISABLE_MIDI_FILE_

//----------------------------------------------------------------------------
// MIDIFile Implementation
//----------------------------------------------------------------------------

MIDIFile::MIDIFile( )
{
}

MIDIFile::~MIDIFile( )
{
}

_FILE_FORMAT MIDIFile::GetFileID( ) const
{
	return _FF_MIDI;
}

_ubool MIDIFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	// Read MIDI buffer data
	mBuffer.Create( stream_reader->GetSize( ) );
	stream_reader->ReadBuffer( mBuffer, stream_reader->GetSize( ) );

	return _true;
}

_void MIDIFile::Unload( )
{
	BaseClass::Unload( );
}

_double MIDIFile::TimeSeek( _SEEK flag, _double time )
{
	return 0.0;
}

_double MIDIFile::GetCurTime( ) const
{
	return 0.0;
}

_dword MIDIFile::Decode( _byte* buffer, _dword size )
{
	if ( buffer == _null || size == 0 )
		return 0;

	return 0;
}

const _byte* MIDIFile::GetBufferData( ) const 
{
	return mBuffer;
}

_dword MIDIFile::GetBufferSize( ) const 
{
	return mBuffer.Number( );
}

#endif