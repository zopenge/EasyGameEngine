//! @file     NetworkProtoBufTCPConnection.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkProtoBufTCPSender
//----------------------------------------------------------------------------
	
class NetworkProtoBufTCPSender : public TObject< IProtoBufSender >
{
private:
	INetworkTCPConnection*	mConnection;

public:
	NetworkProtoBufTCPSender( INetworkTCPConnection* connection );
	virtual ~NetworkProtoBufTCPSender( );

// IProtoBufSender Interface
public:
	virtual _void	Send( const _byte* buffer, _dword size ) override;
	virtual _ubool	Post( AStringPtr url_name, const AStringArray& header_list, const _byte* buffer, _dword size, const QwordParameters4& parameters ) override;
};

//----------------------------------------------------------------------------
// NetworkProtoBufTCPConnection
//----------------------------------------------------------------------------

class NetworkProtoBufTCPConnection : public TNetworkProtoBufConnection< INetworkTCPConnection, INetworkProtoBufTCPConnection >
{
private:
	typedef TNetworkProtoBufConnection< INetworkTCPConnection, INetworkProtoBufTCPConnection > BaseClass;

private:
	NetworkProtoBufTCPSender*	mSender;

public:
	NetworkProtoBufTCPConnection( );
	virtual ~NetworkProtoBufTCPConnection( );

public:
	//!	Initialize.
	_ubool Initialize( const Address& remote_address, _ubool thread_alone_mode );

// INetworkTCPConnection Interface
public:

// INetworkProtoBufTCPConnection Interface
public:
	virtual _void SendMessage( _dword id, const google::protobuf::MessageLite& message ) override;
};

}