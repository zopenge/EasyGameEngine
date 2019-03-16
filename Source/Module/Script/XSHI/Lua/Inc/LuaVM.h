//! @file     LuaVM.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// LuaVM
//----------------------------------------------------------------------------

class LuaVM : public TVMXSHI< VMXSHI >
{
private:
	//!	The lua script string
	AString	mScriptString;
	//!	The source name
	AString	mSourceName;

private:
	//!	Bind VM with LUA state.
	_void Bind( lua_State* lua_state );

	//!	Call script.
	_XSCRIPT_VM_STATUS CallScript( lua_State* lua_state );

public:
	LuaVM( );
	virtual ~LuaVM( );

public:
	//!	Initialize.
	_ubool Initialize( AStringPtr string, AStringPtr source_name );

	//!	Execute.
	_XSCRIPT_VM_STATUS Execute( lua_State* lua_state );
};

}