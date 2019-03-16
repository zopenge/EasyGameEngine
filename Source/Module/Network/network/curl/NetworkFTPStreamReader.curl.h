//! @file     NetworkFTPStreamReader.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkFTPStreamReader
//----------------------------------------------------------------------------

class NetworkFTPStreamReader : public TNetworkStreamReader< INetworkStreamReader >
{
private:
	typedef TNetworkStreamReader< INetworkStreamReader > BaseClass;

private:
	//!	The user name and password string for cURL
	AString		mUserNameAndPassword;

	//!	The remote file handle
	_curlHandle	mURLHandle;

private:
	//!	The CURLOPT_DEBUGFUNCTION callback function.
	static _dword OnDebugFunctionCallback( CURL* urlhandle, curl_infotype type, _chara* buffer, _dword size, _void* userdata );
	//!	The CURLOPT_WRITEFUNCTION callback function.
	static _dword OnWriteFunctionCallback( _chara* buffer, _dword size, _dword number, _void* userdata );
	//!	The CURLOPT_READFUNCTION callback function.
	static _dword OnReadFunctionCallback( _chara* buffer, _dword size, _dword number, _void* userdata );
	//!	The CURLOPT_HEADERFUNCTION callback function.
	static _dword OnHeaderFunctionCallback( _chara* buffer, _dword size, _dword number, _void* userdata );
	//!	The CURLOPT_PROGRESSFUNCTION callback function.
	static _dword OnProgressFunctionCallback( _void* userdata, _double dltotal, _double dlnow, _double ultotal, _double ulnow );

public:
	NetworkFTPStreamReader( INetworkStreamReaderNotifier* notifier );
	virtual ~NetworkFTPStreamReader( );

public:
	//!	Initialize.
	_ubool Initialize( AStringPtr remote_filename, AStringPtr username_and_password, _dword port, _dword timeout, _ubool enable_ssl, AStringPtr ssl_key_filename, AStringPtr ssl_cert_filename, AStringPtr ca_cert_filename );

// INetworkStreamReader Interface
public:
};

//----------------------------------------------------------------------------
// NetworkFTPStreamReader Implementation
//----------------------------------------------------------------------------

}