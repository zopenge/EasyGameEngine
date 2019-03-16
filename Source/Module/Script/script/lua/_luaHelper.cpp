//! @file     _luaHelper.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_LUA_ == 1)

//----------------------------------------------------------------------------
// _luaHelper Helpful Functions Implementation
//----------------------------------------------------------------------------

template< typename Type >
_void PushNumberArg( lua_State* l, _byte*& args_buffer, _int stack_index )
{
	Type value = 0;

	_int type = lua_type( l, stack_index );
	switch ( type )
	{
		case LUA_TNUMBER:
		{
			value = (Type) lua_tonumber( l, stack_index );
		}
		break;

		case LUA_TBOOLEAN:
		{
			value = (Type) lua_toboolean( l, stack_index );
		}
		break;
		
		default:
			EGE_ASSERT( 0 );
			break;
	}
	
	*(Type*) args_buffer = value;
	args_buffer += sizeof( Type );
}

template<>
_void PushNumberArg< _ubool >( lua_State* l, _byte*& args_buffer, _int stack_index )
{
	_ubool value = 0;

	_int type = lua_type( l, stack_index );
	switch ( type )
	{
		case LUA_TNUMBER:
		{
			value = (_ubool)((int) lua_tonumber( l, stack_index ));
		}
		break;

		case LUA_TBOOLEAN:
		{
			value = (_ubool) lua_toboolean( l, stack_index );
		}
		break;
		
		default:
			EGE_ASSERT( 0 );
			break;
	}
	
	*(_ubool*) args_buffer = value;
	args_buffer += sizeof( _ubool );
}

//----------------------------------------------------------------------------
// _luaHelper Implementation
//----------------------------------------------------------------------------

_void _luaHelper::PushNumberArgLong( lua_State* l, _byte*& args_buffer, _int stack_index )
{
	PushNumberArg< _int >( l, args_buffer, stack_index );
}

_void _luaHelper::PushNumberArgDword( lua_State* l, _byte*& args_buffer, _int stack_index )
{
	PushNumberArg< _dword >( l, args_buffer, stack_index );
}

_void _luaHelper::PushNumberArgBool( lua_State* l, _byte*& args_buffer, _int stack_index )
{
	PushNumberArg< _ubool >( l, args_buffer, stack_index );
}

_void _luaHelper::PushNumberArgFloat( lua_State* l, _byte*& args_buffer, _int stack_index )
{
	PushNumberArg< _float >( l, args_buffer, stack_index );
}

_void _luaHelper::PushNumberArgDouble( lua_State* l, _byte*& args_buffer, _int stack_index )
{
	PushNumberArg< _double >( l, args_buffer, stack_index );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_void _luaHelper::PushStringPtrArg( _byte*& args_buffer, ConstString< CharType, _STRING_ENCODE > c_string )
{
	// Get the C string buffer size
	_dword size = c_string.SizeOfBytes( );

	// Allocate and copy C string buffer
	_byte* string_buf = new _byte[ size ];
	EGE_MEM_CPY( string_buf, (const _byte*) c_string.Str( ), size );
	EGE_ASSERT( string_buf != _null );

	// Save into string object
	ConstString< CharType, _STRING_ENCODE >* string_ptr = new ConstString< CharType, _STRING_ENCODE >( );
	*string_ptr = (const CharType*) string_buf;

	// Push into argument buffer
	*(size_t*)args_buffer = (size_t)string_ptr;
	args_buffer += sizeof( ConstString< CharType, _STRING_ENCODE >* );
}

template< typename ObjectType >
_void _luaHelper::PushClassArg( _byte*& args_buffer, const ObjectType* object )
{    
#if (_PLATFORM_ARCH_64 == 1)
    *(_qword*) args_buffer = (_qword) object;
    args_buffer += sizeof( _qword );
#else
	*(_dword*) args_buffer = (_dword) object;
	args_buffer += sizeof( _dword );
#endif
}

AString _luaHelper::GetErrString( )
{
	// Get lua error string
	AString err_string = lua_tostring( gLuaState, -1 );

	// Pop error string
	lua_pop( gLuaState, 1 );

	return err_string;
}

_ubool _luaHelper::ParseArgs( lua_State* l, _dword args_number, const ScriptVarDeclInfoArray& vars, _byte* args_buffer )
{
	for ( _dword i = 0; i < args_number; i ++ )
	{
		const ScriptVarDeclInfo& var = vars[i];

		// Get lua stack index
		_int stack_index = i - args_number;

		switch ( var.mTypeID )
		{
			case ScriptVarDeclInfo::_TYPE_INT32:
			{
				PushNumberArgLong( l, args_buffer, stack_index );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_UINT32:
			{
				PushNumberArgDword( l, args_buffer, stack_index );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_UBOOL:
			{
				PushNumberArgBool( l, args_buffer, stack_index );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_FLOAT:
			{
				PushNumberArgFloat( l, args_buffer, stack_index );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_DOUBLE:
			{
				PushNumberArgDouble( l, args_buffer, stack_index );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_OBJECT:
			{
				// Get the object
				const _byte* object = (const _byte*) tolua_tousertype( l, stack_index, 0 );
				EGE_ASSERT( object != _null );

				PushClassArg( args_buffer, object );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_ASTRING_PTR:	
			{
				const _chara* string = lua_tostring( l, stack_index );
				EGE_ASSERT( string != _null );

				PushStringPtrArg< _chara, _ENCODING_ANSI >( args_buffer, string );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_USTRING_PTR:	
			{
				const _chara* string = lua_tostring( l, stack_index );
				EGE_ASSERT( string != _null );

				PushStringPtrArg< _chara, _ENCODING_UTF8 >( args_buffer, string );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_WSTRING_PTR:	
			{
				const _chara* string = lua_tostring( l, stack_index );
				EGE_ASSERT( string != _null );

				PushStringPtrArg< _charw, _ENCODING_UTF16 >( args_buffer, WString( ).FromString( _ENCODING_UTF8, string ) );
			}
			break;

			default:
				EGE_ASSERT( 0 );
				break;
		}
	}

	return _true;
}

#endif