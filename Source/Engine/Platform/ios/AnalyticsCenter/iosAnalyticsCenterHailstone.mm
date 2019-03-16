#include "EGEEngine.h"

iosAnalyticsCenterHailstone::iosAnalyticsCenterHailstone( UStringPtr game, UStringPtr server, UStringPtr channel, UStringPtr accountName )
{
//    [HailstoneSDK sharedInstance].game = [NSString stringWithUTF8String:game.Str( )];
//    [HailstoneSDK sharedInstance].server = [NSString stringWithUTF8String:server.Str( )];
//    [HailstoneSDK sharedInstance].channel = [NSString stringWithUTF8String:channel.Str( )];
    mAccountName = accountName;
}

iosAnalyticsCenterHailstone::~iosAnalyticsCenterHailstone( )
{

}

_ubool iosAnalyticsCenterHailstone::AddCash( _long paytype, _long addaftermoney, _long addmoney )
{
//    [[HailstoneSDK sharedInstance] addCashWithAccount:[NSString stringWithUTF8String:mAccountName.Str( )] payType:paytype cashAdd:addaftermoney andDelta:addmoney];
    return _true;
}

_ubool iosAnalyticsCenterHailstone::UserLogin( UStringPtr accountID )
{
//    [[HailstoneSDK sharedInstance] loginWithAccount:[NSString stringWithUTF8String:mAccountName.Str( )] andAccountID:[NSString stringWithUTF8String:accountID.Str( )]];
    return _true;
}

_ubool iosAnalyticsCenterHailstone::RedeemWithCode( UStringPtr code )
{
    /*
    if ( mNotifier.IsValid( ) )
        mNotifier->OnRedeem( "" );
    */
    return _true;
}

_void iosAnalyticsCenterHailstone::LogEvent( UStringPtr event_id, const Map< UString, UString >& parameters )
{
    
}

_void iosAnalyticsCenterHailstone::LogEvent( UStringPtr event_id, UStringPtr desc )
{
    
}

_void iosAnalyticsCenterHailstone::Error( UStringPtr error_id, UStringPtr error_msg, UStringPtr error_class )
{

}

_ubool iosAnalyticsCenterHailstone::Initialize( UStringPtr accountName, UStringPtr server, UStringPtr channel )
{
    return _false;
}

_ubool iosAnalyticsCenterHailstone::ShopTrade(UStringPtr order_id,UStringPtr item_id,int item_count, int buytype,int cash_left,int delta)
{
    UString buytype_u = UString( ).FromValue( buytype );
//    [[HailstoneSDK sharedInstance] shopTradeWithAccount:[NSString stringWithUTF8String:mAccountName.Str( )] orderID:[NSString stringWithUTF8String:order_id.Str( )] itemID:[NSString stringWithUTF8String:item_id.Str( )] itemCount:item_count buyType:[NSString stringWithUTF8String:buytype_u.Str( )] cashLeft:cash_left andDelta:delta];
    return _true;
}

_void iosAnalyticsCenterHailstone::SetNotifier( IHailstoneNotifier* notifier )
{
    mNotifier = notifier;
}

IHailstoneNotifierRef iosAnalyticsCenterHailstone::GetNotifier( )
{
    return mNotifier;
}