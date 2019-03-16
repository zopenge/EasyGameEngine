//! @file     MemStreamWriter.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// MemStreamWriter Implementation
//----------------------------------------------------------------------------

MemStreamWriter::MemStreamWriter( _dword size, _dword grow_size ) : BaseClass( _null, size, _STREAM_SHARE_MODE_NONE )
{
	mGrowSize = grow_size;
}

MemStreamWriter::MemStreamWriter( _byte* buffer, _dword size, _STREAM_SHARE_MODE share_mode ) : BaseClass( buffer, size, share_mode )
{
	mGrowSize = 0;
}

MemStreamWriter::~MemStreamWriter( )
{
}

_ubool MemStreamWriter::Grow( _dword size )
{
	// Grow the buffer
	if ( mSize - GetOffset( ) < size )
	{
		_dword grow_size = Math::Max( mGrowSize, size );

		if ( Resize( mSize + grow_size ) == _false )
			return _false;
	}

	return _true;
}

_ubool MemStreamWriter::Resize( _dword size )
{
	if ( mShareMode == _STREAM_SHARE_MODE_READ_ONLY )
		return _false;

	EGE_ASSERT( size > mSize );
	EGE_ASSERT( mPointer >= mBuffer && (_dword)(mPointer - mBuffer) <= mSize );

	// Get the offset
	_dword offset = GetOffset( );

	// Realloc failed, now we try to allocate in the normal way ( new -> copy -> delete )
	_byte* buffer = new _byte[ size ];
	EGE_MEM_CPY( buffer, mBuffer, mSize );

	// Delete the old buffer data
	delete[] mBuffer;

	// Update the buffer data pointers
	mPointer	= buffer + offset;
	mBuffer		= buffer;

	// Update the current buffer size
	mSize = size;

	return _true;
}

_dword MemStreamWriter::Seek( _SEEK flag, _int distance )
{
	switch ( flag )
	{
		case _SEEK_BEGIN:
		{
			if ( distance > 0 && (_dword) distance > mSize )
				Resize( mSize );
		}
		break;

		case _SEEK_CURRENT:
		{
			if ( distance > 0 && (mPointer - mBuffer) + (_dword) distance > mSize )
				Resize( distance );
		}
		break;

		case _SEEK_END:
		{
			if ( distance > 0 )
				Resize( mSize + distance );
		}
		break;

		default:
			break;
	}

	return BaseClass::Seek( flag, distance );
}

_dword MemStreamWriter::RemoveBuffer( _dword size )
{
	if ( size == 0 || size > mSize )
		return 0;

	if ( mShareMode == _STREAM_SHARE_MODE_READ_ONLY )
		return 0;

	// Get the removed size to seek
	_dword removed_size = Math::Min< _dword >( (_dword)(mPointer - mBuffer), size );

	// Update the pointer
	mPointer -= removed_size;

	EGE_ASSERT( mPointer >= mBuffer && (_dword)(mPointer - mBuffer) <= mSize );

	// Move buffer data
	EGE_MEM_MOVE( mBuffer, mBuffer + removed_size, mSize - removed_size );

	return size;
}

_ubool MemStreamWriter::SetCurOffsetAsEndPos( )
{
	// Get the current offset as tail
	_dword size = GetOffset( );
	if ( size == 0 || size == -1 )
		return _false;

	// Create new buffer and copy old buffer data
	_byte* buffer = new _byte[ size ];
	EGE_MEM_CPY( buffer, mBuffer, size );

	// Delete the old buffer
	if ( mShareMode == _STREAM_SHARE_MODE_NONE )
		EGE_DELETE_ARRAY( mBuffer );

	// Initialize buffer info
	mBuffer		= buffer;
	mPointer	= buffer;
	mSize		= size;
	mShareMode	= _STREAM_SHARE_MODE_NONE;

	return _true;
}

_byte* MemStreamWriter::GetBuffer( )
{
	return mBuffer;
}

_dword MemStreamWriter::WriteBuffer( const _void* buffer, _dword size )
{
	if ( Grow( size ) == _false )
		return 0;

	EGE_MEM_CPY( mPointer, buffer, size );
	mPointer += size;

	EGE_ASSERT( mPointer >= mBuffer && (_dword)(mPointer - mBuffer) <= mSize );

	return size;
}

_dword MemStreamWriter::WriteTiny( _tiny data )
{
	return WriteValue( data );
}

_dword MemStreamWriter::WriteShort( _short data )
{
	return WriteValue( data );
}

_dword MemStreamWriter::WriteLong( _int data )
{
	return WriteValue( data );
}

_dword MemStreamWriter::WriteByte( _byte data )
{
	return WriteValue( data );
}

_dword MemStreamWriter::WriteWord( _word data )
{
	return WriteValue( data );
}

_dword MemStreamWriter::WriteDword( _dword data )
{
	return WriteValue( data );
}

_dword MemStreamWriter::WriteQword( _qword data )
{
	return WriteValue( data );
}

_dword MemStreamWriter::WriteFloat( _float data )
{
	return WriteValue( data );
}

_dword MemStreamWriter::WriteDouble( _double data )
{
	return WriteValue( data );
}