//! @file     _luaModule.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_LUA_ == 1)

//----------------------------------------------------------------------------
// _luaModule Implementation
//----------------------------------------------------------------------------

_luaModule::_luaModule( )
{
}

_luaModule::~_luaModule( )
{
	for ( _dword i = 0; i < mProperties.Number( ); i ++ )
		EGE_DELETE( mProperties[i] );

	for ( _dword i = 0; i < mFunctions.Number( ); i ++ )
		EGE_DELETE( mFunctions[i] );
}

int _luaModule::GlobalNew( lua_State* l )
{
	_luaModule* lua_module = (_luaModule*) lua_touserdata( l, lua_upvalueindex( 1 ) );
	EGE_ASSERT( lua_module != _null );

	// Create object
	_byte* object = _null;
	gScriptResourceManager->InvokeConstructorBehaviourFunc( object, lua_module->mName.Str( ) );

	// Feedback object
	tolua_pushusertype( l, (_void*) object, lua_module->mName.Str( ) );

	return 1;
}

int _luaModule::LocalNew( lua_State* l )
{
	_luaModule* lua_module = (_luaModule*) lua_touserdata( l, lua_upvalueindex( 1 ) );
	EGE_ASSERT( lua_module != _null );
	
	// Create object
	_byte* object = _null;
	gScriptResourceManager->InvokeConstructorBehaviourFunc( object, lua_module->mName.Str( ) );

	// Feedback object and clone it
	tolua_pushusertype( l, (_void*) object, lua_module->mName.Str( ) );
	tolua_clone( gLuaState, object, Destructor );

	return 1;
}

int _luaModule::Destructor( lua_State* l )
{
	// Get the type name
	const _chara* type_name = tolua_typename( l, 1 );
	EGE_ASSERT( type_name != _null );

	// Get the object
	_byte* object = (_byte*) tolua_tousertype( l, 1, 0 );
	EGE_ASSERT( object != _null );

	// Release object
	gScriptResourceManager->InvokeDestructorBehaviourFunc( object, type_name );

	return 0;
}

int _luaModule::Getter( lua_State* l )
{
	_byte* object = (_byte*) tolua_tousertype( l, 1, 0 );
	EGE_ASSERT( object != _null );

	PropertyInfo* property_info = (PropertyInfo*) lua_touserdata( l, lua_upvalueindex( 1 ) );
	EGE_ASSERT( property_info != _null );

	const ScriptPropertyDeclInfo& decl_info = property_info->mDeclInfo;

	switch ( decl_info.mTypeID )
	{
		case ScriptVarDeclInfo::_TYPE_INT8:
		{
			tolua_pushnumber( l, (lua_Number) (*(_tiny*) (object + decl_info.mOffset)) );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_INT16:
		{
			tolua_pushnumber( l, (lua_Number) (*(_short*) (object + decl_info.mOffset)) );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_INT32:
		{
			tolua_pushnumber( l, (lua_Number) (*(_int*) (object + decl_info.mOffset)) );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_UINT8:
		{
			tolua_pushnumber( l, (lua_Number) (*(_byte*) (object + decl_info.mOffset)) );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_UINT16:
		{
			tolua_pushnumber( l, (lua_Number) (*(_word*) (object + decl_info.mOffset)) );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_UINT32:
		{
			tolua_pushnumber( l, (lua_Number) (*(_dword*) (object + decl_info.mOffset)) );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_FLOAT:
		{
			tolua_pushnumber( l, (lua_Number) (*(_float*) (object + decl_info.mOffset)) );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_DOUBLE:
		{
			tolua_pushnumber( l, (lua_Number) (*(_double*) (object + decl_info.mOffset)) );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_CLASS:
		{
			if ( decl_info.mTypeName.IsEqual( "AString" ) )
			{
				AString* string = (AString*)(object + decl_info.mOffset);
				tolua_pushstring( l, string->Str( ) );
			}
			else if ( decl_info.mTypeName.IsEqual( "UString" ) )
			{
				UString* string = (UString*)(object + decl_info.mOffset);
				tolua_pushstring( l, string->Str( ) );
			}
			else if ( decl_info.mTypeName.IsEqual( "WString" ) )
			{
				WString* string = (WString*)(object + decl_info.mOffset);
				tolua_pushstring( l, UString( ).FromString( *string ).Str( ) );
			}
			else
			{
				tolua_pushusertype( l, object + decl_info.mOffset, decl_info.mPropertyName.Str( ) );
			}
		}
		break;

		case ScriptVarDeclInfo::_TYPE_OBJECT:
		{
			tolua_pushusertype( l, object + decl_info.mOffset, decl_info.mPropertyName.Str( ) );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_BUFFER:
		{
			tolua_pushusertype( l, object + decl_info.mOffset, decl_info.mPropertyName.Str( ) );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_ASTRING_PTR:
		{
			tolua_pushstring( l, (const _chara*)(object + decl_info.mOffset) );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_USTRING_PTR:
		{
			tolua_pushstring( l, (const _chara*)(object + decl_info.mOffset) );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_WSTRING_PTR:
		{
			AString string_ansi; string_ansi.FromString( _ENCODING_UTF16, (const _charw*) object + decl_info.mOffset );
			tolua_pushstring( l, string_ansi.Str( ) );
		}
		break;

		default:
			break;
	}

	return 1;
}

int _luaModule::Setter( lua_State* l )
{
	_byte* object = (_byte*) tolua_tousertype( l, 1, 0 );
	EGE_ASSERT( object != _null );

	PropertyInfo* property_info = (PropertyInfo*) lua_touserdata( l, lua_upvalueindex( 1 ) );
	EGE_ASSERT( property_info != _null );

	const ScriptPropertyDeclInfo& decl_info = property_info->mDeclInfo;

	switch ( decl_info.mTypeID )
	{
		case ScriptVarDeclInfo::_TYPE_INT8:
		{
			*(_tiny*) (object + decl_info.mOffset) = (_tiny) tolua_tonumber( l, 2, 0 );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_INT16:
		{
			*(_short*) (object + decl_info.mOffset) = (_short) tolua_tonumber( l, 2, 0 );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_INT32:
		{
			*(_int*) (object + decl_info.mOffset) = (_int) tolua_tonumber( l, 2, 0 );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_UINT8:
		{
			*(_byte*) (object + decl_info.mOffset) = (_byte) tolua_tonumber( l, 2, 0 );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_UINT16:
		{
			*(_word*) (object + decl_info.mOffset) = (_word) tolua_tonumber( l, 2, 0 );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_UINT32:
		{
			*(_dword*) (object + decl_info.mOffset) = (_dword) tolua_tonumber( l, 2, 0 );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_FLOAT:
		{
			*(_float*) (object + decl_info.mOffset) = (_float) tolua_tonumber( l, 2, 0 );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_DOUBLE:
		{
			*(_double*) (object + decl_info.mOffset) = (_double) tolua_tonumber( l, 2, 0 );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_CLASS:
		{
			if ( decl_info.mTypeName.IsEqual( "AString" ) )
			{
				AString* string = (AString*)(object + decl_info.mOffset);
				*string = tolua_tostring( l, 2, _null );
			}
			else if ( decl_info.mTypeName.IsEqual( "UString" ) )
			{
				UString* string = (UString*)(object + decl_info.mOffset);
				*string = tolua_tostring( l, 2, _null );
			}
			else if ( decl_info.mTypeName.IsEqual( "WString" ) )
			{
				WString* string = (WString*)(object + decl_info.mOffset);
				string->FromString( _ENCODING_UTF8, tolua_tostring( l, 2, _null ) );
			}
		}
		break;

		case ScriptVarDeclInfo::_TYPE_OBJECT:
		{
		}
		break;

		case ScriptVarDeclInfo::_TYPE_BUFFER:
		{
		}
		break;

		case ScriptVarDeclInfo::_TYPE_ASTRING_PTR:
		{
		}
		break;

		case ScriptVarDeclInfo::_TYPE_USTRING_PTR:
		{
		}
		break;

		case ScriptVarDeclInfo::_TYPE_WSTRING_PTR:
		{
		}
		break;

		default:
			break;
	}

	return 0;
}

_int _luaModule::Call( lua_State* l )
{
	// Get the 'this' object
	_byte* object = (_byte*) tolua_tousertype( l, 1, 0 );

	// Get the function info
	FuncInfo* func_info = (FuncInfo*) lua_touserdata( l, lua_upvalueindex( 1 ) );
	EGE_ASSERT( func_info != _null );

	// Get the lua module
	_luaModule* lua_module = func_info->mModule;
	EGE_ASSERT( lua_module != _null );

	// Call method
	lua_module->InvokeFunc( l, func_info, object );

	return 1;
}

_ubool _luaModule::PushRetValue( lua_State* l, const ScriptVarDeclInfo& var_decl_info, const ScriptVMRegisters& registers )
{
	switch ( var_decl_info.mTypeID )
	{
		case ScriptVarDeclInfo::_TYPE_VOID:
		{
		}
		break;

		case ScriptVarDeclInfo::_TYPE_ASTRING_PTR:
		{
			UString string_utf8;
			string_utf8.FromString( _ENCODING_ANSI, (const _chara*) registers.mValueRegister );

			tolua_pushstring( l, string_utf8.Str( ) );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_USTRING_PTR:
		{
			tolua_pushstring( l, (const _chara*) registers.mValueRegister );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_WSTRING_PTR:
		{
			UString string_utf8;
			string_utf8.FromString( _ENCODING_UTF16, (const _charw*) registers.mValueRegister );

			tolua_pushstring( l, string_utf8.Str( ) );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_INT8:
		case ScriptVarDeclInfo::_TYPE_INT16:
		case ScriptVarDeclInfo::_TYPE_INT32:
		{
			tolua_pushnumber( l, (_double)(_int) registers.mValueRegister );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_UINT8:
		case ScriptVarDeclInfo::_TYPE_UINT16:
		case ScriptVarDeclInfo::_TYPE_UINT32:
		{
			tolua_pushnumber( l, (_double)(_dword) registers.mValueRegister );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_FLOAT:
		{
			_float value = *(_float*)&registers.mValueRegister;

			tolua_pushnumber( l, (_double) value );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_DOUBLE:
		{
			_double value = *(_double*)&registers.mValueRegister;

			tolua_pushnumber( l, value );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_CLASS:
		case ScriptVarDeclInfo::_TYPE_OBJECT:
		{
			// We must have object resource
			_byte* object = registers.mObjectRegister;
			EGE_ASSERT( object != _null );

			// Use as clone object
			tolua_pushusertype( l, object, var_decl_info.mTypeName.Str( ) );
			tolua_clone( gLuaState, object, Destructor );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_BUFFER:
		{
			EGE_ASSERT( 0 );
		}
		break;

		default:
			break;
	}

	return _true;
}

_ubool _luaModule::InvokeFunc( lua_State* l, const FuncInfo* func_info, _void* obj )
{
	const ScriptFuncDeclInfo&		decl_info			= func_info->mDeclInfo;
	const ScriptNativeFuncInfo&		native_func_info	= func_info->mNativeFuncInfo;
	const ScriptVarDeclInfoArray&	native_args_decl	= func_info->mDeclInfo.mParametersDecls;

	// Get parameter number
	_int args_number = lua_gettop( l );
	if ( args_number < 0 )
		return _false;

	// Get the actual arguments number
	if ( obj != _null )
	{
		EGE_ASSERT( args_number >= 1 );
		args_number --;
	}

	// Check the arguments number
	if ( args_number != native_args_decl.Number( ) )
		return _false;

	// Prepare arguments ( The arguments buffer must align to 32 bits number )
	_byte args_buffer[1024]; EGE_STATIC_ASSERT( sizeof( args_buffer ) % sizeof( _dword ) == 0, "The arugments buffer must align to 32 bits" );
	if ( _luaHelper::ParseArgs( l, args_number, native_args_decl, args_buffer ) == _false )
	{
		tolua_error( l, FORMAT_ASTRING_1( "Parse '%s' arguments failed", decl_info.mName.Str( ) ), _null );
		return _false;
	}

	// The temporary host return buffer data
	_byte temporary_host_return_buffer[ 1 KB ];

	// Build script registers
	ScriptVMRegisters registers;
	registers.mStackPointer	= (_dword*) args_buffer;
	if ( decl_info.mRetDecl.HasObj( ) && native_func_info.mHostReturnSize > 0 )
		registers.mObjectRegister = temporary_host_return_buffer;

	// The native function will return object class
	if ( decl_info.mRetDecl.HasObj( ) )
	{
		EGE_ASSERT( native_func_info.mHostReturnSize != 0 );

		// Create class resource for return value if we return the whole class object
		if ( decl_info.mRetDecl.mTypeID == ScriptVarDeclInfo::_TYPE_CLASS )
		{
			if ( GetScriptResourceManager( )->InvokeConstructorBehaviourFunc( registers.mObjectRegister, decl_info.mRetDecl.mTypeName.Str( ) ) == _false )
			{
				tolua_error( l, FORMAT_ASTRING_1( "Invoke '%s' constructor failed", decl_info.mRetDecl.mTypeName.Str( ) ), _null );
				return _false;
			}
		}

		// Invoke method
		_scriptCallFunc::CallFunction( registers, &decl_info, native_func_info, obj );
	}
	else
	{
		if ( obj != _null )
			_scriptCallFunc::CallFunction( registers, &decl_info, native_func_info, obj );
		else
			_scriptCallFunc::CallFunction( registers, &decl_info, native_func_info );
	}

	// Free arguments
	_byte* args_ptr = args_buffer;
	for ( _dword i = 0; i < func_info->mDeclInfo.mParametersDecls.Number( ); i ++ )
	{
		const ScriptVarDeclInfo& var_info = func_info->mDeclInfo.mParametersDecls[i];

		switch ( var_info.mTypeID )
		{
			case ScriptVarDeclInfo::_TYPE_OBJECT:
			{
				args_ptr += sizeof( size_t* );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_INT32:
			case ScriptVarDeclInfo::_TYPE_UINT32:
			case ScriptVarDeclInfo::_TYPE_UBOOL:
			case ScriptVarDeclInfo::_TYPE_FLOAT:
			{
				args_ptr += 4;
			}
			break;
				
			case ScriptVarDeclInfo::_TYPE_DOUBLE:
			{
				args_ptr += 8;
			}
			break;
				
			case ScriptVarDeclInfo::_TYPE_CLASS:
			{
				_byte* object = (_byte*) *(_qword*)args_ptr;
				EGE_ASSERT( object != _null );

				if ( GetScriptResourceManager( )->InvokeDestructorBehaviourFunc( object, var_info.mTypeName.Str( ) ) == _false )
				{
					tolua_error( l, FORMAT_ASTRING_1( "Invoke '%s' destructor failed", var_info.mTypeName.Str( ) ), _null );
					return _false;
				}
				
				args_ptr += sizeof( _byte* );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_ASTRING_PTR:	
			{
				AStringPtr* string = (AStringPtr*) *(_qword*)args_ptr;
				delete[] (_byte*) string->Str( );
				delete string;

				args_ptr += sizeof( AStringPtr* );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_USTRING_PTR:	
			{
				UStringPtr* string = (UStringPtr*) *(_qword*)args_ptr;
				delete[] (_byte*) string->Str( );
				delete string;

				args_ptr += sizeof( UStringPtr* );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_WSTRING_PTR:	
			{
				WStringPtr* string = (WStringPtr*) *(_qword*)args_ptr;
				delete[] (_byte*) string->Str( );
				delete string;

				args_ptr += sizeof( WStringPtr* );
			}
			break;

			default:
				EGE_ASSERT( 0 );
				break;
		}
	}

	// Push return object
	return PushRetValue( l, decl_info.mRetDecl, registers );
}

_ubool _luaModule::Initialize( AStringPtr name, AStringPtr desc )
{
	if ( name.IsEmpty( ) )
		return _false;

	// Copy the basic info
	mName = name;
	mDesc = desc;

	// Register user type
	tolua_module( gLuaState, _null, 0 );
	tolua_usertype( gLuaState, name.Str( ) );

	// Register basic functions
	tolua_beginmodule( gLuaState, _null );
		tolua_cclass( gLuaState, name.Str( ), name.Str( ), "", _null );
		tolua_beginmodule( gLuaState, name.Str( ) );
			tolua_userfunction( gLuaState, "new", GlobalNew, (_void*) this );
			tolua_userfunction( gLuaState, "new_local", LocalNew, (_void*) this );
		tolua_endmodule( gLuaState );
	tolua_endmodule( gLuaState );

	return _true;
}

AStringPtr _luaModule::GetName( ) const
{
	return mName.Str( );
}

const AStringObj& _luaModule::GetNameObj( ) const
{
	return mName;
}

_ubool _luaModule::RegisterEnumValue( AStringPtr name, _dword value )
{
	// Register constant value as enumeration
	tolua_beginmodule( gLuaState, _null );
		tolua_beginmodule( gLuaState, mName.Str( ) );
			tolua_constant( gLuaState, name.Str( ), value );
		tolua_endmodule( gLuaState );
	tolua_endmodule( gLuaState );

	return _true;
}

_ubool _luaModule::RegisterProperty( const ScriptPropertyDeclInfo& decl_info )
{
	// Create property info
	PropertyInfo* property_info	= new PropertyInfo( );
	property_info->mDeclInfo	= decl_info;
	mProperties.Append( property_info );

	// Register function
	tolua_beginmodule( gLuaState, _null );
		tolua_beginmodule( gLuaState, mName.Str( ) );
			tolua_uservariable( gLuaState, decl_info.mPropertyName.Str( ), Getter, Setter, (_void*) property_info );
		tolua_endmodule( gLuaState );
	tolua_endmodule( gLuaState );

	return _true;
}

_ubool _luaModule::RegisterFunction( const ScriptFuncDeclInfo& decl_info, const ScriptNativeFuncInfo& native_func_info )
{
	// Create function info
	FuncInfo* func_info			= new FuncInfo( );
	func_info->mDeclInfo		= decl_info;
	func_info->mNativeFuncInfo	= native_func_info;
	func_info->mModule			= this;
	mFunctions.Append( func_info );

	// Register function
	tolua_beginmodule( gLuaState, _null );
		tolua_beginmodule( gLuaState, mName.Str( ) );
			tolua_userfunction( gLuaState, decl_info.mName.Str( ), Call, (_void*) func_info );
		tolua_endmodule( gLuaState );
	tolua_endmodule( gLuaState );

	return _true;
}

#endif