//! @file     INetworkProtoBufConnection.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// INetworkProtoBufConnectionNotifier
//----------------------------------------------------------------------------

class INetworkProtoBufConnectionNotifier : public IObject
{
public:
	//!	When update connection state.
	//!	@param		state		The current connection state.
	//!	@param		parameters	The user defined parameters.
	//!	@return		none.
	virtual _void OnUpdateState( _CONNECTION_STATE state ) PURE;

	//!	When error occurs.
	//!	@param		err_desc	The error description.
	//!	@param		parameters	The user defined parameters.
	//!	@return		none.
	virtual _void OnErrorOccurs( const NetworkErrorDesc& err_desc, const QwordParameters4& parameters ) PURE;

	//!	When handle message.
	//!	@param		msg_id		The message ID.
	//!	@param		msg_buf		The message buffer data.
	//!	@param		msg_size	The message buffer size in bytes.
	//!	@param		parameters	The user defined parameters.
	//!	@return		none.
	virtual _void OnHandleBinaryMessage( _dword msg_id, const _byte* msg_buf, _dword msg_size, const QwordParameters4& parameters ) PURE;
};

//----------------------------------------------------------------------------
// ITNetworkProtoBufConnection
//----------------------------------------------------------------------------

template< typename Type >
class ITNetworkProtoBufConnection : public Type
{
public:
	//!	Set the notifier.
	//!	@param		notifier	The notifier.
	//!	@return		none.
	virtual _void SetProtoBufNotifier( INetworkProtoBufConnectionNotifier* notifier ) PURE;
	//!	Get the notifier.
	//!	@param		none.
	//!	@return		The notifier.
	virtual INetworkProtoBufConnectionNotifier* GetProtoBufNotifier( ) PURE;
};

//----------------------------------------------------------------------------
// INetworkProtoBufTCPConnection
//----------------------------------------------------------------------------

class INetworkProtoBufTCPConnection : public ITNetworkProtoBufConnection< ITProtoBufProcessor< INetworkTCPConnection > >
{
public:
	//!	Send message in google-protobuf-format.
	//!	@param		id			The request ID.
	//!	@param		message		The message in google-protobuf format.
	//!	@return		none.
	virtual _void SendMessage( _dword id, const google::protobuf::MessageLite& message ) PURE;
};

//----------------------------------------------------------------------------
// INetworkProtoBufHTTPConnection
//----------------------------------------------------------------------------

class INetworkProtoBufHTTPConnection : public ITNetworkProtoBufConnection< ITProtoBufProcessor< INetworkHTTPConnection > >
{
public:
	//!	Post message in google-protobuf-format.
	//!	@param		url_name		The sub url name.
	//!	@param		id				The request ID.
	//!	@param		message			The message in google-protobuf format.
	//!	@param		parameters	The user defined parameters.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool PostMessage( AStringPtr url_name, _dword id, const google::protobuf::MessageLite& message, const QwordParameters4& parameters = QwordParameters4::cNull ) PURE;
	//!	Post message in google-protobuf-format.
	//!	@param		url_name		The sub url name.
	//!	@param		header_list		The HTTP header list.
	//!	@param		id				The request ID.
	//!	@param		message			The message in google-protobuf format.
	//!	@param		parameters	The user defined parameters.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool PostMessage( AStringPtr url_name, const AStringArray& header_list, _dword id, const google::protobuf::MessageLite& message, const QwordParameters4& parameters = QwordParameters4::cNull ) PURE;
};

//----------------------------------------------------------------------------
// INetworkProtoBufNamePipeConnection
//----------------------------------------------------------------------------

class INetworkProtoBufNamedPipeConnection : public ITNetworkProtoBufConnection< ITProtoBufProcessor< INetworkNamedPipeConnection > >
{
public:
	//!	Send message in google-protobuf-format.
	//!	@param		id			The request ID.
	//!	@param		message		The message in google-protobuf format.
	//!	@return		none.
	virtual _void SendMessage( _dword id, const google::protobuf::MessageLite& message ) PURE;
};

}