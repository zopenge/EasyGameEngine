//! @file     PackageFile.cpp
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// PackageFile Implementation
//----------------------------------------------------------------------------

PackageFile::PackageFile( )
{
}

PackageFile::~PackageFile( )
{
	Unload( );
}

_ubool PackageFile::CreateFile( WStringPtr filename )
{
	mStreamWriter = GetInterfaceFactory( )->CreateFileStreamWriter( filename );
	if ( mStreamWriter.IsNull( ) )
		return _false;

	return _true;
}

_FILE_FORMAT PackageFile::GetFileID( ) const
{
	return _FF_PACKAGE;
}

_ubool PackageFile::LoadFromStream( IStreamReader* stream_reader )
{
	return _true;
}

_void PackageFile::Unload( )
{
	mFileItems.Clear( );
}

_float PackageFile::GetCompressionRatio( ) const
{
	return 1.0f;
}

_ubool PackageFile::AddFile( WStringPtr filename )
{
	return AddFile( filename, filename );
}

_ubool PackageFile::AddFile( WStringPtr filename, WStringPtr filename_in_zip ) 
{
	return _false;
}

_ubool PackageFile::HasFile( WStringPtr filename ) const
{
	FileInfoArray::Iterator it = mFileItems.SearchAscending( filename );
	if ( it.IsValid( ) == _false )
		return _false;

	return _true;
}

IStreamReaderPassRef PackageFile::GetFile( WStringPtr filename )
{
	FileInfoArray::Iterator it = mFileItems.SearchAscending( filename );
	if ( it.IsValid( ) == _false )
		return _null;

	return GetFileStreamByIndex( it.mIndex );
}

_ubool PackageFile::AddFolder( WStringPtr dir_path, WStringPtr filter, _dword flags, _dword depth )
{
	return _false;
}

_ubool PackageFile::AddFolder( WStringPtr dir_path, WStringPtr dir_path_in_zip, WStringPtr filter, _dword flags, _dword depth )
{
	return _false;
}

_dword PackageFile::GetFileNumber( ) const
{
	return mFileItems.Number( );
}

WStringPtr PackageFile::GetFileNameByIndex( _dword index )
{
	return mFileItems[index].mFileName;
}

IStreamReaderPassRef PackageFile::GetFileStreamByIndex( _dword index ) 
{
	LockOwner lock_owner( mLocker );

	// Get the file info
	FileInfo& file_info = mFileItems[index];

	return _null;
}