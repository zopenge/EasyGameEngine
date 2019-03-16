//! @file     StreamWriterProcessor.h
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// StreamWriterProcessor
//----------------------------------------------------------------------------

class StreamWriterProcessor : public INTERFACE_STREAMPROCESSOR_IMPL( IStreamProcessor )
{
private:
	//!	The MD5 code
	MD5Code	mMD5Code;
	//!	The MD5 builder
	MD5*	mMD5Builder;

// TStreamProcessor Interface
private:
	virtual _ubool	OnBeginProcessBuffer( ) override;
	virtual _ubool	OnProcessBuffer( const _byte* input_buf, _dword input_size, IStreamWriter* stream_writer, _dword chunk_size, _dword& output_size ) override;
	virtual _ubool	OnEndProcessBuffer( ) override;

public:
	StreamWriterProcessor( const MD5Code& md5_code );
	virtual ~StreamWriterProcessor( );
};

}
