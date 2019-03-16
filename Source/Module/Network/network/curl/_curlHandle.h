//! @file     _curlHandle.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _curlHandle
//----------------------------------------------------------------------------

class _curlHandle
{
private:
	//!	The connect timeout in milliseconds
	_dword		mConnectTimeout;
	//!	The transfer timeout in milliseconds
	_dword		mTransferTimeout;

	//!	The cURL handle
	CURL*		mSessionHandle;

	//!	The last response code ID
	_dword		mLastResponseID;
	//!	The last error ID
	CURLcode	mLastErrorID;
	//!	The last error string buffer
	_chara		mLastErrorString[ CURL_ERROR_SIZE ];

private:
	//!	Perform the cURL operation.
	_ubool Perform( );

public:
	_curlHandle( );
	~_curlHandle( );

public:
	//!	Accessors.
	EGE_GET_ACCESSOR_CONST( _dword, ConnectTimeout )
	EGE_GET_ACCESSOR_CONST( _dword, TransferTimeout )
	EGE_GET_ACCESSOR( CURL*, SessionHandle )
	EGE_GET_SET_ACCESSOR_CONST( CURLcode, LastErrorID )
	EGE_GET_ACCESSOR( const _chara*, LastErrorString )

public:
	//!	Get the cURL handle.
	operator CURL* ( ) const
		{ return mSessionHandle; }

public:
	//!	Set option.
	template< typename Type >
	_void SetOption( CURLoption option, Type value );
	//!	Get option.
	template< typename Type >
	_ubool GetOption( CURLINFO option, Type& value ) const;

public:
	//!	Abort.
	_void Abort( );

	//!	Set time out.
	_void SetConnectTimeout( _dword timeout );
	_void SetTransferTimeout( _dword timeout );

	//!	Set URL.
	_void SetURL( AStringPtr url );

	//!	Set the range option.
	_void SetRangeOption( _dword start_bytes, _dword size );
	//!	Set the proxy server.
	_void SetProxyServer( WStringPtr server_name, _dword port );

	//! Set the HTTP header
	_void SetHTTPHeader( const AStringArray& header_list );

	//!	Set the SSL options.
	_void SetSSLOptions( AStringPtr ssl_key_file_name, AStringPtr ssl_cert_file_name, AStringPtr ca_cert_file_name );

	//!	Perform the HTTP/FTP operation.
	_ubool PerformHTTP( );
	_ubool PerformFTP( );
};

//----------------------------------------------------------------------------
// _curlHandle Implementation
//----------------------------------------------------------------------------

template< typename Type >
_void _curlHandle::SetOption( CURLoption option, Type value )
{
	EGE_ASSERT( mSessionHandle != _null );
	::curl_easy_setopt( mSessionHandle, option, value );
}

template< typename Type >
_ubool _curlHandle::GetOption( CURLINFO option, Type& value ) const
{
	EGE_ASSERT( mSessionHandle != _null );

	// The cURL options document : http://curl.haxx.se/libcurl/c/curl_easy_getinfo.html
	CURLcode err_id = ::curl_easy_getinfo( mSessionHandle, option, &value );
	if ( err_id != CURLE_OK )
	{
		ALOG_ERROR_2( "Get cURL options failed, err:%d(%s)", (_dword)err_id, ::curl_easy_strerror( err_id ) );
		return _false;
	}

	return _true;
}

}