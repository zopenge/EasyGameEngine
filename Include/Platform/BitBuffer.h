//! @file     BitBuffer.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2011 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// BitBuffer
//----------------------------------------------------------------------------

//! This class represents a bit array.
class BitBuffer
{
private:
	//!	The buffer data
	_dword*	mBuffer;
	//!	The buffer size in 4-bytes
	_dword	mSize;

public:
	BitBuffer( );
	~BitBuffer( );

public:
	//!	Clear number of elements.
	//!	@param		none.
	//!	@return		none.
	_void Clear( );

	//!	Get the element value.
	//!	@param		index	The index of elements.
	//!	@return		The element value.
	_dword Get( _dword index ) const;
	//!	Set the element value.
	//!	@param		index	The index of elements.
	//!	@param		value	The element value.
	//!	@return		none.
	_void Set( _dword index, _dword value );
};

//----------------------------------------------------------------------------
// BitBuffer Implementation
//----------------------------------------------------------------------------

inline BitBuffer::BitBuffer( )
{
	mBuffer	= _null;
	mSize	= 0;
}

inline BitBuffer::~BitBuffer( )
{
	EGE_DELETE_ARRAY( mBuffer );
}

inline _void BitBuffer::Clear( )
{
	if ( mBuffer != _null )
	{
		EGE_ASSERT( mSize != 0 );
		Platform::MemSet( mBuffer, 0, mSize * sizeof( _dword ) );
	}
}

inline _dword BitBuffer::Get( _dword index ) const
{
	_dword n1 = index / 32; 
	_dword n2 = index % 32;
	if ( n1 >= mSize )
		return 0;

	return ( mBuffer[ n1 ] >> n2 ) & 0x00000001;
}

inline _void BitBuffer::Set( _dword index, _dword value )
{
	_dword n1 = index / 32; 
	_dword n2 = index % 32;

	// Resize buffer
	_dword size = n1 + 1;
	if ( size > mSize )
	{
		_dword* buffer = new _dword[ size ];
		if ( mSize > 0 )
			Platform::MemCpy( buffer, mBuffer, mSize * sizeof( _dword ) );

		Platform::MemSet( buffer + mSize, 0, ( size - mSize ) * sizeof( _dword ) );
		delete[] mBuffer;

		mBuffer = buffer;
		mSize	= size;
	}

	if ( value )
		mBuffer[ n1 ] |= 1 << n2;
	else
		mBuffer[ n1 ] &= ( 1 << n2 ) ^ 0xFFFFFFFF;
}

}