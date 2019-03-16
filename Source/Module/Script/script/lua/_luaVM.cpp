//! @file     _luaVM.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_LUA_ == 1)

//----------------------------------------------------------------------------
// _luaVM Implementation
//----------------------------------------------------------------------------

_luaVM::_luaVM( )
{
}

_luaVM::~_luaVM( )
{
}

_ubool _luaVM::Initialize( )
{
	return _true;
}

_scriptFunctionPassRef _luaVM::GetScriptFunction( AStringPtr func_name )
{
	_luaFunction* func = new _luaFunction( );
	if ( func->Initialize( func_name ) == _false )
		{ EGE_RELEASE( func ); return _null; }

	return func;
}

_ubool _luaVM::LoadFromBuffer( const _byte* buffer, _dword size, AStringPtr filename )
{
	if ( buffer == _null || size == 0 )
		return _false;

	// Add file name as required file
	_luaCore::GetInstance( ).AddRequiredFile( filename );

	// Load script file
	if ( luaL_loadbuffer( gLuaState, (const _chara*) buffer, size, filename.Str( ) ) != LUA_OK )
	{
		ALOG_ERROR_2( "Load '%s' script file failed ( %s )", filename.Str( ), _luaHelper::GetErrString( ).Str( ) );
		return _false;
	}
	
	// Run script file
	if ( lua_pcall( gLuaState, 0, LUA_MULTRET, 0 ) != LUA_OK )
	{
		ALOG_ERROR_2( "Run '%s' script file failed ( %s )", filename.Str( ), _luaHelper::GetErrString( ).Str( ) );
		return _false;
	}

	return _true;
}

#endif