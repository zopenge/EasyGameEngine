//! @file     NetworkFTPConnection.chrome.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkFTPConnection
//----------------------------------------------------------------------------

class NetworkFTPConnection : public TNetworkConnection< INetworkFTPConnection >
{
private:
	typedef TNetworkConnection< INetworkFTPConnection > BaseClass;

public:
	NetworkFTPConnection( INetworkConnectionThread* connection_thread );
	virtual ~NetworkFTPConnection( );

public:
	//!	Initialize by remote address.
	_ubool Initialize( const Address& remote_address );
	//!	Initialize by URL address.
	_ubool Initialize( WStringPtr url_address );

// INetworkConnection Interface
public:
	virtual _NETWORK_CONNECTION_TYPE			GetType( ) const override;

	virtual _void								Stop( ) override;

	virtual _ubool								IsRemoteFileExist( WStringPtr filename ) override;
	virtual INetworkStreamReaderPassRef			OpenRemoteFile( WStringPtr filename, INetworkStreamReaderNotifier* notifier = _null ) override;

	virtual _void								ProcessDelayConnectOperations( ) override;
	virtual _void								ProcessDelaySendOperations( ) override;
	virtual _void								ProcessDelayRecvOperations( ) override;

// INetworkFTPConnection Interface
public:
	virtual _void								SetFTPNotifier( INetworkFTPConnectionNotifier* notifier ) override;
	virtual INetworkFTPConnectionNotifierRef	GetFTPNotifier( ) override;

	virtual _void								SetUserName( AStringPtr username ) override;
	virtual _void								SetPassword( AStringPtr password ) override;

	virtual _ubool								UploadFile( WStringPtr local_filename, WStringPtr remote_filename, const QwordParameters4& parameters ) override;
};

//----------------------------------------------------------------------------
// NetworkFTPConnection Implementation
//----------------------------------------------------------------------------

}