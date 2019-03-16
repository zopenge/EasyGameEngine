//! @file     winNetFirewall.cpp
//! @author   LiCode
//! @version  1.1.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// winNetFirewall Helpful Functions Implementation
//----------------------------------------------------------------------------

static NET_FW_IP_PROTOCOL_ ConvertIPProtocol( INetFirewall::_IP_PROTOCOL protocol )
{
	switch ( protocol )
	{
		case INetFirewall::_IP_PROTOCOL_ANY: return NET_FW_IP_PROTOCOL_ANY;
		case INetFirewall::_IP_PROTOCOL_TCP: return NET_FW_IP_PROTOCOL_TCP;
		case INetFirewall::_IP_PROTOCOL_UDP: return NET_FW_IP_PROTOCOL_UDP;
		default:
			return NET_FW_IP_PROTOCOL_ANY;
	}
}

static INetFirewall::_IP_PROTOCOL ConvertIPProtocol( NET_FW_IP_PROTOCOL_ protocol )
{
	switch ( protocol )
	{
		case NET_FW_IP_PROTOCOL_ANY: return INetFirewall::_IP_PROTOCOL_ANY;
		case NET_FW_IP_PROTOCOL_TCP: return INetFirewall::_IP_PROTOCOL_TCP;
		case NET_FW_IP_PROTOCOL_UDP: return INetFirewall::_IP_PROTOCOL_UDP;
		default:
			return INetFirewall::_IP_PROTOCOL_ANY;
	}
}

//----------------------------------------------------------------------------
// winNetFirewall Implementation
//----------------------------------------------------------------------------

winNetFirewall::winNetFirewall( )
{
}

winNetFirewall::~winNetFirewall( )
{
}

_ubool winNetFirewall::Initialize( )
{
	// Get the network firewall manager interface
	if ( FAILED( ::CoCreateInstance( __uuidof( NetFwMgr ), _null, CLSCTX_INPROC_SERVER, __uuidof( INetFwMgr ), (_void**) &mFirewallManager.GetRawRef( ) ) ) )
		return _false;

	// Get the local firewall policy
	if ( FAILED( mFirewallManager->get_LocalPolicy( &mFirewallPolicy.GetRawRef( ) ) ) )
		return _false;

	// Get the firewall profile
	if ( FAILED( mFirewallPolicy->get_CurrentProfile( &mFirewallProfile.GetRawRef( ) ) ) )
		return _false;

	return _true;
}

_ubool winNetFirewall::OpenPort( _dword port, _IP_PROTOCOL protocol, WStringPtr name )
{
	// Create the firewall port interface
	RefPtr< INetFwOpenPort > firewallport;
	if ( FAILED( ::CoCreateInstance( __uuidof( NetFwOpenPort ), _null, CLSCTX_INPROC_SERVER, __uuidof( INetFwOpenPort ), (void**) &firewallport.GetRawRef( ) ) ) )
		return _false;

	// Open the firewall port
	if ( FAILED( firewallport->put_Port( port ) ) )
		return _false;

	// Set the protocol
	if ( FAILED( firewallport->put_Protocol( ConvertIPProtocol( protocol ) ) ) )
		return _false;
	
	// Set the name in description
	COMBSTR name_bstr( name );
	if ( FAILED( firewallport->put_Name( name_bstr ) ) )
		return _false;

	// Get the global ports access interface
	RefPtr< INetFwOpenPorts > firewallglobalport;
	if ( FAILED( mFirewallProfile->get_GloballyOpenPorts( &firewallglobalport.GetRawRef( ) ) ) )
		return _false;

	// Add the port into global ports
	if ( FAILED( firewallglobalport->Add( firewallport.GetPtr( ) ) ) )
		return _false;

	return _true;
}

_ubool winNetFirewall::ClosePort( _dword port, _IP_PROTOCOL protocol )
{
	// Get the global ports access interface
	RefPtr< INetFwOpenPorts > firewallglobalport;
	if ( FAILED( mFirewallProfile->get_GloballyOpenPorts( &firewallglobalport.GetRawRef( ) ) ) )
		return _false;

	// Remove the port from global ports
	if ( FAILED( firewallglobalport->Remove( port, ConvertIPProtocol( protocol ) ) ) )
		return _false;

	return _true;
}