//! @file     NSNet.mm
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// NS-Net Implementation
//----------------------------------------------------------------------------

INet::_STATUS NSNet_GetStatus( )
{
	Reachability* reach = [Reachability reachabilityForLocalWiFi];
	if ( reach != nil && [reach isReachable] )
	{
		if ( [reach isReachableViaWiFi] )
			return INet::_STATUS_VIA_WIFI;
		else if ( [reach isReachableViaWWAN] )
			return INet::_STATUS_VIA_WWAN;
	}

	return INet::_STATUS_OFFLINE;
}

_ubool NSNet_Ping( EGE::AStringPtr address )
{
    NSString* hostname = [NSString stringWithUTF8String:address.Str( )];
    Reachability *reach = [Reachability reachabilityWithHostname:hostname];
	NetworkStatus status = [reach currentReachabilityStatus];
	
	switch (status) {
		case NotReachable:{
			return _false;
		}
			break;
		default:
			break;
	}
    return _true;
}

_void NSNet_OpenUrl( const _chara* url )
{
	[[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithUTF8String:url]]];
}
