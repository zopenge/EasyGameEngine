//! @file     androidInterfaceFactory.cpp
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
	// Android platform not support this operation
	return _null;
}

IViewBasedAppPassRef InterfaceFactory::CreateViewBasedApplication( _void* app_handle )
{
	// Android platform not support this operation
	WLOG_ERROR( L"Create android viewbased application whit application handle only failed, not support" );
	return _null;
}

IViewBasedAppPassRef InterfaceFactory::CreateViewBasedApplication( _void* app_handle, const PointU& size )
{
	// Android platform not support this operation
	WLOG_ERROR( L"Create android viewbased application failed, not support" );
	return _null;
}

IViewBasedAppPassRef InterfaceFactory::CreateViewBasedApplication( WStringPtr title, const PointU& size, IViewBasedApp::_CREATION_FLAG flag )
{
	// Android platform not support this operation
	WLOG_ERROR( L"Create android viewbased application with title failed, not support" );
	return _null;
}

IViewBasedAppPassRef InterfaceFactory::CreateDummyViewBasedApplication( )
{
	// Android platform not support this operation
	return _null;
}

INetFirewallPassRef InterfaceFactory::CreateNetFirewall( )
{
	// Android platform not support this operation
	return _null;
}

IShellPassRef InterfaceFactory::CreateShell( )
{
	// Android platform not support this operation
	return _null;
}

IMenuPassRef InterfaceFactory::CreateMenu( _ubool popup )
{
	// Android platform not support this operation
	return _null;
}

IProcessDebuggerPassRef InterfaceFactory::CreateProcessDebugger( )
{
	// Android platform not support this operation
	return _null;
}

IRegistryPassRef InterfaceFactory::CreateRegistry( IRegistry::_ROOT_KEY root, WStringPtr keyname )
{
	// Android platform not support this operation
	return _null;
}