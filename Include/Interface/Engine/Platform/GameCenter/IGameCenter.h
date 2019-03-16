//! @file     IGameCenter.h
//! @author   LiCode
//! @version  1.0.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGameCenter
//----------------------------------------------------------------------------

class IGameCenter : public IObject
{
public:
	//!	Check whether it's available.
	//!	@param		none.
	//!	@return		True indicates it's available.
	virtual _ubool IsAvailable( ) const PURE;

	//!	Open a port in the windows firewall.
	//!	@param		port		The port number.
	//!	@param		protocol	The protocol type setting for this port.
	//!	@param		name		The port name in description.
	//! @return		True indicates success false indicates failure.
};

}