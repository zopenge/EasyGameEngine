//! @file     _jscCore.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_JS_ == 1)

//----------------------------------------------------------------------------
// _jscCore Implementation
//----------------------------------------------------------------------------

_jscCore::_jscCore( )
{
	JS_INIT( mJSClass );
}

_jscCore::~_jscCore( )
{
	OnFinalize( );
}

_ubool _jscCore::Initialize( JSContextRef js_context )
{
	WLOG_TRACE( L"Initialize JS core ..." );

	if ( JS_IS_NULL( js_context ) )
	{
		WLOG_ERROR( L"Initialize JS core failed, due to JS context is null" );
		return _false;
	}

	// Initialize self
	AStringPtr js_core_name = "JSCore";
	if ( OnInitialize( js_core_name, js_context ) == _false )
	{
		WLOG_ERROR( L"Initialize JS core failed, due to initialize JS core class failed" );
		return _false;
	}

	// Create JS object
	JSObjectRef js_object = _jscHelper::MakeJSObject( js_context, mJSClass, this );
	if ( js_object == _null )
	{
		WLOG_ERROR( L"Initialize JS core failed, due to create/make JS core class failed" );
		return _false;
	}

	// Set the JS object to global
	if ( _jscHelper::SetJSObjectProperty( js_context, gGlobalJSObject, js_core_name, JS_OBJECT_TO_VALUE( js_object ), 0 ) == _false )
	{
		WLOG_ERROR( L"Initialize JS core failed, due to set JS core class to global object failed" );
		return _false;
	}

	// Register functions
	if ( _jscGlobal::GetInstance( ).RegisterJSFunction( js_context, "JSCore", js_object, "Require", OnRequireFuncCallback, this ) == _false )
	{
		WLOG_ERROR( L"Initialize JS core failed, due to register JS core function failed" );
		return _false;
	}

	WLOG_TRACE( L"Initialize JS core OK" );

	return _true;
}

_void _jscCore::Finalize( )
{
	OnFinalize( );
}

#endif