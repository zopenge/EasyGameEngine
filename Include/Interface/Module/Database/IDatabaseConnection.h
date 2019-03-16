//! @file     IDatabaseConnection.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IDatabaseConnection
//----------------------------------------------------------------------------

class IDatabaseConnection : public IConnection
{
public:
	//!	Connect.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Connect( ) PURE;
	//!	Disconnect.
	//!	@param		none.
	//! @return		none.
	virtual _void Disconnect( ) PURE;

	//!	Query database records.
	//!	@param		sql		The SQL command string.
	//!	@return		The database record.
	virtual IDatabaseRecordPassRef Query( WStringPtr sql ) PURE;

	//! Get the last command error string.
	//!	@param		none.
	//!	@return		The last command error string.
	virtual WStringR GetLastCommandErrorString( ) PURE;
};

}