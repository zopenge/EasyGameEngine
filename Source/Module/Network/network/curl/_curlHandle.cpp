//! @file     _curlHandle.cpp
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#include "EGENetwork.h"

#if (_USE_CRUL_SDK == 1)

//----------------------------------------------------------------------------
// _curlHandle Implementation
//----------------------------------------------------------------------------

_curlHandle::_curlHandle( ) : mLastResponseID( 0 ), mLastErrorID( CURLE_OK )
{
	mConnectTimeout		= -1;
	mTransferTimeout	= -1;

	// Initialize cURL handle
	mSessionHandle = ::curl_easy_init( );
	EGE_ASSERT( mSessionHandle != _null );

	// Bind the error buffer string
	mLastErrorString[0] = 0;
	SetOption( CURLOPT_ERRORBUFFER, mLastErrorString );
}

_curlHandle::~_curlHandle( )
{
	// Cleanup the cURL handle
	EGE_ASSERT( mSessionHandle != _null );
	::curl_easy_cleanup( mSessionHandle );
}

_ubool _curlHandle::Perform( )
{
	EGE_ASSERT( mSessionHandle != _null );

	// Clear the error info
	mLastResponseID		= 0;
	mLastErrorID		= CURLE_OK;
	mLastErrorString[0]	= 0;

	// Perform the URL handle options
	mLastErrorID = ::curl_easy_perform( mSessionHandle );
	if ( mLastErrorID != CURLE_OK )
	{
		ALOG_ERROR_2( "Perform cURL operation failed, err:%d(%s)", (_dword) mLastErrorID, ::curl_easy_strerror( mLastErrorID ) );
		return _false;
	}

	// Get the response code
	if ( GetOption( CURLINFO_RESPONSE_CODE, mLastResponseID ) == _false )
		return _false;

	return _true;
}

_void _curlHandle::Abort( )
{
	SetOption( CURLOPT_CONNECTTIMEOUT_MS, 1 );
	SetOption( CURLOPT_TIMEOUT_MS, 1 );
}

_void _curlHandle::SetURL( AStringPtr url )
{
	SetOption( CURLOPT_URL, url.Str( ) );
}

_void _curlHandle::SetConnectTimeout( _dword timeout )
{
	mConnectTimeout = timeout;

	SetOption( CURLOPT_CONNECTTIMEOUT_MS, mConnectTimeout );
}

_void _curlHandle::SetTransferTimeout( _dword timeout )
{
	mTransferTimeout = timeout;

	SetOption( CURLOPT_TIMEOUT_MS, mTransferTimeout );
}

_void _curlHandle::SetRangeOption( _dword start_bytes, _dword size )
{
	EGE_ASSERT( size != 0 );

	// Build the HTTP range header
	_chara http_range_header[1024];
	if ( size == -1 )
		Platform::FormatStringBuffer( http_range_header, 1024, "%d-", start_bytes );
	else
		Platform::FormatStringBuffer( http_range_header, 1024, "%d-%d", start_bytes, size + start_bytes - 1 );

	// Set the HTTP range option
	SetOption( CURLOPT_RANGE, http_range_header );
}

_void _curlHandle::SetProxyServer( WStringPtr server_name, _dword port )
{
	// Convert server name to ANSI
	_chara server_name_ansi[1024];
	Platform::Utf16ToAnsi( server_name_ansi, 1024, server_name.Str( ) );

	// Set the proxy server options
	SetOption( CURLOPT_PROXY, server_name_ansi );
	SetOption( CURLOPT_PROXYPORT, port );
}

_void _curlHandle::SetHTTPHeader( const AStringArray& header_list )
{
	if ( header_list.Number( ) == 0 )
		return;

	// Build the data chunk list for HTTP header
	_curlDataList curl_chunk_list;
	curl_chunk_list.Append( header_list );

	SetOption( CURLOPT_HEADER, _true );
	SetOption( CURLOPT_HTTPHEADER, (curl_slist*)curl_chunk_list );
}

_void _curlHandle::SetSSLOptions( AStringPtr ssl_key_file_name, AStringPtr ssl_cert_file_name, AStringPtr ca_cert_file_name )
{
	_ubool has_cert_files = _false;

	// Set the SSL options
	if ( ssl_key_file_name.IsEmpty( ) == _false )
	{
		has_cert_files = _true;
		SetOption( CURLOPT_SSLKEY, ssl_key_file_name.Str( ) );
	}
	if ( ssl_cert_file_name.IsEmpty( ) == _false )
	{
		has_cert_files = _true;
		SetOption( CURLOPT_SSLCERT, ssl_cert_file_name.Str( ) );
	}

	// Set the CA options
	if ( ca_cert_file_name.IsEmpty( ) == _false )
	{
		has_cert_files = _true;
		SetOption( CURLOPT_CAINFO, ca_cert_file_name.Str( ) );
	}

	// Enable SSL with cert files
	if ( has_cert_files )
	{
		// http://curl.haxx.se/libcurl/c/curl_easy_setopt.html#CURLOPTSSLVERIFYHOST
		SetOption( CURLOPT_SSL_VERIFYHOST, 2 );
		SetOption( CURLOPT_SSL_VERIFYPEER, _true );
	}
	// Disable SSL
	else
	{
		SetOption( CURLOPT_SSL_VERIFYHOST, 0 );
		SetOption( CURLOPT_SSL_VERIFYPEER, _false );
	}
}

_ubool _curlHandle::PerformHTTP( )
{
	// Perform operation
	if ( Perform( ) == _false )
		return _false;

	// Check the response code
	if ( IsErrorHTTPCode( mLastResponseID ) )
	{
		ALOG_ERROR_1( "Perform HTTP operation failed, ret code:%d", mLastResponseID );
		return _false;
	}

	return _true;
}

_ubool _curlHandle::PerformFTP( )
{
	// Perform operation
	if ( Perform( ) == _false )
		return _false;

	// Check the response code
	if ( IsFileClosedFTPCode( mLastResponseID ) == _false )
	{
		ALOG_ERROR_1( "Perform FTP operation failed, ret code:%d", mLastResponseID );
		return _false;
	}

	return _true;
}

#endif