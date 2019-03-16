//! @file     TStringStream.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TStringStream
//----------------------------------------------------------------------------

template< class Type, typename CharType, _ENCODING Encoding >
class TStringStream : public Type
{
protected:
	typedef MutableString< CharType, Encoding > StringType;
	typedef ConstString< CharType, Encoding > StringPtrType;

protected:
	//!	The string
	StringType			mString;

	//!	The memory stream reader
	IStreamReaderRef	mMemStreamReader;

protected:
	TStringStream( StringPtrType string );
	virtual ~TStringStream( );

// IStream Interface
public:
	virtual _dword			GetSize( ) const override;
	virtual _dword 			GetOffset( ) const override;

	virtual const _byte*	GetBuffer( ) override;

	virtual _dword 			Seek( _SEEK flag, _int distance ) override;
	virtual _dword			SeekByArrangedValueFromBegin( _dword value ) override;

// IStreamReader Interface
public:
	virtual _dword			GetRemainBytes( ) const override;

	virtual _ubool 			ReachEnd( ) const override;

	virtual _dword 			PeekBuffer( _void* buffer, _dword size ) override;
	virtual _dword			PeekBuffer( _void* buffer, _dword size, _dword offset ) override;

	virtual _dword 			ReadBuffer( _void* buffer, _dword size ) override;
	virtual _dword 			ReadTiny( _tiny& data ) override;
	virtual _dword 			ReadShort( _short& data ) override;
	virtual _dword 			ReadLong( _int& data ) override;
	virtual _dword 			ReadByte( _byte& data ) override;
	virtual _dword 			ReadWord( _word& data ) override;
	virtual _dword 			ReadDword( _dword& data ) override;
	virtual _dword 			ReadQword( _qword& data ) override;
	virtual _dword 			ReadFloat( _float& data ) override;
	virtual _dword 			ReadDouble( _double& data ) override;
};

//----------------------------------------------------------------------------
// TStringStream Implementation
//----------------------------------------------------------------------------

template< class Type, typename CharType, _ENCODING Encoding >
TStringStream< Type, CharType, Encoding >::TStringStream( StringPtrType string ) : mString( string )
{
	// Create memory stream reader but without tail of string
	mMemStreamReader = GetInterfaceFactory( )->CreateMemStreamReader( 
		(const _byte*) mString.Str( ), mString.SizeOfBytes( ) - sizeof( CharType ), _STREAM_SHARE_MODE_READ_ONLY );
}

template< class Type, typename CharType, _ENCODING Encoding >
TStringStream< Type, CharType, Encoding >::~TStringStream( )
{
}

template< class Type, typename CharType, _ENCODING Encoding >
_dword TStringStream< Type, CharType, Encoding >::GetSize( ) const
{ 
	return mMemStreamReader->GetSize( );
}

template< class Type, typename CharType, _ENCODING Encoding >
_dword TStringStream< Type, CharType, Encoding >::GetOffset( ) const
{ 
	return mMemStreamReader->GetOffset( );
}

template< class Type, typename CharType, _ENCODING Encoding >
const _byte* TStringStream< Type, CharType, Encoding >::GetBuffer( )
{
	return mMemStreamReader->GetBuffer( );
}

template< class Type, typename CharType, _ENCODING Encoding >
_dword TStringStream< Type, CharType, Encoding >::Seek( _SEEK flag, _int distance )
{
	return mMemStreamReader->Seek( flag, distance );
}

template< class Type, typename CharType, _ENCODING Encoding >
_dword TStringStream< Type, CharType, Encoding >::SeekByArrangedValueFromBegin( _dword value )
{
	return mMemStreamReader->SeekByArrangedValueFromBegin( value );
}

template< class Type, typename CharType, _ENCODING Encoding >
_dword TStringStream< Type, CharType, Encoding >::GetRemainBytes( ) const
{ 
	return mMemStreamReader->GetRemainBytes( );
}

template< class Type, typename CharType, _ENCODING Encoding >
_ubool TStringStream< Type, CharType, Encoding >::ReachEnd( ) const
{ 
	return mMemStreamReader->ReachEnd( );
}

template< class Type, typename CharType, _ENCODING Encoding >
_dword TStringStream< Type, CharType, Encoding >::PeekBuffer( _void* buffer, _dword size )
{
	return mMemStreamReader->PeekBuffer( buffer, size );
}

template< class Type, typename CharType, _ENCODING Encoding >
_dword TStringStream< Type, CharType, Encoding >::PeekBuffer( _void* buffer, _dword size, _dword offset )
{
	return mMemStreamReader->PeekBuffer( buffer, size, offset );
}

template< class Type, typename CharType, _ENCODING Encoding >
_dword TStringStream< Type, CharType, Encoding >::ReadBuffer( _void* buffer, _dword size )
{
	return mMemStreamReader->ReadBuffer( buffer, size );
}

template< class Type, typename CharType, _ENCODING Encoding >
_dword TStringStream< Type, CharType, Encoding >::ReadTiny( _tiny& data )
{
	return mMemStreamReader->ReadTiny( data );
}

template< class Type, typename CharType, _ENCODING Encoding >
_dword TStringStream< Type, CharType, Encoding >::ReadShort( _short& data )
{
	return mMemStreamReader->ReadShort( data );
}

template< class Type, typename CharType, _ENCODING Encoding >
_dword TStringStream< Type, CharType, Encoding >::ReadLong( _int& data )
{
	return mMemStreamReader->ReadLong( data );
}

template< class Type, typename CharType, _ENCODING Encoding >
_dword TStringStream< Type, CharType, Encoding >::ReadByte( _byte& data )
{
	return mMemStreamReader->ReadByte( data );
}

template< class Type, typename CharType, _ENCODING Encoding >
_dword TStringStream< Type, CharType, Encoding >::ReadWord( _word& data )
{
	return mMemStreamReader->ReadWord( data );
}

template< class Type, typename CharType, _ENCODING Encoding >
_dword TStringStream< Type, CharType, Encoding >::ReadDword( _dword& data )
{
	return mMemStreamReader->ReadDword( data );
}

template< class Type, typename CharType, _ENCODING Encoding >
_dword TStringStream< Type, CharType, Encoding >::ReadQword( _qword& data )
{
	return mMemStreamReader->ReadQword( data );
}

template< class Type, typename CharType, _ENCODING Encoding >
_dword TStringStream< Type, CharType, Encoding >::ReadFloat( _float& data )
{
	return mMemStreamReader->ReadFloat( data );
}

template< class Type, typename CharType, _ENCODING Encoding >
_dword TStringStream< Type, CharType, Encoding >::ReadDouble( _double& data )
{
	return mMemStreamReader->ReadDouble( data );
}

}