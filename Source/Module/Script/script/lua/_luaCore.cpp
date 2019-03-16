//! @file     _luaCore.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_LUA_ == 1)

//----------------------------------------------------------------------------
// _luaCore Implementation
//----------------------------------------------------------------------------

_luaCore::_luaCore( )
{
}

_luaCore::~_luaCore( )
{
}

_ubool _luaCore::ReadScriptString( AStringPtr filename, AString& string )
{
	// Get the script stream reader
	IStreamReaderRef stream_reader = GetWorkingArchive( )->LoadResourceByName( WString( ).FromString( filename ) );
	if ( stream_reader.IsNull( ) )
		return _false;

	// Read the script string
	MemArrayPtr< _byte > buffer( stream_reader->GetSize( ) );
	stream_reader->ReadBuffer( buffer, stream_reader->GetSize( ) );

	string.CopyString( (const _chara*)buffer.GetPointer( ), buffer.Number( ) );

	return _true;
}

_int _luaCore::OnRequireCallback( lua_State* l )
{
	_luaCore* lua_core = (_luaCore*) lua_touserdata( l, lua_upvalueindex( 1 ) );
	EGE_ASSERT( lua_core != _null );

	// Get the file name
	const _chara* filename = lua_tostring( l, -1 );
	EGE_ASSERT( filename != _null );

	// If we have already require it then skip it
	if ( lua_core->mRequiredFiles.SearchAscending< AStringPtr >( filename ).IsValid( ) == _false )
	{
		// Load the script string
		AString script_string;
		if ( lua_core->ReadScriptString( filename, script_string ) == _false )
		{
			tolua_error( l, FORMAT_ASTRING_1( "Load '%s' script file failed in require command" , filename ), _null );
			return 1;
		}

		// Load script file
		if ( luaL_loadbuffer( gLuaState, script_string.Str( ), script_string.GetLength( ), filename ) != LUA_OK )
		{
			tolua_error( l, FORMAT_ASTRING_2( "Load '%s' failed in require command: %s", filename, _luaHelper::GetErrString( ).Str( ) ), _null );
			return 1;
		}

		// Run script file
		if ( lua_pcall( gLuaState, 0, LUA_MULTRET, 0 ) != LUA_OK )
		{
			tolua_error( l, FORMAT_ASTRING_2( "Compile '%s' failed in require command: %s", filename, _luaHelper::GetErrString( ).Str( ) ), _null );
			return 1;
		}

		// Update required files list
		lua_core->mRequiredFiles.InsertAscending( AString( filename ) );
	}

	return 1;
}

_int _luaCore::OnPrintCallback( lua_State* l )
{
	_luaCore* lua_core = (_luaCore*)lua_touserdata( l, lua_upvalueindex( 1 ) );
	EGE_ASSERT( lua_core != _null );

	int n = lua_gettop( l );  /* number of arguments */
	int i;
	lua_getglobal( l, "tostring" );
	for ( i = 1; i <= n; i++ ) {
		const char *s;
		size_t r;
		lua_pushvalue( l, -1 );  /* function to be called */
		lua_pushvalue( l, i );   /* value to print */
		lua_call( l, 1, 1 );
		s = lua_tolstring( l, -1, &r );  /* get result */
		if ( s == NULL )
			return luaL_error( l,
				LUA_QL( "tostring" ) " must return a string to " LUA_QL( "print" ) );
		if ( i > 1 ) 
		{
			ALOG_TRACE( "\t" );
		}
		ALOG_TRACE( s );
		lua_pop( l, 1 );  /* pop result */
	}

	return 1;
}

_ubool _luaCore::Initialize( )
{
	WLOG_TRACE( L"Initialize LUA core ..." );

	// Register user type
	tolua_module( gLuaState, _null, 0 );
	tolua_usertype( gLuaState, "LuaCore" );

	// Register function
	tolua_beginmodule( gLuaState, _null );
		tolua_cclass( gLuaState, "LuaCore", "LuaCore", "", _null );
		tolua_beginmodule( gLuaState, "LuaCore" );
			tolua_userfunction( gLuaState, "Require", OnRequireCallback, this );
			tolua_userfunction( gLuaState, "Print", OnPrintCallback, this );
		tolua_endmodule( gLuaState );
	tolua_endmodule( gLuaState );

	WLOG_TRACE( L"Initialize LUA core OK" );

	return _true;
}

_void _luaCore::Finalize( )
{
	mRequiredFiles.Clear( _true );
}

_void _luaCore::AddRequiredFile( AStringPtr filename )
{
	if ( mRequiredFiles.SearchAscending( filename ).IsValid( ) == _false )
		mRequiredFiles.InsertAscending( filename );
}

#endif