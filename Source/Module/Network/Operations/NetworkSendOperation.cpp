//! @file     NetworkSendOperation.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// NetworkSendOperation Implementation
//----------------------------------------------------------------------------

NetworkSendOperation::NetworkSendOperation( INetworkConnection* connection, _dword size, const _byte* buffer ) : BaseClass( connection )
{
	EGE_ASSERT( size != 0 && buffer != _null );

	// Create the first data chunk
	mDataChunks.Append( DataChunkInfo( size, buffer ) );
}

NetworkSendOperation::~NetworkSendOperation( )
{
}

_ubool NetworkSendOperation::IsNeedRemoveDataChunk( _PROCESS_STATE state ) const
{
	switch ( state )
	{
		case _PS_ERROR:
		case _PS_SKIPPED:
		case _PS_ABORTED:
		case _PS_TIMEOUT:
		case _PS_FINISHED:
			return _true;

		default:
			break;
	}

	return _false;
}

_PROCESS_STATE NetworkSendOperation::OnProcess( )
{
	// Skip to send buffer when it's disconnected
	if ( mConnection->IsConnectionLost( ) )
		return _PS_ERROR;
	else if ( mConnection->IsConnecting( ) )
		return _PS_CONTINUE;

	switch ( mConnection->GetType( ) )
	{
		case _NETWORK_CONNECTION_TCP:
		case _NETWORK_CONNECTION_BLUETOOTH:
		case _NETWORK_CONNECTION_NAMED_PIPE:
		{
			if ( mDataChunks.Number( ) != 0 )
			{
				_PROCESS_STATE state = mConnection->ProcessSendAction( mDataChunks[0].mStreamReader );
				if ( IsNeedRemoveDataChunk( state ) )
					mDataChunks.RemoveByIndex( 0 );
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

	return _PS_CONTINUE;
}

_NETWORK_OPERATION_TYPE NetworkSendOperation::GetType( ) const
{
	return _NETWORK_OPERATION_SEND;
}

_ubool NetworkSendOperation::CombineBuffer( _dword size, const _byte* buffer )
{
	LockOwner lock_owner( mLocker );

	// Add the data chunk
	mDataChunks.Append( DataChunkInfo( size, buffer ) );

	return _true;
}

_void NetworkSendOperation::RemoveProcessingBuffers( )
{
	LockOwner lock_owner( mLocker );

	// Remove the combined buffer offset if we finished combined buffer
	for ( _dword i = 0; i < mDataChunks.Number( ); i ++ )
	{
		const DataChunkInfo& chunk_info = mDataChunks[i];

		if ( chunk_info.mStreamReader->GetOffset( ) != 0 )
			mDataChunks.RemoveByIndex( i -- );
	}
}