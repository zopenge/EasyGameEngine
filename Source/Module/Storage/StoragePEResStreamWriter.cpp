//! @file     StoragePEResStreamWriter.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEStorage.h"

//----------------------------------------------------------------------------
// StoragePEResStreamWriter Implementation
//----------------------------------------------------------------------------

StoragePEResStreamWriter::StoragePEResStreamWriter( )
{
}

StoragePEResStreamWriter::~StoragePEResStreamWriter( )
{
}

_STREAM_TYPE StoragePEResStreamWriter::GetType( ) const
{
	return _STREAM_TYPE_MEMORY;
}

_STREAM_SHARE_MODE StoragePEResStreamWriter::GetShareMode( ) const
{
	return _STREAM_SHARE_MODE_NONE;
}

_dword StoragePEResStreamWriter::GetSize( ) const
{
	return 0;
}

_dword StoragePEResStreamWriter::GetOffset( ) const
{
	return 0;
}

const _byte* StoragePEResStreamWriter::GetBuffer( )
{
	return _null;
}

_dword StoragePEResStreamWriter::Seek( _SEEK flag, _long distance )
{
	return -1;
}

_dword StoragePEResStreamWriter::SeekByArrangedValueFromBegin( _dword value )
{
	return -1;
}

_void StoragePEResStreamWriter::SetEndian( _ENDIAN endian )
{
}

_ENDIAN StoragePEResStreamWriter::GetEndian( ) const
{
	return _ENDIAN_UNKNOWN;
}

_dword StoragePEResStreamWriter::RemoveBuffer( _dword size )
{
	return 0;
}

_ubool StoragePEResStreamWriter::SetCurOffsetAsEndPos( )
{
	return _false;
}

_dword StoragePEResStreamWriter::WriteBuffer( const _void* buffer, _dword size )
{
	return 0;
}

_dword StoragePEResStreamWriter::WriteTiny( _tiny data )
{
	return 0;
}

_dword StoragePEResStreamWriter::WriteShort( _short data )
{
	return 0;
}

_dword StoragePEResStreamWriter::WriteLong( _long data )
{
	return 0;
}

_dword StoragePEResStreamWriter::WriteByte( _byte data )
{
	return 0;
}

_dword StoragePEResStreamWriter::WriteWord( _word data )
{
	return 0;
}

_dword StoragePEResStreamWriter::WriteDword( _dword data )
{
	return 0;
}

_dword StoragePEResStreamWriter::WriteQword( _qword data )
{
	return 0;
}

_dword StoragePEResStreamWriter::WriteFloat( _float data )
{
	return 0;
}

_dword StoragePEResStreamWriter::WriteDouble( _double data )
{
	return 0;
}

_dword StoragePEResStreamWriter::WriteString( AStringPtr string )
{
	return 0;
}

_dword StoragePEResStreamWriter::WriteString( WStringPtr string )
{
	return 0;
}