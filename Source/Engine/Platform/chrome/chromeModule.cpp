//! @file     chromeModule.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// Platform-IO Helpful Structures Implementation
//----------------------------------------------------------------------------

struct chromeHandleBase
{
	PP_ResourcePassRef	mResource;

	chromeHandleBase( PP_Resource res ) : mResource( res )
	{

	}
};

struct chromeFileHandle : public chromeHandleBase
{
	_long	mOffset;

	chromeFileHandle( PP_Resource res ) : chromeHandleBase( res )
	{
		mOffset = 0;
	}
};

struct chromeDirHandle : public chromeHandleBase
{
	Queue< PP_DirectoryEntry >	mFiles;
	Queue< PP_DirectoryEntry >	mDirectories;
	_byte*						mBuffer;
	_dword						mSize;

	chromeDirHandle( PP_Resource res ) : chromeHandleBase( res )
	{
		mBuffer = _null;
		mSize	= 0;
	}
	~chromeDirHandle( )
	{
		EGE_DELETE_ARRAY( mBuffer );
	}
};

//----------------------------------------------------------------------------
// Platform-IO Extern Functions Implementation
//----------------------------------------------------------------------------

_void Chrome_CheckPPRet( _long ppret )
{
	WStringPtr err_string;
	switch ( ppret )
	{
		case PP_ERROR_FAILED:				err_string = L"PP_ERROR_FAILED"; break;
		case PP_ERROR_ABORTED:				err_string = L"PP_ERROR_ABORTED"; break;
		case PP_ERROR_BADARGUMENT:			err_string = L"PP_ERROR_BADARGUMENT"; break;
		case PP_ERROR_BADRESOURCE:			err_string = L"PP_ERROR_BADRESOURCE"; break;
		case PP_ERROR_NOINTERFACE:			err_string = L"PP_ERROR_NOINTERFACE"; break;
		case PP_ERROR_NOACCESS:				err_string = L"PP_ERROR_NOACCESS"; break;
		case PP_ERROR_NOMEMORY:				err_string = L"PP_ERROR_NOMEMORY"; break;
		case PP_ERROR_NOSPACE:				err_string = L"PP_ERROR_NOSPACE"; break;
		case PP_ERROR_NOQUOTA:				err_string = L"PP_ERROR_NOQUOTA"; break;
		case PP_ERROR_INPROGRESS:			err_string = L"PP_ERROR_INPROGRESS"; break;
		case PP_ERROR_NOTSUPPORTED:			err_string = L"PP_ERROR_NOTSUPPORTED"; break;
		case PP_ERROR_BLOCKS_MAIN_THREAD:	err_string = L"PP_ERROR_BLOCKS_MAIN_THREAD"; break;
		case PP_ERROR_MALFORMED_INPUT:		err_string = L"PP_ERROR_MALFORMED_INPUT"; break;
		case PP_ERROR_RESOURCE_FAILED:		err_string = L"PP_ERROR_RESOURCE_FAILED"; break;
		case PP_ERROR_FILENOTFOUND:			err_string = L"PP_ERROR_FILENOTFOUND"; break;
		case PP_ERROR_FILEEXISTS:			err_string = L"PP_ERROR_FILEEXISTS"; break;
		case PP_ERROR_FILETOOBIG:			err_string = L"PP_ERROR_FILETOOBIG"; break;
		case PP_ERROR_FILECHANGED:			err_string = L"PP_ERROR_FILECHANGED"; break;
		case PP_ERROR_NOTAFILE:				err_string = L"PP_ERROR_NOTAFILE"; break;
		case PP_ERROR_TIMEDOUT:				err_string = L"PP_ERROR_TIMEDOUT"; break;
		case PP_ERROR_USERCANCEL:			err_string = L"PP_ERROR_USERCANCEL"; break;
		case PP_ERROR_NO_USER_GESTURE:		err_string = L"PP_ERROR_NO_USER_GESTURE"; break;
		case PP_ERROR_CONTEXT_LOST:			err_string = L"PP_ERROR_CONTEXT_LOST"; break;
		case PP_ERROR_NO_MESSAGE_LOOP:		err_string = L"PP_ERROR_NO_MESSAGE_LOOP"; break;
		case PP_ERROR_WRONG_THREAD:			err_string = L"PP_ERROR_WRONG_THREAD"; break;
		case PP_ERROR_WOULD_BLOCK_THREAD:	err_string = L"PP_ERROR_WOULD_BLOCK_THREAD"; break;
		case PP_ERROR_CONNECTION_CLOSED:	err_string = L"PP_ERROR_CONNECTION_CLOSED"; break;
		case PP_ERROR_CONNECTION_RESET:		err_string = L"PP_ERROR_CONNECTION_RESET"; break;
		case PP_ERROR_CONNECTION_REFUSED:	err_string = L"PP_ERROR_CONNECTION_REFUSED"; break;
		case PP_ERROR_CONNECTION_ABORTED:	err_string = L"PP_ERROR_CONNECTION_ABORTED"; break;
		case PP_ERROR_CONNECTION_FAILED:	err_string = L"PP_ERROR_CONNECTION_FAILED"; break;
		case PP_ERROR_CONNECTION_TIMEDOUT:	err_string = L"PP_ERROR_CONNECTION_TIMEDOUT"; break;
		case PP_ERROR_ADDRESS_INVALID:		err_string = L"PP_ERROR_ADDRESS_INVALID"; break;
		case PP_ERROR_ADDRESS_UNREACHABLE:	err_string = L"PP_ERROR_ADDRESS_UNREACHABLE"; break;
		case PP_ERROR_ADDRESS_IN_USE:		err_string = L"PP_ERROR_ADDRESS_IN_USE"; break;
		case PP_ERROR_MESSAGE_TOO_BIG:		err_string = L"PP_ERROR_MESSAGE_TOO_BIG"; break;
		case PP_ERROR_NAME_NOT_RESOLVED:	err_string = L"PP_ERROR_NAME_NOT_RESOLVED"; break;
		default:
			break;
	}

	if ( ppret != PP_OK && ppret != PP_OK_COMPLETIONPENDING )
		Platform::OutputDebugString( FORMAT_WSTRING_1( L"PPRET ERROR: '%s'\n", err_string.Str( ) ) );
}

//----------------------------------------------------------------------------
// Platform-IO Helpful Functions Implementation
//----------------------------------------------------------------------------

//!	Get the file open flags for PPAPI.
static _dword GetOpenFlags( _FILE_CREATE_FLAG createflag, _dword operateflag )
{
	_dword open_flags = 0;

	switch ( createflag )
	{
		case _FILE_CREATE_NEW:
		case _FILE_CREATE_ALWAYS:
			open_flags |= PP_FILEOPENFLAG_CREATE; 
			break;

		case _FILE_OPEN_EXISTING:
		case _FILE_OPEN_ALWAYS:
		default:
			break;
	}

	return open_flags;
}

//!	Get the file info from directory entry.
static _void GetFileInfo( PP_Resource res, FileFinderData& info )
{
	// Get directory or file info
	PP_FileInfo entry_info;
	GetPPResourceModule( )->GetPPBFileIO( )->Query( res, &entry_info, PP_BlockUntilComplete( ) );

	// Get the file name
	UString filename_utf8;
	GetPPResourceModule( )->VarToUtf8( GetPPResourceModule( )->GetPPBFileRef( )->GetName( res ), filename_utf8 );
	WString filename_utf16 = WString( ).FromString( filename_utf8 );

	// Feedback the file info
	info.mFileAttributes	= entry_info.type == PP_FILETYPE_DIRECTORY ? _FILE_ATTRIBUTE_DIRECTORY : 0;
	info.mCreationTime		= (_qword)entry_info.creation_time;
	info.mLastAccessTime	= (_qword)entry_info.last_access_time;
	info.mLastWriteTime		= (_qword)entry_info.last_modified_time;
	info.mFileSize			= entry_info.size;
	Platform::CopyString( info.mFileName, filename_utf16.Str( ) );
}

//----------------------------------------------------------------------------
// chromePlatform Callback Functions Implementation
//----------------------------------------------------------------------------

//!	When initialize file system done
static _void OnInitFileSystemCallback( _handle user_data, _long result )
{
	chromeViewBasedApp* viewbased_app = (chromeViewBasedApp*) GetMainViewBasedApp( );
	EGE_ASSERT( viewbased_app != _null );

	// Completed init file system
	viewbased_app->SetAppStatus( chromeViewBasedApp::_APP_STATUS_INITIALIZED_FILE_SYSTEM );

	// Start to load application
	ChromeMessageLoad load_msg;
	GetModuleManager( )->AddDelayMessage( load_msg );
}

//!	When get resources from directory.
static _void* OnReadDirectoryEntires( _void* user_data, _dword element_count, _dword element_size )
{
	chromeDirHandle* dir_handle = (chromeDirHandle*) user_data;
	EGE_ASSERT( dir_handle != _null );

	if ( element_count != 0 )
	{
		dir_handle->mSize	= element_count * element_size;
		dir_handle->mBuffer = new _byte[ dir_handle->mSize ];
	}

	return dir_handle->mBuffer;
}

//----------------------------------------------------------------------------
// chromePlatform Helpful Functions Implementation
//----------------------------------------------------------------------------

static _void ProcessEvent( EventInitFileSystem& event )
{
	// Open file system
	GetPPResourceModule( )->GetPPBFileSystem( )->Open( GetPPResourceModule( )->GetPPFileSystemRes( ), 1 MB, PP_BlockUntilComplete( ) );
	OnInitFileSystemCallback( _null, PP_OK );

	// Initialize file system OK
	event.mRet = _true;
}

static _void ProcessEvent( EventOpenDir& event )
{
	// Convert path from UTF-16 to UTF-8
	UString path_utf8 = "/" + UString( ).FromString( event.mPath );

	// Create resource referenced object
	PP_Resource res = GetPPResourceModule( )->GetPPBFileRef( )->Create( GetPPResourceModule( )->GetPPFileIORes( ), path_utf8.Str( ) );
	if ( res == _null )
		return;

	// Initialize directory handle
	chromeDirHandle* dir_handle = new chromeDirHandle( res );

	// Get file attributes
	PP_ArrayOutput output;
	output.GetDataBuffer	= OnReadDirectoryEntires;
	output.user_data		= dir_handle;
	PPRET2BOOL( event.mRet, GetPPResourceModule( )->GetPPBFileRef( )->ReadDirectoryEntries( res, output, PP_BlockUntilComplete( ) ) );

	// Save the directory handle
	event.mRet = (_qword)dir_handle;
}

static _void ProcessEvent( EventCloseDir& event )
{
	chromeDirHandle* dir_handle = (chromeDirHandle*) event.mDirHandle;
	if ( dir_handle == _null )
		return;

	EGE_DELETE( dir_handle );
}

static _void ProcessEvent( EventReadDir& event )
{
	chromeDirHandle* dir_handle = (chromeDirHandle*) event.mDirHandle;
	if ( dir_handle == _null )
		return;

	FileFinderData& file_data = *event.mFinderData;

	// Get file directory or file info
	PP_DirectoryEntry entry;
	if ( dir_handle->mDirectories.Dequeue( entry ) )
	{
		GetFileInfo( entry.file_ref, file_data );
		event.mRet = _true;
	}
	else if ( dir_handle->mFiles.Dequeue( entry ) )
	{
		GetFileInfo( entry.file_ref, file_data );
		event.mRet = _true;
	}
	else
	{
		// No more elements
		event.mRet = _false;
	}
}

static _void ProcessEvent( EventOpenFile& event )
{
	// Convert path from UTF-16 to UTF-8
	UString path_utf8 = "/" + UString( ).FromString( event.mFileName );

	// Create file referenced object
	PP_Resource file_res = GetPPResourceModule( )->GetPPBFileRef( )->Create( GetPPResourceModule( )->GetPPFileSystemRes( ), path_utf8.Str( ) );
	if ( file_res == _null )
		return;

	// Open file IO
	if ( GetPPResourceModule( )->GetPPBFileIO( )->Open( GetPPResourceModule( )->GetPPFileIORes( ), file_res, GetOpenFlags( event.mCreateFlag, event.mOperationFlag ), PP_BlockUntilComplete( ) ) != PP_OK )
		return;

	// Create file handle
	chromeFileHandle* file_handle = new chromeFileHandle( file_res );

	// Save the file resource
	event.mRet = (_qword) file_handle;
}

static _void ProcessEvent( EventCloseFile& event )
{
	chromeFileHandle* file_handle = (chromeFileHandle*) event.mFileHandle;
	if ( file_handle == _null )
		return;

	EGE_DELETE( file_handle );
}

static _void ProcessEvent( EventSetEndOfFile& event )
{
	event.mRet = Platform::SetEndOfFile( event.mFileHandle );
}

static _void ProcessEvent( EventGetFileSize& event )
{
	chromeFileHandle* file_handle = (chromeFileHandle*) event.mFileHandle;
	if ( file_handle == _null )
		return;

	PP_FileInfo file_info;
	PPRET2BOOL( event.mRet, GetPPResourceModule( )->GetPPBFileRef( )->Query( file_handle->mResource, &file_info, PP_BlockUntilComplete( ) ) );

	event.mRet = file_info.size;
}

static _void ProcessEvent( EventSeekFile& event )
{
	chromeFileHandle* file_handle = (chromeFileHandle*) event.mFileHandle;
	if ( file_handle == _null )
		return;

	switch ( event.mFlag )
	{
		case _SEEK_BEGIN:
		{
			file_handle->mOffset = event.mDistance;
		}
		break;

		case _SEEK_CURRENT:
		{
			file_handle->mOffset += event.mDistance;
		}
		break;

		case _SEEK_END:
		{
			PP_FileInfo file_info;
			GetPPResourceModule( )->GetPPBFileRef( )->Query( file_handle->mResource, &file_info, PP_BlockUntilComplete( ) );

			file_handle->mOffset = (_long)(file_info.size - event.mDistance);
		}
		break;

		default:
			break;
	}

	event.mRet = file_handle->mOffset;
}

static _void ProcessEvent( EventPeekFile& event )
{
	// Backup the current file pointer
	_dword old_offset = Platform::SeekFilePointer( event.mFileHandle, _SEEK_CURRENT, 0 );

	// Seek file pointer by offset
	if ( event.mOffset != -1 )
		Platform::SeekFilePointer( event.mFileHandle, _SEEK_BEGIN, event.mOffset );

	// Read the buffer data
	event.mRet = Platform::ReadFile( event.mFileHandle, event.mBufferData, event.mBufferSize );

	// Reset the file pointer
	Platform::SeekFilePointer( event.mFileHandle, _SEEK_BEGIN, old_offset );
}

static _void ProcessEvent( EventReadFile& event )
{
	chromeFileHandle* file_handle = (chromeFileHandle*) event.mFileHandle;
	if ( file_handle == _null )
		return;

	_long read_bytes = GetPPResourceModule( )->GetPPBFileIO( )->Read( file_handle->mResource, file_handle->mOffset, (_chara*) event.mBufferData, event.mBufferSize, PP_BlockUntilComplete( ) );
	if ( read_bytes >= 0 )
	{
		file_handle->mOffset += read_bytes;

		if ( event.mBytesRead != _null )
			*event.mBytesRead = read_bytes;

		event.mRet = _true;
	}
}

static _void ProcessEvent( EventWriteFile& event )
{
	chromeFileHandle* file_handle = (chromeFileHandle*) event.mFileHandle;
	if ( file_handle == _null )
		return;

	_long write_bytes = GetPPResourceModule( )->GetPPBFileIO( )->Write( file_handle->mResource, file_handle->mOffset, (const _chara*) event.mBufferData, event.mBufferSize, PP_BlockUntilComplete( ) );
	if ( write_bytes >= 0 )
	{
		file_handle->mOffset += write_bytes;

		if ( event.mBytesWrite != _null )
			*event.mBytesWrite = write_bytes;

		event.mRet = _true;
	}
}

static _void ProcessEvent( EventCreateDirectory& event )
{
	// Convert path from UTF-16 to UTF-8
	UString path_utf8 = "/" + UString( ).FromString( event.mPath );

	// Create directory referenced object
	PP_ResourcePassRef dir_res = GetPPResourceModule( )->GetPPBFileRef( )->Create( GetPPResourceModule( )->GetPPFileSystemRes( ), path_utf8.Str( ) );
	if ( dir_res == _null )
		return;

	// Create directory
	PPRET2BOOL( event.mRet, GetPPResourceModule( )->GetPPBFileRef( )->MakeDirectory( dir_res, PP_MAKEDIRECTORYFLAG_NONE, PP_BlockUntilComplete( ) ) );
//	Chrome_ReleaseResource( dir_res );
}

static _void ProcessEvent( EventGetFileAttributes& event )
{
	// Convert path from UTF-16 to UTF-8
	UString path_utf8 = "/" + UString( ).FromString( event.mFileName );

	// Create resource referenced object
	PP_ResourcePassRef res = GetPPResourceModule( )->GetPPBFileRef( )->Create( GetPPResourceModule( )->GetPPFileSystemRes( ), path_utf8.Str( ) );
	if ( res == _null )
		return;

	// Try to get file attributes
	PP_FileInfo file_info;
	PPRET2BOOL( event.mRet, GetPPResourceModule( )->GetPPBFileRef( )->Query( res, &file_info, PP_BlockUntilComplete( ) ) );

	// Get the attributes
	_dword* attributes = event.mAttributes;
	EGE_ASSERT( attributes != _null );

	// It's directory
	if ( file_info.type == PP_FILETYPE_DIRECTORY )
		*attributes |= _FILE_ATTRIBUTE_DIRECTORY;
}

//----------------------------------------------------------------------------
// chromeModule Implementation
//----------------------------------------------------------------------------

chromeModule::chromeModule( ) : BaseClass( L"chromeModule", Version( 1, 0, 0, 0 ) )
{
}

chromeModule::~chromeModule( )
{
}

_void chromeModule::HandleEvent( EventBase& event )
{
	switch ( event.mEventID )
	{
		case _EVENT_INIT_FILE_SYSTEM:		ProcessEvent( (EventInitFileSystem&) event ); break;
		case _EVENT_OPEN_DIR:				ProcessEvent( (EventOpenDir&) event ); break;
		case _EVENT_CLOSE_DIR:				ProcessEvent( (EventCloseDir&) event ); break;
		case _EVENT_READ_DIR:				ProcessEvent( (EventReadDir&) event ); break;
		case _EVENT_OPEN_FILE:				ProcessEvent( (EventOpenFile&) event ); break;
		case _EVENT_CLOSE_FILE:				ProcessEvent( (EventCloseFile&) event ); break;
		case _EVENT_SET_END_OF_FILE:		ProcessEvent( (EventSetEndOfFile&) event ); break;
		case _EVENT_GET_FILE_SIZE:			ProcessEvent( (EventGetFileSize&) event ); break;
		case _EVENT_SEEK_FILE:				ProcessEvent( (EventSeekFile&) event ); break;
		case _EVENT_PEEK_FILE:				ProcessEvent( (EventPeekFile&) event ); break;
		case _EVENT_READ_FILE:				ProcessEvent( (EventReadFile&) event ); break;
		case _EVENT_WRITE_FILE:				ProcessEvent( (EventWriteFile&) event ); break;
		case _EVENT_CREATE_DIRECTORY:		ProcessEvent( (EventCreateDirectory&) event ); break;
		case _EVENT_GET_FILE_ATTRIBUTES:	ProcessEvent( (EventGetFileAttributes&) event ); break;
		default:
			break;
	}
}
