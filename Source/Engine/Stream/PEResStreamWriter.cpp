//! @file     PEResStreamWriter.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// PEResStreamWriter Implementation
//----------------------------------------------------------------------------

PEResStreamWriter::PEResStreamWriter( )
{
}

PEResStreamWriter::~PEResStreamWriter( )
{
}

_STREAM_TYPE PEResStreamWriter::GetType( ) const
{
	return _STREAM_TYPE_MEMORY;
}

_STREAM_SHARE_MODE PEResStreamWriter::GetShareMode( ) const
{
	return _STREAM_SHARE_MODE_NONE;
}

_dword PEResStreamWriter::GetSize( ) const
{
	return 0;
}

_dword PEResStreamWriter::GetOffset( ) const
{
	return 0;
}

_byte* PEResStreamWriter::GetBuffer( )
{
	return _null;
}

_dword PEResStreamWriter::Seek( _SEEK flag, _int distance )
{
	return -1;
}

_dword PEResStreamWriter::SeekByArrangedValueFromBegin( _dword value )
{
	return -1;
}

_void PEResStreamWriter::SetEndian( _ENDIAN endian )
{
}

_ENDIAN PEResStreamWriter::GetEndian( ) const
{
	return _ENDIAN_UNKNOWN;
}

_dword PEResStreamWriter::RemoveBuffer( _dword size )
{
	return 0;
}

_ubool PEResStreamWriter::SetCurOffsetAsEndPos( )
{
	return _false;
}

_dword PEResStreamWriter::WriteBuffer( const _void* buffer, _dword size )
{
	return 0;
}

_dword PEResStreamWriter::WriteTiny( _tiny data )
{
	return 0;
}

_dword PEResStreamWriter::WriteShort( _short data )
{
	return 0;
}

_dword PEResStreamWriter::WriteLong( _int data )
{
	return 0;
}

_dword PEResStreamWriter::WriteByte( _byte data )
{
	return 0;
}

_dword PEResStreamWriter::WriteWord( _word data )
{
	return 0;
}

_dword PEResStreamWriter::WriteDword( _dword data )
{
	return 0;
}

_dword PEResStreamWriter::WriteQword( _qword data )
{
	return 0;
}

_dword PEResStreamWriter::WriteFloat( _float data )
{
	return 0;
}

_dword PEResStreamWriter::WriteDouble( _double data )
{
	return 0;
}

_dword PEResStreamWriter::WriteString( AStringPtr string )
{
	return 0;
}

_dword PEResStreamWriter::WriteString( WStringPtr string )
{
	return 0;
}