//! @file     NetworkBluetoothStation.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// NetworkBluetoothStation Implementation
//----------------------------------------------------------------------------

NetworkBluetoothStation::NetworkBluetoothStation( )
{
	mServerUID = UID::cNullUID128;
}

NetworkBluetoothStation::~NetworkBluetoothStation( )
{
	// Close all connections
	Stop( );
}

_dword NetworkBluetoothStation::OnGetAvailableBytes( const SocketInfo& socket_info )
{
	return socket_info.mSocket->GetAvailableBytes( );
}

_dword NetworkBluetoothStation::OnRecv( SocketInfo& socket_info, _byte* buffer, _dword size )
{
	_dword read_size = socket_info.mSocket->Recv( buffer, size );
	return read_size;
}

_dword NetworkBluetoothStation::OnSend( SocketInfo& socket_info, const _byte* buffer, _dword size )
{
	_dword send_size = socket_info.mSocket->Send( buffer, size );
	return send_size;
}

_void NetworkBluetoothStation::OnClose( SocketInfo& socket_info )
{
	socket_info.mSocket.Clear( );
}

_void NetworkBluetoothStation::OnDownload( )
{
	const _dword accept_timeout = 1;

	// Wait for client connect
	IBluetoothSocketRef client = mServerSocket->Accept( accept_timeout );
	if ( client.IsValid( ) )
	{
		// Establish client connection
		AppendSocket( client );
	}

	// Process client connections
	for ( _dword i = 0; i < mSockets.Number( ); i ++ )
	{
		SocketInfo& socket_info = mSockets[i];

		// Process socket
		if ( ProcessSocketDownload( socket_info ) == _false )
		{
			// It's disconnected, remove it
			mSockets.RemoveByIndex( i -- );
			continue;
		}
	}
}

_void NetworkBluetoothStation::OnUpload( )
{

}

_ubool NetworkBluetoothStation::Initialize( const UID128& uid )
{
	// Save the server UUID
	mServerUID = uid;

	// Create server socket
	mServerSocket = GetBluetoothAdapter( )->CreateServerSocket( uid );
	if ( mServerSocket.IsNull( ) )
		return _false;

	// Get the server UID
	WString server_uid = mServerUID.ToStringW( _true );

	// Initialize base core
	WString thread_name = FORMAT_WSTRING_1( L"Bluetooth-%s", server_uid.Str( ) );
	if ( BaseClass::Initialize( thread_name ) == _false )
		return _false;

	return _true;
}