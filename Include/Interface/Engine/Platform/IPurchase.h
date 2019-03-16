//! @file     IPurchase.h
//! @author   LiCode
//! @version  1.0.0.547
//! @date     2011/01/07
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IPurchaseNotifier
//----------------------------------------------------------------------------

class IPurchaseNotifier : public IObject
{
public:
	//!	When buy item succeed.
	//!	@param		id		The item ID.
	//!	@return		none.
	virtual _void OnSucceed( WStringPtr id ) PURE;
	//!	When buy item failed.
	//!	@param		id		The item ID.
	//!	@return		none.
	virtual _void OnFailed( WStringPtr id ) PURE;
	//!	When buy item canceled.
	//!	@param		id		The item ID.
	//!	@return		none.
	virtual _void OnCanceled( WStringPtr id ) PURE;
};

//----------------------------------------------------------------------------
// IPurchase
//----------------------------------------------------------------------------

class IPurchase : public ISerializable
{
public:
	//!	The application info
	struct AppInfo
	{
		//!	The application ID
		WStringObj	mID;
		//!	The application name
		WStringObj	mName;
		//!	The (CP, Content Provider) code
		WStringObj	mCPCode;
		//!	The (CP, Content Provider) ID
		WStringObj	mCPID;
		//!	The company name
		WStringObj	mCompanyName;
		//!	The company telephone number
		WStringObj	mTelNumber;
	};

	//!	The item info.
	struct ItemInfo : public FlagsObject
	{
		//!	The unique item ID
		WString	mID;
		//!	The unique item name
		WString	mName;
		//!	The unique pay code
		WString	mPayCode;
		//!	The description
		WString	mDesc;
		//!	The price
		_dword	mPrice;
	};

public:
	//!	Set the notifier.
	//!	@param		notifier	The notifier.
	//!	@return		none.
	virtual _void SetNotifier( IPurchaseNotifier* notifier ) PURE;
	//!	Get the notifier.
	//!	@param		none.
	//!	@return		The notifier.
	virtual IPurchaseNotifier* GetNotifier( ) PURE;

	//!	Set the application info.
	//!	@param		app_info	The app info.
	//!	@return		none.
	virtual _void SetAppInfo( const AppInfo& app_info ) PURE;
	//!	Get the application info.
	//!	@param		app_info	The app info.
	//!	@return		none.
	virtual const AppInfo& GetAppInfo( ) const PURE;

	//!	Pay the item.
	//!	@param		id			The item ID.
	//! @return		True indicates success otherwise indicates failure.
	virtual _ubool Pay( WStringPtr id ) PURE;
	//!	Add the item.
	//!	@param		item_info	The item info.
	//!	@return		none.
	virtual _void AddItem( const ItemInfo& item_info ) PURE;
	//!	Get the item.
	//!	@param		id			The item ID.
	//!	@return		The item info.
	virtual const ItemInfo* GetItem( WStringPtr id ) const PURE;
};

}