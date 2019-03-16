//! @file     androidPlatform.cpp
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

#if (_USE_NEON_ == 1)
	enable_runfast( );
#endif

	return _true;
}

_void Platform::Finalize( )
{
	// Finalize platform
	anyPlatform::Finalize( );
}
