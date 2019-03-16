//! @file     NetworkFTPStreamReader.chrome.h
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
	AString	mUserNameAndPassword;

private:

public:
	NetworkFTPStreamReader( INetworkStreamReaderNotifier* notifier );
	virtual ~NetworkFTPStreamReader( );

public:
	//!	Initialize.
	_ubool Initialize( AStringPtr remote_filename, AStringPtr username_and_password, _dword port, _dword timeout, _ubool enable_ssl, AStringPtr ssl_key_filename, AStringPtr ssl_cert_filename, AStringPtr ca_cert_filename );

// INetworkStreamReader Interface
public:
	virtual _float	GetDownloadSpeed( ) override;
};

//----------------------------------------------------------------------------
// NetworkFTPStreamReader Implementation
//----------------------------------------------------------------------------

}