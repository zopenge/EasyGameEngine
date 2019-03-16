//! @file     StreamingPCMFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// StreamingPCMFile
//----------------------------------------------------------------------------

class StreamingPCMFile : public INTERFACE_SOUNDFILE_IMPL( IStreamingPCMFile )
{
private:
	typedef INTERFACE_SOUNDFILE_IMPL( IStreamingPCMFile ) BaseClass;

private:
	Lock				mLock;

	IStreamWriterRef	mStreamWriter;

public:
	StreamingPCMFile( );
	virtual ~StreamingPCMFile( );

public:
	_ubool Initialize( const SoundHeaderInfo& info );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT	GetFileID( ) const override;

	virtual _ubool 			LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 			Unload( ) override;

	virtual _ubool			SaveToStream( IStreamWriter* stream_writer, _dword flags ) const override;

// ISoundFile Interface
public:
	virtual _ubool			IsStreaming( ) const override;

	virtual _double			TimeSeek( _SEEK flag, _double time ) override;
	virtual _double			GetCurTime( ) const override;

	virtual _dword			Decode( _byte* buffer, _dword size ) override;

// IStreamingPCMFile Interface
public:
	virtual _void			WriteBuffer( _dword size, const _byte* buffer ) override;
};

}