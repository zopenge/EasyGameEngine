//! @file     iosInterfaceFactory.cpp
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
	return _null;
}

IViewBasedAppPassRef InterfaceFactory::CreateViewBasedApplication( _void* app_handle )
{
	return new iosViewBasedApp( app_handle );
}

IViewBasedAppPassRef InterfaceFactory::CreateViewBasedApplication( _void* app_handle, const PointU& size )
{
	// IOS platform not support this operation
	return _null;
}

IViewBasedAppPassRef InterfaceFactory::CreateViewBasedApplication( WStringPtr title, const PointU& size, IViewBasedApp::_CREATION_FLAG flag )
{
	// IOS platform not support this operation
	return _null;
}

IViewBasedAppPassRef InterfaceFactory::CreateDummyViewBasedApplication( )
{
	// IOS platform not support this operation
	return _null;
}

INetFirewallPassRef InterfaceFactory::CreateNetFirewall( )
{
	return _null;
}

IShellPassRef InterfaceFactory::CreateShell( )
{
	return _null;
}

IMenuPassRef InterfaceFactory::CreateMenu( _ubool popup )
{
	return _null;
}

IProcessDebuggerPassRef InterfaceFactory::CreateProcessDebugger( )
{
	return _null;
}

IRegistryPassRef InterfaceFactory::CreateRegistry( IRegistry::_ROOT_KEY root, WStringPtr keyname )
{
	return _null;
}