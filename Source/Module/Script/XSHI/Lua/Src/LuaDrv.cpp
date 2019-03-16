//! @file     LuaDrv.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

const luaL_Reg LuaDrv::sGlobalFuncs[] = 
{
	{ "using", LuaDrv::LuaUsing },
	{ "type", LuaDrv::LuaGetType },
	{ "rawptr", LuaDrv::LuaGetPointer },
	{ "copy", LuaDrv::LuaCopy },
	{ _null, _null }
};

//----------------------------------------------------------------------------
// LuaDrv Implementation
//----------------------------------------------------------------------------

LuaDrv::LuaDrv( )
{
	mLuaState		= _null;
	mLuaNamespace	= _null;
}

LuaDrv::~LuaDrv( )
{
	LuaHelper::GetInstance( ).Finalize( );

	EGE_RELEASE( mLuaNamespace );

	// Release LUA
	if ( mLuaState != _null )
		::lua_close( mLuaState );
}

_long LuaDrv::LuaUsingIndex( lua_State* lua_state )
{
	//lua_pushnil( lua_state );

	//// Get the 
	//while( lua_next(L, lua_upvalueindex(1)) )
	//{
	//	lua_pushvalue(L,2); // key
	//	lua_gettable(L, -2); 
	//	if (!lua_isnil(L,-1))
	//	{
	//		return 1;
	//	}
	//	lua_pop(L,2);
	//}
	return 0;
}

_long LuaDrv::LuaUsing( lua_State* lua_state )
{
	LuaStackBackup stack_backup( lua_state );

	// The top of stack should be a table
	luaL_checktype( lua_state, 1, LUA_TTABLE );

	// Register a "EGE_using" table if not exist
	lua_getfield( lua_state, LUA_REGISTRYINDEX, "EGE_using" );
	if ( lua_isnil( lua_state, -1 ) )
	{
		// Pop nil value
		lua_pop( lua_state, 1 );

		// Set meta-table of global table
		lua_pushglobaltable( lua_state ); // [1:_G] --> _G = globals
		if ( !lua_getmetatable( lua_state, -1 ) )
		{
			lua_newtable( lua_state ); // [2:_G,MT] --> MT = MetaTable (for globals)
			// set as metatable of _G (keeping a copy)
			lua_pushvalue( lua_state, -1 ); //[3:_G,MT,MT]
			lua_setmetatable( lua_state, -3 ); // [2:_G,MT]
		}

		// [2:(_G)(MT)]
		lua_newtable( lua_state ); // [3:_G,MT,EGE_using] SU --> create the "EGE_using" table
		lua_pushvalue( lua_state, -1 ); // [4:_G,MT,EGE_using,EGE_using] --> keep a copy in registry 
		lua_setfield( lua_state, LUA_REGISTRYINDEX, "EGE_using" ); // [3:_G,MT,EGE_using]

		// push the using_index func with the EGE_using table as closure
		lua_pushvalue( lua_state, -1 ); //[4:_G,MT,EGE_using,EGE_using]
		lua_pushcclosure( lua_state, LuaUsingIndex, 1 ); // [4:_G,MT,EGE_using,func] func -> push the closure
		// set this functions as "__index" of the metatable (at -3)
		lua_setfield( lua_state, -3, "__index" ); // 3[4:_G,MT_SU]

		// leave the EGE_using table at the top
	}

	lua_pushvalue( lua_state,1 ); // get the first argument
	//TODO check not repeating tables...
	luaL_ref( lua_state, -2 ); // add the table

	return 0;
}

_long LuaDrv::LuaGetType( lua_State* lua_state )
{
	//SLB_DEBUG_CALL;
	//const ClassInfo *ci = Manager::getInstance(L)->getClass(L,-1);
	//if (ci)
	//{
	//	lua_pushstring(L, ci->getName().c_str());
	//	return 1;
	//}
	return 0;
}

_long LuaDrv::LuaGetPointer( lua_State* lua_state )
{
	//SLB_DEBUG_CALL;
	//int top = lua_gettop(L);
	//if (lua_getmetatable(L,1))
	//{
	//	lua_getfield(L, -1, "__class_ptr");
	//	if (!lua_isnil(L,-1))
	//	{
	//		ClassInfo* ci = reinterpret_cast<ClassInfo*>( lua_touserdata(L,-1) );
	//		const void* raw = ci->get_const_ptr(L, 1);
	//		lua_settop(L, top);
	//		lua_pushinteger(L, (lua_Integer) raw);
	//		return 1;
	//	}
	//}
	//lua_settop(L, top);
	return 0;
}

_long LuaDrv::LuaCopy( lua_State* lua_state )
{
	//SLB_DEBUG_CALL;
	//int top = lua_gettop(L);
	//if (lua_getmetatable(L,1))
	//{
	//	lua_getfield(L, -1, "__class_ptr");
	//	if (!lua_isnil(L,-1))
	//	{
	//		ClassInfo* ci = reinterpret_cast<ClassInfo*>( lua_touserdata(L,-1) );
	//		lua_settop(L, top);
	//		ci->push_copy(L, ci->get_const_ptr(L,1));
	//		return 1;
	//	}
	//}
	//lua_settop(L, top);
	return 0;
}

_void* LuaDrv::LuaAllocate( _void* ud, _void* ptr, size_t osize, size_t nsize )
{
	LuaDrv* lua_drv = (LuaDrv*) ud;
	EGE_ASSERT( lua_drv != _null );

	// Free memory
	if ( nsize == 0 )
	{
		lua_drv->mAllocator->Free( ptr );
		return _null;
	}

	// Allocate memory
	return ptr = lua_drv->mAllocator->ReAlloc( ptr, nsize );
}

_ubool LuaDrv::RegisterGlobalFunctions( )
{
	LuaStackBackup stack_backup( mLuaState );

	// Register global functions
	lua_newtable( mLuaState );
	luaL_setfuncs( mLuaState, sGlobalFuncs, 0 );
	// Keep a copy of the SLB table before setting the global EGE
	lua_pushvalue( mLuaState, -1 );
	lua_setglobal( mLuaState, "EGE" ); // "EGE" global name is EGE global functions table

	// Set the metatable of "EGE"
	lua_newtable( mLuaState );
	lua_pushstring( mLuaState, "__index" );
	mLuaNamespace->Push( mLuaState );
	lua_rawset( mLuaState, -3 );
	lua_setmetatable( mLuaState, -2 ); // EGE table

	// Set the VM table
	lua_newtable( mLuaState );
	lua_setfield( mLuaState, LUA_REGISTRYINDEX, "LuaVMTable" );

	return _true;
}

_void LuaDrv::RegisterLuaClass( WStringPtr name, LuaClass* lua_class )
{
	// Convert the name to ANSI
	_chara name_ansi[1024];
	Platform::Utf16ToAnsi( name_ansi, 1024, name.Str( ) );

	// Save the LUA class
	mLuaClassMap[ CRC::BuildFromString( name_ansi ) ] = lua_class;
}

_void LuaDrv::UnregisterLuaClass( WStringPtr name )
{
	mLuaClassMap.Remove( name.GetCRCValue( ) );
}

LuaClass* LuaDrv::SearchLuaClassByName( AStringPtr name ) 
{
	RefPtr< LuaClass >* lua_class = mLuaClassMap.Search( name.GetCRCValue( ) );
	if ( lua_class == _null )
		return _null;

	return *lua_class;
}

const LuaClass* LuaDrv::SearchLuaClassByName( AStringPtr name ) const 
{
	const RefPtr< LuaClass >* lua_class = mLuaClassMap.Search( name.GetCRCValue( ) );
	if ( lua_class == _null )
		return _null;

	return *lua_class;
}

_ubool LuaDrv::Initialize( )
{
	// Create allocator
	mAllocator = GetInterfaceFactory( )->CreateMemAllocator( 1 MB );
	if ( mAllocator.IsNull( ) )
		return _false;

	// Create LUA state
	mLuaState = ::lua_newstate( (lua_Alloc) LuaAllocate, this );
	if ( mLuaState == _null )
		return _false;

	// Load default libraries
	::luaL_openlibs( mLuaState );

	// Initialize LUA helper
	if ( LuaHelper::GetInstance( ).Initialize( mLuaState ) == _false )
	{
		WLOG_ERROR( L"Initialize LUA helper failed" );
		return _false;
	}

	// Create the namespace
	mLuaNamespace = new LuaNamespace( );

	// Register all global functions
	if ( RegisterGlobalFunctions( ) == _false )
		return _false;

	// Output the LUA version
	ALOG_TRACE_1( "Load LUA script library, version: %s", LUA_VERSION );

	return _true;
}

_void LuaDrv::Tick( _dword elapse )
{
}