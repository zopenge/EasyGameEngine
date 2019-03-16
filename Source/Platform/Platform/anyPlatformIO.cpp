//! @file     anyPlatformIO.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// anyPlatformIO Helpful Functions Implementation
//----------------------------------------------------------------------------

static _ubool TranslateFileMode( AString& mode, _FILE_CREATE_FLAG createflag, _dword operateflag )
{
	// Build the file mode
	switch ( createflag )
	{
		case _FILE_CREATE_NEW:
		{
			// Not support this ...
			return _false;
		}
		break;

		case _FILE_CREATE_ALWAYS:
		{
			if ( operateflag == _FILE_OPERATION_ALL )
			{
				mode = "w+b";
			}
			else if ( operateflag == _FILE_OPERATION_WRITE_APPEND )
			{
				mode = "a+b";
			}
			else
			{
				mode = "wb";
			}
		}
		break;

		case _FILE_OPEN_EXISTING:
		{
			if ( operateflag == _FILE_OPERATION_ALL )
			{
				mode = "r+b";
			}
			else if ( operateflag & _FILE_OPERATION_READ )
			{
				mode = "rb";
			}
			else if ( operateflag & _FILE_OPERATION_WRITE )
			{
				mode = "wb";
			}
			else
			{
				return _false;
			}
		}
		break;

		case _FILE_OPEN_ALWAYS:
		{
			if ( operateflag == _FILE_OPERATION_ALL )
			{
				mode = "r+b";
			}
			else if ( operateflag & _FILE_OPERATION_READ )
			{
				mode = "rb";
			}
			else if ( operateflag & _FILE_OPERATION_WRITE )
			{
				mode = "wb";
			}
			else
			{
				return _false;
			}
		}
		break;
	}

	return _true;
}

static _dword TranslateFileSeekFlag( _SEEK flag )
{
	switch ( flag )
	{
		case _SEEK_BEGIN:	return SEEK_SET;
		case _SEEK_CURRENT: return SEEK_CUR;
		case _SEEK_END:		return SEEK_END;
		default:
			return 0;
	}
}

//----------------------------------------------------------------------------
// anyPlatformIO Implementation
//----------------------------------------------------------------------------

_handle anyPlatformIO::OpenDir( const _charw* directory )
{
	_chara directory_ansi[1024];
	Platform::Utf16ToAnsi( directory_ansi, 1024, directory );

	DIR* dir_handle = ::opendir( directory_ansi );
	if ( dir_handle == _null )
	{
		OUTPUT_DEBUG_STRING( FORMAT_ASTRING_2( "Open '%s' directory failed, err:%s", (const _chara*)directory_ansi, strerror(errno) ) );
		return _null;
	}

	// Skip '..' files
	while ( _true )
	{
		// Read the directory
		dirent* ent = ::readdir( dir_handle );
		if ( ent == _null )
			break;

		if ( ent->d_name[0] == '.' && ent->d_name[1] == '.' && ent->d_name[2] == 0 )
			break;
	}

	return dir_handle;
}

_void anyPlatformIO::CloseDir( _handle handle )
{
	::closedir( (DIR*) handle );
}

_ubool anyPlatformIO::ReadDir( _handle handle, FileFinderData& finderdata )
{
	dirent* ent = _null;

	// Read the directory ( skip '.' file )
	while ( _true )
	{
		ent = ::readdir( (DIR*) handle );
		if ( ent == _null )
			return _false;

		if ( ent->d_name[0] == '.' && ent->d_name[1] == 0 )
			continue;
		else
			break;
	}

	// Copy the file name
	Platform::AnsiToUtf16( finderdata.mFileName, EGE_ARRAY_NUMBER( finderdata.mFileName ), ent->d_name );

	// Build the file attribute
	if ( ent->d_type == DT_DIR )
		finderdata.mFileAttributes |= _FILE_ATTRIBUTE_DIRECTORY;

	return _true;
}

_ubool anyPlatformIO::GetFileAttributes( const _charw* filename, _dword& attributes )
{
	// Convert file name to ANSI
	_chara filename_ansi[1024];
	Platform::Utf16ToAnsi( filename_ansi, 1024, filename );

	// Get the file / directory attributes
	struct stat stat_buf;
	if ( stat( filename_ansi, &stat_buf ) == -1 )
	{
		OUTPUT_DEBUG_STRING( FORMAT_ASTRING_2( "Get '%s' file attributes failed, error ID: %d", (const _chara*)filename_ansi, strerror(errno) ) );
		return _false;
	}

	// Clear the previous attributes
	attributes = 0;

	// Update the attributes
	if ( S_ISDIR( stat_buf.st_mode ) )
		attributes |= _FILE_ATTRIBUTE_DIRECTORY;

	return _true;
}

_ubool anyPlatformIO::SetFileAttributes( const _charw* filename, _dword attributes )
{
	return _true;
}

_handle anyPlatformIO::OpenFile( const _charw* filename, _FILE_CREATE_FLAG createflag, _dword operateflag, _dword shareflag, _dword attributes )
{
	// Build the file open mode
	AString mode;
	if ( TranslateFileMode( mode, createflag, operateflag ) == _false )
		return _null;

	// Convert the file name to ANSI
	_chara filename_ansi[2048];
	Platform::Utf16ToAnsi( filename_ansi, 2048, filename );

	// Open the file
	_handle file_handle = ::fopen( filename_ansi, mode.Str( ) );
    if ( file_handle == _null )
        return _null;

    return file_handle;
}

_void anyPlatformIO::CloseFile( _handle handle )
{
	if ( handle == _null )
		return;

	::fclose( (FILE*) handle );
}

_ubool anyPlatformIO::ReadFile( _handle handle, _void* buffer, _dword size, _dword* bytesread )
{
	// Get the file handle
	FILE* file_handle = (FILE*) handle;
	if ( file_handle == _null )
		return _false;

	// Read file buffers
	_dword read_bytes = ::fread( buffer, 1, size, (FILE*) handle );
	if ( ferror( file_handle ) )
		return _false;

	// Feedback the total read bytes
	if ( bytesread != _null )
		*bytesread = read_bytes;

	return _true;
}

_ubool anyPlatformIO::WriteFile( _handle handle, const _void* buffer, _dword size, _dword* byteswritten )
{
	// Get the file handle
	FILE* file_handle = (FILE*) handle;
	if ( file_handle == _null )
		return _false;

	// Write file buffers
	_dword write_bytes = ::fwrite( buffer, 1, size, (FILE*) handle );
	if ( ferror( file_handle ) )
	{
		OUTPUT_DEBUG_STRING( FORMAT_ASTRING_2( "Write '0x%.8x' file (size: %d) failed", (_dword) (size_t)handle, size ) );
		return _false;
	}

	// Feedback the total write bytes
	if ( byteswritten != _null )
		*byteswritten = write_bytes;

	return _true;
}

_ubool anyPlatformIO::FlushFileBuffers( _handle handle )
{
	return ::fflush( (FILE*) handle ) == 0;
}

_dword anyPlatformIO::SeekFilePointer( _handle handle, _SEEK flag, _int distance )
{
	// Seek the file pointer
	if ( ::fseek( (FILE*) handle, distance, TranslateFileSeekFlag( flag ) ) != 0 )
		return -1;
	
	// Get the current file position
	_int offset = ::ftell( (FILE*) handle );
	if ( offset == -1 )
		return -1;
	
	return offset;
}

_dword anyPlatformIO::GetFileSize( _handle handle )
{
	// Save the current file position
	_dword position = SeekFilePointer( handle, _SEEK_CURRENT, 0 );

	// Get the file size
	_dword file_size = SeekFilePointer( handle, _SEEK_END, 0 );

	// Resume the file position
	SeekFilePointer( handle, _SEEK_BEGIN, position );

	return file_size;
}

_ubool anyPlatformIO::SetEndOfFile( _handle handle )
{
	return SeekFilePointer( handle, _SEEK_END, 0 ) != -1;
}

_ubool anyPlatformIO::GetFileTime( _handle handle, FileTime* creation, FileTime* lastaccess, FileTime* lastwrite )
{
	return _true;
}

_ubool anyPlatformIO::SetFileTime( _handle handle, const FileTime* creation, const FileTime* lastaccess, const FileTime* lastwrite )
{
	return _true;
}

_ubool anyPlatformIO::DeleteFile( const _charw* filename )
{
	// Convert the path to ANSI
	_chara filename_ansi[1024];
	Platform::Utf16ToAnsi( filename_ansi, 1024, filename );

	if ( ::remove( filename_ansi ) != 0 )
	{
		OUTPUT_DEBUG_STRING( FORMAT_ASTRING_2( "Delete '%s' file failed, err:%s", (const _chara*)filename_ansi, strerror(errno) ) );
		return _false;
	}

	return _true;
}

_ubool anyPlatformIO::CopyFile( const _charw* desfilename, const _charw* srcfilename )
{
	if ( desfilename == _null || srcfilename == _null )
		return _false;

	AString dest; dest.FromString( _ENCODING_UTF16, desfilename );
	AString source; source.FromString( _ENCODING_UTF16, srcfilename );

	FILE* source_file = fopen(source.Str( ), "rb");
	if ( source_file == _null )
		return _false;

	FILE* dest_file	= fopen(dest.Str( ), "wb");
	if ( dest_file == _null )
	{
		fclose(source_file);
		return _false;
	}

	char buf[BUFSIZ]; size_t size;
	while ((size = fread(buf, 1, BUFSIZ, source_file))) {
		fwrite(buf, 1, size, dest_file);
	}

	fclose(source_file);
	fclose(dest_file);

	return _true;
}

_ubool anyPlatformIO::MoveFile( const _charw* desfilename, const _charw* srcfilename )
{
	if ( desfilename == _null || srcfilename == _null )
		return _false;

	AString dest; dest.FromString( _ENCODING_UTF16, desfilename );
	AString source; source.FromString( _ENCODING_UTF16, srcfilename );

	if ( ::rename( source.Str( ), dest.Str( ) ) != 0 )
	{
		OUTPUT_DEBUG_STRING( FORMAT_ASTRING_3( "Move '%s' -> '%s' file failed, err:%s", source.Str( ), dest.Str( ), strerror(errno) ) );
		return _false;
	}

	return _true;
}

_ubool anyPlatformIO::GetAbsoluteDirectory( const _charw* path, _charw* abs_path, _dword abs_path_length )
{
	if ( path == _null || abs_path == _null )
		return _false;

	AString path_ansi = AString( ).FromString( _ENCODING_UTF16, path );

	_chara abs_path_ansi[PATH_MAX]; abs_path_ansi[0] = 0;
	if ( ::realpath( path_ansi.Str( ), abs_path_ansi ) == _null )
		return _false;

	Platform::CopyString( abs_path, WString( ).FromString( _ENCODING_ANSI, abs_path_ansi ).Str( ), abs_path_length );

	return _true;
}

_ubool anyPlatformIO::GetCurrentDirectory( _charw* path, _dword length )
{
	return _true;
}

_ubool anyPlatformIO::SetCurrentDirectory( const _charw* path )
{
	return _true;
}

_ubool anyPlatformIO::CreateDirectory( const _charw* path )
{
	// Convert the path to ANSI
	_chara path_ansi[1024];
	Platform::Utf16ToAnsi( path_ansi, 1024, path );

	// Create directory
	if ( ::mkdir( path_ansi, S_IRWXU | S_IRWXG | S_IRWXO ) == -1 )
	{
		// The directory is existing
		if ( errno == EEXIST )
			return _true;
		
		OUTPUT_DEBUG_STRING( FORMAT_ASTRING_2( "Create '%s' directory failed, err:%s", (const _chara*)path_ansi, strerror(errno) ) );
		return _false;
	}

	return _true;
}

_ubool anyPlatformIO::RemoveDirectory( const _charw* path )
{
	// Convert the path to ANSI
	_chara path_ansi[1024];
	Platform::Utf16ToAnsi( path_ansi, 1024, path );

	// Remove directory
	if ( ::rmdir( path_ansi ) == -1 )
	{
		OUTPUT_DEBUG_STRING( FORMAT_ASTRING_2( "Remove '%s' directory failed, err:%s", (const _chara*)path_ansi, strerror(errno) ) );
		return _false;
	}

	return _true;
}
