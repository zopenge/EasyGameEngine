//! @file     ConstString.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ConstString
//----------------------------------------------------------------------------

//! This class represents a const null-terminated string.
template< typename CharType, _ENCODING _STRING_ENCODE >
class ConstString
{
public:
	typedef CharType _CharType;

protected:
	//!	The null-terminated string.
	CharType*	mString;

protected:
	//!	Clear.
	//!	@param		none.
	//!	@return		none.
	_void Clear( );

public:
	//! Constructor, create a string points to "".
	//! @param		none.
	ConstString( );
	//! Constructor, create a string points to the specified string.
	//! @param		string		The string pointer.
	ConstString( const CharType* string );
	//! Constructor, create a string points to the specified string.
	//! @param		string		The referenced string.
	ConstString( const ConstString< CharType, _STRING_ENCODE >& string );
	//! Destructor.
	//! @param		none.
	~ConstString( );

public:
	//! Set the string from another one.
	//! @param		string		Pointer to a null-terminated string.
	//! @return		The reference of current string.
	ConstString< CharType, _STRING_ENCODE >& operator = ( const CharType* string );
	//! Set the string from another one.
	//! @param		string		The referenced string object.
	//! @return		The reference of current string.
	ConstString< CharType, _STRING_ENCODE >& operator = ( ConstString< CharType, _STRING_ENCODE > string );

	//! Get a character from string by index.
	//! @param		index		The index of the character in string.
	//! @return		A character specified by index
	template< typename IndexType >
	CharType operator [] ( IndexType index ) const;

	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if two strings are same, false otherwise.
	_ubool operator == ( const CharType* string ) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if two strings are not same, false otherwise.
	_ubool operator != ( const CharType* string ) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if the first string is greater than the second one, false otherwise.
	_ubool operator > ( const CharType* string ) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if the first string is less than the second one, false otherwise.
	_ubool operator < ( const CharType* string ) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if the first string is greater or equal than the second one, false otherwise.
	_ubool operator >= ( const CharType* string ) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if the first string is less or equal than the second one, false otherwise.
	_ubool operator <= ( const CharType* string ) const;

	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if two strings are same, false otherwise.
	_ubool operator == ( ConstString< CharType, _STRING_ENCODE > string ) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if two strings are not same, false otherwise.
	_ubool operator != ( ConstString< CharType, _STRING_ENCODE > string ) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if the first string is greater than the second one, false otherwise.
	_ubool operator > ( ConstString< CharType, _STRING_ENCODE > string ) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if the first string is less than the second one, false otherwise.
	_ubool operator < ( ConstString< CharType, _STRING_ENCODE > string ) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if the first string is greater or equal than the second one, false otherwise.
	_ubool operator >= ( ConstString< CharType, _STRING_ENCODE > string ) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if the first string is less or equal than the second one, false otherwise.
	_ubool operator <= ( ConstString< CharType, _STRING_ENCODE > string ) const;

public:
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

	//! CharType conversion, get the const string pointer.
	//! @param		none.
	//! @return		The const string pointer.
	const CharType* Str( ) const;
	//! Get the substring start from a index.
	//! @param		index		The index of the string, must be less or equal than the length of the string.
	//! @return		The substring from the index.
	ConstString< CharType, _STRING_ENCODE > SubString( _dword index ) const;

	//!	Convert the string to boolean.
	//! @param		none.
	//!	@return		The boolean value.
	_boolean ToBool( ) const;
	//!	Convert the string to signed 32-bits integer.
	//! @param		radix		The base of value, which must be in the range 2每36.
	//!	@return		The value in decimal.
	_int ToLong( _dword radix ) const;
	//!	Convert the string to unsigned 32-bits integer.
	//! @param		radix		The base of value, which must be in the range 2每36.
	//!	@return		The value in decimal.
	_dword ToDword( _dword radix ) const;
	//!	Convert the string to signed 64-bits integer.
	//! @param		radix		The base of value, which must be in the range 2每36.
	//!	@return		The value in decimal.
	_large ToLarge( _dword radix ) const;
	//!	Convert the string to unsigned 64-bits integer.
	//! @param		radix		The base of value, which must be in the range 2每36.
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
// ConstString Implementation
//----------------------------------------------------------------------------

template< typename CharType, _ENCODING _STRING_ENCODE >
ConstString< CharType, _STRING_ENCODE >::ConstString( )
{
	static _dword sNull = 0;
	mString = (CharType*) &sNull;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
ConstString< CharType, _STRING_ENCODE >::ConstString( const CharType* string )
{
	static _dword sNull = 0;
	( string != _null && string[0] != 0 ) ? mString = (CharType*) string : mString = (CharType*) &sNull;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
ConstString< CharType, _STRING_ENCODE >::ConstString( const ConstString< CharType, _STRING_ENCODE >& string )
{
	mString = string.mString;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
ConstString< CharType, _STRING_ENCODE >::~ConstString( )
{
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_void ConstString< CharType, _STRING_ENCODE >::Clear( )
{
	static _dword sNull = 0;
	mString = (CharType*) &sNull;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
ConstString< CharType, _STRING_ENCODE >& ConstString< CharType, _STRING_ENCODE >::operator = ( const CharType* string )
{
	static _dword sNull = 0;
	( string != _null ) ? mString = (CharType*) string : mString = (CharType*) &sNull;

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
ConstString< CharType, _STRING_ENCODE >& ConstString< CharType, _STRING_ENCODE >::operator = ( ConstString< CharType, _STRING_ENCODE > string )
{
	mString = string.mString;

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< typename IndexType >
CharType ConstString< CharType, _STRING_ENCODE >::operator [] ( IndexType index ) const
{
	return mString[ index ];
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::operator == ( const CharType* string ) const
{
	return Platform::CompareString( mString, string ) == 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::operator != ( const CharType* string ) const
{
	return Platform::CompareString( mString, string ) != 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::operator > ( const CharType* string ) const
{
	return Platform::CompareString( mString, string ) > 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::operator < ( const CharType* string ) const
{
	return Platform::CompareString( mString, string ) < 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::operator >= ( const CharType* string ) const
{
	return Platform::CompareString( mString, string ) >= 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::operator <= ( const CharType* string ) const
{
	return Platform::CompareString( mString, string ) <= 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::operator == ( ConstString< CharType, _STRING_ENCODE > string ) const
{
	return Platform::CompareString( mString, string.Str( ) ) == 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::operator != ( ConstString< CharType, _STRING_ENCODE > string ) const
{
	return Platform::CompareString( mString, string.Str( ) ) != 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::operator > ( ConstString< CharType, _STRING_ENCODE > string ) const
{
	return Platform::CompareString( mString, string.Str( ) ) > 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::operator < ( ConstString< CharType, _STRING_ENCODE > string ) const
{
	return Platform::CompareString( mString, string.Str( ) ) < 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::operator >= ( ConstString< CharType, _STRING_ENCODE > string ) const
{
	return Platform::CompareString( mString, string.Str( ) ) >= 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::operator <= ( ConstString< CharType, _STRING_ENCODE > string ) const
{
	return Platform::CompareString( mString, string.Str( ) ) <= 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ENCODING ConstString< CharType, _STRING_ENCODE >::GetEncodeType( ) const
{
	return _STRING_ENCODE;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_crcvalue ConstString< CharType, _STRING_ENCODE >::GetCRCValue( _dword flag ) const
{
	return CRC::BuildFromString( mString, flag );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_dword ConstString< CharType, _STRING_ENCODE >::GetLength( ) const
{
	return Platform::StringLength( mString );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_dword ConstString< CharType, _STRING_ENCODE >::SizeOfBytes( ) const
{
	return ( Platform::StringLength( mString ) + 1 ) * sizeof( CharType );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
const CharType* ConstString< CharType, _STRING_ENCODE >::Str( ) const
{
	return mString;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
ConstString< CharType, _STRING_ENCODE > ConstString< CharType, _STRING_ENCODE >::SubString( _dword index ) const
{
	return ConstString< CharType, _STRING_ENCODE >( mString + index );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_boolean ConstString< CharType, _STRING_ENCODE >::ToBool( ) const
{
	return Platform::ConvertStringToBool( mString );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_int ConstString< CharType, _STRING_ENCODE >::ToLong( _dword radix ) const
{
	return Platform::ConvertStringToLong( mString, radix );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_dword ConstString< CharType, _STRING_ENCODE >::ToDword( _dword radix ) const
{
	return Platform::ConvertStringToDword( mString, radix );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_large ConstString< CharType, _STRING_ENCODE >::ToLarge( _dword radix ) const
{
	return Platform::ConvertStringToLarge( mString, radix );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_qword ConstString< CharType, _STRING_ENCODE >::ToQword( _dword radix ) const
{
	return Platform::ConvertStringToQword( mString, radix );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_float ConstString< CharType, _STRING_ENCODE >::ToFloat( ) const
{
	return Platform::ConvertStringToFloat( mString );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_double ConstString< CharType, _STRING_ENCODE >::ToDouble( ) const
{
	return Platform::ConvertStringToDouble( mString );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::StartsWith( CharType character, _ubool ignorecase ) const
{
	return Platform::SearchL2R( mString, character, ignorecase ) == 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::StartsWith( ConstString< CharType, _STRING_ENCODE > string, _ubool ignorecase ) const
{
	return Platform::SearchL2R( mString, string.Str( ), ignorecase, _null ) == 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::EndsWith( CharType character, _ubool ignorecase ) const
{
	return Platform::SearchR2L( mString, character, ignorecase ) == ( this->GetLength( ) - 1 );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::EndsWith( ConstString< CharType, _STRING_ENCODE > string, _ubool ignorecase ) const
{
	_dword length1 = this->GetLength( );
	_dword length2 = string.GetLength( );

	// The compare string is larger than self
	if ( length2 > length1 )
		return _false;

	// It's the same length, we compare the whole string
	if ( length2 == length1 )
		return *this == string;

	return Platform::SearchR2L( mString, string.Str( ), ignorecase, _null ) == ( length1 - length2 );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_dword ConstString< CharType, _STRING_ENCODE >::SearchL2R( CharType character, _ubool ignorecase ) const
{
	return Platform::SearchL2R( mString, character );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_dword ConstString< CharType, _STRING_ENCODE >::SearchR2L( CharType character, _ubool ignorecase ) const
{
	return Platform::SearchR2L( mString, character );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_dword ConstString< CharType, _STRING_ENCODE >::SearchL2R( const CharType* string, _ubool ignorecase, _dword* endindex ) const
{
	return Platform::SearchL2R( mString, string, ignorecase, endindex );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_dword ConstString< CharType, _STRING_ENCODE >::SearchR2L( const CharType* string, _ubool ignorecase, _dword* startindex ) const
{
	return Platform::SearchR2L( mString, string, ignorecase, startindex );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_dword ConstString< CharType, _STRING_ENCODE >::SearchL2R( ConstString< CharType, _STRING_ENCODE > string, _ubool ignorecase, _dword* endindex ) const
{
	return Platform::SearchL2R( mString, string.Str( ), ignorecase, endindex );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_dword ConstString< CharType, _STRING_ENCODE >::SearchR2L( ConstString< CharType, _STRING_ENCODE > string, _ubool ignorecase, _dword* startindex ) const
{
	return Platform::SearchR2L( mString, string.Str( ), ignorecase, startindex );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::IsEqual( const CharType* string, _ubool ignorecase ) const
{
	return Platform::CompareString( mString, string, ignorecase ) == 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::IsEqual( ConstString< CharType, _STRING_ENCODE > string, _ubool ignorecase ) const
{
	return Platform::CompareString( mString, string.Str( ), ignorecase ) == 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_int ConstString< CharType, _STRING_ENCODE >::Compare( const CharType* string, _ubool ignorecase ) const
{
	return Platform::CompareString( mString, string, ignorecase );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_int ConstString< CharType, _STRING_ENCODE >::Compare( ConstString< CharType, _STRING_ENCODE > string, _ubool ignorecase ) const
{
	return Platform::CompareString( mString, string.Str( ), ignorecase );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::CompareWildcard( const CharType* string, _ubool ignorecase ) const
{
	return Platform::CompareWildcard( mString, string, ignorecase );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::CompareWildcard( ConstString< CharType, _STRING_ENCODE > string, _ubool ignorecase ) const
{
	return Platform::CompareWildcard( mString, string.Str( ), ignorecase );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::IsEmpty( ) const
{
	return mString[0] == 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::IsBlank( ) const
{
	return Platform::IsBlank( mString );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool ConstString< CharType, _STRING_ENCODE >::IsFullpath( ) const
{
	return Platform::IsFullpath( mString );
}

}
