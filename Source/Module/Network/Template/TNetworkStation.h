//! @file     TNetworkStation.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TNetworkStation
//----------------------------------------------------------------------------

template< typename Type, typename SocketType >
class TNetworkStation : public TNameObject< TObject< Type > >
{
protected:
	struct SocketInfo
	{
		_dword				mClientID;
		IStreamWriterRef	mC2SStream;
		IStreamWriterRef	mS2CStream;
		SocketType			mSocket;

		//!	Use client ID as key.
		operator _dword( ) const
			{ return mClientID; }

		SocketInfo( )
		{
			mClientID = 0;
		}
	};
	typedef Array< SocketInfo > SocketInfoArray;

protected:
	//!	True indicates it's stopping now
	_ubool						mIsStopping;

	//!	The thread locker
	Lock						mLocker;
	//!	The thread name
	WString						mThreadName;
	//!	The thread
	PersistenceThread			mThread;

	//!	The address
	Address						mAddress;

	//!	The client ID counter
	_dword						mClientIDCounter;
	//!	The sockets
	SocketInfoArray				mSockets;

	//!	The protocol buffer processor
	IProtoBufProcessorRef		mProtoBufProcessor;

	//!	The notifier.
	INetworkStationNotifierRef	mNotifier;

protected:
	//!	When get available bytes.
	virtual _dword OnGetAvailableBytes( const SocketInfo& socket_info ) PURE;
	//!	When recv buffer from client.
	virtual _dword OnRecv( SocketInfo& socket_info, _byte* buffer, _dword size ) PURE;
	//!	When send buffer to client.
	virtual _dword OnSend( SocketInfo& socket_info, const _byte* buffer, _dword size ) PURE;
	//!	When close socket.
	virtual _void OnClose( SocketInfo& socket_info ) PURE;

	//!	When download with all sockets.
	virtual _void OnDownload( ) PURE;
	//!	When upload with all sockets.
	virtual _void OnUpload( ) PURE;

protected:
	//!	When process sockets.
	static _dword OnUpdateFunctionCallback( const QwordParameters2& parameters );

protected:
	//! Initialize.
	_ubool Initialize( WStringPtr thread_name );

	//!	Append socket.
	_ubool AppendSocket( const SocketType& socket );
	//!	Remove socket.
	_void RemoveSocket( _dword client_id );
	//!	Process socket download progression.
	_ubool ProcessSocketDownload( SocketInfo& socket_info );
	//!	Process socket upload progression.
	_ubool ProcessSocketUpload( SocketInfo& socket_info );

protected:
	TNetworkStation( );
	virtual ~TNetworkStation( );

// INetworkStation Interface
public:
	virtual _void						SetNotifier( INetworkStationNotifier* notifier ) override;
	virtual INetworkStationNotifier*	GetNotifier( ) override;

	virtual const Address&				GetAddress( ) const override;

	virtual _ubool						Start( ) override;
	virtual _void						Stop( ) override;

	virtual _dword						GetClientNumber( ) const override;
	virtual _dword						GetClientIDByIndex( _dword index ) override;

	virtual _ubool						SendRequest( _dword client_id, _dword msg_id ) override;
	virtual _ubool						SendMessage( _dword client_id, _dword msg_id, const google::protobuf::MessageLite& message ) override;

	virtual _ubool						Broadcast( _dword size, const _byte* buffer ) override;
};

//----------------------------------------------------------------------------
// TNetworkStation Implementation
//----------------------------------------------------------------------------

template< typename Type, typename SocketType >
TNetworkStation< Type, SocketType >::TNetworkStation( )
{
	mIsStopping			= _false;

	mAddress			= Address::cNullAddress;

	mClientIDCounter	= 0;

	mNotifier			= &NullNetwork::GetInstance( ).GetNetworkStationNotifier( );
}

template< typename Type, typename SocketType >
TNetworkStation< Type, SocketType >::~TNetworkStation( )
{
	Stop( );
}

template< typename Type, typename SocketType >
_dword TNetworkStation< Type, SocketType >::OnUpdateFunctionCallback( const QwordParameters2& parameters )
{
	TNetworkStation* _self = (TNetworkStation*) parameters[0];

	// Process upload and download progression
	_self->mLocker.Enter( );
	_self->OnUpload( );
	_self->OnDownload( );
	_self->mLocker.Leave( );

	return PersistenceThread::_ACTION_KEEP;
}

template< typename Type, typename SocketType >
_ubool TNetworkStation< Type, SocketType >::Initialize( WStringPtr thread_name )
{
	// Save the thread name
	mThreadName = thread_name;

	// Create protocol buffer processor
	mProtoBufProcessor = GetInterfaceFactory( )->CreateProtoBufProcessor( );
	if ( mProtoBufProcessor.IsNull( ) )
		return _false;

	return _true;
}

template< typename Type, typename SocketType >
_ubool TNetworkStation< Type, SocketType >::AppendSocket( const SocketType& socket )
{
	// Create socket info
	SocketInfo socket_info;
	socket_info.mClientID	= ++ mClientIDCounter;
	socket_info.mSocket		= socket;

	// Create C->S stream
	socket_info.mC2SStream = GetInterfaceFactory( )->CreateMemStreamWriter( 1 KB );
	if ( socket_info.mC2SStream.IsNull( ) )
		return _false;

	// Create S->C stream
	socket_info.mS2CStream = GetInterfaceFactory( )->CreateMemStreamWriter( 1 KB );
	if ( socket_info.mS2CStream.IsNull( ) )
		return _false;

	mNotifier->OnAcceptClient( socket_info.mClientID );

	mSockets.InsertAscending( socket_info );

	return _true;
}

template< typename Type, typename SocketType >
_void TNetworkStation< Type, SocketType >::RemoveSocket( _dword client_id )
{
	typename SocketInfoArray::Iterator it = mSockets.SearchAscending( client_id );
	if ( it.IsValid( ) == _false )
		return;

	mNotifier->OnLostClient( client_id );

	SocketInfo& socket_info = it;
	OnClose( socket_info );

	mSockets.RemoveAscending( client_id );
}

template< typename Type, typename SocketType >
_ubool TNetworkStation< Type, SocketType >::ProcessSocketDownload( SocketInfo& socket_info )
{
	// Get the available bytes what will be read
	_dword available_bytes = OnGetAvailableBytes( socket_info );
	if ( available_bytes == 0 )
		return _true;

	// It's disconnected, remove it
	if ( available_bytes == -1 )
		return _false;

	// Read pipe bytes
	MemArrayPtr< _byte > buffer( available_bytes );
	_dword recv_size = OnRecv( socket_info, buffer, available_bytes );
	if ( recv_size == 0 )
		return _true;

	// It's disconnected, remove it
	if ( recv_size == -1 )
		return _false;

	// Write to stream
	socket_info.mC2SStream->WriteBuffer( buffer, recv_size );

	// Get the total bytes
	_dword total_bytes = socket_info.mC2SStream->GetOffset( );

	// Process buffer ( can be broken by stop action )
	while ( total_bytes > 0 && mIsStopping == _false )
	{
		_dword processed_bytes = mNotifier->OnRecvBuffer( socket_info.mClientID, total_bytes, socket_info.mC2SStream->GetBuffer( ), socket_info.mS2CStream );
		if ( processed_bytes == -1 || processed_bytes == 0 )
			break;

		// Send buffer
		if ( socket_info.mS2CStream->GetOffset( ) != 0 )
		{
			_dword send_size = OnSend( socket_info, socket_info.mS2CStream->GetBuffer( ), socket_info.mS2CStream->GetOffset( ) );
			if ( send_size == 0 )
				continue;

			// It's disconnected, remove it
			if ( send_size == -1 )
				return _false;

			// Remove processed buffer from stream
			socket_info.mS2CStream->RemoveBuffer( send_size );
		}

		// Remove recv buffer
		_dword removed_size = socket_info.mC2SStream->RemoveBuffer( processed_bytes );
		EGE_ASSERT( removed_size <= total_bytes );

		// Decrease total bytes
		total_bytes -= removed_size;
	}

	return _true;
}

template< typename Type, typename SocketType >
_ubool TNetworkStation< Type, SocketType >::ProcessSocketUpload( SocketInfo& socket_info )
{
	// Get the total bytes
	_dword total_bytes = socket_info.mS2CStream->GetOffset( );

	// Process buffer ( can be broken by stop action )
	while ( total_bytes > 0 && mIsStopping == _false )
	{
		_dword send_size = OnSend( socket_info, socket_info.mS2CStream->GetBuffer( ), socket_info.mS2CStream->GetOffset( ) );
		if ( send_size == 0 )
			continue;

		// It's disconnected, remove it
		if ( send_size == -1 )
			return _false;

		// Remove processed buffer from stream
		_dword removed_size = socket_info.mS2CStream->RemoveBuffer( send_size );
		EGE_ASSERT( removed_size <= total_bytes );

		// Decrease total bytes
		total_bytes -= removed_size;
	}

	return _true;
}

template< typename Type, typename SocketType >
_void TNetworkStation< Type, SocketType >::SetNotifier( INetworkStationNotifier* notifier )
{
	if ( notifier == _null )
		mNotifier = &NullNetwork::GetInstance( ).GetNetworkStationNotifier( );
	else
		mNotifier = notifier;
}

template< typename Type, typename SocketType >
INetworkStationNotifier* TNetworkStation< Type, SocketType >::GetNotifier( )
{
	return mNotifier;
}

template< typename Type, typename SocketType >
const Address& TNetworkStation< Type, SocketType >::GetAddress( ) const
{
	return mAddress;
}

template< typename Type, typename SocketType >
_ubool TNetworkStation< Type, SocketType >::Start( )
{
	// Create thread
	if ( mThread.Create( 1, 0, _false, 100, mThreadName ) == _false )
		return _false;

	mThread.AddUpdaterFunc( OnUpdateFunctionCallback, QwordParameters2( (_qword)this, _null ) );

	return _true;
}

template< typename Type, typename SocketType >
_void TNetworkStation< Type, SocketType >::Stop( )
{
	mIsStopping = _true;
	{
		mLocker.Enter( );
		{
			for ( _dword i = 0; i < mSockets.Number( ); i ++ )
			{
				mNotifier->OnLostClient( mSockets[i].mClientID );

				OnClose( mSockets[i] );
			}

			mSockets.Clear( _true );
		}
		mLocker.Leave( );

		mThread.Close( );

		// Clear notifier
		mNotifier.Clear( );
	}
	mIsStopping = _false;
}

template< typename Type, typename SocketType >
_dword TNetworkStation< Type, SocketType >::GetClientNumber( ) const
{
	return mSockets.Number( );
}

template< typename Type, typename SocketType >
_dword TNetworkStation< Type, SocketType >::GetClientIDByIndex( _dword index )
{
	if ( index >= mSockets.Number( ) )
		return 0;

	return mSockets[index].mClientID;
}

template< typename Type, typename SocketType >
_ubool TNetworkStation< Type, SocketType >::SendRequest( _dword client_id, _dword msg_id )
{
	LockOwner lock_owner( mLocker );

	typename SocketInfoArray::Iterator it = mSockets.SearchAscending( client_id );
	if ( it.IsValid( ) == _false )
		return _false;

	SocketInfo& socket_info = it;

	// Write message into buffer
	MemArrayPtr< _byte > buffer( sizeof( _dword ) * 2 );
	mProtoBufProcessor->WriteMessageIntoBuffer( msg_id, buffer );

	// Write into buffer and prepare to send it
	socket_info.mS2CStream->WriteBuffer( buffer, buffer.SizeOfBytes( ) );

	return _true;
}

template< typename Type, typename SocketType >
_ubool TNetworkStation< Type, SocketType >::SendMessage( _dword client_id, _dword msg_id, const google::protobuf::MessageLite& message )
{
	LockOwner lock_owner( mLocker );

	typename SocketInfoArray::Iterator it = mSockets.SearchAscending( client_id );
	if ( it.IsValid( ) == _false )
		return _false;

	SocketInfo& socket_info = it;

	// Write message into buffer
	MemArrayPtr< _byte > buffer( message.ByteSize( ) + sizeof( _dword ) * 2 );
	mProtoBufProcessor->WriteMessageIntoBuffer( msg_id, message, buffer );

	// Write into buffer and prepare to send it
	socket_info.mS2CStream->WriteBuffer( buffer, buffer.SizeOfBytes( ) );

	return _true;
}

template< typename Type, typename SocketType >
_ubool TNetworkStation< Type, SocketType >::Broadcast( _dword size, const _byte* buffer )
{
	if ( size == 0 || buffer == _null )
		return _false;

	LockOwner lock_owner( mLocker );

	for ( _dword i = 0; i < mSockets.Number( ); i ++ )
	{
		SocketInfo& socket_info = mSockets[i];

		OnSend( socket_info, buffer, size );
	}

	return _true;
}

}