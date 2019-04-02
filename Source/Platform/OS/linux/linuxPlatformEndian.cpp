//! @file     androidPlatformEndian.cpp
//! @author   LiCode
//! @version  1.1.0.695
//! @date     2011/02/13
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform Endian Implementation
//----------------------------------------------------------------------------

_ubool Platform::IsLittleEndian( )
{
	return anyPlatformEndian::IsLittleEndian( );
}

_ubool Platform::IsBigEndian( )
{
	return anyPlatformEndian::IsBigEndian( );
}

_ENDIAN Platform::GetEndianType( )
{
	return anyPlatformEndian::GetEndianType( );
}