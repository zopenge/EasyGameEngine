//! @file     INetworkPacket.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// INetworkPacket
//----------------------------------------------------------------------------

class INetworkPacket : public IStreamWriter
{
public:
	//!	Get the unique ID.
	//!	@param		none.
	//! @return		The unique ID.
	virtual _dword GetID( ) const PURE;
};

}