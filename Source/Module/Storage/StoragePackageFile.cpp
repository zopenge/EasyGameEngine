//! @file     StoragePackageFile.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEStorage.h"

//----------------------------------------------------------------------------
// StoragePackageFile Implementation
//----------------------------------------------------------------------------

StoragePackageFile::StoragePackageFile( )
{
}

StoragePackageFile::~StoragePackageFile( )
{
	Unload( );
}

_ubool StoragePackageFile::FlushFileHeader( )
{
	// Seek the file pionter to begin in order to write file header
	if ( mFile.Seek( _SEEK_BEGIN, 0 ) == -1 )
	{
		WLOG_ERROR( L"Flush file header failed when seek the file pointer" );
		return _false;
	}

	// Update the file header info
	if ( mFile.WriteBuffer( &mFileHeader, _FILE_HEADER_SIZE ) == _false )
	{
		WLOG_ERROR( L"Flush file header failed when seek the file pointer" );
		return _false;
	}

	return _true;
}

_ubool StoragePackageFile::CheckItemBounds( const PackageItem& item, _dword offset, _dword size ) const
{
	if ( size == 0 )
		return _false;

	if ( ( offset + size ) > item.mBufferSize )
		return _false;

	return _true;
}

_ubool StoragePackageFile::Load( WStringPtr filename )
{
	Unload( );

	// Load *.PAK file
	if ( mFile.Open( filename, _FILE_OPEN_EXISTING, _FILE_OPERATION_READ ) == _false )
	{
		WLOG_ERROR_1( L"Open the '%s' package file failed", filename.Str( ) );
		return _false;
	}

	// Read the *.PAK file header
	if ( mFile.ReadBuffer( &mFileHeader, _FILE_HEADER_SIZE ) == _false )
	{
		WLOG_ERROR_1( L"Read the '%s' package file failed", filename.Str( ) );
		return _false;
	}

	// Check the *.PAK file ID
	if ( mFileHeader.mFileID != PackageFileHeader::_FILE_ID )
	{
		WLOG_ERROR_1( L"The '%s' package file's header ID is invalid", filename.Str( ) );
		return _false;
	}

	// Read the items
	for ( _dword i = 0; i < mFileHeader.mItemsNumber; i ++ )
	{
		_dword read_bytes = 0;

		// Read item data
		PackageItem item;
		if ( mFile.ReadBuffer( &item, _ITEM_SIZE, &read_bytes ) == _false )
		{
			WLOG_ERROR_1( L"Read '%s' package file's item failed", filename.Str( ) );
			return _false;
		}

		// Check the item info
		if ( read_bytes != _ITEM_SIZE )
		{
			WLOG_ERROR_3( L"The '%s' package file's item size is invalid, need to read '%d' bytes, but actual just only read '%d' bytes now", 
				filename.Str( ), (_dword) _ITEM_SIZE, read_bytes );

			return _false;
		}

		// Check the buffer offset
		_dword offset = mFile.GetOffset( );
		if ( offset != item.mBufferOffset )
		{
			WLOG_ERROR_3( L"The '%s' package file's item offset is invalid, the correct offset is '%d', but actual is '%d' now", 
				filename.Str( ), item.mBufferOffset, offset );

			return _false;
		}

		// Skip the item buffer data
		if ( mFile.Seek( _SEEK_CURRENT, item.mBufferSize ) == -1 )
		{
			WLOG_ERROR_1( L"Seek '%s' package file buffer data failed", filename.Str( ) );
			return _false;
		}

		// Insert it into item map
		mItems.Insert( item, item.mFileNameCRC );
	}
	
	return _true;
}

_ubool StoragePackageFile::Create( WStringPtr filename )
{
	Unload( );

	// Create *.PAK file
	if ( mFile.Open( filename, _FILE_CREATE_ALWAYS, _FILE_OPERATION_ALL ) == _false )
	{
		WLOG_ERROR_1( L"Create the '%s' package file failed", filename.Str( ) );
		return _false;
	}

	// Write the *.PAK file header
	mFileHeader.mFileID			= PackageFileHeader::_FILE_ID;
	mFileHeader.mItemsNumber	= 0;
	if ( mFile.WriteBuffer( &mFileHeader, _FILE_HEADER_SIZE ) == _false )
	{
		WLOG_ERROR_1( L"Write the '%s' package file header info failed", filename.Str( ) );
		return _false;
	}

	return _true;
}

_void StoragePackageFile::Unload( )
{
	mFileHeader = PackageFileHeader( );

	// Clear the items
	mItems.Clear( );

	// Close *.PAK file handle
	mFile.Close( );
}

const PackageItem* StoragePackageFile::AddItem( WStringPtr filename, _dword size, const _void* buffer )
{
	if ( filename.IsEmpty( ) ||size == 0 )
		return _null;

	// Make sure the multiple thread is safe
	LockOwner lock_owner( mLocker );

	// Build the key
	_crcvalue key = filename.GetCRCValue( );

	// We can't add a duplicate item
	if ( mItems.Search( key ) != _null )
		return _null;

	// Skip the file pointer to the end to write item info
	if ( mFile.Seek( _SEEK_END, 0 ) == -1 )
		return _null;

	// Build the item info
	PackageItem item;
	item.mFileNameCRC	= key;
	item.mBufferOffset	= mFile.GetOffset( ) + _ITEM_SIZE;
	item.mBufferSize	= size;

	// Write the item header info
	if ( mFile.WriteBuffer( &item, _ITEM_SIZE ) == _false )
		return _null;

	// Write resource buffer if needed
	if ( buffer != _null )
	{
		if ( mFile.WriteBuffer( buffer, size ) == _false )
			return _null;
	}
	// Reserved the buffer by seeking
	else
	{
		if ( mFile.Seek( _SEEK_CURRENT, size ) == -1 )
			return _null;
	}

	// Flush the file header for new item
	mFileHeader.mItemsNumber ++;
	if ( FlushFileHeader( ) == _false )
		return _null;

	// Insert item
	return mItems.Insert( item, item.mFileNameCRC );
}

const PackageItem* StoragePackageFile::SearchItem( WStringPtr filename ) const
{
	return mItems.Search( filename.GetCRCValue( ) );
}

_dword StoragePackageFile::ReadItemBuffer( const PackageItem& item, _dword offset, _dword size, _void* buffer )
{
	// Check the item bounds
	if ( CheckItemBounds( item, offset, size ) == _false )
		return 0;

	// Make sure the multiple thread is safe
	LockOwner lock_owner( mLocker );

	// Locate at the item's buffer data
	if ( mFile.Seek( _SEEK_BEGIN, item.mBufferOffset + offset ) == _false )
		return 0;

	// Read the buffer
	_dword read_bytes = 0;
	if ( mFile.ReadBuffer( buffer, size, &read_bytes ) == _false )
		return 0;

	return read_bytes;
}

_dword StoragePackageFile::WriteItemBuffer( const PackageItem& item, _dword offset, _dword size, const _void* buffer )
{
	// Check the item bounds
	if ( CheckItemBounds( item, offset, size ) == _false )
		return 0;

	// Make sure the multiple thread is safe
	LockOwner lock_owner( mLocker );

	// Locate at the item's buffer data
	if ( mFile.Seek( _SEEK_BEGIN, item.mBufferOffset + offset ) == _false )
		return 0;

	// Write the buffer
	_dword write_bytes = 0;
	if ( mFile.WriteBuffer( buffer, size, &write_bytes ) == _false )
		return 0;

	return write_bytes;
}
