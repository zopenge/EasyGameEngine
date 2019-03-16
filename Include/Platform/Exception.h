//! @file     Exception.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Exception
//----------------------------------------------------------------------------

//! This class catch the unhandled exception, and report to user.
class Exception
{
public:
	//!	When get the dump file name callback function.
	//!	@param		procname		The module file name.
	//! @return		The dump file name.
	typedef WString (*OnGetDumpFileName)( WStringPtr procname );
	//!	When create dump file callback function.
	//!	@param		filename		The dump file name.
	//! @return		True indicates success, false indicates failure.
	typedef _ubool (*OnCreateDumpFile)( WStringPtr filename );

private:
	//! Throw exception to windows again or not.
	static _ubool				sThrowException;

	//!	The callback functions
	static OnGetDumpFileName	sGetDumpFileNameFunc;
	static OnCreateDumpFile		sCreateDumpFileFunc;

private:
	//! The exception filter function, used to catch the unhandled exception.
	//! @param		exception			Exception pointer.
	//! @return		Function code of how to process exception, always be EXCEPTION_EXECUTE_HANDLER.
	static _long ExceptionFilter( _void* exception );

public:
	//! Initialize exception system.
	//!	@param		get_dump_func		The get dump file name callback function.
	//!	@param		create_dump_func	The create dump file callback function.
	//! @param		throwexception		Throw exception to windows again or not.
	//!	@return		none.
	static _void Initialize( OnGetDumpFileName get_dump_func, OnCreateDumpFile create_dump_func, _ubool throwexception = _false );
	//! Finalize exception system.
	//! @param		none.
	//!	@return		none.
	static _void Finalize( );

	//!	Converts a simple exception to a string value.
	//!	@param		exceptioncode		The exception code.
	//!	@return		The string of exception code.
	static WStringPtr GetExceptionCodeString( _dword exceptioncode );
};

}