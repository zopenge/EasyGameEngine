//! @file     RawArray.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{
	
//----------------------------------------------------------------------------
// RawString
//----------------------------------------------------------------------------

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE = 1024 >
class RawString
{
private:
	//!	The string buffer
	CharType	mString[ _SIZE ];

public:
	RawString( );
	explicit RawString( const CharType* string, _dword number = -1 );
	~RawString( );

public:
	//! Set the string from another one.
	//! @param		string		Pointer to a null-terminated string.
	//! @return		The reference of current string.
	RawString& operator = ( const CharType* string );

	//! Append a character to the end of the string.
	//! @param		character	The character to be append.
	//! @return		The reference of current string.
	RawString& operator += ( CharType character );
	//! Append another string to the end of the current one.
	//! @param		string		Pointer to a null-terminated string.
	//! @return		The reference of current string.
	RawString& operator += ( const CharType* string );

	//! Get a character from string by index.
	//! @param		index		The index of the character in string.
	//! @return		A character specified by index
	CharType& operator [] ( _int index );
	//! Get a character from string by index.
	//! @param		index		The index of the character in string.
	//! @return		A character specified by index
	CharType& operator [] ( _dword index );

	//! Get a character from string by index.
	//! @param		index		The index of the character in string.
	//! @return		A character specified by index
	CharType operator [] ( _int index ) const;
	//! Get a character from string by index.
	//! @param		index		The index of the character in string.
	//! @return		A character specified by index
	CharType operator [] ( _dword index ) const;

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

	//! Insert a character into the index of the string.
	//! @param		index		The index of the string
	//! @param		character	The character to be inserted.
	//! @return		none.
	_void Insert( _dword index, CharType character );
	//! Insert a substring into the index of the string.
	//! @param		index		The index of the string.
	//! @param		string		The substring to be inserted.
	//! @return		none.
	_void Insert( _dword index, const CharType* string );

	//! Type conversion, get the const string pointer.
	//! @param		none.
	//! @return		The const string pointer.
	const CharType* Str( ) const;
	//! Get the substring start from a index.
	//! @param		index		The index of the string, must be less or equal than the length of the string.
	//! @return		The substring from the index.
	const CharType* SubString( _dword index ) const;

	//!	Check whether starts with specified string or not.
	//! @param		string		The substring to be searched.
	//!	@return		True indicates it starts with specified string.
	_ubool StartsWith( const CharType* string ) const;

	//! Search a character in the string from left to right.
	//! @param		character	The character to be searched.
	//! @return		The index of the first occurrence of the character or -1 indicates cant find.
	_dword SearchL2R( CharType character ) const;
	//! Lowercased version of SearchL2R ( character ).
	//! @param		character	The character to be searched.
	//! @return		The index of the first occurrence of the character or -1 indicates cant find.
	_dword SearchL2RLowercase( CharType character ) const;
	//! Search a character in the string from right to left.
	//! @param		character	The character to be searched.
	//! @return		The index of the first occurrence of the character or -1 indicates cant find.
	_dword SearchR2L( CharType character ) const;
	//! Lowercased version of SearchR2L ( character ).
	//! @param		character	The character to be searched.
	//! @return		The index of the first occurrence of the character or -1 indicates cant find.
	_dword SearchR2LLowercase( CharType character ) const;
	//! Search a substring in the string from left to right.
	//! @param		string		The substring to be searched.
	//!	@param		endindex	The end index of searching.
	//! @return		The index of the first occurrence of the substring or -1 indicates cant find.
	_dword SearchL2R( const CharType* string, _dword* endindex = _null ) const;
	//! Lowercased version of SearchL2R ( string ).
	//! @param		string		The substring to be searched.
	//!	@param		endindex	The end index of searching.
	//! @return		The index of the first occurrence of the substring or -1 indicates cant find.
	_dword SearchL2RLowercase( const CharType* string, _dword* endindex = _null ) const;
	//! Search a substring in the string from right to left.
	//! @param		string		The substring to be searched.
	//!	@param		startindex	The start index of searching.
	//! @return		The index of the first occurrence of the substring or -1 indicates cant find.
	_dword SearchR2L( const CharType* string, _dword* startindex = _null ) const;
	//! Lowercased version of SearchR2L ( string ).
	//! @param		string		The substring to be searched.
	//!	@param		startindex	The start index of searching.
	//! @return		The index of the first occurrence of the substring or -1 indicates cant find.
	_dword SearchR2LLowercase( const CharType* string, _dword* startindex = _null ) const;

	//! Compare two strings
	//! @param		string		The second string object.
	//!	@param		ignorecase	True indicates case insensitive when compare.
	//! @return		True indicates it's the same string.
	_ubool Equal( const CharType* string, _ubool ignorecase ) const;
	//! Compare two strings.
	//! @param		string		The second string object.
	//!	@param		ignorecase	True indicates case insensitive when compare.
	//! @return		The lexicographic relation of two strings, -1, 0, 1.
	_int Compare( const CharType* string, _ubool ignorecase ) const;
	//! Compare		two strings with wildcards.
	//! @param		string		The second string with wildcards.
	//! @return		True if the string meets the wildcard, false otherwise.
	//!	@remarks	Wildcards must in the second string, otherwise it will be normal character.<br>
	//!				<b>'*'</b> meets zero or more character.<br>
	//!				<b>'?'</b> meets exactly one character.<br>
	//!				'*' must not adjacent with other wildcards together, otherwise will get wrong result.
	//!				For example, "Hello" will meets "He??o" or "H*o" or "*Hello".
	_ubool CompareWildcard( const CharType* string ) const;

	//!	Check whether the string is empty or not.
	//!	@param		none.
	//!	@return		True indicates it's empty string.
	_ubool IsEmpty( ) const;
	//! Determine if string is empty, or looks like blank.
	//! @param		none.
	//! @return		True if blank, false otherwise.
	_ubool IsBlank( ) const;

	//! Copy the string from another string.
	//! @param		string		Pointer to a null-terminated string.
	//!	@param		number		The number of characters to be copied, -1 indicates auto-detected.	
	//! @return		The reference of current string.
	RawString& CopyString( const CharType* string, _dword number = -1 );

	//!	Trim character from left to right.
	//!	@param		character	The character what you want to trim.
	//!	@return		The trimmed string.
	RawString& TrimLeft( CharType character );
	//!	Trim character from right to left.
	//!	@param		character	The character what you want to trim.
	//!	@return		The trimmed string.
	RawString& TrimRight( CharType character );
	//!	Trim character both left and right.
	//!	@param		character	The character what you want to trim.
	//!	@return		The trimmed string.
	RawString& TrimBoth( CharType character );

	//!	Trim substring from left to right.
	//!	@param		charset		The substring what you want to trim.
	//!	@return		The trimmed string.
	RawString& TrimLeft( const CharType* charset );
	//!	Trim substring from right to left.
	//!	@param		charset		The substring what you want to trim.
	//!	@return		The trimmed string.
	RawString& TrimRight( const CharType* charset );
	//!	Trim substring both left and right.
	//!	@param		charset		The substring what you want to trim.
	//!	@return		The trimmed string.
	RawString& TrimBoth( const CharType* charset );

	//! Format string with different number of parameter.
	template< class T1 >
	RawString& Format( const CharType* format, T1 p1 );

	template< class T1, class T2 >
	RawString& Format( const CharType* format, T1 p1, T2 p2 );

	template< class T1, class T2, class T3 >
	RawString& Format( const CharType* format, T1 p1, T2 p2, T3 p3 );

	template< class T1, class T2, class T3, class T4 >
	RawString& Format( const CharType* format, T1 p1, T2 p2, T3 p3, T4 p4 );

	template< class T1, class T2, class T3, class T4, class T5 >
	RawString& Format( const CharType* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5 );

	template< class T1, class T2, class T3, class T4, class T5, class T6 >
	RawString& Format( const CharType* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6 );

	template< class T1, class T2, class T3, class T4, class T5, class T6, class T7 >
	RawString& Format( const CharType* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7 );

	template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8 >
	RawString& Format( const CharType* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8 );
};

//----------------------------------------------------------------------------
// RawString Implementation
//----------------------------------------------------------------------------

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
RawString< CharType, _STRING_ENCODE, _SIZE >::RawString( )
{
	mString[ 0 ]			= 0;
	mString[ _SIZE - 1 ]	= 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
RawString< CharType, _STRING_ENCODE, _SIZE >::RawString( const CharType* string, _dword number )
{
	mString[ 0 ]			= 0;
	mString[ _SIZE - 1 ]	= 0;

	Platform::CopyString( mString, string, number );
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
RawString< CharType, _STRING_ENCODE, _SIZE >::~RawString( )
{
	// The tail of string must be 0, otherwise indicates the buffer is broken by out-of-range operation
	EGE_ASSERT( mString[ _SIZE - 1 ] == 0 );
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
RawString< CharType, _STRING_ENCODE, _SIZE >& RawString< CharType, _STRING_ENCODE, _SIZE >::operator = ( const CharType* string )
{
	EGE_ASSERT( string != _null );

	Platform::CopyString( mString, string );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
RawString< CharType, _STRING_ENCODE, _SIZE >& RawString< CharType, _STRING_ENCODE, _SIZE >::operator += ( CharType character )
{
	CharType string[] = { character, 0 };
	Platform::AppendString( mString, string );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
RawString< CharType, _STRING_ENCODE, _SIZE >& RawString< CharType, _STRING_ENCODE, _SIZE >::operator += ( const CharType* string )
{
	EGE_ASSERT( string != _null );

	Platform::AppendString( mString, string );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
CharType& RawString< CharType, _STRING_ENCODE, _SIZE >::operator [] ( _int index )
{
	EGE_ASSERT( index < _SIZE );

	return mString[ index ];
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
CharType& RawString< CharType, _STRING_ENCODE, _SIZE >::operator [] ( _dword index )
{
	EGE_ASSERT( index < _SIZE );

	return mString[ index ];
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
CharType RawString< CharType, _STRING_ENCODE, _SIZE >::operator [] ( _int index ) const
{
	EGE_ASSERT( index < _SIZE );

	return mString[ index ];
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
CharType RawString< CharType, _STRING_ENCODE, _SIZE >::operator [] ( _dword index ) const
{
	EGE_ASSERT( index < _SIZE );

	return mString[ index ];
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_ubool RawString< CharType, _STRING_ENCODE, _SIZE >::operator == ( const CharType* string ) const
{
	EGE_ASSERT( string != _null );

	return Platform::CompareString( mString, string ) == 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_ubool RawString< CharType, _STRING_ENCODE, _SIZE >::operator != ( const CharType* string ) const
{
	EGE_ASSERT( string != _null );

	return Platform::CompareString( mString, string ) != 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_ubool RawString< CharType, _STRING_ENCODE, _SIZE >::operator > ( const CharType* string ) const
{
	EGE_ASSERT( string != _null );

	return Platform::CompareString( mString, string ) > 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_ubool RawString< CharType, _STRING_ENCODE, _SIZE >::operator < ( const CharType* string ) const
{
	EGE_ASSERT( string != _null );

	return Platform::CompareString( mString, string ) < 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_ubool RawString< CharType, _STRING_ENCODE, _SIZE >::operator >= ( const CharType* string ) const
{
	EGE_ASSERT( string != _null );

	return Platform::CompareString( mString, string ) >= 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_ubool RawString< CharType, _STRING_ENCODE, _SIZE >::operator <= ( const CharType* string ) const
{
	EGE_ASSERT( string != _null );

	return Platform::CompareString( mString, string ) <= 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_ENCODING RawString< CharType, _STRING_ENCODE, _SIZE >::GetEncodeType( ) const
{
	return _STRING_ENCODE;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_crcvalue RawString< CharType, _STRING_ENCODE, _SIZE >::GetCRCValue( _dword flag ) const
{
	return CRC::BuildFromString( mString, flag );
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_dword RawString< CharType, _STRING_ENCODE, _SIZE >::GetLength( ) const
{
	return Platform::StringLength( mString );
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_dword RawString< CharType, _STRING_ENCODE, _SIZE >::SizeOfBytes( ) const
{
	return ( Platform::StringLength( mString ) + 1 ) * sizeof( CharType );
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_void RawString< CharType, _STRING_ENCODE, _SIZE >::Insert( _dword index, CharType character )
{
	EGE_ASSERT( index < _SIZE );

	// Get the string length
	_dword length = GetLength( );
	EGE_ASSERT( index > length );

	// Check the total string length, make sure it's in the range
	EGE_ASSERT( length + 1 < _SIZE );

	// Move backwards
	for ( _dword i = length + 1; i > index; i -- )
		mString[ i ] = mString[ i - 1 ];

	// Insert the character
	mString[ index ] = character;

	// The tail of string must be 0, otherwise indicates the buffer is broken by out-of-range operation
	EGE_ASSERT( mString[ _SIZE - 1 ] == 0 );
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_void RawString< CharType, _STRING_ENCODE, _SIZE >::Insert( _dword index, const CharType* string )
{
	EGE_ASSERT( index < _SIZE );

	// Get the length of insert string
	_dword insert_length = Platform::StringLength( string );

	// Get the string length
	_dword length = GetLength( );
	EGE_ASSERT( index > length );

	// Check the total string length, make sure it's in the range
	EGE_ASSERT( length + insert_length < _SIZE );

	// Move backwards
	for ( _dword i = length + insert_length; i > index; i -- )
		mString[ i ] = mString[ i - 1 - insert_length ];

	// Insert the character
	EGE_MEM_CPY( mString, string, insert_length );

	// The tail of string must be 0, otherwise indicates the buffer is broken by out-of-range operation
	EGE_ASSERT( mString[ _SIZE - 1 ] == 0 );
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
const CharType* RawString< CharType, _STRING_ENCODE, _SIZE >::Str( ) const
{
	return mString;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
const CharType* RawString< CharType, _STRING_ENCODE, _SIZE >::SubString( _dword index ) const
{
	EGE_ASSERT( index < _SIZE );

	return mString + index;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_ubool RawString< CharType, _STRING_ENCODE, _SIZE >::StartsWith( const CharType* string ) const
{
	EGE_ASSERT( string != _null );

	return Platform::SearchL2R( mString, string, _null ) == 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_dword RawString< CharType, _STRING_ENCODE, _SIZE >::SearchL2R( CharType character ) const
{
	return Platform::SearchL2R( mString, character );
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_dword RawString< CharType, _STRING_ENCODE, _SIZE >::SearchL2RLowercase( CharType character ) const
{
	return Platform::SearchL2R( mString, character, _true );
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_dword RawString< CharType, _STRING_ENCODE, _SIZE >::SearchR2L( CharType character ) const
{
	return Platform::SearchR2L( mString, character );
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_dword RawString< CharType, _STRING_ENCODE, _SIZE >::SearchR2LLowercase( CharType character ) const
{
	return Platform::SearchR2L( mString, character, _true );
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_dword RawString< CharType, _STRING_ENCODE, _SIZE >::SearchL2R( const CharType* string, _dword* endindex ) const
{
	EGE_ASSERT( string != _null );

	return Platform::SearchL2R( mString, string, endindex );
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_dword RawString< CharType, _STRING_ENCODE, _SIZE >::SearchL2RLowercase( const CharType* string, _dword* endindex ) const
{
	EGE_ASSERT( string != _null );

	return Platform::SearchL2R( mString, string, _true, endindex );
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_dword RawString< CharType, _STRING_ENCODE, _SIZE >::SearchR2L( const CharType* string, _dword* startindex ) const
{
	EGE_ASSERT( string != _null );

	return Platform::SearchR2L( mString, string, startindex );
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_dword RawString< CharType, _STRING_ENCODE, _SIZE >::SearchR2LLowercase( const CharType* string, _dword* startindex ) const
{
	EGE_ASSERT( string != _null );

	return Platform::SearchR2L( mString, string, _true, startindex );
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_ubool RawString< CharType, _STRING_ENCODE, _SIZE >::Equal( const CharType* string, _ubool ignorecase ) const
{
	EGE_ASSERT( string != _null );

	return Compare( string, ignorecase ) == 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_int RawString< CharType, _STRING_ENCODE, _SIZE >::Compare( const CharType* string, _ubool ignorecase ) const
{
	EGE_ASSERT( string != _null );

	return Platform::CompareString( mString, string, ignorecase );
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_ubool RawString< CharType, _STRING_ENCODE, _SIZE >::CompareWildcard( const CharType* string ) const
{
	EGE_ASSERT( string != _null );

	return Platform::CompareWildcard( mString, string );
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_ubool RawString< CharType, _STRING_ENCODE, _SIZE >::IsEmpty( ) const
{
	return mString[0] == 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
_ubool RawString< CharType, _STRING_ENCODE, _SIZE >::IsBlank( ) const
{
	return Platform::IsBlank( mString );
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
RawString< CharType, _STRING_ENCODE, _SIZE >& RawString< CharType, _STRING_ENCODE, _SIZE >::CopyString( const CharType* string, _dword number )
{
	Platform::CopyString( mString, string, number );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
RawString< CharType, _STRING_ENCODE, _SIZE >& RawString< CharType, _STRING_ENCODE, _SIZE >::TrimLeft( CharType character )
{
	_dword length = GetLength( );

	Platform::TrimStringLeft( mString, length, character );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
RawString< CharType, _STRING_ENCODE, _SIZE >& RawString< CharType, _STRING_ENCODE, _SIZE >::TrimRight( CharType character )
{
	_dword length = GetLength( );

	Platform::TrimStringRight( mString, length, character );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
RawString< CharType, _STRING_ENCODE, _SIZE >& RawString< CharType, _STRING_ENCODE, _SIZE >::TrimBoth( CharType character )
{
	_dword length = GetLength( );

	Platform::TrimStringBoth( mString, length, character );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
RawString< CharType, _STRING_ENCODE, _SIZE >& RawString< CharType, _STRING_ENCODE, _SIZE >::TrimLeft( const CharType* charset )
{
	_dword length = GetLength( );

	Platform::TrimStringLeft( mString, length, charset );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
RawString< CharType, _STRING_ENCODE, _SIZE >& RawString< CharType, _STRING_ENCODE, _SIZE >::TrimRight( const CharType* charset )
{
	_dword length = GetLength( );

	Platform::TrimStringRight( mString, length, charset );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
RawString< CharType, _STRING_ENCODE, _SIZE >& RawString< CharType, _STRING_ENCODE, _SIZE >::TrimBoth( const CharType* charset )
{
	_dword length = GetLength( );

	Platform::TrimStringBoth( mString, length, charset );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
template< class T1 >
RawString< CharType, _STRING_ENCODE, _SIZE >& RawString< CharType, _STRING_ENCODE, _SIZE >::Format( const CharType* format, T1 p1 )
{
	Platform::FormatStringBuffer( mString, _SIZE, format, p1 );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
template< class T1, class T2 >
RawString< CharType, _STRING_ENCODE, _SIZE >& RawString< CharType, _STRING_ENCODE, _SIZE >::Format( const CharType* format, T1 p1, T2 p2 )
{
	Platform::FormatStringBuffer( mString, _SIZE, format, p1, p2 );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
template< class T1, class T2, class T3 >
RawString< CharType, _STRING_ENCODE, _SIZE >& RawString< CharType, _STRING_ENCODE, _SIZE >::Format( const CharType* format, T1 p1, T2 p2, T3 p3 )
{
	Platform::FormatStringBuffer( mString, _SIZE, format, p1, p2, p3 );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
template< class T1, class T2, class T3, class T4 >
RawString< CharType, _STRING_ENCODE, _SIZE >& RawString< CharType, _STRING_ENCODE, _SIZE >::Format( const CharType* format, T1 p1, T2 p2, T3 p3, T4 p4 )
{
	Platform::FormatStringBuffer( mString, _SIZE, format, p1, p2, p3, p4 );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
template< class T1, class T2, class T3, class T4, class T5 >
RawString< CharType, _STRING_ENCODE, _SIZE >& RawString< CharType, _STRING_ENCODE, _SIZE >::Format( const CharType* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5 )
{
	Platform::FormatStringBuffer( mString, _SIZE, format, p1, p2, p3, p4, p5 );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
template< class T1, class T2, class T3, class T4, class T5, class T6 >
RawString< CharType, _STRING_ENCODE, _SIZE >& RawString< CharType, _STRING_ENCODE, _SIZE >::Format( const CharType* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6 )
{
	Platform::FormatStringBuffer( mString, _SIZE, format, p1, p2, p3, p4, p5, p6 );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
template< class T1, class T2, class T3, class T4, class T5, class T6, class T7 >
RawString< CharType, _STRING_ENCODE, _SIZE >& RawString< CharType, _STRING_ENCODE, _SIZE >::Format( const CharType* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7 )
{
	Platform::FormatStringBuffer( mString, _SIZE, format, p1, p2, p3, p4, p5, p6, p7 );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE, _dword _SIZE >
template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8 >
RawString< CharType, _STRING_ENCODE, _SIZE >& RawString< CharType, _STRING_ENCODE, _SIZE >::Format( const CharType* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8 )
{
	Platform::FormatStringBuffer( mString, _SIZE, format, p1, p2, p3, p4, p5, p6, p7, p8 );

	return *this;
}

}