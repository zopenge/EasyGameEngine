//! @file     NetworkBluetoothConnection.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// NetworkBluetoothConnection Implementation
//----------------------------------------------------------------------------

NetworkBluetoothConnection::NetworkBluetoothConnection( INetworkConnectionThread* connection_thread ) : BaseClass( connection_thread )
{
}

NetworkBluetoothConnection::~NetworkBluetoothConnection( )
{
}

_ubool NetworkBluetoothConnection::OnConnect( )
{
	mSocket->Connect( );

	return _true;
}

_dword NetworkBluetoothConnection::OnRecv( _byte* buffer, _dword size )
{
	_dword read_size = Math::Min< _dword >( size, mSocket->GetAvailableBytes( ) );
	return mSocket->Recv( buffer, read_size );
}

_dword NetworkBluetoothConnection::OnSend( const _byte* buffer, _dword size )
{
	_dword send_size = mSocket->Send( buffer, size );
	return send_size;
}

_ubool NetworkBluetoothConnection::Initialize( AStringPtr address, const UID128& uid )
{
	IBluetoothDeviceRef device = GetBluetoothAdapter( )->GetRemoteDevice( address );
	if ( device.IsNull( ) )
		return _false;

	mSocket = device->CreateClientSocket( uid );
	if ( mSocket.IsNull( ) )
		return _false;

	// Add the receive operation 
	mRecvActionRecorder->AddAction( IActionRecordPassRef( new NetworkRecvOperation( this ) ).GetPtr( ) );

	return _true;
}

_NETWORK_CONNECTION_TYPE NetworkBluetoothConnection::GetType( ) const
{
	return _NETWORK_CONNECTION_BLUETOOTH;
}

_void NetworkBluetoothConnection::Stop( )
{
	// Remove all actions
	BaseClass::Stop( );
}

_ubool NetworkBluetoothConnection::Send( _dword size, const _byte* buffer )
{
	if ( BaseClass::Send( size, buffer ) == _false )
		return _false;

	return _true;
}

_ubool NetworkBluetoothConnection::SendInstant( _dword size, const _byte* buffer )
{
	if ( BaseClass::SendInstant( size, buffer ) == _false )
		return _false;

	return _true;
}