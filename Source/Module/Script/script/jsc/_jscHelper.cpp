//! @file     _jscHelper.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_JS_ == 1)

JSContextRef	EGE::gGlobalJSContext	= _null;
JSObjectRef		EGE::gGlobalJSObject	= _null;

//----------------------------------------------------------------------------
// JSStringRefOwner Implementation
//----------------------------------------------------------------------------

JSStringRefOwner::JSStringRefOwner( )
{
	JS_INIT( mJSString );
}

JSStringRefOwner::JSStringRefOwner( const JSStringRefOwner& object )
{
	mJSString = JS_STRING_RETAIN( object.mJSString );
}

JSStringRefOwner::JSStringRefOwner( JSStringRef object )
{
	mJSString = JS_STRING_RETAIN( object );
}

JSStringRefOwner::JSStringRefOwner( AStringPtr string )
{
	mJSString = _jscHelper::CreateJSStringA( string );
}

JSStringRefOwner::JSStringRefOwner( const AStringObj& string )
{
	mJSString = _jscHelper::CreateJSStringA( string.Str( ) );
}

JSStringRefOwner::JSStringRefOwner( UStringPtr string )
{
	mJSString = _jscHelper::CreateJSStringU( string );
}

JSStringRefOwner::JSStringRefOwner( const UStringObj& string )
{
	mJSString = _jscHelper::CreateJSStringU( string.Str( ) );
}

JSStringRefOwner::JSStringRefOwner( WStringPtr string )
{
	mJSString = _jscHelper::CreateJSStringW( string );
}

JSStringRefOwner::JSStringRefOwner( const WStringObj& string )
{
	mJSString = _jscHelper::CreateJSStringW( string.Str( ) );
}

JSStringRefOwner::JSStringRefOwner( const _byte* buffer, _dword size )
{
	CopyFrom( buffer, size );
}

JSStringRefOwner::~JSStringRefOwner( )
{
	if ( JS_IS_VALID( mJSString ) )
		JS_STRING_RELEASE( mJSString );
}

JSStringRefOwner& JSStringRefOwner::operator = ( const JSStringRefOwner& object )
{
	if ( JS_IS_VALID( mJSString ) )
		JS_STRING_RELEASE( mJSString );

	if ( JS_IS_VALID( object.mJSString ) )
		mJSString = JS_STRING_RETAIN( object.mJSString );

	return *this;
}

JSStringRefOwner& JSStringRefOwner::operator = ( const AStringObj& string_obj )
{
	if ( JS_IS_VALID( mJSString ) )
		JS_STRING_RELEASE( mJSString );

	mJSString = _jscHelper::CreateJSStringA( string_obj.Str( ) );

	return *this;
}

JSStringRefOwner& JSStringRefOwner::operator = ( JSStringRef object )
{
	if ( JS_IS_VALID( mJSString ) )
		JS_STRING_RELEASE( mJSString );

	if ( JS_IS_VALID( object ) )
		mJSString = JS_STRING_RETAIN( object );

	return *this;
}

_ubool JSStringRefOwner::IsValid( ) const
{
	return mJSString != _null;
}

_ubool JSStringRefOwner::IsNull( ) const
{
	return mJSString == _null;
}

_void JSStringRefOwner::CopyFrom( const _byte* buffer, _dword size )
{
	AString string( (const _chara*) buffer, size );
	mJSString = _jscHelper::CreateJSStringA( string );
}

AString JSStringRefOwner::ToStringA( ) const
{
	return AString( ).FromString( ToStringW( ) );
}

UString JSStringRefOwner::ToStringU( ) const
{
	return UString( ).FromString( ToStringW( ) );
}

WString JSStringRefOwner::ToStringW( ) const
{
	return _jscHelper::GetJSStringW( mJSString );
}

//----------------------------------------------------------------------------
// _jscHelper Helpful Functions Implementation
//----------------------------------------------------------------------------

//!	Build the JS function key name
static JSStringRef BuildJSFuncKeyName( JSObjectRef js_func )
{
	_chara string[256];
	Platform::ConvertDwordToString( (_dword) js_func, 16, string, 256 );

	AString func_key_name( "JSFunc:" );
	func_key_name += string;

	return _jscHelper::CreateJSStringA( func_key_name );
}

//----------------------------------------------------------------------------
// _jscHelper Implementation
//----------------------------------------------------------------------------

_ubool _jscHelper::Initialize( )
{
	return _true;
}

_void _jscHelper::Finalize( )
{
}

_void _jscHelper::PushNumberArgLong( _byte*& args_buffer, JSContextRef js_context, const JSValueRef js_value, JSValueRef* js_exception )
{
	_int value = _jscHelper::JSValue2Long( js_context, js_value, js_exception );

	*(_int*) args_buffer = value;
	args_buffer += sizeof( _int );
}

_void _jscHelper::PushNumberArgDword( _byte*& args_buffer, JSContextRef js_context, const JSValueRef js_value, JSValueRef* js_exception )
{
	_dword value = _jscHelper::JSValue2Dword( js_context, js_value, js_exception );

	*(_dword*) args_buffer = value;
	args_buffer += sizeof( _dword );
}

_void _jscHelper::PushNumberArgFloat( _byte*& args_buffer, JSContextRef js_context, const JSValueRef js_value, JSValueRef* js_exception )
{
	_float value = (_float) _jscHelper::JSValue2Number( js_context, js_value, js_exception );

	*(_float*) args_buffer = value;
	args_buffer += sizeof( _float );
}

_void _jscHelper::PushNumberArgDouble( _byte*& args_buffer, JSContextRef js_context, const JSValueRef js_value, JSValueRef* js_exception )
{
	_double value = _jscHelper::JSValue2Number( js_context, js_value, js_exception );

	*(_double*) args_buffer = value;
	args_buffer += sizeof( _double );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_void _jscHelper::PushStringPtrArg( _byte*& args_buffer, ConstString< CharType, _STRING_ENCODE > c_string, IAllocator* allocator )
{
	// Allocate C string buffer
	const CharType* string_buf = (const CharType*) allocator->Alloc( c_string.SizeOfBytes( ), (const _byte*) c_string.Str( ) );
	EGE_ASSERT( string_buf != _null );

	// Save into string object
	ConstString< CharType, _STRING_ENCODE >* string_obj = (ConstString< CharType, _STRING_ENCODE >*) allocator->Alloc( sizeof( ConstString< CharType, _STRING_ENCODE > ) );
	*string_obj = string_buf;

	// Push into argument buffer
	*(size_t*)args_buffer = (size_t)string_obj;
	args_buffer += sizeof( ConstString< CharType, _STRING_ENCODE > );
}

template< typename ObjectType >
_void _jscHelper::PushClassArg( _byte*& args_buffer, const ObjectType* object )
{
	*(_dword*) args_buffer = (_dword) object;
	args_buffer += sizeof( _dword );
}

_ubool _jscHelper::SetJSCModule( JSObjectRef js_object, _jscModule* jsc_module )
{
	return _jscHelper::SetJSObjectPrivate( js_object, jsc_module );
}

_jscModule* _jscHelper::GetJSCModule( JSObjectRef js_object )
{
	return (_jscModule*) _jscHelper::GetJSObjectPrivate( js_object );
}

_ubool _jscHelper::SetJSObjectProperty( JSContextRef js_context, JSObjectRef js_object, AStringPtr js_name, JSValueRef js_value, JSPropertyAttributes attributes )
{
	return _jscHelper::SetJSObjectProperty( js_context, js_object, JSStringRefOwner( js_name ), js_value, attributes );
}

JSValueRef _jscHelper::GetJSObjectProperty( JSContextRef js_context, JSObjectRef js_object, AStringPtr name )
{
	return _jscHelper::GetJSObjectProperty( js_context, js_object, JSStringRefOwner( name ) );
}

AString _jscHelper::GetJSStringA( JSStringRef js_string )
{
	return AString( ).FromString( GetJSStringW( js_string ) );
}

AString _jscHelper::GetJSStringA( JSContextRef js_context, JSValueRef js_value )
{
	return AString( ).FromString( GetJSStringW( js_context, js_value ) );
}

UString _jscHelper::GetJSStringU( JSStringRef js_string )
{
	return UString( ).FromString( GetJSStringW( js_string ) );
}

UString _jscHelper::GetJSStringU( JSContextRef js_context, JSValueRef js_value )
{
	return UString( ).FromString( GetJSStringW( js_context, js_value ) );
}

WString _jscHelper::GetJSStringW( JSContextRef js_context, JSValueRef js_value )
{
	JSStringRefOwner js_string( _jscHelper::CreateJSString( js_context, js_value, _null ) );
	if ( js_string.IsNull( ) )
		return WString( L"" );

	return GetJSStringW( js_string );
}

_ubool _jscHelper::RegisterJSProperty( JSContextRef js_context, JSObjectRef js_object, const ScriptPropertyDeclInfo& decl_info )
{
	// Build the JS value
	JSValueRef js_value;
	if ( decl_info.mTypeID == ScriptVarDeclInfo::_TYPE_OBJECT )
	{
		// It's JS object, now get the JSC module by type name
		_jscModule* jsc_module = _jscHelper::GetJSCModule( js_object );
		if ( jsc_module == _null )
			return _false;

		// Create JS object
		js_value = JS_OBJECT_TO_VALUE( jsc_module->CreateJSObject( js_context, _null, _false ) );
	}
	else
	{
		js_value = _jscHelper::BuildJSVAlue( js_context, decl_info.mTypeID );
	}

	// Get the JS property name
	JSStringRefOwner js_property_name( decl_info.mPropertyName );

	// Register JS property
	if ( _jscHelper::SetJSObjectProperty( js_context, js_object, js_property_name, js_value, 0 ) == _false )
		return _false;

	return _true;
}

JSObjectRef _jscHelper::CreateJSFunction( JSContextRef js_context, AStringPtr name, JSObjectCallAsFunctionCallback js_callback_func )
{
	// Convert to the JS string of function name
	JSStringRefOwner js_func_name( name );

	// Create JS embedded function by name
	JSObjectRef js_func = _jscHelper::CreateJSFunction( js_context, js_func_name, js_callback_func );
	if ( JS_IS_NULL( js_func ) )
		return JS_NULL;

	return js_func;
}

JSObjectRef _jscHelper::GetJSFunction( JSContextRef js_context, AStringPtr func_name )
{
	JSValueRef js_value = _jscHelper::GetJSObjectProperty( js_context, gGlobalJSObject, JSStringRefOwner( func_name ) );

	// Get the JS function
	JSObjectRef js_func = JS_VALUE_TO_OBJECT( js_value );
	if ( JS_IS_FUNC( js_context, js_func ) == _false )
	{
		ALOG_ERROR_1( "The '%s' JS function is not existing", func_name.Str( ) );
		return _null;
	}

	return js_func;
}

_ubool _jscHelper::ParseArgs( JSContextRef js_context, _dword args_number, const JSValueRef js_args[], const ScriptVarDeclInfoArray& vars, _byte* args_buffer, JSValueRef* js_exception, IAllocator* allocator )
{
	EGE_ASSERT( allocator != _null );

	for ( _dword i = 0; i < args_number; i ++ )
	{
		const JSValueRef			js_value	= js_args[i];
		const ScriptVarDeclInfo&	var_info	= vars[i];

		switch ( var_info.mTypeID )
		{
			case ScriptVarDeclInfo::_TYPE_INT32:
			{
				PushNumberArgLong( args_buffer, js_context, js_value, js_exception );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_UINT32:
			{
				PushNumberArgDword( args_buffer, js_context, js_value, js_exception );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_FLOAT:
			{
				PushNumberArgFloat( args_buffer, js_context, js_value, js_exception );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_DOUBLE:
			{
				PushNumberArgDouble( args_buffer, js_context, js_value, js_exception );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_CLASS:	
			{
				// Create the class object
				_byte* object = _null;
				if ( GetScriptResourceManager( )->InvokeConstructorBehaviourFunc( object, var_info.mTypeName.Str( ) ) == _false )
					return _false;

				// Copy the class object
				if ( GetScriptResourceManager( )->InvokeCopyBehaviourFunc( object, _null , var_info.mTypeName.Str( ) ) == _false )
					return _false;

				PushClassArg( args_buffer, object );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_ASTRING_PTR:	
			{
				// Convert JS string to C string
				JSStringRefOwner js_string( _jscHelper::CreateJSString( js_context, js_value, js_exception ) );
				AString c_string = js_string.ToStringA( );

				PushStringPtrArg< _chara, _ENCODING_ANSI >( args_buffer, c_string, allocator );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_USTRING_PTR:	
			{
				// Convert JS string to C string
				JSStringRefOwner js_string( _jscHelper::CreateJSString( js_context, js_value, js_exception ) );
				UString c_string = js_string.ToStringU( );

				PushStringPtrArg< _chara, _ENCODING_UTF8 >( args_buffer, c_string, allocator );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_WSTRING_PTR:	
			{
				// Convert JS string to C string
				JSStringRefOwner js_string( _jscHelper::CreateJSString( js_context, js_value, js_exception ) );
				WString c_string = js_string.ToStringW( );

				PushStringPtrArg< _charw, _ENCODING_UTF16 >( args_buffer, c_string, allocator );
			}
			break;

			default:
				EGE_ASSERT( 0 );
				break;
		}
	}

	return _true;
}

JSValueRef _jscHelper::BuildJSVAlue( JSContextRef js_context, const Variable& arg )
{
	switch ( arg.GetType( ) )
	{
		case Variable::_TYPE_ID_INT8:	
		case Variable::_TYPE_ID_INT16:	
		case Variable::_TYPE_ID_INT32:	
		{
			return _jscHelper::MakeJSValueAsLong( js_context, arg );
		}
		break;

		case Variable::_TYPE_ID_UINT8:	
		case Variable::_TYPE_ID_UINT16:	
		case Variable::_TYPE_ID_UINT32:	
		{
			return _jscHelper::MakeJSValueAsDword( js_context, arg );
		}
		break;

		case Variable::_TYPE_ID_FLOAT:	
		{
			return _jscHelper::MakeJSValueAsFloat( js_context, arg );
		}
		break;

		case Variable::_TYPE_ID_DOUBLE:	
		{
			return _jscHelper::MakeJSValueAsDouble( js_context, arg );
		}
		break;

		case Variable::_TYPE_ID_WSTRING:	
		{
			UString string_utf8;
			string_utf8.FromString( arg.Str( ) );

			return _jscHelper::MakeJSValueAsString( js_context, JSStringRefOwner( string_utf8 ) );
		}
		break;

		case Variable::_TYPE_ID_POINTER:	
		{
		}
		break;

		default:
			break;
	}

	return JS_MAKE_NULL( js_context );
}

JSValueRef _jscHelper::BuildJSVAlue( JSContextRef js_context, ScriptVarDeclInfo::_TYPE type )
{
	switch ( type )
	{
		case ScriptVarDeclInfo::_TYPE_INT8:	
		case ScriptVarDeclInfo::_TYPE_INT16:	
		case ScriptVarDeclInfo::_TYPE_INT32:	
		{
			return _jscHelper::MakeJSValueAsLong( js_context, 0 );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_UINT8:	
		case ScriptVarDeclInfo::_TYPE_UINT16:	
		case ScriptVarDeclInfo::_TYPE_UINT32:	
		{
			return _jscHelper::MakeJSValueAsDword( js_context, 0 );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_FLOAT:	
		{
			return _jscHelper::MakeJSValueAsFloat( js_context, 0.0f );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_DOUBLE:	
		{
			return _jscHelper::MakeJSValueAsDouble( js_context, 0.0 );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_CLASS:
		case ScriptVarDeclInfo::_TYPE_OBJECT:
		case ScriptVarDeclInfo::_TYPE_BUFFER:
		{

		}
		break;

		case ScriptVarDeclInfo::_TYPE_ASTRING_PTR:
		case ScriptVarDeclInfo::_TYPE_USTRING_PTR:
		case ScriptVarDeclInfo::_TYPE_WSTRING_PTR:
		{
			return _jscHelper::MakeJSValueAsString( js_context, JSStringRefOwner( AString::cEmptyString ) );
		}
		break;

		default:
			break;
	}

	return JS_MAKE_NULL( js_context );
}

JSValueRef _jscHelper::PackJSProperty( JSContextRef js_context, const _jscObjResource* jsc_obj_res, const ScriptPropertyDeclInfo& decl_info, _jscModule* jsc_module )
{
	// Get the wrapped resource
	_byte* wrapped_res = (_byte*) jsc_obj_res->GetWrappedObject( );
	EGE_ASSERT( wrapped_res != _null );

	// Get the property pointer by offset
	_byte* property_ptr = wrapped_res + decl_info.mOffset;

	// Get the property type name
	AString property_type_name = decl_info.mTypeName.Str( );

	// Start to pack the JS value
	JSValueRef js_value;
	switch ( decl_info.mTypeID )
	{
		case ScriptVarDeclInfo::_TYPE_INT8:
		{
			js_value = _jscHelper::MakeJSValueAsLong( js_context, *(_tiny*) property_ptr );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_INT16:
		{
			js_value = _jscHelper::MakeJSValueAsLong( js_context, *(_short*) property_ptr );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_INT32:
		{
			js_value = _jscHelper::MakeJSValueAsLong( js_context, *(_int*) property_ptr );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_UINT8:
		{
			js_value = _jscHelper::MakeJSValueAsDword( js_context, *(_byte*) property_ptr );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_UINT16:
		{
			js_value = _jscHelper::MakeJSValueAsDword( js_context, *(_word*) property_ptr );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_UINT32:
		{
			js_value = _jscHelper::MakeJSValueAsDword( js_context, *(_dword*) property_ptr );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_FLOAT:
		{
			js_value = _jscHelper::MakeJSValueAsFloat( js_context, *(_float*) property_ptr );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_DOUBLE:
		{
			js_value = _jscHelper::MakeJSValueAsDouble( js_context, *(_double*) property_ptr );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_CLASS:
		{
			// It's ANSI object
			if ( property_type_name == "AString" )
			{
				js_value = _jscHelper::MakeJSValueAsString( js_context, JSStringRefOwner( *(AString*) property_ptr ) );
			}
			// It's UTF-8 object
			else if ( property_type_name == "UString" )
			{
				js_value = _jscHelper::MakeJSValueAsString( js_context, JSStringRefOwner( *(UString*) property_ptr ) );
			}
			// It's UTF-16 object
			else if ( property_type_name == "WString" )
			{
				js_value = _jscHelper::MakeJSValueAsString( js_context, JSStringRefOwner( *(WString*) property_ptr ) );
			}
			// Other class
			else
			{
				// Create JS object
				js_value = JS_OBJECT_TO_VALUE( jsc_module->CreateJSObject( js_context, _null, _false ) );
			}
		}
		break;

		case ScriptVarDeclInfo::_TYPE_OBJECT:
		case ScriptVarDeclInfo::_TYPE_BUFFER:
		{

		}
		break;

		case ScriptVarDeclInfo::_TYPE_ASTRING_PTR:
		{
			js_value = _jscHelper::MakeJSValueAsString( js_context, JSStringRefOwner( *(AStringPtr*) property_ptr ) );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_USTRING_PTR:
		{
			js_value = _jscHelper::MakeJSValueAsString( js_context, JSStringRefOwner( *(UStringPtr*) property_ptr ) );
		}
		break;

		case ScriptVarDeclInfo::_TYPE_WSTRING_PTR:
		{
			js_value = _jscHelper::MakeJSValueAsString( js_context, JSStringRefOwner( *(WStringPtr*) property_ptr ) );
		}
		break;

		default:
			EGE_ASSERT( 0 );
			break;
	}

	return js_value;
}

_ubool _jscHelper::UnpackJSProperty( JSContextRef js_context, _jscObjResource* jsc_obj_res, const ScriptPropertyDeclInfo& decl_info, JSValueRef js_value )
{
	// Get the wrapped resource
	_byte* wrapped_res = (_byte*) jsc_obj_res->GetWrappedObject( );
	if ( wrapped_res != _null )
	{
		// Get the property pointer by offset
		_byte* property_ptr = wrapped_res + decl_info.mOffset;

		// Start to unpack the JS value and update the property value
		switch ( decl_info.mTypeID )
		{
			case ScriptVarDeclInfo::_TYPE_INT8:
			{
				*(_tiny*) property_ptr = (_tiny) _jscHelper::JSValue2Number( js_context, js_value, _null );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_INT16:
			{
				*(_short*) property_ptr = (_short) _jscHelper::JSValue2Number( js_context, js_value, _null );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_INT32:
			{
				*(_int*) property_ptr = (_int) _jscHelper::JSValue2Number( js_context, js_value, _null );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_UINT8:
			{
				*(_byte*) property_ptr = (_byte) _jscHelper::JSValue2Number( js_context, js_value, _null );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_UINT16:
			{
				*(_word*) property_ptr = (_word) _jscHelper::JSValue2Number( js_context, js_value, _null );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_UINT32:
			{
				*(_dword*) property_ptr = (_dword) _jscHelper::JSValue2Number( js_context, js_value, _null );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_FLOAT:
			{
				*(_float*) property_ptr = (_float) _jscHelper::JSValue2Number( js_context, js_value, _null );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_DOUBLE:
			{
				*(_double*) property_ptr = _jscHelper::JSValue2Number( js_context, js_value, _null );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_CLASS:
			{
				// Get the module info
				_jscModule* jsc_module = _jscHelper::GetJSCModule( jsc_obj_res->GetJSObject( ) );
				EGE_ASSERT( jsc_module != _null );

				// It's ANSI object
				if ( jsc_module->GetName( ) == "AString" )
				{
					((AString*) property_ptr)->FromString( _jscHelper::GetJSStringW( js_context, js_value ) );
				}
				// It's UTF-8 object
				else if ( jsc_module->GetName( ) == "UString" )
				{
					((UString*) property_ptr)->FromString( _jscHelper::GetJSStringW( js_context, js_value ) );
				}
				// It's UTF-16 object
				if ( jsc_module->GetName( ) == "WString" )
				{
					*(WString*) property_ptr = _jscHelper::GetJSStringW( js_context, js_value );
				}
			}
			break;

			case ScriptVarDeclInfo::_TYPE_OBJECT:
			case ScriptVarDeclInfo::_TYPE_BUFFER:
			{

			}
			break;

			case ScriptVarDeclInfo::_TYPE_ASTRING_PTR:
			{
				*(AStringPtr*) property_ptr = EGE_GLOBAL_STR( _jscHelper::GetJSStringA( js_context, js_value ) );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_USTRING_PTR:
			{
				*(UStringPtr*) property_ptr = EGE_GLOBAL_STR( _jscHelper::GetJSStringU( js_context, js_value ) );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_WSTRING_PTR:
			{
				*(WStringPtr*) property_ptr = EGE_GLOBAL_STR( _jscHelper::GetJSStringW( js_context, js_value ) );
			}
			break;

			default:
				EGE_ASSERT( 0 );
				break;
		}
	}

	return _true;
}

JSValueRef _jscHelper::CallJSFunction( JSContextRef js_context, JSObjectRef js_func, const Variable& p1 )
{
	VariableArray vars;
	vars.Append( p1 );

	return CallJSFunction( js_context, js_func, vars );
}

JSValueRef _jscHelper::CallJSFunction( JSContextRef js_context, JSObjectRef js_func, const Variable& p1, const Variable& p2 )
{
	VariableArray vars;
	vars.Append( p1 );
	vars.Append( p2 );

	return CallJSFunction( js_context, js_func, vars );
}

JSValueRef _jscHelper::CallJSFunction( JSContextRef js_context, JSObjectRef js_func, const Variable& p1, const Variable& p2, const Variable& p3 )
{
	VariableArray vars;
	vars.Append( p1 );
	vars.Append( p2 );
	vars.Append( p3 );

	return CallJSFunction( js_context, js_func, vars );
}

JSValueRef _jscHelper::CallJSFunction( JSContextRef js_context, JSObjectRef js_func, const Variable& p1, const Variable& p2, const Variable& p3, const Variable& p4 )
{
	VariableArray vars;
	vars.Append( p1 );
	vars.Append( p2 );
	vars.Append( p3 );
	vars.Append( p4 );

	return CallJSFunction( js_context, js_func, vars );
}

JSValueRef _jscHelper::CallJSFunction( JSContextRef js_context, JSObjectRef js_func, const Variable& p1, const Variable& p2, const Variable& p3, const Variable& p4, const Variable& p5 )
{
	VariableArray vars;
	vars.Append( p1 );
	vars.Append( p2 );
	vars.Append( p3 );
	vars.Append( p4 );
	vars.Append( p5 );

	return CallJSFunction( js_context, js_func, vars );
}

#endif