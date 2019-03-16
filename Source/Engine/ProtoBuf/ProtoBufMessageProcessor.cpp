//! @file     ProtoBufMessageProcessor.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// ProtoBufMessageProcessor Implementation
//----------------------------------------------------------------------------

ProtoBufMessageProcessor::ProtoBufMessageProcessor( )
{
	// Use the big endian as default for network translation
	mEndianType = _ENDIAN_BIG;
}

ProtoBufMessageProcessor::~ProtoBufMessageProcessor( )
{

}

_void ProtoBufMessageProcessor::BuildMesHeaderInfo( MsgHeaderInfo& msg_header_info, _dword msg_id, _dword msg_size ) const
{
	switch ( mEndianType )
	{
		case _ENDIAN_UNKNOWN:
		{
			msg_header_info.mID		= msg_id;
			msg_header_info.mSize	= msg_size;
		}
		break;

		case _ENDIAN_BIG:
		{
			if ( Platform::IsLittleEndian( ) )
			{
				msg_header_info.mID		= ntohl( msg_id );
				msg_header_info.mSize	= ntohl( msg_size );
			}
			else
			{
				msg_header_info.mID		= msg_id;
				msg_header_info.mSize	= msg_size;
			}
		}
		break;

		case _ENDIAN_LITTLE:
		{
			if ( Platform::IsBigEndian( ) )
			{
				msg_header_info.mID		= htonl( msg_id );
				msg_header_info.mSize	= htonl( msg_size );
			}
			else
			{
				msg_header_info.mID		= msg_id;
				msg_header_info.mSize	= msg_size;
			}
		}
		break;

		default:
			break;
	}
}

_void ProtoBufMessageProcessor::SetEndianType( _ENDIAN type )
{
	mEndianType = type;
}

_dword ProtoBufMessageProcessor::DecodeMessage( const _byte* buffer, _dword size, _dword& msg_id, const _byte*& msg_buf, _dword& msg_size )
{
	if ( size < sizeof( MsgHeaderInfo ) )
		return 0;

	// Please use the memory copy operation here to avoid the data aligned BUG
	MsgHeaderInfo msg_header_info;
	EGE_MEM_CPY( &msg_header_info, buffer, sizeof( MsgHeaderInfo ) );
	
	switch ( mEndianType )
	{
		case _ENDIAN_UNKNOWN:
		{
		}
		break;
	
		case _ENDIAN_BIG:
		{
			if ( Platform::IsLittleEndian( ) )
			{
				msg_header_info.mID		= htonl( msg_header_info.mID );
				msg_header_info.mSize	= htonl( msg_header_info.mSize );
			}
		}
		break;
	
		case _ENDIAN_LITTLE:
		{
			if ( Platform::IsBigEndian( ) )
			{
				msg_header_info.mID		= ntohl( msg_header_info.mID );
				msg_header_info.mSize	= ntohl( msg_header_info.mSize );
			}
		}
		break;
	
		default:
			break;
	}

	// Check message size
	if ( size < msg_header_info.mSize )
		return 0;

	// Feedback message info
	msg_id		= msg_header_info.mID;
	msg_buf		= buffer + sizeof( MsgHeaderInfo );
	msg_size	= msg_header_info.mSize;

	// Feedback the processed size
	return sizeof( msg_header_info ) + msg_size;
}

_dword ProtoBufMessageProcessor::EncodeMessage( _dword msg_id, MemArrayPtr< _byte >& buffer )
{
	MsgHeaderInfo msg_header_info;
	BuildMesHeaderInfo( msg_header_info, msg_id, 0 );

	// Please use the memory copy operation here to avoid the data aligned BUG
	buffer.Create( sizeof( msg_header_info ) );
	EGE_MEM_CPY( buffer, &msg_header_info, sizeof( MsgHeaderInfo ) );

	// Feedback the processed size
	return sizeof( msg_header_info );
}

_dword ProtoBufMessageProcessor::EncodeMessage( _dword msg_id, _byte* buffer )
{
	MsgHeaderInfo msg_header_info;
	BuildMesHeaderInfo( msg_header_info, msg_id, 0 );

	// Please use the memory copy operation here to avoid the data aligned BUG
	EGE_MEM_CPY( buffer, &msg_header_info, sizeof( MsgHeaderInfo ) );

	// Feedback the processed size
	return sizeof( msg_header_info );
}

_dword ProtoBufMessageProcessor::EncodeMessage( _dword msg_id, const google::protobuf::MessageLite& message, MemArrayPtr< _byte >& buffer )
{
	// Get the message size in bytes
	_dword msg_size = message.ByteSize( );
	if ( msg_size == 0 )
		return 0;

	// Build message header info
	MsgHeaderInfo msg_header_info;
	BuildMesHeaderInfo( msg_header_info, msg_id, msg_size );

	// Please use the memory copy operation here to avoid the data aligned BUG
	buffer.Create( sizeof( msg_header_info ) + msg_size );
	EGE_MEM_CPY( buffer, &msg_header_info, sizeof( MsgHeaderInfo ) );

	// Serialize message to buffer
	message.SerializePartialToArray( buffer.GetPointer( ) + sizeof( MsgHeaderInfo ), msg_size );

	// Feedback the processed size
	return sizeof( msg_header_info ) + msg_size;
}

_dword ProtoBufMessageProcessor::EncodeMessage( _dword msg_id, const google::protobuf::MessageLite& message, _byte* buffer )
{
	// Get the message size in bytes
	_dword msg_size = message.ByteSize( );
	if ( msg_size == 0 )
		return 0;

	// Build message header info
	MsgHeaderInfo msg_header_info;
	BuildMesHeaderInfo( msg_header_info, msg_id, msg_size );

	// Please use the memory copy operation here to avoid the data aligned BUG
	EGE_MEM_CPY( buffer, &msg_header_info, sizeof( MsgHeaderInfo ) );

	// Serialize message to buffer
	message.SerializePartialToArray( buffer + sizeof( MsgHeaderInfo ), msg_size );

	// Feedback the processed size
	return sizeof( msg_header_info ) + msg_size;
}

_dword ProtoBufMessageProcessor::EncodeMessage( _dword msg_id, const _byte* msg_buf, _dword msg_size, MemArrayPtr< _byte >& buffer )
{
	if ( msg_size == 0 )
		return 0;

	// Build message header info
	MsgHeaderInfo msg_header_info;
	BuildMesHeaderInfo( msg_header_info, msg_id, msg_size );

	// Get the total processed size
	_dword processed_size = sizeof( msg_header_info ) + msg_size;

	// Create buffer
	buffer.Create( processed_size );

	// Please use the memory copy operation here to avoid the data aligned BUG
	EGE_MEM_CPY( buffer, &msg_header_info, sizeof( MsgHeaderInfo ) );
	EGE_MEM_CPY( buffer.GetPointer( ) + sizeof( MsgHeaderInfo ), msg_buf, msg_size );

	// Feedback the processed size
	return processed_size;
}

_dword ProtoBufMessageProcessor::EncodeMessage( _dword msg_id, const _byte* msg_buf, _dword msg_size, _byte* buffer )
{
	if ( msg_size == 0 )
		return 0;

	// Build message header info
	MsgHeaderInfo msg_header_info;
	BuildMesHeaderInfo( msg_header_info, msg_id, msg_size );

	// Get the total processed size
	_dword processed_size = sizeof( msg_header_info ) + msg_size;

	// Please use the memory copy operation here to avoid the data aligned BUG
	EGE_MEM_CPY( buffer, &msg_header_info, sizeof( MsgHeaderInfo ) );
	EGE_MEM_CPY( buffer + sizeof( MsgHeaderInfo ), msg_buf, msg_size );

	// Feedback the processed size
	return processed_size;
}
