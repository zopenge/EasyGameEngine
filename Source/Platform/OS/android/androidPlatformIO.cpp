//! @file     androidPlatformIO.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform-IO Implementation
//----------------------------------------------------------------------------

_handle Platform::OpenDir( const _charw* directory )
{
	return anyPlatformIO::OpenDir( directory );
}

_void Platform::CloseDir( _handle handle )
{
	anyPlatformIO::CloseDir( handle );
}

_ubool Platform::ReadDir( _handle handle, FileFinderData& finderdata )
{
	return anyPlatformIO::ReadDir( handle, finderdata );
}

_ubool Platform::GetFileAttributes( const _charw* filename, _dword& attributes )
{
	return anyPlatformIO::GetFileAttributes( filename, attributes );
}

_ubool Platform::SetFileAttributes( const _charw* filename, _dword attributes )
{
	return anyPlatformIO::SetFileAttributes( filename, attributes );
}

_handle Platform::OpenFile( const _charw* filename, _FILE_CREATE_FLAG createflag, _dword operateflag, _dword shareflag, _dword attributes )
{
	return anyPlatformIO::OpenFile( filename, createflag, operateflag, shareflag, attributes );
}

_void Platform::CloseFile( _handle handle )
{
	anyPlatformIO::CloseFile( handle );
}

_ubool Platform::ReadFile( _handle handle, _void* buffer, _dword size, _dword* bytesread )
{
	return anyPlatformIO::ReadFile( handle, buffer, size, bytesread );
}

_ubool Platform::WriteFile( _handle handle, const _void* buffer, _dword size, _dword* byteswritten )
{
	return anyPlatformIO::WriteFile( handle, buffer, size, byteswritten );
}

_ubool Platform::FlushFileBuffers( _handle handle )
{
	return anyPlatformIO::FlushFileBuffers( handle );
}

_dword Platform::SeekFilePointer( _handle handle, _SEEK flag, _int distance )
{
	return anyPlatformIO::SeekFilePointer( handle, flag, distance );
}

_dword Platform::GetFileSize( _handle handle )
{
	return anyPlatformIO::GetFileSize( handle );
}

_ubool Platform::SetEndOfFile( _handle handle )
{
	return anyPlatformIO::SetEndOfFile( handle );
}

_ubool Platform::GetFileTime( _handle handle, FileTime* creation, FileTime* lastaccess, FileTime* lastwrite )
{
	return anyPlatformIO::GetFileTime( handle, creation, lastaccess, lastwrite );
}

_ubool Platform::SetFileTime( _handle handle, const FileTime* creation, const FileTime* lastaccess, const FileTime* lastwrite )
{
	return anyPlatformIO::SetFileTime( handle, creation, lastaccess, lastwrite );
}

_ubool Platform::DeleteFile( const _charw* filename )
{
	return anyPlatformIO::DeleteFile( filename );
}

_ubool Platform::CopyFile( const _charw* desfilename, const _charw* srcfilename )
{
	return anyPlatformIO::CopyFile( desfilename, srcfilename );
}

_ubool Platform::MoveFile( const _charw* desfilename, const _charw* srcfilename )
{
	return anyPlatformIO::MoveFile( desfilename, srcfilename );
}

_ubool Platform::GetAbsoluteDirectory( const _charw* path, _charw* abs_path, _dword abs_path_length )
{
	return anyPlatformIO::GetAbsoluteDirectory( path, abs_path, abs_path_length );
}

_ubool Platform::GetCurrentDirectory( _charw* path, _dword length )
{
	return anyPlatformIO::GetCurrentDirectory( path, length );
}

_ubool Platform::SetCurrentDirectory( const _charw* path )
{
	return anyPlatformIO::SetCurrentDirectory( path );
}

_ubool Platform::CreateDirectory( const _charw* path )
{
	return anyPlatformIO::CreateDirectory( path );
}

_ubool Platform::RemoveDirectory( const _charw* path )
{
	return anyPlatformIO::RemoveDirectory( path );
}

_handle Platform::CreateFileMapping( _handle file, _dword size, _dword operationflag )
{
	return _null;
}

_void* Platform::MapViewOfFile( _handle handle, _dword operationflag )
{
	return _null;
}

_void Platform::UnmapViewOfFile( _void* pointer )
{
}

_ubool Platform::GetInternalPathInDomains( _charw* path, _dword length )
{
	if ( path == _null || length == 0 )
		return _false;

	// Feedback the data path
	Platform::AnsiToUtf16( path, length, GetAndroidInternalPath( ) );

	return _true;
}

_ubool Platform::GetExternalPathInDomains( _charw* path, _dword length )
{
	if ( path == _null || length == 0 )
		return _false;

	// Feedback the data path
	Platform::AnsiToUtf16( path, length, GetAndroidExternalPath( ) );

	return _true;
}

_ubool Platform::GetDocumentPathInDomains( _charw* path, _dword length )
{
	if ( path == _null || length == 0 )
		return _false;

	// 1: Get the internal data path
	AStringPtr internal_data_path = GetAndroidInternalPath( );
	if ( internal_data_path.IsEmpty( ) == _false )
	{
		Platform::AnsiToUtf16( path, length, internal_data_path.Str( ) );
		return _true;
	}

	// 2: Get the external data path + package name
	AStringPtr external_data_path = GetAndroidExternalPath( );
	if ( external_data_path.IsEmpty( ) == _false )
	{
		AString whole_path = Path::BuildFilePath( external_data_path, GetAndroidPackageName( ) );
		Platform::AnsiToUtf16( path, length, whole_path.Str( ) );
		return _true;
	}

	OUTPUT_DEBUG_STRING( L"Android app's internal/external data path all are empty" );
	return _false;
}

_ubool Platform::GetDiskFreeSpace( const _charw* directory, _qword* freebytes, _qword* totalbytes )
{
	return _true;
}