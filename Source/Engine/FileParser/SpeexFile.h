//! @file     SpeexFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// SpeexFile
//----------------------------------------------------------------------------

class SpeexFile : public INTERFACE_SOUNDFILE_IMPL( ISpeexFile )
{
private:
	typedef INTERFACE_SOUNDFILE_IMPL( ISpeexFile ) BaseClass;

private:

private:
	//!	The SPX buffer stream
	IStreamReaderRef	mStreamReader;

	//!	The OGG sync state
	ogg_sync_state		mOGGSyncState;

	//!	The SPX bits
	//SpeexBits			mSPXBits;

private:

public:
	SpeexFile( );
	virtual ~SpeexFile( );

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

// ISpeexFile Interface
public:
};

}