//! @file     _jscHelper.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

class _jscModule;
class _jscObjResource;

//----------------------------------------------------------------------------
// Helpful Macros
//----------------------------------------------------------------------------

#define JS_NULL				_null
#define JS_NULL_STRING		_null
#define JS_INIT( x )		x = _null
#define JS_IS_NULL( x )		(!(x))
#define JS_IS_VALID( x )	((x))

#if (_SCRIPT_USE_GOOGLE_V8_ == 1)

	typedef v8::Data			JSObject;
	typedef v8::Data*			JSObjectRef;
	typedef v8::Value			JSValue;
	typedef v8::Value*			JSValueRef;
	typedef v8::String			JSString;
	typedef v8::String*			JSStringRef;

	typedef v8::ObjectTemplate	JSClass;
	typedef v8::ObjectTemplate*	JSClassRef;

	typedef v8::Context			JSContext;
	typedef v8::Context*		JSContextRef;
	typedef v8::Context			JSGlobalContext;
	typedef v8::Context*		JSGlobalContextRef;
	typedef v8::Context			JSContextGroup;
	typedef v8::Context*		JSContextGroupRef;

	typedef v8::HandleScope		JSHandleScope;
	typedef v8::HandleScope*	JSHandleScopeRef;

	typedef _handle				JSRunTimeRef;

	typedef _dword				JSPropertyAttributes;

	typedef _void (*JSObjectCallAsFunctionCallback)( const v8::FunctionCallbackInfo< v8::Value >& args );

	#define JS_MAKE_NULL( context )			*v8::Null( )
	#define JS_MAKE_UNDEFINED( context )	v8::Undefined( )
	
	#define JS_IS_FUNC( context, x )		0
	#define JS_IS_NULL_VALUE( x )			(!(x))
	#define JS_IS_VALID_VALUE( x )			((x))

	#define JS_CUR_ISOLATE( )				v8::Isolate::GetCurrent( )

	#define JS_STRING_RETAIN( x )			x
	#define JS_STRING_RELEASE( x )			x

	#define JS_GARBAGE_COLLECT( context )	

	#define JS_VALUE_TO_OBJECT( value )		(JSObjectRef) value
	#define JS_OBJECT_TO_VALUE( obj )		(JSValueRef) obj

#elif (_SCRIPT_USE_JAVA_SCRIPT_CORE_ == 1)

	typedef _handle							JSHandleScope;
	typedef _handle							JSRunTimeRef;

	#define JS_MAKE_NULL( context )			::JSValueMakeNull( context )
	#define JS_MAKE_UNDEFINED( context )	::JSValueMakeUndefined( context )

	#define JS_IS_FUNC( context, x )		::JSObjectIsFunction( context, x )
	#define JS_IS_NULL_VALUE( x )			(!(x))
	#define JS_IS_VALID_VALUE( x )			(!(x))

	#define JS_CUR_ISOLATE( )				_null

	#define JS_STRING_RETAIN( x )			::JSStringRetain( (JSStringRef) x )
	#define JS_STRING_RELEASE( x )			::JSStringRelease( (JSStringRef) x )

	#define JS_GARBAGE_COLLECT( context )	::JSGarbageCollect( context )

	#define JS_VALUE_TO_OBJECT( value )		(JSObjectRef) value
	#define JS_OBJECT_TO_VALUE( obj )		(JSValueRef) obj

#elif (_SCRIPT_USE_SPIDER_MONKEY_ == 1)

	typedef JSObject*						JSObjectRef;
	typedef jsval							JSValueRef;
	typedef JSString*						JSStringRef;

	typedef JSClass*						JSClassRef;

	typedef JSContext*						JSContextRef;
	typedef JSContext*						JSGlobalContextRef;
	typedef JSContext*						JSContextGroupRef;

	typedef _handle							JSHandleScope;
	typedef JSRuntime*						JSRunTimeRef;

	typedef _dword							JSPropertyAttributes;

	typedef JSBool (*JSObjectCallAsFunctionCallback)( JSContext* js_context, unsigned argc, jsval* vp );

	#define JS_IS_FUNC( context, x )		::JS_ObjectIsFunction( context, x )

	#define JS_MAKE_NULL( context )			JSVAL_NULL
	#define JS_MAKE_UNDEFINED( context )	JSVAL_VOID
	#define JS_IS_NULL_VALUE( x )			JSVAL_IS_NULL_IMPL( x )
	#define JS_IS_VALID_VALUE( x )			(!JSVAL_IS_NULL_IMPL( x ))

	#define JS_CUR_ISOLATE( )				_null

	#define JS_STRING_RETAIN( x )			x
	#define JS_STRING_RELEASE( x )			x

	#define JS_GARBAGE_COLLECT( context )	

#ifdef _SCRIPT_USE_OLD_SPIDER_MONKEY_
	#define JS_VALUE_TO_OBJECT( value )		JSVAL_IS_OBJECT( value ) ? JSVAL_TO_OBJECT( value ) : _null
#else
	#define JS_VALUE_TO_OBJECT( value )		JSVAL_IS_OBJECT_IMPL( JSVAL_TO_IMPL( value ) ) ? JSVAL_TO_OBJECT( value ) : _null
#endif
	#define JS_OBJECT_TO_VALUE( obj )		OBJECT_TO_JSVAL( obj )

#endif

// The global JS variables
extern JSContextRef gGlobalJSContext;
extern JSObjectRef	gGlobalJSObject;

//----------------------------------------------------------------------------
// JSStringRefOwner
//----------------------------------------------------------------------------

//!	The JS string object wrapper
struct JSStringRefOwner
{
	JSStringRef mJSString;

	JSStringRefOwner( );
	explicit JSStringRefOwner( const JSStringRefOwner& object );
	explicit JSStringRefOwner( JSStringRef object );
	explicit JSStringRefOwner( AStringPtr string );
	explicit JSStringRefOwner( const AStringObj& string );
	explicit JSStringRefOwner( UStringPtr string );
	explicit JSStringRefOwner( const UStringObj& string );
	explicit JSStringRefOwner( WStringPtr string );
	explicit JSStringRefOwner( const WStringObj& string );
	explicit JSStringRefOwner( const _byte* buffer, _dword size );
	~JSStringRefOwner( );

	JSStringRefOwner& operator = ( const JSStringRefOwner& object );
	JSStringRefOwner& operator = ( const AStringObj& string_obj );
	JSStringRefOwner& operator = ( JSStringRef object );

	operator JSStringRef( )
		{ return mJSString; }
	operator const JSStringRef&( ) const
		{ return mJSString; }

	_ubool IsValid( ) const;
	_ubool IsNull( ) const;

	_void CopyFrom( const _byte* buffer, _dword size );

	AString ToStringA( ) const;
	UString ToStringU( ) const;
	WString ToStringW( ) const;
};

//----------------------------------------------------------------------------
// _jscHelper
//----------------------------------------------------------------------------

class _jscHelper
{
private:
	//!	Push number argument.
	static _void PushNumberArgLong( _byte*& args_buffer, JSContextRef js_context, const JSValueRef js_value, JSValueRef* js_exception );
	static _void PushNumberArgDword( _byte*& args_buffer, JSContextRef js_context, const JSValueRef js_value, JSValueRef* js_exception );
	static _void PushNumberArgFloat( _byte*& args_buffer, JSContextRef js_context, const JSValueRef js_value, JSValueRef* js_exception );
	static _void PushNumberArgDouble( _byte*& args_buffer, JSContextRef js_context, const JSValueRef js_value, JSValueRef* js_exception );
	//!	Push StringPtr argument.
	template< typename CharType, _ENCODING _STRING_ENCODE >
	static _void PushStringPtrArg( _byte*& args_buffer, ConstString< CharType, _STRING_ENCODE > c_string, IAllocator* allocator );
	//!	Push class argument.
	template< typename ObjectType >
	static _void PushClassArg( _byte*& args_buffer, const ObjectType* object );

public:
	//!	Initialize.
	static _ubool Initialize( );
	//!	Finalize.
	static _void Finalize( );

	//!	Set JSC module.
	static _ubool SetJSCModule( JSObjectRef js_object, _jscModule* jsc_module );
	//!	Get JSC module.
	static _jscModule* GetJSCModule( JSObjectRef js_object );

	//!	Set the private from object.
	static _ubool SetJSObjectPrivate( JSObjectRef js_object, _void* data );
	//!	Get the private from object.
	static _void* GetJSObjectPrivate( JSObjectRef js_object );

	//!	Set JS object property.
	static _ubool SetJSObjectProperty( JSContextRef js_context, JSObjectRef js_object, AStringPtr name, JSValueRef js_value, JSPropertyAttributes attributes );
	static _ubool SetJSObjectProperty( JSContextRef js_context, JSObjectRef js_object, JSStringRef name, JSValueRef js_value, JSPropertyAttributes attributes );
	//!	Get JS object property.
	static JSValueRef GetJSObjectProperty( JSContextRef js_context, JSObjectRef js_object, AStringPtr name );
	static JSValueRef GetJSObjectProperty( JSContextRef js_context, JSObjectRef js_object, JSStringRef js_name );

	//!	Create JS string.
	static JSStringRef CreateJSStringA( AStringPtr string );
	static JSStringRef CreateJSStringU( UStringPtr string );
	static JSStringRef CreateJSStringW( WStringPtr string );

	//!	Create JS string ref owner.
	static JSStringRef CreateJSString( JSContextRef js_context, const JSValueRef js_value, JSValueRef* js_exception );

	//!	Get ANSI string from JS value object.
	static AString GetJSStringA( JSStringRef js_string );
	static AString GetJSStringA( JSContextRef js_context, JSValueRef js_value );
	//!	Get UTF-8 string from JS value object.
	static UString GetJSStringU( JSStringRef js_string );
	static UString GetJSStringU( JSContextRef js_context, JSValueRef js_value );
	//!	Get UTF-16 string from JS value object.
	static WString GetJSStringW( JSStringRef js_string );
	static WString GetJSStringW( JSContextRef js_context, JSValueRef js_value );

	//!	Register JS property.
	static _ubool RegisterJSProperty( JSContextRef js_context, JSObjectRef js_object, const ScriptPropertyDeclInfo& decl_info );

	//!	Create JS function.
	static JSObjectRef CreateJSFunction( JSContextRef js_context, AStringPtr name, JSObjectCallAsFunctionCallback js_callback_func );
	static JSObjectRef CreateJSFunction( JSContextRef js_context, JSStringRef js_func_name, JSObjectCallAsFunctionCallback js_callback_func );
	//!	Get the JS function object.
	static JSObjectRef GetJSFunction( JSContextRef js_context, AStringPtr func_name );

	//!	Parse js_arguments.
	static _ubool ParseArgs( JSContextRef js_context, _dword args_number, const JSValueRef args[], const ScriptVarDeclInfoArray& js_vars, _byte* args_buffer, JSValueRef* js_exception, IAllocator* allocator );

	//!	Build JS value.
	static JSValueRef BuildJSVAlue( JSContextRef js_context, const Variable& arg );
	static JSValueRef BuildJSVAlue( JSContextRef js_context, ScriptVarDeclInfo::_TYPE type );
	//!	Property get/set operation.
	static JSValueRef PackJSProperty( JSContextRef js_context, const _jscObjResource* jsc_obj_res, const ScriptPropertyDeclInfo& decl_info, _jscModule* jsc_module );
	static _ubool UnpackJSProperty( JSContextRef js_context, _jscObjResource* jsc_obj_res, const ScriptPropertyDeclInfo& decl_info, JSValueRef js_value );

	//!	Throw exception.
	static _void ThrowException( JSContextRef js_context, UStringPtr err_desc, JSObjectRef js_object, JSValueRef* js_exception );

	//!	Call JS function.
	static JSValueRef CallJSFunction( JSContextRef js_context, JSObjectRef js_func );
	static JSValueRef CallJSFunction( JSContextRef js_context, JSObjectRef js_func, const Variable& p1 );
	static JSValueRef CallJSFunction( JSContextRef js_context, JSObjectRef js_func, const Variable& p1, const Variable& p2 );
	static JSValueRef CallJSFunction( JSContextRef js_context, JSObjectRef js_func, const Variable& p1, const Variable& p2, const Variable& p3 );
	static JSValueRef CallJSFunction( JSContextRef js_context, JSObjectRef js_func, const Variable& p1, const Variable& p2, const Variable& p3, const Variable& p4 );
	static JSValueRef CallJSFunction( JSContextRef js_context, JSObjectRef js_func, const Variable& p1, const Variable& p2, const Variable& p3, const Variable& p4, const Variable& p5 );
	static JSValueRef CallJSFunction( JSContextRef js_context, JSObjectRef js_func, const VariableArray& args );

	//!	Evaluate script.
	static _ubool EvaluateScript( JSContextRef js_context, JSStringRef js_script, JSObjectRef js_object, int starting_line_number, AStringPtr script_filename, JSValueRef* js_ret_value, JSValueRef* js_exception );

public:
	//!	Make JS value as number.
	static JSValueRef MakeJSValueAsLong( JSContextRef js_context, _int value );
	static JSValueRef MakeJSValueAsDword( JSContextRef js_context, _dword value );
	static JSValueRef MakeJSValueAsFloat( JSContextRef js_context, _float value );
	static JSValueRef MakeJSValueAsDouble( JSContextRef js_context, _double value );

	//!	Convert JS value to number.
	static _double JSValue2Number( JSContextRef js_context, const JSValueRef js_value, JSValueRef* js_exception );
	static _int JSValue2Long( JSContextRef js_context, const JSValueRef js_value, JSValueRef* js_exception );
	static _dword JSValue2Dword( JSContextRef js_context, const JSValueRef js_value, JSValueRef* js_exception );

	//!	Make JS value as string.
	static JSValueRef MakeJSValueAsString( JSContextRef js_context, JSStringRef js_string );

	//!	Make JS object.
	static JSObjectRef MakeJSObject( JSContextRef js_context, JSClassRef js_class, _void* data );
};

//----------------------------------------------------------------------------
// _jscHelper Implementation
//----------------------------------------------------------------------------

}