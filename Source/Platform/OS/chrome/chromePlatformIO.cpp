//! @file     chromePlatformIO.cpp
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
	if ( directory == _null )
		return _null;
	
	// Process open directory event
	EventOpenDir event;
	event.mPath = directory;
	ProcessChromeEvent( event );

	return (_handle)event.mRet;
}

_void Platform::CloseDir( _handle handle )
{
	// Process close directory event
	EventCloseDir event;
	event.mDirHandle = handle;
	ProcessChromeEvent( event );
}

_ubool Platform::ReadDir( _handle handle, FileFinderData& finderdata )
{
	// Process read directory event
	EventReadDir event;
	event.mDirHandle	= handle;
	event.mFinderData	= &finderdata;
	ProcessChromeEvent( event );

	return EGE_BOOLEAN( event.mRet );
}

_ubool Platform::GetFileAttributes( const _charw* filename, _dword& attributes )
{
	if ( filename == _null )
		return _false;

	// Process get file attributes event
	EventGetFileAttributes event;
	event.mFileName		= filename;
	event.mAttributes	= &attributes;
	ProcessChromeEvent( event );

	return EGE_BOOLEAN( event.mRet );
}

_ubool Platform::SetFileAttributes( const _charw* filename, _dword attributes )
{
	if ( filename == _null )
		return _false;

	return _false;
}

_handle Platform::OpenFile( const _charw* filename, _FILE_CREATE_FLAG createflag, _dword operateflag, _dword shareflag, _dword attributes )
{
	if ( filename == _null )
		return _null;

	// Process open file event
	EventOpenFile event;
	event.mFileName			= filename;
	event.mCreateFlag		= createflag;
	event.mOperationFlag	= operateflag;
	event.mShareFlags		= shareflag;
	ProcessChromeEvent( event );

	return (_handle)event.mRet;
}

_void Platform::CloseFile( _handle handle )
{
	// Process close file event
	EventCloseFile event;
	event.mFileHandle	= handle;
	ProcessChromeEvent( event );
}

_ubool Platform::ReadFile( _handle handle, _void* buffer, _dword size, _dword* bytesread )
{
	if ( handle == _null || buffer == _null || size == 0 )
		return _false;

	// Process read file event
	EventReadFile event;
	event.mFileHandle	= handle;
	event.mBufferData	= buffer;
	event.mBufferSize	= size;
	event.mBytesRead	= bytesread;
	ProcessChromeEvent( event );

	return EGE_BOOLEAN( event.mRet );
}

_ubool Platform::WriteFile( _handle handle, const _void* buffer, _dword size, _dword* byteswritten )
{
	if ( handle == _null || buffer == _null || size == 0 )
		return _false;

	// Process write file event
	EventWriteFile event;
	event.mFileHandle	= handle;
	event.mBufferData	= buffer;
	event.mBufferSize	= size;
	event.mBytesWrite	= byteswritten;
	ProcessChromeEvent( event );

	return EGE_BOOLEAN( event.mRet );
}

_ubool Platform::FlushFileBuffers( _handle handle )
{
	if ( handle == _null )
		return _false;

	return _true;
}

_dword Platform::SeekFilePointer( _handle handle, _SEEK flag, _long distance )
{
	if ( handle == _null )
		return -1;

	// Process seek file event
	EventSeekFile event;
	event.mFileHandle	= handle;
	event.mFlag			= flag;
	event.mDistance		= distance;
	ProcessChromeEvent( event );

	return (_dword) event.mRet;
}

_dword Platform::GetFileSize( _handle handle )
{
	if ( handle == _null )
		return 0;

	// Process get file size event
	EventGetFileSize event;
	event.mFileHandle	= handle;
	ProcessChromeEvent( event );

	return (_dword) event.mRet;
}

_ubool Platform::SetEndOfFile( _handle handle )
{
	if ( handle == _null )
		return _false;

	// Process set end of file event
	EventSetEndOfFile event;
	event.mFileHandle	= handle;
	ProcessChromeEvent( event );

	return EGE_BOOLEAN( event.mRet );
}

_ubool Platform::GetFileTime( _handle handle, FileTime* creation, FileTime* lastaccess, FileTime* lastwrite )
{
	if ( handle == _null )
		return _false;

	return _false;
}

_ubool Platform::SetFileTime( _handle handle, const FileTime* creation, const FileTime* lastaccess, const FileTime* lastwrite )
{
	if ( handle == _null )
		return _false;

	return _false;
}

_ubool Platform::DeleteFile( const _charw* filename )
{
	if ( filename == _null )
		return _false;

	return _false;
}

_ubool Platform::CopyFile( const _charw* desfilename, const _charw* srcfilename )
{
	if ( desfilename == _null || srcfilename == _null )
		return _false;

	return _false;
}

_ubool Platform::MoveFile( const _charw* desfilename, const _charw* srcfilename )
{
	if ( desfilename == _null || srcfilename == _null )
		return _false;

	return _false;
}

_ubool Platform::GetCurrentDirectory( _charw* path, _dword length )
{
	if ( path == _null || length == 0 )
		return _false;

	return _false;
}

_ubool Platform::SetCurrentDirectory( const _charw* path )
{
	if ( path == _null )
		return _false;

	return _false;
}

_ubool Platform::CreateDirectory( const _charw* path )
{
	if ( path == _null )
		return _false;

	// Skip some resident paths
	if ( path[0] == '.' && path[1] == '\0' )
		return _true;

	// Process create directory event
	EventCreateDirectory event;
	event.mPath	= path;
	ProcessChromeEvent( event );

	return EGE_BOOLEAN( event.mRet );
}

_ubool Platform::RemoveDirectory( const _charw* path )
{
	if ( path == _null )
		return _false;

	return _false;
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

	Platform::CopyString( path, L"Internal", length );

	return _true;
}

_ubool Platform::GetExternalPathInDomains( _charw* path, _dword length )
{
	if ( path == _null || length == 0 )
		return _false;

	Platform::CopyString( path, L"External", length );

	return _true;
}

_ubool Platform::GetDocumentPathInDomains( _charw* path, _dword length )
{
	if ( path == _null || length == 0 )
		return _false;

	Platform::CopyString( path, L"Document", length );

	return _true;
}

_ubool Platform::GetDiskFreeSpace( const _charw* directory, _qword* freebytes, _qword* totalbytes )
{
	return _false;
}