//! @file     AESDecryptor.h
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// AESDecryptor
//----------------------------------------------------------------------------

class AESDecryptor : public TDecryptor< IDecryptor, OAES_BLOCK_SIZE >
{
private:
	OAES_CTX*	mContext;

// TDecryptor Interface
private:
	virtual _void OnProcessBuffer( const _byte* in_buffer, _dword size, _byte* out_buffer ) override;

public:
	AESDecryptor( );
	virtual ~AESDecryptor( );

// ICrypto Interface
public:
	virtual _ubool	SetKey( AStringPtr key ) override;

// IDecoder Interface
public:
	virtual _ubool	ProcessBuffer( _dword size, const _byte* buffer ) override;
};

}
