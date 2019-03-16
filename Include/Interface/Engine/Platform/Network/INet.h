//! @file     INet.h
//! @author   LiCode
//! @version  1.0.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// INet
//----------------------------------------------------------------------------

class INet : public IObject
{
public:
	//!	The network status
	enum _STATUS
	{
		_STATUS_OFFLINE,
		_STATUS_VIA_LAN,
		_STATUS_VIA_MODEM,
		_STATUS_VIA_WWAN,
		_STATUS_VIA_WIFI,
	};

public:
	//!	Get the network status.
	//!	@param		none.
	//! @return		The network status.
	virtual _STATUS GetStatus( ) const PURE;

	//!	Get adapter number.
	//!	@param		none.
	//!	@return		The adapter number.
	virtual _dword GetAdapterNumber( ) const PURE;
	//!	Get local IP address.
	//!	@param		adapterindex	The adapter index.
	//!	@return		The local IP address, 0 indicates failure.
	virtual _dword GetLocalIPAddress( _dword adapterindex ) const PURE;
	//!	Get local MAC address.
	//!	@param		mac_address		The local MAC address.
	//! @return		True indicates success false indicates failure.
	virtual _ubool GetLocalMACAddress( AString& mac_address ) const PURE;
	//!	Enumerate IP address.
	//!	@param		address_list	The IP address list.
	//!	@param		number			The address number.
	//! @return		True indicates success false indicates failure.
	virtual _ubool EnumIPAddress( _dword* address_list, _dword& number ) const PURE;

	//!	Get URL IP address.
	//!	@param		url_address		The url address.
	//!	@return		The IP address, 0 indicates failure.
	virtual _dword GetURLIPAddress( AStringPtr url_address ) const PURE;

	//!	Get network card name.
	//!	@param		name			The network card name.
	//! @return		True indicates success false indicates failure.
	virtual _ubool GetNetworkCardName( AString& name ) const PURE;
    
    virtual _ubool Ping( AStringPtr address ) const PURE;
};

}