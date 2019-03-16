//! @file     ScriptModule.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

//----------------------------------------------------------------------------
// ScriptModule Helpful Functions Implementation
//----------------------------------------------------------------------------

const _charw* GetScriptTypeName( _SCRIPT type )
{
	switch ( type )
	{
		case _SCRIPT_PYTHON:		return L"Python";
		case _SCRIPT_JAVA_SCRIPT:	return L"JavaScript";
		case _SCRIPT_LUA:			return L"Lua";
		default:
			return L"Unknown";
	}
}

//----------------------------------------------------------------------------
// ScriptModule Implementation
//----------------------------------------------------------------------------

ScriptModule::ScriptModule( ) : BaseClass( L"Script", Version( SCRIPT_FILEVER ) )
{
}

ScriptModule::~ScriptModule( )
{
	Finalize( );

	GetModuleManager( )->UnregisterModule( this );
}

_ubool ScriptModule::InitInternalScriptModule( _SCRIPT type )
{
	switch ( type )
	{
#if (_SCRIPT_USE_PYTHON_ == 1)
		case _SCRIPT_PYTHON:		mInternalScriptSystem = new _pySystem( ); break;
#elif (_SCRIPT_USE_JS_ == 1)
		case _SCRIPT_JAVA_SCRIPT:	mInternalScriptSystem = new _jscSystem( ); break;
#elif (_SCRIPT_USE_LUA_ == 1)
		case _SCRIPT_LUA:			mInternalScriptSystem = new _luaSystem( ); break;
#endif
		default:
			WLOG_ERROR_1( L"The script module does not support '%s' script", GetScriptTypeName( type ) );
			return _false;
	}

	// Initialize internal script system
	if ( mInternalScriptSystem->Initialize( ) == _false )
		return _false;

	gInternalScriptSystem = mInternalScriptSystem.GetPtr( );

	return _true;
}

_ubool ScriptModule::Initialize( _SCRIPT type )
{
	WLOG_TRACE( L"Create script module ..." );

	// Initialize script helper
	if ( _scriptHelper::Initialize( ) == _false )
		return _false;

	// Initialize internal script module
	if ( InitInternalScriptModule( type ) == _false )
		return _false;

	// Initialize resource manager
	gScriptResourceManager = &mResourceManager;
	if ( mResourceManager.Initialize( ) == _false )
		return _false;

	WLOG_TRACE( L"Create script module DONE" );

	return _true;
}

_void ScriptModule::Finalize( )
{
	WLOG_TRACE( L"Release script module ..." );

	// Finalize internal components
	mResourceManager.Finalize( );

	// Release internal script system
	mInternalScriptSystem.Clear( );

	// Finalize script helper
	_scriptHelper::Finalize( );

	WLOG_TRACE( L"Release script module DONE" );

	// Clear global modules
	gInternalScriptSystem	= &NullScript::GetInstance( ).GetScriptSystem( );
	gScriptResourceManager	= &NullScript::GetInstance( ).GetScriptResourceManager( );
	gScriptModule			= &NullScript::GetInstance( ).GetScriptModule( );
}

_void ScriptModule::Tick( _dword limited_elapse, _dword elapse )
{
	gInternalScriptSystem->Tick( limited_elapse, elapse );
}

_void ScriptModule::HandleEvent( EventBase& event )
{
}

_dword ScriptModule::GetTotalMemSize( ) const
{
	return gInternalScriptSystem->GetTotalMemSize( );
}

_ubool ScriptModule::SetRemoteDebugger( const Address& address )
{
	return gInternalScriptSystem->SetRemoteDebugger( address );
}

const Address& ScriptModule::GetRemoteDebugger( ) const
{
	return gInternalScriptSystem->GetRemoteDebugger( );
}