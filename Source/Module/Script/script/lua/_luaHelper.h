//! @file     _luaHelper.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _luaHelper
//----------------------------------------------------------------------------

class _luaHelper
{
private:
	//!	Push number argument.
	static _void PushNumberArgLong( lua_State* l, _byte*& args_buffer, _int stack_index );
	static _void PushNumberArgDword( lua_State* l, _byte*& args_buffer, _int stack_index );
	static _void PushNumberArgBool( lua_State* l, _byte*& args_buffer, _int stack_index );
	static _void PushNumberArgFloat( lua_State* l, _byte*& args_buffer, _int stack_index );
	static _void PushNumberArgDouble( lua_State* l, _byte*& args_buffer, _int stack_index );
	//!	Push StringPtr argument.
	template< typename CharType, _ENCODING _STRING_ENCODE >
	static _void PushStringPtrArg( _byte*& args_buffer, ConstString< CharType, _STRING_ENCODE > c_string );
	//!	Push class argument.
	template< typename ObjectType >
	static _void PushClassArg( _byte*& args_buffer, const ObjectType* object );

public:
	//!	Get the error string.
	static AString GetErrString( );

	//!	Parse arguments.
	static _ubool ParseArgs( lua_State* l, _dword args_number, const ScriptVarDeclInfoArray& vars, _byte* args_buffer );
};

//----------------------------------------------------------------------------
// _luaHelper Implementation
//----------------------------------------------------------------------------

}