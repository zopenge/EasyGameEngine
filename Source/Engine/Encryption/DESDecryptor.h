//! @file     DESDecryptor.h
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// DESDecryptor
//----------------------------------------------------------------------------

class DESDecryptor : public TDecryptor< IDecryptor, 8 >
{
private:
	des_context	mContext;

// TDecryptor Interface
private:
	virtual _void OnProcessBuffer( const _byte* in_buffer, _dword size, _byte* out_buffer ) override;

public:
	DESDecryptor( );
	virtual ~DESDecryptor( );

// IDecryptor Interface
public:
	virtual _ubool	SetKey( AStringPtr key ) override;
};

}
