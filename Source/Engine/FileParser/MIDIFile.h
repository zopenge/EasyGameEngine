//! @file     MIDIFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

#ifndef _EGE_DISABLE_MIDI_FILE_

namespace EGE
{

//----------------------------------------------------------------------------
// MIDIFile
//----------------------------------------------------------------------------

class MIDIFile : public INTERFACE_SOUNDFILE_IMPL( IMIDIFile )
{
public:
	//!	The MIDI file ID
	enum { _FILE_ID = EGE_ID( 'M', 't', 'h', 'd' ) };

private:
	typedef INTERFACE_SOUNDFILE_IMPL( IMIDIFile ) BaseClass;

private:
	MemArrayPtr< _byte > mBuffer;

public:
	MIDIFile( );
	virtual ~MIDIFile( );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT	GetFileID( ) const override;

	virtual _ubool 			LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 			Unload( ) override;

// IBinaryFile Interface
public:

// ISoundFile Interface
public:
	virtual _double			TimeSeek( _SEEK flag, _double time ) override;
	virtual _double			GetCurTime( ) const override;

	virtual _dword			Decode( _byte* buffer, _dword size ) override;

// IMIDIFile Interface
public:
	virtual const _byte*	GetBufferData( ) const override;
	virtual _dword			GetBufferSize( ) const override;
};

}

#endif