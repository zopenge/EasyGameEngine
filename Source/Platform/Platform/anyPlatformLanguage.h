//! @file     anyPlatformLanguage.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// anyPlatformLanguage
//----------------------------------------------------------------------------

class anyPlatformLanguage
{
public:
	static _ubool IsVowelInThai( _charw code );
	static _ubool IsUpperVowelInThai( _charw code );
	static _ubool IsDownVowelInThai( _charw code );
	static _ubool IsToneInThai( _charw code );
};

//----------------------------------------------------------------------------
// anyPlatformLanguage Implementation
//----------------------------------------------------------------------------

}