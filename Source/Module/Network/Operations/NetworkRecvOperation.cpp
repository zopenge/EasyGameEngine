//! @file     NetworkRecvOperation.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// NetworkRecvOperation Implementation
//----------------------------------------------------------------------------

NetworkRecvOperation::NetworkRecvOperation( INetworkConnection* connection ) : BaseClass( connection )
{
	mStreamWriter	= GetInterfaceFactory( )->CreateMemStreamWriter( 256 KB );
}

NetworkRecvOperation::~NetworkRecvOperation( )
{
}

_PROCESS_STATE NetworkRecvOperation::OnProcess( )
{
	// Skip to read buffer when it's connecting
	if ( mConnection->IsConnecting( ) )
		return _PS_CONTINUE;

	switch ( mConnection->GetType( ) )
	{
		case _NETWORK_CONNECTION_TCP:
		case _NETWORK_CONNECTION_BLUETOOTH:
		case _NETWORK_CONNECTION_NAMED_PIPE:
		{
			// Process recv action
			return mConnection->ProcessRecvAction( mStreamWriter );
		}
		break;

		case _NETWORK_CONNECTION_HTTP:
		{

		}
		break;

		default:
			break;
	}

	return _PS_FINISHED;
}

_NETWORK_OPERATION_TYPE NetworkRecvOperation::GetType( ) const
{
	return _NETWORK_OPERATION_RECV;
}
