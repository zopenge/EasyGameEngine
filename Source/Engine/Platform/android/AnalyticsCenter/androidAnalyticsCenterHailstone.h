//! @file     iosAnalyticsCenterHailstone.h
//! @author   foreven
//! @version  1.0.0.
//! @date     2013/09/16

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// androidAnalyticsCenterHailstone
//----------------------------------------------------------------------------

class androidAnalyticsCenterHailstone : public TObject< IHailstone >
{
public:
	androidAnalyticsCenterHailstone();
	virtual ~androidAnalyticsCenterHailstone( );

public:
	virtual _ubool					AddCash( _long paytype, _long addaftermoney, _long addmoney ) override;
    virtual _ubool					UserLogin( UStringPtr accountID ) override;
    virtual _ubool					RedeemWithCode( UStringPtr code ) override;
	virtual _void					LogEvent( UStringPtr event_id, const Map< UString, UString >& parameters ) override;
	virtual _void					Error( UStringPtr error_id, UStringPtr error_msg, UStringPtr error_class ) override;
	virtual _void					LogEvent( UStringPtr event_id, UStringPtr desc ) override;
	virtual _void					SetNotifier( IHailstoneNotifier* notifier ) override;
	virtual IHailstoneNotifierRef	GetNotifier( ) override;
	virtual _ubool					ShopTrade( UStringPtr order_id,UStringPtr item_id,int item_count, int buytype,int cash_left,int delta );

	_ubool							Initialize( UStringPtr accountName, UStringPtr server, UStringPtr channel );
	_void							SetAppId( UStringPtr appId );

private:
	UString							mAccountName;
	UString							mServer;
	UString							mChannel;
	UString							mAppId;

	//!	The analySDK interface object
	JNIObject				mJniInterfaceObject;
	IHailstoneNotifierRef			mNotifier;
};

}
