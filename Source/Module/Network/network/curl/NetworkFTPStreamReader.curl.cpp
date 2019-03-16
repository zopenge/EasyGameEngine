//! @file     NetworkFTPStreamReader.curl.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

#if (_USE_CRUL_SDK == 1)

//----------------------------------------------------------------------------
// NetworkFTPStreamReader Implementation
//----------------------------------------------------------------------------

NetworkFTPStreamReader::NetworkFTPStreamReader( INetworkStreamReaderNotifier* notifier ) : BaseClass( notifier )
{
}

NetworkFTPStreamReader::~NetworkFTPStreamReader( )
{
}

_dword NetworkFTPStreamReader::OnDebugFunctionCallback( CURL* urlhandle, curl_infotype type, _chara* buffer, _dword size, _void* userdata )
{
	NetworkFTPStreamReader* http_stream_reader = (NetworkFTPStreamReader*) userdata;
	EGE_ASSERT( http_stream_reader != _null );

	//AString string( buffer, size );
	//ALOG_TRACE( string );

	// Feedback the total bytes	
	return size;
}

_dword NetworkFTPStreamReader::OnWriteFunctionCallback( _chara* buffer, _dword size, _dword number, _void* userdata )
{
	NetworkFTPStreamReader* http_stream_reader = (NetworkFTPStreamReader*) userdata;
	EGE_ASSERT( http_stream_reader != _null );

	// Get the total size
	_dword totalsize = size * number;

	// Write the buffer data
	http_stream_reader->mStreamWriter->WriteBuffer( buffer, totalsize );

	// Notify outside
	http_stream_reader->GetNotifier( )->OnReading( totalsize, http_stream_reader->mMIMEContentSize );
	
	// Feedback the total bytes	
	return totalsize;
}

_dword NetworkFTPStreamReader::OnReadFunctionCallback( _chara* buffer, _dword size, _dword number, _void* userdata )
{
	NetworkFTPStreamReader* http_stream_reader = (NetworkFTPStreamReader*) userdata;
	EGE_ASSERT( http_stream_reader != _null );

	// Get the total size
	_dword totalsize = size * number;

	// Feedback the total bytes
	return totalsize;
}

_dword NetworkFTPStreamReader::OnHeaderFunctionCallback( _chara* buffer, _dword size, _dword number, _void* userdata )
{
	NetworkFTPStreamReader* http_stream_reader = (NetworkFTPStreamReader*) userdata;
	EGE_ASSERT( http_stream_reader != _null );

	// Build the command string
	AString cmd_string( buffer, size * number );

	// Try to match the MIME content
	_NETWORK_FTP_CODE code = _FTP_CODE_COMAND_OKAY; AString string;
	if ( NetworkProtocol::ParseFTP( cmd_string, code, string ) )
	{
		// Get the content size
		if ( code == _FTP_CODE_FILE_STATUS )
		{
			http_stream_reader->mMIMEContentSize = string.ToDword( 10 );
			if ( http_stream_reader->mMIMEContentSize == 0 )
			{
				ALOG_ERROR_1( "The FTP '%s' remote file size is invalid", http_stream_reader->mRemoteFileName.Str( ) );
				return 0;
			}
		}
	}

	// Feedback the total bytes
	return size * number;
}

_dword NetworkFTPStreamReader::OnProgressFunctionCallback( _void* userdata, _double dltotal, _double dlnow, _double ultotal, _double ulnow )
{
	NetworkFTPStreamReader* http_stream_reader = (NetworkFTPStreamReader*) userdata;
	EGE_ASSERT( http_stream_reader != _null );

	// No error
	return 0;
}

_ubool NetworkFTPStreamReader::Initialize( AStringPtr remote_filename, AStringPtr username_and_password, _dword port, _dword timeout, _ubool enable_ssl, AStringPtr ssl_key_filename, AStringPtr ssl_cert_filename, AStringPtr ca_cert_filename )
{
	mRemoteFileName			= remote_filename;
	mUserNameAndPassword	= username_and_password;

	// Create stream writer
	mStreamWriter = GetInterfaceFactory( )->CreateMemStreamWriter( 128 KB );
	if ( mStreamWriter.IsNull( ) )
		return _false;

	// Set the URL address and port options
	mURLHandle.SetOption( CURLOPT_URL, remote_filename.Str( ) );
	mURLHandle.SetOption( CURLOPT_PORT, port );
	// Use the user name and password
	mURLHandle.SetOption( CURLOPT_USERPWD, mUserNameAndPassword.Str( ) );
	// Disable to use any signal/alarm handlers
	mURLHandle.SetOption( CURLOPT_NOSIGNAL, _true );
	// Use the location
	mURLHandle.SetOption( CURLOPT_FOLLOWLOCATION, _true );
	// Bind 'CURLOPT_HEADERFUNCTION' callback function
	mURLHandle.SetOption( CURLOPT_HEADERDATA, this );
	mURLHandle.SetOption( CURLOPT_HEADERFUNCTION, OnHeaderFunctionCallback );
	// Bind 'CURLOPT_READFUNCTION' callback function
	mURLHandle.SetOption( CURLOPT_READDATA, this );
	mURLHandle.SetOption( CURLOPT_READFUNCTION, OnReadFunctionCallback );
	// Bind 'CURLOPT_WRITEFUNCTION' callback function
	mURLHandle.SetOption( CURLOPT_WRITEDATA, this );
	mURLHandle.SetOption( CURLOPT_WRITEFUNCTION, OnWriteFunctionCallback );
	// Bind 'CURLOPT_PROGRESSFUNCTION' callback function
	mURLHandle.SetOption( CURLOPT_NOPROGRESS, _false );
	mURLHandle.SetOption( CURLOPT_PROGRESSDATA, this );
	mURLHandle.SetOption( CURLOPT_PROGRESSFUNCTION, OnProgressFunctionCallback );
	// Bind 'CURLOPT_DEBUGFUNCTION' callback function
	mURLHandle.SetOption( CURLOPT_VERBOSE, _true );
	mURLHandle.SetOption( CURLOPT_DEBUGDATA, this );
	mURLHandle.SetOption( CURLOPT_DEBUGFUNCTION, OnDebugFunctionCallback );

	// Enable SSL
	if ( enable_ssl )
	{
		// Set the SSL options
		mURLHandle.SetOption( CURLOPT_SSLKEY, ssl_key_filename.Str( ) );
		mURLHandle.SetOption( CURLOPT_SSLCERT, ssl_cert_filename.Str( ) );

		// Set the CA options
		mURLHandle.SetOption( CURLOPT_CAINFO, ca_cert_filename.Str( ) );

		// Enable verify
		mURLHandle.SetOption( CURLOPT_SSL_VERIFYHOST, 2 );
		mURLHandle.SetOption( CURLOPT_SSL_VERIFYPEER, _true );
	}

	// Set the connection timeout in seconds
	if ( timeout != -1 )
		mURLHandle.SetOption( CURLOPT_FTP_RESPONSE_TIMEOUT, timeout / 1000 );

	// Perform to download file 
	if ( mURLHandle.PerformFTP( ) == _false )
		return _false;

	// Cut the unused memory block
	if ( mStreamWriter->SetCurOffsetAsEndPos( ) == _false )
		return _false;

	// Create stream reader
	mStreamReader = GetInterfaceFactory( )->CreateMemStreamReader( mStreamWriter->GetBuffer( ), mStreamWriter->GetSize( ), _STREAM_SHARE_MODE_READ_ONLY );
	if ( mStreamReader.IsNull( ) )
		return _false;

	return _true;
}

#endif