//! @file     TBitStream.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TBitStream
//----------------------------------------------------------------------------

template< typename Type >
class TBitStream : public TMemStream< Type >
{
protected:
	typedef TMemStream< Type > TBaseClass;

protected:
	//!	The current bit offset of 8-bits chunk
	_dword	mBitOffset;

protected:
	TBitStream( );
	TBitStream( _byte* buffer, _dword size, _STREAM_SHARE_MODE share_mode );
	virtual ~TBitStream( );
	
// IBitStream Interface
public:
	virtual _void 	SeekPaddedSection( ) override;
	virtual _void 	SeekBits( _dword bits ) override;
};

//----------------------------------------------------------------------------
// TBitStream Implementation
//----------------------------------------------------------------------------

template< typename Type >
TBitStream< Type >::TBitStream( )
{
	mBitOffset = 0;
}

template< typename Type >
TBitStream< Type >::TBitStream( _byte* buffer, _dword size, _STREAM_SHARE_MODE share_mode ) : TBaseClass( buffer, size, share_mode )
{
	mBitOffset = 0;
}

template< typename Type >
TBitStream< Type >::~TBitStream( )
{

}

template< typename Type >
_void TBitStream< Type >::SeekPaddedSection( )
{
	// Jump the padded section data
	if ( mBitOffset % 8 )
		this->Seek( _SEEK_CURRENT, 1 );

	mBitOffset = 0;
}

template< typename Type >
_void TBitStream< Type >::SeekBits( _dword bits )
{
	mBitOffset += bits;

	while ( mBitOffset >= 8 )
	{
		this->Seek( _SEEK_CURRENT, 1 );

		mBitOffset -= 8;
	}
}

}