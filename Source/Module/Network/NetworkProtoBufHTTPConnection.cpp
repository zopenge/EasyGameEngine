//! @file     NetworkProtoBufHTTPConnection.cpp
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// NetworkProtoBufHTTPSender Implementation
//----------------------------------------------------------------------------

NetworkProtoBufHTTPSender::NetworkProtoBufHTTPSender( INetworkHTTPConnection* connection )
{
	mConnection = connection;
}

NetworkProtoBufHTTPSender::~NetworkProtoBufHTTPSender( )
{
}

_void NetworkProtoBufHTTPSender::Send( const _byte* buffer, _dword size )
{
	EGE_ASSERT( 0 );
}

_ubool NetworkProtoBufHTTPSender::Post( AStringPtr url_name, const AStringArray& header_list, const _byte* buffer, _dword size, const QwordParameters4& parameters )
{
	return mConnection->Post( url_name, header_list, buffer, size, parameters );
}

//----------------------------------------------------------------------------
// NetworkProtoBufHTTPConnection Implementation
//----------------------------------------------------------------------------

NetworkProtoBufHTTPConnection::NetworkProtoBufHTTPConnection( )
{
	mSender = new NetworkProtoBufHTTPSender( this );
}

NetworkProtoBufHTTPConnection::~NetworkProtoBufHTTPConnection( )
{
	EGE_RELEASE( mSender );
}

_ubool NetworkProtoBufHTTPConnection::Initialize( WStringPtr url_address, _ubool thread_alone_mode )
{
	mConnection = GetNetworkResourceManager( )->CreateHTTPConnection( url_address, mNotifier, thread_alone_mode );
	if ( mConnection.IsNull( ) )
		return _false;

	mProtoBufProcessor->SetSender( mSender );

	return _true;
}

_ubool NetworkProtoBufHTTPConnection::SetSSLKeyFromFile( WStringPtr filename )
{
	return mConnection->SetSSLKeyFromFile( filename );
}

_ubool NetworkProtoBufHTTPConnection::SetSSLCertFromFile( WStringPtr filename )
{
	return mConnection->SetSSLCertFromFile( filename );
}

_ubool NetworkProtoBufHTTPConnection::SetSSLKeyFromStream( IStreamReader* stream_reader )
{
	return mConnection->SetSSLKeyFromStream( stream_reader );
}

_ubool NetworkProtoBufHTTPConnection::SetSSLCertFromStream( IStreamReader* stream_reader )
{
	return mConnection->SetSSLCertFromStream( stream_reader );
}

_ubool NetworkProtoBufHTTPConnection::SetCACertFromFile( WStringPtr filename )
{
	return mConnection->SetCACertFromFile( filename );
}

_ubool NetworkProtoBufHTTPConnection::SetCACertFromStream( IStreamReader* stream_reader )
{
	return mConnection->SetCACertFromStream( stream_reader );
}

_ubool NetworkProtoBufHTTPConnection::Get( AStringPtr url_name, AStringPtr get_field, const QwordParameters4& parameters )
{
	return mConnection->Get( url_name, get_field, parameters );
}

_ubool NetworkProtoBufHTTPConnection::Get( AStringPtr url_name, const AStringArray& header_list, AStringPtr get_field, const QwordParameters4& parameters )
{
	return mConnection->Get( url_name, header_list, get_field, parameters );
}

_ubool NetworkProtoBufHTTPConnection::GetWithNoBody( AStringPtr url_name )
{
	return mConnection->GetWithNoBody( url_name );
}

_ubool NetworkProtoBufHTTPConnection::Post( AStringPtr url_name, AStringPtr post_field, const QwordParameters4& parameters )
{
	return mConnection->Post( url_name, post_field, parameters );
}

_ubool NetworkProtoBufHTTPConnection::Post( AStringPtr url_name, const AStringArray& header_list, AStringPtr post_field, const QwordParameters4& parameters )
{
	return mConnection->Post( url_name, header_list, post_field, parameters );
}

_ubool NetworkProtoBufHTTPConnection::Post( AStringPtr url_name, const _byte* buffer, _dword size, const QwordParameters4& parameters )
{
	return mConnection->Post( url_name, buffer, size, parameters );
}

_ubool NetworkProtoBufHTTPConnection::Post( AStringPtr url_name, const AStringArray& header_list, const _byte* buffer, _dword size, const QwordParameters4& parameters )
{
	return mConnection->Post( url_name, header_list, buffer, size, parameters );
}

_ubool NetworkProtoBufHTTPConnection::PostMessage( AStringPtr url_name, _dword id, const google::protobuf::MessageLite& message, const QwordParameters4& parameters )
{
	static AStringArray sNullHeaderList;
	return PostMessage( url_name, sNullHeaderList, id, message, parameters );
}

_ubool NetworkProtoBufHTTPConnection::PostMessage( AStringPtr url_name, const AStringArray& header_list, _dword id, const google::protobuf::MessageLite& message, const QwordParameters4& parameters )
{
	// Create buffer to save binary data of message
	MemArrayPtr< _byte > temp_buf;
	if ( CreateTempBuf( temp_buf, message ) == _false )
		return _false;

	return mProtoBufProcessor->PostBuffer( url_name, header_list, id, temp_buf.GetPointer( ), temp_buf.SizeOfBytes( ), parameters );
}
