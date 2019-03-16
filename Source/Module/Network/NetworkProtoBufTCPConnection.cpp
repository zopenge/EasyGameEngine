//! @file     NetworkProtoBufTCPConnection.cpp
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// NetworkProtoBufTCPSender Implementation
//----------------------------------------------------------------------------

NetworkProtoBufTCPSender::NetworkProtoBufTCPSender( INetworkTCPConnection* connection )
{
	mConnection = connection;
}

NetworkProtoBufTCPSender::~NetworkProtoBufTCPSender( )
{
}

_void NetworkProtoBufTCPSender::Send( const _byte* buffer, _dword size )
{
	mConnection->Send( size, buffer );
}

_ubool NetworkProtoBufTCPSender::Post( AStringPtr url_name, const AStringArray& header_list, const _byte* buffer, _dword size, const QwordParameters4& parameters )
{
	EGE_ASSERT( 0 );
	return _false;
}

//----------------------------------------------------------------------------
// NetworkProtoBufTCPConnection Implementation
//----------------------------------------------------------------------------

NetworkProtoBufTCPConnection::NetworkProtoBufTCPConnection( )
{
	mSender = new NetworkProtoBufTCPSender( this );
}

NetworkProtoBufTCPConnection::~NetworkProtoBufTCPConnection( )
{
	EGE_RELEASE( mSender );
}

_ubool NetworkProtoBufTCPConnection::Initialize( const Address& remote_address, _ubool thread_alone_mode )
{
	mConnection = GetNetworkResourceManager( )->CreateTCPConnection( remote_address, mNotifier, thread_alone_mode );
	if ( mConnection.IsNull( ) )
		return _false;

	mProtoBufProcessor->SetSender( mSender );

	return _true;
}

_void NetworkProtoBufTCPConnection::SendMessage( _dword id, const google::protobuf::MessageLite& message )
{
	// Create buffer to save binary data of message
	MemArrayPtr< _byte > temp_buf;
	if ( CreateTempBuf( temp_buf, message ) == _false )
		return;

	mProtoBufProcessor->WriteBuffer( id, temp_buf.GetPointer( ), temp_buf.SizeOfBytes( ) );
}