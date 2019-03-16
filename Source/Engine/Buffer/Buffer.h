//! @file     Buffer.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Buffer
//----------------------------------------------------------------------------

class Buffer : public TObject< IBuffer >
{
private:
	//!	The cache buffer.
	ICacheBufferRef	mCachedBuffer;

public:
	Buffer( );
	virtual ~Buffer( );

public:
	_ubool Initialize( _dword buffer_size, _dword cache_size, IBufferNotifier* notifier );

// IBuffer Interface
public:
	virtual _dword	GetSize( ) const override;
	virtual _dword	GetOffset( ) const override;

	virtual _dword	Seek( _SEEK flag, _dword offset ) override;
	virtual _void	Reset( ) override;

	virtual _void	Write( _dword size, const _byte* buffer ) override;
	virtual _void	Flush( ) override;
};

//----------------------------------------------------------------------------
// Buffer Implementation
//----------------------------------------------------------------------------

}