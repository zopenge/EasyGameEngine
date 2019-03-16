//! @file   StorageFileStreamReader.cpp
//! @author  LiCode
//! @version 1.0.0.613
//! @date   2011/01/17
//! Copyright ...

#include "EGEStorage.h"

//----------------------------------------------------------------------------
// StorageFileStreamReader Implementation
//----------------------------------------------------------------------------

StorageFileStreamReader::StorageFileStreamReader( )
{
}

StorageFileStreamReader::~StorageFileStreamReader( )
{
}

_ubool StorageFileStreamReader::Initialize( WStringPtr root_path, WStringPtr relative_file_name )
{
	// Build the resource file name
	WString file_name = Path::BuildFilePath( root_path, relative_file_name );
	EGE_ASSERT( file_name.IsEmpty( ) == _false );

	// Create file stream reader
	mStreamReader = GetInterfaceFactory( )->CreateFileStreamReader( file_name );
	if ( mStreamReader.IsNull( ) )
		return _false;

	return _true;
}

_void StorageFileStreamReader::Uninitialize( )
{
	mStreamReader.Clear( );
}

WStringPtr StorageFileStreamReader::GetFileName( ) const
{
	return mStreamReader->GetFileName( );
}

_STREAM_TYPE StorageFileStreamReader::GetType( ) const
{
	return mStreamReader->GetType( );
}

_STREAM_SHARE_MODE StorageFileStreamReader::GetShareMode( ) const
{
	return mStreamReader->GetShareMode( );
}

_dword StorageFileStreamReader::GetSize( ) const
{
	return mStreamReader->GetSize( );
}

_dword StorageFileStreamReader::GetOffset( ) const
{
	return mStreamReader->GetOffset( );
}

const _byte* StorageFileStreamReader::GetBuffer( )
{
	return mStreamReader->GetBuffer( );
}

_dword StorageFileStreamReader::Seek( _SEEK flag, _long distance )
{
	return mStreamReader->Seek( flag, distance );
}

_dword StorageFileStreamReader::SeekByArrangedValueFromBegin( _dword value )
{
	return mStreamReader->SeekByArrangedValueFromBegin( value );
}

_void StorageFileStreamReader::SetEndian( _ENDIAN endian )
{
	mStreamReader->SetEndian( endian );
}

_ENDIAN StorageFileStreamReader::GetEndian( ) const
{
	return mStreamReader->GetEndian( );
}

IStreamReaderPassRef StorageFileStreamReader::CloneTo( )
{
	StorageFileStreamReader* storage_file_stream_reader = new StorageFileStreamReader( );

	// Create file stream reader
	storage_file_stream_reader->mStreamReader = GetInterfaceFactory( )->CreateFileStreamReader( mStreamReader->GetFileName( ) );
	if ( storage_file_stream_reader->mStreamReader.IsNull( ) )
		{ EGE_RELEASE( storage_file_stream_reader ); return _null; }

	return storage_file_stream_reader;
}

_dword StorageFileStreamReader::GetRemainBytes( ) const
{
	return mStreamReader->GetRemainBytes( );
}

_ubool StorageFileStreamReader::ReachEnd( ) const
{
	return mStreamReader->ReachEnd( );
}

_dword StorageFileStreamReader::PeekBuffer( _void* buffer, _dword size )
{
	return mStreamReader->PeekBuffer( buffer, size );
}

_dword StorageFileStreamReader::PeekBuffer( _void* buffer, _dword size, _dword offset )
{
	return mStreamReader->PeekBuffer( buffer, size, offset );
}

_dword StorageFileStreamReader::ReadBuffer( _void* buffer, _dword size )
{
	return mStreamReader->ReadBuffer( buffer, size );
}

_dword StorageFileStreamReader::ReadByte( _tiny& data )
{
	return mStreamReader->ReadByte( data );
}

_dword StorageFileStreamReader::ReadWord( _short& data )
{
	return mStreamReader->ReadWord( data );
}

_dword StorageFileStreamReader::ReadDword( _long& data )
{
	return mStreamReader->ReadDword( data );
}

_dword StorageFileStreamReader::ReadByte( _byte& data )
{
	return mStreamReader->ReadByte( data );
}

_dword StorageFileStreamReader::ReadWord( _word& data )
{
	return mStreamReader->ReadWord( data );
}

_dword StorageFileStreamReader::ReadDword( _dword& data )
{
	return mStreamReader->ReadDword( data );
}

_dword StorageFileStreamReader::ReadQword( _qword& data )
{
	return mStreamReader->ReadQword( data );
}

_dword StorageFileStreamReader::ReadFloat( _float& data )
{
	return mStreamReader->ReadFloat( data );
}

_dword StorageFileStreamReader::ReadDouble( _double& data )
{
	return mStreamReader->ReadDouble( data );
}

_dword StorageFileStreamReader::ReadString( AString& string )
{
	return mStreamReader->ReadString( string );
}

_dword StorageFileStreamReader::ReadString( UString& string )
{
	return mStreamReader->ReadString( string );
}

_dword StorageFileStreamReader::ReadString( WString& string )
{
	return mStreamReader->ReadString( string );
}