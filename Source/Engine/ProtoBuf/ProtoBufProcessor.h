//! @file     ProtoBufProcessor.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ProtoBufProcessor
//----------------------------------------------------------------------------

class ProtoBufProcessor : public TObject< IProtoBufProcessor >
{
private:
	IProtoBufSenderRef				mSender;
	IProtoBufMessageProcessorRef	mMessageProcessor;

public:
	ProtoBufProcessor( );
	virtual ~ProtoBufProcessor( );

// ITProtoBufProcessor Interface
public:
	virtual _void						SetMessageProcessor( IProtoBufMessageProcessor* processor ) override;
	virtual IProtoBufMessageProcessor*	GetMessageProcessor( ) override;

	virtual _void						SetSender( IProtoBufSender* sender ) override;
	virtual IProtoBufSender*			GetSender( ) override;

	virtual _dword						ParseMessageFromBuffer( const _byte* buffer, _dword size, _dword& msg_id, const _byte*& msg_buf, _dword& msg_size ) override;
	virtual _dword						WriteMessageIntoBuffer( _dword id, IStreamWriter* stream_writer ) override;
	virtual _dword						WriteMessageIntoBuffer( _dword id, const google::protobuf::MessageLite& message, IStreamWriter* stream_writer ) override;
	virtual _dword						WriteMessageIntoBuffer( _dword id, _byte* buffer ) override;
	virtual _dword						WriteMessageIntoBuffer( _dword id, const google::protobuf::MessageLite& message, _byte* buffer ) override;

	virtual _void						WriteBuffer( _dword id ) override;
	virtual _void						WriteBuffer( _dword id, const _byte* buffer, _dword size ) override;
	virtual _ubool						PostBuffer( AStringPtr url_name, const AStringArray& header_list, _dword id, const QwordParameters4& parameters ) override;
	virtual _ubool						PostBuffer( AStringPtr url_name, const AStringArray& header_list, _dword id, const _byte* buffer, _dword size, const QwordParameters4& parameters ) override;
};

}