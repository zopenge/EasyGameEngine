//! @file     androidNet.cpp
//! @author   LiCode
//! @version  1.1.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// androidNet Implementation
//----------------------------------------------------------------------------

androidNet::androidNet( )
{
}

androidNet::~androidNet( )
{
}

INet::_STATUS androidNet::GetStatus( ) const
{
	// Get JNI utils object
	JNIObject& utils_obj = androidJNI::GetInstance( ).GetUtilsObj( );

	// Get JNI context
	jobject	jni_context = androidJNI::GetInstance( ).GetContextObj( );

	// Get the method
	int network_type = utils_obj.CallStaticIntMethod( "getNetworkInfo", "(Landroid/content/Context;)I", jni_context );
	
	// AndroidUtils network status constants
	const _dword CMNET	= 1; 
	const _dword CMWAP	= 2; 
	const _dword WIFI	= 3; 

	// Check network status
	switch ( network_type )
	{
		case CMNET:
		case CMWAP:
			return _STATUS_VIA_WWAN;

		case WIFI:
			return _STATUS_VIA_WIFI;

		default:
			break;
	}

	return _STATUS_OFFLINE;
}

_dword androidNet::GetAdapterNumber( ) const
{
	return 0;
}

_dword androidNet::GetLocalIPAddress( _dword adapterindex ) const
{
	return 0;
}

_ubool androidNet::GetLocalMACAddress( AString& mac_address ) const
{
	// Get JNI utils object
	JNIObject& utils_obj = androidJNI::GetInstance( ).GetUtilsObj( );

	// Call method
	jobject js_mac_string = (jobject) utils_obj.CallStaticObjectMethod( "getMACAddress", "()Ljava/lang/String;" );
	EGE_ASSERT( js_mac_string != _null );

	// Get the JNI env handle
	androidJNIEnv jni_env = androidJNI::GetInstance( ).GetJNIEnv( );

	// Get the mac address string in UTF8
	const _chara* mac_string = jni_env->GetStringUTFChars( (jstring) js_mac_string, _null );
	EGE_ASSERT( mac_string != _null );

	// Feedback the mac address
	for ( _dword i = 0; mac_string[i] != 0; i ++ )
	{
		if ( mac_string[i] == ':' )
			continue;

		mac_address += mac_string[i];
	}

	return _true;
}

_ubool androidNet::EnumIPAddress( _dword* address_list, _dword& number ) const
{
	return _false;
}

_dword androidNet::GetURLIPAddress( AStringPtr url_address ) const
{
	return Platform::GetURLIPAddress( url_address.Str( ) );
}

_ubool androidNet::GetNetworkCardName( AString& name ) const
{
	return _false;
}

_ubool androidNet::Ping( AStringPtr address ) const
{
	return _false;
}