//! @file     DatabaseConnection.cpp
//! @author   LiCode
//! @version  1.1.0.695
//! @date     2011/02/13
//! Copyright ...

#include "EGEDatabase.h"

//----------------------------------------------------------------------------
// DatabaseConnection Implementation
//----------------------------------------------------------------------------

DatabaseConnection::DatabaseConnection( _handle sql_env_handle, WStringPtr dsn, WStringPtr username, WStringPtr password )
	: mSQLEnvironment( sql_env_handle ), mConnectionDSN( dsn ), mConnectionUsername( username ), mConnectionPassword( password )
{
	mSQLConnection	= _null;
	mSQLStatement	= _null;
}

DatabaseConnection::~DatabaseConnection( )
{
	Disconnect( );
}

_ubool DatabaseConnection::Execute( WStringPtr sql )
{
	if ( sql.IsEmpty( ) )
		return _false;

	SQLWCHAR* sql_command_string = (SQLWCHAR*) sql.Str( );

	// Execute the SQL command 
	SQLRETURN result = ::SQLExecDirectW( mSQLStatement, sql_command_string, SQL_NTS );
	if ( ! SQL_SUCCEEDED( result ) )
	{
		if ( result == SQL_NO_DATA )
			return _true;

		return _false;
	}

	return _true;
}

_ubool DatabaseConnection::Initialize( )
{
	// Allocate the SQL handle
	if ( ! SQL_SUCCEEDED( ::SQLAllocHandle( SQL_HANDLE_DBC, mSQLEnvironment, &mSQLConnection ) ) )
		return _false;

	// Start to connect
	if ( Connect( ) == _false )
		return _false;

	return _true;
}

_ubool DatabaseConnection::Connect( )
{
	SQLWCHAR* dsn		= (SQLWCHAR*) mConnectionDSN.Str( );
	SQLWCHAR* username 	= (SQLWCHAR*) mConnectionUsername.Str( );
	SQLWCHAR* password 	= (SQLWCHAR*) mConnectionPassword.Str( );

	// Connect to database
	if ( ! SQL_SUCCEEDED( ::SQLConnectW( mSQLConnection, dsn, SQL_NTS, username, SQL_NTS, password, SQL_NTS ) ) )
		return _false;

	if ( ! SQL_SUCCEEDED( ::SQLSetConnectAttr( mSQLConnection, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER) SQL_CURSOR_KEYSET_DRIVEN, SQL_IS_POINTER ) ) )
		return _false;

	if ( ! SQL_SUCCEEDED( ::SQLAllocHandle( SQL_HANDLE_STMT, mSQLConnection, &mSQLStatement ) ) )
		return _false;

	if ( ! SQL_SUCCEEDED( ::SQLSetStmtAttr( mSQLStatement, SQL_ATTR_CURSOR_TYPE, (SQLPOINTER) SQL_CURSOR_DYNAMIC, SQL_IS_INTEGER ) ) )
		return _false;

	// Connected successful
	SetConnectionState( _CS_CONNECTED );

	return _true;
}

_void DatabaseConnection::Disconnect( )
{
	BaseClass::Disconnect( );

	if ( mSQLConnection != _null )
	{
		::SQLDisconnect( mSQLConnection );
		::SQLFreeHandle( SQL_HANDLE_DBC, mSQLConnection );
	}

	if ( mSQLStatement != _null )
		::SQLFreeHandle( SQL_HANDLE_STMT, mSQLStatement );

	mSQLConnection	= _null;
	mSQLStatement	= _null;
}

//_ubool DatabaseConnection::IsConnectionLost( ) const
//{
//	WString state_string;
//	if ( DatabaseModule::GetDiagnosticRecordInfo( mSQLEnvironment, SQL_HANDLE_STMT, _null, &state_string, _null ) == _false )
//		return _true; // If we get diagnostic record info failed then we assume that we lost connection
//
//	return state_string == L"01000";
//}

IDatabaseRecordPassRef DatabaseConnection::Query( WStringPtr sql )
{
	// Perform the SQL command 
	if ( Execute( sql ) == _false )
		return _null;

	// Create database records
	DatabaseRecord* record = new DatabaseRecord( this );
	if ( record->Initialize( ) == _false )
		{ EGE_RELEASE( record ); return _null; }

	return record;
}

WStringR DatabaseConnection::GetLastCommandErrorString( )
{
	WString error_string;
	if ( DatabaseModule::GetDiagnosticRecordInfo( mSQLEnvironment, SQL_HANDLE_STMT, _null, _null, &error_string ) == _false )
		return WString( L"" );

	return error_string;
}