//! @file     IProtoBufProcessor.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IProtoBufSender
//----------------------------------------------------------------------------

class IProtoBufSender : public IObject
{
public:
	//!	Send buffer.
	//!	@param		buffer		The buffer data.
	//!	@param		size		The buffer size in bytes.
	//!	@param		parameters	The user defined parameters.
	//!	@return		none.
	virtual _void Send( const _byte* buffer, _dword size ) PURE;
	//!	Post with user defined HTTP header list.
	//!	@param		url_name		The sub url name.
	//!	@param		header_list		The HTTP header list.
	//!	@param		buffer			The buffer data.
	//!	@param		size			The buffer size in bytes.
	//!	@param		parameters		The user defined parameters.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Post( AStringPtr url_name, const AStringArray& header_list, const _byte* buffer, _dword size, const QwordParameters4& parameters ) PURE;
};

//----------------------------------------------------------------------------
// IProtoBufMessageProcessor
//----------------------------------------------------------------------------

class IProtoBufMessageProcessor : public IObject
{
public:
	//!	Set the endian type.
	//!	@param		type		The endian type.
	//!	@return		none.
	virtual _void SetEndianType( _ENDIAN type ) PURE;

	//!	Decode message.
	//!	@param		buffer		The buffer data.
	//!	@param		size		The buffer size.
	//!	@param		msg_id		The message ID.
	//!	@param		msg_buf		The message buffer data.
	//!	@param		msg_size	The message buffer size in bytes.
	//! @return		The processed size in bytes, 0 indicates the message is incompleted, still need to wait.
	virtual _dword DecodeMessage( const _byte* buffer, _dword size, _dword& msg_id, const _byte*& msg_buf, _dword& msg_size ) PURE;

	//!	Encode message.
	//!	@param		msg_id			The message ID.
	//!	@param		buffer			The target buffer.
	//! @return		The processed size in bytes.
	virtual _dword EncodeMessage( _dword msg_id, MemArrayPtr< _byte >& buffer ) PURE;
	//!	Encode message.
	//!	@param		msg_id			The message ID.
	//!	@param		buffer			The target buffer.
	//! @return		The processed size in bytes.
	virtual _dword EncodeMessage( _dword msg_id, _byte* buffer ) PURE;
	//!	Encode message.
	//!	@param		msg_id			The message ID.
	//!	@param		message			The message info.
	//!	@param		buffer			The target buffer.
	//! @return		The processed size in bytes.
	virtual _dword EncodeMessage( _dword msg_id, const google::protobuf::MessageLite& message, MemArrayPtr< _byte >& buffer ) PURE;
	//!	Encode message.
	//!	@param		msg_id			The message ID.
	//!	@param		message			The message info.
	//!	@param		buffer			The target buffer.
	//! @return		The processed size in bytes.
	virtual _dword EncodeMessage( _dword msg_id, const google::protobuf::MessageLite& message, _byte* buffer ) PURE;
	//!	Encode message.
	//!	@param		msg_id			The message ID.
	//!	@param		msg_buf			The message buffer data.
	//!	@param		msg_size		The message buffer size.
	//!	@param		buffer			The target buffer.
	//! @return		The processed size in bytes.
	virtual _dword EncodeMessage( _dword msg_id, const _byte* msg_buf, _dword msg_size, MemArrayPtr< _byte >& buffer ) PURE;
	//!	Encode message.
	//!	@param		msg_id			The message ID.
	//!	@param		msg_buf			The message buffer data.
	//!	@param		msg_size		The message buffer size.
	//!	@param		buffer			The target buffer.
	//! @return		The processed size in bytes.
	virtual _dword EncodeMessage( _dword msg_id, const _byte* msg_buf, _dword msg_size, _byte* buffer ) PURE;
};

//----------------------------------------------------------------------------
// ITProtoBufProcessor
//----------------------------------------------------------------------------

template< typename Type >
class ITProtoBufProcessor : public Type
{
public:
	//!	Set the message processor.
	//!	@param		processor	The message processor
	//!	@return		none.
	virtual _void SetMessageProcessor( IProtoBufMessageProcessor* processor ) PURE;
	//!	Get the message processor.
	//!	@param		none.
	//!	@return		The message processor
	virtual IProtoBufMessageProcessor* GetMessageProcessor( ) PURE;

	//!	Set the sender.
	//!	@param		sender		The sender.
	//!	@return		none.
	virtual _void SetSender( IProtoBufSender* sender ) PURE;
	//!	Get the sender.
	//!	@param		none.
	//!	@return		The sender.
	virtual IProtoBufSender* GetSender( ) PURE;

	//!	Parse message from buffer.
	//!	@param		buffer		The buffer data.
	//!	@param		size		The buffer size in bytes.
	//!	@param		msg_id		The message ID.
	//!	@param		msg_buf		The message buffer data.
	//!	@param		msg_size	The message buffer size in bytes.
	//!	@return		The read size in bytes.
	virtual _dword ParseMessageFromBuffer( const _byte* buffer, _dword size, _dword& msg_id, const _byte*& msg_buf, _dword& msg_size ) PURE;
	//!	Write message into buffer.
	//!	@param		id				The message ID.
	//!	@param		stream_writer	The stream writer.
	//!	@return		The write size in bytes.
	virtual _dword WriteMessageIntoBuffer( _dword id, IStreamWriter* stream_writer ) PURE;
	//!	Write message into buffer.
	//!	@param		id				The message ID.
	//!	@param		message			The message data.
	//!	@param		stream_writer	The stream writer.
	//!	@return		The write size in bytes.
	virtual _dword WriteMessageIntoBuffer( _dword id, const google::protobuf::MessageLite& message, IStreamWriter* stream_writer ) PURE;
	//!	Write message into buffer.
	//!	@param		id				The message ID.
	//!	@param		buffer			The message buffer data.
	//!	@return		The write size in bytes.
	virtual _dword WriteMessageIntoBuffer( _dword id, _byte* buffer ) PURE;
	//!	Write message into buffer.
	//!	@param		id				The message ID.
	//!	@param		message			The message data.
	//!	@param		buffer			The message buffer data.
	//!	@return		The write size in bytes.
	virtual _dword WriteMessageIntoBuffer( _dword id, const google::protobuf::MessageLite& message, _byte* buffer ) PURE;

	//!	Write ID only.
	//!	@param		id			The message ID.
	//!	@return		none.
	virtual _void WriteBuffer( _dword id ) PURE;
	//!	Write message into buffer.
	//!	@param		id			The message ID.
	//!	@param		buffer		The buffer data.
	//!	@param		size		The buffer size in bytes.
	//!	@return		none.
	virtual _void WriteBuffer( _dword id, const _byte* buffer, _dword size ) PURE;
	//!	Post message with ID only.
	//!	@param		url_name	The sub url name.
	//!	@param		header_list	The HTTP header list.
	//!	@param		id			The message ID.
	//!	@param		parameters	The user defined parameters.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool PostBuffer( AStringPtr url_name, const AStringArray& header_list, _dword id, const QwordParameters4& parameters ) PURE;
	//!	Post message into buffer.
	//!	@param		url_name	The sub url name.
	//!	@param		header_list	The HTTP header list.
	//!	@param		id			The message ID.
	//!	@param		buffer		The buffer data.
	//!	@param		size		The buffer size in bytes.
	//!	@param		parameters	The user defined parameters.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool PostBuffer( AStringPtr url_name, const AStringArray& header_list, _dword id, const _byte* buffer, _dword size, const QwordParameters4& parameters ) PURE;
};

//----------------------------------------------------------------------------
// IProtoBufProcessor
//----------------------------------------------------------------------------

class IProtoBufProcessor : public ITProtoBufProcessor< IObject >
{
};

}