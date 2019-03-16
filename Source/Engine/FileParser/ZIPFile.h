//! @file     ZIPFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ZIPFile
//----------------------------------------------------------------------------

class ZIPFile : public INTERFACE_BASEFILE_IMPL( IZIPFile )
{
private:
	typedef INTERFACE_BASEFILE_IMPL( IZIPFile ) BaseClass;

public:
	enum { _FILE_ID = 0x04034B50 };

private:
#if defined(_USE_LITE_ZIP_SDK_)
	typedef ZIPENTRY	ZipEntry;
#elif defined(_USE_LIBZIP_SDK_)
	typedef zip_entry	ZipEntry;
#endif

private:
	//!	The item info
	struct ItemInfo
	{
		ZipEntry	mEntry;
		WString		mFileName;

		operator WStringPtr ( ) const
			{ return mFileName; }

		ItemInfo( )
		{

		}
		ItemInfo( WStringPtr filename, const ZipEntry& entry )
		{
			mEntry		= entry;
			mFileName	= filename;
		}
	};
	typedef Array< ItemInfo > ItemInfoArray;

private:
	//!	The thread locker
	Lock			mLocker;

	//!	The items
	ItemInfoArray	mItems;

	//!	The default password
	AString			mPassword;

	//!	The zip file handle
#if defined(_USE_LITE_ZIP_SDK_)
	HZIP			mZipFileHandle;
	HUNZIP			mUnzipFileHandle;
#elif defined(_USE_LIBZIP_SDK_)
	zip_source*		mZipSource;
	zip*			mZip;
#endif

private:
	//!	Fix the file name.
	WString FixFileName( WStringPtr file_name ) const;

	//!	Build items from ZIP.
	_ubool BuildItemsFromZIP( );

	//!	Get the item stream.
#if defined(_USE_LITE_ZIP_SDK_)
	IStreamReaderPassRef GetItemStream( ZipEntry& zip_entry );
#elif defined(_USE_LIBZIP_SDK_)
	IStreamReaderPassRef GetItemStream( const ZipEntry& zip_entry, _dword index );
#endif

public:
	ZIPFile( WStringPtr password );
	virtual ~ZIPFile( );

public:
	//!	Create zip file.
	_ubool CreateFile( WStringPtr filename );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT			GetFileID( ) const override;

	virtual _ubool 					LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 					Unload( ) override;

// IZIPFile Interface
public:
	virtual _float					GetCompressionRatio( ) const override;

	virtual _ubool					AddFile( WStringPtr filename ) override;
	virtual _ubool					AddFile( WStringPtr filename, WStringPtr filename_in_zip ) override;
	virtual _ubool					HasFile( WStringPtr filename ) const override;
	virtual IStreamReaderPassRef	GetFile( WStringPtr filename ) override;

	virtual _ubool					AddFolder( WStringPtr dir_path, WStringPtr filter = L"", _dword flags = 0, _dword depth = -1 ) override;
	virtual _ubool					AddFolder( WStringPtr dir_path, WStringPtr dir_path_in_zip, WStringPtr filter = L"", _dword flags = 0, _dword depth = -1 ) override;

	virtual _dword					GetFileNumber( ) const override;
	virtual WStringPtr				GetFileNameByIndex( _dword index ) override;
	virtual IStreamReaderPassRef	GetFileStreamByIndex( _dword index ) override;
};

}