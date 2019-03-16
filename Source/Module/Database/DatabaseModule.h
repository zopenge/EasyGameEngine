//! @file     DatabaseModule.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// DatabaseModule
//----------------------------------------------------------------------------

class DatabaseModule : public INTERFACE_MODULE_IMPL( IDatabaseModule )
{
private:
	typedef INTERFACE_MODULE_IMPL( IDatabaseModule ) BaseClass;

private:
	//!	The SQL environment handle
	_handle	mSQLEnvironment;

public:
	DatabaseModule( );
	virtual ~DatabaseModule( );

public:
	//!	Get several commonly used fields of a diagnostic record, including the SQLSTATE, the native error code, and the diagnostic message text.
	//!	@param		sql_env_handle	The SQL environment handle.
	//!	@param		sql_handle_id	The SQL handle ID.
	//!	@param		native_err_code	The native error code.
	//!	@param		state_string	The state string.
	//!	@param		error_string	The error string.
	//! @return		True indicates success, false indicates failure.
	static _ubool GetDiagnosticRecordInfo( _handle sql_env_handle, SQLSMALLINT sql_handle_id, _int* native_err_code = _null, WString* state_string = _null, WString* error_string = _null );

public:
	//!	Initialize.
	_ubool Initialize( );
	//!	Finalize.
	_void Finalize( );

// IObject Interface
public:
	virtual _void						Tick( _dword limited_elapse, _dword elapse ) override;

// IModule Interface
public:
	virtual _void						HandleEvent( EventBase& event ) override;

// IDatabaseModule Interface
public:
	virtual WStringR					GetLastError( ) override;

	virtual IDatabaseConnectionPassRef	CreateConnection( WStringPtr dsn, WStringPtr username, WStringPtr password ) override;
};

}