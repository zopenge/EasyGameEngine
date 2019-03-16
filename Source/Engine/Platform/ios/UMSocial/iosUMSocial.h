//! @file     iosUMSocial.h
//! @author   foreven10
//! @version  1.
//! @date     2013/09/13

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// iosUMSocial
//----------------------------------------------------------------------------

class iosUMSocial : public TUserSystem< IUserSystem >
{
private:
	IViewBasedApp*	mViewBasedApp;
public:
	iosUMSocial( );
	virtual ~iosUMSocial( );

public:
	virtual _ubool Initialize( UStringPtr app_id, UStringPtr channel, IViewBasedApp* viewbased_app ) override;
	virtual _ubool ShowLoginUI( _dword type ) override;
	virtual _void	ApplicationBecomeActive( ) override;
	virtual _ubool	ApplicationOpenUrl( UStringPtr url ) override;
    
    virtual IUserSystemNotifierRef SetNotifier( IUserSystemNotifier* notifier ) override;

	virtual _ubool	GetRankFriend(UStringPtr strtokeninfo,UStringPtr start, UStringPtr count,UStringPtr strTopid ) override;
	virtual _ubool	GetContactContent(UStringPtr strtokeninfo,UStringPtr start, UStringPtr count ) override;
	virtual _ubool	InviteFriend(UStringPtr strtokeninfo,UStringPtr strPhone, UStringPtr strQid ,UStringPtr strSMS) override;
	virtual _ubool	AddFriend(UStringPtr strtokeninfo ) override; 
	virtual _ubool	GetGameFriend(UStringPtr strtokeninfo ,UStringPtr start, UStringPtr count) override;
	virtual _ubool	UploadScore(UStringPtr strtokeninfoz ,UStringPtr strScore,UStringPtr strTopid ) override;
	virtual _ubool	SendGiftMsg(UStringPtr strtokeninfoz ,UStringPtr strQid , UStringPtr strContent ) override;
	virtual _ubool PayFor360( UStringPtr strtokeninfo,UStringPtr	strQid,UStringPtr strAmount,
		UStringPtr strRate,UStringPtr strProductName,UStringPtr strProductID,UStringPtr strNotifyUri,UStringPtr strAppName,UStringPtr strAppUserName,
		UStringPtr strAppUserId,UStringPtr strAppExt1,UStringPtr strAppExt2,UStringPtr strOrderId,UStringPtr strPayType) override;
	virtual _ubool ShareSinaWeibo(UStringPtr strTitle,UStringPtr	strContent, UStringPtr strImagePath,UStringPtr strWXurl,
		UStringPtr strthumbPath,UStringPtr strappPath)override;
	virtual _ubool Logout() override;
	virtual _ubool JoySDK_BindUserInfo( _dword type ) override;
	virtual _ubool JoySDK_PayBilling( _dword money, UStringPtr type, UStringPtr name, int count, UStringPtr ext1, UStringPtr ext2, UStringPtr ext3, UStringPtr ext4 ) override;
	virtual _ubool JoySDK_GetGameFriend( ) override;
	virtual _ubool JoySDK_GetContactContent(  ) override;
	virtual _ubool JoySDK_InviteFriend( UStringPtr id ) override;
	virtual _ubool JoySDK_ReadContacts(  ) override;
	virtual _ubool CM_getMusicisOpen(  ) override;
	virtual _ubool CM_exitGame(  ) override;
	virtual _ubool CM_viewMoreGames(  ) override;
	virtual _ubool CM_payBilling( UStringPtr billingIndex) override;
	virtual _ubool CM_getSimType(  ) override;
};

//----------------------------------------------------------------------------
// iosUMSocial Implementation
//----------------------------------------------------------------------------

}