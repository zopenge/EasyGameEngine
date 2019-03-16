//! @file     _jscSystem.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_JS_ == 1)

//----------------------------------------------------------------------------
// _jscSystem Implementation
//----------------------------------------------------------------------------

_jscSystem::_jscSystem( ) : mJSHandleScope( JS_CUR_ISOLATE( ) ), mJSRunTime( _null )
{
	mGCCleanupTimer.Init( _DEFAULT_GC_COLLECTION_INTERVAL );

	mJSClass	= _null;
	mJSContext	= _null;
}

_jscSystem::~_jscSystem( )
{
	WLOG_TRACE( L"Finalize JS module ..." );

	// Release all modules
	mModules.Clear( _true );

	// Finalize self
	OnFinalize( );

	// Finalize JS core
	_jscGlobal::GetInstance( ).Finalize( );

	// Finalize JS helper
	_jscHelper::Finalize( );

	WLOG_TRACE( L"Finalize JS module OK" );
}

_void _jscSystem::Tick( _dword limited_elapse, _dword elapse )
{
	mGCCleanupTimer.Tick( elapse );
	if ( mGCCleanupTimer.IsOverdue( ) )
	{
		ALOG_TRACE( "Collecting JSC garbage ..." );
		JS_GARBAGE_COLLECT( mJSContext );
		ALOG_TRACE( "Collect JSC garbage OK" );
	}
}

_ubool _jscSystem::Initialize( )
{
	WLOG_TRACE( L"Create JS module ..." );

	// Create stack allocator
	mAllocator = GetInterfaceFactory( )->CreateStackAllocator( _DEFAULT_STACK_ALLOCATOR_SIZE );
	if ( mAllocator.IsNull( ) )
		return _false;

	// Initialize self
	if ( OnInititalize( ) == _false )
		return _false;

	// Set the global JS context
	gGlobalJSContext = mJSContext;

	// Initialize JS helper
	if ( _jscHelper::Initialize( ) == _false )
		return _false;

	// Initialize JS core
	if ( _jscGlobal::GetInstance( ).Initialize( ) == _false )
	{
		WLOG_ERROR( L"Initialize JS core failed" );
		return _false;
	}

	// Create JS object resource key
	WLOG_TRACE_1( L"Create JS module DONE[ver:%s]", mVersion.ToWString( ).Str( ) );

	return _true;
}

_scriptModuleRef _jscSystem::CreateScriptModule( AStringPtr name, AStringPtr desc )
{
	_jscModule* module = new _jscModule( mJSContext );
	if ( module->Initialize( name, desc ) == _false )
		{ EGE_RELEASE( module ); return _null; }

	mModules.Append( module );

	return _scriptModulePassRef( module ).GetPtr( );
}

_scriptVMPassRef _jscSystem::CreateScriptVM( )
{
	_jscVM* vm = new _jscVM( );
	if ( vm->Initialize( ) == _false )
		{ EGE_RELEASE( vm ); return _null; }

	return vm;
}

#endif