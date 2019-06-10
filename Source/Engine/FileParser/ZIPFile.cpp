//! @file     ZIPFile.cpp
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// ZIPFile Helpful Functions Implementation
//----------------------------------------------------------------------------

#if defined(_USE_LIBZIP_SDK_)

static WString GetLIBZIPErrString( const zip_error& err )
{
	return WString( ).Format( L"zip_err: %d, sys_err: %d, err: %s",
		err.zip_err, err.sys_err, WString( ).FromString( _ENCODING_ANSI, err.str ).Str( ) );
}

#endif

//----------------------------------------------------------------------------
// ZIPFile Implementation
//----------------------------------------------------------------------------

ZIPFile::ZIPFile( WStringPtr password )
{
	mPassword.FromString( password );

#if defined(_USE_LITE_ZIP_SDK_)
	mZipFileHandle		= _null;
	mUnzipFileHandle	= _null;
#elif defined(_USE_LIBZIP_SDK_)
	mZipSource			= _null;
	mZip				= _null;
#endif
}

ZIPFile::~ZIPFile( )
{
	Unload( );
}

WString ZIPFile::FixFileName( WStringPtr file_name ) const
{
	WString fixed_file_name = file_name;

	if ( HasFlags( _FLAG_USE_FILE_NAME_ONLY ) )
	{
		fixed_file_name = Path::GetFileName( file_name, _true );
		
		// Remove '@' suffix name
		_dword index = fixed_file_name.SearchL2R( L"@" );
		if ( index != -1 )
		{
			_dword extension_index = fixed_file_name.SearchR2L( L"." );
			if ( extension_index != -1 )
				fixed_file_name.Remove( index, extension_index - index );
			else
				fixed_file_name.Remove( index );
		}
	}
	else
	{
		fixed_file_name = file_name;
	}

	fixed_file_name.ReplaceAll( '\\', '/' );

	return fixed_file_name;
}

_ubool ZIPFile::BuildItemsFromZIP( )
{
	mItems.Clear( );

#if defined(_USE_LITE_ZIP_SDK_)
	// Find out how many items are in the archive.
	ZipEntry ze = {0};
	if ( ::UnzipGetFirstItemW( mUnzipFileHandle, &ze ) != ZR_OK )
		return _false;

	// Unzip each item, using the name stored (in the zip) for that item.
	do
	{
		// Skip directory
#if defined(_PLATFORM_WINDOWS_)
		if ( ze.Attributes & FILE_ATTRIBUTE_DIRECTORY )
			continue;
#endif

		// Get the file name
		WString filename = FixFileName( ((const _charw*)ze.Name) + 1 );

		// Add item
		mItems.InsertAscending( ItemInfo( filename, ze ) );

	} while ( ::UnzipGetNextItemW( mUnzipFileHandle, &ze ) == ZR_OK );
#elif defined(_USE_LIBZIP_SDK_)
	_dword number = (_dword)zip_get_num_entries( mZip, 0 );
	for ( _dword i = 0; i < number; i ++ )
	{
		const zip_entry& entry = mZip->entry[i];

		// Skip directory or empty file
		if ( entry.orig->uncomp_size == 0 )
			continue;

		// Get the file name
		WString filename = FixFileName( WString( ).FromString( _ENCODING_UTF8, entry.orig->filename->raw ) );

		// ADd item
		mItems.InsertAscending< WStringPtr >( ItemInfo( filename, entry ) );
	}
#endif

	return _true;
}

#if defined(_USE_LITE_ZIP_SDK_)

IStreamReaderPassRef ZIPFile::GetItemStream( ZipEntry& zip_entry )
{
	LockOwner lock_owner( mLocker );

	// The item buffer data and its size
	_dword size		= 0;
	_byte* buffer	= _null;

	// Set the current entry
	if ( ::UnzipSetCurItemW( mUnzipFileHandle, &zip_entry ) != ZR_OK )
		return _null;

	// Get the file buffer data
	size = zip_entry.UncompressedSize; buffer = new _byte[ size ];
	if ( ::UnzipItemToBuffer( mUnzipFileHandle, buffer, size, &zip_entry ) != ZR_OK )
	{ 
		EGE_DELETE_ARRAY( buffer ); 
		return _null; 
	}

	return GetInterfaceFactory( )->CreateMemStreamReader( buffer, size, _STREAM_SHARE_MODE_MANAGED );
}

#elif defined(_USE_LIBZIP_SDK_)

IStreamReaderPassRef ZIPFile::GetItemStream( const ZipEntry& zip_entry, _dword index )
{
	// The item buffer data and its size
	_dword size		= 0;
	_byte* buffer	= _null;

	// Open item
	zip_file* file = zip_fopen_index( mZip, index, ZIP_FL_UNCHANGED );
	if ( file == _null )
	{
		ALOG_ERROR_1( "Open the '%s' from ZIP file failed", (const _chara*)zip_entry.orig->filename->raw );
		return _null;
	}

	size = (_dword)zip_entry.orig->uncomp_size; buffer = new _byte[size];
	_dword read_size = (_dword)zip_source_read( file->src, buffer, size );
	if ( read_size != size )
	{
		EGE_DELETE_ARRAY( buffer );
		ALOG_ERROR_1( "Get the '%s' from ZIP file failed", (const _chara*)zip_entry.orig->filename->raw );
		return _null;
	}

	return GetInterfaceFactory( )->CreateMemStreamReader( buffer, size, _STREAM_SHARE_MODE_MANAGED );
}

#endif

_ubool ZIPFile::CreateFile( WStringPtr filename )
{
#if defined(_USE_LITE_ZIP_SDK_)
	// Create the zip file
	if ( ::ZipCreateFileA( &mZipFileHandle, AString( ).FromString( filename ).Str( ), mPassword.Str( ) ) != ZR_OK )
		return _false;
#elif defined(_USE_LIBZIP_SDK_)
	_int err = ZIP_ET_NONE;
	mZip = zip_open( AString( ).FromString( filename ).Str( ), ZIP_CREATE, &err );
	if ( mZip == _null )
	{
		WLOG_ERROR_2( L"Create '%s' ZIP file failed(err: %d)", filename.Str( ), err );
		return _false;
	}
#endif

	return _true;
}

_FILE_FORMAT ZIPFile::GetFileID( ) const
{
	return _FF_ZIP;
}

_ubool ZIPFile::LoadFromStream( IStreamReader* stream_reader )
{
	// Get the password
	const _chara* password = mPassword.IsEmpty( ) ? _null : mPassword.Str( );

	// Load from file stream
	if ( stream_reader->GetType( ) == _STREAM_TYPE_FILE )
	{
		// Get file stream reader
		IFileStreamReader* file_stream_reader = static_cast< IFileStreamReader* >( stream_reader );
		EGE_ASSERT( file_stream_reader != _null );

		// Get the file name
		WStringPtr filename = file_stream_reader->GetFileName( );
		if ( filename.IsEmpty( ) )
			return _false;

#if defined(_USE_LITE_ZIP_SDK_)
		if ( ::UnzipOpenFileW( &mUnzipFileHandle, (const WCHAR*)filename.Str( ), password ) != ZR_OK )
			return _false;

		if ( ::UnzipSetBaseDirW( mUnzipFileHandle, (const WCHAR*)L"" ) != ZR_OK )
			return _false;
#elif defined(_USE_LIBZIP_SDK_)
		zip_error err = {0};
		mZipSource = zip_source_file_create( AString( ).FromString( filename ).Str( ), 0, -1, &err );
		if ( mZipSource == _null )
		{
			WLOG_ERROR_2( L"Load the '%s' from ZIP file failed(%s)", filename.Str( ), GetLIBZIPErrString( err ).Str( ) );
			return _false;
		}

		mZip = zip_open_from_source( mZipSource, 0, &err );
		if ( mZip == _null )
		{
			WLOG_ERROR_2( L"Open the '%s' from ZIP source(file) failed(%s)", filename.Str( ), GetLIBZIPErrString( err ).Str( ) );
			return _false;
		}

		if ( password != _null )
			zip_set_default_password( mZip, password );
#endif
	}
	// Load from memory stream
	else
	{
#if defined(_USE_LITE_ZIP_SDK_)
		if ( ::UnzipOpenBuffer( &mUnzipFileHandle, (_void*) stream_reader->GetBuffer( ), stream_reader->GetSize( ), password ) != ZR_OK )
			return _false;
#elif defined(_USE_LIBZIP_SDK_)
		zip_error err = {0};
		mZipSource = zip_source_buffer_create( (const _void*) stream_reader->GetBuffer( ), stream_reader->GetSize( ), 0, &err );
		if ( mZipSource == _null )
		{
			WLOG_ERROR_1( L"Load the ZIP from stream failed(%s)", GetLIBZIPErrString( err ).Str( ) );
			return _false;
		}

		mZip = zip_open_from_source( mZipSource, 0, &err );
		if ( mZip == _null )
		{
			WLOG_ERROR_1( L"Open the ZIP from source(stream) failed(%s)", GetLIBZIPErrString( err ).Str( ) );
			return _false;
		}
#endif
	}

	// Check whether need to build items
	if ( HasFlags( _FLAG_SKIP_TO_BUILD_ITEMS ) == _false )
	{
		if ( BuildItemsFromZIP( ) == _false )
			return _false;
	}

	return _true;
}

_void ZIPFile::Unload( )
{
#if defined(_USE_LITE_ZIP_SDK_)
	// Close the zip file handle
	if ( mZipFileHandle != _null )
	{
		::ZipClose( mZipFileHandle );
		mZipFileHandle = _null;
	}

	// Close the unzip file handle
	if ( mUnzipFileHandle != _null )
	{
		::UnzipClose( mUnzipFileHandle );
		mUnzipFileHandle = _null;
	}
#elif defined(_USE_LIBZIP_SDK_)
	if ( mZip != _null )
	{
		zip_close( mZip );
		mZip = _null;
	}

	if ( mZipSource != _null )
	{
		zip_source_close( mZipSource );
		mZipSource = _null;
	}
#endif
}

_float ZIPFile::GetCompressionRatio( ) const
{
	return 0.99f;
}

_ubool ZIPFile::AddFile( WStringPtr filename )
{
	return AddFile( filename, filename );
}

_ubool ZIPFile::AddFile( WStringPtr filename, WStringPtr filename_in_zip ) 
{
	LockOwner lock_owner( mLocker );

#if defined(_USE_LITE_ZIP_SDK_)
	// Open the file in zip file
	if ( ::ZipAddFileA( mZipFileHandle, AString( ).FromString( filename_in_zip ).Str( ), AString( ).FromString( filename ).Str( ) ) != ZR_OK )
		return _false;
#elif defined(_USE_LIBZIP_SDK_)
	zip_error err = {0};
	zip_source* zip_source = zip_source_file_create( AString( ).FromString( filename ).Str( ), 0, -1, &err );
	if ( zip_source == _null )
	{
		WLOG_ERROR_2( L"Create '%s' as ZIP source failed(%s)", filename.Str( ), GetLIBZIPErrString( err ).Str( ) );
		return _false;
	}

	if ( zip_file_add( mZip, AString( ).FromString( filename_in_zip ).Str( ), zip_source, 0 ) != 0 )
	{
		WLOG_ERROR_3( L"Add '%s->%s' into ZIP file failed(%s)", filename.Str( ), filename_in_zip.Str( ), GetLIBZIPErrString( err ).Str( ) );
		return _false;
	}
#endif

	return _true;
}

_ubool ZIPFile::AddFolder( WStringPtr dir_path, WStringPtr filter, _dword flags, _dword depth )
{
	return AddFolder( dir_path, Path::GetFileName( dir_path ), filter, flags, depth );
}

_ubool ZIPFile::HasFile( WStringPtr filename ) const
{
	// We have not items info
	if ( mItems.Number( ) == 0 )
	{
		LockOwner lock_owner( mLocker );

		// Get the file name in ANSI format
		AString filename_ansi = AString( ).FromString( filename );

#if defined(_USE_LITE_ZIP_SDK_)
		// Build file entry info
		ZipEntry file_entry = {0};
		::SafeCopyString( file_entry.Name, filename_ansi.Str( ) );

		// Get the file
		if ( ::UnzipFindItemA( mUnzipFileHandle, &file_entry, _false ) != Z_OK )
			return _false;

#elif defined(_USE_LIBZIP_SDK_)
		_dword number = (_dword)zip_get_num_entries( mZip, 0 );
		for ( _dword i = 0; i < number; i ++ )
		{
			const ZipEntry& entry = mZip->entry[i];

			// Skip directory or empty file
			if ( entry.orig->uncomp_size == 0 )
				continue;

			// Get the file name
			if ( filename_ansi != (const _chara*)entry.orig->filename->raw )
				continue;

			return _true;
		}
#endif
	}
	// Search from items
	else
	{
		// Get the item info
		ItemInfoArray::Iterator it = mItems.SearchAscending( filename );
		if ( it.IsValid( ) == _false )
			return _false;
	}

	return _true;
}

IStreamReaderPassRef ZIPFile::GetFile( WStringPtr filename )
{
	// We have not items info
	if ( mItems.Number( ) == 0 )
	{
		LockOwner lock_owner( mLocker );

		// Get the file name in ANSI format
		AString filename_ansi = AString( ).FromString( filename );

#if defined(_USE_LITE_ZIP_SDK_)
		// Build file entry info
		ZipEntry file_entry = {0};
		::SafeCopyString( file_entry.Name, filename_ansi.Str( ) );

		// Get the file
		if ( ::UnzipFindItemA( mUnzipFileHandle, &file_entry, _false ) != Z_OK )
		{
			ALOG_ERROR_1( "Get the '%s' from the ZIP file failed", filename_ansi.Str( ) );
			return _null;
		}

		return GetItemStream( file_entry );
#elif defined(_USE_LIBZIP_SDK_)
		_dword number = (_dword)zip_get_num_entries( mZip, 0 );
		for ( _dword i = 0; i < number; i ++ )
		{
			const ZipEntry& entry = mZip->entry[i];

			// Skip directory or empty file
			if ( entry.orig->uncomp_size == 0 )
				continue;

			// Get the file name
			if ( filename_ansi != (const _chara*)entry.orig->filename->raw )
				continue;

			return GetItemStream( entry, i );
		}

		WLOG_ERROR_1( L"Get the '%s' from the ZIP file failed", filename.Str( ) );
		return _null;
#endif
	}
	// Search from items
	else
	{
		// Get the item info
		ItemInfoArray::Iterator it = mItems.SearchAscending( filename );
		if ( it.IsValid( ) == _false )
			return _null;

		ItemInfo& item_info = it.GetObject( );

#if defined(_USE_LITE_ZIP_SDK_)
		return GetItemStream( item_info.mEntry );
#elif defined(_USE_LIBZIP_SDK_)
		return GetItemStream( item_info.mEntry, it.mIndex );
#endif
	}
}

_ubool ZIPFile::AddFolder( WStringPtr dir_path, WStringPtr dir_path_in_zip, WStringPtr filter, _dword flags, _dword depth )
{
	// Open the directory
	FileFinder file_finder;
	if ( file_finder.Open( dir_path ) == _false )
		return _false;

	// Walk directory to add files
	FileInfo file_info;
	while ( file_finder.Walk( file_info, filter, flags, depth ) )
	{
		// Skip the directory
		if ( file_info.mAttributes & _FILE_ATTRIBUTE_DIRECTORY )
			continue;

		if ( AddFile( file_info.mAbsolutePath, Path::BuildFilePath( dir_path_in_zip, file_info.mRelativePath ) ) == _false )
			return _false;
	}

	return _true;
}

_dword ZIPFile::GetFileNumber( ) const
{
	return mItems.Number( );
}

WStringPtr ZIPFile::GetFileNameByIndex( _dword index )
{
	if ( index >= mItems.Number( ) )
		return L"";

	return (WStringPtr) mItems[index];
}

IStreamReaderPassRef ZIPFile::GetFileStreamByIndex( _dword index )
{
	if ( index >= mItems.Number( ) )
		return _null;

	ItemInfo& item_info = mItems[index];

#if defined(_USE_LITE_ZIP_SDK_)
	return GetItemStream( item_info.mEntry );
#elif defined(_USE_LIBZIP_SDK_)
	return GetItemStream( item_info.mEntry, index );
#endif
}
