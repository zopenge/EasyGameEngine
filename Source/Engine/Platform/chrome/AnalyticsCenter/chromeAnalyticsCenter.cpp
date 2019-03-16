//! @file     androidAnalyticsCenter.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// androidAnalyticsCenter Implementation
//----------------------------------------------------------------------------

androidAnalyticsCenter::androidAnalyticsCenter( )
{
}

androidAnalyticsCenter::~androidAnalyticsCenter( )
{
	Finalize( );
}

_ubool androidAnalyticsCenter::Initialize( UStringPtr app_id )
{
	if ( mAnalyticesCenterInterfaceObject.Initialize( "com/ege/android/AndroidAnalyticesCenter" ) == _false )
		return _false;

	// Start session
	C2JString j_app_id( app_id );
	mAnalyticesCenterInterfaceObject.CallStaticVoidMethod( "start", "(Landroid/app/Activity;Ljava/lang/String;)V", 
		androidJNI::GetInstance( ).GetContextObj( ), j_app_id.GetJString( ) );

	return _true;
}

_void androidAnalyticsCenter::Finalize( )
{
	// Stop session
	mAnalyticesCenterInterfaceObject.CallStaticVoidMethod( "stop", "()V" );
}

_void androidAnalyticsCenter::SetUserID( UStringPtr user_id )
{
	C2JString j_user_id( user_id );

	mAnalyticesCenterInterfaceObject.CallStaticVoidMethod( "setUserID", "(Ljava/lang/String;)V", j_user_id.GetJString( ) );
}

_void androidAnalyticsCenter::SetAge( _dword age )
{
	mAnalyticesCenterInterfaceObject.CallStaticVoidMethod( "setAge", "(I)V", jint( age ) );
}

_void androidAnalyticsCenter::SetGender( _GENDER gender )
{
	mAnalyticesCenterInterfaceObject.CallStaticVoidMethod( "setGender", "(I)V", jint( gender ) );
}

_void androidAnalyticsCenter::Enable( _ubool enable )
{
	mAnalyticesCenterInterfaceObject.CallStaticVoidMethod( "setLogEnabled", "(Z)V", jboolean( enable ) );
}

_void androidAnalyticsCenter::LogEvent( UStringPtr event_id, const Map< UString, UString >& parameters )
{
	C2JString	j_event_id( event_id );
	C2JStringMap	j_parameters( parameters );

	mAnalyticesCenterInterfaceObject.CallStaticVoidMethod( "logEvent", "(Ljava/lang/String;Ljava/util/Map;)V", 
		j_event_id.GetJString( ), j_parameters.GetMapObject( ) );
}

_void androidAnalyticsCenter::Error( UStringPtr error_id, UStringPtr error_msg, UStringPtr error_class )
{
	C2JString j_error_id( error_id );
	C2JString j_error_msg( error_msg );
	C2JString j_error_class( error_class );

	mAnalyticesCenterInterfaceObject.CallStaticVoidMethod( "error", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", 
		j_error_id.GetJString( ), j_error_msg.GetJString( ), j_error_class.GetJString( ) );
}
