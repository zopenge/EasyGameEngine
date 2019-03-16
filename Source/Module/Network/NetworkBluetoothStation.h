//! @file     NetworkBluetoothStation.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkBluetoothStation
//----------------------------------------------------------------------------

class NetworkBluetoothStation : public TNetworkStation< INetworkStation, IBluetoothSocketRef >
{
private:
	typedef TNetworkStation< INetworkStation, IBluetoothSocketRef > BaseClass;

private:
	//!	The server UID
	UID128						mServerUID;
	//!	The server socket
	IBluetoothServerSocketRef	mServerSocket;

// TNetworkStation Interface
private:
	virtual _dword	OnGetAvailableBytes( const SocketInfo& socket_info ) override;
	virtual _dword	OnRecv( SocketInfo& socket_info, _byte* buffer, _dword size ) override;
	virtual _dword	OnSend( SocketInfo& socket_info, const _byte* buffer, _dword size ) override;
	virtual _void	OnClose( SocketInfo& socket_info ) override;

	virtual _void	OnDownload( ) override;
	virtual _void	OnUpload( ) override;

public:
	NetworkBluetoothStation( );
	virtual ~NetworkBluetoothStation( );

public:
	//!	Initialize.
	_ubool Initialize( const UID128& uid );
};

//----------------------------------------------------------------------------
// NetworkBluetoothStation Implementation
//----------------------------------------------------------------------------

}