//! @file     TDecryptor.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TDecryptor
//----------------------------------------------------------------------------

template< typename Type, _dword _BLOCK_SIZE >
class TDecryptor : public TCryptor< Type, _BLOCK_SIZE >
{
protected:

protected:
	//!	When process buffer.
	virtual _void OnProcessBuffer( const _byte* in_buffer, _dword size, _byte* out_buffer ) PURE;

protected:
	TDecryptor( );
	virtual ~TDecryptor( );

// IDecoder Interface
public:
	virtual _ubool	ProcessBuffer( _dword size, const _byte* buffer ) override;
};

//----------------------------------------------------------------------------
// TDecryptor Implementation
//----------------------------------------------------------------------------

template< typename Type, _dword _BLOCK_SIZE >
TDecryptor< Type, _BLOCK_SIZE >::TDecryptor( )
{
}

template< typename Type, _dword _BLOCK_SIZE >
TDecryptor< Type, _BLOCK_SIZE >::~TDecryptor( )
{
}

template< typename Type, _dword _BLOCK_SIZE >
_ubool TDecryptor< Type, _BLOCK_SIZE >::ProcessBuffer( _dword size, const _byte* buffer )
{
	if ( buffer == _null || size == 0 )
		return _false;

	if ( ((size - sizeof( _dword )) % _BLOCK_SIZE) != 0 )
		return _false;

	// Get the original size
	_dword original_size = *(const _dword*) buffer;
	buffer += sizeof( _dword );

	// Create processed buffer
	_byte* des_buffer = this->mProcessedBuffer.Create( original_size );
	if ( des_buffer == _null )
		return _false;

	EGE_MEM_SET( des_buffer, 0, original_size );

	// Start to process
	_dword steps = this->GetStepsNumber( original_size );
	for ( _dword i = 0; i < steps; i ++ )
	{
		_dword offset		= i * _BLOCK_SIZE;
		_dword remain_size	= Math::Min< _dword >( _BLOCK_SIZE, original_size - offset );
		_dword in_size		= Math::Min< _dword >( _BLOCK_SIZE, remain_size );

		_byte out_buffer[ _BLOCK_SIZE ];
		OnProcessBuffer( buffer + offset, in_size, out_buffer );

		EGE_MEM_CPY( des_buffer + offset, out_buffer, remain_size );
	}

	return _true;
}

}