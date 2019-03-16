//! @file     ProtoBufProcessor.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// ProtoBufProcessor Implementation
//----------------------------------------------------------------------------

ProtoBufProcessor::ProtoBufProcessor( )
{
	mSender				= &NullEngine::GetInstance( ).GetProtoBufSender( );
	mMessageProcessor	= GetInterfaceFactory( )->CreateProtoBufMessageProcessor( );
}

ProtoBufProcessor::~ProtoBufProcessor( )
{

}

_void ProtoBufProcessor::SetMessageProcessor( IProtoBufMessageProcessor* processor )
{
	if ( processor == _null )
		mMessageProcessor = GetInterfaceFactory( )->CreateProtoBufMessageProcessor( );
	else
		mMessageProcessor = processor;
}

IProtoBufMessageProcessor* ProtoBufProcessor::GetMessageProcessor( )
{
	return mMessageProcessor;
}

_void ProtoBufProcessor::SetSender( IProtoBufSender* sender )
{
	if ( sender == _null )
		mSender = &NullEngine::GetInstance( ).GetProtoBufSender( );
	else
		mSender = sender;
}

IProtoBufSender* ProtoBufProcessor::GetSender( )
{
	return mSender;
}

_dword ProtoBufProcessor::ParseMessageFromBuffer( const _byte* buffer, _dword size, _dword& msg_id, const _byte*& msg_buf, _dword& msg_size )
{
	if ( buffer == 0 || size == 0 )
		return 0;

	// Decode message info
	_dword processed_size = mMessageProcessor->DecodeMessage( buffer, size, msg_id, msg_buf, msg_size );
	if ( processed_size == 0 )
		return 0; // The protocol data is not ready ...

	// Finish to process message
	return processed_size;
}

_dword ProtoBufProcessor::WriteMessageIntoBuffer( _dword id, IStreamWriter* stream_writer )
{
	if ( stream_writer == _null )
		return 0;

	// Encode message info
	MemArrayPtr< _byte > msg_buf;
	_dword processed_size = mMessageProcessor->EncodeMessage( id, msg_buf );
	if ( processed_size == 0 )
		return 0;

	// Write message header
	return stream_writer->WriteBuffer( msg_buf, processed_size );
}

_dword ProtoBufProcessor::WriteMessageIntoBuffer( _dword id, const google::protobuf::MessageLite& message, IStreamWriter* stream_writer )
{
	if ( stream_writer == _null )
		return 0;

	// Encode message info
	MemArrayPtr< _byte > msg_buf;
	_dword processed_size = mMessageProcessor->EncodeMessage( id, message, msg_buf );
	if ( processed_size == 0 )
		return 0;

	// Write message header
	return stream_writer->WriteBuffer( msg_buf, processed_size );
}

_dword ProtoBufProcessor::WriteMessageIntoBuffer( _dword id, _byte* buffer )
{
	if ( buffer == _null )
		return 0;

	// Encode message info
	_dword processed_size = mMessageProcessor->EncodeMessage( id, buffer );
	if ( processed_size == 0 )
		return 0;

	// Feedback the write size in bytes
	return processed_size;
}

_dword ProtoBufProcessor::WriteMessageIntoBuffer( _dword id, const google::protobuf::MessageLite& message, _byte* buffer )
{
	if ( buffer == _null )
		return 0;

	// Encode message info
	_dword processed_size = mMessageProcessor->EncodeMessage( id, message, buffer );
	if ( processed_size == 0 )
		return 0;

	// Feedback the write size in bytes
	return processed_size;
}

_void ProtoBufProcessor::WriteBuffer( _dword id )
{
	// Encode message info
	MemArrayPtr< _byte > msg_buf;
	_dword processed_size = mMessageProcessor->EncodeMessage( id, msg_buf );
	if ( processed_size == 0 )
		return;

	// Send it
	mSender->Send( msg_buf, processed_size );
}

_void ProtoBufProcessor::WriteBuffer( _dword id, const _byte* buffer, _dword size )
{
	if ( buffer == _null || size == 0 )
		return;

	// Encode message
	MemArrayPtr< _byte > msg_buf;
	_dword processed_size = mMessageProcessor->EncodeMessage( id, buffer, size, msg_buf );
	if ( processed_size == 0 )
		return;

	// Send it
	mSender->Send( msg_buf, processed_size );
}

_ubool ProtoBufProcessor::PostBuffer( AStringPtr url_name, const AStringArray& header_list, _dword id, const QwordParameters4& parameters )
{
	// Encode message info
	MemArrayPtr< _byte > msg_buf;
	_dword processed_size = mMessageProcessor->EncodeMessage( id, msg_buf );
	if ( processed_size == 0 )
		return _false;

	// Post it
	return mSender->Post( url_name, header_list, msg_buf, processed_size, parameters );
}

_ubool ProtoBufProcessor::PostBuffer( AStringPtr url_name, const AStringArray& header_list, _dword id, const _byte* buffer, _dword size, const QwordParameters4& parameters )
{
	if ( buffer == _null || size == 0 )
		return _false;

	// Encode message
	MemArrayPtr< _byte > msg_buf;
	_dword processed_size = mMessageProcessor->EncodeMessage( id, buffer, size, msg_buf );
	if ( processed_size == 0 )
		return _false;

	// Post it
	return mSender->Post( url_name, header_list, msg_buf, processed_size, parameters );
}