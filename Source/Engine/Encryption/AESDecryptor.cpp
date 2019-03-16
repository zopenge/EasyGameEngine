//! @file     AESDecryptor.cpp
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// AESDecryptor Implementation
//----------------------------------------------------------------------------

AESDecryptor::AESDecryptor( )
{
	mContext = oaes_alloc( );
}

AESDecryptor::~AESDecryptor( )
{
	oaes_free( &mContext );
}

_void AESDecryptor::OnProcessBuffer( const _byte* in_buffer, _dword size, _byte* out_buffer )
{
	EGE_ASSERT( 0 );
}

_ubool AESDecryptor::SetKey( AStringPtr key )
{
	switch ( key.GetLength( ) )
	{
		case 16:
			if ( oaes_key_set_128( mContext, (const uint8_t*) key.Str( ) ) != OAES_RET_SUCCESS )
				return _false;
			break;

		case 24:
			if ( oaes_key_set_192( mContext, (const uint8_t*) key.Str( ) ) != OAES_RET_SUCCESS )
				return _false;
			break;

		case 32:
			if ( oaes_key_set_256( mContext, (const uint8_t*) key.Str( ) ) != OAES_RET_SUCCESS )
				return _false;
			break;

		default:
			return _false;
	}

	return _true;
}

_ubool AESDecryptor::ProcessBuffer( _dword size, const _byte* buffer )
{
	// Get the decrypted size
	size_t out_size = 0;
	if ( oaes_decrypt( mContext, (const uint8_t *)buffer, size, _null, &out_size ) != OAES_RET_SUCCESS )
		return _false;

	// Create decrypted buffer
	MemArrayPtr< _byte > decrypted_buffer( out_size );

	// Start to decrypt
	if ( oaes_decrypt( mContext, (const uint8_t *)buffer, size, decrypted_buffer, &out_size ) != OAES_RET_SUCCESS )
		return _false;

	// Save the decrypted buffer
	mProcessedBuffer.Create( out_size, decrypted_buffer );

	return _true;
}