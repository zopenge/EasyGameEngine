//! @file     LuaHelper.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// LuaStackBackup
//----------------------------------------------------------------------------

class LuaStackBackup
{
private:
	_long		mTop;
	lua_State*	mLuaState;

public:
	//!	Get the top.
	EGE_GET_ACCESSOR( _long, Top )

public:
	LuaStackBackup( lua_State* state ) : mLuaState( state ) 
	{
		// Backup the stack pointer
		mTop = ::lua_gettop( mLuaState );
	}
	~LuaStackBackup( )
	{
		// Resume the stack pointer
		::lua_settop( mLuaState, mTop );
	}
};

//----------------------------------------------------------------------------
// LuaHelper
//----------------------------------------------------------------------------

class LuaHelper
{
public:
	//!	It's singleton class.
	SINGLETON( LuaHelper )

private:
	//!	The LUA state
	lua_State*	mLuaState;

public:
	//!	Initialize/Finalize.
	_ubool Initialize( lua_State* lua_state );
	_void Finalize( );

	//!	Create the table.
	//_ubool CreateTable( WStringPtr table_name, ILuaTableNotifier* notifier );
	////!	Register the method of table.
	//_ubool RegisterMethod( WStringPtr table_name, WStringPtr method_name );
};

}