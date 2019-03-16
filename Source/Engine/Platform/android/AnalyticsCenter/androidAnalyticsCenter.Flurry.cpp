//! @file     androidAnalyticsCenter.Flurry.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// androidAnalyticsCenterFlurry Implementation
//----------------------------------------------------------------------------

androidAnalyticsCenterFlurry::androidAnalyticsCenterFlurry( )
{
}

androidAnalyticsCenterFlurry::~androidAnalyticsCenterFlurry( )
{
	Finalize( );
}

_ubool androidAnalyticsCenterFlurry::Initialize( UStringPtr app_id )
{
	if ( mAnalyticesCenterJNIObject.Initialize( "com/ege/android/AndroidAnalyticesCenter", _false ) == _false )
		return _false;

	// Start session
	C2JString j_app_id( app_id );
	mAnalyticesCenterJNIObject.CallStaticVoidMethod( "start", "(Landroid/app/Activity;Ljava/lang/String;)V", 
		androidJNI::GetInstance( ).GetContextObj( ), j_app_id.ToJString( ) );

	return _true;
}

_void androidAnalyticsCenterFlurry::Finalize( )
{
	// Stop session
	mAnalyticesCenterJNIObject.CallStaticVoidMethod( "stop", "()V" );
}

_void androidAnalyticsCenterFlurry::SetUserID( UStringPtr user_id )
{
	C2JString j_user_id( user_id );

	mAnalyticesCenterJNIObject.CallStaticVoidMethod( "setUserID", "(Ljava/lang/String;)V", j_user_id.ToJString( ) );
}

_void androidAnalyticsCenterFlurry::SetAge( _dword age )
{
	mAnalyticesCenterJNIObject.CallStaticVoidMethod( "setAge", "(I)V", jint( age ) );
}

_void androidAnalyticsCenterFlurry::SetGender( _GENDER gender )
{
	mAnalyticesCenterJNIObject.CallStaticVoidMethod( "setGender", "(I)V", jint( gender ) );
}

_void androidAnalyticsCenterFlurry::Enable( _ubool enable )
{
	mAnalyticesCenterJNIObject.CallStaticVoidMethod( "setLogEnabled", "(Z)V", jboolean( enable ) );
}

_void androidAnalyticsCenterFlurry::LogEvent( UStringPtr event_id, const Map< UString, UString >& parameters )
{
	WLOG_TRACE_1( L"androidAnalyticsCenterFlurry::LogEvent 1 (%s)", WString( ).FromString( event_id ).Str( ) );

	C2JString		j_event_id( event_id );
	C2JStringMap	j_parameters( parameters );

	WLOG_TRACE( L"androidAnalyticsCenterFlurry::LogEvent 2" );

	mAnalyticesCenterJNIObject.CallStaticVoidMethod( "logEvent", "(Ljava/lang/String;Ljava/util/Map;)V", 
		j_event_id.ToJString( ), j_parameters.ToJMapObject( ) );

	WLOG_TRACE( L"androidAnalyticsCenterFlurry::LogEvent 3" );
}

_void androidAnalyticsCenterFlurry::Error( UStringPtr error_id, UStringPtr error_msg, UStringPtr error_class )
{
	C2JString j_error_id( error_id );
	C2JString j_error_msg( error_msg );
	C2JString j_error_class( error_class );

	mAnalyticesCenterJNIObject.CallStaticVoidMethod( "error", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", 
		j_error_id.ToJString( ), j_error_msg.ToJString( ), j_error_class.ToJString( ) );
}

_void androidAnalyticsCenterFlurry::LogEvent( UStringPtr event_id, UStringPtr desc )
{

}
