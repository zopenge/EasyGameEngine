//! @file     DatabaseModule.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEDatabase.h"

//----------------------------------------------------------------------------
// DatabaseModule Implementation
//----------------------------------------------------------------------------

DatabaseModule::DatabaseModule( ) : BaseClass( L"Database", Version( DATABASE_FILEVER ) )
{
	mSQLEnvironment	= _null;
}

DatabaseModule::~DatabaseModule( )
{
	Finalize( );
}

_ubool DatabaseModule::GetDiagnosticRecordInfo( _handle sql_env_handle, SQLSMALLINT sql_handle_id, _int* native_err_code, WString* state_string, WString* error_string )
{
	EGE_ASSERT( sql_env_handle != _null );

	_charw sqlstate[256]; sqlstate[0] = 0;
	_charw sqlerror[1024]; sqlerror[0] = 0;

	// Get the SQL diagnostic record info
	_short size = 0;
	if ( ! SQL_SUCCEEDED( ::SQLGetDiagRecW( sql_handle_id, sql_env_handle, 1, sqlstate, (SQLINTEGER*) native_err_code, sqlerror, 1024, &size ) ) )
		return _false;

	// Feedback the state string
	if ( sqlstate[0] != 0 )
		*state_string = sqlstate;

	// Feedback the error string
	if ( sqlerror[0] != 0 )
		*error_string = sqlerror;

	return _true;
}

_ubool DatabaseModule::Initialize( )
{
	WLOG_TRACE( L"Create database module ..." );

	if ( ! SQL_SUCCEEDED( ::SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HANDLE, &mSQLEnvironment ) ) )
		return _false;

	if ( ! SQL_SUCCEEDED( ::SQLSetEnvAttr( mSQLEnvironment, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, SQL_IS_INTEGER ) ) )
		return _false;

	WLOG_TRACE( L"Create database module DONE" );

	return _true;
}

_void DatabaseModule::Finalize( )
{
	WLOG_TRACE( L"Release database module ..." );

	// Free SQL environment
	if ( mSQLEnvironment != _null )
		::SQLFreeHandle( SQL_HANDLE_ENV, mSQLEnvironment );

	WLOG_TRACE( L"Release database module DONE" );

	// Release global modules
	gDatabaseModule = &sNullDatabaseModule;
}

_void DatabaseModule::Tick( _dword limited_elapse, _dword elapse )
{

}

_void DatabaseModule::HandleEvent( EventBase& event )
{
}

WStringR DatabaseModule::GetLastError( )
{
	WString error_string;
	if ( GetDiagnosticRecordInfo( mSQLEnvironment, SQL_HANDLE_ENV, _null, _null, &error_string ) == _false )
		return L"";

	return error_string;
}

IDatabaseConnectionPassRef DatabaseModule::CreateConnection( WStringPtr dsn, WStringPtr username, WStringPtr password )
{
	DatabaseConnection* connection = new DatabaseConnection( mSQLEnvironment, dsn, username, password );
	if ( connection->Initialize( ) == _false )
		{ EGE_RELEASE( connection ); return _null; }

	return connection;
}