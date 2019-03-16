//! @file     NetworkNamedPipeStation.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkNamedPipeStation
//----------------------------------------------------------------------------

class NetworkNamedPipeStation : public TNetworkStation< INetworkStation, Pipe* >
{
private:
	typedef TNetworkStation< INetworkStation, Pipe* > BaseClass;

private:
	//!	Build candidate named pipe's name
	WString BuildCandidateName( _dword index ) const;

// TNetworkStation Interface
private:
	virtual _dword	OnGetAvailableBytes( const SocketInfo& socket_info ) override;
	virtual _dword	OnRecv( SocketInfo& socket_info, _byte* buffer, _dword size ) override;
	virtual _dword	OnSend( SocketInfo& socket_info, const _byte* buffer, _dword size ) override;
	virtual _void	OnClose( SocketInfo& socket_info ) override;

	virtual _void	OnDownload( ) override;
	virtual _void	OnUpload( ) override;

public:
	NetworkNamedPipeStation( );
	virtual ~NetworkNamedPipeStation( );

public:
	//!	Initialize.
	_ubool Initialize( WStringPtr pipename, _dword type, _dword size, _dword timeout );

// INetworkStation Interface
public:
};

//----------------------------------------------------------------------------
// NetworkNamedPipeStation Implementation
//----------------------------------------------------------------------------

}