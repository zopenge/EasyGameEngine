//! @file     TStream.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TStream
//----------------------------------------------------------------------------

template< typename Type >
class TStream : public Type
{
protected:
	//!	The endian type
	_ENDIAN				mEndian;

	//!	Share mode
	_STREAM_SHARE_MODE	mShareMode;

protected:
	TStream( );
	virtual ~TStream( );

// IStream Interface
public:
	virtual _STREAM_TYPE		GetType( ) const override;
	virtual _STREAM_SHARE_MODE	GetShareMode( ) const override;

	virtual _void				SetEndian( _ENDIAN endian ) override;
	virtual _ENDIAN				GetEndian( ) const override;
};

//----------------------------------------------------------------------------
// TStream Implementation
//----------------------------------------------------------------------------

template< typename Type >
TStream< Type >::TStream( )
{
	this->mEndian		= Platform::GetEndianType( );

	this->mShareMode	= _STREAM_SHARE_MODE_NONE;
}

template< typename Type >
TStream< Type >::~TStream( )
{
}

template< typename Type >
_STREAM_TYPE TStream< Type >::GetType( ) const
{
	return _STREAM_TYPE_MEMORY;
}

template< typename Type >
_STREAM_SHARE_MODE TStream< Type >::GetShareMode( ) const
{
	return mShareMode;
}

template< typename Type >
_void TStream< Type >::SetEndian( _ENDIAN endian )
{
	mEndian = endian;
}

template< typename Type >
_ENDIAN TStream< Type >::GetEndian( ) const
{
	return mEndian;
}

}