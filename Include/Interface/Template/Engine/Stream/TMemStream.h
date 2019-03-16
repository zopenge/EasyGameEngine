//! @file     TMemStream.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TMemStream
//----------------------------------------------------------------------------

template< typename Type >
class TMemStream : public TStream< TObject< Type > >
{
protected:
	typedef TStream< TObject< Type > > TBaseClass;

protected:
	//!	The current buffer size
	_dword	mSize;
	//!	The buffer data
	_byte*	mBuffer;
	//!	The current buffer pointer [ mBuffer, mPointer )
	_byte*	mPointer;

protected:
	TMemStream( );
	TMemStream( _byte* buffer, _dword size, _STREAM_SHARE_MODE share_mode );
	virtual ~TMemStream( );

// IStream Interface
public:
	virtual _dword	GetSize( ) const override;
	virtual _dword 	GetOffset( ) const override;

	virtual _dword 	Seek( _SEEK flag, _int distance ) override;
	virtual _dword	SeekByArrangedValueFromBegin( _dword value ) override;
};

//----------------------------------------------------------------------------
// TMemStream Implementation
//----------------------------------------------------------------------------

template< typename Type >
TMemStream< Type >::TMemStream( )
{
	mSize		= 0;
	mBuffer		= _null;
	mPointer	= _null;
}

template< typename Type >
TMemStream< Type >::TMemStream( _byte* buffer, _dword size, _STREAM_SHARE_MODE share_mode ) 
	: mSize( size ), mBuffer( buffer ), mPointer( buffer )
{
	this->mShareMode = share_mode;

	switch ( this->mShareMode )
	{
		case _STREAM_SHARE_MODE_NONE:
		{
			EGE_ASSERT( size != 0 );

			mBuffer		= new _byte[ size ];
			mPointer	= mBuffer;
			if ( buffer != _null )
				EGE_MEM_CPY( mBuffer, buffer, size );
		}
		break;

        case _STREAM_SHARE_MODE_MANAGED:
		case _STREAM_SHARE_MODE_READ_ONLY:
		{
			mBuffer	= buffer;
		}
		break;

		default:
			break;
	}
}

template< typename Type >
TMemStream< Type >::~TMemStream( )
{
	if ( this->mShareMode != _STREAM_SHARE_MODE_READ_ONLY )
		EGE_DELETE_ARRAY( mBuffer );
}

template< typename Type >
_dword TMemStream< Type >::GetSize( ) const
{ 
	return mSize; 
}

template< typename Type >
_dword TMemStream< Type >::GetOffset( ) const
{ 
	return mPointer - mBuffer; 
}

template< typename Type >
_dword TMemStream< Type >::Seek( _SEEK flag, _int distance )
{
	_byte* min_location = mBuffer;
	_byte* max_location = mBuffer + mSize;

	switch ( flag )
	{
		case _SEEK_BEGIN:
			mPointer = Math::Clamp< _byte* >( mBuffer + distance, min_location, max_location ); 
			break;

		case _SEEK_CURRENT:
			mPointer = Math::Clamp< _byte* >( mPointer + distance, min_location, max_location ); 
			break;

		case _SEEK_END:
			mPointer = Math::Clamp< _byte* >( ( mBuffer + mSize ) - distance, min_location, max_location ); 
			break;
	}

	EGE_ASSERT( mPointer >= mBuffer && (_dword)(mPointer - mBuffer) <= mSize );

	_dword offset = (_dword)(mPointer - mBuffer);
	EGE_ASSERT( offset <= mSize );

	return offset;
}

template< typename Type >
_dword TMemStream< Type >::SeekByArrangedValueFromBegin( _dword value )
{
	_dword offset = GetOffset( );

	if ( offset % value != 0 )
		Seek( _SEEK_BEGIN, (_int)Math::UpperArrange( offset, value ) );

	return GetOffset( );
}

}