//! @file     StreamWriterProcessor.cpp
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// StreamWriterProcessor Implementation
//----------------------------------------------------------------------------

StreamWriterProcessor::StreamWriterProcessor( const MD5Code& md5_code )
{
	mMD5Code	= md5_code;
	mMD5Builder	= _null;

	if ( mMD5Code != MD5Code::cNull )
		mMD5Builder = new MD5( );
}

StreamWriterProcessor::~StreamWriterProcessor( )
{
	EGE_DELETE( mMD5Builder );
}

_ubool StreamWriterProcessor::OnBeginProcessBuffer( )
{
	return _true;
}

_ubool StreamWriterProcessor::OnProcessBuffer( const _byte* input_buf, _dword input_size, IStreamWriter* stream_writer, _dword chunk_size, _dword& output_size )
{
	// Update the MD5 code
	if ( mMD5Builder != _null )
	{
		mMD5Builder->AppendBuffer( input_buf, input_size );

		output_size = input_size;
	}

	return _true;
}

_ubool StreamWriterProcessor::OnEndProcessBuffer( )
{
	// Check the MD5 code
	if ( mMD5Builder != _null )
	{
		mMD5Builder->Digest( );

		MD5Code md5_code = mMD5Builder->GetCode( );
		if ( md5_code != mMD5Code )
		{
			WLOG_TRACE_2( L"The '%s' is different with '%s', MD5 check failed", 
				md5_code.ToWString( _true ).Str( ), mMD5Code.ToWString( _true ).Str( ) );

			return _false;
		}
	}

	return _true;
}