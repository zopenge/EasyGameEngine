//! @file     Buffer.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// Buffer Implementation
//----------------------------------------------------------------------------

Buffer::Buffer( )
{
}

Buffer::~Buffer( )
{
}

_ubool Buffer::Initialize( _dword buffer_size, _dword cache_size, IBufferNotifier* notifier )
{
	if ( buffer_size == 0 || cache_size == 0 || notifier == _null )
		return _false;

	// Create cache buffer
	mCachedBuffer = GetInterfaceFactory( )->CreateCacheBuffer( buffer_size, cache_size, notifier );
	if ( mCachedBuffer.IsNull( ) )
		return _false;

	return _true;
}

_dword Buffer::GetSize( ) const
{
	return mCachedBuffer->GetBufferSize( );
}

_dword Buffer::GetOffset( ) const
{
	return mCachedBuffer->GetOffset( );
}

_dword Buffer::Seek( _SEEK flag, _dword offset )
{
	return mCachedBuffer->SeekBufferOffset( flag, offset );
}

_void Buffer::Reset( )
{
	mCachedBuffer->ResetBuffer( );
}

_void Buffer::Write( _dword size, const _byte* buffer )
{
	if ( size == 0 || buffer == _null )
		return;

	mCachedBuffer->WriteBuffer( size, buffer );
}

_void Buffer::Flush( )
{
	mCachedBuffer->FlushCacheBuffer( );
}
