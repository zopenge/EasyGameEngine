//! @file     CompressionEncoderZLIB.h
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// CompressionEncoderZLIB
//----------------------------------------------------------------------------

class CompressionEncoderZLIB : public INTERFACE_STREAMPROCESSOR_IMPL( ICompressionEncoder )
{
private:
	//!	The ZIp stream
	struct ZIPStream : public z_stream
	{
		_ubool	mIsInited;
	};

private:
	//!	The compression level
	_LEVEL		mLevel;
	//!	The compression ZLIB stream
	ZIPStream	mZIPStream;

// TStreamProcessor Interface
private:
	virtual _ubool	OnBeginProcessBuffer( ) override;
	virtual _ubool	OnProcessBuffer( const _byte* input_buf, _dword input_size, IStreamWriter* stream_writer, _dword chunk_size, _dword& output_size ) override;
	virtual _ubool	OnEndProcessBuffer( ) override;

public:
	CompressionEncoderZLIB( );
	virtual ~CompressionEncoderZLIB( );

// ICompressionEncoder Interface
public:
	virtual _void	SetLevel( _LEVEL level ) override;
};

}