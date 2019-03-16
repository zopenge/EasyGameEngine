//! @file     _jscSystem.v8.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_GOOGLE_V8_ == 1)

//----------------------------------------------------------------------------
// _jscSystem Implementation
//----------------------------------------------------------------------------

_ubool _jscSystem::OnInititalize( )
{
	// Initialize ICU
	if ( v8::V8::InitializeICU( ) == _false )
	{
		WLOG_ERROR( L"Initialize ICU for v8 failed" );
		return _false;
	}

	// Get the current isolate
	v8::Isolate* js_isolate = v8::Isolate::GetCurrent( );
	EGE_ASSERT( js_isolate != _null );

	// Create a stack-allocated handle scope. 
	v8::HandleScope handle_scope( v8::Isolate::GetCurrent( ) );
	// Create a new context. 
	v8::Local<v8::Context> context = v8::Context::New( v8::Isolate::GetCurrent( ) );
	// Enter the created context for compiling and 
	// running the hello world script. 
	v8::Context::Scope context_scope(context);
	// Create a string containing the JavaScript source code. 
	v8::Handle<v8::String> source = v8::String::New("'Hello' + ', World!'");
	// Compile the source code. 
	v8::Handle<v8::Script> script = v8::Script::Compile(source);
	// Run the script to get the result. 
	v8::Handle<v8::Value> result = script->Run();
	// Dispose the persistent context. 
	//	context.Dispose();
	// Convert the result to an ASCII string and print it. 
	v8::String::AsciiValue ascii(result); 
	//	printf("%s\n", *ascii); 
	return 0; 

	// Create scope
	//mJSHandleScope = v8::HandleScope( js_isolate );

	// Create context
	v8::Handle< v8::ObjectTemplate > js_global = v8::ObjectTemplate::New( );
	mJSContext = *v8::Context::New( js_isolate, _null, js_global );
	if ( JS_IS_NULL( mJSContext ) )
	{
		WLOG_ERROR( L"Create v8 context failed" );
		return _false;
	}

	return _true;
}

_void _jscSystem::OnFinalize( )
{
}

#endif