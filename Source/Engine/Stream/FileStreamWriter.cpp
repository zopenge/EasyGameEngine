//! @file     FileStreamWriter.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// FileStreamWriter Implementation
//----------------------------------------------------------------------------

FileStreamWriter::FileStreamWriter( )
{
}

FileStreamWriter::~FileStreamWriter( )
{
}

_ubool FileStreamWriter::Initialize( WStringPtr root_path, WStringPtr relative_file_name )
{
	// Build the resource file name
	mFileName = Path::BuildFilePath( root_path, relative_file_name );
	EGE_ASSERT( mFileName.IsEmpty( ) == _false );

	if ( mFile.Open( mFileName, _FILE_CREATE_ALWAYS, _FILE_OPERATION_WRITE, _FILE_SHARE_READ | _FILE_SHARE_WRITE ) == _false )
	{
		WLOG_ERROR_1( L"Open '%s' file stream writer failed", mFileName.Str( ) );
		return _false;
	}

	return _true;
}

_dword FileStreamWriter::GetSize( ) const
{
	return mFile.GetSize( );
}

_dword FileStreamWriter::RemoveBuffer( _dword size )
{
	return 0;
}

_ubool FileStreamWriter::SetCurOffsetAsEndPos( )
{
	return mFile.SetEndOfFile( );
}

_byte* FileStreamWriter::GetBuffer( )
{
	return _null;
}

_dword FileStreamWriter::WriteBuffer( const _void* buffer, _dword size )
{
	_dword write_bytes = 0;
	if ( mFile.WriteBuffer( buffer, size, &write_bytes ) == _false )
		return 0;

	return write_bytes;
}

_dword FileStreamWriter::WriteTiny( _tiny data )
{
	return WriteBuffer( &data, sizeof( _tiny ) );
}

_dword FileStreamWriter::WriteShort( _short data )
{
	return WriteBuffer( &data, sizeof( _short ) );
}

_dword FileStreamWriter::WriteLong( _int data )
{
	return WriteBuffer( &data, sizeof( _int ) );
}

_dword FileStreamWriter::WriteByte( _byte data )
{
	return WriteBuffer( &data, sizeof( _byte ) );
}

_dword FileStreamWriter::WriteWord( _word data )
{
	return WriteBuffer( &data, sizeof( _word ) );
}

_dword FileStreamWriter::WriteDword( _dword data )
{
	return WriteBuffer( &data, sizeof( _dword ) );
}

_dword FileStreamWriter::WriteQword( _qword data )
{
	return WriteBuffer( &data, sizeof( _qword ) );
}

_dword FileStreamWriter::WriteFloat( _float data )
{
	return WriteBuffer( &data, sizeof( _float ) );
}

_dword FileStreamWriter::WriteDouble( _double data )
{
	return WriteBuffer( &data, sizeof( _double ) );
}