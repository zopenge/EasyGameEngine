//! @file     NSPlatform.h
//! @author   LiCode
//! @version  1.1.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NSPlatform
//----------------------------------------------------------------------------

class NSPlatform
{
public:
	//!	Convert ANSI string to NSString.
	//!	@param		string		The ANSI string.
	//!	@return		The NSString.
	static NSString* AnsiToNSString( const _chara* string );
	//!	Convert UTF-8 string to NSString.
	//!	@param		string		The UTF-8 string.
	//!	@return		The NSString.
	static NSString* Utf8ToNSString( const _chara* string );
	//!	Convert UTF-16 string to NSString.
	//!	@param		string		The UTF-16 string.
	//!	@return		The NSString.
	static NSString* Utf16ToNSString( const _charw* string );
	//!	Convert ANSI string to NSString.
	//!	@param		string		The ANSI string.
	//!	@return		The NSString.
	static NSString* AnsiToNSString( AStringPtr string );
	//!	Convert UTF-8 string to NSString.
	//!	@param		string		The UTF-8 string.
	//!	@return		The NSString.
	static NSString* Utf8ToNSString( UStringPtr string );
	//!	Convert UTF-16 string to NSString.
	//!	@param		string		The UTF-16 string.
	//!	@return		The NSString.
	static NSString* Utf16ToNSString( WStringPtr string );
	//!	Convert ANSI string to NSString.
	//!	@param		string		The ANSI string.
	//!	@return		The NSString.
	static NSString* AnsiToNSString( const AStringR& string );
	//!	Convert UTF-8 string to NSString.
	//!	@param		string		The UTF-8 string.
	//!	@return		The NSString.
	static NSString* Utf8ToNSString( const UStringR& string );
	//!	Convert UTF-16 string to NSString.
	//!	@param		string		The UTF-16 string.
	//!	@return		The NSString.
	static NSString* Utf16ToNSString( const WStringR& string );
	//!	Convert NSString to UTF-16 string.
	//!	@param		string		The NS-String.
	//!	@return		The UTF-16 string.
	static WString NSStringToUtf16( NSString* ns_string );
};

}
