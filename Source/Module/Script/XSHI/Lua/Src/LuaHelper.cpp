//! @file     LuaHelper.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

//----------------------------------------------------------------------------
// LuaHelper Implementation
//----------------------------------------------------------------------------

LuaHelper::LuaHelper( )
{
	mLuaState = _null;
}

LuaHelper::~LuaHelper( )
{

}

_ubool LuaHelper::Initialize( lua_State* lua_state )
{
	mLuaState = lua_state;

	return _true;
}

_void LuaHelper::Finalize( )
{

}

//_ubool LuaHelper::CreateTable( WStringPtr table_name, ILuaTableNotifier* notifier )
//{
//	return _true;
//}
//
//_ubool LuaHelper::RegisterMethod( WStringPtr table_name, WStringPtr method_name )
//{
//	return _true;
//}
