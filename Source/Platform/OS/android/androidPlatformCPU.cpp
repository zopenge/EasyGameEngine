//! @file     androidPlatformCPU.cpp
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
	return ::android_getCpuCount( );
}

_CPU_FAMILY Platform::GetCPUFamilyID( )
{
	switch ( ::android_getCpuFamily( ) )
	{
		case ANDROID_CPU_FAMILY_ARM:	return _CPU_FAMILY_ARM;
		case ANDROID_CPU_FAMILY_X86:	return _CPU_FAMILY_X86;
		case ANDROID_CPU_FAMILY_MIPS:	return _CPU_FAMILY_MIPS;
		default:
			return _CPU_FAMILY_UNKNOWN;
	}
}

const _charw* Platform::GetCPUFamilyName( )
{
	return anyPlatformCPU::GetCPUFamilyName( );
}

_dword Platform::GetCPUFeatures( )
{
	_dword cpu_features = 0;

	_CPU_FAMILY cpu_family = Platform::GetCPUFamilyID( );
	if ( cpu_family == _CPU_FAMILY_UNKNOWN )
		return 0;

	_qword android_cpu_features = ::android_getCpuFeatures( );
	for ( _dword i = 0; i < 63 && android_cpu_features != 0; i ++, android_cpu_features >>= 1 )
	{
		if ( android_cpu_features & 1 )
		{
			switch ( cpu_family )
			{
				// It's x86 CPU
				case _CPU_FAMILY_X86:
				{
					switch ( 1 << i )
					{
						case ANDROID_CPU_X86_FEATURE_SSSE3:		cpu_features |= _CPU_FEATURE_SSSE3; break;
						case ANDROID_CPU_X86_FEATURE_POPCNT:	cpu_features |= _CPU_FEATURE_POPCNT; break;
						case ANDROID_CPU_X86_FEATURE_MOVBE:		cpu_features |= _CPU_FEATURE_MOVBE; break;
						default:
							break;
					}
				}
				break;

				// It's ARM CPU
				case _CPU_FAMILY_ARM:
				{
					switch ( 1 << i )
					{
						case ANDROID_CPU_ARM_FEATURE_ARMv7:			cpu_features |= _CPU_FEATURE_ARMv7; break;
						case ANDROID_CPU_ARM_FEATURE_VFPv3:			cpu_features |= _CPU_FEATURE_VFPv3; break;
						case ANDROID_CPU_ARM_FEATURE_NEON:			cpu_features |= _CPU_FEATURE_NEON; break;
						case ANDROID_CPU_ARM_FEATURE_LDREX_STREX:	cpu_features |= _CPU_FEATURE_LDREX_STREX; break;
						default:
							break;
					}
				}
				break;

				default:
					break;
			}
		}
	}

	return cpu_features;
}

_float Platform::GetCurrentCPUUsage( )
{
	return 0.0f;
}