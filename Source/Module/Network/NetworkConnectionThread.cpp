//! @file     NetworkConnectionThread.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// NetworkConnectionThread Implementation
//----------------------------------------------------------------------------

NetworkConnectionThread::NetworkConnectionThread( _dword flags ) : mFlags( flags )
{
}

NetworkConnectionThread::~NetworkConnectionThread( )
{
	Finalize( );
}

_dword NetworkConnectionThread::OnUpdateConnectionCallback( const QwordParameters2& parameters )
{
	INetworkConnection* connection = (INetworkConnection*) parameters[0];
	EGE_ASSERT( connection != _null );

	NetworkConnectionThread* connection_thread = (NetworkConnectionThread*) parameters[1];
	EGE_ASSERT( connection_thread != _null );

	// If other modules do not keep this connection then release it
	if ( connection->GetRefCount( ) == 1 && connection->IsBusy( ) == _false )
	{
		connection_thread->mLocker.Enter( );
		connection_thread->mConnections.Remove( connection );
		connection_thread->mLocker.Leave( );

		return PersistenceThread::_ACTION_REMOVE;
	}

	// Process operations
	connection_thread->ProcessConnectionOperations( connection );

	return PersistenceThread::_ACTION_KEEP;
}

_ubool NetworkConnectionThread::Initialize( _dword max_connection_number, _dword interval, WStringPtr thread_name )
{
	// Create thread
	if ( mThread.Create( max_connection_number, 0, _false, interval, thread_name ) == _false )
	{
		WLOG_ERROR_1( L"Create network connection thread (name: %s) failed", thread_name.Str( ) );
		return _false;
	}

	return _true;
}

_void NetworkConnectionThread::Finalize( )
{
	// Get the thread name
	WString thread_name = mThread.GetThreadName( );

	// Closing
	WLOG_TRACE_1( L"Finalizing '%s' network connection thread ...", thread_name.Str( ) );

	// Resume the thread to process stop connections
	mThread.Resume( );

	// Stop all connections
	Stop( );

	// Close thread
	mThread.Close( );

	// Closed
	WLOG_TRACE_1( L"Finalized '%s' network connection thread", thread_name.Str( ) );
}

_void NetworkConnectionThread::Tick( _dword limited_elapse, _dword elapse )
{
	LockOwner lock_owner( mLocker );

	for ( _dword i = 0; i < mConnections.Number( ); i ++ )
	{
		INetworkConnection* connection = mConnections[i];
		EGE_ASSERT( connection != _null );

		connection->Tick( limited_elapse, elapse );
	}
}

WStringPtr NetworkConnectionThread::GetName( ) const
{
	return mThread.GetThreadName( );
}

_void NetworkConnectionThread::Stop( )
{
	LockOwner lock_owner( mLocker );

	for ( _dword i = 0; i < mConnections.Number( ); i ++ )
		mConnections[i]->Stop( );
}

_void NetworkConnectionThread::Pause( )
{
	LockOwner lock_owner( mLocker );

	mThread.Suspend( );
}

_void NetworkConnectionThread::Resume( )
{
	LockOwner lock_owner( mLocker );

	mThread.Resume( );
}

_void NetworkConnectionThread::AddConnection( INetworkConnection* connection )
{
	EGE_ASSERT( connection != _null );

	LockOwner lock_owner( mLocker );

	// And and keep connection alive
	mConnections.Append( connection );

	// Register the connection update thread
	mThread.AddUpdaterFunc( OnUpdateConnectionCallback, QwordParameters2( (_qword)connection, (_qword)this ) );

	WLOG_TRACE_2( L"Network connection thread(%s) Add (%s) connection", 
		mThread.GetThreadName( ).Str( ), WString( ).FromString( connection->GetRootURL( ) ).Str( ) );
}

_dword NetworkConnectionThread::GetConnectionsNumber( ) const
{
	return mConnections.Number( );
}

_void NetworkConnectionThread::ProcessConnectionOperations( INetworkConnection* connection )
{
	// Process delay connect operations
	if ( mFlags.HasFlags( _FLAG_CONNECT ) )
		connection->ProcessDelayConnectOperations( );

	// Process delay send operations
	if ( mFlags.HasFlags( _FLAG_SEND ) )
		connection->ProcessDelaySendOperations( );

	// Process delay recv operations
	if ( mFlags.HasFlags( _FLAG_RECV ) )
		connection->ProcessDelayRecvOperations( );
}