//! @file     INetFirewall.h
//! @author   LiCode
//! @version  1.0.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// INetFirewall
//----------------------------------------------------------------------------

class INetFirewall : public IObject
{
public:
	//!	The protocol type setting
	enum _IP_PROTOCOL
	{
		_IP_PROTOCOL_ANY,
		_IP_PROTOCOL_TCP,
		_IP_PROTOCOL_UDP,
	};

public:
	//!	Open a port in the windows firewall.
	//!	@param		port		The port number.
	//!	@param		protocol	The protocol type setting for this port.
	//!	@param		name		The port name in description.
	//! @return		True indicates success false indicates failure.
	virtual _ubool OpenPort( _dword port, _IP_PROTOCOL protocol, WStringPtr name = L"" ) PURE;
	//!	Close a port in the windows firewall.
	//!	@param		port		The port number.
	//!	@param		protocol	The protocol type setting for this port.
	//! @return		True indicates success false indicates failure.
	virtual _ubool ClosePort( _dword port, _IP_PROTOCOL protocol ) PURE;
};

}