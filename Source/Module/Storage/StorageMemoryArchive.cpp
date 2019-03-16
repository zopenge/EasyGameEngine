//! @file     StorageMemoryArchive.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEStorage.h"

//----------------------------------------------------------------------------
// StorageMemoryArchive Implementation
//----------------------------------------------------------------------------

StorageMemoryArchive::StorageMemoryArchive( WStringPtr path ) : BaseClass( _ARCHIVE_MEMORY, path )
{
}

StorageMemoryArchive::~StorageMemoryArchive( )
{
}

IFileStreamReaderRef StorageMemoryArchive::LoadCompressedFileFromDocument( WStringPtr filename, const MD5Code& md5_code, IStreamReader* stream_reader )
{
	// Get the document path
	_charw document_path[1024] = {0};
	Platform::GetDocumentPathInDomains( document_path, 1024 );

	// Build the file path in document
	WString rootpath = Path::BuildFilePath( document_path, Path::BuildFilePath( L"archive", filename ) );
	WString filepath = Path::BuildFilePath( rootpath, md5_code.ToWString( _false ) );

	// If the file is existing then skip to create it
	if ( FileSystem::IsFileExist( filepath ) == _false )
	{
		// Remove all temporary files in document
		FileSystem::CleanDir( rootpath );

		// Create file in document
		if ( FileSystem::CreateFile( filepath, stream_reader->GetSize( ), stream_reader->GetBuffer( ) ) == _false )
			return _null;
	}

	// Open file stream
	return GetInterfaceFactory( )->CreateFileStreamReader( filepath );
}

IStreamReaderPassRef StorageMemoryArchive::OnLoadResource( WStringPtr filename )
{
	// Get the resource name
	WString res_name = Path::GetFileName( filename, _true );
	
	// Get the file stream
	IStreamReaderPassRef res_stream	= mZIPFile->GetFile( res_name );
	if ( res_stream.IsNull( ) )
		return _null;

	return res_stream;
}

IStreamWriterPassRef StorageMemoryArchive::OnCreateResource( WStringPtr filename, _dword size )
{
	return _null;
}

_ubool StorageMemoryArchive::Initialize( WStringPtr password, WStringPtr module_name )
{
	// Get the archive file name
	WString filename = mPath;
	if ( filename.IsEmpty( ) )
		return _false;

	// Open the archive file from working archive
	IStreamReaderRef stream_reader = GetStorageWorkingArchive( )->LoadResource( filename );
	if ( stream_reader.IsNull( ) )
	{
		WLOG_ERROR_1( L"Initialize memory archive failed, '%s' is not existing in working archive", filename.Str( ) );
		return _false;
	}

	// Get the MD5 code
	if ( GetInterfaceFactory( )->BuildMD5Code( stream_reader, mMD5Code ) == _false )
	{
		WLOG_ERROR_1( L"Build MD5 code of '%s' memory archive failed", filename.Str( ) );
		return _false;
	}

	// Get the extension name
	WString extension_name = Path::GetExtension( filename );

	// Parse archive file
	if ( extension_name == L"7z" )
	{
		IFileStreamReaderRef stream_reader_in_document = LoadCompressedFileFromDocument( filename, mMD5Code, stream_reader );
		if ( stream_reader_in_document.IsValid( ) )
			mZIPFile = GetInterfaceFactory( )->Parse7zFile( stream_reader_in_document, password, IZIPFile::_FLAG_USE_FILE_NAME_ONLY );
		else
			mZIPFile = GetInterfaceFactory( )->Parse7zFile( stream_reader, password, IZIPFile::_FLAG_USE_FILE_NAME_ONLY );
	}
	else if ( extension_name == L"zip" )
	{
		IFileStreamReaderRef stream_reader_in_document = LoadCompressedFileFromDocument( filename, mMD5Code, stream_reader );
		if ( stream_reader_in_document.IsValid( ) )
			mZIPFile = GetInterfaceFactory( )->ParseZipFile( stream_reader_in_document, password, IZIPFile::_FLAG_USE_FILE_NAME_ONLY );
		else
			mZIPFile = GetInterfaceFactory( )->ParseZipFile( stream_reader, password, IZIPFile::_FLAG_USE_FILE_NAME_ONLY );
	}

	// Check archive file
	if ( mZIPFile.IsNull( ) )
	{
		WLOG_ERROR_2( L"Initialize memory archive failed, Parse '%s' as *.%s failed", filename.Str( ), extension_name.Str( ) );
		return _false;
	}

	return _true;
}

_ubool StorageMemoryArchive::EnumResources( OnWalkItem walk_item_func, WStringPtr path, WStringPtr filter, _dword flags, _dword depth, const QwordParameters2& parameters )
{
	return _false;
}

IManifestFilePassRef StorageMemoryArchive::LoadManifestFile( _ENCRYPTION manifest_encryption_type, WStringPtr manifest_encryption_key )
{
	// Open the manifest file stream
	IStreamReaderRef manifest_stream_reader = mZIPFile->GetFile( L"manifest.xml" );
	if ( manifest_stream_reader.IsNull( ) )
	{
		WLOG_ERROR_1( L"The '%s' memory archive's manifest file is missing", mPath.Str( ) );
		return _null;
	}

	// Parse the manifest file
	IManifestFilePassRef manifest_file = GetInterfaceFactory( )->ParseManifestFile( manifest_stream_reader, manifest_encryption_type, AString( ).FromString( manifest_encryption_key ) );
	if( manifest_file.IsNull( ) )
	{
		WLOG_ERROR_1( L"The '%s' memory archive's manifest file is invalid", mPath.Str( ) );
		return _null;
	}

	return manifest_file;
}
