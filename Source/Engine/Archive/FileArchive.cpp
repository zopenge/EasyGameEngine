//! @file     FileArchive.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// FileArchive Implementation
//----------------------------------------------------------------------------

FileArchive::FileArchive( WStringPtr path ) : mPath( path )
{
}

FileArchive::~FileArchive( )
{

}

WStringPtr FileArchive::GetPath( ) const
{
	return mPath;
}

_ubool FileArchive::HasResourceByPath( WStringPtr file_name ) const
{
	if ( FileSystem::IsFileExist( file_name ) == _false )
		return _false;

	return _true;
}

IStreamReaderPassRef FileArchive::LoadResourceByPath( WStringPtr file_name )
{
	// Try to load from patch archives
	IStreamReaderPassRef stream_reader = BaseClass::LoadResourceByPath( file_name );
	if ( stream_reader.IsValid( ) )
		return stream_reader;

	// The file stream reader
	FileStreamReader* file_stream_reader = new FileStreamReader( );

	// Open the file by absolute path
	_ubool ret = _false;
	if ( Path::IsPathRooted( file_name ) && FileSystem::IsFileExist( file_name ) )
	{
		ret = file_stream_reader->Initialize( L"", file_name );
	}
	// Open the file by relative path
	else
	{
		ret = file_stream_reader->Initialize( mPath, file_name );
	}

	// Check file open result
	if ( ret == _false )
	{
		WLOG_ERROR_1( L"Load '%s' resource from file archive failed", file_name.Str( ) );

		EGE_RELEASE( file_stream_reader ); 
		return _null;
	}

	return file_stream_reader;
}

_ubool FileArchive::EnumResources( OnWalkItem walk_item_func, WStringPtr path, WStringPtr filter, _dword flags, _dword depth, const QwordParams2& params ) const
{
	if ( walk_item_func == _null )
		return _false;

	// Locate directory
	FileFinder file_finder;
	if ( file_finder.Open( Path::BuildFilePath( mPath, path ) ) == _false )
		return _false;

	// Start to walk
	FileInfo file_info;
	while ( file_finder.Walk( file_info, filter, flags, depth ) )
	{
		if ( (*walk_item_func)( file_info, params ) == _false )
			break;
	}

	return _true;
}