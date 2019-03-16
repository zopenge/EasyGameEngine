//! @file     FileStreamReader.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// FileStreamReader Implementation
//----------------------------------------------------------------------------

FileStreamReader::FileStreamReader( )
{
	mFileSize	= 0;

	mTempBuffer = _null;
}

FileStreamReader::~FileStreamReader( )
{
	EGE_DELETE_ARRAY( mTempBuffer );
}

_ubool FileStreamReader::Initialize( WStringPtr root_path, WStringPtr relative_file_name )
{
	// Build the resource file name
	mFileName = Path::BuildFilePath( root_path, relative_file_name );
	if ( mFileName.IsEmpty( ) )
		return _false;

	if ( mFile.Open( mFileName, _FILE_OPEN_EXISTING, _FILE_OPERATION_READ, _FILE_SHARE_READ | _FILE_SHARE_WRITE ) == _false )
		return _false;

	mFileSize = mFile.GetSize( );

	return _true;
}

_dword FileStreamReader::GetSize( ) const
{
	return mFileSize;
}

IObject* FileStreamReader::CloneTo( _ubool standalone ) const
{
	FileStreamReader* stream_reader = new FileStreamReader( );
	if ( stream_reader->Initialize( L"", mFileName ) == _false )
		{ EGE_RELEASE( stream_reader ); return _null; }

	return stream_reader;
}

_dword FileStreamReader::GetRemainBytes( ) const
{ 
	return GetSize( ) - GetOffset( );
}

const _byte* FileStreamReader::GetBuffer( )
{
	if ( GetSize( ) == 0 )
		return _null;

	// Read file data into temporary buffer
	if ( mTempBuffer == _null )
	{
		mTempBuffer = new _byte[ GetSize( ) ];

		_dword cur_pos = Seek( _SEEK_CURRENT, 0 );

		Seek( _SEEK_BEGIN, 0 );
		ReadBuffer( mTempBuffer, GetSize( ) );
		Seek( _SEEK_BEGIN, (_int)cur_pos );
	}

	return mTempBuffer;
}

_ubool FileStreamReader::ReachEnd( ) const
{ 
	return GetSize( ) == GetOffset( );
}

_dword FileStreamReader::PeekBuffer( _void* buffer, _dword size )
{
	_dword bytesread = 0;
	if ( mFile.PeekBuffer( buffer, size, &bytesread ) == _false )
		return 0;

	return bytesread;
}

_dword FileStreamReader::PeekBuffer( _void* buffer, _dword size, _dword offset )
{
	_dword bytesread = 0;
	if ( mFile.PeekBuffer( buffer, size, offset, &bytesread ) == _false )
		return 0;

	return bytesread;
}

_dword FileStreamReader::ReadBuffer( _void* buffer, _dword size )
{
	_dword read_bytes = 0;
	if ( mFile.ReadBuffer( buffer, size, &read_bytes ) == _false )
		return 0;

	return read_bytes;
}

_dword FileStreamReader::ReadTiny( _tiny& data )
{
	return ReadBuffer( &data, sizeof( _tiny ) );
}

_dword FileStreamReader::ReadShort( _short& data )
{
	_dword read_bytes = ReadBuffer( &data, sizeof( _short ) );

	if ( GetEndian( ) != Platform::GetEndianType( ) )
		Math::BSwap16( data );

	return read_bytes;
}

_dword FileStreamReader::ReadLong( _int& data )
{
	_dword read_bytes = ReadBuffer( &data, sizeof( _int ) );

	if ( GetEndian( ) != Platform::GetEndianType( ) )
		Math::BSwap32( data );

	return read_bytes;
}

_dword FileStreamReader::ReadByte( _byte& data )
{
	return ReadBuffer( &data, sizeof( _byte ) );
}

_dword FileStreamReader::ReadWord( _word& data )
{
	_dword read_bytes = ReadBuffer( &data, sizeof( _word ) );

	if ( GetEndian( ) != Platform::GetEndianType( ) )
		Math::BSwap16( data );

	return read_bytes;
}

_dword FileStreamReader::ReadDword( _dword& data )
{
	_dword read_bytes = ReadBuffer( &data, sizeof( _dword ) );

	if ( GetEndian( ) != Platform::GetEndianType( ) )
		Math::BSwap32( data );

	return read_bytes;
}

_dword FileStreamReader::ReadQword( _qword& data )
{
	_dword read_bytes = ReadBuffer( &data, sizeof( _qword ) );

	if ( GetEndian( ) != Platform::GetEndianType( ) )
		Math::BSwap64( data );

	return read_bytes;
}

_dword FileStreamReader::ReadFloat( _float& data )
{
	_dword read_bytes = ReadBuffer( &data, sizeof( _float ) );

	if ( GetEndian( ) != Platform::GetEndianType( ) )
		Math::BSwapFloat( data );

	return read_bytes;
}

_dword FileStreamReader::ReadDouble( _double& data )
{
	_dword read_bytes = ReadBuffer( &data, sizeof( _double ) );

	if ( GetEndian( ) != Platform::GetEndianType( ) )
		Math::BSwapDouble( data );

	return read_bytes;
}