//! @file     TStreamReader.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TStreamReader
//----------------------------------------------------------------------------

template< typename Type >
class TStreamReader : public TStream< Type >
{
protected:
	typedef TStream< Type > TBaseClass;

protected:
	//!	Read string to buffer and feedback encoding.
	template< typename StringType >
	_dword TReadString( StringType& string );

protected:
	TStreamReader( );
	virtual ~TStreamReader( );

// IStreamReader Interface
public:
	virtual _dword ReadString( AString& string ) override;
	virtual _dword ReadString( UString& string ) override;
	virtual _dword ReadString( WString& string ) override;

	virtual _dword ReadLine( AString& string ) override;
	virtual _dword ReadLine( UString& string ) override;
	virtual _dword ReadLine( WString& string ) override;

	virtual _dword ReadLine( _ENCODING encode_type, AString& string ) override;
	virtual _dword ReadLine( _ENCODING encode_type, UString& string ) override;
	virtual _dword ReadLine( _ENCODING encode_type, WString& string ) override;

	virtual _dword ReadEncodeType( _ENCODING& encode_type ) override;
};

//----------------------------------------------------------------------------
// TStreamReader Implementation
//----------------------------------------------------------------------------

template< typename Type >
TStreamReader< Type >::TStreamReader( )
{
}

template< typename Type >
TStreamReader< Type >::~TStreamReader( )
{
}

template< typename Type >
template< typename StringType >
_dword TStreamReader< Type >::TReadString( StringType& string )
{
	// Read the string encoding type
	_byte encoding_type = _ENCODING_UNKNOWN;
	this->ReadByte( encoding_type );

	// Read the total bytes of string
	_dword total_bytes = 0;
	this->ReadDword( total_bytes );

	// Create string buffer and read it
	MemArrayPtr< _byte > string_buffer( total_bytes + 2 );
	this->ReadBuffer( string_buffer, total_bytes );

	// Insert the tail of string
	string_buffer[ total_bytes ] = 0;
	string_buffer[ total_bytes + 1 ] = 0;

	// Convert string to ANSI
	string.FromString( (_ENCODING) encoding_type, (_byte*) string_buffer );

	return total_bytes + sizeof( _dword ) + sizeof( _byte );
}

template< typename Type >
_dword TStreamReader< Type >::ReadString( AString& string )
{
	return TReadString( string );
}

template< typename Type >
_dword TStreamReader< Type >::ReadString( UString& string )
{
	return TReadString( string );
}

template< typename Type >
_dword TStreamReader< Type >::ReadString( WString& string )
{
	return TReadString( string );
}

template< typename Type >
_dword TStreamReader< Type >::ReadLine( AString& string )
{
	if ( this->ReachEnd( ) )
		return 0;

	_dword offset = this->GetOffset( );

	while ( this->ReachEnd( ) == _false )
	{
		_byte character;
		this->ReadByte( character );

		// Skip for '\r'
		if ( character == '\r' )
			continue;

		// We finished the line string reading
		if ( character == '\n' )
			break;

		// Update the single line string
		string += (_chara)character;
	}

	return this->GetOffset( ) - offset;
}

template< typename Type >
_dword TStreamReader< Type >::ReadLine( UString& string )
{
	AString string_ansi;
	_dword read_size = ReadLine( string_ansi );
	if ( read_size != 0 )
		string.FromString( string_ansi );

	return read_size;
}

template< typename Type >
_dword TStreamReader< Type >::ReadLine( WString& string )
{
	if ( this->ReachEnd( ) )
		return 0;

	_dword offset = this->GetOffset( );

	while ( this->ReachEnd( ) == _false )
	{
		_word character;
		this->ReadWord( character );

		// Skip for '\r'
		if ( character == '\r' )
			continue;

		// We finished the line string reading
		if ( character == '\n' )
			break;

		// Update the single line string
		string += (_charw)character;
	}

	return this->GetOffset( ) - offset;
}

template< typename Type >
_dword TStreamReader< Type >::ReadLine( _ENCODING encode_type, AString& string )
{
	if ( encode_type == _ENCODING_UNKNOWN )
		return 0;

	_dword offset = this->GetOffset( );

	switch ( encode_type )
	{
		case _ENCODING_ANSI:
		{
			// Read line
			while ( this->ReachEnd( ) == _false )
			{
				// Read character
				_byte character;
				this->ReadByte( character );

				// Skip for '\r'
				if ( character == '\r' )
					continue;

				// We finished the line string reading
				if ( character == '\n' )
					break;

				// Update the single line string
				string += (_chara)character;
			}
		}
		break;

		case _ENCODING_UTF8:
		{
			UString string_utf8;

			// Read line
			while ( this->ReachEnd( ) == _false )
			{
				_byte character;
				this->ReadByte( character );

				// Skip for '\r'
				if ( character == '\r' )
					continue;

				// We finished the line string reading
				if ( character == '\n' )
					break;

				// Update the single line string
				string_utf8 += (_chara)character;
			}

			string.FromString( string_utf8 );
		}
		break;

		case _ENCODING_UTF16:
		{
			WString string_utf16;

			// Read line
			while ( this->ReachEnd( ) == _false )
			{
				_word character;
				this->ReadWord( character );

				// Skip for '\r'
				if ( character == '\r' )
					continue;

				// We finished the line string reading
				if ( character == '\n' )
					break;

				// Update the single line string
				string_utf16 += (_charw)character;
			}

			string.FromString( string_utf16 );
		}
		break;

		default:
			break;
	}

	return this->GetOffset( ) - offset;
}

template< typename Type >
_dword TStreamReader< Type >::ReadLine( _ENCODING encode_type, UString& string )
{
	AString string_ansi;
	_dword read_size = ReadLine( encode_type, string_ansi );
	string.FromString( string_ansi );

	return read_size;
}

template< typename Type >
_dword TStreamReader< Type >::ReadLine( _ENCODING encode_type, WString& string )
{
	AString string_ansi;
	_dword read_size = ReadLine( encode_type, string_ansi );
	string.FromString( string_ansi );

	return read_size;
}

template< typename Type >
_dword TStreamReader< Type >::ReadEncodeType( _ENCODING& encode_type )
{
	// The read byte size
	_dword read_size = 0;

	encode_type = _ENCODING_ANSI;

	// UTF-8
	if ( this->GetSize( ) >= 3 )
	{
		// Peek first 3 bytes to get unique ID
		_dword utf8_id = 0;
		this->PeekBuffer( &utf8_id, 3 );

		if ( utf8_id == _UTF8_HEADER )
		{
			encode_type = _ENCODING_UTF8;
			read_size = 3;
		}
	}

	// UNICODE
	if ( this->GetSize( ) >= 2 )
	{
		// Peek first 2 bytes to get unique ID
		_dword unicode_id = 0;
		this->PeekBuffer( &unicode_id, 2 );

		if ( unicode_id == _UTF16_HEADER )
		{
			encode_type = _ENCODING_UTF16;
			read_size = 2;
		}
	}

	if ( read_size != 0 )
		this->Seek( _SEEK_CURRENT, read_size );

	return read_size;
}

}