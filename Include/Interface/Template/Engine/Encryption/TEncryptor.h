//! @file     TEncryptor.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TEncryptor
//----------------------------------------------------------------------------

template< typename Type, _dword _BLOCK_SIZE >
class TEncryptor : public TCryptor< Type, _BLOCK_SIZE >
{
protected:

protected:
	//!	When process buffer.
	virtual _void OnProcessBuffer( const _byte* in_buffer, _dword in_size, _byte* out_buffer, _dword& out_size ) PURE;

protected:
	TEncryptor( );
	virtual ~TEncryptor( );

// IDecoder Interface
public:
	virtual _ubool	ProcessBuffer( _dword size, const _byte* buffer ) override;

// IEncryptor Interface
public:
	virtual _ubool	ProcessString( AStringPtr src_string ) override;
};

//----------------------------------------------------------------------------
// TEncryptor Implementation
//----------------------------------------------------------------------------

template< typename Type, _dword _BLOCK_SIZE >
TEncryptor< Type, _BLOCK_SIZE >::TEncryptor( )
{
}

template< typename Type, _dword _BLOCK_SIZE >
TEncryptor< Type, _BLOCK_SIZE >::~TEncryptor( )
{
}

template< typename Type, _dword _BLOCK_SIZE >
_ubool TEncryptor< Type, _BLOCK_SIZE >::ProcessBuffer( _dword size, const _byte* buffer )
{
	if ( buffer == _null || size == 0 )
		return _false;

	// Get the steps
	_dword steps = this->GetStepsNumber( size );
	if ( steps == 0 )
		return _false;

	// Get the allocated buffer size
	_dword allocated_buffer_size = steps * _BLOCK_SIZE + sizeof( _dword );

	// Create processed buffer
	this->mProcessedBuffer.Create( allocated_buffer_size );
	EGE_MEM_SET( this->mProcessedBuffer, 0, this->mProcessedBuffer.SizeOfBytes( ) );

	// Get the start address
	_byte* processed_buffer = this->mProcessedBuffer.GetPointer( );

	// Write original size
	*(_dword*) processed_buffer = size;
	processed_buffer += sizeof( _dword );

	// Start to process
	_dword offset = 0;
	for ( _dword i = 0; i < steps; i ++ )
	{
		_dword remain_size	= Math::Min< _dword >( _BLOCK_SIZE, size - offset );
		_dword in_size		= Math::Min< _dword >( _BLOCK_SIZE, remain_size );

		_byte in_buffer[ _BLOCK_SIZE ] = {0};
		EGE_MEM_CPY( in_buffer, buffer + offset, remain_size );

		_dword out_size = 0;
		OnProcessBuffer( in_buffer, in_size, processed_buffer + offset, out_size );

		offset += out_size;
	}

	return _true;
}

template< typename Type, _dword _BLOCK_SIZE >
_ubool TEncryptor< Type, _BLOCK_SIZE >::ProcessString( AStringPtr src_string )
{
	if ( src_string.IsEmpty( ) )
		return _false;

	return ProcessBuffer( src_string.SizeOfBytes( ), (const _byte*) src_string.Str( ) );
}

}