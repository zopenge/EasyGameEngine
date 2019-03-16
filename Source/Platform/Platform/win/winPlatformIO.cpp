//! @file     winPlatformIO.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//!	The IO performance info.
static IOPerformanceInfo	sIOPerformanceInfo;

//----------------------------------------------------------------------------
// Helpful Functions
//----------------------------------------------------------------------------

static _dword TranslateFileSeekFlag( _SEEK flag )
{
	switch ( flag )
	{
		case _SEEK_BEGIN:	return FILE_BEGIN;
		case _SEEK_CURRENT: return FILE_CURRENT;
		case _SEEK_END:		return FILE_END;
		default:
			return 0;
	}
}

static _dword TranslateCreateFlag( _FILE_CREATE_FLAG createflag )
{
	switch ( createflag )
	{
		case _FILE_CREATE_NEW:		return CREATE_NEW;
		case _FILE_CREATE_ALWAYS:	return CREATE_ALWAYS;
		case _FILE_OPEN_EXISTING:	return OPEN_EXISTING;
		case _FILE_OPEN_ALWAYS:		return OPEN_ALWAYS;
		default:
			return 0;
	}
}

//----------------------------------------------------------------------------
// Platform-IO Implementation
//----------------------------------------------------------------------------

static _void CopyFileFinderData( FileFinderData& finderdata, const WIN32_FIND_DATAW& win32_find_data )
{
	// Feedback find data 
	finderdata.mFileAttributes	= win32_find_data.dwFileAttributes;
	finderdata.mCreationTime	= *(const FileTime*) &win32_find_data.ftCreationTime;
	finderdata.mLastAccessTime	= *(const FileTime*) &win32_find_data.ftLastAccessTime;
	finderdata.mLastWriteTime	= *(const FileTime*) &win32_find_data.ftLastWriteTime;
	finderdata.mFileSize		= ( _qword( win32_find_data.nFileSizeHigh ) << 32 ) | win32_find_data.nFileSizeLow;
	SafeCopyString( finderdata.mFileName, win32_find_data.cFileName );
	SafeCopyString( finderdata.mAlternateFileName, win32_find_data.cAlternateFileName );
}

_handle Platform::OpenDir( const _charw* directory )
{
	if ( directory == _null )
		return _null;

	// The find data on Win32 platform
	WIN32_FIND_DATAW win32_find_data;

	// Build the directory path
	_charw path[1024];
	Platform::FormatStringBuffer( path, 1024, L"%s/*.*", directory );

	// Open the directory
	_handle handle = ::FindFirstFileW( path, &win32_find_data );
	if ( handle == INVALID_HANDLE_VALUE )
		return _null;

	// Skip for the '.' and '..' files
	do
	{
		if ( win32_find_data.cFileName[0] == '.' && win32_find_data.cFileName[1] == '.' && win32_find_data.cFileName[2] == 0 )
			break;
	}
	while ( ::FindNextFileW( handle, &win32_find_data ) );

	return handle;
}

_void Platform::CloseDir( _handle handle )
{
	::FindClose( handle );
}

_ubool Platform::ReadDir( _handle handle, FileFinderData& finderdata )
{
	WIN32_FIND_DATAW win32_find_data;
	if ( !::FindNextFileW( handle, &win32_find_data ) )
		return _false;

	// Copy file find data 
	CopyFileFinderData( finderdata, win32_find_data );

	return _true;
}

_ubool Platform::GetFileAttributes( const _charw* filename, _dword& attributes )
{
	if ( filename == _null )
		return _false;

	attributes = ::GetFileAttributesW( filename );
	if ( attributes == -1 )
		return _false;

	return _true;
}

_ubool Platform::SetFileAttributes( const _charw* filename, _dword attributes )
{
	if ( filename == _null )
		return _false;

	return EGE_BOOLEAN( ::SetFileAttributesW( filename, attributes ) );
}

_handle Platform::OpenFile( const _charw* filename, _FILE_CREATE_FLAG createflag, _dword operateflag, _dword shareflag, _dword attributes )
{
	if ( filename == _null )
		return _null;

	// Set the file flags
	_dword file_attributes = attributes == 0 ? FILE_ATTRIBUTE_NORMAL : attributes;

	// Create or open file
	_handle handle = ::CreateFileW( filename, operateflag, shareflag, _null, TranslateCreateFlag( createflag ), attributes, _null );
	if ( handle == INVALID_HANDLE_VALUE )
		return _null;

	// If it's write and append mode then we need to seek file pointer to the end of the file
	if ( ( operateflag & _FILE_OPERATION_WRITE_APPEND ) == _FILE_OPERATION_WRITE_APPEND )
		Platform::SeekFilePointer( handle, _SEEK_END, 0 );

	OUTPUT_DEBUG_STRING( FORMAT_WSTRING_1( L"Platform::OpenFile : '%s' [OK]\n", filename ) );

	// Update IO performance info
	sIOPerformanceInfo.mFileOpenCount ++;

	return handle;
}

_void Platform::CloseFile( _handle handle )
{
	if ( handle != _null )
		::CloseHandle( handle );
}

_ubool Platform::ReadFile( _handle handle, _void* buffer, _dword size, _dword* bytesread )
{
	if ( handle == _null || buffer == _null || size == 0 )
		return _false;

	DWORD bytes = 0;
	if ( ::ReadFile( handle, buffer, size, &bytes, _null ) == 0 )
		return _false;

	// If doesn't need bytes read, and the bytes read is less than request, then return false.
	if ( bytesread == _null && bytes < size )
		return _false;

	if ( bytesread != _null )
		*bytesread = bytes;

	// Update IO performance info
	sIOPerformanceInfo.mFileReadCount ++;
	sIOPerformanceInfo.mFileReadBytes += bytes;

	return _true;
}

_ubool Platform::WriteFile( _handle handle, const _void* buffer, _dword size, _dword* byteswritten )
{
	if ( handle == _null || buffer == _null || size == 0 )
		return _false;

	DWORD bytes = 0;
	if ( ::WriteFile( handle, buffer, size, &bytes, _null ) == 0 )
		return _false;

	// If doesn't need bytes written, and the bytes written is less than request, then return false.
	if ( byteswritten == _null && bytes < size )
		return _false;

	if ( byteswritten != _null )
		*byteswritten = bytes;

	// Update IO performance info
	sIOPerformanceInfo.mFileWriteCount ++;
	sIOPerformanceInfo.mFileWriteBytes += bytes;

	return _true;
}

_ubool Platform::FlushFileBuffers( _handle handle )
{
	if ( handle == _null )
		return _false;

	return ::FlushFileBuffers( handle ) != 0;
}

_dword Platform::SeekFilePointer( _handle handle, _SEEK flag, _int distance )
{
	if ( handle == _null )
		return -1;

	return ::SetFilePointer( handle, distance, _null, TranslateFileSeekFlag( flag ) );
}

_dword Platform::GetFileSize( _handle handle )
{
	if ( handle == _null )
		return 0;

	return ::GetFileSize( handle, _null );
}

_ubool Platform::SetEndOfFile( _handle handle )
{
	if ( handle == _null )
		return _false;

	return ::SetEndOfFile( handle ) != 0;
}

_ubool Platform::GetFileTime( _handle handle, FileTime* creation, FileTime* lastaccess, FileTime* lastwrite )
{
	if ( handle == _null )
		return _false;

	return EGE_BOOLEAN( ::GetFileTime( handle, (::FILETIME*) creation, (::FILETIME*) lastaccess, (::FILETIME*) lastwrite ) );
}

_ubool Platform::SetFileTime( _handle handle, const FileTime* creation, const FileTime* lastaccess, const FileTime* lastwrite )
{
	if ( handle == _null )
		return _false;

	return EGE_BOOLEAN( ::SetFileTime( handle, (const ::FILETIME*) creation, (const ::FILETIME*) lastaccess, (const ::FILETIME*) lastwrite ) );
}

_ubool Platform::DeleteFile( const _charw* filename )
{
	if ( filename == _null )
		return _false;

	return EGE_BOOLEAN( ::DeleteFileW( filename ) );
}

_ubool Platform::CopyFile( const _charw* desfilename, const _charw* srcfilename )
{
	if ( desfilename == _null || srcfilename == _null )
		return _false;

	return EGE_BOOLEAN( ::CopyFileW( srcfilename, desfilename, _false ) );
}

_ubool Platform::MoveFile( const _charw* desfilename, const _charw* srcfilename )
{
	if ( desfilename == _null || srcfilename == _null )
		return _false;

	return EGE_BOOLEAN( ::MoveFileExW( srcfilename, desfilename, MOVEFILE_REPLACE_EXISTING ) );
}

_ubool Platform::GetAbsoluteDirectory( const _charw* path, _charw* abs_path, _dword abs_path_length )
{
	if ( _wfullpath( abs_path, path, abs_path_length ) == _null )
		return _false;

	return _true;
}

_ubool Platform::GetCurrentDirectory( _charw* path, _dword length )
{
	if ( path == _null || length == 0 )
		return _false;

	return ::GetCurrentDirectoryW( length, (LPWSTR) path ) != 0;
}

_ubool Platform::SetCurrentDirectory( const _charw* path )
{
	if ( path == _null )
		return _false;

	return ::SetCurrentDirectoryW( path ) != 0;
}

_ubool Platform::CreateDirectory( const _charw* path )
{
	if ( path == _null )
		return _false;

	// Create directory
	if ( ::CreateDirectoryW( path, _null ) == 0 )
	{
		// Skip for the existing error
		if ( ::GetLastError( ) != ERROR_ALREADY_EXISTS )
			return _false;
	}

	return _true;
}

_ubool Platform::RemoveDirectory( const _charw* path )
{
	if ( path == _null )
		return _false;

	return EGE_BOOLEAN( ::RemoveDirectoryW( path ) );
}

_handle Platform::CreateFileMapping( _handle file, _dword size, _dword operationflag )
{
	_dword protect = PAGE_READONLY;
	if ( operationflag & _FILE_OPERATION_WRITE )
		protect = PAGE_READWRITE;

	return ::CreateFileMapping( file, _null, protect, 0, size, _null );
}

_void* Platform::MapViewOfFile( _handle handle, _dword operationflag )
{
	_dword access = FILE_MAP_READ;
	if ( operationflag & _FILE_OPERATION_WRITE )
		access = FILE_MAP_WRITE;

	return ::MapViewOfFile( handle, access, 0, 0, 0 );
}

_void Platform::UnmapViewOfFile( _void* pointer )
{
	::UnmapViewOfFile( pointer );
}

_ubool Platform::GetInternalPathInDomains( _charw* path, _dword length )
{
	if ( path == _null || length == 0 )
		return _false;

	Platform::CopyString( path, L"./Internal", length );

	return _true;
}

_ubool Platform::GetExternalPathInDomains( _charw* path, _dword length )
{
	if ( path == _null || length == 0 )
		return _false;

	Platform::CopyString( path, L"./External", length );

	return _true;
}

_ubool Platform::GetDocumentPathInDomains( _charw* path, _dword length )
{
	if ( path == _null || length == 0 )
		return _false;

	Platform::CopyString( path, L"./Document", length );

	return _true;
}

_ubool Platform::GetDiskFreeSpace( const _charw* directory, _qword* freebytes, _qword* totalbytes )
{
	return EGE_BOOLEAN( ::GetDiskFreeSpaceExW( directory, (ULARGE_INTEGER*) freebytes, (ULARGE_INTEGER*) totalbytes, _null ) );
}

_void Platform::GetIOPerformanceInfo( IOPerformanceInfo& info )
{
	info = sIOPerformanceInfo;
}
