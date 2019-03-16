//! @file     LuaDrv.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// LuaDrv
//----------------------------------------------------------------------------

class LuaDrv : public INTERFACE_OBJECT_IMPL( IDynamicXSHI )
{
private:
	//!	The LUA class map with name 
	typedef Map< RefPtr< LuaClass >, _crcvalue > LuaClassMap;

private:
	//!	The LUA state
	lua_State*		mLuaState;
	//!	The EGE namespace of LUA
	LuaNamespace*	mLuaNamespace;

	//!	The allocator
	IAllocatorRef	mAllocator;

	//!	The LUA class map
	LuaClassMap		mLuaClassMap;

private:
	//!	The global functions table.
	static const luaL_Reg sGlobalFuncs[];

private:
	//!	Access the index of EGE table.
	static _long LuaUsingIndex( lua_State* lua_state );

	//!	Using the index of EGE table.
	static _long LuaUsing( lua_State* lua_state );
	//!	Get the type in string.
	static _long LuaGetType( lua_State* lua_state );
	//!	Get the address/pointer.
	static _long LuaGetPointer( lua_State* lua_state );
	//!	Copy.
	static _long LuaCopy( lua_State* lua_state );

	//!	Allocate memory in LUA.
	static _void* LuaAllocate( _void* ud, _void* ptr, size_t osize, size_t nsize );

private:
	//!	Register global functions.
	_ubool RegisterGlobalFunctions( );

	//!	Register LUA class.
	_void RegisterLuaClass( WStringPtr name, LuaClass* lua_class );
	//!	Unregister LUA class.
	_void UnregisterLuaClass( WStringPtr name );

public:
	LuaDrv( );
	virtual ~LuaDrv( );

public:
	//!	Get the singleton instance.
	static LuaDrv* GetInstance( )
	{
		return static_cast< LuaDrv* >( gDynamicXSHI );
	}

public:
	//!	Search the LUA class by name.
	LuaClass* SearchLuaClassByName( AStringPtr name );
	const LuaClass* SearchLuaClassByName( AStringPtr name ) const;

// IDynamicXSHI Interface
public:
	// The XSHI methods are defined as virtual functions.
	#define DEFINE_XSHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Interface/Module/Script/XSHIMethods.h"
	#undef DEFINE_XSHIMETHOD
};

}