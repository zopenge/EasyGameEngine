//! @file     TTextFile.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TTextFile
//----------------------------------------------------------------------------

template< typename Type >
class TTextFile : public Type
{
protected:
	//!	The encode type
	_ENCODING			mEncodeType;
	//!	The current line number
	_dword				mCurrentLineNumber;

	//!	The stream reader
	IStreamReaderRef	mStreamReader;

protected:
	//!	Build the encode type by stream.
	inline _ubool BuildEncodeType( );
	//!	Get the character size in bytes by encode type.
	inline _dword GetCharSize( ) const;

protected:
	TTextFile( );
	virtual ~TTextFile( );
	
// IBaseFile Interface
public:
	virtual _ubool 		LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 		Unload( ) override;

// ITXTFile Interface
public:
	virtual _ENCODING	GetEncodeType( ) const override;

	virtual _ubool		ReadString( WString& string ) override;

	virtual _ubool 		ReadLine( AString& string, _dword* linenumber = _null ) override;
	virtual _ubool 		ReadLine( WString& string, _dword* linenumber = _null ) override;

	virtual _ubool		JumpToLine( _dword linenumber ) override;
};

//----------------------------------------------------------------------------
// TTextFile Implementation
//----------------------------------------------------------------------------

template< typename Type >
TTextFile< Type >::TTextFile( )
{
	mEncodeType			= _ENCODING_UNKNOWN;
	mCurrentLineNumber	= 1;
}

template< typename Type >
TTextFile< Type >::~TTextFile( )
{

}

template< typename Type >
_ubool TTextFile< Type >::BuildEncodeType( )
{
	if ( mEncodeType != _ENCODING_UNKNOWN )
		return _true;

	// Check the stream reader
	if ( this->mStreamReader.IsNull( ) )
		return _false;

	// UTF-8
	if ( this->mStreamReader->GetSize( ) >= 3 )
	{
		// Peek first 3 bytes to get unique ID
		_dword utf8_id = 0;
		this->mStreamReader->PeekBuffer( &utf8_id, 3 );

		if ( utf8_id == _UTF8_HEADER )
		{
			mEncodeType = _ENCODING_UTF8;
			return _true;
		}
	}

	// UNICODE
	if ( this->mStreamReader->GetSize( ) >= 2 )
	{
		// Peek first 2 bytes to get unique ID
		_dword unicode_id = 0;
		this->mStreamReader->PeekBuffer( &unicode_id, 2 );

		if ( unicode_id == _UTF16_HEADER )
		{
			mEncodeType = _ENCODING_UTF16;
			return _true;
		}
	}

	// ANSI
	mEncodeType = _ENCODING_ANSI;

	return _true;
}

template< typename Type >
_dword TTextFile< Type >::GetCharSize( ) const
{
	_dword char_size = GetEncodeType( ) == _ENCODING_UTF16 ? sizeof( _charw ) : sizeof( _chara );
	return char_size;
}

template< typename Type >
_ubool TTextFile< Type >::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	mStreamReader = stream_reader;

	// Build the encoding type
	return BuildEncodeType( );
}

template< typename Type >
_void TTextFile< Type >::Unload( )
{
	mEncodeType			= _ENCODING_UNKNOWN;
	mCurrentLineNumber	= 0;

	mStreamReader.Clear( );
}

template< typename Type >
_ENCODING TTextFile< Type >::GetEncodeType( ) const
{
	return mEncodeType;
}

template< typename Type >
_ubool TTextFile< Type >::ReadString( WString& string )
{
	if ( this->mStreamReader.IsNull( ) )
		return _false;

	// Read whole text string info ( +2 in order to fill '\0' character )
	MemArrayPtr< _byte > buffer( this->mStreamReader->GetSize( ) + 2 );
	this->mStreamReader->PeekBuffer( buffer, this->mStreamReader->GetSize( ), 0 );

	// Convert string to UNICODE
	switch ( GetEncodeType( ) )
	{
		// ANSI
		case _ENCODING_ANSI:
		{
			buffer[ this->mStreamReader->GetSize( ) ] = 0;

			string.FromString( _ENCODING_ANSI, (const _chara*) (const _byte*) buffer );
		}
		break;

		// UTF-8
		case _ENCODING_UTF8:
		{
			buffer[ this->mStreamReader->GetSize( ) ] = 0;

			// Jump UTF-8 header tag
			string.FromString( _ENCODING_UTF8, (const _chara*) ( (const _byte*) buffer ) + 3 );
		}
		break;

		// UNICODE
		case _ENCODING_UTF16:	
		{
			buffer[ this->mStreamReader->GetSize( ) ]		= 0;
			buffer[ this->mStreamReader->GetSize( ) + 1 ]	= 0;

			// Jump UNICOD header tag
			string = (const _charw*)( ( (const _byte*) buffer ) + 2 ); 
		}
		break;

		// Unknown encode ID
		default:
			return _false;
	}

	return _true;
}

template< typename Type >
_ubool TTextFile< Type >::ReadLine( AString& string, _dword* linenumber )
{
	if ( this->mStreamReader.IsNull( ) )
		return _false;

	if ( this->mStreamReader->ReachEnd( ) )
		return _false;

	string.Clear( );

	// Get the character size in bytes
	const _dword char_size = GetCharSize( );

	// Read line
	while ( this->mStreamReader->ReachEnd( ) == _false )
	{
		// Read character
		switch ( char_size )
		{
			case 1:
			{
				_byte character;
				this->mStreamReader->ReadByte( character );

				// Skip for '\r'
				if ( character == '\r' )
					continue;

				// We finished the line string reading
				if ( character == '\n' )
				{
					// Feedback line number
					if ( linenumber != _null )
						*linenumber = mCurrentLineNumber;

					// Update the line number
					mCurrentLineNumber ++;
					return _true;
				}
				else
				{
					// Update the single line string
					string += (_chara)character;
				}
			}
			break;

			case 2:
			{
				_word character;
				this->mStreamReader->ReadWord( character );

				// Skip for '\r'
				if ( character == '\r' )
					continue;

				// We finished the line string reading
				if ( character == '\n' )
				{
					// Feedback line number
					if ( linenumber != _null )
						*linenumber = mCurrentLineNumber;

					// Update the line number
					mCurrentLineNumber ++;
					return _true;
				}
				else
				{
					// Update the single line string
					string += AString( ).FromString( WString( (_charw)character ) );
				}
			}
			break;
		}
	}

	return _true;
}

template< typename Type >
_ubool TTextFile< Type >::ReadLine( WString& string, _dword* linenumber )
{
	if ( this->mStreamReader.IsNull( ) )
		return _false;

	if ( this->mStreamReader->ReachEnd( ) )
		return _false;

	string.Clear( );

	// Get the character size in bytes
	const _dword char_size = GetCharSize( );

	// Read line
	while ( this->mStreamReader->ReachEnd( ) == _false )
	{
		// Read character
		switch ( char_size )
		{
			case 1:
			{
				_byte character;
				this->mStreamReader->ReadByte( character );

				// Skip for '\r'
				if ( character == '\r' )
					continue;

				// We finished the line string reading
				if ( character == '\n' )
				{
					// Feedback line number
					if ( linenumber != _null )
						*linenumber = mCurrentLineNumber;

					// Update the line number
					mCurrentLineNumber ++;
					return _true;
				}
				else
				{
					// Update the single line string
					string += WString( ).FromString( AString( (_chara)character ) );
				}
			}
			break;

			case 2:
			{
				_word character;
				this->mStreamReader->ReadWord( character );

				// Skip for '\r'
				if ( character == '\r' )
					continue;

				// We finished the line string reading
				if ( character == '\n' )
				{
					// Feedback line number
					if ( linenumber != _null )
						*linenumber = mCurrentLineNumber;

					// Update the line number
					mCurrentLineNumber ++;
					return _true;
				}
				else
				{
					// Update the single line string
					string += (_charw)character;
				}
			}
			break;
		}
	}

	return _true;
}

template< typename Type >
_ubool TTextFile< Type >::JumpToLine( _dword linenumber )
{
	if ( linenumber == 0 )
		return _false;

	if ( this->mStreamReader.IsNull( ) )
		return _false;

	// Get the header size
	_dword header_size = 0;
	switch ( GetEncodeType( ) )
	{
		case _ENCODING_ANSI:	header_size = 0; break;
		case _ENCODING_UTF8:	header_size = 3; break;
		case _ENCODING_UTF16:	header_size = 2; break;
		default:
			break;
	}

	// Seek header section
	this->mStreamReader->Seek( _SEEK_BEGIN, (_long)header_size );

	// Locate at the first line
	if ( linenumber == 1 )
		return _true;

	// Get the character size in bytes
	const _dword char_size = GetCharSize( );

	// Read line
	while ( this->mStreamReader->ReachEnd( ) == _false )
	{
		// Read character
		switch ( char_size )
		{
			case 1:
			{
				_byte character;
				this->mStreamReader->ReadByte( character );

				// It's line section
				if ( character == '\n' )
				{
					linenumber --;
					if ( linenumber == 0 )
						return _true;
				}
			}
			break;

			case 2:
			{
				_word character;
				this->mStreamReader->ReadWord( character );

				// It's line section
				if ( character == '\n' )
				{
					linenumber --;
					if ( linenumber == 0 )
						return _true;
				}
			}
			break;
		}
	}

	// Locate failed
	return _false;
}

}