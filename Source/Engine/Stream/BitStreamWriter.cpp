//! @file     BitStreamWriter.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// BitStreamWriter Implementation
//----------------------------------------------------------------------------

BitStreamWriter::BitStreamWriter( _dword size ) : BaseClass( _null, size, _STREAM_SHARE_MODE_NONE )
{
}

BitStreamWriter::~BitStreamWriter( )
{
}

_dword BitStreamWriter::RemoveBuffer( _dword size )
{
	return 0;
}

_ubool BitStreamWriter::SetCurOffsetAsEndPos( )
{
	return _false;
}

_byte* BitStreamWriter::GetBuffer( )
{
	return mBuffer;
}

_dword BitStreamWriter::WriteBuffer( const _void* buffer, _dword size )
{
	return 0;
}

_dword BitStreamWriter::WriteTiny( _tiny data )
{
	return 0;
}

_dword BitStreamWriter::WriteShort( _short data )
{
	return 0;
}

_dword BitStreamWriter::WriteLong( _int data )
{
	return 0;
}

_dword BitStreamWriter::WriteByte( _byte data )
{
	return 0;
}

_dword BitStreamWriter::WriteWord( _word data )
{
	return 0;
}

_dword BitStreamWriter::WriteDword( _dword data )
{
	return 0;
}

_dword BitStreamWriter::WriteQword( _qword data )
{
	return 0;
}

_dword BitStreamWriter::WriteFloat( _float data )
{
	return 0;
}

_dword BitStreamWriter::WriteDouble( _double data )
{
	return 0;
}