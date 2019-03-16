//! @file     Logger.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// Logger Implementation
//----------------------------------------------------------------------------

Logger::Logger( )
{
}

Logger::~Logger( )
{

}

_void Logger::OnPreWriteLogString( _LOG type, WString& string )
{
}

_void Logger::OnWriteLogString( WStringPtr string )
{
	// Output the log when we are debugging
	Platform::OutputDebugString( string.Str( ) );
}

//----------------------------------------------------------------------------
// FileLogger Implementation
//----------------------------------------------------------------------------

FileLogger::FileLogger( )
{
}

FileLogger::~FileLogger( )
{

}

_void FileLogger::OnPreWriteLogString( _LOG type, WString& string )
{
}

_void FileLogger::OnWriteLogString( WStringPtr string )
{
	// Write log
	mLogFile.WriteString( AString( ).FromString( string ) );

	// Output the log when we are debugging
	Platform::OutputDebugString( string.Str( ) );
}

_ubool FileLogger::Initialize( WStringPtr appname )
{
	if ( appname.IsBlank( ) )
		return _false;

	// Get the external path
	WString path = GetPlatform( )->GetExternalDirectory( );
	if ( path.IsEmpty( ) )
		path = GetPlatform( )->GetDocumentDirectory( );

	// Build the relative log file name with application name
	WString relative_log_filename = FORMAT_WSTRING_1( L"logs/%s.log", appname.Str( ) );

	// Build the absolute log file name 
	WString absolute_log_filepath = Path::BuildFilePath( path, relative_log_filename );

	// Create the log file 
	if ( mLogFile.Open( absolute_log_filepath, _FILE_CREATE_ALWAYS, _FILE_OPERATION_WRITE ) == _false )
		return _false;

	return _true;
}
