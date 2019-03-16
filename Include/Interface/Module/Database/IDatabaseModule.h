//! @file     IDatabaseModule.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IDatabaseModule
//----------------------------------------------------------------------------

class IDatabaseModule : public IModule
{
public:
	//! Get the last error string.
	//!	@param		none.
	//!	@return		The last error string.
	virtual WStringR GetLastError( ) PURE;

	//!	Create database connection.
	//!	@param		dsn			The data source name.
	//!	@param		username	The user name.
	//!	@param		password	The password.
	//!	@return		The database connection.
	virtual IDatabaseConnectionPassRef CreateConnection( WStringPtr dsn, WStringPtr username, WStringPtr password ) PURE;
};

}