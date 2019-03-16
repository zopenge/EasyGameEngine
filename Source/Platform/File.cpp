//! @file     File.cpp
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// File Implementation
//----------------------------------------------------------------------------

File::File( )
{
 mObjectHandle = _null;
}

File::~File( )
{
 Close( );
}

_void File::Close( )
{
 Platform::CloseFile( mObjectHandle );
 mObjectHandle = _null;
}

_ubool File::Open( WStringPtr filename, _FILE_CREATE_FLAG createflag, _dword operateflag, _dword shareflag, _dword attributes )
{
 // Create directory if needed
 if ( createflag == _FILE_CREATE_NEW || createflag == _FILE_CREATE_ALWAYS || createflag == _FILE_OPEN_ALWAYS )
 {
  WString pathname = Path::GetDirectoryName( filename );

  // Create directory if it's not existing
  if ( pathname[0] != 0 && FileSystem::IsDirectoryExist( pathname.Str( ) ) == _false )
  {
   if ( FileSystem::CreateDir( pathname.Str( ) ) == _false )
    return _false;
  }
 }

 // Set file attribute to normal if it's existing
 if ( operateflag & _FILE_OPERATION_WRITE )
 {
  if ( FileSystem::IsFileExist( filename ) && FileSystem::SetAttributes( filename, _FILE_ATTRIBUTE_NORMAL ) == _false )
   return _false;
 }

 // Create file handle
 mObjectHandle = Platform::OpenFile( filename.Str( ), createflag, operateflag, shareflag, attributes );
 if ( mObjectHandle == _null )
  return _false;

 return _true;
}

_ubool File::PeekBuffer( _void* buffer, _dword size, _dword* bytesread )
{
 // Backup the current file pointer
 _dword offset = GetOffset( );

 // Read the buffer data
 _ubool ret = ReadBuffer( buffer, size, bytesread );

 // Reset the file pointer
 Seek( _SEEK_BEGIN, offset );

 return ret;
}

_ubool File::PeekBuffer( _void* buffer, _dword size, _dword offset, _dword* bytesread )
{
 // Backup the current file pointer
 _dword old_offset = GetOffset( );

 // Seek file pointer by offset
 if ( offset != -1 )
  Seek( _SEEK_BEGIN, offset );

 // Read the buffer data
 _ubool ret = ReadBuffer( buffer, size, bytesread );

 // Reset the file pointer
 Seek( _SEEK_BEGIN, old_offset );

 return ret;
}

_ubool File::ReadBuffer( _void* buffer, _dword size, _dword* bytesread )
{
 if ( bytesread != _null )
  *bytesread = 0;

 // Length is not zero, so buffer must be valid too.
 EGE_ASSERT( buffer != _null )

 // Read file buffer data
 return Platform::ReadFile( mObjectHandle, buffer, size, bytesread );
}

_ubool File::WriteBuffer( const _void* buffer, _dword size, _dword* byteswritten )
{
 if ( byteswritten != _null )
  *byteswritten = 0;

 // Length is not zero, so buffer must be valid too.
 EGE_ASSERT( buffer != _null )

 // Write file buffer data
 return Platform::WriteFile( mObjectHandle, buffer, size, byteswritten );
}

_ubool File::Flush( )
{
 return Platform::FlushFileBuffers( mObjectHandle );
}

_ubool File::ReadByte( _tiny& value )
{
 return ReadBuffer( &value, sizeof( _tiny ) );
}

_ubool File::ReadWord( _short& value )
{
 return ReadBuffer( &value, sizeof( _short ) );
}

_ubool File::ReadDword( _int& value )
{
 return ReadBuffer( &value, sizeof( _int ) );
}

_ubool File::ReadByte( _byte& value )
{
 return ReadBuffer( &value, sizeof( _byte ) );
}

_ubool File::ReadWord( _word& value )
{
 return ReadBuffer( &value, sizeof( _word ) );
}

_ubool File::ReadDword( _dword& value )
{
 return ReadBuffer( &value, sizeof( _dword ) );
}

_ubool File::ReadQword( _qword& value )
{
 return ReadBuffer( &value, sizeof( _qword ) );
}

_ubool File::ReadFloat( _float& value )
{
 return ReadBuffer( &value, sizeof( _float ) );
}

_ubool File::ReadDouble( _double& value )
{
 return ReadBuffer( &value, sizeof( _double ) );
}

_ubool File::WriteByte( _tiny value )
{
 return WriteBuffer( &value, sizeof( _tiny ) );
}

_ubool File::WriteWord( _short value )
{
 return WriteBuffer( &value, sizeof( _short ) );
}

_ubool File::WriteDword( _int value )
{
 return WriteBuffer( &value, sizeof( _int ) );
}

_ubool File::WriteByte( _byte value )
{
 return WriteBuffer( &value, sizeof( _byte ) );
}

_ubool File::WriteWord( _word value )
{
 return WriteBuffer( &value, sizeof( _word ) );
}

_ubool File::WriteDword( _dword value )
{
 return WriteBuffer( &value, sizeof( _dword ) );
}

_ubool File::WriteQword( _qword value )
{
 return WriteBuffer( &value, sizeof( _qword ) );
}

_ubool File::WriteFloat( _float value )
{
 return WriteBuffer( &value, sizeof( _float ) );
}

_ubool File::WriteDouble( _double value )
{
 return WriteBuffer( &value, sizeof( _double ) );
}

_ubool File::WriteString( AStringPtr string )
{
 return WriteBuffer( string.Str( ), string.GetLength( ) * sizeof( _chara ) );
}

_ubool File::WriteString( WStringPtr string )
{
 return WriteBuffer( string.Str( ), string.GetLength( ) * sizeof( _charw ) );
}

_ubool File::WriteUnicodeFlag( )
{
 return WriteWord( _word( _UTF16_HEADER ) );
}

_ubool File::WriteUTF8Flag( )
{
 _dword utf8flag = _UTF8_HEADER;
 return WriteBuffer( &utf8flag, 3 );
}

_dword File::Seek( _SEEK flag, _int distance )
{
 return Platform::SeekFilePointer( mObjectHandle, flag, distance );
}

_dword File::GetOffset( ) const
{
 return Platform::SeekFilePointer( mObjectHandle, _SEEK_CURRENT, 0 );
}

_dword File::GetSize( ) const
{
 return Platform::GetFileSize( mObjectHandle );
}

_ubool File::SetSize( _dword size )
{
 // Move pointer to the end of file
 if ( Seek( _SEEK_BEGIN, (_int) size ) == -1 )
  return _false;

 // Set it as end of file
 return SetEndOfFile( );
}

_ubool File::SetEndOfFile( )
{
 return Platform::SetEndOfFile( mObjectHandle );
}

_ubool File::GetTimes( FileTime* creation, FileTime* lastaccess, FileTime* lastwrite ) const
{
 return Platform::GetFileTime( mObjectHandle, creation, lastaccess, lastwrite );
}

_ubool File::GetTimes( CalendarTime* creation, CalendarTime* lastaccess, CalendarTime* lastwrite ) const
{
 // Get the file time
 FileTime file_creationtime, file_lastaccesstime, file_lastwritetime;
 if ( GetTimes( &file_creationtime, &file_lastaccesstime, &file_lastwritetime ) == _false )
  return _false;

 // Feedback the file creation time
 if ( creation != _null )
 {
  Platform::FileTimeToLocalFileTime( file_creationtime, file_creationtime );
  Platform::FileTimeToSystemTime( *creation, file_creationtime );
 }

 // Feedback the file last access time
 if ( lastaccess != _null )
 {
  Platform::FileTimeToLocalFileTime( file_lastaccesstime, file_lastaccesstime );
  Platform::FileTimeToSystemTime( *lastaccess, file_lastaccesstime );
 }

 // Feedback the file last write time
 if ( lastwrite != _null )
 {
  Platform::FileTimeToLocalFileTime( file_lastwritetime, file_lastwritetime );
  Platform::FileTimeToSystemTime( *lastwrite, file_lastwritetime );
 }

 return _true;
}

_ubool File::SetTimes( const CalendarTime* creation, const CalendarTime* lastaccess, const CalendarTime* lastwrite )
{
 FileTime file_creationtime, file_lastaccesstime, file_lastwritetime;

 FileTime* file_creationtime_ptr  = _null;
 FileTime* file_lastaccesstime_ptr = _null;
 FileTime* file_lastwritetime_ptr = _null;

 // Get the creation time of file
 if ( creation != _null )
 {
  file_creationtime_ptr = &file_creationtime;
  Platform::SystemTimeToFileTime( file_creationtime, *creation );
  Platform::LocalFileTimeToFileTime( file_creationtime, file_creationtime );
 }

 // Get the last access time of file
 if ( lastaccess != _null )
 {
  file_lastaccesstime_ptr = &file_lastaccesstime;
  Platform::SystemTimeToFileTime( file_lastaccesstime, *lastaccess );
  Platform::LocalFileTimeToFileTime( file_lastaccesstime, file_lastaccesstime );
 }

 // Get the last write time of file
 if ( lastwrite != _null )
 {
  file_lastwritetime_ptr = &file_lastwritetime;
  Platform::SystemTimeToFileTime( file_lastwritetime, *lastwrite );
  Platform::LocalFileTimeToFileTime( file_lastwritetime, file_lastwritetime );
 }

 // Set the file time
 return Platform::SetFileTime( mObjectHandle, file_creationtime_ptr, file_lastaccesstime_ptr, file_lastwritetime_ptr );
}
