//! @file     INetworkConnectionThread.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// INetworkConnectionThread
//----------------------------------------------------------------------------

class INetworkConnectionThread : public IObject
{
public:
	//!	Get name.
	virtual WStringPtr GetName( ) const PURE;

	//!	Stop.
	virtual _void Stop( ) PURE;
	//!	Pause.
	virtual _void Pause( ) PURE;
	//!	Resume.
	virtual _void Resume( ) PURE;

	//!	Add the connection operations.
	//!	@param		connection	The connection.
	//!	@return		none.
	virtual _void AddConnection( INetworkConnection* connection ) PURE;
	//!	Get the connections number.
	//!	@param		none.
	//!	@return		The connections number.
	virtual _dword GetConnectionsNumber( ) const PURE;

	//!	Process the connection operations.
	//!	@param		connection	The connection.
	//!	@return		none.
	virtual _void ProcessConnectionOperations( INetworkConnection* connection ) PURE;
};

}