//! @file     DESEncryptor.h
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// DESEncryptor
//----------------------------------------------------------------------------

class DESEncryptor : public TEncryptor< IEncryptor, 8 >
{
private:
	des_context	mContext;
	
// TEncryptor Interface
private:
	virtual _void OnProcessBuffer( const _byte* in_buffer, _dword in_size, _byte* out_buffer, _dword& out_size ) override;

public:
	DESEncryptor( );
	virtual ~DESEncryptor( );

// IEncryptor Interface
public:
	virtual _ubool	SetKey( AStringPtr key ) override;
};

}
