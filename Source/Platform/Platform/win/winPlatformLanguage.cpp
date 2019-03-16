//! @file     winPlatformLanguage.cpp
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
	_dword langid = ::GetUserDefaultLangID( );

	switch ( langid & 0x000003FF )
	{
		case LANG_ENGLISH:	return _LANG_ENG;
		case LANG_CHINESE:	return langid == 0x0804 ? _LANG_CHS : _LANG_CHT;
	}

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