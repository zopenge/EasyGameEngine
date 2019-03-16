//! @file     LuaClass.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

//----------------------------------------------------------------------------
// LuaDrv-Class Implementation
//----------------------------------------------------------------------------

ClassXSHIPassRef LuaDrv::RegisterClass( const ClassDefXSHI& def )
{
	// Create LUA class
	LuaClass* lua_class = new LuaClass( );
	if ( lua_class->Initialize( def ) == _false )
		{ EGE_RELEASE( lua_class ); return _null; }

	// Register the LUA class
	RegisterLuaClass( def.mName, lua_class );

	return lua_class;
}

_ubool LuaDrv::RegisterClassProperty( ClassXSHI* script_class, const ClassPropertyDefXSHI& def )
{
	DYNAMIC_CAST_LUARESOURCE( Class, script_class );

	// Register property
	return lua_script_class->RegisterProperty( def.mName, def.mDataTypeDef );
}

_ubool LuaDrv::RegisterClassBehaviour( ClassXSHI* script_class, _XSCRIPT_BEHAVIOUR behaviour, const FuncPtrXSHI& func )
{
	DYNAMIC_CAST_LUARESOURCE( Class, script_class );

	// Register behaviour
	lua_script_class->SetBehaviourFunc( behaviour, func );

	return _true;
}

_dword LuaDrv::GetClassNumber( ) const
{
	return 0;
}

ClassXSHIRef LuaDrv::GetClassByName( AStringPtr name )
{
	RefPtr< LuaClass >* lua_class = mLuaClassMap.Search( name.GetCRCValue( ) );
	if ( lua_class == _null )
		return _null;

	return (ClassXSHI*) *lua_class;
}

ClassXSHIRef LuaDrv::GetClassByName( WStringPtr name )
{
	_chara name_ansi[1024];
	Platform::Utf16ToAnsi( name_ansi, 1024, name.Str( ) );

	return GetClassByName( name_ansi );
}

//----------------------------------------------------------------------------
// LuaClass Implementation
//----------------------------------------------------------------------------

LuaClass::LuaClass( )
{

}

LuaClass::~LuaClass( )
{

}

LuaVM* LuaClass::GetCurVM( lua_State* lua_state )
{
	LuaStackBackup stack_backup( lua_state );

	// Make the lua state in thread as string key
	_chara key[1024];
	Platform::FormatStringBuffer( key, 1024, "%d", (_dword) lua_state );

	// Get the LUA VM table
	lua_getfield( lua_state, LUA_REGISTRYINDEX, "LuaVMTable" );
	if ( lua_isnil( lua_state, -1 ) )
		return _null;

	// Get the VM instance pointer
	lua_getfield( lua_state, -1, key );
	if ( lua_islightuserdata( lua_state, -1 ) )
		return (LuaVM*) lua_touserdata( lua_state, -1 );

	return _null;
}

_void LuaClass::PushInstance( lua_State* lua_state, _void* instance )
{
    int top = lua_gettop( lua_state );
    
	// Create user object ( top + 1 )
    _void** object = static_cast<_void**>( lua_newuserdata( lua_state, sizeof( _void* ) ) );
    *object = instance;

    // Get metatable (class table's metatable)
    Push( lua_state );  // (table) top+2
    lua_getmetatable( lua_state, -1 );
    lua_replace( lua_state, -2 );

	// Set the instance's meta-table to object meta-table
    lua_pushvalue( lua_state, -1 );
    lua_setmetatable( lua_state, top + 1 );

	// Return instance ( user object )
    lua_settop( lua_state, top + 1 );

	// The top of stack is user object instance now
}

_void LuaClass::OnPushImplementation( lua_State* lua_state )
{
	BaseClass::OnPushImplementation( lua_state );

	// Get the meta-table of class
	lua_getmetatable( lua_state, -1 );

	// meta[ "__class_info_ptr" ] = LuaClass
	lua_pushstring( lua_state, "__class_ptr" );
	lua_pushlightuserdata( lua_state, (_void*) this );
	lua_rawset( lua_state, -3 );

	// Remove meta-table
	lua_pop( lua_state, 1 ); 
}

_long LuaClass::__index( lua_State* lua_state )
{
	return 0;
}

_long LuaClass::__newindex( lua_State* lua_state )
{
	return 0;
}

_long LuaClass::__call( lua_State* lua_state )
{
	// Get the constructor function
	const FuncPtrXSHI* constructor = GetBehaviourFunc( _XB_CONSTRUCTOR );
	if ( constructor == _null )
	{
		luaL_error( lua_state, "LuaClass '%s' doesn't register constructor", mName.Str( ) );
		return 0;
	}

	// Get the current VM
	LuaVM* vm = GetCurVM( lua_state );
	EGE_ASSERT( vm != _null );

	// Invoke it
	NativeFunctionInfoXSHI function_info( *constructor );
	ScriptCallFunc::CallFunction( vm, function_info, _null );

	// Get the instance object from value register
	_void* instance = (_void*) vm->GetRegisters( ).mValueRegister;
	if ( instance == _null )
	{
		luaL_error( lua_state, "LuaClass '%s' invoke constructor to create instance failed", mName.Str( ) );
		return 0;
	}
	
	// Push instance
	PushInstance( lua_state, instance );

	return 0;
}

_long LuaClass::__garbage_collect( lua_State* lua_state )
{
	// Get the instance object
	_void* raw_ptr	= lua_touserdata( lua_state, 1 );
	_void* instance = *static_cast<_void**>( raw_ptr );

	// Get the destructor function
	const FuncPtrXSHI* destructor = GetBehaviourFunc( _XB_DESTRUCTOR );
	if ( destructor == _null )
	{
		luaL_error( lua_state, "LuaClass '%s' doesn't register constructor", mName.Str( ) );
		return 0;
	}

	// Build the stack
	_dword stack[1] = { (_dword) instance };

	// Build the VM registers
	VMRegisters vm_registers;
	vm_registers.mStackPointer = stack;

	// Build the native function info
	NativeFunctionInfoXSHI function_info( *destructor );
	function_info.mParamSize = 4; // The instance object as parameter

	// Invoke it
	ScriptCallFunc::CallFunction( vm_registers, function_info );

	return 0;
}

_long LuaClass::__tostring( lua_State* lua_state )
{
	return 0;
}

_long LuaClass::__eq( lua_State* lua_state )
{
	return 0;
}

_ubool LuaClass::Initialize( const ClassDefXSHI& def )
{
	// Set the class name
	mName.FromString( def.mName );

	return _true;
}

_ubool LuaClass::RegisterProperty( WStringPtr name, const DataTypeDefXSHI& def )
{
	mPropertyMap[ name.GetCRCValue( ) ] = def;

	return _true;
}