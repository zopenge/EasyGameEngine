//! @file     LuaVM.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

//----------------------------------------------------------------------------
// LuaDrv-VM Implementation
//----------------------------------------------------------------------------

VMXSHIPassRef LuaDrv::LoadScript( const ScriptDataDefXSHI& def )
{
	// Convert source name to ANSI
	_chara source_name_ansi[1024];
	Platform::Utf16ToAnsi( source_name_ansi, 1024, def.mSourceName.Str( ) );

	// Read the script string as ANSI
	AStringPtr script_string_ansi = (const _chara*) def.mBufferData;

	// Create and initialize virtual machine
	LuaVM* lua_vm = new LuaVM( );
	if ( lua_vm->Initialize( script_string_ansi, source_name_ansi ) == _false )
		{ EGE_RELEASE( lua_vm ); return _null; }

	return lua_vm;
}

_XSCRIPT_VM_STATUS LuaDrv::ExecuteVM( VMXSHI* vm )
{
	DYNAMIC_CAST_LUARESOURCE( VM, vm );

	return lua_vm->Execute( mLuaState );
}

_dword LuaDrv::CallGeneric( VMXSHI* vm, const NativeFunctionInfoXSHI& function_info, _void* object )
{
	DYNAMIC_CAST_LUARESOURCE( VM, vm );

	return 0;
}

VMRegisters& LuaDrv::GetVMRegisters( VMXSHI* vm )
{
	DYNAMIC_CAST_LUARESOURCE( VM, vm );

	return lua_vm->GetRegisters( );
}

_void LuaDrv::SetVMInternalExceptionDesc( VMXSHI* vm, WStringPtr exception )
{
	DYNAMIC_CAST_LUARESOURCE( VM, vm );

	lua_vm->SetExceptionDesc( exception );
}

WStringPtr LuaDrv::GetVMInternalExceptionDesc( VMXSHI* vm )
{
	DYNAMIC_CAST_LUARESOURCE( VM, vm );

	return lua_vm->GetExceptionDesc( );
}

_void LuaDrv::BeginCallNativeFunc( VMXSHI* vm )
{
	DYNAMIC_CAST_LUARESOURCE( VM, vm );

	lua_vm->GetFlags( ).CombineFlags( LuaVM::_FLAG_CALLING_NATIVE_FUNC );
}

_void LuaDrv::EndCallNativeFunc( VMXSHI* vm )
{
	DYNAMIC_CAST_LUARESOURCE( VM, vm );

	lua_vm->GetFlags( ).ClearFlags( LuaVM::_FLAG_CALLING_NATIVE_FUNC );
}

//----------------------------------------------------------------------------
// LuaVM Implementation
//----------------------------------------------------------------------------

LuaVM::LuaVM( )
{
}

LuaVM::~LuaVM( )
{
}

_void LuaVM::Bind( lua_State* lua_state )
{
	// Make the lua state in thread as string key
	_chara key[1024];
	Platform::FormatStringBuffer( key, 1024, "%d", (_dword) lua_state );

	// Get the VM table
	lua_getfield( lua_state, LUA_REGISTRYINDEX, "LuaVMTable" );
	lua_pushlightuserdata( lua_state, this );
	lua_setfield( lua_state, -2, key );
}

_XSCRIPT_VM_STATUS LuaVM::CallScript( lua_State* lua_state )
{
	// Load the script ( -1 bytes to Skip the '\0' character at the tail )
	_long ret = luaL_loadbuffer( lua_state, mScriptString.Str( ), mScriptString.SizeOfBytes( ) - 1, mSourceName.Str( ) );
	if ( ret != LUA_OK )
	{
		AStringPtr error_string_ansi = lua_tostring( lua_state, -1 );
		ALOG_ERROR_2( "Load '%s' lua script failed, error:%s", mSourceName.Str( ), error_string_ansi.Str( ) );

		return _XVMS_PARSE_SCRIPT_ERROR;
	}

	// Call it
	ret = lua_pcall( lua_state, 0, 0, 0 );
	if ( ret != LUA_OK )
	{
		AStringPtr error_string_ansi = lua_tostring( lua_state, -1 );
		ALOG_ERROR_1( "Exectue lua script failed: %s", error_string_ansi.Str( ) );

		return _XVMS_RUNTIME_ERROR;
	}

	return _XVMS_NO_ERROR;
}

_ubool LuaVM::Initialize( AStringPtr string, AStringPtr source_name )
{
	mScriptString	= string;
	mSourceName		= source_name;

	return _true;
}

_XSCRIPT_VM_STATUS LuaVM::Execute( lua_State* lua_state )
{
	LuaStackBackup stack_backup( lua_state );

	// Create thread lua state
	lua_State* lua_state_in_thread = lua_newthread( lua_state );
	if ( lua_state_in_thread == _null )
		return _XVMS_FATAL_ERROR;

	// Bind virtual machine with lua state ( thread )
	Bind( lua_state_in_thread );

	// Call script
	return CallScript( lua_state_in_thread );
}