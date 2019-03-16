//! @file     winInterfaceFactory.cpp
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
	return new winConsoleApp( );
}

IViewBasedAppPassRef InterfaceFactory::CreateViewBasedApplication( _void* app_handle )
{
	return new winApp( app_handle );
}

IViewBasedAppPassRef InterfaceFactory::CreateViewBasedApplication( _void* app_handle, const PointU& size )
{
	// Windows platform not support this operation
	return _null;
}

IViewBasedAppPassRef InterfaceFactory::CreateViewBasedApplication( IViewBasedApp::_CREATION_FLAG flag )
{
	winViewBasedApp* viewbased_app = new winViewBasedApp( flag );
	if ( viewbased_app->Initialize( ) == _false )
		{ EGE_RELEASE( viewbased_app ); return _null; }

	return viewbased_app;
}

INetFirewallPassRef InterfaceFactory::CreateNetFirewall( )
{
	winNetFirewall* firewall = new winNetFirewall( );
	if ( firewall->Initialize( ) == _false )
		{ firewall->Release( ); return _null; }

	return firewall;
}

IShellPassRef InterfaceFactory::CreateShell( )
{
	winShell* shell = new winShell( );
	if ( shell->Initialize( ) == _false )
		{ shell->Release( ); return _null; }

	return shell;
}

IMenuPassRef InterfaceFactory::CreateMenu( _ubool popup )
{
	winMenu* menu = new winMenu( popup );
	if ( menu->Initialize( ) == _false )
		{ menu->Release( ); return _null; }

	return menu;
}

IProcessDebuggerPassRef InterfaceFactory::CreateProcessDebugger( )
{
	return new winProcessDebugger( );
}

IRegistryPassRef InterfaceFactory::CreateRegistry( IRegistry::_ROOT_KEY root, WStringPtr keyname )
{
	winRegistry* registry = new winRegistry( );
	if ( registry->Initialize( root, keyname ) == _false )
		{ registry->Release( ); return _null; }

	return registry;
}