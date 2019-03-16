//! @file     Pipe.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Pipe Implementation
//----------------------------------------------------------------------------

Pipe::Pipe( )
{
 mIsServerProcess = _false;
 mIsConnected  = _false;

 mType    = 0;
 mSize    = 0;
 mTimeout   = 0;
}

Pipe::~Pipe( )
{
 Disconnect( );
}

WString Pipe::BuildPipeName( WStringPtr pipename )
{
 _charw fixed_pipename[1024];
 return WString( Platform::FormatStringBuffer( fixed_pipename, 1024, L"\\\\.\\pipe\\%s", pipename.Str( ) ) );
}

_ubool Pipe::CreateServer( WStringPtr pipename, _dword type, _dword size, _dword timeout )
{
 // Build the pipe name
 WString fixed_pipename = BuildPipeName( pipename );

 // Initialize basic info
 mName  = pipename;
 mType  = type;
 mSize  = size;
 mTimeout = timeout;

 // Create the named pipe
 mObjectHandle = Platform::CreateNamedPipe( fixed_pipename.Str( ), _PIPE_ACCESS_DUPLEX, type, 32, size, size, timeout );
 if ( mObjectHandle == _null )
  return _false;

 mIsServerProcess = _true;

 return _true;
}

_ubool Pipe::CreateClient( WStringPtr pipename, _dword timeout )
{
 // Build the pipe name
 WString fixed_pipename = BuildPipeName( pipename );

 // Test connection
 if ( Platform::WaitNamedPipe( fixed_pipename.Str( ), timeout ) == _false )
  return _false;

 // Initialize basic info
 mName  = pipename;
 mType  = 0;
 mSize  = 0;
 mTimeout = timeout;

 // Open named pipe connection
 mObjectHandle = Platform::OpenFile( fixed_pipename.Str( ), _FILE_OPEN_EXISTING, _FILE_OPERATION_ALL, _FILE_SHARE_NONE, 0 );
 if ( mObjectHandle == _null )
  return _false;

 mIsServerProcess = _false;

 return _true;
}

_ubool Pipe::WaitConnection( )
{
 return mIsConnected = Platform::ConnectNamedPipe( mObjectHandle );
}

_ubool Pipe::IsConnected( ) const
{
 return mIsConnected;
}

_void Pipe::Disconnect( )
{
 // Only for server
 if ( mIsServerProcess )
  Platform::DisconnectNamedPipe( mObjectHandle );

 mIsConnected = _false;
}

_ubool Pipe::TestConnection( WStringPtr pipename, _dword timeout )
{
 // Build the pipe name
 WString fixed_pipename = BuildPipeName( pipename );

 return Platform::WaitNamedPipe( fixed_pipename.Str( ), timeout );
}

_dword Pipe::GetTotalAvailableSize( ) const
{
 _dword total_bytes_avail = 0;
 if ( Platform::PeekNamedPipe( mObjectHandle, _null, 0, _null, &total_bytes_avail, _null ) == _false )
  return -1;

 return total_bytes_avail;
}

_ubool Pipe::Read( _void* buffer, _dword size, _dword* bytesread )
{
 return Platform::ReadFile( mObjectHandle, buffer, size, bytesread );
}

_ubool Pipe::Write( const _void* buffer, _dword size, _dword* byteswritten )
{
 return Platform::WriteFile( mObjectHandle, buffer, size, byteswritten );
}