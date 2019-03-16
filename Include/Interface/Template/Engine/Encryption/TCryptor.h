//! @file     TCryptor.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TCryptor
//----------------------------------------------------------------------------

template< typename Type, _dword _BLOCK_SIZE >
class TCryptor : public TObject< Type >
{
protected:
	//!	The processed buffer
	MemArrayPtr< _byte > mProcessedBuffer;

protected:
	//!	Get the steps number.
	_dword GetStepsNumber( _dword size ) const;

protected:
	TCryptor( );
	virtual ~TCryptor( );

// IDecoder Interface
public:
	virtual _dword					GetProcessedBufferSize( ) const override;
	virtual const _byte*			GetProcessedBufferData( ) const override;
	virtual IStreamReaderPassRef	GetProcessedStreamReader( ) const override;
};

//----------------------------------------------------------------------------
// TCryptor Implementation
//----------------------------------------------------------------------------

template< typename Type, _dword _BLOCK_SIZE >
TCryptor< Type, _BLOCK_SIZE >::TCryptor( )
{
	EGE_STATIC_ASSERT( _BLOCK_SIZE != 0, "The block's size can not be zero" );
}

template< typename Type, _dword _BLOCK_SIZE >
TCryptor< Type, _BLOCK_SIZE >::~TCryptor( )
{
}

template< typename Type, _dword _BLOCK_SIZE >
_dword TCryptor< Type, _BLOCK_SIZE >::GetStepsNumber( _dword size ) const
{
	if ( size % _BLOCK_SIZE )
		return (size / _BLOCK_SIZE) + 1;
	else
		return size / _BLOCK_SIZE;
}

template< typename Type, _dword _BLOCK_SIZE >
_dword TCryptor< Type, _BLOCK_SIZE >::GetProcessedBufferSize( ) const
{
	return mProcessedBuffer.SizeOfBytes( );
}

template< typename Type, _dword _BLOCK_SIZE >
const _byte* TCryptor< Type, _BLOCK_SIZE >::GetProcessedBufferData( ) const
{
	return mProcessedBuffer;
}

template< typename Type, _dword _BLOCK_SIZE >
IStreamReaderPassRef TCryptor< Type, _BLOCK_SIZE >::GetProcessedStreamReader( ) const
{
	return GetInterfaceFactory( )->CreateMemStreamReader( GetProcessedBufferData( ), GetProcessedBufferSize( ), _STREAM_SHARE_MODE_READ_ONLY );
}

}