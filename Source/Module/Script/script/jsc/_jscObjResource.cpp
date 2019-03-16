//! @file     _jscObjResource.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_JS_ == 1)

//----------------------------------------------------------------------------
// _jscObjResource Implementation
//----------------------------------------------------------------------------

_jscObjResource::_jscObjResource( const AStringObj& name )
{
	mName		= name;
	mJSObject	= _null;
	mWrapClass	= _null;
}

_jscObjResource::~_jscObjResource( )
{
	FreeInstance( _true );
}

JSValueRef _jscObjResource::BuildRetValue( JSContextRef js_context, const ScriptVarDeclInfo& var_decl_info, const ScriptVMRegisters& registers )
{
	JSValueRef js_value;

	switch ( var_decl_info.mTypeID )
	{
		case ScriptVarDeclInfo::_TYPE_VOID:
		{
			js_value = JS_MAKE_NULL( js_context );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_ASTRING_PTR:
		{
			UString string_utf8;
			string_utf8.FromString( _ENCODING_ANSI, (const _chara*) registers.mValueRegister );

			js_value = _jscHelper::MakeJSValueAsString( js_context, JSStringRefOwner( string_utf8 ) );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_USTRING_PTR:
		{
			js_value = _jscHelper::MakeJSValueAsString( js_context, JSStringRefOwner( (UStringPtr) (const _chara*) registers.mValueRegister ) );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_WSTRING_PTR:
		{
			UString string_utf8;
			string_utf8.FromString( _ENCODING_UTF16, (const _charw*) registers.mValueRegister );

			js_value = _jscHelper::MakeJSValueAsString( js_context, JSStringRefOwner( string_utf8 ) );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_INT8:
		case ScriptVarDeclInfo::_TYPE_INT16:
		case ScriptVarDeclInfo::_TYPE_INT32:
		{
			js_value = _jscHelper::MakeJSValueAsLong( js_context, (_int) registers.mValueRegister );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_UINT8:
		case ScriptVarDeclInfo::_TYPE_UINT16:
		case ScriptVarDeclInfo::_TYPE_UINT32:
		{
			js_value = _jscHelper::MakeJSValueAsDword( js_context, (_dword) registers.mValueRegister );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_FLOAT:
		{
			_float value = *(_float*)&registers.mValueRegister;

			js_value = _jscHelper::MakeJSValueAsFloat( js_context, value );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_DOUBLE:
		{
			_double value = *(_double*)&registers.mValueRegister;

			js_value = _jscHelper::MakeJSValueAsDouble( js_context, value );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_CLASS:
		case ScriptVarDeclInfo::_TYPE_OBJECT:
		{
			// We must have object resource
			EGE_ASSERT( registers.mObjectRegister != _null );

			// Get the JSC module info
			_jscGlobal::JSCModlueInfo* jsc_module_info = _jscGlobal::GetInstance( ).GetJSCModule( var_decl_info.mTypeName );
			EGE_ASSERT( jsc_module_info != _null );

			// Create JS object
			JSObjectRef js_object = jsc_module_info->mJSCModule->CreateJSObject( js_context, (_byte*) registers.mObjectRegister, _true );
			EGE_ASSERT( js_object != _null );

			// Feedback the JS object as value
			js_value = JS_OBJECT_TO_VALUE( js_object );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_BUFFER:
		{
			_byte* buffer	= (_byte*) ((_dword) registers.mValueRegister);
			_dword size		= ((_dword) (registers.mValueRegister >> 32 ));
			EGE_ASSERT( buffer != _null && size != 0 );

			js_value = _jscHelper::MakeJSValueAsString( js_context, JSStringRefOwner( buffer, size ) );
		}
		break;

		default:
			break;
	}

	return js_value;
}

_jscObjResource* _jscObjResource::CreateInstance( const AStringObj& name )
{
	return new _jscObjResource( name );
}

_ubool _jscObjResource::InitInstance( JSObjectRef js_object, _ubool call_constructor )
{
	mJSObject = js_object;

	// Add JS resource object
	_jscGlobal::GetInstance( ).AddJSObjRes( js_object, this );

	// Invoke the constructor
	if ( call_constructor && GetScriptResourceManager( )->InvokeConstructorBehaviourFunc( mWrapClass, mName.Str( ) ) == _false )
		return _false;

	ALOG_DEBUG_2( "Create JS (0x%x: %s) object", (_dword) mJSObject, mName.Str( ) );

	return _true;
}

_void _jscObjResource::FreeInstance( _ubool all )
{
	// Check whether the binding resource has been released or not
	if ( mWrapClass == _null && mWrapObject.IsNull( ) )
		return;

	// It's class not inherit from IObject
	if ( mWrapClass != _null )
	{
		// Call destructor to release it
		GetScriptResourceManager( )->InvokeDestructorBehaviourFunc( mWrapClass, mName.Str( ) );
	}
	// It's object inherit from IObject
	else if ( mWrapObject.IsValid( ) )
	{
		// Call Release( ) to decrease referenced counter
		mWrapObject.Clear( );
	}

	ALOG_DEBUG_2( "Delete JS (0x%x: %s) object", (_dword) mJSObject, mName.Str( ) );
}

JSValueRef _jscObjResource::InvokeMethod( IStackAllocator* allocator, JSContextRef js_context, JSObjectRef js_func, JSObjectRef js_object, _dword args_number, const JSValueRef js_args[], JSValueRef* js_exception )
{
	// Get the registered function info
	const _jscGlobal::RegisteredFuncInfo* func_info = _jscGlobal::GetInstance( ).GetRegisteredJSFunction( js_object, js_func );
	EGE_ASSERT( func_info != _null );

	if ( func_info == _null )
	{
		WLOG_ERROR( L"func_info == null");
		return JS_MAKE_NULL( js_context );
	}

	const ScriptFuncDeclInfo&		decl_info			= func_info->mDeclInfo;
	const ScriptNativeFuncInfo&		native_func_info	= func_info->mNativeFuncInfo;
	const ScriptVarDeclInfoArray&	native_args_decl	= func_info->mDeclInfo.mParametersDecls;

	// Prepare arguments ( The arguments buffer must align to 32 bits number )
	_byte args_buffer[1024]; EGE_STATIC_ASSERT( sizeof( args_buffer ) % sizeof( _dword ) == 0 );
	if ( _jscHelper::ParseArgs( js_context, args_number, js_args, native_args_decl, args_buffer, js_exception, allocator ) == _false )
		return JS_MAKE_NULL( js_context );

	// Build script registers
	ScriptVMRegisters registers;
	registers.mStackPointer	= (_dword*) args_buffer;
	if ( decl_info.mRetDecl.HasObj( ) && native_func_info.mHostReturnSize > 0 )
		registers.mObjectRegister = allocator->Alloc( native_func_info.mHostReturnSize );

	// The native function will return object class
	if ( decl_info.mRetDecl.HasObj( ) )
	{
		EGE_ASSERT( native_func_info.mHostReturnSize != 0 );

		// Create class resource for return value if we return the whole class object
		if ( decl_info.mRetDecl.mTypeID == ScriptVarDeclInfo::_TYPE_CLASS )
		{
			if ( GetScriptResourceManager( )->InvokeConstructorBehaviourFunc( registers.mObjectRegister, decl_info.mRetDecl.mTypeName.Str( ) ) == _false )
				return JS_MAKE_NULL( js_context );
		}

		// Invoke method
		_scriptCallFunc::CallFunction( registers, &decl_info, native_func_info, mWrapClass );
	}
	else
	{
		if ( mWrapClass != _null )
			_scriptCallFunc::CallFunction( registers, &decl_info, native_func_info, mWrapClass );
		else
			_scriptCallFunc::CallFunction( registers, &decl_info, native_func_info );
	}

	// Free arguments
	for ( _dword i = 0; i < func_info->mDeclInfo.mParametersDecls.Number( ); i ++ )
	{
		const ScriptVarDeclInfo& var_info = func_info->mDeclInfo.mParametersDecls[i];

		// Get the variable pointer in 32-bits range
		_dword* arg_ptr = (_dword*)((_dword*)args_buffer)[i];

		switch ( var_info.mTypeID )
		{
			case ScriptVarDeclInfo::_TYPE_CLASS:
			{
				_byte* object = (_byte*) arg_ptr;
				EGE_ASSERT( object != _null );

				if ( GetScriptResourceManager( )->InvokeDestructorBehaviourFunc( object, var_info.mTypeName.Str( ) ) == _false )
				{
					tolua_error( l, FORMAT_ASTRING_1( "Invoke '%s' destructor failed", var_info.mTypeName.Str( ) ), _null );
					return _false;
				}
			}
			break;

			case ScriptVarDeclInfo::_TYPE_ASTRING_PTR:	
			{
				EGE_ASSERT( arg_ptr != _null );

				AStringPtr* string = (AStringPtr*) arg_ptr;
				delete[] (_byte*) string->Str( );
				delete string;
			}
			break;

			case ScriptVarDeclInfo::_TYPE_USTRING_PTR:	
			{
				EGE_ASSERT( arg_ptr != _null );

				UStringPtr* string = (UStringPtr*) arg_ptr;
				delete[] (_byte*) string->Str( );
				delete string;
			}
			break;

			case ScriptVarDeclInfo::_TYPE_WSTRING_PTR:	
			{
				EGE_ASSERT( arg_ptr != _null );

				WStringPtr* string = (WStringPtr*) arg_ptr;
				delete[] (_byte*) string->Str( );
				delete string;
			}
			break;

			case ScriptVarDeclInfo::_TYPE_CLASS:
			{
				_byte* object = (_byte*)(intptr_t) args_buffer[ i * sizeof( _dword ) ];
				if ( GetScriptResourceManager( )->InvokeDestructorBehaviourFunc( object, var_info.mTypeName.Str( ) ) == _false )
					return JS_MAKE_NULL( js_context );
			}
			break;

			default:
				break;
		}
	}

	// Build the return object
	return BuildRetValue( js_context, decl_info.mRetDecl, registers );
}

#endif