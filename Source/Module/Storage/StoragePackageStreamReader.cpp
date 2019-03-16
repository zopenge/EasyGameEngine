//! @file     StoragePackageStreamReader.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEStorage.h"

//----------------------------------------------------------------------------
// StoragePackageStreamReader Implementation
//----------------------------------------------------------------------------

StoragePackageStreamReader::StoragePackageStreamReader( const PackageItem* package_item, StoragePackageFile* package_file ) 
	: mPackageItem( package_item ), mPackageFile( package_file )
{
	mOffset = 0;
}

StoragePackageStreamReader::~StoragePackageStreamReader( )
{
}

_dword StoragePackageStreamReader::GetSize( ) const
{
	return mPackageItem->mBufferSize;
}

_dword StoragePackageStreamReader::GetOffset( ) const
{
	return mOffset;
}

const _byte* StoragePackageStreamReader::GetBuffer( )
{
	return _null;
}

_dword StoragePackageStreamReader::Seek( _SEEK flag, _long distance )
{
	switch ( flag )
	{
		case _SEEK_BEGIN:
			mOffset = Math::Clamp< _dword >( distance, 0, mPackageItem->mBufferSize );
			break;

		case _SEEK_CURRENT:
			mOffset = Math::Clamp< _dword >( (_long) mOffset + distance, 0, mPackageItem->mBufferSize );
			break;

		case _SEEK_END:
			mOffset = Math::Clamp< _dword >( (_long) mPackageItem->mBufferSize + distance, 0, mPackageItem->mBufferSize );
			break;
	}

	return mOffset;
}

_dword StoragePackageStreamReader::SeekByArrangedValueFromBegin( _dword value )
{
	_dword offset = GetOffset( );

	if ( offset % value != 0 )
		Seek( _SEEK_BEGIN, Math::UpperArrange( offset, value ) );

	return GetOffset( );
}

_void StoragePackageStreamReader::SetEndian( _ENDIAN endian )
{
	BaseClass::SetEndian( endian );
}

_ENDIAN StoragePackageStreamReader::GetEndian( ) const
{
	return BaseClass::GetEndian( );
}

IStreamReaderPassRef StoragePackageStreamReader::CloneTo( )
{
	return _null;
}

_dword StoragePackageStreamReader::GetRemainBytes( ) const
{
	return mPackageItem->mBufferSize - mOffset;
}

_ubool StoragePackageStreamReader::ReachEnd( ) const
{
	return mOffset == mPackageItem->mBufferSize;
}

_dword StoragePackageStreamReader::PeekBuffer( _void* buffer, _dword size )
{
	return mPackageFile->ReadItemBuffer( *mPackageItem, 0, size, buffer );
}

_dword StoragePackageStreamReader::PeekBuffer( _void* buffer, _dword size, _dword offset )
{
	return mPackageFile->ReadItemBuffer( *mPackageItem, offset, size, buffer );
}

_dword StoragePackageStreamReader::ReadBuffer( _void* buffer, _dword size )
{
	// Read the item buffer
	_dword item_read_bytes = mPackageFile->ReadItemBuffer( *mPackageItem, mOffset, size, buffer );
	if ( item_read_bytes == 0 )
		return 0;

	// Update the offset
	mOffset += item_read_bytes;

	return item_read_bytes;
}

_dword StoragePackageStreamReader::ReadByte( _tiny& data )
{
	return ReadBuffer( &data, sizeof( data ) );
}

_dword StoragePackageStreamReader::ReadWord( _short& data )
{
	return ReadBuffer( &data, sizeof( data ) );
}

_dword StoragePackageStreamReader::ReadDword( _long& data )
{
	return ReadBuffer( &data, sizeof( data ) );
}

_dword StoragePackageStreamReader::ReadByte( _byte& data )
{
	return ReadBuffer( &data, sizeof( data ) );
}

_dword StoragePackageStreamReader::ReadWord( _word& data )
{
	return ReadBuffer( &data, sizeof( data ) );
}

_dword StoragePackageStreamReader::ReadDword( _dword& data )
{
	return ReadBuffer( &data, sizeof( data ) );
}

_dword StoragePackageStreamReader::ReadQword( _qword& data )
{
	return ReadBuffer( &data, sizeof( data ) );
}

_dword StoragePackageStreamReader::ReadFloat( _float& data )
{
	return ReadBuffer( &data, sizeof( data ) );
}

_dword StoragePackageStreamReader::ReadDouble( _double& data )
{
	return ReadBuffer( &data, sizeof( data ) );
}

_dword StoragePackageStreamReader::ReadString( AString& string )
{
	return BaseClass::ReadString( string );
}

_dword StoragePackageStreamReader::ReadString( WString& string )
{
	return BaseClass::ReadString( string );
}