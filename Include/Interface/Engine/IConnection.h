//! @file     IConnection.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IConnection
//----------------------------------------------------------------------------

class IConnection : public ITPriorityObject< IObservable >
{
public:
	//!	Get the connection state.
	//!	@param		none.
	//!	@return		The connection state.
	virtual _CONNECTION_STATE GetConnectionState( ) const PURE;

	//!	Check whether it's connecting or not.
	//!	@param		none.
	//!	@return		True indicates it's connecting.
	virtual _ubool IsConnecting( ) const PURE;
	//!	Check whether has connected or not.
	//!	@param		none.
	//!	@return		True indicates had connected.
	virtual _ubool IsConnected( ) const PURE;
	//!	Check whether connection has lost or not.
	//!	@param		none.
	//!	@return		True indicates the connection has lost.
	virtual _ubool IsConnectionLost( ) const PURE;
};

}