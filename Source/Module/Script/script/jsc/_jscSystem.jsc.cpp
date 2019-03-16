//! @file     _jscSystem.jsc.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_JAVA_SCRIPT_CORE_ == 1)

//----------------------------------------------------------------------------
// _jscSystem Implementation
//----------------------------------------------------------------------------

_ubool _jscSystem::OnInititalize( )
{
	// Create global object class
	JSClassDefinition js_class_definition	= kJSClassDefinitionEmpty;
	js_class_definition.attributes			= kJSClassAttributeNoAutomaticPrototype;
	mJSClass = ::JSClassCreate( &js_class_definition );
	if ( mJSClass == _null )
		return _false;

	// Create JS context
	mJSContext = ::JSGlobalContextCreateInGroup( _null, mJSClass );
	if ( mJSContext == _null )
	{
		WLOG_ERROR( L"Create JS context failed" );
		return _false;
	}

	// Save global context
	gGlobalJSContext = mJSContext;

    // Save global object
	gGlobalJSObject = ::JSContextGetGlobalObject( mJSContext );
    if ( gGlobalJSObject == _null )
	{
		WLOG_ERROR( L"Get global JS object from JS context failed" );
		return _false;
	}

	return _true;
}

_void _jscSystem::OnFinalize( )
{
	// Release JS class
	if ( mJSClass != _null )
	{
		::JSClassRelease( mJSClass );
		mJSClass = _null;
	}

	// Release JS context
	if ( JS_IS_VALID( mJSContext ) )
		::JSGlobalContextRelease( mJSContext );
}

#endif