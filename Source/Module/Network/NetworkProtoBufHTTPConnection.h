//! @file     NetworkProtoBufHTTPConnection.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkProtoBufHTTPSender
//----------------------------------------------------------------------------
	
class NetworkProtoBufHTTPSender : public TObject< IProtoBufSender >
{
private:
	INetworkHTTPConnection*	mConnection;

public:
	NetworkProtoBufHTTPSender( INetworkHTTPConnection* connection );
	virtual ~NetworkProtoBufHTTPSender( );

// IProtoBufSender Interface
public:
	virtual _void	Send( const _byte* buffer, _dword size ) override;
	virtual _ubool	Post( AStringPtr url_name, const AStringArray& header_list, const _byte* buffer, _dword size, const QwordParameters4& parameters ) override;
};

//----------------------------------------------------------------------------
// NetworkProtoBufHTTPConnection
//----------------------------------------------------------------------------

class NetworkProtoBufHTTPConnection : public TNetworkProtoBufConnection< INetworkHTTPConnection, INetworkProtoBufHTTPConnection >
{
private:
	typedef TNetworkProtoBufConnection< INetworkHTTPConnection, INetworkProtoBufHTTPConnection > BaseClass;

private:
	NetworkProtoBufHTTPSender*	mSender;

public:
	NetworkProtoBufHTTPConnection( );
	virtual ~NetworkProtoBufHTTPConnection( );

public:
	//!	Initialize.
	_ubool Initialize( WStringPtr url_address, _ubool thread_alone_mode );

// INetworkHTTPConnection Interface
public:
	virtual _ubool	SetSSLKeyFromFile( WStringPtr filename ) override;
	virtual _ubool	SetSSLCertFromFile( WStringPtr filename ) override;
	virtual _ubool	SetSSLKeyFromStream( IStreamReader* stream_reader ) override;
	virtual _ubool	SetSSLCertFromStream( IStreamReader* stream_reader ) override;

	virtual _ubool	SetCACertFromFile( WStringPtr filename ) override;
	virtual _ubool	SetCACertFromStream( IStreamReader* stream_reader ) override;

	virtual _ubool	Get( AStringPtr url_name, AStringPtr get_field, const QwordParameters4& parameters = QwordParameters4::cNull ) override;
	virtual _ubool	Get( AStringPtr url_name, const AStringArray& header_list, AStringPtr get_field, const QwordParameters4& parameters = QwordParameters4::cNull ) override;
	virtual _ubool	GetWithNoBody( AStringPtr url_name ) override;

	virtual _ubool	Post( AStringPtr url_name, AStringPtr post_field, const QwordParameters4& parameters ) override;
	virtual _ubool	Post( AStringPtr url_name, const AStringArray& header_list, AStringPtr post_field, const QwordParameters4& parameters ) override;
	virtual _ubool	Post( AStringPtr url_name, const _byte* buffer, _dword size, const QwordParameters4& parameters = QwordParameters4::cNull ) override;
	virtual _ubool	Post( AStringPtr url_name, const AStringArray& header_list, const _byte* buffer, _dword size, const QwordParameters4& parameters = QwordParameters4::cNull ) override;

// INetworkProtoBufHTTPConnection Interface
public:
	virtual _ubool	PostMessage( AStringPtr url_name, _dword id, const google::protobuf::MessageLite& message, const QwordParameters4& parameters ) override;
	virtual _ubool	PostMessage( AStringPtr url_name, const AStringArray& header_list, _dword id, const google::protobuf::MessageLite& message, const QwordParameters4& parameters ) override;
};

}