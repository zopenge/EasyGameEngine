//! @file     MutableString.h
//! @author   LiCode
//! @version  1.0.1.804
//! @date     2011/03/10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// MutableString
//----------------------------------------------------------------------------

//! This class represents a mutable null-terminated string.
template< typename CharType, _ENCODING _STRING_ENCODE >
class MutableString : public ConstString< CharType, _STRING_ENCODE >
{
protected:
	typedef ConstString< CharType, _STRING_ENCODE > TBaseClass;
	typedef ConstString< CharType, _STRING_ENCODE > _StringPtr;

protected:
	//!	The string length
	_dword	mLength;
	//!	The string buffer size in (Type) mode
	_dword	mSize;

protected:
	//!	Create string buffer.
	//!	@param		string		If we provide the string buffer then copy it when create string buffer finished.
	//!	@return		none.
	_void CreateStringBuffer( const CharType* string = _null );
	//!	Copy string buffer.
	//!	@param		string		The source string buffer.
	//!	@return		none.
	_void CopyStringBuffer( const CharType* string );

	//!	Append string buffer.
	//!	@param		string		The string buffer.
	//!	@param		length		The string length.
	//!	@return		none.
	_void AppendStringBuffer( const CharType* string, _dword length );

	//!	Format string.
	//!	@param		format		The format of string.
	//!	@param		...			The optional arguments.
	//! @return		none.
	_void FormatStringByArguments( const CharType* format, ... );
	//!	Format string.
	//!	@param		format		The format of string.
	//!	@param		arguments	The optional arguments.
	//! @return		none.
	_void FormatStringByVAList( const CharType* format, _va_list arguments );
	 
public:
	//! Constructor, create a string only contains the terminal null.
	//! @param		none
	MutableString( );
	//! Copy-Constructor, create a string by copy another string.
	//! @param		string	The string.
	MutableString( const CharType* string );
	//! Copy-Constructor, create a string by copy another string object.
	//! @param		string	The second string object.
	MutableString( _StringPtr string );
	//! Copy-Constructor, create a string by copy another string object.
	//! @param		string	The second string object.
	MutableString( const MutableString& string );
	//! Constructor, create a string by copy some characters from another string.
	//! @param		string		Pointer to a null-terminated string.
	//! @param		number		The number of characters to be copy.
	MutableString( const CharType* string, _dword number );
	//! Constructor, create a string by character.
	//! @param		char_code	The character code.
	MutableString( CharType char_code );
	//! Destructor, delete the memory of the string.
	//! @param		none
	~MutableString( );

public:
	//!	Convert to const null-terminated string.
	//!	@param		none.
	//!	@return		The const null-terminated string.
	operator _StringPtr ( ) const;

	//! Copy the string from character, and recreates memory to hold it.
	//! @param		character	The character.
	//! @return		The reference of current string.
	MutableString& operator = ( CharType character );
	//! Copy the string from another one, and recreates memory to hold it.
	//! @param		string		Pointer to a null-terminated string.
	//! @return		The reference of current string.
	MutableString& operator = ( const CharType* string );
	//! Copy the string from another one, and recreates memory to hold it.
	//! @param		string		The string object.
	//! @return		The reference of current string.
	MutableString& operator = ( const MutableString& string );

	//! Append a character to the end of the string.
	//! @param		character	The character to be append.
	//! @return		The reference of current string.
	MutableString& operator += ( CharType character );
	//! Append another string to the end of the current one.
	//! @param		string		Pointer to a null-terminated string.
	//! @return		The reference of current string.
	MutableString& operator += ( const CharType* string );
	//! Append another string to the end of the current one.
	//! @param		string		Pointer to a null-terminated string.
	//! @return		The reference of current string.
	MutableString& operator += ( const MutableString& string );

	//! Get a character from string by index.
	//! @param		index		The index of the character in string.
	//! @return		A character specified by index
	template< typename IndexType >
	CharType& operator [] ( IndexType index );
	//! Get a character from string by index.
	//! @param		index		The index of the character in string.
	//! @return		A character specified by index
	template< typename IndexType >
	const CharType& operator [] ( IndexType index ) const;

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
	_ubool operator == ( const MutableString& string ) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if two strings are not same, false otherwise.
	_ubool operator != ( const MutableString& string ) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if the first string is greater than the second one, false otherwise.
	_ubool operator > ( const MutableString& string ) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if the first string is less than the second one, false otherwise.
	_ubool operator < ( const MutableString& string ) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if the first string is greater or equal than the second one, false otherwise.
	_ubool operator >= ( const MutableString& string ) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if the first string is less or equal than the second one, false otherwise.
	_ubool operator <= ( const MutableString& string ) const;

public:
	//! Get the length of the string, excluding the terminal null, overwrite parent class function.
	//! @param		none
	//! @return		The Length of the string.
	_dword GetLength( ) const;
	//! Get the size of the string.
	//! @param		none
	//! @return		The size of the string.
	_dword GetSize( ) const;
	//! Get the number of bytes used by string, include the terminal null, overwrite parent class function.
	//! @param		none
	//! @return		The number of bytes used by string.
	_dword SizeOfBytes( ) const;

	//!	Resize.
	//!	@param		size		The length of string, including the terminal null.
	//!	@none.
	_void Resize( _dword size );
	//!	Clear.
	//! @param		freememory	True indicates free the memory used by string.
	//!	@return		none.
	_void Clear( _ubool freememory = _false );
	//!	Reduce capacity.
	//!	@param		none.
	//!	@return		none.
	_void ShrinkToFit( );

	//! Insert a character into the index of the string.
	//! @param		index		The index of the string
	//! @param		character	The character to be inserted.
	//! @remark		The character will be inserted before the index.<br>
	//!				For example, "Hello".Insert( 0, 'W' ) will results "WHello",
	//!				and "Hello".Insert( 5, 'W' ) will results "HelloW".
	_void Insert( _dword index, CharType character );
	//! Insert a substring into the index of the string.
	//! @param		index		The index of the string.
	//! @param		string		The substring to be inserted.
	//! @remark		The substring will be inserted before the index.<br>
	//!				For example, "Hello".Insert( 0, "World" ) will results "WorldHello",
	//!				and "Hello".Insert( 5, "World" ) will results "HelloWorld".
	_void Insert( _dword index, const _StringPtr& string );
	//! Remove some characters at the index of the string.
	//! @param		index		The index of the string.
	//! @param		number		The number of characters to be removed.
	//! @remark		The character will be removed start from the index.<br>
	//!				For example, "Hello".Remove( 0, 2 ) will results "llo",
	//!				"Hello".Remove( 4, 1 ) will results "Hell",
	//!				and "Hello".Remove( 4, 2 ) will failed ( return false ).
	_void Remove( _dword index, _dword number = -1 );
	//! Remove some characters by range.
	//! @param		start_index	The start index of the string.
	//! @param		end_index	The end index of the string.
	_void RemoveByRange( _dword start_index, _dword end_index );

	_void RemoveChar( CharType character );
	//! Search and replace a substring to another.
	//! @param		srcstring	The substring to be searched.
	//! @param		desstring	The substring to be replaced.
	//! @return		True if successfully searched & replaced, false otherwise.
	_ubool Replace( _StringPtr srcstring, _StringPtr desstring );
	//! Search and replace a character to another one.
	//! @param		index		The index of character to be replaced.
	//! @param		character	The character to be used.
	//! @return		True if successfully searched & replaced, false otherwise.
	_ubool Replace( _dword index, CharType character );
	//! Search and replace a character to another one.
	//! @param		index		The index of character to be replaced.
	//! @param		number		The number for character to be replaced.
	//! @param		character	The character to be used.
	//! @return		True if successfully searched & replaced, false otherwise.
	_ubool Replace( _dword index, _dword number, CharType character );
	//! Search and replace all character to another.
	//!	@param		oldchar		The old character.
	//!	@param		newchar		The new character.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//! @return		True if successfully searched & replaced, false otherwise.
	_ubool ReplaceAll( CharType oldchar, CharType newchar, _ubool ignorecase = _false );
	//! Search and replace all substring to another.
	//! @param		srcstring	The substring to be searched.
	//! @param		desstring	The substring to be replaced.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//! @return		True if successfully searched & replaced, false otherwise.
	_ubool ReplaceAll( _StringPtr srcstring, _StringPtr desstring, _ubool ignorecase = _false );

	//! Copy the string from another string, and recreates memory to hold it.
	//! @param		string		Pointer to a null-terminated string.
	//! @param		length		The length of string.
	//! @return		The reference of current string.
	MutableString& CopyString( const CharType* string, _dword length = -1 );

	//! Convert the string to lowercase.
	//! @return		The pointer of the string with lowercase.
	MutableString& Lowercase( );
	//! Convert the string to uppercase.
	//! @return		The pointer of the string with uppercase.
	MutableString& Uppercase( );

	//!	Trim character from left to right.
	//!	@param		character	The character what you want to trim.
	//!	@return		The trimmed string.
	MutableString& TrimLeft( CharType character );
	//!	Trim character from right to left.
	//!	@param		character	The character what you want to trim.
	//!	@return		The trimmed string.
	MutableString& TrimRight( CharType character );
	//!	Trim character both left and right.
	//!	@param		character	The character what you want to trim.
	//!	@return		The trimmed string.
	MutableString& TrimBoth( CharType character );

	//!	Trim substring from left to right.
	//!	@param		charset		The substring what you want to trim.
	//!	@return		The trimmed string.
	MutableString& TrimLeft( _StringPtr charset );
	//!	Trim substring from right to left.
	//!	@param		charset		The substring what you want to trim.
	//!	@return		The trimmed string.
	MutableString& TrimRight( _StringPtr charset );
	//!	Trim substring both left and right.
	//!	@param		charset		The substring what you want to trim.
	//!	@return		The trimmed string.
	MutableString& TrimBoth( _StringPtr charset );

	//! Get the substring start from a index.
	//! @param		index		The index of the string, must be less or equal than the length of the string.
	//! @return		The substring from the index.
	_StringPtr SubString( _dword index ) const;
	//! Get the substring start from a index.
	//! @param		start		The index of the string, must be less or equal than the length of the string.
	//! @return		The substring from the index.
	MutableString SubString( _dword start, _dword length ) const;

	//! Get the substring from left to right.
	//! @param		delimiter	The delimiter character what substring will be end there.
	//! @return		The substring.
	MutableString LeftSubString( CharType delimiter ) const;
	//! Get the substring from left to right.
	//! @param		delimiter	The delimiter string what substring will be end there.
	//! @return		The substring.
	MutableString LeftSubString( _StringPtr delimiter ) const;
	//! Get the substring from right to left. 
	//! @param		delimiter	The delimiter character what substring will be end there.
	//! @return		The substring.
	MutableString RightSubString( CharType delimiter ) const;
	//! Get the substring from right to left.
	//! @param		delimiter	The delimiter string what substring will be end there.
	//! @return		The substring.
	MutableString RightSubString( _StringPtr delimiter ) const;

	//! Remove the file extension from the full path.
	//! @param		none.
	//! @return		True indicates remove it successful.
	_ubool RemoveExtension( );

	//! Copy from signed value.
	//! @param		value		The integer value.
	//! @param		radix		The base of value, which must be in the range 2每36.
	//! @return		The referenced string.
	MutableString& FromValue( _int value, _dword radix = 10 );
	//! Copy from unsigned value.
	//! @param		value		The integer value.
	//! @param		radix		The base of value, which must be in the range 2每36.
	//! @return		The referenced string.
	MutableString& FromValue( _dword value, _dword radix = 10 );
	//! Copy from 64-bits unsigned value.
	//! @param		value		The integer value.
	//! @param		radix		The base of value, which must be in the range 2每36.
	//! @return		The referenced string.
	MutableString& FromValue( _large value, _dword radix = 10 );
	//! Copy from 64-bits unsigned value.
	//! @param		value		The integer value.
	//! @param		radix		The base of value, which must be in the range 2每36.
	//! @return		The referenced string.
	MutableString& FromValue( _qword value, _dword radix = 10 );
	//! Copy from float value.
	//! @param		value		The float value.
	//! @param		precision	The floating point precision after decimal point.
	//! @return		The referenced string.
	MutableString& FromValue( _float value, _dword precision = 6 );
	//! Copy from double value.
	//! @param		value		The double value.
	//! @param		precision	The floating point precision after decimal point.
	//! @return		The referenced string.
	MutableString& FromValue( _double value, _dword precision = 15 );

	//! Copy from another string ( auto convert encode type ).
	//! @param		string		The another string object.
	//! @return		The referenced string.
	template< class FromStringType >
	MutableString& FromString( const FromStringType& string );
	//! Copy from another string ( auto convert encode type ).
	//! @param		encode		The another string encode type.
	//! @param		string		The another string pointer.
	//! @return		The referenced string.
	template< typename FromCharType >
	MutableString& FromString( _ENCODING encode, const FromCharType* string );

	//!	Format string to bytes style.
	//! @param		bytes		The total bytes.
	//! @return		The referenced string.
	MutableString& FormatBytes( _qword bytes );
	//!	Format string to currency style.
	//! @param		currency	The currency.
	//! @return		The referenced string.
	MutableString& FormatCurrency( _qword currency );
	//!	Format string to time style.
	//! @param		millisecond	The millisecond.
	//! @return		The referenced string.
	MutableString& FormatTime( _qword millisecond );

	//! Format string with different number of parameter.
	template< class T1 >
	MutableString& Format( const _StringPtr& format, const T1& p1 );

	template< class T1, class T2 >
	MutableString& Format( const _StringPtr& format, const T1& p1, const T2& p2 );

	template< class T1, class T2, class T3 >
	MutableString& Format( const _StringPtr& format, const T1& p1, const T2& p2, const T3& p3 );

	template< class T1, class T2, class T3, class T4 >
	MutableString& Format( const _StringPtr& format, const T1& p1, const T2& p2, const T3& p3, const T4& p4 );

	template< class T1, class T2, class T3, class T4, class T5 >
	MutableString& Format( const _StringPtr& format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5 );

	template< class T1, class T2, class T3, class T4, class T5, class T6 >
	MutableString& Format( const _StringPtr& format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6 );

	template< class T1, class T2, class T3, class T4, class T5, class T6, class T7 >
	MutableString& Format( const _StringPtr& format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7 );

	template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8 >
	MutableString& Format( const _StringPtr& format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8 );

	template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9 >
	MutableString& Format( const _StringPtr& format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8, const T9& p9 );

	template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10 >
	MutableString& Format( const _StringPtr& format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8, const T9& p9, const T10& p10 );

	template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11 >
	MutableString& Format( const _StringPtr& format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8, const T9& p9, const T10& p10, const T11& p11 );

	template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12 >
	MutableString& Format( const _StringPtr& format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8, const T9& p9, const T10& p10, const T11& p11, const T12& p12 );

	template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13 >
	MutableString& Format( const _StringPtr& format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8, const T9& p9, const T10& p10, const T11& p11, const T12& p12, const T13& p13 );

	//! Format string with different number of parameter.
	template< class T1 >
	MutableString& Format( const CharType* format, const T1& p1 );

	template< class T1, class T2 >
	MutableString& Format( const CharType* format, const T1& p1, const T2& p2 );

	template< class T1, class T2, class T3 >
	MutableString& Format( const CharType* format, const T1& p1, const T2& p2, const T3& p3 );

	template< class T1, class T2, class T3, class T4 >
	MutableString& Format( const CharType* format, const T1& p1, const T2& p2, const T3& p3, const T4& p4 );

	template< class T1, class T2, class T3, class T4, class T5 >
	MutableString& Format( const CharType* format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5 );

	template< class T1, class T2, class T3, class T4, class T5, class T6 >
	MutableString& Format( const CharType* format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6 );

	template< class T1, class T2, class T3, class T4, class T5, class T6, class T7 >
	MutableString& Format( const CharType* format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7 );

	template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8 >
	MutableString& Format( const CharType* format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8 );

	template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9 >
	MutableString& Format( const CharType* format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8, const T9& p9 );

	template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10 >
	MutableString& Format( const CharType* format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8, const T9& p9, const T10& p10 );

	template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11 >
	MutableString& Format( const CharType* format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8, const T9& p9, const T10& p10, const T11& p11 );

	template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12 >
	MutableString& Format( const CharType* format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8, const T9& p9, const T10& p10, const T11& p11, const T12& p12 );

	template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13 >
	MutableString& Format( const CharType* format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8, const T9& p9, const T10& p10, const T11& p11, const T12& p12, const T13& p13 );
};

//----------------------------------------------------------------------------
// MutableString Implementation
//----------------------------------------------------------------------------

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >::MutableString( )
{
	mLength	= 0;
	mSize	= 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >::MutableString( const CharType* string )
{
	if ( string == _null || *string == 0 )
	{
		mLength	= 0;
		mSize	= 0;
	}
	else
	{
		// Get the string length
		mLength	= Platform::StringLength( string );

		// Create and copy the string buffer
		CreateStringBuffer( string );
	}
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >::MutableString( _StringPtr string )
{
	if ( string.IsEmpty( ) )
	{
		mLength	= 0;
		mSize	= 0;
	}
	else
	{
		// Get the string length
		mLength	= string.GetLength( );

		// Create and copy the string buffer
		CreateStringBuffer( string.Str( ) );
	}
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >::MutableString( const MutableString& string )
{
	if ( string.IsEmpty( ) )
	{
		mLength	= 0;
		mSize	= 0;
	}
	else
	{
		// Get the string length
		mLength	= string.GetLength( );

		// Create and copy the string buffer
		CreateStringBuffer( string.Str( ) );
	}
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >::MutableString( const CharType* string, _dword number )
{
	if ( string == _null || *string == 0 )
	{
		mLength	= 0;
		mSize	= 0;
	}
	else
	{
		// Get the string length
		if ( number == -1 )
			mLength	= Platform::StringLength( string );
		else
			mLength	= number;

		// Create and copy the string buffer
		CreateStringBuffer( string );
	}
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >::MutableString( CharType char_code )
{
	if ( char_code == 0 )
	{
		mLength	= 0;
		mSize	= 0;
	}
	else
	{
		mLength			= 1;
		mSize			= mLength + 1;
		this->mString	= new CharType[ mSize ];

		// Copy string
		this->mString[ 0 ]			= char_code;
		this->mString[ mLength ]	= 0;
	}	
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >::~MutableString( )
{
	Clear( _true );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_void MutableString< CharType, _STRING_ENCODE >::CreateStringBuffer( const CharType* string )
{
	// Create string buffer
	mSize			= mLength + 1;
	this->mString	= new CharType[ mSize ];

	// Copy string
	if ( string != _null )
		CopyStringBuffer( string );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_void MutableString< CharType, _STRING_ENCODE >::CopyStringBuffer( const CharType* string )
{
	// Copy string
	EGE_MEM_CPY( this->mString, string, mLength * sizeof( CharType ) );

	// Set null-terminated
	this->mString[ mLength ] = 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_void MutableString< CharType, _STRING_ENCODE >::AppendStringBuffer( const CharType* string, _dword length )
{
	// Get the string length
	_dword length1 = mLength;
	_dword length2 = length;

	// Get the total string length
	mLength = length1 + length2;

	// Create more memory if necessary
	if ( mSize < mLength + 1 )
	{
		CharType*	oldstring = this->mString;
		_ubool		olddelete = mSize > 0;

		// Create new memory to save both string
		mSize			= mLength + 1;
		this->mString	= new CharType[ mSize ];

		// Copy old string back to buffer
		EGE_MEM_CPY( this->mString, oldstring, length1 * sizeof( CharType ) );

		// Delete the old memory
		if ( olddelete )
		{
			delete[] oldstring;
		}
	}

	// Append new string
	EGE_MEM_CPY( this->mString + length1, string, length2 * sizeof( CharType ) );

	// Set null-terminated
	this->mString[ mLength ] = 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_void MutableString< CharType, _STRING_ENCODE >::FormatStringByArguments( const CharType* format, ... )
{
	BEGIN_VA_LIST( args, format );
		FormatStringByVAList( format, args );
	END_VA_LIST( args );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_void MutableString< CharType, _STRING_ENCODE >::FormatStringByVAList( const CharType* format, _va_list arguments )
{
	mLength = Platform::GetFormatStringLength( format, arguments );

	// Create more memory if necessary
	if ( mSize < mLength + 1 )
	{
		CharType*	oldstring = this->mString;
		_ubool		olddelete = mSize > 0;

		// Create new memory to save both string
		mSize			= mLength + 1;
		this->mString	= new CharType[ mSize ];

		// Delete the old memory
		if ( olddelete )
		{
			delete[] oldstring;
		}
	}

	// Format string
	Platform::FormatStringByVAList( this->mString, mSize, format, arguments );

	// Set null-terminated
	this->mString[ mLength ] = 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >::operator _StringPtr ( ) const
{
	return _StringPtr( this->mString );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::operator = ( CharType character )
{
	CharType string[] = { character, 0 };
	return operator = ( string );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::operator = ( const CharType* string )
{
	// Get the string length
	mLength = Platform::StringLength( string );

	// It's empty string
	if ( mLength == 0 )
	{
		if ( mSize > 0 )
			this->mString[0] = 0;
	}
	// Create more memory if necessary
	else if ( mSize < mLength + 1 )
	{
		// Free the old string buffer
		if ( mSize > 0 )
		{
			delete[] this->mString;
		}

		// Create and copy the string buffer
		CreateStringBuffer( string );
	}
	else
	{
		// Copy the string buffer
		CopyStringBuffer( string );
	}

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::operator = ( const MutableString& string )
{
	// Get the string length
	mLength = string.GetLength( );

	// It's empty string
	if ( mLength == 0 )
	{
		if ( mSize > 0 )
			this->mString[0] = 0;
	}
	// Create more memory if necessary
	else if ( mSize < mLength + 1 )
	{
		// Free the old string buffer
		if ( mSize > 0 )
		{
			delete[] this->mString;
		}

		// Create and copy the string buffer
		CreateStringBuffer( string.Str( ) );
	}
	else
	{
		// Copy the string buffer
		CopyStringBuffer( string.Str( ) );
	}

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::operator += ( CharType character )
{
	if ( character == 0 )
		return *this;

	_dword oldlength = mLength;

	// Increase the string length
	mLength ++;

	// Create more memory if necessary.
	if ( mSize < mLength + 1 )
	{
		CharType*	oldstring = this->mString;
		_ubool		olddelete = mSize > 0;

		// Create new memory to save both string
		mSize			= mLength + 1;
		this->mString	= new CharType[ mSize ];

		// Copy old string back to buffer
		EGE_MEM_CPY( this->mString, oldstring, oldlength * sizeof( CharType ) );

		// Delete the old memory
		if ( olddelete )
		{
			delete[] oldstring;
		}
	}

	// Append character
	this->mString[ oldlength ] = character;

	// Set null-terminated
	this->mString[ mLength ] = 0;

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::operator += ( const CharType* string )
{
	if ( string == _null || *string == 0 )
		return *this;

	AppendStringBuffer( string, Platform::StringLength( string ) );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::operator += ( const MutableString& string )
{
	if ( string.IsEmpty( ) )
		return *this;

	AppendStringBuffer( string.Str( ), string.GetLength( ) );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< typename IndexType >
CharType& MutableString< CharType, _STRING_ENCODE >::operator [] ( IndexType index )
{
	return this->mString[ index ];
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< typename IndexType >
const CharType& MutableString< CharType, _STRING_ENCODE >::operator [] ( IndexType index ) const
{
	return this->mString[ index ];
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableString< CharType, _STRING_ENCODE >::operator == ( const CharType* string ) const
{
	return Platform::CompareString( this->mString, string ) == 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableString< CharType, _STRING_ENCODE >::operator != ( const CharType* string ) const
{
	return Platform::CompareString( this->mString, string ) != 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableString< CharType, _STRING_ENCODE >::operator > ( const CharType* string ) const
{
	return Platform::CompareString( this->mString, string ) > 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableString< CharType, _STRING_ENCODE >::operator < ( const CharType* string ) const
{
	return Platform::CompareString( this->mString, string ) < 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableString< CharType, _STRING_ENCODE >::operator >= ( const CharType* string ) const
{
	return Platform::CompareString( this->mString, string ) >= 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableString< CharType, _STRING_ENCODE >::operator <= ( const CharType* string ) const
{
	return Platform::CompareString( this->mString, string ) <= 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableString< CharType, _STRING_ENCODE >::operator == ( const MutableString& string ) const
{
	if ( mLength != string.GetLength( ) )
		return _false;

	return Platform::CompareString( this->mString, string.Str( ) ) == 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableString< CharType, _STRING_ENCODE >::operator != ( const MutableString& string ) const
{
	if ( mLength != string.GetLength( ) )
		return _true;

	return Platform::CompareString( this->mString, string.Str( ) ) != 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableString< CharType, _STRING_ENCODE >::operator > ( const MutableString& string ) const
{
	return Platform::CompareString( this->mString, string.Str( ) ) > 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableString< CharType, _STRING_ENCODE >::operator < ( const MutableString& string ) const
{
	return Platform::CompareString( this->mString, string.Str( ) ) < 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableString< CharType, _STRING_ENCODE >::operator >= ( const MutableString& string ) const
{
	return Platform::CompareString( this->mString, string.Str( ) ) >= 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableString< CharType, _STRING_ENCODE >::operator <= ( const MutableString& string ) const
{
	return Platform::CompareString( this->mString, string.Str( ) ) <= 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_dword MutableString< CharType, _STRING_ENCODE >::GetLength( ) const
{
	return mLength;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_dword MutableString< CharType, _STRING_ENCODE >::GetSize( ) const
{
	return mSize;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_dword MutableString< CharType, _STRING_ENCODE >::SizeOfBytes( ) const
{
	return ( mLength + 1 ) * sizeof( CharType );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_void MutableString< CharType, _STRING_ENCODE >::Resize( _dword size )
{
	// Free string buffer
	if ( size == 0 )
	{
		Clear( _true );
	}
	// Create string buffer
	else if ( mSize == 0 )
	{
		// Create new memory to save string
		mSize			= size;
		this->mString	= new CharType[ mSize ];

		// Set the null-terminated character
		this->mString[ mLength ] = 0;
	}
	// Grow the string buffer size
	else if ( mSize < size )
	{
		CharType*	oldstring = this->mString;
		_ubool		olddelete = mSize > 0;

		// Create new memory to save both string
		mSize			= size;
		this->mString	= new CharType[ mSize ];

		// Copy old string back to buffer
		if ( oldstring != _null && oldstring[0] != 0 )
			EGE_MEM_CPY( this->mString, oldstring, mLength * sizeof( CharType ) );

		// Delete the old memory
		if ( olddelete )
		{
			delete[] oldstring;
		}

		// Set the null-terminated character
		this->mString[ mLength ] = 0;
	}
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_void MutableString< CharType, _STRING_ENCODE >::Clear( _ubool freememory )
{
	mLength = 0;

	// Not allocated any string buffer
	if ( mSize == 0 )
	{
		TBaseClass::Clear( );
	}
	// Free the string buffer
	else if ( freememory )
	{
		if ( mSize > 0 )
		{
			delete[] this->mString;
			mSize = 0;
		}

		TBaseClass::Clear( );
	}
	// Not free the string buffer
	else
	{
		this->mString[0] = 0;
	}
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_void MutableString< CharType, _STRING_ENCODE >::ShrinkToFit( )
{
	if ( mLength < mSize - 1 )
	{
		CharType* oldstring = this->mString;
		EGE_ASSERT( oldstring != _null );

		// Check whether need to delete old string buffer
		_ubool olddelete = mSize > 0;

		// Create new memory to save both string
		mSize = mLength + 1;
		this->mString = new CharType[mSize];

		// Copy old string back to buffer
		EGE_MEM_CPY( this->mString, oldstring, mLength * sizeof( CharType ) );

		// Delete the old memory
		if ( olddelete )
			delete[] oldstring;

		// Set the null-terminated character
		this->mString[mLength] = 0;
	}
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_void MutableString< CharType, _STRING_ENCODE >::Insert( _dword index, CharType character )
{
	EGE_ASSERT( index <= mLength );

	_dword oldlength = mLength;

	// Increase the string length
	mLength ++;

	// Create more memory if necessary
	if ( mSize < mLength + 1 )
	{
		CharType*	oldstring = this->mString;
		_ubool		olddelete = mSize > 0;

		// Create new memory to save both string
		mSize			= mLength + 1;
		this->mString	= new CharType[ mSize ];

		// Copy old string back to buffer
		EGE_MEM_CPY( this->mString, oldstring, index * sizeof( CharType ) );
		EGE_MEM_CPY( this->mString + index + 1, oldstring + index, ( oldlength - index ) * sizeof( CharType ) );

		// Delete the old memory
		if ( olddelete )
		{
			delete[] oldstring;
		}
	}
	else
	{
		for ( _dword i = index; i < oldlength; i ++ )
			this->mString[ mLength - i + index - 1 ] = this->mString[ oldlength - i + index - 1 ];
	}

	// Insert character
	this->mString[ index ] = character;

	// Set null-terminated
	this->mString[ mLength ] = 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_void MutableString< CharType, _STRING_ENCODE >::Insert( _dword index, const _StringPtr& string )
{
	EGE_ASSERT( index <= mLength );

	// Get the string length
	_dword length1 = mLength;
	_dword length2 = Platform::StringLength( string.Str( ) );

	// Get the total string length
	mLength = length1 + length2;

	// Create more memory if necessary
	if ( mSize < mLength + 1 )
	{
		CharType*	oldstring = this->mString;
		_ubool		olddelete = mSize > 0;

		// Create new memory to save both string
		mSize			= mLength + 1;
		this->mString	= new CharType[ mSize ];

		// Copy old string back to buffer
		EGE_MEM_CPY( this->mString, oldstring, index * sizeof( CharType ) );
		EGE_MEM_CPY( this->mString + index + length2, oldstring + index, ( length1 - index ) * sizeof( CharType ) );

		// Delete the old memory
		if ( olddelete )
		{
			delete[] oldstring;
		}
	}
	else
	{
		for ( _dword i = index; i < length1; i ++ )
			this->mString[ mLength - i + index - 1 ] = this->mString[ length1 - i + index - 1 ];
	}

	// Insert string
	EGE_MEM_CPY( this->mString + index, (const CharType*) string.Str( ), length2 * sizeof( CharType ) );

	// Set null-terminated
	this->mString[ mLength ] = 0;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_void MutableString< CharType, _STRING_ENCODE >::Remove( _dword index, _dword number )
{
	if ( number == 0 )
		return;

	if ( number == -1 )
	{
		this->mString[ index ] = 0;

		mLength = index;
	}
	else
	{
		EGE_ASSERT( index + number <= mLength );

		for ( _dword i = index + number; i <= mLength; i ++ )
			this->mString[ i - number ] = this->mString[i];

		mLength -= number;
	}
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_void MutableString< CharType, _STRING_ENCODE >::RemoveByRange( _dword start_index, _dword end_index )
{
	EGE_ASSERT( end_index >= start_index );

	Remove( start_index, end_index - start_index + 1 );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_void MutableString< CharType, _STRING_ENCODE >::RemoveChar( CharType character )
{
	_dword i = 0;
	_dword j = 0;
	_dword remove_number = 0;
	for ( ; i <= mLength; ++ i )
	{
		if ( this->mString[i] == character )
		{
			remove_number ++;
			continue;
		}
		this->mString[j] = this->mString[i];

		++ j;
	}
	mLength -= remove_number;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableString< CharType, _STRING_ENCODE >::Replace( _StringPtr srcstring, _StringPtr desstring )
{
	// Find the sub-string
	_dword index = this->SearchL2R( srcstring );
	if ( index == -1 )
		return _false;

	// Remove the old substring, and insert the new one
	Remove( index, srcstring.GetLength( ) );
	Insert( index, desstring );

	return _true;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableString< CharType, _STRING_ENCODE >::Replace( _dword index, CharType character )
{
	if ( index >= mLength )
		return _false;

	this->mString[ index ] = character;

	return _true;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableString< CharType, _STRING_ENCODE >::Replace( _dword index, _dword number, CharType character )
{
	_dword end = index + number;
	if ( end > mLength )
		return _false;

	for ( _dword i = index; i < end; i ++ )
		this->mString[i] = character;

	return _true;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableString< CharType, _STRING_ENCODE >::ReplaceAll( CharType oldchar, CharType newchar, _ubool ignorecase )
{
	if ( ignorecase )
		oldchar = EGE_TO_UPPER( oldchar );

	_ubool replaced = _false;

	for ( _dword i = 0; this->mString[i] != 0; i ++ )
	{
		if ( ignorecase )
		{
			if ( EGE_TO_UPPER( this->mString[i] ) != oldchar )
				continue;
		}
		else
		{
			if ( this->mString[i] != oldchar )
				continue;
		}

		this->mString[i] = newchar;

		// We have replaced it
		replaced = _true;
	}

	return replaced;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableString< CharType, _STRING_ENCODE >::ReplaceAll( _StringPtr srcstring, _StringPtr desstring, _ubool ignorecase )
{
	_ubool replaced = _false;

	// Get the sub-string length
	_dword srcstringlength = srcstring.GetLength( );
	_dword desstringlength = desstring.GetLength( );

	// The start index of substring
	_dword startindex = 0;

	// Start to replace sub-string
	_StringPtr string = *this;
	while ( string.IsEmpty( ) == _false )
	{
		// Search for the source sub-string
		_dword index = string.SearchL2R( srcstring, ignorecase );
		if ( index == -1 )
			break;

		// Replace the sub-string
		Remove( startindex + index, srcstringlength );
		Insert( startindex + index, desstring );

		// Continue to search sub-string
		startindex += index + desstringlength;
		string = SubString( startindex );

		// We have replaced it
		replaced = _true;
	}

	return replaced;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::CopyString( const CharType* string, _dword length )
{
	// Get string length
	if ( length == -1 )
		mLength	= Platform::StringLength( string );
	else
		mLength = length;

	// It's empty string
	if ( mLength == 0 && mSize > 0 )
	{
		this->mString[0] = 0;
	}
	// Create more memory if necessary.
	else if ( mSize < mLength + 1 )
	{
		// Free the old string buffer
		if ( mSize > 0 )
		{
			delete[] this->mString;
		}

		// Create and copy the string buffer
		CreateStringBuffer( string );
	}
	else
	{
		// Copy the string buffer
		CopyStringBuffer( string );
	}

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Lowercase( )
{
	if ( mLength > 0 )
		Platform::LowercaseString( this->mString );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Uppercase( )
{
	if ( mLength > 0 )
		Platform::UppercaseString( this->mString );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::TrimLeft( CharType character )
{
	Platform::TrimStringLeft( this->mString, mLength, character );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::TrimRight( CharType character )
{
	Platform::TrimStringRight( this->mString, mLength, character );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::TrimBoth( CharType character )
{
	Platform::TrimStringBoth( this->mString, mLength, character );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::TrimLeft( _StringPtr charset )
{
	Platform::TrimStringLeft( this->mString, mLength, charset.Str( ) );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::TrimRight( _StringPtr charset )
{
	Platform::TrimStringRight( this->mString, mLength, charset.Str( ) );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::TrimBoth( _StringPtr charset )
{
	Platform::TrimStringBoth( this->mString, mLength, charset.Str( ) );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
ConstString< CharType, _STRING_ENCODE > MutableString< CharType, _STRING_ENCODE >::SubString( _dword index ) const
{
	return TBaseClass::SubString( index ).Str( );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE > MutableString< CharType, _STRING_ENCODE >::SubString( _dword start, _dword length ) const
{
	if ( start >= mLength )
		return MutableString( );

	if ( start + length > mLength )
		length = -1;

	return MutableString( this->mString + start, length );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE > MutableString< CharType, _STRING_ENCODE >::LeftSubString( CharType delimiter ) const
{
	_dword index = this->SearchL2R( delimiter );
	if ( index == -1 )
		return *this;

	return MutableString( this->mString, index );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE > MutableString< CharType, _STRING_ENCODE >::LeftSubString( _StringPtr delimiter ) const
{
	_dword index = this->SearchL2R( delimiter );
	if ( index == -1 )
		return *this;

	return MutableString( this->mString, index );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE > MutableString< CharType, _STRING_ENCODE >::RightSubString( CharType delimiter ) const
{
	_dword index = TBaseClass::SearchR2L( delimiter );
	if ( index == -1 )
		return *this;

	return MutableString( this->mString + index + 1, mLength - index - 1 );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE > MutableString< CharType, _STRING_ENCODE >::RightSubString( _StringPtr delimiter ) const
{
	_dword index = TBaseClass::SearchR2L( delimiter );
	if ( index == -1 )
		return *this;

	return MutableString( this->mString + index + delimiter.GetLength( ), mLength - index - delimiter.GetLength( ) );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
_ubool MutableString< CharType, _STRING_ENCODE >::RemoveExtension( )
{
	_dword index = TBaseClass::SearchR2L( '.' );
	if ( index == -1 )
		return _false;

	Remove( index );

	return _true;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::FromValue( _int value, _dword radix )
{
	CharType string[ 1024 ];
	Platform::ConvertLongToString( value, radix, string, 1024 );

	CopyString( string );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::FromValue( _dword value, _dword radix )
{
	CharType string[ 1024 ];
	Platform::ConvertDwordToString( value, radix, string, 1024 );

	CopyString( string );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::FromValue( _large value, _dword radix )
{
	CharType string[1024];
	Platform::ConvertLargeToString( value, radix, string, 1024 );

	CopyString( string );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::FromValue( _qword value, _dword radix )
{
	CharType string[ 1024 ];
	Platform::ConvertQwordToString( value, radix, string, 1024 );

	CopyString( string );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::FromValue( _float value, _dword precision )
{
	CharType string[ 1024 ];
	Platform::ConvertFloatToString( value, string, 1024, precision );

	CopyString( string );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::FromValue( _double value, _dword precision )
{
	CharType string[ 1024 ];
	Platform::ConvertDoubleToString( value, string, 1024, precision );

	CopyString( string );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class FromStringType >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::FromString( const FromStringType& string )
{
	return FromString( string.GetEncodeType( ), string.Str( ) );
}

template<>
template< typename FromCharType >
MutableString< _chara, _ENCODING_ANSI >& MutableString< _chara, _ENCODING_ANSI >::FromString( _ENCODING encode, const FromCharType* string )
{
	Clear( );

	// Skip for empty string
	if ( string == _null || string[0] == 0 )
		return *this;

	// Start to convert string
	switch ( encode )
	{
		case _ENCODING_ANSI:
		{
			CopyString( (const _chara*) string, -1 );
		}
		break;

		case _ENCODING_UTF8:
		{
			// Get the UNICODE string ansi_string_size in bytes
			_dword utf16_string_size = Platform::Utf8ToUtf16( _null, 0, (const _chara*) string, -1 );
			if ( utf16_string_size > 0 )
			{
				// Convert to number of characters of UNICODE
				utf16_string_size /= sizeof( _charw );

				// Get the UTF-16 string size in 2 bytes ( contains '\0' )
				_dword size = utf16_string_size + 1;

				// Convert UTF-8 string to UNICODE
				MemArrayPtr< _charw > string_unicode( size );
				Platform::Utf8ToUtf16( string_unicode, size, (const _chara*) string, utf16_string_size );

				// Import from UNICODE string
				return FromString( _ENCODING_UTF16, (const _charw*) string_unicode );
			}
		}
		break;

		case _ENCODING_UTF16: 
		{
			// Get the ANSI string size in bytes
			_dword ansi_string_size = Platform::Utf16ToAnsi( _null, 0, (const _charw*) string, -1 );
			if ( ansi_string_size > 0 )
			{
				mLength = ansi_string_size;

				// Get the ANSI string size in 1 byte ( contains '\0' )
				_dword size = mLength + 1;

				// Grow the ANSI string buffer if needed
				if ( mSize < size )
					Resize( size );

				// Convert UNICODE string to ANSI
				Platform::Utf16ToAnsi( (_chara*) this->mString, size, (const _charw*) string, ansi_string_size );
			}	
		}
		break;
                    
        default:
        {
        }
        break;
	}

	return *this;
}

template<>
template< typename FromCharType >
MutableString< _chara, _ENCODING_UTF8 >& MutableString< _chara, _ENCODING_UTF8 >::FromString( _ENCODING encode, const FromCharType* string )
{
	Clear( );

	// Skip for empty string
	if ( string == _null || string[0] == 0 )
		return *this;

	// Start to convert string
	switch ( encode )
	{
		case _ENCODING_ANSI:
		{
			// Get the UNICODE string size in bytes
			_dword utf16_string_size = Platform::AnsiToUtf16( _null, 0, (const _chara*) string );
			if ( utf16_string_size > 0 )
			{
				// Convert to number of characters of UNICODE
				utf16_string_size /= sizeof( _charw );

				// Get the UTF-16 string size in 2 bytes ( contains '\0' )
				_dword size = utf16_string_size + 1;

				// Convert ANSI string to UNICODE
				MemArrayPtr< _charw > string_unicode( size );
				Platform::AnsiToUtf16( string_unicode, size, (const _chara*) string, utf16_string_size );

				// Import from UNICODE string
				return FromString( _ENCODING_UTF16, (const _charw*) string_unicode );
			}
		}
		break;

		case _ENCODING_UTF8: 
		{
			CopyString( (const _chara*) string, -1 ); 
		}
		break;

		case _ENCODING_UTF16:
		{
			// Get the UTF-8 string size in bytes
			_dword utf8_string_size = Platform::Utf16ToUtf8( _null, 0, (const _charw*) string, -1 );
			if ( utf8_string_size > 0 )
			{
				mLength = utf8_string_size;

				// Get the UTF-16 string size in 1 byte ( contains '\0' )
				_dword size = mLength + 1;

				// Grow the UTF-8 string buffer if needed
				if ( mSize < size )
					Resize( size );

				// Convert UNICODE string to UTF-8
				Platform::Utf16ToUtf8( (_chara*) this->mString, size, (const _charw*) string, utf8_string_size );
			}
		}
		break;

        default:
        {
        }
        break;
	}

	return *this;
}

template<>
template< typename FromCharType >
MutableString< _charw, _ENCODING_UTF16 >& MutableString< _charw, _ENCODING_UTF16 >::FromString( _ENCODING encode, const FromCharType* string )
{
	Clear( );

	// Skip for empty string
	if ( string == _null || string[0] == 0 )
		return *this;

	// Start to convert string
	switch ( encode )
	{
		case _ENCODING_ANSI:
		{
			// Get the UNICODE string size in bytes
			_dword utf16_string_size = Platform::AnsiToUtf16( _null, 0, (const _chara*) string, -1 );
			if ( utf16_string_size > 0 )
			{
				// Convert to number of characters of UNICODE
				mLength = utf16_string_size / sizeof( _charw );

				// Get the UTF-16 string size in 2 bytes ( contains '\0' )
				_dword size = mLength + 1;

				// Grow the UNICODE string buffer if needed
				if ( mSize < size )
					Resize( size );

				// Convert ANSI string to UNICODE
				Platform::AnsiToUtf16( (_charw*) this->mString, size, (const _chara*) string, utf16_string_size );
			}
		}
		break;

		case _ENCODING_UTF8:
		{
			// Get the UNICODE string size in bytes
			_dword utf16_string_size = Platform::Utf8ToUtf16( _null, 0, (const _chara*) string, -1 );
			if ( utf16_string_size > 0 )
			{
				// Convert to number of characters of UNICODE
				mLength = ( utf16_string_size / sizeof( _charw ) );

				// Get the UTF-16 string size in 2 bytes ( contains '\0' )
				_dword size = mLength + 1;

				// Grow the UNICODE string buffer if needed
				if ( mSize < size )
					Resize( size );

				// Convert UTF-8 string to UNICODE
				Platform::Utf8ToUtf16( (_charw*) this->mString, size, (const _chara*) string, utf16_string_size );
			}
		}
		break;

		case _ENCODING_UTF16: 
		{
			CopyString( (const _charw*) string, -1 ); 
		}
		break;
                    
        default:
        {
        }
        break;
	}

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const _StringPtr& format, const T1& p1 )
{
	return Format( format.Str( ), p1 );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const _StringPtr& format, const T1& p1, const T2& p2 )
{
	return Format( format.Str( ), p1, p2 );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2, class T3 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const _StringPtr& format, const T1& p1, const T2& p2, const T3& p3 )
{
	return Format( format.Str( ), p1, p2, p3 );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2, class T3, class T4 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const _StringPtr& format, const T1& p1, const T2& p2, const T3& p3, const T4& p4 )
{
	return Format( format.Str( ), p1, p2, p3, p4 );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2, class T3, class T4, class T5 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const _StringPtr& format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5 )
{
	return Format( format.Str( ), p1, p2, p3, p4, p5 );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2, class T3, class T4, class T5, class T6 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const _StringPtr& format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6 )
{
	return Format( format.Str( ), p1, p2, p3, p4, p5, p6 );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2, class T3, class T4, class T5, class T6, class T7 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const _StringPtr& format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7 )
{
	return Format( format.Str( ), p1, p2, p3, p4, p5, p6, p7 );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const _StringPtr& format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8 )
{
	return Format( format.Str( ), p1, p2, p3, p4, p5, p6, p7, p8 );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const _StringPtr& format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8, const T9& p9 )
{
	return Format( format.Str( ), p1, p2, p3, p4, p5, p6, p7, p8, p9 );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const _StringPtr& format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8, const T9& p9, const T10& p10 )
{
	return Format( format.Str( ), p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const _StringPtr& format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8, const T9& p9, const T10& p10, const T11& p11 )
{
	return Format( format.Str( ), p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const _StringPtr& format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8, const T9& p9, const T10& p10, const T11& p11, const T12& p12 )
{
	return Format( format.Str( ), p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const _StringPtr& format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8, const T9& p9, const T10& p10, const T11& p11, const T12& p12, const T13& p13 )
{
	return Format( format.Str( ), p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 );
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const CharType* format, const T1& p1 )
{
	_EGE_BUILD_ARGS_BEGIN( );
		_EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
	_EGE_BUILD_ARGS_END( );

	FormatStringByArguments( format, p1 );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const CharType* format, const T1& p1, const T2& p2 )
{
	_EGE_BUILD_ARGS_BEGIN( );
		_EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
		_EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
	_EGE_BUILD_ARGS_END( );

	FormatStringByArguments( format, p1, p2 );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2, class T3 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const CharType* format, const T1& p1, const T2& p2, const T3& p3 )
{
	_EGE_BUILD_ARGS_BEGIN( );
		_EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
		_EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
		_EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
	_EGE_BUILD_ARGS_END( );

	FormatStringByArguments( format, p1, p2, p3 );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2, class T3, class T4 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const CharType* format, const T1& p1, const T2& p2, const T3& p3, const T4& p4 )
{
	_EGE_BUILD_ARGS_BEGIN( );
		_EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
		_EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
		_EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
		_EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
	_EGE_BUILD_ARGS_END( );

	FormatStringByArguments( format, p1, p2, p3, p4 );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2, class T3, class T4, class T5 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const CharType* format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5 )
{
	_EGE_BUILD_ARGS_BEGIN( );
		_EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
		_EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
		_EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
		_EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
		_EGE_BUILD_ARG_WITH_INDEX( 5, p5 );
	_EGE_BUILD_ARGS_END( );

	FormatStringByArguments( format, p1, p2, p3, p4, p5 );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2, class T3, class T4, class T5, class T6 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const CharType* format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6 )
{
	_EGE_BUILD_ARGS_BEGIN( );
		_EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
		_EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
		_EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
		_EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
		_EGE_BUILD_ARG_WITH_INDEX( 5, p5 );
		_EGE_BUILD_ARG_WITH_INDEX( 6, p6 );
	_EGE_BUILD_ARGS_END( );

	FormatStringByArguments( format, p1, p2, p3, p4, p5, p6 );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2, class T3, class T4, class T5, class T6, class T7 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const CharType* format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7 )
{
	_EGE_BUILD_ARGS_BEGIN( );
		_EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
		_EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
		_EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
		_EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
		_EGE_BUILD_ARG_WITH_INDEX( 5, p5 );
		_EGE_BUILD_ARG_WITH_INDEX( 6, p6 );
		_EGE_BUILD_ARG_WITH_INDEX( 7, p7 );
	_EGE_BUILD_ARGS_END( );

	FormatStringByArguments( format, p1, p2, p3, p4, p5, p6, p7 );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const CharType* format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8 )
{
	_EGE_BUILD_ARGS_BEGIN( );
		_EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
		_EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
		_EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
		_EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
		_EGE_BUILD_ARG_WITH_INDEX( 5, p5 );
		_EGE_BUILD_ARG_WITH_INDEX( 6, p6 );
		_EGE_BUILD_ARG_WITH_INDEX( 7, p7 );
		_EGE_BUILD_ARG_WITH_INDEX( 8, p8 );
	_EGE_BUILD_ARGS_END( );

	FormatStringByArguments( format, p1, p2, p3, p4, p5, p6, p7, p8 );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const CharType* format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8, const T9& p9 )
{
	_EGE_BUILD_ARGS_BEGIN( );
		_EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
		_EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
		_EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
		_EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
		_EGE_BUILD_ARG_WITH_INDEX( 5, p5 );
		_EGE_BUILD_ARG_WITH_INDEX( 6, p6 );
		_EGE_BUILD_ARG_WITH_INDEX( 7, p7 );
		_EGE_BUILD_ARG_WITH_INDEX( 8, p8 );
		_EGE_BUILD_ARG_WITH_INDEX( 9, p9 );
	_EGE_BUILD_ARGS_END( );

	FormatStringByArguments( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const CharType* format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8, const T9& p9, const T10& p10 )
{
	_EGE_BUILD_ARGS_BEGIN( );
		_EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
		_EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
		_EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
		_EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
		_EGE_BUILD_ARG_WITH_INDEX( 5, p5 );
		_EGE_BUILD_ARG_WITH_INDEX( 6, p6 );
		_EGE_BUILD_ARG_WITH_INDEX( 7, p7 );
		_EGE_BUILD_ARG_WITH_INDEX( 8, p8 );
		_EGE_BUILD_ARG_WITH_INDEX( 9, p9 );
		_EGE_BUILD_ARG_WITH_INDEX( 10, p10 );
	_EGE_BUILD_ARGS_END( );

	FormatStringByArguments( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const CharType* format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8, const T9& p9, const T10& p10, const T11& p11 )
{
	_EGE_BUILD_ARGS_BEGIN( );
		_EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
		_EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
		_EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
		_EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
		_EGE_BUILD_ARG_WITH_INDEX( 5, p5 );
		_EGE_BUILD_ARG_WITH_INDEX( 6, p6 );
		_EGE_BUILD_ARG_WITH_INDEX( 7, p7 );
		_EGE_BUILD_ARG_WITH_INDEX( 8, p8 );
		_EGE_BUILD_ARG_WITH_INDEX( 9, p9 );
		_EGE_BUILD_ARG_WITH_INDEX( 10, p10 );
		_EGE_BUILD_ARG_WITH_INDEX( 11, p11 );
	_EGE_BUILD_ARGS_END( );

	FormatStringByArguments( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const CharType* format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8, const T9& p9, const T10& p10, const T11& p11, const T12& p12 )
{
	_EGE_BUILD_ARGS_BEGIN( );
		_EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
		_EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
		_EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
		_EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
		_EGE_BUILD_ARG_WITH_INDEX( 5, p5 );
		_EGE_BUILD_ARG_WITH_INDEX( 6, p6 );
		_EGE_BUILD_ARG_WITH_INDEX( 7, p7 );
		_EGE_BUILD_ARG_WITH_INDEX( 8, p8 );
		_EGE_BUILD_ARG_WITH_INDEX( 9, p9 );
		_EGE_BUILD_ARG_WITH_INDEX( 10, p10 );
		_EGE_BUILD_ARG_WITH_INDEX( 11, p11 );
		_EGE_BUILD_ARG_WITH_INDEX( 12, p12 );
	_EGE_BUILD_ARGS_END( );

	FormatStringByArguments( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 );

	return *this;
}

template< typename CharType, _ENCODING _STRING_ENCODE >
template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13 >
MutableString< CharType, _STRING_ENCODE >& MutableString< CharType, _STRING_ENCODE >::Format( const CharType* format, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8, const T9& p9, const T10& p10, const T11& p11, const T12& p12, const T13& p13 )
{
	_EGE_BUILD_ARGS_BEGIN( );
		_EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
		_EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
		_EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
		_EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
		_EGE_BUILD_ARG_WITH_INDEX( 5, p5 );
		_EGE_BUILD_ARG_WITH_INDEX( 6, p6 );
		_EGE_BUILD_ARG_WITH_INDEX( 7, p7 );
		_EGE_BUILD_ARG_WITH_INDEX( 8, p8 );
		_EGE_BUILD_ARG_WITH_INDEX( 9, p9 );
		_EGE_BUILD_ARG_WITH_INDEX( 10, p10 );
		_EGE_BUILD_ARG_WITH_INDEX( 11, p11 );
		_EGE_BUILD_ARG_WITH_INDEX( 12, p12 );
		_EGE_BUILD_ARG_WITH_INDEX( 13, p13 );
	_EGE_BUILD_ARGS_END( );

	FormatStringByArguments( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 );

	return *this;
}

}
