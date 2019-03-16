//! @file     NetworkConnectOperation.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// NetworkConnectOperation Implementation
//----------------------------------------------------------------------------

NetworkConnectOperation::NetworkConnectOperation( INetworkConnection* connection ) : BaseClass( connection )
{
	mStartTime = 0;
}

NetworkConnectOperation::~NetworkConnectOperation( )
{
}

_PROCESS_STATE NetworkConnectOperation::OnProcess( )
{
	// If the connection had established then skip it
	if ( mConnection->IsConnected( ) )
		return _PS_FINISHED;

	// Process connection operation
	switch ( mConnection->GetType( ) )
	{
		case _NETWORK_CONNECTION_TCP:
		case _NETWORK_CONNECTION_BLUETOOTH:
		case _NETWORK_CONNECTION_NAMED_PIPE:
		{
			// Enable the auto-connection feature
			if ( mConnection->HasFlags( INetworkConnection::_FLAG_AUTO_CONNECTION ) )
			{
				if ( mStartTime == 0 )
					mStartTime = Platform::GetCurrentTickCount( ) + mConnection->GetAutoReconnectionInterval( );

				if ( Platform::GetCurrentTickCount( ) >= mStartTime )
					return mConnection->ProcessConnectAction( );
				else
					return _PS_CONTINUE;
			}
			// Disable the auto-connection feature
			else
			{
				return mConnection->ProcessConnectAction( );
			}
		}
		break;

		case _NETWORK_CONNECTION_HTTP:
		{

		}
		break;

		default:
			return _PS_ERROR;
	}

	return _PS_FINISHED;
}

_NETWORK_OPERATION_TYPE NetworkConnectOperation::GetType( ) const
{
	return _NETWORK_OPERATION_CONNECT;
}
