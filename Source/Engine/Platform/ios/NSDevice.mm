//! @file     NSDevice.mm
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// NS-Device Implementation
//----------------------------------------------------------------------------

WString NSDevice_GetIdentifierForVendor( )
{
	NSUUID* id = [[UIDevice currentDevice] identifierForVendor];

	return NSPlatform::NSStringToUtf16( id.UUIDString );
}

WString	NSDevice_GetAdvertisingIdentifier( )
{
	return NSPlatform::NSStringToUtf16( [[[ASIdentifierManager sharedManager] advertisingIdentifier] UUIDString] );
}

WString	NSDevice_GetDeviceName( )
{
	return NSPlatform::NSStringToUtf16( [[UIDevice currentDevice] name] );
}

WString	NSDevice_GetModelName( )
{
	return NSPlatform::NSStringToUtf16( [[UIDevice currentDevice] model] );
}

WString	NSDevice_GetSystemName( )
{
	return NSPlatform::NSStringToUtf16( [[UIDevice currentDevice] systemName] );
}

WString NSDevice_GetSystemVersion( )
{
	return NSPlatform::NSStringToUtf16( [[UIDevice currentDevice] systemVersion] );
}

WString	NSDevice_GetHardwareID( )
{
    IKeychainRef key_chain = GetPlatform( )->CreateKeychain( L"EGE_IOS_DEVICE_ID", L"" );
	if ( key_chain.IsNull( ) )
		return WString( L"" );
    
    // Try to get the existing devicve hardware ID
    WString value;
    key_chain->GetObject( IKeychain::_KEY_SEC_ATTR_TYPE, value );
    
    // Save the device hardware ID into key chain
    if ( value.IsEmpty( ) )
    {
        value = NSDevice_GetAdvertisingIdentifier( );
        key_chain->SetObject( IKeychain::_KEY_SEC_ATTR_TYPE, value );
    }

	return value;
}

_USER_INTERFACE	NSDevice_GetUserInterfaceIdiom( )
{
	UIUserInterfaceIdiom user_interface_id = [[UIDevice currentDevice] userInterfaceIdiom];

	if ( user_interface_id == UIUserInterfaceIdiomPhone )
		return _USER_INTERFACE_PHONE;
	else if ( user_interface_id == UIUserInterfaceIdiomPad )
		return _USER_INTERFACE_PAD;
	else
		return _USER_INTERFACE_UNKNOWN;
}

_void NS_RegisterForPushNotification( )
{
    NSLog(@"Registering for push notifications...");
    [[UIApplication sharedApplication] registerForRemoteNotificationTypes:
     (UIRemoteNotificationTypeSound | UIRemoteNotificationTypeAlert)];
}