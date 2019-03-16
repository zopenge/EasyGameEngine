//! @file     iosAnalyticsCenterHailstone.h
//! @author   foreven
//! @version  1.0.0.
//! @date     2013/09/16

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// iosAnalyticsCenterHailstone
//----------------------------------------------------------------------------

class iosAnalyticsCenterHailstone : public TObject< IHailstone >
{
public:
    UString     mAccountName;
    IHailstoneNotifierRef   mNotifier;
public:
	iosAnalyticsCenterHailstone( UStringPtr game, UStringPtr server, UStringPtr channel, UStringPtr accountName );
	virtual ~iosAnalyticsCenterHailstone( );
public:
	virtual _ubool AddCash( _long paytype, _long addaftermoney, _long addmoney ) override;
    virtual _ubool UserLogin( UStringPtr accountID ) override;
    virtual _ubool RedeemWithCode( UStringPtr code ) override;
    virtual	_ubool	Initialize( UStringPtr accountName, UStringPtr server, UStringPtr channel ) override;
	virtual	_ubool	ShopTrade(UStringPtr order_id,UStringPtr item_id,int item_count, int buytype,int cash_left,int delta) override;
	virtual _void LogEvent( UStringPtr event_id, const Map< UString, UString >& parameters ) override;
    virtual _void LogEvent( UStringPtr event_id, UStringPtr desc ) override;
	virtual _void Error( UStringPtr error_id, UStringPtr error_msg, UStringPtr error_class ) override;
    
    virtual _void SetNotifier( IHailstoneNotifier* notifier ) override;
	virtual IHailstoneNotifierRef GetNotifier( ) override;
};

}