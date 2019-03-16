//! @file     StorageFileStreamWriter.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEStorage.h"

//----------------------------------------------------------------------------
// StorageFileStreamWriter Implementation
//----------------------------------------------------------------------------

StorageFileStreamWriter::StorageFileStreamWriter( )
{
}

StorageFileStreamWriter::~StorageFileStreamWriter( )
{
}

_ubool StorageFileStreamWriter::Initialize( WStringPtr root_path, WStringPtr relative_file_name )
{
	// Build the resource file name
	WString file_name = FORMAT_WSTRING_2( L"%s/%s", root_path.Str( ), relative_file_name.Str( ) );

	// Create file stream writer
	mStreamWriter = GetInterfaceFactory( )->CreateFileStreamWriter( file_name );
	if ( mStreamWriter.IsNull( ) )
		return _false;

	return _true;
}

_void StorageFileStreamWriter::Uninitialize( )
{
	mStreamWriter.Clear( );
}

WStringPtr StorageFileStreamWriter::GetFileName( ) const
{
	return mStreamWriter->GetFileName( );
}

_STREAM_TYPE StorageFileStreamWriter::GetType( ) const
{
	return mStreamWriter->GetType( );
}

_STREAM_SHARE_MODE StorageFileStreamWriter::GetShareMode( ) const
{
	return mStreamWriter->GetShareMode( );
}

_dword StorageFileStreamWriter::GetSize( ) const
{
	return mStreamWriter->GetSize( );
}

_dword StorageFileStreamWriter::GetOffset( ) const
{
	return mStreamWriter->GetOffset( );
}

const _byte* StorageFileStreamWriter::GetBuffer( )
{
	return mStreamWriter->GetBuffer( );
}

_dword StorageFileStreamWriter::Seek( _SEEK flag, _long distance )
{
	return mStreamWriter->Seek( flag, distance );
}

_dword StorageFileStreamWriter::SeekByArrangedValueFromBegin( _dword value )
{
	return mStreamWriter->SeekByArrangedValueFromBegin( value );
}

_void StorageFileStreamWriter::SetEndian( _ENDIAN endian )
{
	mStreamWriter->SetEndian( endian );
}

_ENDIAN StorageFileStreamWriter::GetEndian( ) const
{
	return mStreamWriter->GetEndian( );
}

_dword StorageFileStreamWriter::RemoveBuffer( _dword size )
{
	return mStreamWriter->RemoveBuffer( size );
}

_ubool StorageFileStreamWriter::SetCurOffsetAsEndPos( )
{
	return mStreamWriter->SetCurOffsetAsEndPos( );
}

_dword StorageFileStreamWriter::WriteBuffer( const _void* buffer, _dword size )
{
	return mStreamWriter->WriteBuffer( buffer, size );
}

_dword StorageFileStreamWriter::WriteByte( _tiny data )
{
	return mStreamWriter->WriteByte( data );
}

_dword StorageFileStreamWriter::WriteWord( _short data )
{
	return mStreamWriter->WriteWord( data );
}

_dword StorageFileStreamWriter::WriteDword( _long data )
{
	return mStreamWriter->WriteDword( data );
}

_dword StorageFileStreamWriter::WriteByte( _byte data )
{
	return mStreamWriter->WriteByte( data );
}

_dword StorageFileStreamWriter::WriteWord( _word data )
{
	return mStreamWriter->WriteWord( data );
}

_dword StorageFileStreamWriter::WriteDword( _dword data )
{
	return mStreamWriter->WriteDword( data );
}

_dword StorageFileStreamWriter::WriteQword( _qword data )
{
	return mStreamWriter->WriteQword( data );
}

_dword StorageFileStreamWriter::WriteFloat( _float data )
{
	return mStreamWriter->WriteFloat( data );
}

_dword StorageFileStreamWriter::WriteDouble( _double data )
{
	return mStreamWriter->WriteDouble( data );
}

_dword StorageFileStreamWriter::WriteString( AStringPtr string )
{
	return mStreamWriter->WriteString( string );
}

_dword StorageFileStreamWriter::WriteString( WStringPtr string )
{
	return mStreamWriter->WriteString( string );
}