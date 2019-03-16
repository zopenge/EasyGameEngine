//! @file     NetworkKeepAliveOperation.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// NetworkKeepAliveOperation Implementation
//----------------------------------------------------------------------------

NetworkKeepAliveOperation::NetworkKeepAliveOperation( INetworkConnection* connection ) : BaseClass( connection )
{
	mLastTickcount			= 0;

	mCounter				= 0;

	mProtocolBufProcessor	= GetInterfaceFactory( )->CreateProtoBufProcessor( );
}

NetworkKeepAliveOperation::~NetworkKeepAliveOperation( )
{
}

_PROCESS_STATE NetworkKeepAliveOperation::OnProcess( )
{
	// Get the connection state
	_CONNECTION_STATE connection_state = mConnection->GetConnectionState( );
	
	// Only process keep alive packet with connected state
	if ( connection_state == _CS_CONNECTED )
	{
		switch ( mConnection->GetType( ) )
		{
			case _NETWORK_CONNECTION_TCP:
			{
				// Get the current tickcount
				_dword cur_tickcount = Platform::GetCurrentTickCount( );
				if ( cur_tickcount - mLastTickcount > (NetworkPacket::KEEP_ALIVE_CHECK_INTERVAL / 4) )
				{
					mLastTickcount = cur_tickcount;

					NetworkPacket::KeepAliveInfo keep_alive_info;
					keep_alive_info.set_number( ++ mCounter );

					_byte buffer[128];
					_dword size = mProtocolBufProcessor->WriteMessageIntoBuffer( NetworkPacket::MT_KEEP_ALIVE, keep_alive_info, buffer );
					if ( size == 0 )
						return _PS_ERROR;

					IStreamReaderRef stream_reader = GetInterfaceFactory( )->CreateMemStreamReader( buffer, size, _STREAM_SHARE_MODE_READ_ONLY );
					if ( stream_reader.IsNull( ) )
						return _PS_ERROR;

					mConnection->ProcessSendAction( stream_reader );
				}
			}
			break;

			case _NETWORK_CONNECTION_BLUETOOTH:
			case _NETWORK_CONNECTION_NAMED_PIPE:
			case _NETWORK_CONNECTION_HTTP:
			{

			}
			break;

			default:
				return _PS_ERROR;
		}
	}

	// Always keep it
	return _PS_CONTINUE;
}

_NETWORK_OPERATION_TYPE NetworkKeepAliveOperation::GetType( ) const
{
	return _NETWORK_OPERATION_SEND;
}
