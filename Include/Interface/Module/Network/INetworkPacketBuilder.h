//! @file     INetworkPacketBuilder.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// INetworkPacketBuilder
//----------------------------------------------------------------------------

class INetworkPacketBuilder
{
public:
	//!	Allocate packet.
	//!	@param		max_size	The max size in bytes.
	//!	@param		name		The packet name.
	//!	@return		none.
	virtual INetworkPacketPassRef AllocPacket( _dword max_size, WStringPtr name = L"" ) PURE;
};

}