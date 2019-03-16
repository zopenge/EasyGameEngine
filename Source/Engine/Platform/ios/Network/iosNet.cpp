//! @file     iosNet.cpp
//! @author   LiCode
//! @version  1.1.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// iosNet Implementation
//----------------------------------------------------------------------------

iosNet::iosNet( )
{
}

iosNet::~iosNet( )
{
}

INet::_STATUS iosNet::GetStatus( ) const
{
	return NSNet_GetStatus( );
}

_ubool iosNet::Ping( AStringPtr address ) const
{
    return _false;
}

_dword iosNet::GetAdapterNumber( ) const
{
	return 0;
}

_dword iosNet::GetLocalIPAddress( _dword adapterindex ) const
{
	return 0;
}

_ubool iosNet::GetLocalMACAddress( AString& mac_address ) const
{
	// These codes referenced from http://ericasadun.com, Thanks for open source
	int	mib[6];
	mib[0] = CTL_NET;
	mib[1] = AF_ROUTE;
	mib[2] = 0;
	mib[3] = AF_LINK;
	mib[4] = NET_RT_IFLIST;
	if ((mib[5] = if_nametoindex("en0")) == 0)
		return _false;

	size_t len = 0;
	if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0)
		return _false;

	MemArrayPtr< _byte > buf( len );
	if (sysctl(mib, 6, buf, &len, NULL, 0) < 0)
		return _false;

	const if_msghdr*	ifm = (const if_msghdr*) buf.GetPointer( );
	const sockaddr_dl*	sdl = (const sockaddr_dl*)(ifm + 1);
	const _byte*		ptr = (const _byte*)LLADDR(sdl);

	mac_address.Format( "%02x%02x%02x%02x%02x%02x", *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5) );

	return _true;
}

_ubool iosNet::EnumIPAddress( _dword* address_list, _dword& number ) const
{
	return _false;
}

_dword iosNet::GetURLIPAddress( AStringPtr url_address ) const
{
	return Platform::GetURLIPAddress( url_address.Str( ) );
}

_ubool iosNet::GetNetworkCardName( AString& name ) const
{
	return _false;
}