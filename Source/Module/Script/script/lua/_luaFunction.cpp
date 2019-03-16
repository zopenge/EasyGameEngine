//! @file     _luaFunction.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_LUA_ == 1)

//----------------------------------------------------------------------------
// _luaFunction Implementation
//----------------------------------------------------------------------------

_luaFunction::_luaFunction( )
{
}

_luaFunction::~_luaFunction( )
{
}

_ubool _luaFunction::Initialize( AStringPtr func_name )
{
	// Check whether function is existing
	lua_getglobal( gLuaState, func_name.Str( ) );
	if ( lua_isfunction( gLuaState, 1 ) != 1 )
	{
		ALOG_ERROR_1( "The lua function '%s' is not existing", func_name.Str( ) );
		return _false;
	}

	mFuncName = func_name;

	return _true;
}

AStringPtr _luaFunction::GetName( ) const
{
	return mFuncName.Str( );
}

_scriptValuePassRef _luaFunction::Invoke( )
{
	static VariableArray sVariableArray;
	return Invoke( sVariableArray );
}

_scriptValuePassRef _luaFunction::Invoke( const VariableArray& vars )
{
	// Locate at the function
	lua_getglobal( gLuaState, mFuncName.Str( ) ); 

	// Push arguments
	for ( _dword i = 0; i < vars.Number( ); i ++ )
	{
		const Variable& var = vars[i];

		// It's string
		if ( var.IsString( ) )
		{
			lua_pushstring( gLuaState, AString( ).FromString( var.GetString( ) ).Str( ) );
		}
		// It's float
		else if ( var.IsFloat( ) || var.IsDouble( ) )
		{
			lua_pushnumber( gLuaState, (_double) var );
		}
		// It's number or integer
		else if ( var.IsInteger( ) )
		{
			if ( var.IsSigned( ) )
				lua_pushinteger( gLuaState, (_int) var );
			else
				lua_pushunsigned( gLuaState, (_dword) var );
		}
		// It's boolean
		else if ( var.IsBoolean( ) )
		{
			lua_pushinteger( gLuaState, (_boolean)var );
		}
		// Unknown type
		else
		{
			EGE_ASSERT( 0 );
		}
	}

	// Call function
	if ( lua_pcall( gLuaState, vars.Number( ), 1, 0 ) != 0 )
	{
		ALOG_ERROR_2( "Invoke '%s' script function failed ( %s )", mFuncName.Str( ), _luaHelper::GetErrString( ).Str( ) );
		return _null;
	}

	// Save the return value
	_luaValue* lua_value = new _luaValue( );
	if ( lua_value->InitByRetValue( ) == _false )
	{ 
		EGE_RELEASE( lua_value ); 
		return _null; 
	}

	// Pop the return value
	lua_pop( gLuaState, 1 );

	return lua_value;
}

#endif