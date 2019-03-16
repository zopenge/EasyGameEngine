//! @file     MemStreamWriter.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// MemStreamWriter
//----------------------------------------------------------------------------

class MemStreamWriter : public TMemStream< TStreamWriter< IStreamWriter > >
{
private:
	typedef TMemStream< TStreamWriter< IStreamWriter > > BaseClass;

private:
	//!	The grow size in bytes
	_dword	mGrowSize;

private:
	//!	Write the value data.
	template< typename DataType >
	_dword WriteValue( DataType data );

	//!	Grow the buffer data with incremental size.
	//!	@param		size	The incremental size in bytes.
	//! @return		True indicates success, false indicates failure.
	_ubool Grow( _dword size );

	//!	Resize the buffer data.
	//!	@param		size	The new size of the stream in bytes.
	//! @return		True indicates success, false indicates failure.
	_ubool Resize( _dword size );

public:
	MemStreamWriter( _dword size, _dword grow_size );
	MemStreamWriter( _byte* buffer, _dword size, _STREAM_SHARE_MODE share_mode );
	virtual ~MemStreamWriter( );

// IStream Interface
public:
	virtual _dword 	Seek( _SEEK flag, _int distance ) override;

// IStreamWriter Interface
public:
	virtual _dword	RemoveBuffer( _dword size ) override;
	virtual _ubool	SetCurOffsetAsEndPos( ) override;

	virtual _byte*	GetBuffer( ) override;

	virtual _dword 	WriteBuffer( const _void* buffer, _dword size ) override;
	virtual _dword 	WriteTiny( _tiny data ) override;
	virtual _dword 	WriteShort( _short data ) override;
	virtual _dword 	WriteLong( _int data ) override;
	virtual _dword 	WriteByte( _byte data ) override;
	virtual _dword 	WriteWord( _word data ) override;
	virtual _dword 	WriteDword( _dword data ) override;
	virtual _dword	WriteQword( _qword data ) override;
	virtual _dword 	WriteFloat( _float data ) override;
	virtual _dword 	WriteDouble( _double data ) override;
};

//----------------------------------------------------------------------------
// MemStreamWriter Implementation
//----------------------------------------------------------------------------

template< typename DataType >
_dword MemStreamWriter::WriteValue( DataType data )
{
	if ( Grow( sizeof( DataType ) ) == _false )
		return 0;

	*(DataType*) mPointer = data;
	mPointer += sizeof( DataType );

	EGE_ASSERT( (_dword)(mPointer - mBuffer) <= mSize );

	return sizeof( DataType );
}

}