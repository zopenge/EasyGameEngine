//! @file     iosPlatform.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform Implementation
//----------------------------------------------------------------------------

_ubool Platform::Initialize( )
{
	if ( anyPlatform::Initialize( ) == _false )
		return _false;

	if ( GetIOSPlatformModule( )->Initialize( ) == _false )
		return _false;
	
	return _true;
}

_void Platform::Finalize( )
{
	GetIOSPlatformModule( )->Finalize( );
	
	// Finalize platform
	anyPlatform::Finalize( );
}
