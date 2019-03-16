//! @file     _jscSystem.spidermonkey.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_SPIDER_MONKEY_ == 1)

//----------------------------------------------------------------------------
// _jscSystem Helpful Variables Implementation
//----------------------------------------------------------------------------


#ifdef _SCRIPT_USE_OLD_SPIDER_MONKEY_
	static JSAutoRequest* sJSAutoRequest = _null;
#else
	static JSAutoCompartment* sJSAutoRequest = _null;
#endif


//----------------------------------------------------------------------------
// _jscSystem Helpful Functions Implementation
//----------------------------------------------------------------------------

static void OnReportJSError( JSContext* js_context, const char* message, JSErrorReport* js_report )
{
	EGE_ASSERT( js_report != _null );

	ALOG_ERROR_3( "%s(%u): %s",
		js_report->filename ? js_report->filename : "<no filename>",
		(unsigned int) js_report->lineno,
		message );

	// Dump the callstack
	_jscCallStack::PrintCallStack( js_context );
}

static JSBool OnJSDebugError( JSContext* js_context, const char* message, JSErrorReport* js_report, void* closure )
{
	EGE_ASSERT( js_report != _null );

	ALOG_ERROR_3( "%s(%u): %s",
		js_report->filename ? js_report->filename : "<no filename>",
		(unsigned int) js_report->lineno,
		message );

	// Dump the callstack
	_jscCallStack::PrintCallStack( js_context );

	return _true;
}

//----------------------------------------------------------------------------
// _jscSystem Implementation
//----------------------------------------------------------------------------

_ubool _jscSystem::OnInititalize( )
{
	// Create a JS runtime
#ifdef _SCRIPT_USE_OLD_SPIDER_MONKEY_
	mJSRunTime = JS_NewRuntime( 8 MB );
#else
	mJSRunTime = JS_NewRuntime( 8 MB, JS_NO_HELPER_THREADS );
#endif
	if ( mJSRunTime == _null )
	{
		WLOG_ERROR( L"Create JS run time failed" );
		return _false;
	}

	// Create JS context
	mJSContext = JS_NewContext( mJSRunTime, 8 KB );
	if ( mJSContext == _null )
	{
		WLOG_ERROR( L"Create JS context failed" );
		return _false;
	}

	// Set JS options
	JS_SetOptions( mJSContext, JSOPTION_VAROBJFIX );

	// Set hooker functions
	JS_SetErrorReporter( mJSContext, OnReportJSError );
	JS_SetDebugErrorHook( mJSRunTime, OnJSDebugError, this );

#ifdef _SCRIPT_USE_OLD_SPIDER_MONKEY_
	// Enter a request before running anything in the context
	sJSAutoRequest = new JSAutoRequest( mJSContext );
#endif

	// Create global class
	static JSClass js_global_class = { 
		"global",
		JSCLASS_NEW_RESOLVE | JSCLASS_GLOBAL_FLAGS,
		JS_PropertyStub,
#ifdef _SCRIPT_USE_OLD_SPIDER_MONKEY_
		JS_PropertyStub,
#else
		JS_DeletePropertyStub,
#endif
		JS_PropertyStub,
		JS_StrictPropertyStub,
		JS_EnumerateStub,
		JS_ResolveStub,
		JS_ConvertStub,
		NULL,
		JSCLASS_NO_OPTIONAL_MEMBERS
	};
#ifdef _SCRIPT_USE_OLD_SPIDER_MONKEY_
	JSObjectRef js_global_object = ::JS_NewCompartmentAndGlobalObject( mJSContext, &js_global_class, _null );
#else
	JSObjectRef js_global_object = ::JS_NewGlobalObject( mJSContext, &js_global_class, _null );
#endif
	if ( js_global_object == _null )
		return _false;

#ifndef _SCRIPT_USE_OLD_SPIDER_MONKEY_
	// Enter a request before running anything in the context
	sJSAutoRequest = new JSAutoCompartment( mJSContext, js_global_object );
#endif

	// Set the context's global
	JS_SetGlobalObject( mJSContext, js_global_object );

	// Populate the global object with the standard globals, like Object and Array
	if ( !JS_InitStandardClasses( mJSContext, js_global_object ) )
		return _false;

	// Save global object
	gGlobalJSObject = js_global_object;

	// Output the JS version info
	JSVersion js_version = ::JS_GetVersion( mJSContext );
	ALOG_TRACE_1( "The spider monkey JS version: %d", (_dword) js_version );

	return _true;
}

_void _jscSystem::OnFinalize( )
{
	// Release components
	EGE_DELETE( sJSAutoRequest );

	// Release JS class
	EGE_DELETE( mJSClass );

	if ( JS_IS_VALID( mJSContext ) )
		JS_DestroyContext( mJSContext );

	if ( JS_IS_VALID( mJSRunTime ) )
		JS_DestroyRuntime( mJSRunTime );

	JS_ShutDown( );
}

#endif