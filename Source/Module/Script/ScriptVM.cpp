//! @file     ScriptVM.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

//----------------------------------------------------------------------------
// ScriptVM Implementation
//----------------------------------------------------------------------------

ScriptVM::ScriptVM( )
{
}

ScriptVM::~ScriptVM( )
{
}

_ubool ScriptVM::Initialize( )
{
	mVM = gInternalScriptSystem->CreateScriptVM( );
	if ( mVM.IsNull( ) )
		return _false;

	return _true;
}

ScriptVMRegisters& ScriptVM::GetRegisters( )
{
	return mRegistersInfo;
}

const ScriptVMRegisters& ScriptVM::GetRegisters( ) const
{
	return mRegistersInfo;
}

_void ScriptVM::SetExceptionInfo( const ScriptVMExceptionInfo& info )
{
	mExceptionInfo = info;
}

const ScriptVMExceptionInfo& ScriptVM::GetExceptionInfo( ) const
{
	return mExceptionInfo;
}

_ubool ScriptVM::LoadFromResName( WStringPtr res_name )
{
	// Load resource
	IStreamReaderRef stream_reader = GetWorkingArchive( )->LoadResourceByName( res_name );
	if ( stream_reader.IsNull( ) )
		return _false;

	// Load script
	if ( mVM->LoadFromBuffer( (const _byte*) stream_reader->GetBuffer( ), stream_reader->GetSize( ), AString( ).FromString( res_name ) ) == _false )
    {
        WLOG_ERROR_1( L"Load script from '%s' resource failed", res_name.Str( ) );
		return _false;
    }

	return _true;
}

IScriptFunctionPassRef ScriptVM::GetScriptFunction( AStringPtr func_name )
{
	_scriptFunctionRef function = mVM->GetScriptFunction( func_name );
	if ( function.IsNull( ) )
	{
		ALOG_ERROR_1( "The '%s' function name is not existing", func_name.Str( ) );
		return _null;
	}

	return new ScriptFunction( function );
}