//! @file     DESDecryptor.cpp
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// DESDecryptor Implementation
//----------------------------------------------------------------------------

DESDecryptor::DESDecryptor( )
{
	EGE_INIT( mContext );
}

DESDecryptor::~DESDecryptor( )
{
}

_void DESDecryptor::OnProcessBuffer( const _byte* in_buffer, _dword size, _byte* out_buffer )
{
	des_decrypt( &mContext, (uint8*) in_buffer, out_buffer );
}

_ubool DESDecryptor::SetKey( AStringPtr key )
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