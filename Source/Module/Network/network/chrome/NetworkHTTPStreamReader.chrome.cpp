//! @file     NetworkHTTPStreamReader.chrome.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

#if (_USE_CHROME_SDK == 1)

//----------------------------------------------------------------------------
// NetworkHTTPStreamReader Implementation
//----------------------------------------------------------------------------

NetworkHTTPStreamReader::NetworkHTTPStreamReader( INetworkStreamReaderNotifier* notifier ) : BaseClass( notifier )
{
	mURLLoader		= _null;
	mURLRequestInfo	= _null;
}

NetworkHTTPStreamReader::~NetworkHTTPStreamReader( )
{
	GetPPResourceModule( )->ReleaseResource( mURLLoader );
	GetPPResourceModule( )->ReleaseResource( mURLRequestInfo );
}

_ubool NetworkHTTPStreamReader::GetResponseInfo( )
{
	// Get response info
	PP_ResourcePassRef response_info_res = GetPPResourceModule( )->GetPPBURLLoader( )->GetResponseInfo( mURLLoader );
	if ( response_info_res.IsNull( ) )
		return _false;

	// Get response status code
	PP_VarPassRef status_code = GetPPResourceModule( )->GetPPBURLResponseInfo( )->GetProperty( response_info_res, PP_URLRESPONSEPROPERTY_STATUSCODE );
	if ( status_code->type != PP_VARTYPE_INT32 )
		return _false;

	// Only accept OK or Partial Content.
	_dword code = status_code->value.as_int;
	if ( IsErrorHTTPCode( code ) )
		return _false;

	// Get response headers
	PP_VarPassRef response_headers_var = GetPPResourceModule( )->GetPPBURLResponseInfo( )->GetProperty( response_info_res, PP_URLRESPONSEPROPERTY_HEADERS );
	if ( response_headers_var->type != PP_VARTYPE_STRING )
		return _false;

	GetPPResourceModule( )->VarToAnsi( response_headers_var, mResponseHeaderInfo );

	return _true;
}

_ubool NetworkHTTPStreamReader::GetMIMEContentInfo( )
{
	// Split the response header string
	AStringArray strings;
	StringFormatter::SplitString( mResponseHeaderInfo, strings, "\n", " \t" );

	// Analyze response header info line by line
	for ( _dword i = 0; i < strings.Number( ); i ++ )
	{
		AStringPtr string = strings[i];

		_NETWORK_MIME_KEY_TYPE key; AString value;
		if ( NetworkProtocol::ParseMIME( string, key, value ) == _false )
			continue;

		switch ( key )
		{
			case _MIME_KEY_TYPE_CONTENT_TYPE:
			{
				mMIMEContentType = NetworkProtocol::ParseMIMEContentType( value );
				if ( mMIMEContentType == _MIME_CONTENT_TYPE_UNKNOWN )
				{
					ALOG_ERROR_1( "The '%s' remote file type is unknown, please check the 'Content-Type' MIME protocol of HTTP header", mRemoteFileName.Str( ) );
					return 0;
				}
			}
			break;

			case _MIME_KEY_TYPE_CONTENT_LENGTH:
			{
				mMIMEContentSize = value.ToDword( 10 );
				if ( mMIMEContentSize == 0 )
				{
					ALOG_ERROR_1( "The '%s' remote file size is 0, please check the 'Content-Length' MIME protocol of HTTP header", mRemoteFileName.Str( ) );
					return 0;
				}
			}
			break;

			default:
				break;
		}
	}

	return _true;
}

_ubool NetworkHTTPStreamReader::BuildRequestInfo( )
{
	// Create URL request info
	mURLRequestInfo = GetPPResourceModule( )->GetPPBURLRequestInfo( )->Create( GetPPResourceModule( )->GetPPInstance( ) );
	if ( mURLRequestInfo == _null )
		return _false;

	// Initialize URL request info
	GetPPResourceModule( )->GetPPBURLRequestInfo( )->SetProperty( mURLRequestInfo, PP_URLREQUESTPROPERTY_URL, GetPPResourceModule( )->AnsiToVar( mRemoteFileName ) );
	GetPPResourceModule( )->GetPPBURLRequestInfo( )->SetProperty( mURLRequestInfo, PP_URLREQUESTPROPERTY_METHOD, GetPPResourceModule( )->Utf8ToVar( "GET" ) );
	GetPPResourceModule( )->GetPPBURLRequestInfo( )->SetProperty( mURLRequestInfo, PP_URLREQUESTPROPERTY_RECORDDOWNLOADPROGRESS, GetPPResourceModule( )->BoolToVar( _true ) );

	return _true;
}

_ubool NetworkHTTPStreamReader::BuildStreamsInfo( )
{
	// Get the download progression to get the total size in bytes
	_large bytes_received = 0, total_bytes_to_be_received = 0;
	GetPPResourceModule( )->GetPPBURLLoader( )->GetDownloadProgress( mURLLoader, &bytes_received, &total_bytes_to_be_received );
	if ( total_bytes_to_be_received == -1 || total_bytes_to_be_received == 0 )
		return _false;

	// Create stream writer
	mStreamWriter = GetInterfaceFactory( )->CreateMemStreamWriter( (_dword)total_bytes_to_be_received );
	if ( mStreamWriter.IsNull( ) )
		return _false;

	// Read the remote buffer data block by block
	_dword cur_read_bytes = 0, total_size = (_dword)total_bytes_to_be_received;
	while ( cur_read_bytes < total_size )
	{
		_byte* buffer	= (_byte*)mStreamWriter->GetBuffer( ) + cur_read_bytes;
		_dword size		= total_size - cur_read_bytes;

		_int read_bytes = GetPPResourceModule( )->GetPPBURLLoader( )->ReadResponseBody( mURLLoader, (_void*)buffer, size, PP_BlockUntilComplete( ) );
		if ( read_bytes < 0 )
			return _false;

		cur_read_bytes += read_bytes;
	}

	// Create stream reader
	mStreamReader = GetInterfaceFactory( )->CreateMemStreamReader( mStreamWriter->GetBuffer( ), mStreamWriter->GetSize( ), _STREAM_SHARE_MODE_READ_ONLY );
	if ( mStreamReader.IsNull( ) )
		return _false;

	return _true;
}

_ubool NetworkHTTPStreamReader::OpenURL( )
{
	// Create URL loader
	mURLLoader = GetPPResourceModule( )->GetPPBURLLoader( )->Create( GetPPResourceModule( )->GetPPInstance( ) );
	if ( mURLLoader == _null )
		return _false;

	// Start to load URL
	if ( GetPPResourceModule( )->GetPPBURLLoader( )->Open( mURLLoader, mURLRequestInfo, PP_BlockUntilComplete( ) ) != PP_OK )
		return _false;

	return _true;
}

_ubool NetworkHTTPStreamReader::Initialize( WStringPtr remote_filename )
{
	// Save the remote file name
	mRemoteFileName.FromString( remote_filename );

	// Build request info
	if ( BuildRequestInfo( ) == _false )
		return _false;

	// Open URL 
	if ( OpenURL( ) == _false )
		return _false;

	// Get response info
	if ( GetResponseInfo( ) == _false )
		return _false;

	// Build streams info
	if ( BuildStreamsInfo( ) == _false )
		return _false;

	// Get MIME content info
	if ( GetMIMEContentInfo( ) == _false )
		return _false;

	return _true;
}

_float NetworkHTTPStreamReader::GetDownloadSpeed( )
{
	return 0.0f;
}

#endif