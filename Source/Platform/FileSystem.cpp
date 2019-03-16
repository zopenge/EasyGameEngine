//! @file     FileSystem.cpp
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// FileSystem Helpful Functions Implementation
//----------------------------------------------------------------------------

static _ubool _TrimDir( WStringPtr directory, _ubool& no_any_files_in_it )
{
	// Check directory name
	if ( directory.IsEmpty( ) )
		return _false;

	// Initialize the files tag
	no_any_files_in_it = _true;

	// Open the directory
	FileFinder filefinder;
	if ( filefinder.Open( directory ) == _false )
		return _false;

	// Walk the directory
	FileInfo fileinfo;
	while ( filefinder.Walk( fileinfo, L"", 0, 1 ) )
	{
		_charw filename[1024];
		Platform::FormatStringBuffer( filename, 1024, L"%s/%s", directory.Str( ), fileinfo.mFileName.Str( ) );

		// Found a sub directory
		if ( fileinfo.mAttributes & _FILE_ATTRIBUTE_DIRECTORY )
		{
			// Trim sub directory recursively
			if ( _TrimDir( filename, no_any_files_in_it ) == _false )
				return _false;

			// Delete sub directory itself
			if ( no_any_files_in_it )
			{
				Platform::SetFileAttributes( filename, _FILE_ATTRIBUTE_NORMAL | _FILE_ATTRIBUTE_DIRECTORY );
				Platform::RemoveDirectory( filename );
			}
		}
		// Found a file
		else
		{
			no_any_files_in_it = _false;
		}
	}

	return _true;
}

//----------------------------------------------------------------------------
// FileSystem Implementation
//----------------------------------------------------------------------------

_ubool FileSystem::IsFileExist( WStringPtr filename )
{
	_dword attributes = 0;
	if ( Platform::GetFileAttributes( filename.Str( ), attributes ) == _false )
		return _false;

	return ( attributes & _FILE_ATTRIBUTE_DIRECTORY ) == 0;
}

_ubool FileSystem::IsDirectoryExist( WStringPtr directory )
{
	_dword attributes = 0;
	if ( Platform::GetFileAttributes( directory.Str( ), attributes ) == _false )
		return _false;

	return ( attributes & _FILE_ATTRIBUTE_DIRECTORY ) != 0;
}

_ubool FileSystem::IsDirectoryEmpty( WStringPtr directory )
{
	// Open the directory
	FileFinder filefinder;
	if ( filefinder.Open( directory ) )
	{
		// Walk it to check whether the directory is empty or not
		FileInfo fileinfo;
		if ( filefinder.Walk( fileinfo, L"", 0, 1 ) == _false )
			return _true; // It's empty directory
	}

	return _false;
}

WString FileSystem::GetInternalPathInDomains( )
{
	_charw path[1024];
	if ( Platform::GetInternalPathInDomains( path, 1024 ) == _false )
		return WString( L"" );

	return WString( path );
}

WString FileSystem::GetExternalPathInDomains( )
{
	_charw path[1024];
	if ( Platform::GetExternalPathInDomains( path, 1024 ) == _false )
		return WString( L"" );

	return WString( path );
}

WString FileSystem::GetDocumentPathInDomains( )
{
	_charw path[1024];
	if ( Platform::GetDocumentPathInDomains( path, 1024 ) == _false )
		return WString( L"" );

	return WString( path );
}

_ubool FileSystem::GetTempDirName( WStringPtr path, WString& name )
{
	// The path must be existing
	if ( path.IsEmpty( ) == _false && IsDirectoryExist( path ) == _false )
		return _false;

	// We try to use the random number to find the unique directory
	for ( _dword i = 0; i < 1024 * 1024; i ++ )
	{
		// Build the random number as part of prefix and suffix name
		_dword prefix_number = Random::Gen( (_dword) 256, (_dword) 0xFFFFFFFF );
		_dword suffix_number = Random::Gen( (_dword) 256, (_dword) 0xFFFFFFFF );

		// Build the directory name
		if ( path.IsEmpty( ) == _false )
		{
			name = path;
			name += L"/";
		}

		// Add prefix and suffix name
		_charw name_buffer[1024];
		name += Platform::FormatStringBuffer( name_buffer, 1024, L"%d.%d", prefix_number, suffix_number );

		// Check whether the directory is existing or not
		if ( IsDirectoryExist( name ) == _false )
			return _true;
	}

	return _false;
}

_ubool FileSystem::GetTempFileName( WStringPtr path, WStringPtr extensionname, WString& filename )
{
	// The path must be existing
	if ( path.IsEmpty( ) == _false && IsDirectoryExist( path ) == _false )
	{
		if ( FileSystem::CreateDir( path ) == _false )
			return _false;
	}

	// Find the unique file name 
	for ( _dword i = 0; i < 1024; i ++ )
	{
		// Build the directory name
		if ( path.IsEmpty( ) == _false )
		{
			filename = path;
			filename += L"/";
		}

		// Add prefix and suffix name
		_charw name_buffer[1024];
		filename += Platform::FormatStringBuffer( name_buffer, 1024, L"%d.%s", i, extensionname.Str( ) );

		// Check whether the file is existing or not
		if ( IsFileExist( filename ) == _false )
			return _true;
	}

	// We try to use the random number to find the unique file
	for ( _dword i = 0; i < 1024 * 1024; i ++ )
	{
		// Build the random number as part of prefix name
		_dword prefix_number = Random::Gen( (_dword) 256, (_dword) 0xFFFFFFFF );

		// Build the directory name
		if ( path.IsEmpty( ) == _false )
		{
			filename = path;
			filename += L"/";
		}

		// Add prefix and suffix name
		_charw name_buffer[1024];
		filename += Platform::FormatStringBuffer( name_buffer, 1024, L"%d.%s", prefix_number, extensionname.Str( ) );

		// Check whether the file is existing or not
		if ( IsFileExist( filename ) == _false )
			return _true;
	}

	return _false;
}

_ubool FileSystem::GetFileSize( WStringPtr filename, _dword& bytes )
{
	File file;
	if ( file.Open( filename, _FILE_OPEN_EXISTING, 0 ) == _false )
		return _false;

	bytes = file.GetSize( );

	return bytes != -1;
}

_ubool FileSystem::GetAttributes( WStringPtr filename, _dword& attributes )
{
	return Platform::GetFileAttributes( filename.Str( ), attributes );
}

_ubool FileSystem::SetAttributes( WStringPtr filename, _dword attributes )
{
	return Platform::SetFileAttributes( filename.Str( ), attributes );
}

_ubool FileSystem::GetTimes( WStringPtr filename, FileTime* creation, FileTime* lastaccess, FileTime* lastwrite )
{
	File file;
	if ( file.Open( filename, _FILE_OPEN_EXISTING, _FILE_OPERATION_READ ) == _false )
		return _false;

	return file.GetTimes( creation, lastaccess, lastwrite );
}

_ubool FileSystem::GetTimes( WStringPtr filename, CalendarTime* creation, CalendarTime* lastaccess, CalendarTime* lastwrite )
{
	File file;
	if ( file.Open( filename, _FILE_OPEN_EXISTING, _FILE_OPERATION_READ ) == _false )
		return _false;

	return file.GetTimes( creation, lastaccess, lastwrite );
}

_ubool FileSystem::SetTimes( WStringPtr filename, CalendarTime* creation, CalendarTime* lastaccess, CalendarTime* lastwrite )
{
	File file;
	if ( file.Open( filename, _FILE_OPEN_EXISTING, _FILE_OPERATION_WRITE, _FILE_SHARE_READ ) == _false )
		return _false;

	return file.SetTimes( creation, lastaccess, lastwrite );
}

_ubool FileSystem::CreateFile( WStringPtr filename, _dword attributeflag )
{
	File file;
	if ( file.Open( filename, _FILE_OPEN_ALWAYS, _FILE_OPERATION_WRITE, _FILE_SHARE_READ, attributeflag ) == _false )
		return _false;

	return _true;
}

_ubool FileSystem::CreateFile( WStringPtr filename, AStringPtr string, _dword attributeflag )
{
	return CreateFile( filename, string.GetLength( ), string.Str( ), attributeflag );
}

_ubool FileSystem::CreateFile( WStringPtr filename, _dword size, const _void* buffer, _dword attributeflag )
{
	File file;
	if ( file.Open( filename, _FILE_CREATE_ALWAYS, _FILE_OPERATION_WRITE, _FILE_SHARE_READ, attributeflag ) == _false )
		return _false;

	if ( buffer != _null && size != _null )
	{
		if ( file.WriteBuffer( buffer, size ) == _false )
			return _false;
	}
	else if ( size != _null )
	{
		if ( file.SetSize( size ) == _false )
			return _false;
	}

	return _true;
}

_ubool FileSystem::DeleteFile( WStringPtr filename )
{
	if ( IsFileExist( filename ) == _false )
		return _true;

	// First set file attribute to normal.
	if ( SetAttributes( filename, _FILE_ATTRIBUTE_NORMAL ) == _false )
		return _false;

	// Delete the file.
	return Platform::DeleteFile( filename.Str( ) );
}

_ubool FileSystem::CopyFile( WStringPtr desfilename, WStringPtr srcfilename )
{
	if ( IsFileExist( srcfilename ) == _false )
		return _false;

	// Get the path name
	WString pathname = Path::GetDirectoryName( desfilename );

	// Create directory if needed
	if ( CreateDir( pathname.Str( ) ) == _false )
		return _false;

	return Platform::CopyFile( desfilename.Str( ), srcfilename.Str( ) );
}

_ubool FileSystem::MoveFile( WStringPtr desfilename, WStringPtr srcfilename )
{
	if ( IsFileExist( srcfilename ) == _false )
		return _false;

	// Get the path name
	WString pathname = Path::GetDirectoryName( desfilename );

	// Create directory if needed
	if ( CreateDir( pathname.Str( ) ) == _false )
		return _false;

	return Platform::MoveFile( desfilename.Str( ), srcfilename.Str( ) );
}

_ubool FileSystem::ReadFile( WStringPtr filename, AString& string )
{
	_ENCODING encoding = GetFileEncodingType( filename );
	if ( encoding == _ENCODING_UNKNOWN )
		return _false;

	File file;
	if ( file.Open( filename, _FILE_OPEN_EXISTING, _FILE_OPERATION_READ, _FILE_SHARE_READ ) == _false )
		return _false;

	_dword file_size = file.GetSize( );
	if ( file_size == 0 )
		return _false;

	MemArrayPtr< _byte > buffer( file_size + 1 ); buffer[ file_size ] = 0;
	file.ReadBuffer( buffer, file_size );

	string.FromString( encoding, buffer.GetPointer( ) );

	return _true;
}

_ubool FileSystem::ReadFile( WStringPtr filename, UString& string )
{
	AString string_ansi;
	if ( ReadFile( filename, string_ansi ) == _false )
		return _false;

	string.FromString( string_ansi );

	return _true;
}

_ubool FileSystem::ReadFile( WStringPtr filename, WString& string )
{
	AString string_ansi;
	if ( ReadFile( filename, string_ansi ) == _false )
		return _false;

	string.FromString( string_ansi );

	return _true;
}

_ENCODING FileSystem::GetFileEncodingType( WStringPtr filename )
{
	File file;
	if ( file.Open( filename, _FILE_OPEN_EXISTING, _FILE_OPERATION_READ, _FILE_SHARE_READ ) == _false )
		return _ENCODING_UNKNOWN;

	_dword size = file.GetSize( );
	if ( size == 0 )
		return _ENCODING_UNKNOWN;

	_byte encoding_tag[4];
	file.ReadBuffer( encoding_tag, sizeof( encoding_tag ) );

	if ( encoding_tag[0] == _UTF16_HEADER_0 && encoding_tag[1] == _UTF16_HEADER_1 )
	{
		return _ENCODING_UTF16;
	}
	else if ( encoding_tag[0] == _UTF8_HEADER_0 && encoding_tag[1] == _UTF8_HEADER_1 && encoding_tag[2] == _UTF8_HEADER_2 )
	{
		return _ENCODING_UTF8;
	}

	return _ENCODING_ANSI;
}

WString FileSystem::GetCurrentDir( )
{	
	_charw buffer[1024];
	if ( Platform::GetCurrentDirectory( buffer, 1024 ) == _false )
		return WString( L"" );

	return WString( buffer );
}

_ubool FileSystem::SetCurrentDir( WStringPtr directory )
{
	// Create directory as needed.
	if ( CreateDir( directory ) == _false )
		return _false;

	return Platform::SetCurrentDirectory( directory.Str( ) );
}

_ubool FileSystem::CreateDir( WStringPtr directory )
{
	if ( directory.IsEmpty( ) )
		return _false;

	if ( IsDirectoryExist( directory ) )
		return _true;

	if ( directory[ directory.GetLength( ) - 1 ] == ':' )
		return _true;

	// Auto create middle path
	for ( _dword i = 0; directory[i] != 0; i ++ )
	{
		if ( directory[i] != '\\' && directory[i] != '/' )
			continue;

		if ( i == 0 )
			continue;

		if ( directory[ i - 1 ] == ':' )
			continue;

		WString middlepath( directory.Str( ), i );

		if ( IsDirectoryExist( middlepath ) )
			continue;

		if ( Platform::CreateDirectory( middlepath.Str( ) ) == _false )
			return _false;
	}

	return Platform::CreateDirectory( directory.Str( ) );
}

_ubool FileSystem::DeleteDir( WStringPtr directory )
{
	if ( directory.IsEmpty( ) )
		return _false;

	// Open the directory
	FileFinder filefinder;
	if ( filefinder.Open( directory ) == _false )
		return _false;

	// Walk the directory
	FileInfo fileinfo;
	while ( filefinder.Walk( fileinfo, L"", 0, 1 ) )
	{
		_charw filename[1024];
		Platform::FormatStringBuffer( filename, 1024, L"%s/%s", directory.Str( ), fileinfo.mFileName.Str( ) );

		// Found a sub directory
		if ( fileinfo.mAttributes & _FILE_ATTRIBUTE_DIRECTORY )
		{
			// Delete sub directory recursively
			DeleteDir( filename );

			// Delete sub directory itself
			Platform::SetFileAttributes( filename, _FILE_ATTRIBUTE_NORMAL | _FILE_ATTRIBUTE_DIRECTORY );
			Platform::RemoveDirectory( filename );
		}
		// Found a file.
		else
		{
			// Delete a file
			Platform::SetFileAttributes( filename, _FILE_ATTRIBUTE_NORMAL );
			Platform::DeleteFile( filename );
		}
	}

	// Close the file finder
	filefinder.Close( );

	// Delete root directory
	Platform::SetFileAttributes( directory.Str( ), _FILE_ATTRIBUTE_NORMAL | _FILE_ATTRIBUTE_DIRECTORY );
	Platform::RemoveDirectory( directory.Str( ) );

	return _true;
}

_ubool FileSystem::CopyDir( WStringPtr desdirectory, WStringPtr srcdirectory )
{
	if ( desdirectory.IsEmpty( ) || srcdirectory.IsEmpty( ) )
		return _false;

	// Open the source directory
	FileFinder filefinder;
	if ( filefinder.Open( srcdirectory ) == _false )
		return _false;

	// Walk the source directory
	FileInfo fileinfo;
	while ( filefinder.Walk( fileinfo, L"", 0, 1 ) )
	{
		_charw srcfilename[1024], desfilename[1024];
		Platform::FormatStringBuffer( srcfilename, 1024, L"%s/%s", srcdirectory.Str( ), fileinfo.mFileName.Str( ) );
		Platform::FormatStringBuffer( desfilename, 1024, L"%s/%s", desdirectory.Str( ), fileinfo.mFileName.Str( ) );

		// Found a sub directory
		if ( fileinfo.mAttributes & _FILE_ATTRIBUTE_DIRECTORY )
		{
			// Copy sub directory itself
			CreateDir( desfilename );

			// Copy sub directory recursively
			CopyDir( desfilename, srcfilename );
		}
		// Found a file
		else
		{
			// Copy a file
			CopyFile( desfilename, srcfilename );
		}
	}

	return _true;
}

_ubool FileSystem::MoveDir( WStringPtr desdirectory, WStringPtr srcdirectory )
{
	if ( desdirectory.IsEmpty( ) || srcdirectory.IsEmpty( ) )
		return _false;

	// Open the source directory
	FileFinder filefinder;
	if ( filefinder.Open( srcdirectory ) == _false )
		return _false;

	// Walk the source directory
	FileInfo fileinfo;
	while ( filefinder.Walk( fileinfo, L"", 0, 1 ) )
	{
		_charw srcfilename[1024], desfilename[1024];
		Platform::FormatStringBuffer( srcfilename, 1024, L"%s/%s", srcdirectory.Str( ), fileinfo.mFileName.Str( ) );
		Platform::FormatStringBuffer( desfilename, 1024, L"%s/%s", desdirectory.Str( ), fileinfo.mFileName.Str( ) );

		// Found a sub directory.
		if ( fileinfo.mAttributes & _FILE_ATTRIBUTE_DIRECTORY )
		{
			// Copy sub directory itself
			CreateDir( desfilename );

			// Move sub directory recursively
			MoveDir( desfilename, srcfilename );

			// Delete sub directory itself
			Platform::SetFileAttributes( srcfilename, _FILE_ATTRIBUTE_NORMAL | _FILE_ATTRIBUTE_DIRECTORY );
			Platform::RemoveDirectory( srcfilename );
		}
		// Found a file
		else
		{
			// Move a file
			MoveFile( desfilename, srcfilename );
		}
	}

	// Close the file finder
	filefinder.Close( );

	// Delete root directory
	Platform::SetFileAttributes( srcdirectory.Str( ), _FILE_ATTRIBUTE_NORMAL | _FILE_ATTRIBUTE_DIRECTORY );
	Platform::RemoveDirectory( srcdirectory.Str( ) );

	return _true;
}

_ubool FileSystem::TrimDir( WStringPtr directory )
{
	_ubool no_any_files_in_it = _false;
	if ( _TrimDir( directory, no_any_files_in_it ) == _false )
		return _false;

	return _true;
}

_ubool FileSystem::CleanDir( WStringPtr directory )
{
	if ( directory.IsEmpty( ) )
		return _false;

	// Open the directory
	FileFinder filefinder;
	if ( filefinder.Open( directory ) == _false )
		return _false;

	// Walk the directory
	FileInfo fileinfo;
	while ( filefinder.Walk( fileinfo, L"", 0, 1 ) )
	{
		_charw filename[1024];
		Platform::FormatStringBuffer( filename, 1024, L"%s/%s", directory.Str( ), fileinfo.mFileName.Str( ) );

		// Found a sub directory
		if ( ( fileinfo.mAttributes & _FILE_ATTRIBUTE_DIRECTORY ) != 0 )
		{
			// Clean sub directory recursively
			if ( CleanDir( filename ) == _true )
			{
				// Delete sub directory itself
				Platform::SetFileAttributes( filename, _FILE_ATTRIBUTE_NORMAL | _FILE_ATTRIBUTE_DIRECTORY );
				Platform::RemoveDirectory( filename );
			}
		}
		// Found a file
		else
		{
			// Delete sub file
			Platform::SetFileAttributes( filename, _FILE_ATTRIBUTE_NORMAL );
			Platform::DeleteFile( filename );
		}
	}

	return _true;
}

_ubool FileSystem::Delete( WStringPtr path )
{
	if ( IsDirectoryExist( path ) )
		return DeleteDir( path );
	else
		return DeleteFile( path );
}

_ubool FileSystem::GetDiskSpace( WStringPtr directory, _qword& total, _qword& available )
{
	_ubool autocreate = _false;

	if ( IsFileExist( directory ) == _false && IsDirectoryExist( directory ) == _false )
	{
		CreateDir( directory );

		autocreate = _true;
	}

	_ubool retval = Platform::GetDiskFreeSpace( directory.Str( ), &available, &total );

	if ( autocreate == _true )
	{
		DeleteDir( directory );
	}

	return retval;
}

_ubool FileSystem::CompareFile( WStringPtr srcfilename, WStringPtr desfilename )
{
	File srcfile, desfile;

	// Open source file.
	if ( srcfile.Open( srcfilename, _FILE_OPEN_EXISTING, _FILE_OPERATION_READ, _FILE_SHARE_READ ) == _false )
		return _false;

	// Open target file.
	if ( desfile.Open( desfilename, _FILE_OPEN_EXISTING, _FILE_OPERATION_READ, _FILE_SHARE_READ ) == _false )
		return _false;

	if ( srcfile.GetSize( ) != desfile.GetSize( ) )
		return _false;

	const _dword cMaxBufferSize = 64 KB;
	MemArrayPtr< _byte > buffer1( cMaxBufferSize );
	MemArrayPtr< _byte > buffer2( cMaxBufferSize );

	_dword length1 = 0, length2 = 0;

	while ( _true )
	{
		if ( srcfile.ReadBuffer( buffer1, cMaxBufferSize, &length1 ) == _false )
			return _false;

		if ( desfile.ReadBuffer( buffer2, cMaxBufferSize, &length2 ) == _false )
			return _false;

		if ( length1 != length2 )
			return _false;

		if ( length1 == 0 )
			break;

		// Compare data read from files.
		if ( EGE_MEM_CMP( buffer1, buffer2, length1 ) != 0 )
			return _false;
	}

	return _true;
}

_ubool FileSystem::CompareDir( WStringPtr srcdirectory, WStringPtr desdirectory, _ubool deletesame )
{
	if ( srcdirectory.IsEmpty( ) || desdirectory.IsEmpty( ) )
		return _false;

	_ubool compareresult = _true;

	// Open the source directory
	FileFinder filefinder;
	if ( filefinder.Open( srcdirectory ) == _false )
		return _false;

	// Walk the source directory
	FileInfo fileinfo;
	while ( filefinder.Walk( fileinfo, L"", 0, 1 ) )
	{
		_charw srcfilename[1024], desfilename[1024];
		Platform::FormatStringBuffer( srcfilename, 1024, L"%s/%s", srcdirectory.Str( ), fileinfo.mFileName.Str( ) );
		Platform::FormatStringBuffer( desfilename, 1024, L"%s/%s", desdirectory.Str( ), fileinfo.mFileName.Str( ) );

		// Found a sub directory
		if ( fileinfo.mAttributes & _FILE_ATTRIBUTE_DIRECTORY )
		{
			// Compare sub directory recursively
			if ( CompareDir( srcfilename, desfilename, deletesame ) == _false )
				compareresult = _false;

			if ( deletesame == _false && compareresult == _false )
				return _false;
		}
		// Found a file
		else
		{
			// Compare files
			if ( CompareFile( srcfilename, desfilename ) == _false )
			{
				compareresult = _false;
			}
			else if ( deletesame )
			{
				DeleteFile( desfilename );
			}

			if ( deletesame == _false && compareresult == _false )
				return _false;
		}
	}

	return compareresult;
}

_ubool FileSystem::EnumResources( WStringPtr path, WStringPtr filter, _dword flags, _dword depth, FileInfoArray& items )
{
	if ( path.IsEmpty( ) )
		return _false;

	// Create file finder
	FileFinder file_finder;
	if ( file_finder.Open( path ) == _false )
		return _false;

	// Start to walk
	FileInfo file_info;
	while ( file_finder.Walk( file_info, filter, flags, depth ) )
	{
		items.Append( file_info );
	}

	return _true;
}

_ubool FileSystem::IsTextFile( WStringPtr filename )
{
	File file;
	if ( file.Open( filename, _FILE_OPEN_EXISTING, _FILE_OPERATION_READ ) == _false )
		return _false;

	_dword file_size = file.GetSize( );
	if ( file_size == 0 )
		return _false;

	MemArrayPtr< _byte > file_buffer( file_size );
	if ( file.ReadBuffer( file_buffer, file_size ) == _false )
		return _false;

	const _byte* pointer = file_buffer;
	SKIP_UTF_CODE( pointer, file_size );

	for ( _dword i = 0; i < file_size; i ++ )
	{
		if ( pointer[i] == 0 )
			return _false;
	}

	return _true;
}