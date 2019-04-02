//! @file     chromePlatformConsole.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform Console Implementation
//----------------------------------------------------------------------------

_chara Platform::GetAChar( )
{
	return getchar( );
}

_charw Platform::GetWChar( )
{
	return getwchar( );
}

_void Platform::WriteConsole( const _chara* string )
{
}

_void Platform::WriteConsole( const _charw* string )
{
}