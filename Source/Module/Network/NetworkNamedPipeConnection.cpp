//! @file     NetworkNamedPipeConnection.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// NetworkNamedPipeConnection Implementation
//----------------------------------------------------------------------------

NetworkNamedPipeConnection::NetworkNamedPipeConnection( INetworkConnectionThread* connection_thread ) : BaseClass( connection_thread )
{
}

NetworkNamedPipeConnection::~NetworkNamedPipeConnection( )
{
}

_ubool NetworkNamedPipeConnection::OnConnect( )
{
	if ( mPipe.CreateClient( mPipeName, GetConnectTimeout( ) ) == _false )
		return _false;

	return _true;
}

_dword NetworkNamedPipeConnection::OnRecv( _byte* buffer, _dword size )
{
	EGE_ASSERT( buffer != _null );
	EGE_ASSERT( size != 0 );

	_dword available_size = mPipe.GetTotalAvailableSize( );
	if ( available_size == -1 )
		return -1;

	_dword read_size = Math::Min< _dword >( size, available_size );
	if ( read_size == 0 )
		return 0; // Wait for data receive

	if ( mPipe.Read( buffer, read_size ) == _false )
		return -1;

	return read_size;
}

_dword NetworkNamedPipeConnection::OnSend( const _byte* buffer, _dword size )
{
	if ( mPipe.Write( buffer, size ) == _false )
		return -1;

	return size;
}

_ubool NetworkNamedPipeConnection::Initialize( WStringPtr pipename )
{
	mPipeName = pipename;

	// Add the receive operation 
	mRecvActionRecorder->AddAction( IActionRecordPassRef( new NetworkRecvOperation( this ) ).GetPtr( ) );

	return _true;
}

_void NetworkNamedPipeConnection::Disconnect( )
{
	mPipe.Disconnect( );

	BaseClass::Disconnect( );
}

_NETWORK_CONNECTION_TYPE NetworkNamedPipeConnection::GetType( ) const
{
	return _NETWORK_CONNECTION_NAMED_PIPE;
}

_void NetworkNamedPipeConnection::Stop( )
{
	// Remove all actions
	BaseClass::Stop( );

	// Add the receive operation 
	mRecvActionRecorder->AddAction( IActionRecordPassRef( new NetworkRecvOperation( this ) ).GetPtr( ) );
}