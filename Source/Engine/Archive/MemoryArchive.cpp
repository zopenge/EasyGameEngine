//! @file     MemoryArchive.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// MemoryArchive Implementation
//----------------------------------------------------------------------------

MemoryArchive::MemoryArchive( )
{
	mMD5Code = MD5Code::cNull;
}

MemoryArchive::~MemoryArchive( )
{
	mFileCopier.Clear( );
}

WString MemoryArchive::GetArchiveFileNameFromDocument( WStringPtr name )
{
	// Get the document path
	_charw document_path[1024] = {0};
	Platform::GetDocumentPathInDomains( document_path, 1024 );

	// Build the file path in document
	WString rootpath = Path::BuildFilePath( document_path, Path::BuildFilePath( L"archive", name ) );
	WString filepath = Path::BuildFilePath( rootpath, mMD5Code.ToWString( _false ) );

	return filepath;
}

IStreamReaderRef MemoryArchive::GetArchiveStreamReader( WStringPtr name, IStreamReader* stream_reader )
{
	// Get the MD5 code
	if ( GetInterfaceFactory( )->BuildMD5CodeFromStream( stream_reader, mMD5Code ) == _false )
		return _null;

	// In android platform, we try to load it from real file(NOT in asset), it can drop down the memory usage
	if ( Platform::GetPlatformType( ) == _PLATFORM_TYPE_ANDROID )
	{
		// The archive stream
		IStreamReaderRef archive_stream_reader;

		// Get the archive file name from document
		WString filepath = GetArchiveFileNameFromDocument( name );
		EGE_ASSERT( filepath.IsEmpty( ) == _false );

		// Try to load archive stream from document
		IFileStreamReaderRef stream_reader_in_document = GetInterfaceFactory( )->CreateFileStreamReader( filepath );
		if ( stream_reader_in_document.IsValid( ) )
		{
			// We already have the existing archive in document, just load it to reduce memory usage
			archive_stream_reader = stream_reader_in_document;

			WLOG_TRACE_1( L"Load '%s' memory archive from document OK", filepath.Str( ) );
		}
		else
		{
			// Remove all temporary files in document
			FileSystem::CleanDir( Path::GetDirectoryName( filepath ) );

			// Use the safe stream reader to read in file copier
			archive_stream_reader = GetInterfaceFactory( )->CreateSafeStreamReader( stream_reader );
			if ( archive_stream_reader.IsNull( ) )
				return _null;

			// We do not have the existing archive in document, now we need to create a thread to copy archive to document (optional)
			mFileCopier = GetInterfaceFactory( )->CreateFileCopier( );
			if ( mFileCopier.IsValid( ) )
			{
				if ( mFileCopier->Start( 16 KB, mMD5Code, archive_stream_reader, filepath ) )
				{
					WLOG_TRACE_1( L"Start '%s' file copier of memory archive OK", filepath.Str( ) );
				}
				else
				{
					WLOG_ERROR_1( L"Start '%s' file copier of memory archive failed", filepath.Str( ) );
				}
			}
		}

		return archive_stream_reader;
	}
	else
	{
		return stream_reader;
	}
}

_ubool MemoryArchive::LoadManifestFile( WStringPtr manifest_filename, _ENCRYPTION manifest_encryption_type, WStringPtr manifest_encryption_key )
{
	// Check whether do we have manifest file in archive
	if ( HasResourceByPath( manifest_filename ) == _false )
		return _false;

	// Load manifest file in the root path
	IStreamReaderRef stream_reader = LoadResourceByPath( manifest_filename );
	if ( stream_reader.IsNull( ) )
		return _false;

	// Parse and decrypt it
	if ( manifest_encryption_type == _ENCRYPTION_UNKNOWN && manifest_encryption_key == L"" )
		mManifestFile = GetInterfaceFactory( )->ParseManifestFile( stream_reader );
	else
		mManifestFile = GetInterfaceFactory( )->ParseManifestFile( stream_reader, manifest_encryption_type, manifest_encryption_key );

	if ( mManifestFile.IsNull( ) )
		return _false;

	return _true;
}

_ubool MemoryArchive::Initialize( WStringPtr name, IStreamReader* stream_reader, WStringPtr password, _ENCRYPTION manifest_encryption_type, WStringPtr manifest_encryption_key )
{
	if ( stream_reader == _null )
		return _false;

	// Get the archive stream
	IStreamReaderRef archive_stream_reader = GetArchiveStreamReader( name, stream_reader );
	if ( archive_stream_reader.IsNull( ) )
		return _false;

	// Get the file ID from stream
	_dword file_id = 0;
	archive_stream_reader->PeekBuffer( &file_id, 4 );

	// It's 7Z file
	if ( file_id == EGE_ID( '7', 'z', 0xBC, 0xAF ) )
		mZIPFile = GetInterfaceFactory( )->Parse7zFile( archive_stream_reader, password, IZIPFile::_FLAG_USE_FILE_NAME_ONLY );
	// It's ZIP file
	else if ( file_id == EGE_ID( 0x50, 0x4B, 0x03, 0x04 ) )
		mZIPFile = GetInterfaceFactory( )->ParseZipFile( archive_stream_reader, password, IZIPFile::_FLAG_USE_FILE_NAME_ONLY );

	// Check archive file
	if ( mZIPFile.IsNull( ) )
		return _false;

	// Try to load manifest file to update manifest file manager info
	if ( LoadManifestFile( L"manifest.xml", manifest_encryption_type, manifest_encryption_key ) == _false )
		return _false;

	// Create manifest file manager and combine it
	mManifestFileManager = GetInterfaceFactory( )->CreateManifestFileManager( );
	if ( mManifestFileManager.IsNull( ) )
		return _false;

	if ( mManifestFileManager->LoadManifestFile( mManifestFile ) == -1 )
	{
		WLOG_ERROR( L"Load manifest file into manager failed" );
		return _false;
	}

	return _true;
}

WStringPtr MemoryArchive::GetPath( ) const
{
	return L"";
}

const MD5Code& MemoryArchive::GetMD5Code( ) const
{
	return mMD5Code;
}

const IManifestFile* MemoryArchive::GetManifestFile( ) const
{
	return mManifestFile;
}

_ubool MemoryArchive::HasResourceByPath( WStringPtr file_name ) const
{
	if ( mZIPFile->HasFile( file_name ) == _false )
		return _false;

	return _true;
}

IStreamReaderPassRef MemoryArchive::LoadResourceByPath( WStringPtr file_name )
{
	// Try to load from patch archives
	IStreamReaderPassRef stream_reader = BaseClass::LoadResourceByPath( file_name );
	if ( stream_reader.IsValid( ) )
		return stream_reader;

	// Get the resource name
	WString res_name = Path::GetFileName( file_name, _true );

	// Get the file stream
	IStreamReaderPassRef mem_stream_reader = mZIPFile->GetFile( res_name );
	if ( mem_stream_reader.IsValid( ) )
		return mem_stream_reader;

	WLOG_ERROR_1( L"Load '%s' resource from memory archive failed", file_name.Str( ) );
	return _null;
}
