//! @file     iosPlatformLanguage.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform-Language Implementation
//----------------------------------------------------------------------------

_LANG Platform::GetLocalLanguage( )
{
	return _LANG_UNKNOWN;
}

_ubool Platform::IsVowelInThai( _charw code )
{
	return anyPlatformLanguage::IsVowelInThai( code );
}

_ubool Platform::IsUpperVowelInThai( _charw code )
{
	return anyPlatformLanguage::IsUpperVowelInThai( code );
}

_ubool Platform::IsDownVowelInThai( _charw code )
{
	return anyPlatformLanguage::IsDownVowelInThai( code );
}

_ubool Platform::IsToneInThai( _charw code )
{
	return anyPlatformLanguage::IsToneInThai( code );
}