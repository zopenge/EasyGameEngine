//! @file     StoragePackageFile.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// PackageFileHeader
//----------------------------------------------------------------------------

struct PackageFileHeader
{
	enum { _FILE_ID	= EGE_ID( 'P', 'A', 'K', '1' ) };

	//!	The *.PAK file ID
	_dword	mFileID;
	//!	The *.PAK items number
	_dword	mItemsNumber;
	//!	The reserved data
	_dword	mReserved[4];

	PackageFileHeader( ) : mFileID( _FILE_ID ), mItemsNumber( 0 ) 
	{
		EGE_INIT_ARRAY( mReserved );
	}
};

//----------------------------------------------------------------------------
// PackageItem
//----------------------------------------------------------------------------

struct PackageItem
{
	//!	The file name CRC value
	_crcvalue	mFileNameCRC;
	//!	The buffer offset
	_dword		mBufferOffset;
	//!	The buffer size
	_dword		mBufferSize;
	//!	The reserved data
	_dword		mReserved[2];

	PackageItem( )
	{
		mFileNameCRC	= 0;
		mBufferOffset	= 0;
		mBufferSize		= 0;

		EGE_INIT_ARRAY( mReserved );
	}
};

//----------------------------------------------------------------------------
// StoragePackageFile
//----------------------------------------------------------------------------

class StoragePackageFile : public RefObject
{
private:
	typedef Map< PackageItem, _crcvalue > PackageItemMap;

private:
	//!	The file header size
	enum { _FILE_HEADER_SIZE = sizeof( PackageFileHeader ) };
	//!	The item size
	enum { _ITEM_SIZE = sizeof( PackageItem ) };

private:
	//!	The file handle
	File				mFile;
	//!	The file header
	PackageFileHeader	mFileHeader;

	//!	The locker
	Lock				mLocker;

	//!	The items
	PackageItemMap		mItems;

private:
	//!	Flush the file header ( Flush file buffer ).
	_ubool FlushFileHeader( );

	//!	Check item bounds.
	_ubool CheckItemBounds( const PackageItem& item, _dword offset, _dword size ) const;

public:
	StoragePackageFile( );
	virtual ~StoragePackageFile( );

public:
	//!	Load the *.PAK file.
	//!	@param		filename	The *.PAK file name.
	//! @return		True indicates success, false indicates failure.
	_ubool Load( WStringPtr filename );
	//!	Create the *.PAK file.
	//!	@param		filename	The *.PAK file name.
	//! @return		True indicates success, false indicates failure.
	_ubool Create( WStringPtr filename );
	//!	Unload the *.PAK file.
	//!	@param		none.
	//!	@return		none.
	_void Unload( );

	//!	Add item.
	//!	@param		filename	The file name.
	//!	@param		size		The resource buffer size.
	//!	@param		buffer		The resource buffer data.
	//!	@return		The item info.
	const PackageItem* AddItem( WStringPtr filename, _dword size, const _void* buffer );
	//!	Search item.
	//!	@param		filename	The file name.
	//!	@return		The item info.
	const PackageItem* SearchItem( WStringPtr filename ) const;

	//!	Read item data.
	//!	@param		item		The item info.
	//!	@param		offset		The item resource buffer offset what you want to seek.
	//!	@param		size		The item resource buffer size what you want to read.
	//!	@param		buffer		The item resource buffer.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	_dword ReadItemBuffer( const PackageItem& item, _dword offset, _dword size, _void* buffer );
	//!	Write item data.
	//!	@param		item		The item info.
	//!	@param		offset		The item resource buffer offset what you want to seek.
	//!	@param		size		The item resource buffer size what you want to write.
	//!	@param		buffer		The item resource buffer.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	_dword WriteItemBuffer( const PackageItem& item, _dword offset, _dword size, const _void* buffer );
};

//----------------------------------------------------------------------------
// StoragePackageFile Implementation
//----------------------------------------------------------------------------

}
