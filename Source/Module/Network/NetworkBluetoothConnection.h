//! @file     NetworkBluetoothConnection.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkBluetoothConnection
//----------------------------------------------------------------------------

class NetworkBluetoothConnection : public TNetworkConnection< INetworkBluetoothConnection >
{
private:
	typedef TNetworkConnection< INetworkBluetoothConnection > BaseClass;

private:
	IBluetoothSocketRef	mSocket;

// TNetworkConnection Interface
private:
	virtual _ubool	OnConnect( ) override;
	virtual _dword	OnRecv( _byte* buffer, _dword size ) override;
	virtual _dword	OnSend( const _byte* buffer, _dword size ) override;

public:
	NetworkBluetoothConnection( INetworkConnectionThread* connection_thread );
	virtual ~NetworkBluetoothConnection( );

public:
	//!	Initialize.
	_ubool Initialize( AStringPtr address, const UID128& uid );

// INetworkConnection Interface
public:
	virtual _NETWORK_CONNECTION_TYPE	GetType( ) const override;

	virtual _void						Stop( ) override;

	virtual _ubool						Send( _dword size, const _byte* buffer ) override;
	virtual _ubool						SendInstant( _dword size, const _byte* buffer ) override;
};

//----------------------------------------------------------------------------
// NetworkBluetoothConnection Implementation
//----------------------------------------------------------------------------

}