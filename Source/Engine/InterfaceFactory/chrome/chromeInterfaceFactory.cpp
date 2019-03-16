//! @file     chromeInterfaceFactory.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// InterfaceFactory Implementation
//----------------------------------------------------------------------------

IConsoleAppPassRef InterfaceFactory::CreateConsoleApplication( )
{
	// Chrome platform not support this operation
	return _null;
}

IViewBasedAppPassRef InterfaceFactory::CreateViewBasedApplication( _void* app_handle )
{
	// Chrome platform not support this operation
	WLOG_ERROR( L"Create chrome viewbased application whit application handle only failed, not support" );
	return _null;
}

IViewBasedAppPassRef InterfaceFactory::CreateViewBasedApplication( _void* app_handle, const PointU& size )
{
	// Chrome platform not support this operation
	WLOG_ERROR( L"Create chrome viewbased application failed, not support" );
	return _null;
}

IViewBasedAppPassRef InterfaceFactory::CreateViewBasedApplication( WStringPtr title, const PointU& size, IViewBasedApp::_CREATION_FLAG flag )
{
	// Chrome platform not support this operation
	WLOG_ERROR( L"Create chrome viewbased application with title failed, not support" );
	return _null;
}

IViewBasedAppPassRef InterfaceFactory::CreateDummyViewBasedApplication( )
{
	// Chrome platform not support this operation
	return _null;
}

INetFirewallPassRef InterfaceFactory::CreateNetFirewall( )
{
	// Chrome platform not support this operation
	return _null;
}

IShellPassRef InterfaceFactory::CreateShell( )
{
	// Chrome platform not support this operation
	return _null;
}

IMenuPassRef InterfaceFactory::CreateMenu( _ubool popup )
{
	// Chrome platform not support this operation
	return _null;
}

IProcessDebuggerPassRef InterfaceFactory::CreateProcessDebugger( )
{
	// Chrome platform not support this operation
	return _null;
}

IRegistryPassRef InterfaceFactory::CreateRegistry( IRegistry::_ROOT_KEY root, WStringPtr keyname )
{
	// Chrome platform not support this operation
	return _null;
}