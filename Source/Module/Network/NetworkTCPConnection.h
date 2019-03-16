//! @file     NetworkTCPConnection.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkTCPConnection
//----------------------------------------------------------------------------

class NetworkTCPConnection : public TNetworkConnection< INetworkTCPConnection >
{
private:
	typedef TNetworkConnection< INetworkTCPConnection > BaseClass;

private:
	//!	The default wait time in milliseconds
	enum { _DEFAULT_WAIT_TIME = 2 SEC };

private:
	//!	The socket handle
	_socket mSocket;

private:
	//!	Add the stable operations.
	_void AddStableOperations( );

// TNetworkConnection Interface
private:
	virtual _ubool	OnConnect( ) override;
	virtual _dword	OnRecv( _byte* buffer, _dword size ) override;
	virtual _dword	OnSend( const _byte* buffer, _dword size ) override;

public:
	NetworkTCPConnection( INetworkConnectionThread* connection_thread );
	virtual ~NetworkTCPConnection( );

public:
	//!	Initialize.
	_ubool Initialize( const Address& remote_address );

// ITimeoutObject Interface
public:
	virtual _void						SetConnectTimeout( _dword timeout ) override;

// INetworkConnection Interface
public:
	virtual _NETWORK_CONNECTION_TYPE	GetType( ) const override;

	virtual _void						Disconnect( ) override;

	virtual _void						Stop( ) override;
};

//----------------------------------------------------------------------------
// NetworkTCPConnection Implementation
//----------------------------------------------------------------------------

}