//! @file     ProtoBufMessageProcessor.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ProtoBufMessageProcessor
//----------------------------------------------------------------------------

class ProtoBufMessageProcessor : public TObject< IProtoBufMessageProcessor >
{
private:
	//!	The message header info
	struct MsgHeaderInfo
	{
		_dword	mSize;
		_dword	mID;

		MsgHeaderInfo( )
		{
			mSize	= 0;
			mID		= 0;
		}
	};

private:
	_ENDIAN	mEndianType;

private:
	//!	Build message header info.
	_void BuildMesHeaderInfo( MsgHeaderInfo& msg_header_info, _dword msg_id, _dword msg_size ) const;

public:
	ProtoBufMessageProcessor( );
	virtual ~ProtoBufMessageProcessor( );

// ITProtoBufMessageProcessor Interface
public:
	virtual _void	SetEndianType( _ENDIAN type ) override;

	virtual _dword	DecodeMessage( const _byte* buffer, _dword size, _dword& msg_id, const _byte*& msg_buf, _dword& msg_size ) override;

	virtual _dword	EncodeMessage( _dword msg_id, MemArrayPtr< _byte >& buffer ) override;
	virtual _dword	EncodeMessage( _dword msg_id, _byte* buffer ) override;
	virtual _dword	EncodeMessage( _dword msg_id, const google::protobuf::MessageLite& message, MemArrayPtr< _byte >& buffer ) override;
	virtual _dword	EncodeMessage( _dword msg_id, const google::protobuf::MessageLite& message, _byte* buffer ) override;
	virtual _dword	EncodeMessage( _dword msg_id, const _byte* msg_buf, _dword msg_size, MemArrayPtr< _byte >& buffer ) override;
	virtual _dword	EncodeMessage( _dword msg_id, const _byte* msg_buf, _dword msg_size, _byte* buffer ) override;
};

}