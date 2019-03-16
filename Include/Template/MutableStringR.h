//! @file     MutableStringR.h
//! @author   LiCode
//! @version  1.0.1.804
//! @date     2011/03/10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// MutableStringR
//----------------------------------------------------------------------------

//! This class represents a mutable null-terminated string.
template< typename CharType, _ENCODING _STRING_ENCODE >
class MutableStringR
{
private:
	typedef MutableString< CharType, _STRING_ENCODE > _MutableString;
	typedef ConstString< CharType, _STRING_ENCODE > _ConstString;

private:
	_MutableString	mString;

private:
	operator _ConstString ( ) const;
	operator const _ConstString& ( ) const;

public:
	//! Copy-Constructor, create a string by copy another string object.
	//! @param		string	The second string object.
	MutableStringR( const CharType* string );
	//! Copy-Constructor, create a string by copy another string object.
	//! @param		string	The second string object.
	MutableStringR( const _ConstString& string );
	//! Destructor, delete the memory of the string.
	//! @param		none
	~MutableStringR( );

public:
	//!	Convert to const null-terminated string.
	//!	@param		none.
	//!	@return		The const null-terminated string.
	operator const _MutableString& ( ) const;

	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if two strings are same, false otherwise.
	_ubool operator == ( const CharType* string ) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if two strings are same, false otherwise.
	_ubool operator != ( const CharType* string ) const;

	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if two strings are same, false otherwise.
	_ubool operator == ( const MutableStringR& string ) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if two strings are same, false otherwise.
	_ubool operator != ( const MutableStringR& string ) const;

	//!	Get the encode type.
	//!	@param		none.
	//!	@return		The encode type.
	_ENCODING GetEncodeType( ) const;

	//! Get CRC value of the string.
	//! @param		flag		The CRC string flag.
	//! @return		The CRC value of the string.
	_crcvalue GetCRCValue( _dword flag = 0 ) const;

	//! Get the length of the string, excluding the terminal null.
	//! @param		none.
	//! @return		The Length of the string.
	_dword GetLength( ) const;
	//! Get the number of bytes used by string, include the terminal null.
	//! @param		none.
	//! @return		The number of bytes used by string.
	_dword SizeOfBytes( ) const;

	//!	Convert the string to boolean.
	//! @param		none.
	//!	@return		The boolean value.
	_boolean ToBool( ) const;
	//!	Convert the string to signed 32-bits integer.
	//! @param		radix		The base of value, which must be in the range 2¨C36.
	//!	@return		The value in decimal.
	_int ToLong( _dword radix ) const;
	//!	Convert the string to unsigned 32-bits integer.
	//! @param		radix		The base of value, which must be in the range 2¨C36.
	//!	@return		The value in decimal.
	_dword ToDword( _dword radix ) const;
	//!	Convert the string to unsigned 64-bits integer.
	//! @param		radix		The base of value, which must be in the range 2¨C36.
	//!	@return		The value in decimal.
	_qword ToQword( _dword radix ) const;
	//!	Convert the string to float.
	//!	@param		none.
	//!	@return		The value in floating point.
	_float ToFloat( ) const;
	//!	Convert the string to double.
	//!	@param		none.
	//!	@return		The value in floating point.
	_double ToDouble( ) const;

	//!	Check whether starts with specified character or not.
	//! @param		character	The character to be searched.
	//!	@param		ignorecase	True indicates case insensitive.
	//!	@return		True indicates it starts with specified string.
	_ubool StartsWith( CharType character, _ubool ignorecase = _false ) const;
	//!	Check whether starts with specified string or not.
	//! @param		string		The substring to be searched.
	//!	@param		ignorecase	True indicates case insensitive.
	//!	@return		True indicates it starts with specified string.
	_ubool StartsWith( ConstString< CharType, _STRING_ENCODE > string, _ubool ignorecase = _false ) const;
	//!	Check whether ends with specified character or not.
	//! @param		character	The character to be searched.
	//!	@param		ignorecase	True indicates case insensitive.
	//!	@return		True indicates it starts with specified string.
	_ubool EndsWith( CharType character, _ubool ignorecase = _false ) const;
	//!	Check whether ends with specified string or not.
	//! @param		string		The substring to be searched.
	//!	@param		ignorecase	True indicates case insensitive.
	//!	@return		True indicates it starts with specified string.
	_ubool EndsWith( ConstString< CharType, _STRING_ENCODE > string, _ubool ignorecase = _false ) const;

	//! Search a character in the string from left to right.
	//! @param		character	The character to be searched.
	//!	@param		ignorecase	True indicates case insensitive.
	//! @return		The index of the first occurrence of the character or -1 indicates cant find.
	_dword SearchL2R( CharType character, _ubool ignorecase = _false ) const;
	//! Search a character in the string from right to left.
	//! @param		character	The character to be searched.
	//!	@param		ignorecase	True indicates case insensitive.
	//! @return		The index of the first occurrence of the character or -1 indicates cant find.
	_dword SearchR2L( CharType character, _ubool ignorecase = _false ) const;
	//! Search a substring in the string from left to right.
	//! @param		string		The substring to be searched.
	//!	@param		ignorecase	True indicates case insensitive.
	//!	@param		endindex	The end index of searching.
	//! @return		The index of the first occurrence of the substring or -1 indicates cant find.
	_dword SearchL2R( const CharType* string, _ubool ignorecase = _false, _dword* endindex = _null ) const;
	//! Search a substring in the string from right to left.
	//! @param		string		The substring to be searched.
	//!	@param		ignorecase	True indicates case insensitive.
	//!	@param		startindex	The start index of searching.
	//! @return		The index of the first occurrence of the substring or -1 indicates cant find.
	_dword SearchR2L( const CharType* string, _ubool ignorecase = _false, _dword* startindex = _null ) const;
	//! Search a substring in the string from left to right.
	//! @param		string		The substring to be searched.
	//!	@param		ignorecase	True indicates case insensitive.
	//!	@param		endindex	The end index of searching.
	//! @return		The index of the first occurrence of the substring or -1 indicates cant find.
	_dword SearchL2R( ConstString< CharType, _STRING_ENCODE > string, _ubool ignorecase = _false, _dword* endindex = _null ) const;
	//! Search a substring in the string from right to left.
	//! @param		string		The substring to be searched.
	//!	@param		ignorecase	True indicates case insensitive.
	//!	@param		startindex	The start index of searching.
	//! @return		The index of the first occurrence of the substring or -1 indicates cant find.
	_dword SearchR2L( ConstString< CharType, _STRING_ENCODE > string, _ubool ignorecase = _false, _dword* startindex = _null ) const;

	//! Compare two strings
	//! @param		string		The second string object.
	//!	@param		ignorecase	True indicates case insensitive when compare.
	//! @return		True indicates it's the same string.
	_ubool IsEqual( const CharType* string, _ubool ignorecase ) const;
	//! Compare two strings
	//! @param		string		The second string object.
	//!	@param		ignorecase	True indicates case insensitive when compare.
	//! @return		True indicates it's the same string.
	_ubool IsEqual( ConstString< CharType, _STRING_ENCODE > string, _ubool ignorecase ) const;
	//! Compare two strings.
	//! @param		string		The second string object.
	//!	@param		ignorecase	True indicates case insensitive when compare.
	//! @return		The lexicographic relation of two strings, -1, 0, 1.
	_int Compare( const CharType* string, _ubool ignorecase ) const;
	//! Compare two strings.
	//! @param		string		The second string object.
	//!	@param		ignorecase	True indicates case insensitive when compare.
	//! @return		The lexicographic relation of two strings, -1, 0, 1.
	_int Compare( ConstString< CharType, _STRING_ENCODE > string, _ubool ignorecase ) const;
	//! Compare		two strings with wildcards.
	//! @param		string		The second string with wildcards.
	//!	@param		ignorecase	True indicates case insensitive.
	//! @return		True if the string meets the wildcard, false otherwise.
	//!	@remarks	Wildcards must in the second string, otherwise it will be normal character.<br>
	//!				<b>'*'</b> meets zero or more character.<br>
	//!				<b>'?'</b> meets exactly one character.<br>
	//!				'*' must not adjacent with other wildcards together, otherwise will get wrong result.
	//!				For example, "Hello" will meets "He??o" or "H*o" or "*Hello".
	_ubool CompareWildcard( const CharType* string, _ubool ignorecase = _false ) const;
	//! Compare		two strings with wildcards.
	//! @param		string		The second string with wildcards.
	//!	@param		ignorecase	True indicates case insensitive.
	//! @return		True if the string meets the wildcard, false otherwise.
	//!	@remarks	Wildcards must in the second string, otherwise it will be normal character.<br>
	//!				<b>'*'</b> meets zero or more character.<br>
	//!				<b>'?'</b> meets exactly one character.<br>
	//!				'*' must not adjacent with other wildcards together, otherwise will get wrong result.
	//!				For example, "Hello" will meets "He??o" or "H*o" or "*Hello".
	_ubool CompareWildcard( ConstString< CharType, _STRING_ENCODE > string, _ubool ignorecase = _false ) const;

	//!	Check whether the string is empty or not.
	//!	@param		none.
	//!	@return		True indicates it's empty string.
	_ubool IsEmpty( ) const;
	//! Determine if string is empty, or looks like blank.
	//! @param		none.
	//! @return		True if blank, false otherwise.
	_ubool IsBlank( ) const;
	//! Determine the path is a full path or not, a full path will begin with "X:" or "\\"
	//!	@param		none.
	//! @return		True if full path, false otherwise.
	_ubool IsFullpath( ) const;
};

//----------------------------------------------------------------------------
// MutableStringR Implementation
//----------------------------------------------------------------------------

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableStringR< CharType, _STRING_ENCODE >::MutableStringR( const CharType* string )
{
	mString = string;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableStringR< CharType, _STRING_ENCODE >::MutableStringR( const _ConstString& string )
{
	mString = string;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableStringR< CharType, _STRING_ENCODE >::~MutableStringR( )
{
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableStringR< CharType, _STRING_ENCODE >::operator const MutableString< CharType, _STRING_ENCODE >& ( ) const
{
	return mString;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableStringR< CharType, _STRING_ENCODE >::operator == ( const CharType* string ) const
{
	return mString == string;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableStringR< CharType, _STRING_ENCODE >::operator != ( const CharType* string ) const
{
	return mString != string;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableStringR< CharType, _STRING_ENCODE >::operator == ( const MutableStringR& string ) const
{
	return mString == string.mString;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableStringR< CharType, _STRING_ENCODE >::operator != ( const MutableStringR& string ) const
{
	return mString != string.mString;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ENCODING MutableStringR< CharType, _STRING_ENCODE >::GetEncodeType( ) const
{
	return mString.GetEncodeType( );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_crcvalue MutableStringR< CharType, _STRING_ENCODE >::GetCRCValue( _dword flag ) const
{
	return mString.GetCRCValue( flag );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_dword MutableStringR< CharType, _STRING_ENCODE >::GetLength( ) const
{
	return mString.GetLength( );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_dword MutableStringR< CharType, _STRING_ENCODE >::SizeOfBytes( ) const
{
	return mString.SizeOfBytes( );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_boolean MutableStringR< CharType, _STRING_ENCODE >::ToBool( ) const
{
	return mString.ToBool( );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_int MutableStringR< CharType, _STRING_ENCODE >::ToLong( _dword radix ) const
{
	return mString.ToLong( radix );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_dword MutableStringR< CharType, _STRING_ENCODE >::ToDword( _dword radix ) const
{
	return mString.ToDword( radix );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_qword MutableStringR< CharType, _STRING_ENCODE >::ToQword( _dword radix ) const
{
	return mString.ToQword( radix );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_float MutableStringR< CharType, _STRING_ENCODE >::ToFloat( ) const
{
	return mString.ToFloat( );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_double MutableStringR< CharType, _STRING_ENCODE >::ToDouble( ) const
{
	return mString.ToDouble( );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableStringR< CharType, _STRING_ENCODE >::StartsWith( CharType character, _ubool ignorecase ) const
{
	return mString.StartsWith( character, ignorecase );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableStringR< CharType, _STRING_ENCODE >::StartsWith( ConstString< CharType, _STRING_ENCODE > string, _ubool ignorecase ) const
{
	return mString.StartsWith( string, ignorecase );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableStringR< CharType, _STRING_ENCODE >::EndsWith( CharType character, _ubool ignorecase ) const
{
	return mString.EndsWith( character, ignorecase );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableStringR< CharType, _STRING_ENCODE >::EndsWith( ConstString< CharType, _STRING_ENCODE > string, _ubool ignorecase ) const
{
	return mString.EndsWith( string, ignorecase );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_dword MutableStringR< CharType, _STRING_ENCODE >::SearchL2R( CharType character, _ubool ignorecase ) const
{
	return mString.SearchL2R( character, ignorecase );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_dword MutableStringR< CharType, _STRING_ENCODE >::SearchR2L( CharType character, _ubool ignorecase ) const
{
	return mString.SearchR2L( character, ignorecase );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_dword MutableStringR< CharType, _STRING_ENCODE >::SearchL2R( const CharType* string, _ubool ignorecase, _dword* endindex ) const
{
	return mString.SearchL2R( string, ignorecase, endindex );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_dword MutableStringR< CharType, _STRING_ENCODE >::SearchR2L( const CharType* string, _ubool ignorecase, _dword* startindex ) const
{
	return mString.SearchR2L( string, ignorecase, startindex );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_dword MutableStringR< CharType, _STRING_ENCODE >::SearchL2R( ConstString< CharType, _STRING_ENCODE > string, _ubool ignorecase, _dword* endindex ) const
{
	return mString.SearchL2R( string, ignorecase, endindex );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_dword MutableStringR< CharType, _STRING_ENCODE >::SearchR2L( ConstString< CharType, _STRING_ENCODE > string, _ubool ignorecase, _dword* startindex ) const
{
	return mString.SearchR2L( string, ignorecase, startindex );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableStringR< CharType, _STRING_ENCODE >::IsEqual( const CharType* string, _ubool ignorecase ) const
{
	return mString.IsEqual( string, ignorecase );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableStringR< CharType, _STRING_ENCODE >::IsEqual( ConstString< CharType, _STRING_ENCODE > string, _ubool ignorecase ) const
{
	return mString.IsEqual( string, ignorecase );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_int MutableStringR< CharType, _STRING_ENCODE >::Compare( const CharType* string, _ubool ignorecase ) const
{
	return mString.Compare( string, ignorecase );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_int MutableStringR< CharType, _STRING_ENCODE >::Compare( ConstString< CharType, _STRING_ENCODE > string, _ubool ignorecase ) const
{
	return mString.Compare( string, ignorecase );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableStringR< CharType, _STRING_ENCODE >::CompareWildcard( const CharType* string, _ubool ignorecase ) const
{
	return mString.CompareWildcard( string, ignorecase );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableStringR< CharType, _STRING_ENCODE >::CompareWildcard( ConstString< CharType, _STRING_ENCODE > string, _ubool ignorecase ) const
{
	return mString.CompareWildcard( string, ignorecase );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableStringR< CharType, _STRING_ENCODE >::IsEmpty( ) const
{
	return mString.IsEmpty( );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableStringR< CharType, _STRING_ENCODE >::IsBlank( ) const
{
	return mString.IsBlank( );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableStringR< CharType, _STRING_ENCODE >::IsFullpath( ) const
{
	return mString.IsFullpath( );
}

}
