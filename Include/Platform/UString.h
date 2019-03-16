//! @file     UString.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2011 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// UString
//----------------------------------------------------------------------------

//! This class represents a mutable null-terminated UTF-8 string.
class UString : public String< _chara >
{
public:
	//! Constructor, create a string by copy some characters from another string.
	//! @param		string		Pointer to a null-terminated string.
	//! @param		number		The number of characters to be copy.
	UString( const _chara* string = _null, _dword number = -1 );
	//! Copy-Constructor, create a string by copy another string object.
	//! @param		string		The second string object.
	UString( const AString& string );
	//! Copy-Constructor, create a string by copy another string object.
	//! @param		string		The second string object.
	UString( const WString& string );
	//! Copy-Constructor, create a string by copy another string object.
	//! @param		string		The second string object.
	UString( const UString& string );
	//! Destructor, delete the memory of the string.
	//! @param		none
	~UString( );

public:
	//! Copy the string from another one, and recreates memory to hold it.
	//! @param		string		Pointer to a null-terminated string.
	//! @return		The reference of current string.
	UString& operator = ( const _chara* string );
	//! Copy the string from another one, and recreates memory to hold it.
	//! @param		string		The string object.
	//! @return		The reference of current string.
	UString& operator = ( const UString& string );

	//! Append a character to the end of the string.
	//! @param		character	The character to be append.
	//! @return		The reference of current string.
	UString& operator += ( _chara character );
	//! Append another string to the end of the current one.
	//! @param		string		Pointer to a null-terminated string.
	//! @return		The reference of current string.
	UString& operator += ( const _chara* string );

public:
	//! Import from an ANSI string.
	//! @param		string			The ANSI string.
	//! @return		True indicates success false indicates failure.
	_bool FromAnsiString( AStringPtr string );
	//! Import from an ANSI string.
	//! @param		string			The ANSI string.
	//! @param		stringlength	The ANSI string length.
	//! @return		True indicates success false indicates failure.
	_bool FromAnsiString( const _chara* string, _dword stringlength = -1 );
	//! Import from an UNICODE string.
	//! @param		string			The UNICODE string.
	//! @return		True indicates success false indicates failure.
	_bool FromUnicodeString( WStringPtr string );
	//! Import from an UNICODE string.
	//! @param		string			The UNICODE string.
	//! @param		stringlength	The UNICODE string length.
	//! @return		True indicates success false indicates failure.
	_bool FromUnicodeString( const _charw* string, _dword stringlength = -1 );
};

//----------------------------------------------------------------------------
// UString Implementation
//----------------------------------------------------------------------------

}
