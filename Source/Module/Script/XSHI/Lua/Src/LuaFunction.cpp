//! @file     LuaFunction.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

//----------------------------------------------------------------------------
// LuaDrv-Function Implementation
//----------------------------------------------------------------------------

_ubool LuaDrv::RegisterGlobalFunction( const NativeFunctionDefXSHI& def )
{
	return _true;
}

_dword LuaDrv::GetGlobalFunctionNumber( ) const
{
	return 0;
}

FunctionXSHIRef LuaDrv::GetGlobalFunctionByIndex( _dword index ) const
{
	return _null;
}

const NativeFunctionInfoXSHI& LuaDrv::GetFunctionInfo( FunctionXSHI* function ) const
{
	DYNAMIC_CAST_LUARESOURCE( Function, function );

	return lua_function->GetFunctionInfo( );
}

//----------------------------------------------------------------------------
// LuaFunction Implementation
//----------------------------------------------------------------------------

LuaFunction::LuaFunction( )
{

}

LuaFunction::~LuaFunction( )
{

}

_long LuaFunction::Invoke( lua_State* state )
{
	// Get LUA script function
	LuaFunction* lua_function = (LuaFunction*) lua_touserdata( state, lua_upvalueindex( 1 ) );
	EGE_ASSERT( lua_function != _null );

	return 0;
}

_ubool LuaFunction::Initialize( lua_State* state, const NativeFunctionDefXSHI& def )
{
	// Convert method name to ANSI
	_chara method_name_ansi[1024];
	Platform::Utf16ToAnsi( method_name_ansi, 1024, def.mName.Str( ) );

	// Register and bind script function with LUA
	lua_pushlightuserdata( state, (_void*) this );
	lua_pushcclosure( state, Invoke, 1 ); // We only need to push 'this' pointer on this registered function, so use one element on the stack is enough
	lua_setglobal( state, method_name_ansi );

	return _true;
}
