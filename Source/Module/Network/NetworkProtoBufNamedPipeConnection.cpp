//! @file     NetworkProtoBufNamedPipeConnection.cpp
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// NetworkProtoBufNamedPipeSender Implementation
//----------------------------------------------------------------------------

NetworkProtoBufNamedPipeSender::NetworkProtoBufNamedPipeSender( INetworkNamedPipeConnection* connection )
{
	mConnection = connection;
}

NetworkProtoBufNamedPipeSender::~NetworkProtoBufNamedPipeSender( )
{
}

_void NetworkProtoBufNamedPipeSender::Send( const _byte* buffer, _dword size )
{
	mConnection->Send( size, buffer );
}

_ubool NetworkProtoBufNamedPipeSender::Post( AStringPtr url_name, const AStringArray& header_list, const _byte* buffer, _dword size, const QwordParameters4& parameters )
{
	EGE_ASSERT( 0 );
	return _false;
}

//----------------------------------------------------------------------------
// NetworkProtoBufNamedPipeConnection Implementation
//----------------------------------------------------------------------------

NetworkProtoBufNamedPipeConnection::NetworkProtoBufNamedPipeConnection( )
{
	mSender = new NetworkProtoBufNamedPipeSender( this );
}

NetworkProtoBufNamedPipeConnection::~NetworkProtoBufNamedPipeConnection( )
{
	EGE_RELEASE( mSender );
}

_ubool NetworkProtoBufNamedPipeConnection::Initialize( WStringPtr pipename, _ubool thread_alone_mode )
{
	mConnection = GetNetworkResourceManager( )->CreateNamedPipeConnection( pipename, mNotifier, thread_alone_mode );
	if ( mConnection.IsNull( ) )
		return _false;

	mProtoBufProcessor->SetSender( mSender );

	return _true;
}

_void NetworkProtoBufNamedPipeConnection::SendMessage( _dword id, const google::protobuf::MessageLite& message )
{
	// Create buffer to save binary data of message
	MemArrayPtr< _byte > temp_buf;
	if ( CreateTempBuf( temp_buf, message ) == _false )
		return;

	mProtoBufProcessor->WriteBuffer( id, temp_buf.GetPointer( ), temp_buf.SizeOfBytes( ) );
}