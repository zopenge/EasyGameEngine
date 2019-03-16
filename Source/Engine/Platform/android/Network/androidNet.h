//! @file     androidNet.h
//! @author   LiCode
//! @version  1.1.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// androidNet
//----------------------------------------------------------------------------

class androidNet : public INTERFACE_OBJECT_IMPL( INet )
{
private:

public:
	androidNet( );
	virtual ~androidNet( );

// INet Interface
public:
	virtual _STATUS GetStatus( ) const override;

	virtual _dword	GetAdapterNumber( ) const override;
	virtual _dword	GetLocalIPAddress( _dword adapterindex ) const override;
	virtual _ubool	GetLocalMACAddress( AString& mac_address ) const override;
	virtual _ubool	EnumIPAddress( _dword* address_list, _dword& number ) const override;

	virtual _dword	GetURLIPAddress( AStringPtr url_address ) const override;

	virtual _ubool	GetNetworkCardName( AString& name ) const override;

	virtual _ubool	Ping( AStringPtr address ) const override;
};

//----------------------------------------------------------------------------
// androidNet Implementation
//----------------------------------------------------------------------------

}