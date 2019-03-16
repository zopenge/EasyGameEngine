#include "EGEEngine.h"

JNI_FUNC_2( void, AndroidAnalyticesCenterHailstone, OnRedeem, jint message_id, jint user_data )
{
	OUTPUT_DEBUG_STRING( "JNI_FUNC_2( void, BISK, OnRedeem, jstring message, jint user_data )" );

	androidAnalyticsCenterHailstone* pHialStone = (androidAnalyticsCenterHailstone*) user_data;
	EGE_ASSERT( pHialStone != _null );

	pHialStone->GetNotifier( )->OnRedeem( message_id );
}

androidAnalyticsCenterHailstone::androidAnalyticsCenterHailstone( )
{
	mAppId = "";
}

androidAnalyticsCenterHailstone::~androidAnalyticsCenterHailstone( )
{

}

_ubool androidAnalyticsCenterHailstone::Initialize( UStringPtr accountName, UStringPtr server, UStringPtr channel )
{
	mAccountName = accountName;
	mServer = server;
	mChannel = channel;

	C2JString sAppId( mAppId );
	C2JString sChannel( mChannel );

	if ( mJniInterfaceObject.Initialize( "com/ege/android/AndroidAnalyticesCenterHailstone", _false ) == _false )
		return _false;

	// Call method
	mJniInterfaceObject.CallStaticVoidMethod( "initHailstone", "(ILjava/lang/String;Ljava/lang/String;)V", 
		jint( this ), sAppId.ToJString(), sChannel.ToJString() );

	return _true;
}


_ubool androidAnalyticsCenterHailstone::AddCash( _long paytype, _long addaftermoney, _long addmoney )
{
	C2JString	j_accountName( mAccountName );

	mJniInterfaceObject.CallStaticVoidMethod( "AddCash", "(Ljava/lang/String;III)V",
		j_accountName.ToJString( ),jint(paytype),jint(addaftermoney) ,jint(addmoney));

    return _true;
}

_ubool androidAnalyticsCenterHailstone::UserLogin( UStringPtr accountID )
{
	C2JString	j_accountName( mAccountName );
	C2JString	j_accountID( accountID );

	mJniInterfaceObject.CallStaticVoidMethod( "UserLogin", "(Ljava/lang/String;Ljava/lang/String;)V",
		j_accountName.ToJString( ),j_accountID.ToJString() );
    return _true;
}

_ubool androidAnalyticsCenterHailstone::RedeemWithCode( UStringPtr code )
{
	C2JString	j_code( code );

	mJniInterfaceObject.CallStaticVoidMethod( "RedeemWithCode", "(Ljava/lang/String;)V",
		j_code.ToJString( ) );

    return _true;
}

_void androidAnalyticsCenterHailstone::LogEvent( UStringPtr event_id, const Map< UString, UString >& parameters )
{
    ALOG_TRACE( "TODO: Implement LogEvent( UStringPtr event_id, const Map< UString, UString >& parameters )" );
}

_void androidAnalyticsCenterHailstone::Error( UStringPtr error_id, UStringPtr error_msg, UStringPtr error_class )
{

}

_void androidAnalyticsCenterHailstone::LogEvent( UStringPtr event_id, UStringPtr desc )
{
	C2JString	j_accountName( mAccountName );
	C2JString	j_eventType( event_id );
	C2JString	j_description( desc );

	mJniInterfaceObject.CallStaticVoidMethod( "CustomEvent", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V",
		j_accountName.ToJString( ), j_eventType.ToJString(), j_description.ToJString( ) );
}

_ubool androidAnalyticsCenterHailstone::ShopTrade( UStringPtr order_id,UStringPtr item_id,int item_count, int buytype,int cash_left,int delta )
{
	C2JString	j_accountName( mAccountName );
	C2JString	j_orderid( order_id );
	C2JString	j_itemid( item_id );

	mJniInterfaceObject.CallStaticVoidMethod( "ShopTrade", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;IIII)V",
		j_accountName.ToJString( ), j_orderid.ToJString( ), j_itemid.ToJString( ), jint(item_count), jint(buytype), jint(cash_left), jint(delta) );

	return _true;
}

_void androidAnalyticsCenterHailstone::SetNotifier( IHailstoneNotifier* notifier )
{
	if ( notifier == _null )
		mNotifier = &NullEngine::GetInstance( ).GetHailstoneNotifier( );
	else
		mNotifier = notifier;
}

IHailstoneNotifierRef androidAnalyticsCenterHailstone::GetNotifier( )
{
	return mNotifier;
}

_void androidAnalyticsCenterHailstone::SetAppId( UStringPtr appId )
{
	mAppId = appId;
}
