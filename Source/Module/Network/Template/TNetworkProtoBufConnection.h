//! @file     TNetworkProtoBufConnection.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TNetworkProtoBufConnection
//----------------------------------------------------------------------------

template< typename NetworkConnectionType, typename Type >
class TNetworkProtoBufConnection : public TObject< Type >
{
protected:
	RefPtr< NetworkConnectionType >	mConnection;

	IProtoBufProcessorRef			mProtoBufProcessor;
	NetworkProtoBufNotifier*		mNotifier;

protected:
	//!	Create temporary buffer for google-protocol-buffer message.
	_ubool CreateTempBuf( MemArrayPtr< _byte >& temp_buf, const google::protobuf::MessageLite& message );

protected:
	TNetworkProtoBufConnection( );
	virtual ~TNetworkProtoBufConnection( );

// IPriorityObject Interface
public:
	virtual _void								SetPriority( _int priority ) override;
	virtual _int								GetPriority( ) const override;

// IObservable Interface
public:
	virtual _void								RegisterObserver( IObserver* observer ) override;
	virtual _void								UnregisterObserver( IObserver* observer ) override;

	virtual _void								NotifyObservers( const IObservable* generator, const EventBase& event ) override;

// IConnection Interface
public:
	virtual _CONNECTION_STATE					GetConnectionState( ) const override;

	virtual _ubool								IsConnecting( ) const override;
	virtual _ubool								IsConnected( ) const override;
	virtual _ubool								IsConnectionLost( ) const override;

// IFlagsObject Interface
public:
	virtual _ubool								HasFlags( _dword flags, _ubool match_all = _false ) const override;
	virtual _void								EnableFlags( _dword flags, _ubool enable ) override;
	virtual _void								CombineFlags( _dword flags ) override;
	virtual _void								ClearFlags( _dword flags ) override;

	virtual _void								SetFlags( _dword flags ) override;
	virtual _dword								GetFlags( ) const override;
	virtual const FlagsObject&					GetFlagsObject( ) const override;

// INetworkConnection Interface
public:
	virtual _void								SetNotifier( INetworkConnectionNotifier* notifier ) override;
	virtual INetworkConnectionNotifier*			GetNotifier( ) override;

	virtual _NETWORK_CONNECTION_TYPE			GetType( ) const override;

	virtual AStringPtr							GetRootURL( ) const override;

	virtual _ubool								IsBusy( ) const override;

	virtual _void								SetConnectTimeout( _dword timeout ) override;
	virtual _dword								GetConnectTimeout( ) const override;

	virtual _void								SetLowSpeedLimit( _dword limit_speed_bytes ) override;
	virtual _dword								GetLowSpeedLimit( ) const override;

	virtual _void								SetMaxUploadSpeed( _qword max_send_bytes ) override;
	virtual _qword								GetMaxUploadSpeed( ) const override;

	virtual _void								SetMaxDownloadSpeed( _qword max_recv_bytes ) override;
	virtual _qword								GetMaxDownloadSpeed( ) const override;

	virtual _dword								GetPort( ) const override;
	virtual const Address&						GetLocalAddress( ) const override;
	virtual const Address&						GetRemoteAddress( ) const override;

	virtual _void								SetRequestTime( const Time& time ) override;
	virtual const Time&							GetRequestTime( ) const override;

	virtual _void								SetAutoReconnection( _ubool enable, _dword interval ) override;
	virtual _dword								GetAutoReconnectionInterval( ) const override;

	virtual _ubool								Connect( ) override;
	virtual _void								Disconnect( ) override;

	virtual _void								Stop( ) override;

	virtual _ubool								Send( _dword size, const _byte* buffer ) override;
	virtual _ubool								SendInstant( _dword size, const _byte* buffer ) override;

	virtual _ubool								IsRemoteFileExist( WStringPtr filename ) override;
	virtual _ubool								GetRemoteFileLastModifiedTime( WStringPtr filename, Time& time ) override;
	virtual INetworkStreamReaderPassRef			OpenRemoteFile( WStringPtr filename, INetworkStreamReaderNotifier* notifier = _null ) override;

	virtual IActionRecorder*					GetConnectActionRecord( ) override;
	virtual IActionRecorder*					GetSendActionRecord( ) override;
	virtual IActionRecorder*					GetRecvActionRecord( ) override;

	virtual _void								ProcessDelayConnectOperations( ) override;
	virtual _void								ProcessDelaySendOperations( ) override;
	virtual _void								ProcessDelayRecvOperations( ) override;

	virtual _PROCESS_STATE						ProcessConnectAction( ) override;
	virtual _PROCESS_STATE						ProcessRecvAction( IStreamWriter* stream_writer ) override;
	virtual _PROCESS_STATE						ProcessSendAction( IStreamReader* stream_reader ) override;

// ITNetworkProtoBufConnection Interface
public:
	virtual _void								SetProtoBufNotifier( INetworkProtoBufConnectionNotifier* notifier ) override;
	virtual INetworkProtoBufConnectionNotifier* GetProtoBufNotifier( ) override;

// ITProtoBufProcessor Interface
public:
	virtual _void								SetMessageProcessor( IProtoBufMessageProcessor* processor ) override;
	virtual IProtoBufMessageProcessor*			GetMessageProcessor( ) override;

	virtual _void								SetSender( IProtoBufSender* sender ) override;
	virtual IProtoBufSender*					GetSender( ) override;

	virtual _dword								ParseMessageFromBuffer( const _byte* buffer, _dword size, _dword& msg_id, const _byte*& msg_buf, _dword& msg_size ) override;
	virtual _dword								WriteMessageIntoBuffer( _dword id, IStreamWriter* stream_writer ) override;
	virtual _dword								WriteMessageIntoBuffer( _dword id, const google::protobuf::MessageLite& message, IStreamWriter* stream_writer ) override;
	virtual _dword								WriteMessageIntoBuffer( _dword id, _byte* buffer ) override;
	virtual _dword								WriteMessageIntoBuffer( _dword id, const google::protobuf::MessageLite& message, _byte* buffer ) override;

	virtual _void								WriteBuffer( _dword id ) override;
	virtual _void								WriteBuffer( _dword id, const _byte* buffer, _dword size ) override;
	virtual _ubool								PostBuffer( AStringPtr url_name, const AStringArray& header_list, _dword id, const QwordParameters4& parameters ) override;
	virtual _ubool								PostBuffer( AStringPtr url_name, const AStringArray& header_list, _dword id, const _byte* buffer, _dword size, const QwordParameters4& parameters ) override;
};

//----------------------------------------------------------------------------
// TNetworkProtoBufConnection Implementation
//----------------------------------------------------------------------------

template< typename NetworkConnectionType, typename Type >
TNetworkProtoBufConnection< NetworkConnectionType, Type >::TNetworkProtoBufConnection( )
{
	mProtoBufProcessor	= GetInterfaceFactory( )->CreateProtoBufProcessor( );

	mNotifier			= new NetworkProtoBufNotifier( mProtoBufProcessor );
}

template< typename NetworkConnectionType, typename Type >
TNetworkProtoBufConnection< NetworkConnectionType, Type >::~TNetworkProtoBufConnection( )
{
	EGE_RELEASE( mNotifier );
}

template< typename NetworkConnectionType, typename Type >
_ubool TNetworkProtoBufConnection< NetworkConnectionType, Type >::CreateTempBuf( MemArrayPtr< _byte >& temp_buf, const google::protobuf::MessageLite& message )
{
	// Get the message size in bytes
	_dword msg_size = message.ByteSize( );

	// Create buffer to save binary data of message
	temp_buf.Create( msg_size );

	// Serialize message to binary data
	if ( message.SerializePartialToArray( temp_buf.GetPointer( ), msg_size ) == _false )
		return _false;

	return _true;
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::SetPriority( _int priority )
{
	mConnection->SetPriority( priority );
}

template< typename NetworkConnectionType, typename Type >
_int TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetPriority( ) const
{
	return mConnection->GetPriority( );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::RegisterObserver( IObserver* observer )
{
	mConnection->RegisterObserver( observer );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::UnregisterObserver( IObserver* observer )
{
	mConnection->UnregisterObserver( observer );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::NotifyObservers( const IObservable* generator, const EventBase& event )
{
	mConnection->NotifyObservers( generator, event );
}

template< typename NetworkConnectionType, typename Type >
_CONNECTION_STATE TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetConnectionState( ) const
{
	return mConnection->GetConnectionState( );
}

template< typename NetworkConnectionType, typename Type >
_ubool TNetworkProtoBufConnection< NetworkConnectionType, Type >::IsConnecting( ) const
{
	return mConnection->IsConnecting( );
}

template< typename NetworkConnectionType, typename Type >
_ubool TNetworkProtoBufConnection< NetworkConnectionType, Type >::IsConnected( ) const
{
	return mConnection->IsConnected( );
}

template< typename NetworkConnectionType, typename Type >
_ubool TNetworkProtoBufConnection< NetworkConnectionType, Type >::IsConnectionLost( ) const
{
	return mConnection->IsConnectionLost( );
}

template< typename NetworkConnectionType, typename Type >
_ubool TNetworkProtoBufConnection< NetworkConnectionType, Type >::HasFlags( _dword flags, _ubool match_all ) const
{
	return mConnection->HasFlags( flags, match_all );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::EnableFlags( _dword flags, _ubool enable )
{
	mConnection->EnableFlags( flags, enable );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::CombineFlags( _dword flags )
{
	mConnection->CombineFlags( flags );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::ClearFlags( _dword flags )
{
	mConnection->ClearFlags( flags );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::SetFlags( _dword flags )
{
	mConnection->SetFlags( flags );
}

template< typename NetworkConnectionType, typename Type >
_dword TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetFlags( ) const
{
	return mConnection->GetFlags( );
}

template< typename NetworkConnectionType, typename Type >
const FlagsObject& TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetFlagsObject( ) const
{
	return mConnection->GetFlagsObject( );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::SetNotifier( INetworkConnectionNotifier* notifier )
{
	mConnection->SetNotifier( notifier );
}

template< typename NetworkConnectionType, typename Type >
INetworkConnectionNotifier* TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetNotifier( )
{
	return mConnection->GetNotifier( );
}

template< typename NetworkConnectionType, typename Type >
_NETWORK_CONNECTION_TYPE TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetType( ) const
{
	return mConnection->GetType( );
}

template< typename NetworkConnectionType, typename Type >
AStringPtr TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetRootURL( ) const
{
	return mConnection->GetRootURL( );
}

template< typename NetworkConnectionType, typename Type >
_ubool TNetworkProtoBufConnection< NetworkConnectionType, Type >::IsBusy( ) const
{
	return mConnection->IsBusy( );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::SetConnectTimeout( _dword timeout )
{
	mConnection->SetConnectTimeout( timeout );
}

template< typename NetworkConnectionType, typename Type >
_dword TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetConnectTimeout( ) const
{
	return mConnection->GetConnectTimeout( );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::SetLowSpeedLimit( _dword limit_speed_bytes )
{
	mConnection->SetLowSpeedLimit( limit_speed_bytes );
}

template< typename NetworkConnectionType, typename Type >
_dword TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetLowSpeedLimit( ) const
{
	return mConnection->GetLowSpeedLimit( );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::SetMaxUploadSpeed( _qword max_send_bytes )
{
	mConnection->SetMaxUploadSpeed( max_send_bytes );
}

template< typename NetworkConnectionType, typename Type >
_qword TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetMaxUploadSpeed( ) const
{
	return mConnection->GetMaxUploadSpeed( );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::SetMaxDownloadSpeed( _qword max_recv_bytes )
{
	mConnection->SetMaxDownloadSpeed( max_recv_bytes );
}

template< typename NetworkConnectionType, typename Type >
_qword TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetMaxDownloadSpeed( ) const
{
	return mConnection->GetMaxDownloadSpeed( );
}

template< typename NetworkConnectionType, typename Type >
_dword TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetPort( ) const
{
	return mConnection->GetPort( );
}

template< typename NetworkConnectionType, typename Type >
const Address& TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetLocalAddress( ) const
{
	return mConnection->GetLocalAddress( );
}

template< typename NetworkConnectionType, typename Type >
const Address& TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetRemoteAddress( ) const
{
	return mConnection->GetRemoteAddress( );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::SetRequestTime( const Time& time )
{
	mConnection->SetRequestTime( time );
}

template< typename NetworkConnectionType, typename Type >
const Time& TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetRequestTime( ) const
{
	return mConnection->GetRequestTime( );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::SetAutoReconnection( _ubool enable, _dword interval )
{
	mConnection->SetAutoReconnection( enable, interval );
}

template< typename NetworkConnectionType, typename Type >
_dword TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetAutoReconnectionInterval( ) const
{
	return mConnection->GetAutoReconnectionInterval( );
}

template< typename NetworkConnectionType, typename Type >
_ubool TNetworkProtoBufConnection< NetworkConnectionType, Type >::Connect( )
{
	return mConnection->Connect( );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::Disconnect( )
{
	mConnection->Disconnect( );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::Stop( )
{
	mConnection->Stop( );
}

template< typename NetworkConnectionType, typename Type >
_ubool TNetworkProtoBufConnection< NetworkConnectionType, Type >::Send( _dword size, const _byte* buffer )
{
	return mConnection->Send( size, buffer );
}

template< typename NetworkConnectionType, typename Type >
_ubool TNetworkProtoBufConnection< NetworkConnectionType, Type >::SendInstant( _dword size, const _byte* buffer )
{
	return mConnection->SendInstant( size, buffer );
}

template< typename NetworkConnectionType, typename Type >
_ubool TNetworkProtoBufConnection< NetworkConnectionType, Type >::IsRemoteFileExist( WStringPtr filename )
{
	return mConnection->IsRemoteFileExist( filename );
}

template< typename NetworkConnectionType, typename Type >
_ubool TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetRemoteFileLastModifiedTime( WStringPtr filename, Time& time )
{
	return mConnection->GetRemoteFileLastModifiedTime( filename, time );
}

template< typename NetworkConnectionType, typename Type >
INetworkStreamReaderPassRef TNetworkProtoBufConnection< NetworkConnectionType, Type >::OpenRemoteFile( WStringPtr filename, INetworkStreamReaderNotifier* notifier )
{
	return mConnection->OpenRemoteFile( filename, notifier );
}

template< typename NetworkConnectionType, typename Type >
IActionRecorder* TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetConnectActionRecord( )
{
	return mConnection->GetConnectActionRecord( );
}

template< typename NetworkConnectionType, typename Type >
IActionRecorder* TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetSendActionRecord( )
{
	return mConnection->GetSendActionRecord( );
}

template< typename NetworkConnectionType, typename Type >
IActionRecorder* TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetRecvActionRecord( )
{
	return mConnection->GetRecvActionRecord( );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::ProcessDelayConnectOperations( )
{
	mConnection->ProcessDelayConnectOperations( );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::ProcessDelaySendOperations( )
{
	mConnection->ProcessDelaySendOperations( );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::ProcessDelayRecvOperations( )
{
	mConnection->ProcessDelayRecvOperations( );
}

template< typename NetworkConnectionType, typename Type >
_PROCESS_STATE TNetworkProtoBufConnection< NetworkConnectionType, Type >::ProcessConnectAction( )
{
	return mConnection->ProcessConnectAction( );
}

template< typename NetworkConnectionType, typename Type >
_PROCESS_STATE TNetworkProtoBufConnection< NetworkConnectionType, Type >::ProcessRecvAction( IStreamWriter* stream_writer )
{
	return mConnection->ProcessRecvAction( stream_writer );
}

template< typename NetworkConnectionType, typename Type >
_PROCESS_STATE TNetworkProtoBufConnection< NetworkConnectionType, Type >::ProcessSendAction( IStreamReader* stream_reader )
{
	return mConnection->ProcessSendAction( stream_reader );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::SetProtoBufNotifier( INetworkProtoBufConnectionNotifier* notifier )
{
	mNotifier->SetNotifier( notifier );
}

template< typename NetworkConnectionType, typename Type >
INetworkProtoBufConnectionNotifier* TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetProtoBufNotifier( )
{
	return mNotifier->GetNotifier( );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::SetMessageProcessor( IProtoBufMessageProcessor* processor )
{
	mProtoBufProcessor->SetMessageProcessor( processor );
}

template< typename NetworkConnectionType, typename Type >
IProtoBufMessageProcessor* TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetMessageProcessor( )
{
	return mProtoBufProcessor->GetMessageProcessor( );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::SetSender( IProtoBufSender* sender )
{
	mProtoBufProcessor->SetSender( sender );
}

template< typename NetworkConnectionType, typename Type >
IProtoBufSender* TNetworkProtoBufConnection< NetworkConnectionType, Type >::GetSender( )
{
	return mProtoBufProcessor->GetSender( );
}

template< typename NetworkConnectionType, typename Type >
_dword TNetworkProtoBufConnection< NetworkConnectionType, Type >::ParseMessageFromBuffer( const _byte* buffer, _dword size, _dword& msg_id, const _byte*& msg_buf, _dword& msg_size )
{
	return mProtoBufProcessor->ParseMessageFromBuffer( buffer, size, msg_id, msg_buf, msg_size );
}

template< typename NetworkConnectionType, typename Type >
_dword TNetworkProtoBufConnection< NetworkConnectionType, Type >::WriteMessageIntoBuffer( _dword id, IStreamWriter* stream_writer )
{
	return mProtoBufProcessor->WriteMessageIntoBuffer( id, stream_writer );
}

template< typename NetworkConnectionType, typename Type >
_dword TNetworkProtoBufConnection< NetworkConnectionType, Type >::WriteMessageIntoBuffer( _dword id, const google::protobuf::MessageLite& message, IStreamWriter* stream_writer )
{
	return mProtoBufProcessor->WriteMessageIntoBuffer( id, message, stream_writer );
}

template< typename NetworkConnectionType, typename Type >
_dword TNetworkProtoBufConnection< NetworkConnectionType, Type >::WriteMessageIntoBuffer( _dword id, _byte* buffer )
{
	return mProtoBufProcessor->WriteMessageIntoBuffer( id, buffer );
}

template< typename NetworkConnectionType, typename Type >
_dword TNetworkProtoBufConnection< NetworkConnectionType, Type >::WriteMessageIntoBuffer( _dword id, const google::protobuf::MessageLite& message, _byte* buffer )
{
	return mProtoBufProcessor->WriteMessageIntoBuffer( id, message, buffer );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::WriteBuffer( _dword id )
{
	mProtoBufProcessor->WriteBuffer( id );
}

template< typename NetworkConnectionType, typename Type >
_void TNetworkProtoBufConnection< NetworkConnectionType, Type >::WriteBuffer( _dword id, const _byte* buffer, _dword size )
{
	mProtoBufProcessor->WriteBuffer( id, buffer, size );
}

template< typename NetworkConnectionType, typename Type >
_ubool TNetworkProtoBufConnection< NetworkConnectionType, Type >::PostBuffer( AStringPtr url_name, const AStringArray& header_list, _dword id, const QwordParameters4& parameters )
{
	return mProtoBufProcessor->PostBuffer( url_name, header_list, id, parameters );
}

template< typename NetworkConnectionType, typename Type >
_ubool TNetworkProtoBufConnection< NetworkConnectionType, Type >::PostBuffer( AStringPtr url_name, const AStringArray& header_list, _dword id, const _byte* buffer, _dword size, const QwordParameters4& parameters )
{
	return mProtoBufProcessor->PostBuffer( url_name, header_list, id, buffer, size, parameters );
}

}