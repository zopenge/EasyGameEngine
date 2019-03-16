//! @file     NetworkConnectionNotifier.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkConnectionNotifier
//----------------------------------------------------------------------------

class NetworkConnectionNotifier : public TObject< INetworkConnectionNotifier >
{
private:
	INetworkConnectionNotifierRef	mNotifier;

public:
	NetworkConnectionNotifier( INetworkConnectionNotifier* notifier );
	virtual ~NetworkConnectionNotifier( );

// INetworkConnectionNotifier Interface
public:
	virtual _void	OnUpdateState( _CONNECTION_STATE state ) override;
	virtual _void	OnError( const NetworkErrorDesc& err_desc, const QwordParameters4& parameters ) override;

	virtual _void	OnDebugBuffer( _NETWORK_DEBUG_TYPE type, const _chara* buffer, _dword size, const QwordParameters4& parameters ) override;
	virtual _dword	OnRecvBuffer( _dword size, const _byte* buffer, const QwordParameters4& parameters ) override;
	virtual _void	OnSendBuffer( _dword size, const _byte* buffer, const QwordParameters4& parameters ) override;
	virtual _void	OnHeaderBuffer( _dword size, const _chara* buffer, const QwordParameters4& parameters ) override;
	virtual _void	OnProgressBuffer( _double dltotal, _double dlnow, _double ultotal, _double ulnow, const QwordParameters4& parameters ) override;
	virtual _void	OnFinishBuffer( const QwordParameters4& parameters ) override;
};

//----------------------------------------------------------------------------
// NetworkConnectionNotifier Implementation
//----------------------------------------------------------------------------

}