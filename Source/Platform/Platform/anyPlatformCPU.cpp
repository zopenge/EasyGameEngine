//! @file     anyPlatformCPU.cpp
//! @author   LiCode
//! @version  1.1.0.695
//! @date     2011/02/13
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// anyPlatformCPU Implementation
//----------------------------------------------------------------------------

const _charw* anyPlatformCPU::GetCPUFamilyName( )
{
 switch ( Platform::GetCPUFamilyID( ) )
 {
  case _CPU_FAMILY_X86: return L"x86";
  case _CPU_FAMILY_ARM: return L"ARM";
  case _CPU_FAMILY_MIPS: return L"MIPS";
  default:
   return L"";
 }
}
