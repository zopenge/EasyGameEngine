//! @file     NetworkNamedPipeConnection.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkNamedPipeConnection
//----------------------------------------------------------------------------

class NetworkNamedPipeConnection : public TNetworkConnection< INetworkNamedPipeConnection >
{
private:
	typedef TNetworkConnection< INetworkNamedPipeConnection > BaseClass;

private:
	//!	The pipe name
	WString	mPipeName;
	//!	The named pipe
	Pipe	mPipe;

// TNetworkConnection Interface
private:
	virtual _ubool	OnConnect( ) override;
	virtual _dword	OnRecv( _byte* buffer, _dword size ) override;
	virtual _dword	OnSend( const _byte* buffer, _dword size ) override;

public:
	NetworkNamedPipeConnection( INetworkConnectionThread* connection_thread );
	virtual ~NetworkNamedPipeConnection( );

public:
	//!	Initialize.
	_ubool Initialize( WStringPtr pipename );

// INetworkConnection Interface
public:
	virtual _NETWORK_CONNECTION_TYPE	GetType( ) const override;

	virtual _void						Disconnect( ) override;

	virtual _void						Stop( ) override;
};

//----------------------------------------------------------------------------
// NetworkNamedPipeConnection Implementation
//----------------------------------------------------------------------------

}