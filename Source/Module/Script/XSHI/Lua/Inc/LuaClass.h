//! @file     LuaClass.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// LuaClass
//----------------------------------------------------------------------------

class LuaClass : public LuaTable< TClassXSHI< ClassXSHI > >
{
private:
	typedef LuaTable< TClassXSHI< ClassXSHI > > BaseClass;

private:
	//!	The property map with name 
	typedef Map< DataTypeDefXSHI, _crcvalue > PropertyMap;

private:
	//!	The class name.
	AString		mName;
	//!	The properties
	PropertyMap	mPropertyMap;

private:
	//!	Get the current virtual machine.
	LuaVM* GetCurVM( lua_State* lua_state );

	//!	Push instance.
	_void PushInstance( lua_State* lua_state, _void* instance );

// LuaObject Interface
private:
	virtual _void OnPushImplementation( lua_State* lua_state ) override;

// LuaTable Interface
private:
	virtual _long __index( lua_State* lua_state ) override;
	virtual _long __newindex( lua_State* lua_state ) override;

	virtual _long __call( lua_State* lua_state ) override;
	virtual _long __garbage_collect( lua_State* lua_state ) override;
	virtual _long __tostring( lua_State* lua_state ) override;
	virtual _long __eq( lua_State* lua_state ) override;

public:
	LuaClass( );
	virtual ~LuaClass( );

public:
	//!	Get the class name.
	EGE_GET_ACCESSOR( AStringPtr, Name )

public:
	//!	Initialize.
	_ubool Initialize( const ClassDefXSHI& def );

	//!	Register property.
	_ubool RegisterProperty( WStringPtr name, const DataTypeDefXSHI& def );
};

}