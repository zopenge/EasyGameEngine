//! @file     chromePlatformCPU.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform CPU Implementation
//----------------------------------------------------------------------------

_dword Platform::GetCPUNumber( )
{
	return 1;
}

_CPU_FAMILY Platform::GetCPUFamilyID( )
{
	return _CPU_FAMILY_UNKNOWN;
}

const _charw* Platform::GetCPUFamilyName( )
{
	return anyPlatformCPU::GetCPUFamilyName( );
}

_dword Platform::GetCPUFeatures( )
{
	return 0;
}

_float Platform::GetCurrentCPUUsage( )
{
	return 0.0f;
}