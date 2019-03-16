//! @file     NetworkTCPConnection.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// NetworkTCPConnection Helpful Functions Implementation
//----------------------------------------------------------------------------

static _ubool OnIsBreakConnectingProcCallback( _dword elapse, _void* userdata )
{
	NetworkTCPConnection* connection = (NetworkTCPConnection*) userdata;
	EGE_ASSERT( connection != _null );

	if ( GetNetworkModule( )->IsPowerOff( ) )
		return _true;

	_dword timeout = connection->GetConnectTimeout( );
	if ( timeout != -1 && elapse >= timeout )
		return _true;

	// Let it go ~
	return _false;
}

//----------------------------------------------------------------------------
// NetworkTCPConnection Implementation
//----------------------------------------------------------------------------

NetworkTCPConnection::NetworkTCPConnection( INetworkConnectionThread* connection_thread ) : BaseClass( connection_thread )
{
	mSocket = _null;
}

NetworkTCPConnection::~NetworkTCPConnection( )
{
	// Close the socket
	if ( mSocket != _null )
		Platform::CloseSocket( mSocket );
}

_void NetworkTCPConnection::AddStableOperations( )
{
	mRecvActionRecorder->AddAction( IActionRecordPassRef( new NetworkRecvOperation( this ) ).GetPtr( ) );
}

_ubool NetworkTCPConnection::OnConnect( )
{
	WLOG_TRACE_1( L"Starting connect to (%s) server ...", mRemoteAddress.ToStringW( _true ).Str( ) );

	// Clear recv actions
	mRecvActionRecorder->ClearAllActions( _true );

	// Clear processing buffers of sending
	for ( _dword i = 0; i < mSendActionRecorder->GetActionsNumber( ); i ++ )
	{
		INetworkOperation* network_operation = (INetworkOperation*) mSendActionRecorder->GetActionByIndex( i );
		EGE_ASSERT( network_operation != _null );

		network_operation->RemoveProcessingBuffers( );
	}

	// Delete socket
	if ( mSocket != _null )
		Platform::CloseSocket( mSocket );

	// Get the IP address without port number
	AString ip_address = mRemoteAddress.ToStringA( _false );

	// Get the family type
	_DOMAIN_FAMILY_TYPE family_type = Platform::GetFamilyType( mRemoteAddress.mPort, ip_address.Str( ) );

	// Create socket
	mSocket = Platform::CreateSocket( family_type, _SOCK_STREAM, _true );
	if ( mSocket == _null )
		return _false;

	// Set the timeout
	SetConnectTimeout( mConnectTimeout );

	// Start to connect
	if ( Platform::ConnectSocket( mSocket, ip_address.Str( ), mRemoteAddress.mPort, OnIsBreakConnectingProcCallback, this ) == _false )
	{
		WLOG_TRACE_1( L"Connect to (%s) server failed", mRemoteAddress.ToStringW( _true ).Str( ) );
		return _false;
	}

	// Add stable operations
	AddStableOperations( );

	WLOG_TRACE_1( L"Connect to (%s) server OK", mRemoteAddress.ToStringW( _true ).Str( ) );
	return _true;
}

_dword NetworkTCPConnection::OnRecv( _byte* buffer, _dword size )
{
	_dword read_bytes = Platform::ReadSocket( mSocket, buffer, size );
	if ( read_bytes != -1 )
		GetNetworkModule( )->UpdateTotalDownloadBytes( read_bytes );

	return read_bytes;
}

_dword NetworkTCPConnection::OnSend( const _byte* buffer, _dword size )
{
	_dword send_bytes = Platform::WriteSocket( mSocket, (const _void*) buffer, size );
	if ( send_bytes != -1 )
		GetNetworkModule( )->UpdateTotalDownloadBytes( send_bytes );

	return send_bytes;
}

_ubool NetworkTCPConnection::Initialize( const Address& remote_address )
{
	// Initialize the local address
	if ( InitLocalAddress( Address::_TYPE_TCP ) == _false )
		return _false;

	// Initialize the remote address
	if ( InitRemoteAddress( remote_address ) == _false )
		return _false;

	// Process connection operations
	mConnectionThread->ProcessConnectionOperations( this );

	return _true;
}

_void NetworkTCPConnection::SetConnectTimeout( _dword timeout )
{
	BaseClass::SetConnectTimeout( timeout );

	// Set recv/send time out
	if ( mSocket != _null )
	{
		Platform::SetSocketRecvTimeOutOption( mSocket, timeout );
		Platform::SetSocketSendTimeOutOption( mSocket, timeout );
	}
}

_NETWORK_CONNECTION_TYPE NetworkTCPConnection::GetType( ) const
{
	return _NETWORK_CONNECTION_TCP;
}

_void NetworkTCPConnection::Disconnect( )
{
	// Close the socket
	if ( mSocket != _null )
	{
		Platform::CloseSocket( mSocket );
		mSocket = _null;
	}

	BaseClass::Disconnect( );
}

_void NetworkTCPConnection::Stop( )
{
	// Remove all actions
	BaseClass::Stop( );
}
