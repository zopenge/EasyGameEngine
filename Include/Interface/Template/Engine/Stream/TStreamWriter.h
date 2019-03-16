//! @file     TStreamWriter.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TStreamWriter
//----------------------------------------------------------------------------

template< typename Type >
class TStreamWriter : public Type
{
protected:
	template< typename StringPtrType >
	_dword TWriteString( _dword encoding_type, StringPtrType string );

protected:
	TStreamWriter( );
	virtual ~TStreamWriter( );

// IStreamWriter Interface
public:
	virtual _dword	WriteString( AStringPtr string ) override;
	virtual _dword	WriteString( WStringPtr string ) override;
};

//----------------------------------------------------------------------------
// TStreamWriter Implementation
//----------------------------------------------------------------------------

template< typename Type >
TStreamWriter< Type >::TStreamWriter( )
{
}

template< typename Type >
TStreamWriter< Type >::~TStreamWriter( )
{
}

template< typename Type >
template< typename StringPtrType >
_dword TStreamWriter< Type >::TWriteString( _dword encoding_type, StringPtrType string )
{
	// Write the string encoding type
	if ( this->WriteByte( (_byte) encoding_type ) == 0 )
		return 0;

	// Write the string length in bytes
	_dword string_length_in_bytes = string.GetLength( ) * sizeof( typename StringPtrType::_CharType );
	if ( this->WriteDword( string_length_in_bytes ) == 0 )
		return 0;

	// Feedback GUI tree
	if ( this->WriteBuffer( string.Str( ), string_length_in_bytes ) == 0 )
		return 0;

	return string_length_in_bytes + sizeof( _dword ) + sizeof( _byte );
}

template< typename Type >
_dword TStreamWriter< Type >::WriteString( AStringPtr string )
{
	return TWriteString( _ENCODING_ANSI, string );
}

template< typename Type >
_dword TStreamWriter< Type >::WriteString( WStringPtr string )
{
	return TWriteString( _ENCODING_UTF16, string );
}

}