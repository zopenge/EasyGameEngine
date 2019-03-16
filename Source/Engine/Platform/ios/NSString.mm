//! @file     NSDevice.mm
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#include "EGEEngine.h"

extern NSString* NSHelper_AnsiToNSString( const _chara* string );
extern NSString* NSHelper_Utf8ToNSString( const _chara* string );
extern NSString* NSHelper_Utf16ToNSString( const _charw* string );

//----------------------------------------------------------------------------
// NS-Device Implementation
//----------------------------------------------------------------------------

NSString* NSString_AnsiToNSString( const _chara* string )
{
	return NSHelper_AnsiToNSString( string );
}

NSString* NSString_Utf8ToNSString( const _chara* string )
{
	return NSHelper_AnsiToNSString( string );
}

NSString* NSString_Utf16ToNSString( const _charw* string )
{
	return NSHelper_Utf16ToNSString( string );
}

WString NSString_NSStringToUtf16( NSString* ns_string )
{
	_charw buffer[2048] = {0};
	[ns_string getCString:(char*)buffer maxLength:2048 encoding:NSUTF16StringEncoding];
	
	return WString( buffer );
}