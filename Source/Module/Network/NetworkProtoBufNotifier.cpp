//! @file     NetworkProtoBufNotifier.cpp
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// NetworkProtoBufNotifier Implementation
//----------------------------------------------------------------------------

NetworkProtoBufNotifier::NetworkProtoBufNotifier( IProtoBufProcessor* processor )
{
	mProcessor = processor;
}

NetworkProtoBufNotifier::~NetworkProtoBufNotifier( )
{
}

_void NetworkProtoBufNotifier::SetNotifier( INetworkProtoBufConnectionNotifier* notifier )
{
	if ( notifier == _null )
		mNotifier = &NullNetwork::GetInstance( ).GetNetworkProtoBufConnectionNotifier( );
	else
		mNotifier = notifier;
}

INetworkProtoBufConnectionNotifier* NetworkProtoBufNotifier::GetNotifier( )
{
	return mNotifier;
}

_void NetworkProtoBufNotifier::OnUpdateState( _CONNECTION_STATE state )
{
	mNotifier->OnUpdateState( state );
}

_void NetworkProtoBufNotifier::OnError( const NetworkErrorDesc& err_desc, const QwordParameters4& parameters )
{
	mNotifier->OnErrorOccurs( err_desc, parameters );
}

_void NetworkProtoBufNotifier::OnDebugBuffer( _NETWORK_DEBUG_TYPE type, const _chara* buffer, _dword size, const QwordParameters4& parameters )
{

}

_dword NetworkProtoBufNotifier::OnRecvBuffer( _dword size, const _byte* buffer, const QwordParameters4& parameters )
{
	// The message info
	_dword			msg_id		= 0;
	const _byte*	msg_buf		= _null;
	_dword			msg_size	= 0;

	// Read message from buffer, we can not use this size to feedback because it not equal to input size
	_dword read_size = mProcessor->ParseMessageFromBuffer( buffer, size, msg_id, msg_buf, msg_size );
	if ( read_size == 0 )
		return 0;

	// Notify outside
	mNotifier->OnHandleBinaryMessage( msg_id, msg_buf, msg_size, parameters );

	// Feedback the read size
	return size;
}

_void NetworkProtoBufNotifier::OnSendBuffer( _dword size, const _byte* buffer, const QwordParameters4& parameters )
{

}

_void NetworkProtoBufNotifier::OnHeaderBuffer( _dword size, const _chara* buffer, const QwordParameters4& parameters )
{

}

_void NetworkProtoBufNotifier::OnProgressBuffer( _double dltotal, _double dlnow, _double ultotal, _double ulnow, const QwordParameters4& parameters )
{

}

_void NetworkProtoBufNotifier::OnFinishBuffer( const QwordParameters4& parameters )
{

}
