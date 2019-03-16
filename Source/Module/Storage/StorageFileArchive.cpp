//! @file     StorageFileArchive.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEStorage.h"

//----------------------------------------------------------------------------
// StorageFileArchive Implementation
//----------------------------------------------------------------------------

StorageFileArchive::StorageFileArchive( WStringPtr path ) : BaseClass( _ARCHIVE_FILE, path )
{
}

StorageFileArchive::~StorageFileArchive( )
{
}

IStreamReaderPassRef StorageFileArchive::OnLoadResource( WStringPtr filename )
{
	// The file stream reader
	StorageFileStreamReader* stream_reader = new StorageFileStreamReader( );

	// Open the file by absolute path
	if ( Path::IsPathRooted( filename ) && FileSystem::IsFileExist( filename ) )
	{
		if ( stream_reader->Initialize( L"", filename ) == _false )
			{ EGE_RELEASE( stream_reader ); return _null; }
	}
	// Open the file by relative path
	else
	{
		if ( stream_reader->Initialize( GetPath( ), filename ) == _false )
			{ EGE_RELEASE( stream_reader ); return _null; }
	}

	return stream_reader;
}

IStreamWriterPassRef StorageFileArchive::OnCreateResource( WStringPtr filename, _dword size )
{
	StorageFileStreamWriter* stream_writer = new StorageFileStreamWriter( );
	if ( stream_writer->Initialize( GetPath( ), filename ) == _false )
		{ EGE_RELEASE( stream_writer ); return _null; }

	return stream_writer;
}

_ubool StorageFileArchive::Initialize( WStringPtr password, WStringPtr module_name )
{
	return _true;
}

_ubool StorageFileArchive::EnumResources( OnWalkItem walk_item_func, WStringPtr path, WStringPtr filter, _dword flags, _dword depth, const QwordParameters2& parameters )
{
	if ( walk_item_func == _null )
		return _false;

	// Locate directory
	FileFinder file_finder;
	if ( file_finder.Open( BuildFullPath( path ) ) == _false )
		return _false;

	// Start to walk
	FileInfo file_info;
	while ( file_finder.Walk( file_info, filter, flags, depth ) )
	{
		if ( (*walk_item_func)( file_info, parameters ) == _false )
			break;
	}

	return _true;
}