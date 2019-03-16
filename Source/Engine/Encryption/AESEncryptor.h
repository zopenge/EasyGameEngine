//! @file     AESEncryptor.h
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// AESEncryptor
//----------------------------------------------------------------------------

class AESEncryptor : public TEncryptor< IEncryptor, OAES_BLOCK_SIZE >
{
private:
	OAES_CTX*	mContext;
	
// TEncryptor Interface
private:
	virtual _void OnProcessBuffer( const _byte* in_buffer, _dword in_size, _byte* out_buffer, _dword& out_size ) override;

public:
	AESEncryptor( );
	virtual ~AESEncryptor( );

// ICrypto Interface
public:
	virtual _ubool	SetKey( AStringPtr key ) override;

// IDecoder Interface
public:
	virtual _ubool	ProcessBuffer( _dword size, const _byte* buffer ) override;
};

}
