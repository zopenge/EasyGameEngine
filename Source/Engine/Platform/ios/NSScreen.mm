//! @file     NSScreen.mm
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// NS-Screen Implementation
//----------------------------------------------------------------------------

PointU NS_ScreenGetSize( )
{
    CGSize screen_size = [[[UIScreen mainScreen] currentMode] size];

    float version = [[[UIDevice currentDevice] systemVersion] floatValue];
    if ( version >= 8.0 )
        Math::Swap( screen_size.width, screen_size.height );
	
	return PointU( (_dword) screen_size.width, (_dword) screen_size.height );
}