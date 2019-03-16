//! @file     NetworkTCPStation.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// NetworkTCPStationNotifier Implementation
//----------------------------------------------------------------------------

NetworkTCPStationNotifier::NetworkTCPStationNotifier( )
{
	mProtocolBufProcessor = GetInterfaceFactory( )->CreateProtoBufProcessor( );
}

NetworkTCPStationNotifier::~NetworkTCPStationNotifier( )
{

}

_void NetworkTCPStationNotifier::OnAcceptClient( _dword client_id )
{
	if ( mNotifier.IsValid( ) )
		mNotifier->OnAcceptClient( client_id );
}

_void NetworkTCPStationNotifier::OnLostClient( _dword client_id )
{
	if ( mNotifier.IsValid( ) )
		mNotifier->OnLostClient( client_id );
}

_dword NetworkTCPStationNotifier::OnRecvBuffer( _dword client_id, _dword size, const _byte* buffer, IStreamWriter* stream_writer )
{
	// Parse the message from buffer
	_dword msg_id = 0; _dword msg_size = 0; const _byte* msg_buf = _null;
	_dword read_size = mProtocolBufProcessor->ParseMessageFromBuffer( buffer, size, msg_id, msg_buf, msg_size );
	if ( read_size == 0 )
		return 0;

	// Notify outside
	if ( mNotifier.IsValid( ) )
		return mNotifier->OnRecvBuffer( client_id, size, buffer, stream_writer );

	return read_size;
}

//----------------------------------------------------------------------------
// NetworkTCPStation Implementation
//----------------------------------------------------------------------------

NetworkTCPStation::NetworkTCPStation( )
{
	mRecvBlockSize	= 0;
	mAliveCheckTime = 60 SEC;

	mListenedSocket	= _null;

	mNotifier		= &mInternalNotifier;
}

NetworkTCPStation::~NetworkTCPStation( )
{
	// Close all connections
	Stop( );

	// Close server socket
	Platform::CloseSocket( mListenedSocket );
}

_ubool NetworkTCPStation::IsDeadSocket( _dword tickcount, const SocketInfo& socket_info ) const
{
	// Check the keep alive time
	if ( tickcount - socket_info.mSocket.mLastKeepAliveCheckTime >= mAliveCheckTime )
		return _true;

	// Dead connection ...
	return _false;
}

_dword NetworkTCPStation::OnGetAvailableBytes( const SocketInfo& socket_info )
{
	return mRecvBlockSize;
}

_dword NetworkTCPStation::OnRecv( SocketInfo& socket_info, _byte* buffer, _dword size )
{
	_dword read_size = Platform::ReadSocket( socket_info.mSocket.mSocket, buffer, size );
	if ( read_size != 0 )
		socket_info.mSocket.mLastKeepAliveCheckTime = Platform::GetCurrentTickCount( );

	return read_size;
}

_dword NetworkTCPStation::OnSend( SocketInfo& socket_info, const _byte* buffer, _dword size )
{
	_dword send_size = Platform::WriteSocket( socket_info.mSocket.mSocket, buffer, size );
	if ( send_size != 0 )
		socket_info.mSocket.mLastKeepAliveCheckTime = Platform::GetCurrentTickCount( );

	return send_size;
}

_void NetworkTCPStation::OnClose( SocketInfo& socket_info )
{
	Platform::CloseSocket( socket_info.mSocket.mSocket );
	socket_info.mSocket.mSocket = _null;
}

_void NetworkTCPStation::OnDownload( )
{
	// Get the current tickcount
	_dword cur_tickcount = Platform::GetCurrentTickCount( );

	// Wait for client connect
	_socket client_socket = Platform::AcceptSocket( mListenedSocket );
	if ( client_socket != _null )
	{
		// Establish client connection
		AppendSocket( NetworkTCPSocketInfo( cur_tickcount, client_socket ) );
	}

	// Process client connections
	for ( _dword i = 0; i < mSockets.Number( ); )
	{
		SocketInfo& socket_info = mSockets[i];

		// Check whether it's dead connection
		if ( IsDeadSocket( cur_tickcount, socket_info ) )
		{
			// Seems dead ...
			RemoveSocket( socket_info.mClientID );
			continue;
		}

		// Process socket
		if ( ProcessSocketDownload( socket_info ) == _false )
		{
			// It's disconnected, remove it
			RemoveSocket( socket_info.mClientID );
			continue;
		}

		// Process with the next socket
		i ++;
	}
}

_void NetworkTCPStation::OnUpload( )
{
	// Process client connections
	for ( _dword i = 0; i < mSockets.Number( ); )
	{
		SocketInfo& socket_info = mSockets[i];

		// Process socket
		if ( ProcessSocketUpload( socket_info ) == _false )
		{
			// It's disconnected, remove it
			RemoveSocket( socket_info.mClientID );
			continue;
		}

		// Process with the next socket
		i ++;
	}
}

_ubool NetworkTCPStation::Initialize( _dword port, _dword max_connection_number, _dword recv_block_size )
{
	if ( recv_block_size == 0 )
		return _false;

	mRecvBlockSize = recv_block_size;

	// Create listened socket
	mListenedSocket = Platform::CreateListenedSocket( _DOMAIN_AF_INET, _SOCK_STREAM, _false, port, max_connection_number );
	if ( mListenedSocket == _null )
		return _false;

	// Initialize base core
	WString thread_name = FORMAT_WSTRING_1( L"TCPStation-%d", port );
	if ( BaseClass::Initialize( thread_name ) == _false )
		return _false;

	return _true;
}

_void NetworkTCPStation::SetNotifier( INetworkStationNotifier* notifier )
{
	mInternalNotifier.SetNotifier( notifier );
}

INetworkStationNotifier* NetworkTCPStation::GetNotifier( )
{
	return mInternalNotifier.GetNotifier( );
}