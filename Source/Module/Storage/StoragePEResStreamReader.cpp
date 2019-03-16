//! @file     StoragePEResStreamReader.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEStorage.h"

//----------------------------------------------------------------------------
// StoragePEResStreamReader Implementation
//----------------------------------------------------------------------------

StoragePEResStreamReader::StoragePEResStreamReader( )
{
	mResource	= _null;
	mBuffer		= _null;
	mSize		= 0;
}

StoragePEResStreamReader::~StoragePEResStreamReader( )
{
	if ( mResource != _null )
	{
		Platform::FreeResource( _null, mResource );
		mResource = _null;
	}
}

_ubool StoragePEResStreamReader::Initialize( _handle resource, _dword size )
{
	mResource	= resource;
	mSize		= size;

	// Lock resource
	mBuffer = (_byte*) Platform::LockResource( mResource );
	if ( mBuffer == _null )
		return _false;

	// Create stream reader
	mStreamReader = GetInterfaceFactory( )->CreateMemStreamReader( mBuffer, mSize, _STREAM_SHARE_MODE_READ_ONLY );
	if ( mStreamReader.IsNull( ) )
		return _false;

	return _true;
}

_STREAM_TYPE StoragePEResStreamReader::GetType( ) const
{
	return mStreamReader->GetType( );
}

_STREAM_SHARE_MODE StoragePEResStreamReader::GetShareMode( ) const
{
	return mStreamReader->GetShareMode( );
}

_dword StoragePEResStreamReader::GetSize( ) const
{
	return mStreamReader->GetSize( );
}

_dword StoragePEResStreamReader::GetOffset( ) const
{
	return mStreamReader->GetOffset( );
}

const _byte* StoragePEResStreamReader::GetBuffer( )
{
	return mStreamReader->GetBuffer( );
}

_dword StoragePEResStreamReader::Seek( _SEEK flag, _long distance )
{
	return mStreamReader->Seek( flag, distance );
}

_dword StoragePEResStreamReader::SeekByArrangedValueFromBegin( _dword value )
{
	return mStreamReader->SeekByArrangedValueFromBegin( value );
}

_void StoragePEResStreamReader::SetEndian( _ENDIAN endian )
{
	mStreamReader->SetEndian( endian );
}

_ENDIAN StoragePEResStreamReader::GetEndian( ) const
{
	return mStreamReader->GetEndian( );
}

IObject* StoragePEResStreamReader::CloneTo( ) const
{
	StoragePEResStreamReader* stream_reader = new StoragePEResStreamReader( );

	// Create file stream reader
	stream_reader->mStreamReader = GetInterfaceFactory( )->CreateMemStreamReader( mBuffer, mSize, _STREAM_SHARE_MODE_READ_ONLY );
	if ( stream_reader->mStreamReader.IsNull( ) )
		{ EGE_RELEASE( stream_reader ); return _null; }

	return stream_reader;
}

_dword StoragePEResStreamReader::GetRemainBytes( ) const
{
	return mStreamReader->GetRemainBytes( );
}

_ubool StoragePEResStreamReader::ReachEnd( ) const
{
	return mStreamReader->ReachEnd( );
}

_dword StoragePEResStreamReader::PeekBuffer( _void* buffer, _dword size )
{
	return mStreamReader->PeekBuffer( buffer, size );
}

_dword StoragePEResStreamReader::PeekBuffer( _void* buffer, _dword size, _dword offset )
{
	return mStreamReader->PeekBuffer( buffer, size, offset );
}

_dword StoragePEResStreamReader::ReadBuffer( _void* buffer, _dword size )
{
	return mStreamReader->ReadBuffer( buffer, size );
}

_dword StoragePEResStreamReader::ReadTiny( _tiny& data )
{
	return mStreamReader->ReadTiny( data );
}

_dword StoragePEResStreamReader::ReadShort( _short& data )
{
	return mStreamReader->ReadShort( data );
}

_dword StoragePEResStreamReader::ReadLong( _long& data )
{
	return mStreamReader->ReadLong( data );
}

_dword StoragePEResStreamReader::ReadByte( _byte& data )
{
	return mStreamReader->ReadByte( data );
}

_dword StoragePEResStreamReader::ReadWord( _word& data )
{
	return mStreamReader->ReadWord( data );
}

_dword StoragePEResStreamReader::ReadDword( _dword& data )
{
	return mStreamReader->ReadDword( data );
}

_dword StoragePEResStreamReader::ReadQword( _qword& data )
{
	return mStreamReader->ReadQword( data );
}

_dword StoragePEResStreamReader::ReadFloat( _float& data )
{
	return mStreamReader->ReadFloat( data );
}

_dword StoragePEResStreamReader::ReadDouble( _double& data )
{
	return mStreamReader->ReadDouble( data );
}

_dword StoragePEResStreamReader::ReadString( AString& string )
{
	return mStreamReader->ReadString( string );
}

_dword StoragePEResStreamReader::ReadString( UString& string )
{
	return mStreamReader->ReadString( string );
}

_dword StoragePEResStreamReader::ReadString( WString& string )
{
	return mStreamReader->ReadString( string );
}