//! @file     _pySystem.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_PYTHON_ == 1)

//----------------------------------------------------------------------------
// _pySystem Implementation
//----------------------------------------------------------------------------

_pySystem::_pySystem( )
{
	mVersion = Version( PY_MAJOR_VERSION, PY_MINOR_VERSION, PY_MICRO_VERSION, 0 );
}

_pySystem::~_pySystem( )
{
	WLOG_TRACE( L"Finalize python script module ..." );

	mModules.Clear( _true );

	_pyModule::sPyObjTypeManager.Finalize( );

	Py_Finalize( );

	WLOG_TRACE( L"Finalize python script module OK" );
}

_ubool _pySystem::LoadLibraries( )
{
	/* Import _importlib through its frozen version, _frozen_importlib. */
	if ( PyImport_ImportFrozenModule("_frozen_importlib") <= 0 )
		return _false;

	// Add frozen import libraries
	PyObject* importlib = PyImport_AddModule( "_frozen_importlib" );
	EGE_ASSERT( importlib != _null );

	// Get the python thread state
	PyThreadState* py_thread_state = PyThreadState_Get( );
	if ( py_thread_state == _null )
		return _false;

	// Update thread state
	py_thread_state->interp->importlib = importlib;
	Py_INCREF( importlib );

	/* Install _importlib as __import__ */
	PyObjectOwner impmod = PyInit_imp();
	if ( impmod.IsNull( ) )
		return _false;

	PyObject* sys_modules = PyImport_GetModuleDict();
	if (PyDict_SetItemString(sys_modules, "_imp", impmod) < 0)
		return _false;

	return _true;
}

_void _pySystem::Tick( _dword limited_elapse, _dword elapse )
{
	// Garbage collect
	_dword released_bytes = PyGC_Collect( );
	if ( released_bytes > 0 )
	{
		ALOG_DEBUG_1( "Python GC collected (%d) bytes", released_bytes );
	}
}

_ubool _pySystem::Initialize( )
{
	WLOG_TRACE( L"Create python script module ..." );

	// Suppress 'import site'
	Py_NoSiteFlag				= _true;
	// Skip to load site.py ?!
	Py_NoUserSiteDirectory		= _true;
	// Ignore the environment of python
	Py_IgnoreEnvironmentFlag	= _true;

	// Set the python home and program name
	Py_SetPythonHome( (_charw*) L"." );
	Py_SetProgramName( (_charw*) L"EGE-Python" );

	// Don't install importlib
	_Py_InitializeEx_Private( _true, _false );
	if ( Py_IsInitialized( ) == _false )
	{
		WLOG_ERROR( L"Initialize python failed" );
		return _false;
	}

	// Load libraries
	if ( LoadLibraries( ) == _false )
	{
		WLOG_ERROR( L"Load python libraries failed" );
		return _false;
	}

	WLOG_TRACE_1( L"Create python script module DONE[ver:%s]", mVersion.ToWString( ).Str( ) );

	return _true;
}

_scriptModuleRef _pySystem::CreateScriptModule( AStringPtr name, AStringPtr desc )
{
	_pyModule* module = new _pyModule( );
	if ( module->Initialize( name, desc ) == _false )
		{ EGE_RELEASE( module ); return _null; }

	mModules.Append( module );

	return _scriptModulePassRef( module ).GetPtr( );
}

_scriptVMPassRef _pySystem::CreateScriptVM( )
{
	_pyVM* vm = new _pyVM( );
	if ( vm->Initialize( ) == _false )
		{ EGE_RELEASE( vm ); return _null; }

	return vm;
}

#endif