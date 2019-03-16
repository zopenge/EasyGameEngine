//! @file     AESEncryptor.cpp
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// AESEncryptor Implementation
//----------------------------------------------------------------------------

AESEncryptor::AESEncryptor( )
{
	mContext = oaes_alloc( );
}

AESEncryptor::~AESEncryptor( )
{
	oaes_free( &mContext );
}

_void AESEncryptor::OnProcessBuffer( const _byte* in_buffer, _dword in_size, _byte* out_buffer, _dword& out_size )
{
	EGE_ASSERT( 0 );
}

_ubool AESEncryptor::SetKey( AStringPtr key )
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

_ubool AESEncryptor::ProcessBuffer( _dword size, const _byte* buffer )
{
	// Get the encrypted size
	size_t out_size = 0;
	if ( oaes_encrypt( mContext, (const uint8_t *)buffer, size, _null, &out_size ) != OAES_RET_SUCCESS )
		return _false;

	// Create encrypted buffer
	mProcessedBuffer.Create( out_size );
	EGE_MEM_SET( mProcessedBuffer, 0, out_size );

	// Start to encrypt
	if ( oaes_encrypt( mContext, (const uint8_t *)buffer, size, mProcessedBuffer, &out_size ) != OAES_RET_SUCCESS )
		return _false;

	return _true;
}