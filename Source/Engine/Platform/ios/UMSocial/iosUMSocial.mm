//! @file     iosUMSocial.cpp
//! @author   foreven10
//! @version  1.1.0.621
//! @date     2013/09/13

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// iosUMSocial Implementation
//----------------------------------------------------------------------------

iosUMSocial::iosUMSocial( )
{
	mViewBasedApp	= _null;
    mNotifier       = &sNullUserSystemNotifier;
}

iosUMSocial::~iosUMSocial( )
{

}

_ubool iosUMSocial::Initialize( UStringPtr app_id, UStringPtr channel, IViewBasedApp* viewbased_app )
{
	mViewBasedApp	= viewbased_app;
	[UMSocialData setAppKey:[NSString stringWithUTF8String:app_id.Str( )]];

	return _true;
}

_ubool iosUMSocial::ShowLoginUI( _dword type )
{
    // Get the NS-Application
	NSApplication* ns_app = (__bridge NSApplication*) mViewBasedApp->GetApplicationHandle( );
    EGE_ASSERT( ns_app != _null );
    
	UMSocialSnsPlatform*	snsPlatform = [UMSocialSnsPlatformManager getSocialPlatformWithName:UMShareToSina];
	snsPlatform.loginClickHandler( ns_app.viewController, [UMSocialControllerService defaultControllerService], YES, ^(UMSocialResponseEntity *response)
	{
        if (response.responseCode == UMSResponseCodeSuccess)
        {
            UMSocialAccountEntity *snsAccount = [[UMSocialAccountManager socialAccountDictionary] valueForKey:UMShareToSina];
            NSLog(@"username is %@, uid is %@, token is %@",snsAccount.userName,snsAccount.usid,snsAccount.accessToken);
            
            WString username = WString( (const _charw*) [snsAccount.userName cStringUsingEncoding:NSUTF16StringEncoding] );
            WString uid = WString( (const _charw*) [snsAccount.usid cStringUsingEncoding:NSUTF16StringEncoding] );
            WString token = WString( (const _charw*) [snsAccount.accessToken cStringUsingEncoding:NSUTF16StringEncoding] );
            
            WString message = WString( L"{ username:" ) + username + WString( L", uid:" ) + uid + WString( L", token:" ) + token + WString( L"}" );
            AString message_a   = AString( ).FromString( message );
            if ( mNotifier.IsValid( ) )
            {
                mNotifier->OnLogin( message_a );
            }
            
            [[UMSocialDataService defaultDataService] requestSnsFriends:UMShareToSina completion:^(UMSocialResponseEntity* response)
             {
                 NSLog( @"GetGameFriend response:, %@", response );
                 AString message_a;
                 if ( mNotifier.IsValid( ) )
                     mNotifier->OnGetContactContent( message_a );
             }];
        }
	});
    
    return _true;
}

_void iosUMSocial::ApplicationBecomeActive( )
{
	[UMSocialSnsService  applicationDidBecomeActive];
}

_ubool iosUMSocial::ApplicationOpenUrl( UStringPtr url )
{
    NSURL* ns_url   = [NSURL URLWithString:[NSString stringWithUTF8String:url.Str( )]];
	 return  [UMSocialSnsService handleOpenURL:ns_url wxApiDelegate:nil];
}

IUserSystemNotifierRef iosUMSocial::SetNotifier( IUserSystemNotifier* notifier )
{
    return SwapRefPtr< IUserSystemNotifier >( mNotifier, notifier, &sNullUserSystemNotifier );
}

_ubool iosUMSocial::GetRankFriend(UStringPtr strtokeninfo,UStringPtr start, UStringPtr count,UStringPtr strTopid )
{
	// do nothing
	return _true;
}

_ubool iosUMSocial::GetContactContent(UStringPtr strtokeninfo,UStringPtr start, UStringPtr count )
{
	[[UMSocialDataService defaultDataService] requestSnsFriends:UMShareToSina completion:^(UMSocialResponseEntity* response)
     {
         NSLog( @"GetContactContent2 response:, @s", response );
         AString message_a;
         if ( mNotifier.IsValid( ) )
             mNotifier->OnGetContactContent( message_a );
     }];

	return _true;
}

_ubool iosUMSocial::InviteFriend(UStringPtr strtokeninfo,UStringPtr strPhone, UStringPtr strQid ,UStringPtr strSMS)
{
	// do nothing
	return _true;
}

_ubool iosUMSocial::AddFriend(UStringPtr strtokeninfo )
{
	// do nothing
	return _true;
}

_ubool iosUMSocial::GetGameFriend(UStringPtr strtokeninfo ,UStringPtr start, UStringPtr count )
{
    [[UMSocialDataService defaultDataService] requestSnsFriends:UMShareToSina completion:^(UMSocialResponseEntity* response)
     {
         NSLog( @"GetGameFriend response:, @s", response );
         AString message_a;
         if ( mNotifier.IsValid( ) )
             mNotifier->OnGetGameFriend( message_a );
     }];
    
	return _true;
}

_ubool iosUMSocial::UploadScore(UStringPtr strtokeninfoz ,UStringPtr strScore,UStringPtr strTopid )
{
	// do nothing
	return _true;
}

_ubool iosUMSocial::SendGiftMsg(UStringPtr strtokeninfoz ,UStringPtr strQid , UStringPtr strContent )
{
	// do nothing
	return _true;
}

_ubool iosUMSocial::PayFor360( UStringPtr strtokeninfo,UStringPtr	strQid,UStringPtr strAmount,
		UStringPtr strRate,UStringPtr strProductName,UStringPtr strProductID,UStringPtr strNotifyUri,UStringPtr strAppName,UStringPtr strAppUserName,
		UStringPtr strAppUserId,UStringPtr strAppExt1,UStringPtr strAppExt2,UStringPtr strOrderId,UStringPtr strPayType )
{
	// do nothing
	return _true;
}

_ubool iosUMSocial::ShareSinaWeibo(UStringPtr strTitle,UStringPtr	strContent, UStringPtr strImagePath,UStringPtr strWXurl,
		UStringPtr strthumbPath,UStringPtr strappPath )
{
	// do nothing
	return _true;
}

_ubool iosUMSocial::Logout()
{
	// do nothing
	return _true;
}

_ubool iosUMSocial::JoySDK_BindUserInfo( _dword type )
{
	// do nothing
	return _true;
}

_ubool iosUMSocial::JoySDK_PayBilling( _dword money, UStringPtr type, UStringPtr name, int count, UStringPtr ext1, UStringPtr ext2, UStringPtr ext3, UStringPtr ext4 )
{
	// do nothing
	return _true;
}

_ubool iosUMSocial::JoySDK_GetGameFriend( )
{
	// do nothing
	return _true;
}

_ubool iosUMSocial::JoySDK_GetContactContent(  )
{
	// do nothing
	return _true;
}

_ubool iosUMSocial::JoySDK_InviteFriend( UStringPtr id )
{
	// do nothing
	return _true;
}

_ubool iosUMSocial::JoySDK_ReadContacts(  )
{
	// do nothing
	return _true;
}

_ubool iosUMSocial::CM_getMusicisOpen(  )
{
	// do nothing
	return _true;
}

_ubool iosUMSocial::CM_exitGame(  )
{
	// do nothing
	return _true;
}

_ubool iosUMSocial::CM_viewMoreGames(  )
{
	// do nothing
	return _true;
}

_ubool iosUMSocial::CM_payBilling( UStringPtr billingIndex)
{
	// do nothing
	return _true;
}

_ubool iosUMSocial::CM_getSimType(  )
{
	// do nothing
	return _true;
}
