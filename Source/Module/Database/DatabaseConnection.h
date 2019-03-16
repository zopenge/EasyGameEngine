//! @file     DatabaseConnection.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// DatabaseConnection
//----------------------------------------------------------------------------

class DatabaseConnection : public INTERFACE_CONNECTION_IMPL( IDatabaseConnection )
{
private:
	typedef INTERFACE_CONNECTION_IMPL( IDatabaseConnection ) BaseClass;

private:
	//!	The connection info
	WString	mConnectionDSN;
	WString	mConnectionUsername;
	WString	mConnectionPassword;

	//!	The SQL connection handles
	_handle	mSQLEnvironment;
	_handle	mSQLConnection;
	_handle	mSQLStatement;

private:
	//!	Execute SQL command.
	//!	@param		sql		The SQL command string.
	//! @return		True indicates success, false indicates failure.
	_ubool Execute( WStringPtr sql );

public:
	DatabaseConnection( _handle sql_env_handle, WStringPtr dsn, WStringPtr username, WStringPtr password );
	virtual ~DatabaseConnection( );

public:
	//!	Initialize.
	_ubool Initialize( );

// IDatabaseConnection Interface
public:
	virtual _ubool					Connect( ) override;
	virtual _void					Disconnect( ) override;

	virtual IDatabaseRecordPassRef 	Query( WStringPtr sql ) override;

	virtual WStringR				GetLastCommandErrorString( ) override;
};

}