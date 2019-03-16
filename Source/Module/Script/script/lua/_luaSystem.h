//! @file     _luaSystem.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//!	The global lua state
extern lua_State*	gLuaState;

//----------------------------------------------------------------------------
// _luaSystem
//----------------------------------------------------------------------------

class _luaSystem : public _t_scriptSystem< _scriptSystem >
{
private:
	typedef _t_scriptSystem< _scriptSystem > BaseClass;

private:
	//!	The preload module info
	struct PreloadModuleInfo
	{
		AString	mCode;
	};
	//!	Use the module name as key.
	typedef Map< PreloadModuleInfo, AString > PreloadModuleInfoMap;

private:
	//!	The lua state
	lua_State*				mLuaState;

	//!	The preload modules
	PreloadModuleInfoMap	mPreloadModules;

private:
	//!	Allocate memory.
	static _void* OnAllocate( void* ud, void* ptr, size_t osize, size_t nsize );

	//!	When preload module.
	static _int OnPreloadModule( lua_State* l );

public:
	_luaSystem( );
	virtual ~_luaSystem( );

// IObject Interface
public:
	virtual _void				Tick( _dword limited_elapse, _dword elapse ) override;

// _scriptSystem Interface
public:
	virtual _ubool				Initialize( ) override;

	virtual _ubool				SetRemoteDebugger( const Address& address ) override;

	virtual _ubool				PreloadModule( AStringPtr name, AStringPtr code ) override;

	virtual _scriptModuleRef	CreateScriptModule( AStringPtr name, AStringPtr desc ) override;

	virtual _scriptVMPassRef	CreateScriptVM( ) override;
};

}