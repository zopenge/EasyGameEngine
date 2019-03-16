//! @file     NetworkTCPStation.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkTCPSocketInfo
//----------------------------------------------------------------------------

struct NetworkTCPSocketInfo
{
	//!	The last keep alive check time in milliseconds
	_dword	mLastKeepAliveCheckTime;

	//!	The TCP socket
	_socket	mSocket;

	NetworkTCPSocketInfo( )
	{
		mLastKeepAliveCheckTime	= 0;

		mSocket					= _null;
	}
	NetworkTCPSocketInfo( _dword last_check_time, _socket handle )
	{
		mLastKeepAliveCheckTime	= last_check_time;

		mSocket					= handle;
	}
};

//----------------------------------------------------------------------------
// NetworkTCPStationNotifier
//----------------------------------------------------------------------------

class NetworkTCPStationNotifier : public TObject< INetworkStationNotifier >
{
private:
	//!	The protocol buffer processor
	IProtoBufProcessorRef		mProtocolBufProcessor;

	//!	The notifier.
	INetworkStationNotifierRef	mNotifier;

public:
	NetworkTCPStationNotifier( );
	virtual ~NetworkTCPStationNotifier( );

public:
	EGE_GET_SET_ACCESSOR( INetworkStationNotifier*, Notifier )

// INetworkStationNotifier Interface
public:
	virtual _void	OnAcceptClient( _dword client_id ) override;
	virtual _void	OnLostClient( _dword client_id ) override;

	virtual _dword	OnRecvBuffer( _dword client_id, _dword size, const _byte* buffer, IStreamWriter* stream_writer ) override;
};

//----------------------------------------------------------------------------
// NetworkTCPStation
//----------------------------------------------------------------------------

class NetworkTCPStation : public TNetworkStation< INetworkStation, NetworkTCPSocketInfo >
{
private:
	typedef TNetworkStation< INetworkStation, NetworkTCPSocketInfo > BaseClass;

private:
	//!	The recv block size in bytes
	_dword						mRecvBlockSize;
	//!	The alive socket connection check alive time in milliseconds
	_dword						mAliveCheckTime;

	//!	The TCP listened socket
	_socket						mListenedSocket;

	//!	The station notifier, we handle some internal packet first, so we need to wrap it
	NetworkTCPStationNotifier	mInternalNotifier;

private:
	//!	Check whether it's dead socket or not.
	_ubool IsDeadSocket( _dword tickcount, const SocketInfo& socket_info ) const;

// TNetworkStation Interface
private:
	virtual _dword	OnGetAvailableBytes( const SocketInfo& socket_info ) override;
	virtual _dword	OnRecv( SocketInfo& socket_info, _byte* buffer, _dword size ) override;
	virtual _dword	OnSend( SocketInfo& socket_info, const _byte* buffer, _dword size ) override;
	virtual _void	OnClose( SocketInfo& socket_info ) override;

	virtual _void	OnDownload( ) override;
	virtual _void	OnUpload( ) override;

public:
	NetworkTCPStation( );
	virtual ~NetworkTCPStation( );

public:
	//!	Initialize.
	_ubool Initialize( _dword port, _dword max_connection_number, _dword recv_block_size );

// INetworkStation Interface
public:
	virtual _void						SetNotifier( INetworkStationNotifier* notifier ) override;
	virtual INetworkStationNotifier*	GetNotifier( ) override;
};

//----------------------------------------------------------------------------
// NetworkTCPStation Implementation
//----------------------------------------------------------------------------

}