//! @file     RegularExpression.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// RegularExpression Implementation
//----------------------------------------------------------------------------

RegularExpression::RegularExpression( ) : mOptions( 0 ), mPCREContext( _null ), mPCREExtra( _null )
{
}

RegularExpression::~RegularExpression( )
{
	Clear( );
}

_void RegularExpression::Clear( )
{
	// Release pcre result data
	if ( mPCREContext != _null )
	{
		::free( mPCREContext );
		mPCREContext = _null;
	}

	// Release pcre extra
	if ( mPCREExtra != _null )
	{
		::free( mPCREExtra );
		mPCREExtra = _null;
	}
}

_ubool RegularExpression::SetPattern( WStringPtr pattern, _dword options )
{
	Clear( );

	mOptions			= options;
	mPCREPatternString	= pattern;

	// Convert pattern string to UTF-8.
	_chara pattern_string_ansi[ 4096 ];
	Platform::Utf16ToUtf8( pattern_string_ansi, 4096, pattern.Str( ) );

	// PCRE error string
	const _chara* error_string_ansi	= _null; 
	_int error_char_offset = 0;

	// Initialize PCRE options
	_dword pcre_options = PCRE_UTF8;
	if ( options & _MATCH_CASELESS )
		pcre_options |= PCRE_CASELESS;

	// Try to compile the pattern string
	mPCREContext = ::pcre_compile( pattern_string_ansi, pcre_options, &error_string_ansi, &error_char_offset, _null );
	if ( mPCREContext == _null && error_string_ansi != _null )
	{
		// Get error character
		_charw error_character = (_charw) pattern[ error_char_offset ];
		if ( error_character == 0 )
			error_character = '?';

		// Get the error string
		WString error_string; 
		error_string.FromString( _ENCODING_ANSI, error_string_ansi );

		// Output the error message
		WLOG_ERROR_3( L"%s:%d:'%c'", error_string.Str( ), error_char_offset, error_character );

		return _false;
	}

	// Create extra data
	mPCREExtra = (pcre_extra*) ::pcre_study( (const pcre*) mPCREContext, 0, &error_string_ansi );
	if ( mPCREExtra == _null && error_string_ansi != _null )
	{
		// Output the error message
		ALOG_ERROR( error_string_ansi );

		return _false;
	}

	return _true;
}

WStringPtr RegularExpression::GetPattern( ) const
{
	return mPCREPatternString;
}

_ubool RegularExpression::Match( AStringPtr string ) const
{
	if ( string.IsEmpty( ) )
		return _false;

	// Match sub-string with pattern
	if ( mPCREContext != _null )
	{
		_int match_buffer[1024]; match_buffer[0] = 0;

		// Execute the regular expression matching
		_dword substringnumber = ::pcre_exec( (const pcre*) mPCREContext, (const pcre_extra*) mPCREExtra, string.Str( ), string.GetLength( ), 0, 0, match_buffer, 1024 );
		if ( substringnumber > 0 )
			return match_buffer[0] != -1 && match_buffer[1] != -1;
	}

	return _false;
}

_ubool RegularExpression::Match( WStringPtr string ) const
{
	if ( string.IsEmpty( ) )
		return _false;

	// Convert to UTF8 string
	_chara string_utf8[ 4096 ]; 
	Platform::Utf16ToUtf8( string_utf8, 4096, string.Str( ) );

	// Match sub-string in UTF-8 format
	return Match( string_utf8 );
}