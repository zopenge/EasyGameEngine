//! @file     _luaSystem.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_LUA_ == 1)

lua_State*	EGE::gLuaState = _null;

//----------------------------------------------------------------------------
// _luaSystem Implementation
//----------------------------------------------------------------------------

_luaSystem::_luaSystem( )
{
	mVersion	= Version( AStringPtr( LUA_VERSION_MAJOR "." LUA_VERSION_MINOR ) );

	mLuaState	= _null;
}

_luaSystem::~_luaSystem( )
{
	WLOG_TRACE( L"Finalize lua script module ..." );

	// Clear all modules
	mModules.Clear( _true );

	// Finalize core
	_luaCore::GetInstance( ).Finalize( );

	// Delete lua state
	if ( mLuaState != _null )
	{
		lua_gc( mLuaState, LUA_GCCOLLECT, 0 );
		lua_close( mLuaState );
	}

	gLuaState = _null;

	WLOG_TRACE( L"Finalize lua script module OK" );
}

_void* _luaSystem::OnAllocate( void* ud, void* ptr, size_t osize, size_t nsize )
{
	_luaSystem* lua_system = (_luaSystem*) ud;
	EGE_ASSERT( lua_system != _null );

	// Free memory
	if ( nsize == 0 )
	{
		lua_system->mTotalMemSize -= osize;

		free( ptr );
		
		return _null;
	}

	lua_system->mTotalMemSize += nsize;

	// Allocate memory
	return realloc( ptr, nsize ); 
}

void luna_printStack( lua_State* L, bool compact )
{
	if ( compact )
	{
		ALOG_ERROR_1( "stack top:%d - ", lua_gettop( L ) );
	}
	else
	{
		ALOG_ERROR_1( "stack trace: top %d\n", lua_gettop( L ) );
	}

	for ( int ist = 1; ist <= lua_gettop( L ); ist++ ) {
		if ( compact )
		{
			ALOG_ERROR_2( "%d:%c", ist, luaL_typename( L, ist )[0] );
		}
		else
		{
			ALOG_ERROR_2( "%d:%s", ist, luaL_typename( L, ist ) );
		}
		if ( lua_isnumber( L, ist ) == 1 ) {
			ALOG_ERROR_1( "=%f ", (float)lua_tonumber( L, ist ) );
		}
		else if ( lua_isstring( L, ist ) == 1 ) {
			ALOG_ERROR_1( "=%s ", lua_tostring( L, ist ) );
		}
		else {
			ALOG_ERROR( " " );
		}
		if ( !compact )ALOG_ERROR( "\n" );
	}
	ALOG_ERROR( "\n" );
}

_int _luaSystem::OnPreloadModule( lua_State* l )
{
	// Get the script system
	const _luaSystem* lua_system = (const _luaSystem*) gInternalScriptSystem;
	EGE_ASSERT( lua_system != _null );

	// Get the module name
	const _chara* module_name = lua_tostring( l, -1 );
	EGE_ASSERT( module_name != _null );

	// Get the module info
	const PreloadModuleInfo* module_info = lua_system->mPreloadModules.Search( module_name );
	EGE_ASSERT( module_info != _null );

	// Load the module
	if ( luaL_dostring( l, module_info->mCode.Str( ) ) )
	{
		luna_printStack( l, _false );
		lua_error( l );
	}

	return 1;
}

_void _luaSystem::Tick( _dword limited_elapse, _dword elapse )
{
}

_ubool _luaSystem::Initialize( )
{
	WLOG_TRACE( L"Create lua script module ..." );

	// Create lua state
	mLuaState = lua_newstate( (lua_Alloc) OnAllocate, this );
	if ( mLuaState == _null )
		return _false;

	gLuaState = mLuaState;

	// Load default libraries
	luaL_openlibs( mLuaState );

	// Initialize ToLua library
	tolua_open( mLuaState );

	// Initialize LUA core
	if ( _luaCore::GetInstance( ).Initialize( ) == _false )
		return _false;

	WLOG_TRACE_1( L"Create lua script module DONE[ver:%s]", mVersion.ToWString( ).Str( ) );

	return _true;
}

_ubool _luaSystem::SetRemoteDebugger( const Address& address )
{
	if ( address.IsValid() == _false )
		return _false;

	// Initialize socket core
	if ( mRemoteAddress.IsValid( ) == _false )
	{
		luaopen_socket_core( mLuaState );

		// Preload debug module
		PreloadLuaDebugger( );
	}

	// Set the remote debugger
	if ( BaseClass::SetRemoteDebugger( address ) == _false )
		return _false;

	// Set the lua debug remote address and port
	AString debug_code = FORMAT_ASTRING_2( "require('mobdebug').start('%s', %d)", address.ToStringA( _false ).Str( ), address.mPort );
	if ( luaL_dostring( gLuaState, debug_code.Str( ) ) )
	{
		ALOG_ERROR_2( "Set '%s' remote debugger failed(%s)", address.ToStringA( _true ).Str( ), debug_code.Str( ) );
		return _false;
	}

	return _true;
}

_ubool _luaSystem::PreloadModule( AStringPtr name, AStringPtr code )
{
	// Update the preload module info
	PreloadModuleInfo& module_info	= mPreloadModules[ name ];
	module_info.mCode				= code;

	// Check that the module name was not already defined.
	lua_getfield( gLuaState, LUA_REGISTRYINDEX, name.Str( ) );
	EGE_ASSERT( lua_isnil( gLuaState, -1 ) || strcmp( name.Str( ), luaL_checkstring( gLuaState, -1 ) ) );
	lua_pop( gLuaState, 1 );

	// Push the module name into the registry.
	lua_pushstring( gLuaState, name.Str( ) );
	lua_setfield( gLuaState, LUA_REGISTRYINDEX, ( AString( "Preload_" ) + name ).Str( ) );

	// Preload the module
	luaL_requiref( gLuaState, name.Str( ), OnPreloadModule, 0 );

	return _true;
}

_scriptModuleRef _luaSystem::CreateScriptModule( AStringPtr name, AStringPtr desc )
{
	_luaModule* module = new _luaModule( );
	if ( module->Initialize( name, desc ) == _false )
		{ EGE_RELEASE( module ); return _null; }

	mModules.Append( module );

	return _scriptModulePassRef( module ).GetPtr( );
}

_scriptVMPassRef _luaSystem::CreateScriptVM( )
{
	_luaVM* vm = new _luaVM( );
	if ( vm->Initialize( ) == _false )
		{ EGE_RELEASE( vm ); return _null; }

	return vm;
}

#endif