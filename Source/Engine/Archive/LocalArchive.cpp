//! @file     LocalArchive.cpp
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// LocalArchive Implementation
//----------------------------------------------------------------------------

LocalArchive::LocalArchive( )
{
}

LocalArchive::~LocalArchive( )
{
}

_ubool LocalArchive::RefreshDir( WStringPtr dir )
{
	// Make sure the working directory is existing
	if ( FileSystem::IsDirectoryExist( dir ) == _false )
		return _false;

	// Open the working directory
	FileFinder file_finder;
	if ( file_finder.Open( dir ) == _false )
		return _false;

	// Enumerate all resources
	FileInfo file_info;
	while ( file_finder.Walk( file_info, L"", _FILE_FINDER_FILE_MASK, -1 ) )
	{
		if ( RefreshFile( dir, file_info ) == _false )
			return _false;
	}

	return _true;
}

_ubool LocalArchive::RefreshFile( WStringPtr dir, const FileInfo& file_info )
{
	// Get the extension name
	WStringObj extension_name = Path::GetExtension( file_info.mFileName );

	// Update file cache
	FileCacheInfoMap&	file_caches	= mFileCaches[extension_name];
	FileCacheInfo&		file_cache	= file_caches[file_info.mFileName];
	file_cache.mRootPath			= dir;
	file_cache.mResRelativePath		= file_info.mRelativePath;

	return _true;
}

WString LocalArchive::GetAbsoluteFileName( WStringPtr res_name ) const
{
	// Get the extension name
	WStringObj extension_name = Path::GetExtension( res_name );

	// Find it
	const FileCacheInfoMap* resources = mFileCaches.Search( extension_name );
	if ( resources == _null )
		return WString( L"" );

	// Get resource name with extension name
	const FileCacheInfo* file_cache_info = resources->Search( res_name );
	if ( file_cache_info == _null )
	{
		// Get resource name without extension name
		file_cache_info = resources->Search( Path::GetFileName( res_name, _false ) );
		if ( file_cache_info == _null )
			return WString( L"" );
	}

	return Path::BuildFilePath( file_cache_info->mRootPath, file_cache_info->mResRelativePath );
}

WString LocalArchive::GetRelativeFileName( WStringPtr res_name ) const
{
	// Get the extension name
	WStringObj extension_name = Path::GetExtension( res_name );

	// Find it
	const FileCacheInfoMap* resources = mFileCaches.Search( extension_name );
	if ( resources != _null )
	{
		// Get resource name with extension name
		const FileCacheInfo* file_cache_info = resources->Search( res_name );
		if ( file_cache_info != _null )
			return file_cache_info->mResRelativePath;

		// Get resource name without extension name
		file_cache_info = resources->Search( Path::GetFileName( res_name, _false ) );
		if ( file_cache_info != _null )
			return file_cache_info->mResRelativePath;
	}

	return WString( L"" );
}

_ubool LocalArchive::AddPatchDir( WStringPtr path )
{
	// Check whether it's directory
	if ( FileSystem::IsDirectoryExist( path ) == _false )
		return _false;

	// Skip for the existing patch directory
	if ( mPatches.Search( path ).IsValid( ) )
		return _false;

	// Add patch directory
	mPatches.Append( path );

	// Refresh working directory
	if ( RefreshWorkingDir( ) == _false )
		return _false;

	return _true;
}

_ubool LocalArchive::RemovePatchDir( WStringPtr path )
{
	// Remove patch
	if ( mPatches.Remove( path ) == _false )
		return _false;

	// Refresh working directory
	if ( RefreshWorkingDir( ) == _false )
		return _false;

	return _true;
}

_ubool LocalArchive::RefreshWorkingDir( )
{
	// Clear current file caches
	mFileCaches.Clear( );

	// Add and refresh patch directories
	for ( _dword i = 0; i < mPatches.Number( ); i ++ )
	{
		if ( RefreshDir( mPatches[i] ) == _false )
			return _false;
	}

	return _true;
}

WStringPtr LocalArchive::GetPath( ) const
{
	return L"";
}

WString LocalArchive::GetResourceAbsolutePath( WStringPtr res_name ) const
{
	WString relative_path = BaseClass::GetResourceAbsolutePath( res_name );
	if ( relative_path.IsEmpty( ) == _false )
		return relative_path;

	return GetAbsoluteFileName( res_name );
}

WString LocalArchive::GetResourceRelativePath( WStringPtr res_name ) const
{
	WString relative_path = BaseClass::GetResourceRelativePath( res_name );
	if ( relative_path.IsEmpty( ) == _false )
		return relative_path;

	return GetAbsoluteFileName( res_name );
}

IStreamReaderPassRef LocalArchive::LoadResourceByName( WStringPtr res_name )
{
	WString file_name = GetAbsoluteFileName( res_name );
	if ( file_name.IsEmpty( ) == _false )
	{
		IStreamReaderPassRef stream_reader = GetInterfaceFactory( )->CreateFileStreamReader( file_name );
		if ( stream_reader.IsValid( ) )
			return stream_reader;
	}

	IStreamReaderPassRef stream_reader = BaseClass::LoadResourceByName( res_name );
	if ( stream_reader.IsNull( ) )
	{
		WLOG_ERROR_1( L"Load '%s' resource from local archive failed", res_name.Str( ) );
		return _null;
	}

	return stream_reader;
}

_ubool LocalArchive::HasResourceByPath( WStringPtr file_name ) const
{
	return _false;
}
