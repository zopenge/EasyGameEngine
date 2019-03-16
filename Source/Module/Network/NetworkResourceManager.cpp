//! @file     NetworkResourceManager.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// NetworkResourceManager Implementation
//----------------------------------------------------------------------------

NetworkResourceManager::NetworkResourceManager( )
{
	mMaxConnectionNumber = 0;
}

NetworkResourceManager::~NetworkResourceManager( )
{
	Finalize( );
}

template< typename Type >
_void NetworkResourceManager::PauseConnectionThreads( Type& threads )
{
	for ( _dword i = 0; i < threads.Number( ); i ++ )
	{
		if ( threads[i] != _null )
			threads[i]->Pause( );
	}
}

template< typename Type >
_void NetworkResourceManager::ResumeConnectionThreads( Type& threads )
{
	for ( _dword i = 0; i < threads.Number( ); i ++ )
	{
		if ( threads[i] != _null )
			threads[i]->Resume( );
	}
}

INetworkConnectionThread* NetworkResourceManager::GetConnectionThread( _ubool thread_alone_mode, WStringPtr thread_name )
{
	NetworkConnectionThread* connection_thread = _null;

	// Use thread alone mode
	if ( thread_alone_mode )
	{
		// Fix the thread name
		WString fixed_thread_name = FORMAT_WSTRING_2( L"Dynamic-%sConnection[%d]", thread_name.Str( ), mConnectionThreads.Number( ) );

		// Create dynamic thread
		connection_thread = new NetworkConnectionThread( NetworkConnectionThread::_FLAG_ALL );
		if ( connection_thread->Initialize( 1, 10, fixed_thread_name ) == _false )
			{ EGE_RELEASE( connection_thread ); return _null; }
	}
	// Use resident thread mode
	else
	{
		// Fix the thread name
		WString fixed_thread_name = FORMAT_WSTRING_1( L"Resident-%sConnections", thread_name.Str( ) );

		// Try to use the existing connection thread
		INetworkConnectionThread* exist_connection_thread = FindConnectionThreadByName( fixed_thread_name );
		if ( exist_connection_thread != _null )
			return exist_connection_thread;

		// Create new connection thread
		connection_thread = new NetworkConnectionThread( NetworkConnectionThread::_FLAG_ALL );
		if ( connection_thread->Initialize( mMaxConnectionNumber, 10, fixed_thread_name ) == _false )
			{ EGE_RELEASE( connection_thread ); return _null; }
	}

	// Let the array to manage it
	mConnectionThreads.Append( connection_thread );
	connection_thread->Release( );

	return connection_thread;
}

INetworkConnectionThread* NetworkResourceManager::FindConnectionThreadByName( WStringPtr thread_name )
{
	for ( _dword i = 0; i < mConnectionThreads.Number( ); i ++ )
	{
		if ( mConnectionThreads[i]->GetName( ) == thread_name )
			return mConnectionThreads[i];
	}

	return _null;
}

_ubool NetworkResourceManager::Initialize( _dword max_connection_number )
{
	WLOG_TRACE( L"Initialize network resource manager ..." );

	mMaxConnectionNumber = max_connection_number;

	WLOG_TRACE( L"Initialize network resource manager OK" );

	return _true;
}

_void NetworkResourceManager::Finalize( )
{
	WLOG_TRACE( L"Release network resource manager ..." );

	// Finalize dynamic threads
	mConnectionThreads.Clear( _true );

	WLOG_TRACE( L"Release network resource manager DONE" );
}

_void NetworkResourceManager::Pause( )
{
	WLOG_TRACE( L"Pausing network resource manager ..." );
	{
		PauseConnectionThreads( mConnectionThreads );
	}
	WLOG_TRACE( L"Pause network resource manager DONE" );
}

_void NetworkResourceManager::Resume( )
{
	WLOG_TRACE( L"Resuming network resource manager ..." );
	{
		ResumeConnectionThreads( mConnectionThreads );
	}
	WLOG_TRACE( L"Resume network resource manager DONE" );
}

_void NetworkResourceManager::Tick( _dword limited_elapse, _dword elapse )
{
	LockOwner lock_owner( mLock );

	// Update connection threads
	for ( _dword i = 0; i < mConnectionThreads.Number( ); i ++ )
	{
		INetworkConnectionThread* connection_thread = mConnectionThreads[i];
		EGE_ASSERT( connection_thread != _null );

		connection_thread->Tick( limited_elapse, elapse );

		// Remove dynamic connection thread
		if ( connection_thread->GetConnectionsNumber( ) == 0 )
		{
			mConnectionThreads[i].Clear( );
			mConnectionThreads.RemoveByIndex( i -- );
		}
	}
}

INetworkConnectionNotifierPassRef NetworkResourceManager::CreateNetworkConnectionNotifier( INetworkConnectionNotifier* notifier )
{
	if ( notifier == _null )
		return _null;

	return new NetworkConnectionNotifier( notifier );
}

INetworkTCPConnectionPassRef NetworkResourceManager::CreateTCPConnection( const Address& remote_address, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode )
{
	LockOwner lock_owner( mLock );

	// The connection thread
	INetworkConnectionThread* connection_thread = GetConnectionThread( thread_alone_mode, L"TCP" );
	if ( connection_thread == _null )
		return _null;

	// Create connection
	NetworkTCPConnection* connection = new NetworkTCPConnection( connection_thread );
	if ( connection->Initialize( remote_address ) == _false )
		{ EGE_RELEASE( connection ); return _null; }

	// Set notifier and bind with connection thread
	connection->SetNotifier( notifier );
	connection_thread->AddConnection( connection );

	return connection;
}

INetworkStationPassRef NetworkResourceManager::CreateTCPStation( _dword port, _dword max_connection_number, _dword recv_block_size )
{
	NetworkTCPStation* station = new NetworkTCPStation( );
	if ( station->Initialize( port, max_connection_number, recv_block_size ) == _false )
		{ EGE_RELEASE( station ); return _null; }

	return station;
}

INetworkHTTPConnectionPassRef NetworkResourceManager::CreateHTTPConnection( const Address& remote_address, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode )
{
	LockOwner lock_owner( mLock );

	// The connection thread
	INetworkConnectionThread* connection_thread = GetConnectionThread( thread_alone_mode, L"HTTP" );
	if ( connection_thread == _null )
		return _null;

	NetworkHTTPConnection* connection = new NetworkHTTPConnection( connection_thread );
	if ( connection->Initialize( remote_address ) == _false )
		{ EGE_RELEASE( connection ); return _null; }

	// Set notifier and bind with connection thread
	connection->SetNotifier( notifier );
	connection_thread->AddConnection( connection );

	return connection;
}

INetworkHTTPConnectionPassRef NetworkResourceManager::CreateHTTPConnection( AStringPtr url_address, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode )
{
	return CreateHTTPConnection( WString( ).FromString( url_address ), notifier, thread_alone_mode );
}

INetworkHTTPConnectionPassRef NetworkResourceManager::CreateHTTPConnection( WStringPtr url_address, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode )
{
	LockOwner lock_owner( mLock );

	// The connection thread
	INetworkConnectionThread* connection_thread = GetConnectionThread( thread_alone_mode, L"HTTP" );
	if ( connection_thread == _null )
		return _null;

	NetworkHTTPConnection* connection = new NetworkHTTPConnection( connection_thread );
	if ( connection->Initialize( url_address ) == _false )
		{ EGE_RELEASE( connection ); return _null; }

	// Set notifier and bind with connection thread
	connection->SetNotifier( notifier );
	connection_thread->AddConnection( connection );

	return connection;
}

INetworkFTPConnectionPassRef NetworkResourceManager::CreateFTPConnection( const Address& remote_address, INetworkFTPConnectionNotifier* notifier, _ubool thread_alone_mode )
{
	LockOwner lock_owner( mLock );

	// The connection thread
	INetworkConnectionThread* connection_thread = GetConnectionThread( thread_alone_mode, L"FTP" );
	if ( connection_thread == _null )
		return _null;

	NetworkFTPConnection* connection = new NetworkFTPConnection( connection_thread );
	if ( connection->Initialize( remote_address ) == _false )
		{ EGE_RELEASE( connection ); return _null; }

	// Set notifier and bind with connection thread
	connection->SetFTPNotifier( notifier );
	connection_thread->AddConnection( connection );

	return connection;
}

INetworkFTPConnectionPassRef NetworkResourceManager::CreateFTPConnection( AStringPtr url_address, INetworkFTPConnectionNotifier* notifier, _ubool thread_alone_mode )
{
	return CreateFTPConnection( WString( ).FromString( url_address ), notifier, thread_alone_mode );
}

INetworkFTPConnectionPassRef NetworkResourceManager::CreateFTPConnection( WStringPtr url_address, INetworkFTPConnectionNotifier* notifier, _ubool thread_alone_mode )
{
	LockOwner lock_owner( mLock );

	// The connection thread
	INetworkConnectionThread* connection_thread = GetConnectionThread( thread_alone_mode, L"FTP" );
	if ( connection_thread == _null )
		return _null;

	NetworkFTPConnection* connection = new NetworkFTPConnection( connection_thread );
	if ( connection->Initialize( url_address ) == _false )
		{ EGE_RELEASE( connection ); return _null; }

	// Set notifier and bind with connection thread
	connection->SetFTPNotifier( notifier );
	connection_thread->AddConnection( connection );

	return connection;
}

INetworkNamedPipeConnectionPassRef NetworkResourceManager::CreateNamedPipeConnection( WStringPtr pipename, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode )
{
	LockOwner lock_owner( mLock );

	// The connection thread
	INetworkConnectionThread* connection_thread = GetConnectionThread( thread_alone_mode, L"NamePipe" );
	if ( connection_thread == _null )
		return _null;

	NetworkNamedPipeConnection* connection = new NetworkNamedPipeConnection( connection_thread );
	if ( connection->Initialize( pipename ) == _false )
		{ EGE_RELEASE( connection ); return _null; }

	// Set notifier and bind with connection thread
	connection->SetNotifier( notifier );
	connection_thread->AddConnection( connection );

	return connection;
}

INetworkStationPassRef NetworkResourceManager::CreateNamedPipeStation( WStringPtr pipename, _dword type, _dword size, _dword timeout )
{
	NetworkNamedPipeStation* station = new NetworkNamedPipeStation( );
	if ( station->Initialize( pipename, type, size, timeout ) == _false )
		{ EGE_RELEASE( station ); return _null; }

	return station;
}

INetworkBluetoothConnectionPassRef NetworkResourceManager::CreateBluetoothConnection( AStringPtr address, const UID128& uid, INetworkConnectionNotifier* notifier, _ubool thread_alone_mode )
{
	LockOwner lock_owner( mLock );

	// The connection thread
	INetworkConnectionThread* connection_thread = GetConnectionThread( thread_alone_mode, L"BT" );
	if ( connection_thread == _null )
		return _null;

	NetworkBluetoothConnection* connection = new NetworkBluetoothConnection( connection_thread );
	if ( connection->Initialize( address, uid ) == _false )
		{ EGE_RELEASE( connection ); return _null; }

	// Set notifier and bind with connection thread
	connection->SetNotifier( notifier );
	connection_thread->AddConnection( connection );

	return connection;
}

INetworkStationPassRef NetworkResourceManager::CreateBluetoothStation( const UID128& uid )
{
	NetworkBluetoothStation* station = new NetworkBluetoothStation( );
	if ( station->Initialize( uid ) == _false )
		{ EGE_RELEASE( station ); return _null; }

	return station;
}

INetworkProtoBufTCPConnectionPassRef NetworkResourceManager::CreateProtoBufTCPConnection( const Address& remote_address, INetworkProtoBufConnectionNotifier* notifier, _ubool thread_alone_mode )
{
	NetworkProtoBufTCPConnection* connection = new NetworkProtoBufTCPConnection( );
	if ( connection->Initialize( remote_address, thread_alone_mode ) == _false )
		{ EGE_RELEASE( connection ); return _null; }

	connection->SetProtoBufNotifier( notifier );

	return connection;
}

INetworkProtoBufHTTPConnectionPassRef NetworkResourceManager::CreateProtoBufHTTPConnection( WStringPtr url_address, INetworkProtoBufConnectionNotifier* notifier, _ubool thread_alone_mode )
{
	NetworkProtoBufHTTPConnection* connection = new NetworkProtoBufHTTPConnection( );
	if ( connection->Initialize( url_address, thread_alone_mode ) == _false )
		{ EGE_RELEASE( connection ); return _null; }

	connection->SetProtoBufNotifier( notifier );

	return connection;
}

INetworkProtoBufNamedPipeConnectionPassRef NetworkResourceManager::CreateProtoBufNamedPipeConnection( WStringPtr pipename, INetworkProtoBufConnectionNotifier* notifier, _ubool thread_alone_mode )
{
	NetworkProtoBufNamedPipeConnection* connection = new NetworkProtoBufNamedPipeConnection( );
	if ( connection->Initialize( pipename, thread_alone_mode ) == _false )
		{ EGE_RELEASE( connection ); return _null; }

	connection->SetProtoBufNotifier( notifier );

	return connection;
}

IArchivePassRef NetworkResourceManager::CreateHTTPArchive( WStringPtr remote_path, _ubool use_whole_path )
{
	NetworkHTTPArchive* archive = new NetworkHTTPArchive( );
	if ( archive->Initialize( remote_path, use_whole_path ) == _false )
		{ EGE_RELEASE( archive ); return _null; }

	return archive;
}