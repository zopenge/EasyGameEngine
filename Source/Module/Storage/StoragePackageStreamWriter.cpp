//! @file     StoragePackageStreamWriter.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEStorage.h"

//----------------------------------------------------------------------------
// StoragePackageStreamWriter Implementation
//----------------------------------------------------------------------------

StoragePackageStreamWriter::StoragePackageStreamWriter( const PackageItem* package_item, StoragePackageFile* package_file ) 
	: mPackageItem( package_item ), mPackageFile( package_file )
{
	mOffset = 0;
}

StoragePackageStreamWriter::~StoragePackageStreamWriter( )
{
}

_dword StoragePackageStreamWriter::GetSize( ) const
{
	return mPackageItem->mBufferSize;
}

_dword StoragePackageStreamWriter::GetOffset( ) const
{
	return mOffset;
}

const _byte* StoragePackageStreamWriter::GetBuffer( )
{
	return _null;
}

_dword StoragePackageStreamWriter::Seek( _SEEK flag, _long distance )
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

_dword StoragePackageStreamWriter::SeekByArrangedValueFromBegin( _dword value )
{
	_dword offset = GetOffset( );

	if ( offset % value != 0 )
		Seek( _SEEK_BEGIN, Math::UpperArrange( offset, value ) );

	return GetOffset( );
}

_void StoragePackageStreamWriter::SetEndian( _ENDIAN endian )
{
	BaseClass::SetEndian( endian );
}

_ENDIAN StoragePackageStreamWriter::GetEndian( ) const
{
	return BaseClass::GetEndian( );
}

_dword StoragePackageStreamWriter::RemoveBuffer( _dword offset, _dword size )
{
	return 0;
}

_ubool StoragePackageStreamWriter::SetCurOffsetAsEndPos( )
{
	return _false;
}

_dword StoragePackageStreamWriter::WriteBuffer( const _void* buffer, _dword size )
{
	// Write item
	_dword write_bytes_of_item = mPackageFile->WriteItemBuffer( *mPackageItem, mOffset, size, buffer );
	if ( write_bytes_of_item == 0 )
		return 0;

	// Update the offset
	mOffset += write_bytes_of_item;

	return write_bytes_of_item;
}

_dword StoragePackageStreamWriter::WriteByte( _tiny data )
{
	return WriteBuffer( &data, sizeof( data ) );
}

_dword StoragePackageStreamWriter::WriteWord( _short data )
{
	return WriteBuffer( &data, sizeof( data ) );
}

_dword StoragePackageStreamWriter::WriteDword( _long data )
{
	return WriteBuffer( &data, sizeof( data ) );
}

_dword StoragePackageStreamWriter::WriteByte( _byte data )
{
	return WriteBuffer( &data, sizeof( data ) );
}

_dword StoragePackageStreamWriter::WriteWord( _word data )
{
	return WriteBuffer( &data, sizeof( data ) );
}

_dword StoragePackageStreamWriter::WriteDword( _dword data )
{
	return WriteBuffer( &data, sizeof( data ) );
}

_dword StoragePackageStreamWriter::WriteQword( _qword data )
{
	return WriteBuffer( &data, sizeof( data ) );
}

_dword StoragePackageStreamWriter::WriteFloat( _float data )
{
	return WriteBuffer( &data, sizeof( data ) );
}

_dword StoragePackageStreamWriter::WriteDouble( _double data )
{
	return WriteBuffer( &data, sizeof( data ) );
}

_dword StoragePackageStreamWriter::WriteString( AStringPtr string )
{
	return BaseClass::WriteString( string );
}

_dword StoragePackageStreamWriter::WriteString( WStringPtr string )
{
	return BaseClass::WriteString( string );
}