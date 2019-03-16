//! @file     INetworkStation.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// INetworkStationNotifier
//----------------------------------------------------------------------------

class INetworkStationNotifier : public IObject
{
public:
	//!	When accept a client connection.
	//!	@param		client_id		The client ID.
	//!	@return		none.
	virtual _void OnAcceptClient( _dword client_id ) PURE;
	//!	When lost a client connection.
	//!	@param		client_id		The client ID.
	//!	@return		none.
	virtual _void OnLostClient( _dword client_id ) PURE;

	//!	When receive buffer on connection.
	//!	@param		client_id		The client ID.
	//!	@param		size			The buffer size.
	//!	@param		buffer			The buffer data.
	//!	@param		stream_writer	The stream what you want to send.
	//!	@return		The processed buffer size what you have processed.
	virtual _dword OnRecvBuffer( _dword client_id, _dword size, const _byte* buffer, IStreamWriter* stream_writer ) PURE;
};

//----------------------------------------------------------------------------
// INetworkStation
//----------------------------------------------------------------------------

class INetworkStation : public ITNameObject< IObject >
{
public:
	//!	Set the notifier.
	//!	@param		notifier	The notifier.
	//! @return		none.
	virtual _void SetNotifier( INetworkStationNotifier* notifier ) PURE;
	//!	Get the notifier.
	//!	@param		none.
	//! @return		The notifier.
	virtual INetworkStationNotifier* GetNotifier( ) PURE;

	//!	Get the address.
	//!	@param		none.
	//!	@return		The address.
	virtual const Address& GetAddress( ) const PURE;

	//!	Start.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Start( ) PURE;
	//!	Stop.
	//!	@param		none.
	//! @return		none.
	virtual _void Stop( ) PURE;

	//!	Get the total client number.
	//!	@param		none.
	//!	@return		The total client number.
	virtual _dword GetClientNumber( ) const PURE;
	//!	Get the client ID by index.
	//!	@param		index		The index of client.
	//!	@return		The client ID, 0 indicates failure.
	virtual _dword GetClientIDByIndex( _dword index ) PURE;

	//!	Send request in google-protobuf-format with ID only.
	//!	@param		client_id	The client ID.
	//!	@param		msg_id		The message ID.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SendRequest( _dword client_id, _dword msg_id ) PURE;
	//!	Send message in protocol buffer format.
	//!	@param		client_id	The client ID.
	//!	@param		msg_id		The message ID.
	//!	@param		message		The message data.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SendMessage( _dword client_id, _dword msg_id, const google::protobuf::MessageLite& message ) PURE;

	//!	Broadcast.
	//!	@param		size	The buffer size.
	//!	@param		buffer	The buffer data.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Broadcast( _dword size, const _byte* buffer ) PURE;
};

}