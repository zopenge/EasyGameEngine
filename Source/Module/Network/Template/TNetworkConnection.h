//! @file     TNetworkConnection.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TNetworkConnection
//----------------------------------------------------------------------------

template< typename Type >
class TNetworkConnection : public INTERFACE_CONNECTION_IMPL( TFlagsObject< Type > )
{
protected:
	typedef INTERFACE_CONNECTION_IMPL( TFlagsObject< Type > ) TBaseClass;

protected:
	//!	The stop state
	enum _STOP_STATE
	{
		_STOP_FLAG_NONE,
		_STOP_FLAG_STOPPING,
	};

protected:
	//!	The thread locker
	Lock							mLock;
	//!	The stop state
	_STOP_STATE						mStopState;

	//!	The connect time out
	_dword							mConnectTimeout;
	//!	The transfer time out
	_dword							mTransferTimeout;

	//!	The upload speed
	_qword							mMaxUploadSpeed;
	//!	The download speed
	_qword							mMaxDownloadSpeed;

	//!	The low limited speed bytes
	_dword							mLimitSpeedBytes;

	//!	The connect action recorder
	IActionRecorderRef				mConnectActionRecorder;
	//!	The send action recorder
	IActionRecorderRef				mSendActionRecorder;
	//!	The recv action recorder
	IActionRecorderRef				mRecvActionRecorder;

	//!	The root URL
	AString							mRootURL;

	//!	The local address
	Address							mLocalAddress;
	//!	The remote address, if we use the 
	Address							mRemoteAddress;

	//!	The request time
	Time							mRequestTime;

	//!	The auto-connection interval
	_dword							mAutoConnectionInterval;

	//!	The notifier.
	INetworkConnectionNotifierRef	mNotifier;

	//!	The connection thread 
	INetworkConnectionThread*		mConnectionThread;

protected:
	//!	Initialize local address.
	_ubool InitLocalAddress( Address::_TYPE type );
	//!	Initialize remote address.
	_ubool InitRemoteAddress( Address::_TYPE type, _dword port, _dword ip_address );
	_ubool InitRemoteAddress( const Address& ip_address );

protected:
	//!	When connect.
	virtual _ubool OnConnect( ) { return _false; }
	//!	When recv buffer.
	virtual _dword OnRecv( _byte* buffer, _dword size ) { return 0; }
	//!	When send buffer.
	virtual _dword OnSend( const _byte* buffer, _dword size ) { return 0; }

// TConnection Interface
protected:
	virtual _void							SetConnectionState( _CONNECTION_STATE state ) override;

protected:
	TNetworkConnection( INetworkConnectionThread* connection_thread );
	virtual ~TNetworkConnection( );

public:
	//!	Initialize by UR.
	_ubool Initialize( const Address& remote_address );
	//!	Initialize by URL address.
	_ubool Initialize( AStringPtr url_address );
	_ubool Initialize( WStringPtr url_address );

// INetworkConnection Interface
public:
	virtual _void							SetNotifier( INetworkConnectionNotifier* notifier ) override;
	virtual INetworkConnectionNotifier*		GetNotifier( ) override;

	virtual AStringPtr						GetRootURL( ) const override;

	virtual _ubool							IsBusy( ) const override;

	virtual _void							SetConnectTimeout( _dword timeout ) override;
	virtual _dword							GetConnectTimeout( ) const override;

	virtual _void							SetLowSpeedLimit( _dword limit_speed_bytes ) override;
	virtual _dword							GetLowSpeedLimit( ) const override;

	virtual _void							SetMaxUploadSpeed( _qword max_send_bytes ) override;
	virtual _qword							GetMaxUploadSpeed( ) const override;

	virtual _void							SetMaxDownloadSpeed( _qword max_recv_bytes ) override;
	virtual _qword							GetMaxDownloadSpeed( ) const override;

	virtual _dword							GetPort( ) const override;
	virtual const Address&					GetLocalAddress( ) const override;
	virtual const Address&					GetRemoteAddress( ) const override;

	virtual _void							SetRequestTime( const Time& time ) override;
	virtual const Time&						GetRequestTime( ) const override;

	virtual _void							SetAutoReconnection( _ubool enable, _dword interval ) override;
	virtual _dword							GetAutoReconnectionInterval( ) const override;

	virtual _ubool							Connect( ) override;
	virtual _void							Disconnect( ) override;

	virtual _void							Stop( ) override;

	virtual _ubool							Send( _dword size, const _byte* buffer ) override;
	virtual _ubool							SendInstant( _dword size, const _byte* buffer ) override;

	virtual _ubool							IsRemoteFileExist( WStringPtr filename ) override;
	virtual _ubool							GetRemoteFileLastModifiedTime( WStringPtr filename, Time& time ) override;
	virtual INetworkStreamReaderPassRef		OpenRemoteFile( WStringPtr filename, INetworkStreamReaderNotifier* notifier = _null ) override;

	virtual IActionRecorder*				GetConnectActionRecord( ) override;
	virtual IActionRecorder*				GetSendActionRecord( ) override;
	virtual IActionRecorder*				GetRecvActionRecord( ) override;

	virtual _void							ProcessDelayConnectOperations( ) override;
	virtual _void							ProcessDelaySendOperations( ) override;
	virtual _void							ProcessDelayRecvOperations( ) override;

	virtual _PROCESS_STATE					ProcessConnectAction( ) override;
	virtual _PROCESS_STATE					ProcessRecvAction( IStreamWriter* stream_writer ) override;
	virtual _PROCESS_STATE					ProcessSendAction( IStreamReader* stream_reader ) override;
};

//----------------------------------------------------------------------------
// TNetworkConnection Implementation
//----------------------------------------------------------------------------

template< typename Type >
TNetworkConnection< Type >::TNetworkConnection( INetworkConnectionThread* connection_thread )
{
	mStopState				= _STOP_FLAG_NONE;

	mConnectTimeout			= -1;
	mTransferTimeout		= -1;

	mMaxUploadSpeed			= -1;
	mMaxDownloadSpeed		= -1;

	mLimitSpeedBytes		= -1;

	mLocalAddress			= Address::cNullAddress;
	mRemoteAddress			= Address::cNullAddress;

	mRequestTime			= Time::cNull;

	mAutoConnectionInterval	= 0;

	mConnectActionRecorder	= GetInterfaceFactory( )->CreateActionRecorder( );
	mSendActionRecorder		= GetInterfaceFactory( )->CreateActionRecorder( );
	mRecvActionRecorder		= GetInterfaceFactory( )->CreateActionRecorder( );

	mNotifier				= &NullNetwork::GetInstance( ).GetNetworkConnectionNotifier( );

	mConnectionThread		= connection_thread;
}

template< typename Type >
TNetworkConnection< Type >::~TNetworkConnection( )
{
}

template< typename Type >
_ubool TNetworkConnection< Type >::InitLocalAddress( Address::_TYPE type )
{
	mLocalAddress.mType	= type;
	mLocalAddress.mPort	= 0;
	mLocalAddress.mIP	= GetNet( )->GetLocalIPAddress( 0 );

	return _true;
}

template< typename Type >
_ubool TNetworkConnection< Type >::InitRemoteAddress( Address::_TYPE type, _dword port, _dword ip_address )
{
	if ( port == 0 )
	{
		WLOG_ERROR( L"The port is 0, you must provide the port number" );
		return _false;
	}

	if ( ip_address == 0 )
	{
		WLOG_ERROR( L"The IP address is 0, you must provide the IP address" );
		return _false;
	}

	mRemoteAddress.mType	= type;
	mRemoteAddress.mPort	= (_word) port;
	mRemoteAddress.mIP		= ip_address;

	return _true;
}

template< typename Type >
_ubool TNetworkConnection< Type >::InitRemoteAddress( const Address& ip_address )
{
	return InitRemoteAddress( (Address::_TYPE) ip_address.mType, ip_address.mPort, ip_address.mIP );
}

template< typename Type >
_void TNetworkConnection< Type >::SetConnectionState( _CONNECTION_STATE state )
{
	// Get the previous state
	_CONNECTION_STATE prev_state = TBaseClass::GetConnectionState( );

	// Update connection state
	TBaseClass::SetConnectionState( state );

	// Notify if the state has changed
	if ( prev_state != state )
	{
		// Output connection state changed log
		WLOG_TRACE_3( L"Update network connection state: %s->%s [%s]",
			mLocalAddress.ToStringW( _true ).Str( ), mRemoteAddress.ToStringW( _true ).Str( ), this->GetConnectionStateString( state ).Str( ) );

		// Tell the user connection state
		mNotifier->OnUpdateState( this->GetConnectionState( ) );
	}
}

template< typename Type >
_ubool TNetworkConnection< Type >::Initialize( const Address& remote_address )
{
	mRootURL.Clear( );

	// Initialize the local address
	if ( InitLocalAddress( Address::_TYPE_TCP ) == _false )
		return _false;

	// Initialize the remote address
	if ( InitRemoteAddress( remote_address ) == _false )
		return _false;

	return _true;
}

template< typename Type >
_ubool TNetworkConnection< Type >::Initialize( AStringPtr url_address )
{
	return Initialize( WString( ).FromString( url_address ) );
}

template< typename Type >
_ubool TNetworkConnection< Type >::Initialize( WStringPtr url_address )
{
	// Check root URL
	if ( url_address.IsEmpty( ) )
	{
		WLOG_ERROR( L"Initialize network connection failed, due to the URL address is empty" );
		return _false;
	}

	// Initialize the local address
	if ( InitLocalAddress( Address::_TYPE_TCP ) == _false )
		return _false;

	// Jump the "xxx://" string
	AString url_address_without_protocols = _networkHelper::GetURLAddressWithoutProtocols( AString( ).FromString( url_address ) );

	// Get the URL address and port number
	if ( url_address_without_protocols.SearchL2R( ":" ) != -1 )
	{
		StringFormatter::ParseString( url_address_without_protocols.Str( ), "%s:%d", mRootURL, mRemoteAddress.mPort );
	}
	else
	{
		mRootURL				= url_address_without_protocols;
		mRemoteAddress.mPort	= 80;
	}

	// Check root URL
	if ( mRootURL.IsEmpty( ) )
	{
		WLOG_ERROR( L"Initialize network connection failed, due to the root URL address is empty" );
		return _false;
	}

	// Check root URL and port number
	if ( mRemoteAddress.mPort == 0 )
	{
		WLOG_ERROR( L"Initialize network connection failed, due to the port of root URL address is 0" );
		return _false;
	}

	return _true;
}

template< typename Type >
_void TNetworkConnection< Type >::SetNotifier( INetworkConnectionNotifier* notifier )
{
	if ( notifier == _null )
		mNotifier = &NullNetwork::GetInstance( ).GetNetworkConnectionNotifier( );
	else
		mNotifier = GetNetworkResourceManager( )->CreateNetworkConnectionNotifier( notifier );
}

template< typename Type >
INetworkConnectionNotifier* TNetworkConnection< Type >::GetNotifier( )
{
	return mNotifier;
}

template< typename Type >
AStringPtr TNetworkConnection< Type >::GetRootURL( ) const
{
	return mRootURL;
}

template< typename Type >
_ubool TNetworkConnection< Type >::IsBusy( ) const
{
	if ( mConnectActionRecorder->GetActionsNumber( ) != 0 )
		return _true;

	if ( mSendActionRecorder->GetActionsNumber( ) != 0 )
		return _true;

	return _false;
}

template< typename Type >
_void TNetworkConnection< Type >::SetConnectTimeout( _dword timeout )
{
	mConnectTimeout = timeout;
}

template< typename Type >
_dword TNetworkConnection< Type >::GetConnectTimeout( ) const
{
	return mConnectTimeout;
}

template< typename Type >
_void TNetworkConnection< Type >::SetLowSpeedLimit( _dword limit_speed_bytes )
{
	mLimitSpeedBytes = limit_speed_bytes;
}

template< typename Type >
_dword TNetworkConnection< Type >::GetLowSpeedLimit( ) const
{
	return mLimitSpeedBytes;
}

template< typename Type >
_void TNetworkConnection< Type >::SetMaxUploadSpeed( _qword max_send_bytes )
{
	mMaxUploadSpeed = max_send_bytes;
}

template< typename Type >
_qword TNetworkConnection< Type >::GetMaxUploadSpeed( ) const
{
	return mMaxUploadSpeed;
}

template< typename Type >
_void TNetworkConnection< Type >::SetMaxDownloadSpeed( _qword max_recv_bytes )
{
	mMaxDownloadSpeed = max_recv_bytes;
}

template< typename Type >
_qword TNetworkConnection< Type >::GetMaxDownloadSpeed( ) const
{
	return mMaxDownloadSpeed;
}

template< typename Type >
_dword TNetworkConnection< Type >::GetPort( ) const
{
	return mLocalAddress.mPort;
}

template< typename Type >
const Address& TNetworkConnection< Type >::GetLocalAddress( ) const
{
	return mLocalAddress;
}

template< typename Type >
const Address& TNetworkConnection< Type >::GetRemoteAddress( ) const
{
	return mRemoteAddress;
}

template< typename Type >
_void TNetworkConnection< Type >::SetRequestTime( const Time& time )
{
	mRequestTime = time;
}

template< typename Type >
const Time& TNetworkConnection< Type >::GetRequestTime( ) const
{
	return mRequestTime;
}

template< typename Type >
_void TNetworkConnection< Type >::SetAutoReconnection( _ubool enable, _dword interval )
{
	mAutoConnectionInterval = interval;

	this->EnableFlags( INetworkConnection::_FLAG_AUTO_CONNECTION, enable );
}

template< typename Type >
_dword TNetworkConnection< Type >::GetAutoReconnectionInterval( ) const
{
	return mAutoConnectionInterval;
}

template< typename Type >
_ubool TNetworkConnection< Type >::Connect( )
{
	// We only allow one connection action
	if ( mConnectActionRecorder->GetActionsNumber( ) == 0 )
		mConnectActionRecorder->AddAction( IActionRecordPassRef( new NetworkConnectOperation( this ) ).GetPtr( ) );

	// Update the state here to prevent duplicated connection operations
	SetConnectionState( _CS_CONNECTING );

	return _true;
}

template< typename Type >
_void TNetworkConnection< Type >::Disconnect( )
{
	SetConnectionState( _CS_DISCONNECTED );

	Stop( );
}

template< typename Type >
_void TNetworkConnection< Type >::Stop( )
{
	mStopState = _STOP_FLAG_STOPPING;

	mConnectActionRecorder->ClearAllActions( _true );
	mSendActionRecorder->ClearAllActions( _true );
	mRecvActionRecorder->ClearAllActions( _true );

	mStopState = _STOP_FLAG_NONE;
}

template< typename Type >
_ubool TNetworkConnection< Type >::Send( _dword size, const _byte* buffer )
{
	if ( size == 0 || buffer == _null )
		return _false;

	LockOwner lock_owner( mLock );

	if ( this->GetConnectionState( ) == _CS_DISCONNECTED )
		return _false;

	// Get the last network send operation to combine
	INetworkOperationRef last_send_op = (INetworkOperation*) mSendActionRecorder->GetLastAction( );
	if ( last_send_op.IsValid( ) && last_send_op->CombineBuffer( size, buffer ) )
		return _true; // Combine successful

	// Add new send operation
	mSendActionRecorder->AddAction( IActionRecordPassRef( new NetworkSendOperation( this, size, buffer ) ).GetPtr( ) );

	// Process connection operations
	if ( this->HasFlags( INetworkConnection::_FLAG_BLOCK_MODE ) )
		mConnectionThread->ProcessConnectionOperations( this );

	return _true;
}

template< typename Type >
_ubool TNetworkConnection< Type >::SendInstant( _dword size, const _byte* buffer )
{
	LockOwner lock_owner( mLock );

	if ( this->GetConnectionState( ) == _CS_DISCONNECTED )
		return _false;

	// Insert new send operation to the first place
	mSendActionRecorder->InsertAction( 0, IActionRecordPassRef( new NetworkSendOperation( this, size, buffer ) ).GetPtr( ) );

	// Process connection operations
	if ( this->HasFlags( INetworkConnection::_FLAG_BLOCK_MODE ) )
		mConnectionThread->ProcessConnectionOperations( this );

	return _true;
}

template< typename Type >
_ubool TNetworkConnection< Type >::IsRemoteFileExist( WStringPtr filename )
{
	return _false;
}

template< typename Type >
_ubool TNetworkConnection< Type >::GetRemoteFileLastModifiedTime( WStringPtr filename, Time& time )
{
	return _false;
}

template< typename Type >
INetworkStreamReaderPassRef TNetworkConnection< Type >::OpenRemoteFile( WStringPtr filename, INetworkStreamReaderNotifier* notifier )
{
	return _null;
}

template< typename Type >
IActionRecorder* TNetworkConnection< Type >::GetConnectActionRecord( )
{
	return mConnectActionRecorder;
}

template< typename Type >
IActionRecorder* TNetworkConnection< Type >::GetSendActionRecord( )
{
	return mSendActionRecorder;
}

template< typename Type >
IActionRecorder* TNetworkConnection< Type >::GetRecvActionRecord( )
{
	return mRecvActionRecorder;
}

template< typename Type >
_void TNetworkConnection< Type >::ProcessDelayConnectOperations( )
{
	mConnectActionRecorder->ProcessActions( );
}

template< typename Type >
_void TNetworkConnection< Type >::ProcessDelaySendOperations( )
{
	mSendActionRecorder->ProcessActions( );
}

template< typename Type >
_void TNetworkConnection< Type >::ProcessDelayRecvOperations( )
{
	mRecvActionRecorder->ProcessActions( );
}

template< typename Type >
_PROCESS_STATE TNetworkConnection< Type >::ProcessConnectAction( )
{
	if ( mStopState != _STOP_FLAG_NONE )
		return _PS_ABORTED;

	// Start to connect
	if ( OnConnect( ) == _false )
	{
		// If we enable auto-connection then re-connect it
		if ( GetNetworkModule( )->IsPowerOn( ) )
		{
			if ( this->HasFlags( INetworkConnection::_FLAG_AUTO_CONNECTION ) )
			{
				// Do not remove the action and try to connect again
				SetConnectionState( _CS_DISCONNECTED );
				return _PS_CONTINUE;
			}
		}

		return _PS_ERROR;
	}
	// Connection successful
	else
	{
		SetConnectionState( _CS_CONNECTED );
	}

	return _PS_FINISHED;
}

template< typename Type >
_PROCESS_STATE TNetworkConnection< Type >::ProcessRecvAction( IStreamWriter* stream_writer )
{
	if ( GetNetworkModule( )->IsPowerOff( ) )
		return _PS_ABORTED;

	if ( mStopState != _STOP_FLAG_NONE )
		return _PS_ABORTED;

	// Process recv action by state
	if ( this->GetConnectionState( ) == _CS_CONNECTED )
	{
		// Make sure the connection does not stop by user
		while ( mStopState == _STOP_FLAG_NONE )
		{
			// Read chunk_buffer from socket
			const _dword chunk_size = 8 KB; _byte chunk_buffer[ chunk_size ]; 
			_dword read_bytes = OnRecv( chunk_buffer, chunk_size );

			// Connection lost or receive nothing
			if ( read_bytes == -1 || read_bytes == 0 )
				break; // The connection is break, continue to receive the buffer data from remote

			// Update stream writer chunk_buffer data
			stream_writer->WriteBuffer( chunk_buffer, read_bytes );

			// Build the buffer data
			_dword			size	= stream_writer->GetOffset( );
			const _byte*	buffer	= stream_writer->GetBuffer( );

			// Here we record the processed time, we won't let it to process too much time
			const _dword time_out	= 5 SEC;
			const _dword start_tick = Platform::GetCurrentTickCount( );

			// Start to process buffer data
			_dword processed_bytes = 0;
			while ( size != 0 || Platform::GetCurrentTickCount( ) - start_tick >= time_out )
			{
				// Tell user we have receive buffer data
				_dword recv_bytes = mNotifier->OnRecvBuffer( size, buffer, QwordParameters4::cNull );
				if ( recv_bytes == 0 )
					break; // The protocol is incomplete, continue to receive the buffer data from remote

				// The user processed buffer data successful, so we can remove it later
				processed_bytes += recv_bytes;

				// Update the size and buffer by processed bytes
				size	-= recv_bytes;
				buffer	+= recv_bytes;
			}

			// Remove the processed buffer data
			stream_writer->RemoveBuffer( processed_bytes );
		}
	}

	// We always let the recv operation alive if we do not call stop operations
	return _PS_CONTINUE;
}

template< typename Type >
_PROCESS_STATE TNetworkConnection< Type >::ProcessSendAction( IStreamReader* stream_reader )
{
	if ( mStopState != _STOP_FLAG_NONE )
		return _PS_ABORTED;

	if ( this->GetConnectionState( ) == _CS_CONNECTED )
	{
		// Get the buffer data and size
		const _dword size	= stream_reader->GetSize( ) - stream_reader->GetOffset( );
		const _byte* buffer	= stream_reader->GetBuffer( ) + stream_reader->GetOffset( );

		// Send buffer
		_dword send_bytes = OnSend( buffer, size );

		// Connection lost
		if ( send_bytes == -1 )
		{
			// If we had disconnect it then break it
			if ( this->GetConnectionState( ) == _CS_DISCONNECTED )
				return _PS_ABORTED;

			// If we enable auto-connection then re-connect it
			if ( this->HasFlags( INetworkConnection::_FLAG_AUTO_CONNECTION ) )
				Connect( );

			// If we enable resend all data feature then need to send from the begin of the data
			if ( this->HasFlags( INetworkConnection::_FLAG_RESEND_ALL_DATA_WHEN_RECONNECT ) )
				stream_reader->Seek( _SEEK_BEGIN, 0 );
		}
		else
		{
			// Tell user we have send buffer data
			mNotifier->OnSendBuffer( send_bytes, buffer, QwordParameters4::cNull );

			// Update the stream current position
			_dword cur_pos = stream_reader->Seek( _SEEK_CURRENT, send_bytes );

			// Check whether finished or processing
			if ( cur_pos >= stream_reader->GetSize( ) - 1 )
				return _PS_FINISHED;
			else
				return _PS_CONTINUE;
		}
	}

	// We always let the send operation alive if we do not call stop operations
	return _PS_CONTINUE;
}

}
