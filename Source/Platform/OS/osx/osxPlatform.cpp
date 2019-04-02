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

	if ( GetIOSResourceModule( )->Initialize( ) == _false )
		return _false;
	
	return _true;
}

_void Platform::Finalize( )
{
	GetIOSResourceModule( )->Finalize( );
	
	// Finalize platform
	anyPlatform::Finalize( );
}