//! @file     NetworkProtoBufNamedPipeConnection.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkProtoBufNamedPipeSender
//----------------------------------------------------------------------------
	
class NetworkProtoBufNamedPipeSender : public TObject< IProtoBufSender >
{
private:
	INetworkNamedPipeConnection*	mConnection;

public:
	NetworkProtoBufNamedPipeSender( INetworkNamedPipeConnection* connection );
	virtual ~NetworkProtoBufNamedPipeSender( );

// IProtoBufSender Interface
public:
	virtual _void	Send( const _byte* buffer, _dword size ) override;
	virtual _ubool	Post( AStringPtr url_name, const AStringArray& header_list, const _byte* buffer, _dword size, const QwordParameters4& parameters ) override;
};

//----------------------------------------------------------------------------
// NetworkProtoBufNamedPipeConnection
//----------------------------------------------------------------------------

class NetworkProtoBufNamedPipeConnection : public TNetworkProtoBufConnection< INetworkNamedPipeConnection, INetworkProtoBufNamedPipeConnection >
{
private:
	typedef TNetworkProtoBufConnection< INetworkNamedPipeConnection, INetworkProtoBufNamedPipeConnection > BaseClass;

private:
	NetworkProtoBufNamedPipeSender*	mSender;

public:
	NetworkProtoBufNamedPipeConnection( );
	virtual ~NetworkProtoBufNamedPipeConnection( );

public:
	//!	Initialize.
	_ubool Initialize( WStringPtr pipename, _ubool thread_alone_mode );

// INetworkNamedPipeConnection Interface
public:

// INetworkProtoBufNamedPipeConnection Interface
public:
	virtual _void SendMessage( _dword id, const google::protobuf::MessageLite& message ) override;
};

}