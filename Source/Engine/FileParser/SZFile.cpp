//! @file     SZFile.cpp
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#include "EGEEngine.h"

ISzAlloc	SZFile::sAllocImp		= {0};
ISzAlloc	SZFile::sAllocImpTemp	= {0};

//----------------------------------------------------------------------------
// SZFile Implementation
//----------------------------------------------------------------------------

SZFile::SZFile( WStringPtr password )
{
	mCompressionRatio			= 1.0f;

	mDecompressionBufferData	= _null;

	mPassword.FromString( password );

	mArchiveStream.mSZReader.Read = SZFile::FileInStream_Read;
	mArchiveStream.mSZReader.Seek = SZFile::FileInStream_Seek;

	::LookToRead_CreateVTable( &mLookStream, False);
	::SzArEx_Init( &mArchive );
}

SZFile::~SZFile( )
{
	Unload( );
}

_void* SZFile::OnMemAlloc( _void*, size_t size )
{
	if ( size == 0 )
		return _null;

	return ::malloc( size );
}

_void SZFile::OnMemFree( _void*, _void* address )
{
	if ( address == _null )
		return;

	::free( address );
}

_ubool SZFile::InitArchive( )
{
	mLookStream.realStream = &mArchiveStream.mSZReader;
	::LookToRead_Init( &mLookStream );

	// load 7z archive
	SRes res = SzArEx_Open( &mArchive, &mLookStream.s, &sAllocImp, &sAllocImpTemp );
	if ( res != SZ_OK )
	{
		WLOG_ERROR_1( L"Open 7Z stream failed (err: %d)", (_dword)res );
		return _false;
	}

	return _true;
}

WString SZFile::FixFileName( WStringPtr file_name ) const
{
	WString fixed_file_name;

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

	return fixed_file_name;
}

_ubool SZFile::LoadFileItem( FileInfo& file_info, _byte*& out_buffer, size_t out_buffer_size )
{
	UInt32 block_index			= mArchive.FileIndexToFolderIndexMap[ file_info.mIndex ];
	size_t offset				= 0;
	size_t out_size_processed	= 0;

	SRes res = ::SzArEx_Extract( &mArchive, &mLookStream.s, file_info.mIndex, &block_index, &out_buffer, &out_buffer_size, &offset, &out_size_processed, &sAllocImp, &sAllocImpTemp );
	if ( res != SZ_OK )
		return _false;

	file_info.mStream = GetInterfaceFactory( )->CreateMemStreamReader( out_buffer + offset, (_dword)out_size_processed, _STREAM_SHARE_MODE_READ_ONLY );
	if ( file_info.mStream.IsNull( ) )
		return _false;

	return _true;
}

_ubool SZFile::Initialize( )
{
	sAllocImp.Alloc		= OnMemAlloc;
	sAllocImp.Free		= OnMemFree;
	sAllocImpTemp.Alloc = OnMemAlloc;
	sAllocImpTemp.Free	= OnMemFree;

	// global crc code
	::CrcGenerateTable( );

	return _true;
}

_void SZFile::Finalize( )
{

}

_ubool SZFile::CreateFile( WStringPtr filename )
{
// 	if ( ::InFile_Open( &mArchiveStream.file, AString( ).FromString( filename ).Str( ) ) )
// 	{
// 		WLOG_ERROR_1( L"7Z Open %s Failed", filename.Str( ) );
// 		return _false;
// 	}
// 
// 	if ( InitArchive( ) == _false )
// 	{
// 		WLOG_ERROR_1( L"7Z Init %s Failed", filename.Str( ) );
// 		return _false;
// 	}

	return _true;
}

_FILE_FORMAT SZFile::GetFileID( ) const
{
	return _FF_7Z;
}

_ubool SZFile::LoadFromStream( IStreamReader* stream_reader )
{
	mArchiveStream.mStreamReader = stream_reader;

	// Initialize archive
	if ( InitArchive( ) == _false )
	{
		WLOG_ERROR( L"7Z Init Failed" );
		return _false;
	}
	
	// Check do we have any resources
	if ( mArchive.db.Folders == _null )
	{
		WLOG_ERROR( L"7Z is empty" );
		return _false;
	}

	// Get the unpacked size
	_qword unpacked_size = *mArchive.db.Folders->UnpackSizes;
	if ( unpacked_size == 0 )
	{
		WLOG_ERROR( L"7Z unpacked size is 0" );
		return _false;
	}

	// Get the packed size
	_qword packed_size = *mArchive.db.PackSizes;
	if ( packed_size == 0 )
	{
		WLOG_ERROR( L"7Z packed size is 0" );
		return _false;
	}

	// Update compression ratio
	mCompressionRatio = (_float)EGE_RATIO_DOUBLE( packed_size, unpacked_size );
	
	// Fit the file items best
	mFileItems.Resize( mArchive.db.NumFiles );

	// The file item name buffer
	_charw file_item_name_buf[512] = {0};

	// Build the file items
	for ( _dword i = 0; i < mArchive.db.NumFiles; i ++ )
	{
		// Skip directory item
		const CSzFileItem *f = mArchive.db.Files + i;
		if ( f->IsDir )
			continue;

		// Get the file name
		::SzArEx_GetFileNameCharW( &mArchive, i, file_item_name_buf );

		// Build the file info
		FileInfo file_info;
		file_info.mIndex	= i;
		file_info.mFileName = FixFileName( file_item_name_buf );

		// Insert file info
		mFileItems.InsertAscending< WStringPtr >( file_info );
	}

	// Load all resources in compressed mode
	if ( mCompressionRatio != 1.0f )
	{
		WLOG_TRACE_1(L"Start to decode items from 7z, due to compression ratio is '%f'", mCompressionRatio);

		size_t out_buffer_size = (size_t) *mArchive.db.Folders->UnpackSizes;
		if ( out_buffer_size == 0 )
			return _false;

		for ( _dword i = 0; i < mFileItems.Number( ); i ++ )
		{
			FileInfo& file_info = mFileItems[i];

			if ( LoadFileItem( file_info, mDecompressionBufferData, out_buffer_size ) == _false )
			{
				WLOG_ERROR_1( L"Load '%s' file item from 7Z failed", file_info.mFileName.Str( ) );
				return _false;
			}
		}
	}

	return _true;
}

_void SZFile::Unload( )
{
	if ( mDecompressionBufferData != _null )
	{
		IAlloc_Free( &sAllocImp, mDecompressionBufferData );
		mDecompressionBufferData = _null;
	}

	::SzArEx_Free( &mArchive, &sAllocImp );
}

_float SZFile::GetCompressionRatio( ) const
{
	return mCompressionRatio;
}

_ubool SZFile::AddFile( WStringPtr filename )
{
	return _false;
}

_ubool SZFile::AddFile( WStringPtr filename, WStringPtr filename_in_zip ) 
{
	return _false;
}

_ubool SZFile::HasFile( WStringPtr filename ) const
{
	FileInfoArray::Iterator it = mFileItems.SearchAscending( filename );
	if ( it.IsValid( ) == _false )
		return _false;

	return _true;
}

IStreamReaderPassRef SZFile::GetFile( WStringPtr filename )
{
	FileInfoArray::Iterator it = mFileItems.SearchAscending( filename );
	if ( it.IsValid( ) == _false )
		return _null;

	return GetFileStreamByIndex( it.mIndex );
}

_ubool SZFile::AddFolder( WStringPtr dir_path, WStringPtr filter, _dword flags, _dword depth )
{
	return _false;
}

_ubool SZFile::AddFolder( WStringPtr dir_path, WStringPtr dir_path_in_zip, WStringPtr filter, _dword flags, _dword depth )
{
	return _false;
}

_dword SZFile::GetFileNumber( ) const
{
	return mFileItems.Number( );
}

WStringPtr SZFile::GetFileNameByIndex( _dword index )
{
	return mFileItems[index].mFileName;
}

IStreamReaderPassRef SZFile::GetFileStreamByIndex( _dword index ) 
{
	LockOwner lock_owner( mLocker );

	// Get the file info
	FileInfo& file_info = mFileItems[index];

	// It's un-compressed archive
	if ( mCompressionRatio == 1.0f )
	{
		_byte* out_buffer = _null;
		if ( LoadFileItem( file_info, out_buffer, 0 ) == _false )
			return _null;

		// Copy the stream reader
		IStreamReaderPassRef stream_reader = file_info.mStream->CloneToPassRef< IStreamReader >( _true );
		if ( stream_reader.IsNull( ) )
			return _null;

		// Get the allocated buffer data
		_byte* buffer = (_byte*) file_info.mStream->GetBuffer( );
		EGE_ASSERT( buffer != _null );

		// Free it
		IAlloc_Free( &sAllocImp, buffer );

		// Clear stream of file
		file_info.mStream.Clear( );

		return stream_reader;
	}
	// It's compressed archive
	else
	{
		// Get the item stream
		IStreamReaderRef item_stream_reader = file_info.mStream;
		if ( item_stream_reader.IsNull( ) )
			return _null;

		// Get the stream buffer and size
		const _byte*	buffer_data	= item_stream_reader->GetBuffer( );
		_dword			buffer_size	= item_stream_reader->GetSize( );

		// Create the stream reader
		IStreamReaderPassRef stream_reader = GetInterfaceFactory( )->CreateMemStreamReader( buffer_data, buffer_size, _STREAM_SHARE_MODE_READ_ONLY );
		if ( stream_reader.IsNull( ) )
			return _null;

		return stream_reader;
	}
}

SRes SZFile::FileInStream_Read( void *pp, void *buf, size_t *size )
{
	SZStreamReader *p = (SZStreamReader *) pp;
	if ( p->mStreamReader->ReadBuffer( buf, *size ) == 0 )
		return SZ_ERROR_READ;
	return SZ_OK;
}

SRes SZFile::FileInStream_Seek( void *pp, Int64 *pos, ESzSeek origin )
{
	SZStreamReader *p = (SZStreamReader *) pp;
	switch ( origin )
	{
	case SZ_SEEK_CUR:
		*pos = p->mStreamReader->Seek( _SEEK_CURRENT, (_int)*pos );
		break;
	case SZ_SEEK_END:
		*pos = p->mStreamReader->Seek( _SEEK_END, (_int)*pos );
		break;
	case SZ_SEEK_SET:
		*pos = p->mStreamReader->Seek( _SEEK_BEGIN, (_int)*pos );
		break;
	}
	return SZ_OK;
}
