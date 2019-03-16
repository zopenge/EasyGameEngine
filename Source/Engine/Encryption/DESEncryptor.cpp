//! @file     DESEncryptor.cpp
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// DESEncryptor Implementation
//----------------------------------------------------------------------------

DESEncryptor::DESEncryptor( )
{
	EGE_INIT( mContext );
}

DESEncryptor::~DESEncryptor( )
{
}

_void DESEncryptor::OnProcessBuffer( const _byte* in_buffer, _dword in_size, _byte* out_buffer, _dword& out_size )
{
	des_encrypt( &mContext, (uint8*) in_buffer, out_buffer );

	out_size = 8;
}

_ubool DESEncryptor::SetKey( AStringPtr key )
{
	if ( key.IsEmpty( ) )
		return _false;

	// Get the key length
	_dword key_length = key.GetLength( );
	if ( key_length != 8 )
	{
		WLOG_ERROR_2( L"The DES key length (%d) is invalid, valid length is (%d)", key_length, 8 );
		return _false;
	}

	des_set_key( &mContext, (unsigned char*) key.Str( ) );

	return _true;
}