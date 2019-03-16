//! @file     androidUserSystem.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// JNI Functions Implementation
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// androidUserSystem Implementation
//----------------------------------------------------------------------------

androidUserSystem::androidUserSystem( )
{
}

androidUserSystem::~androidUserSystem( )
{
}

_ubool androidUserSystem::Initialize( WStringPtr app_id, WStringPtr channel )
{
	if ( BaseClass::Initialize( app_id, channel ) == _false )
		return _false;

	if ( mUserSystemObject.Initialize( "com/ege/android/AndroidUserSystem", _false ) == _false )
		return _false;

	// Call method
	//C2JString j_app_id( app_id );
	//C2JString j_channel( channel );
	//mUserSystemObject.CallStaticVoidMethod( "initUserSystem", "(Ljava/lang/String;Ljava/lang/String;I)V",
	//	j_app_id.GetJString( ), j_channel.GetJString( ), jint( this ) );

	return _true;
}