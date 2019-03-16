//! @file     NetworkConnectionNotifier.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// NetworkConnectionNotifier Implementation
//----------------------------------------------------------------------------

NetworkConnectionNotifier::NetworkConnectionNotifier( INetworkConnectionNotifier* notifier )
{
	mNotifier = notifier;
}

NetworkConnectionNotifier::~NetworkConnectionNotifier( )
{
}

_void NetworkConnectionNotifier::OnUpdateState( _CONNECTION_STATE state )
{
	mNotifier->OnUpdateState( state );
}

_void NetworkConnectionNotifier::OnError( const NetworkErrorDesc& err_desc, const QwordParameters4& parameters )
{
	mNotifier->OnError( err_desc, parameters );
}

_void NetworkConnectionNotifier::OnDebugBuffer( _NETWORK_DEBUG_TYPE type, const _chara* buffer, _dword size, const QwordParameters4& parameters )
{
	mNotifier->OnDebugBuffer( type, buffer, size, parameters );
}

_dword NetworkConnectionNotifier::OnRecvBuffer( _dword size, const _byte* buffer, const QwordParameters4& parameters )
{
	if ( GetNetworkModule( )->IsEnableOptions( _NETWORK_OPTION_ENABLE_SIMULATING_LAG ) )
	{
		_dword sleep_time = Random::Gen( GetNetworkModule( )->GetSimulatingLag( ) );
		Platform::Sleep( sleep_time );
	}

	return mNotifier->OnRecvBuffer( size, buffer, parameters );
}

_void NetworkConnectionNotifier::OnSendBuffer( _dword size, const _byte* buffer, const QwordParameters4& parameters )
{
	mNotifier->OnSendBuffer( size, buffer, parameters );
}

_void NetworkConnectionNotifier::OnHeaderBuffer( _dword size, const _chara* buffer, const QwordParameters4& parameters )
{
	mNotifier->OnHeaderBuffer( size, buffer, parameters );
}

_void NetworkConnectionNotifier::OnProgressBuffer( _double dltotal, _double dlnow, _double ultotal, _double ulnow, const QwordParameters4& parameters )
{
	mNotifier->OnProgressBuffer( dltotal, dlnow, ultotal, ulnow, parameters );
}

_void NetworkConnectionNotifier::OnFinishBuffer( const QwordParameters4& parameters )
{
	mNotifier->OnFinishBuffer( parameters );
}
