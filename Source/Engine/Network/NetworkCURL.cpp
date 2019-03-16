//! @file     NetworkCURL.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// NetworkCURL Implementation
//----------------------------------------------------------------------------

NetworkCURL::NetworkCURL( )
{
}

NetworkCURL::~NetworkCURL( )
{
}

_ubool NetworkCURL::Initialize( )
{
	// Initialize cURL
	if ( ::curl_global_init( CURL_GLOBAL_ALL ) != CURLE_OK )
		return _false;

	return _true;
}

_void NetworkCURL::Finalize( )
{
	// Cleanup cURL
	::curl_global_cleanup( );
}
