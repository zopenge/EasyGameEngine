//! @file     anyPlatformDebugging.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform-Debugging Implementation
//----------------------------------------------------------------------------

EGE_INTERNAL void __ege__assert( const wchar_t* error, const wchar_t* filename, unsigned int linenumber )
{
 Platform::AssertReport( error, filename, linenumber );
}