//! @file     chromeNet.cpp
//! @author   LiCode
//! @version  1.1.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// chromeNet Implementation
//----------------------------------------------------------------------------

chromeNet::chromeNet( )
{
}

chromeNet::~chromeNet( )
{
}

INet::_STATUS chromeNet::GetStatus( ) const
{
	return _STATUS_OFFLINE;
}

_dword chromeNet::GetAdapterNumber( ) const
{
	return 0;
}

_dword chromeNet::GetLocalIPAddress( _dword adapterindex ) const
{
	return 0;
}

_ubool chromeNet::GetLocalMACAddress( AString& mac_address ) const
{
	return _true;
}

_ubool chromeNet::EnumIPAddress( _dword* address_list, _dword& number ) const
{
	return _false;
}

_dword chromeNet::GetURLIPAddress( AStringPtr url_address ) const
{
	return Platform::GetURLIPAddress( url_address.Str( ) );
}

_ubool chromeNet::GetNetworkCardName( AString& name ) const
{
	return _false;
}

_ubool chromeNet::Ping( AStringPtr address ) const
{
	return _false;
}