//! @file     _luaValue.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_LUA_ == 1)

//----------------------------------------------------------------------------
// _luaValue Implementation
//----------------------------------------------------------------------------

_luaValue::_luaValue( )
{
}

_luaValue::~_luaValue( )
{
}

_ubool _luaValue::InitByRetValue( )
{
	if ( lua_isboolean( gLuaState, -1 ) )
	{
		mValue = (_ubool)lua_toboolean( gLuaState, -1 );
	}
	else if ( lua_isnumber( gLuaState, -1 ) )
	{
		mValue = (_double)lua_tonumber( gLuaState, -1 );
	}
	else if ( lua_isstring( gLuaState, -1 ) )
	{
		mValueString.FromString( _ENCODING_ANSI, lua_tostring( gLuaState, -1 ) );
		mValue.SetString( mValueString );
	}

	return _true;
}

const _void* _luaValue::GetPointer( ) const
{
	return (const _void*) mValue;
}

_double _luaValue::GetDouble( ) const 
{
	return (_double) mValue;
}

WStringR _luaValue::GetStringW( ) const
{
	return mValue.GetString( );
}

#endif