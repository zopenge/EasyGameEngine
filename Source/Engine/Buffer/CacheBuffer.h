//! @file     CacheBuffer.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// CacheBuffer
//----------------------------------------------------------------------------

class CacheBuffer : public TObject< ICacheBuffer >
{
private:
	//!	The offset of buffer in bytes
	_dword					mBufferOffset;
	//!	The max buffer size in bytes
	_dword					mBufferSize;

	//!	The offset of cache buffer
	_dword					mCacheBufferOffset;
	//!	The cache buffer max size
	_dword					mCacheBufferSize;
	//!	The cache buffer data
	_byte*					mCacheBuffer;

	//!	The notifier
	ICacheBufferNotifierRef	mNotifier;

private:
	_void Resize( _dword size );

public:
	CacheBuffer( );
	virtual ~CacheBuffer( );

public:
	_ubool Initialize( _dword buffer_size, _dword cache_size, ICacheBufferNotifier* notifier );

// ICacheBuffer Interface
public:
	virtual _ubool			SetCacheBufferSize( _dword size ) override;
	virtual _dword			GetCacheBufferOffset( ) const override;
	virtual _dword			GetCacheBufferSize( ) const override;
	virtual const _byte*	GetCacheBufferData( ) const override;

	virtual _dword			GetSize( ) const override;
	virtual _dword			GetOffset( ) const override;

	virtual _dword			Seek( _SEEK flag, _dword offset ) override;

	virtual _void			Write( _dword size, const _byte* buffer ) override;
	virtual _void			Flush( ) override;
	virtual _void			Reset( ) override;
};

//----------------------------------------------------------------------------
// CacheBuffer Implementation
//----------------------------------------------------------------------------

}