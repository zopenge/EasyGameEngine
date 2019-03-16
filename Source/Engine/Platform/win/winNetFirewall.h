//! @file     winNetFirewall.h
//! @author   LiCode
//! @version  1.0.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// winNetFirewall
//----------------------------------------------------------------------------

class winNetFirewall : public INTERFACE_OBJECT_IMPL( INetFirewall )
{
private:
	//!	The firewall manager interface
	RefPtr< INetFwMgr >		mFirewallManager;
	//!	The firewall policy interface
	RefPtr< INetFwPolicy >	mFirewallPolicy;
	//!	The firewall profile interface
	RefPtr< INetFwProfile >	mFirewallProfile;

public:
	winNetFirewall( );
	virtual ~winNetFirewall( );

public:
	//!	Initialize.
	//!	@param		none.
	//! @return		True indicates success false indicates failure.
	_ubool Initialize( );

// INetFirewall Interface
public:
	virtual _ubool OpenPort( _dword port, _IP_PROTOCOL protocol, WStringPtr name = L"" ) override;
	virtual _ubool ClosePort( _dword port, _IP_PROTOCOL protocol ) override;
};

//----------------------------------------------------------------------------
// winNetFirewall Implementation
//----------------------------------------------------------------------------

}