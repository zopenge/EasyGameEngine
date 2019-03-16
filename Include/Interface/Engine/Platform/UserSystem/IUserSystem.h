//! @file     IUserSystem.h
//! @author   LiCode
//! @version  1.0.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IUserSystemNotifier
//----------------------------------------------------------------------------

class IUserSystemNotifier : public IObject
{
public:
	//!	When login.
	//!	@param		message		The message info.
	//!	@return		none.
	virtual _void OnLogin( WStringPtr message ) PURE;
	//!	When logout.
	//!	@param		message		The message info.
	//!	@return		none.
	virtual _void OnLogout( WStringPtr message ) PURE;
};

//----------------------------------------------------------------------------
// IUserSystem
//----------------------------------------------------------------------------

class IUserSystem : public IObject
{
public:
	//!	Set the notifier.
	//!	@param		notifier	The notifier.
	//!	@return		none.
	virtual _void SetNotifier( IUserSystemNotifier* notifier ) PURE;
	//!	Get the notifier.
	//!	@param		none.
	//!	@return		The notifier.
	virtual IUserSystemNotifierRef GetNotifier( ) PURE;

	//!	Initialize.
	//!	@param		app_id		The application ID.
	//!	@param		channel		The application channel.
	//! @return		True indicates success false indicates failure.
	virtual _ubool Initialize( WStringPtr app_id, WStringPtr channel ) PURE;

	//!	Get the user info.
	//!	@param		none.
	//! @return		True indicates success false indicates failure.
	virtual _ubool GetUserInfo( ) PURE;

	//!	Show login UI interface.
	//!	@param		none.
	//!	@return		none.
	virtual _void ShowLoginUI( ) PURE;

	//!	Open URL by user system.
	//!	@param		url			The URL address.
	//! @return		True indicates success false indicates failure.
	virtual _ubool OpenURL( WStringPtr url ) PURE;
	//!	Share message.
	//!	@param		message		The share mesasge.
	//! @return		True indicates success false indicates failure.
	virtual _ubool Share( WStringPtr message ) PURE;

	//!	Invite firend.
	//!	@param		message		The invite mesasge.
	//! @return		True indicates success false indicates failure.
	virtual _ubool InviteFriend( WStringPtr message ) PURE;
	//!	Get firends info.
	//!	@param		none.
	//! @return		True indicates success false indicates failure.
	virtual _ubool GetFriends( ) PURE;
};

}