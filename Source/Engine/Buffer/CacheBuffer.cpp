//! @file     CacheBuffer.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// CacheBuffer Implementation
//----------------------------------------------------------------------------

CacheBuffer::CacheBuffer( )
{
	mBufferOffset		= 0;
	mBufferSize			= 0;

	mCacheBufferOffset	= 0;
	mCacheBufferSize	= 0;
	mCacheBuffer		= _null;
}

CacheBuffer::~CacheBuffer( )
{
	EGE_DELETE_ARRAY( mCacheBuffer );
}

_void CacheBuffer::Resize( _dword size )
{
	EGE_ASSERT( size != 0 );

	mBufferSize = size;
	mNotifier->OnResizeBuffer( size );
}

_ubool CacheBuffer::Initialize( _dword buffer_size, _dword cache_size, ICacheBufferNotifier* notifier )
{
	if ( buffer_size == 0 || cache_size == 0 || notifier == _null )
		return _false;

	mBufferOffset		= 0;
	mBufferSize			= buffer_size;

	mCacheBufferOffset	= 0;
	mCacheBufferSize	= cache_size;
	mCacheBuffer		= new _byte[ mCacheBufferSize ];

	mNotifier			= notifier;

	return _true;
}

_ubool CacheBuffer::SetCacheBufferSize( _dword size )
{
	// Resize the cache buffer size
	if ( size != mCacheBufferSize )
	{
		_byte* old_buffer	= mCacheBuffer;
		_dword old_size		= mCacheBufferSize;

		mCacheBuffer		= new _byte[ size ];
		mCacheBufferSize	= size;

		EGE_MEM_CPY( mCacheBuffer, old_buffer, old_size );

		EGE_DELETE_ARRAY( old_buffer );
	}

	return _true;
}

_dword CacheBuffer::GetCacheBufferOffset( ) const
{
	return mCacheBufferOffset;
}

_dword CacheBuffer::GetCacheBufferSize( ) const
{
	return mCacheBufferSize;
}

const _byte* CacheBuffer::GetCacheBufferData( ) const
{
	return mCacheBuffer;
}

_dword CacheBuffer::GetSize( ) const
{
	return mBufferSize;
}

_dword CacheBuffer::GetOffset( ) const
{
	return mBufferOffset + mCacheBufferOffset;
}

_dword CacheBuffer::Seek( _SEEK flag, _dword offset )
{
	_dword pos = 0;

	switch ( flag )
	{
		case _SEEK_BEGIN:
		{
			pos = offset;
		}
		break;

		case _SEEK_CURRENT:
		{
			pos = mBufferOffset + offset;
		}
		break;

		case _SEEK_END:
		{
			pos = Math::Clamp< _dword >( mBufferSize - offset, 0, mBufferSize - 1 );
		}
		break;

		default:
			break;
	}

	// Flush cache buffer when offset changed
	if ( pos != mBufferOffset + mCacheBufferOffset )
		Flush( );

	mBufferOffset = pos;

	return mBufferOffset;
}

_void CacheBuffer::Write( _dword size, const _byte* buffer )
{
	if ( size == 0 || buffer == _null )
		return;

	// Update buffer if cache buffer is full
	if ( mCacheBufferOffset + size > mCacheBufferSize )
		Flush( );

	// If the buffer is bigger than cache then update it without any cache operation
	if ( size >= mCacheBufferSize )
	{
		_dword new_size = GetOffset( ) + size;
		if ( new_size > mBufferSize )
			Resize( new_size );

		// Flush buffer
		mNotifier->OnUpdateBuffer( mBufferOffset, size, buffer );

		// Update buffer offset
		mBufferOffset += size;
	}
	// Save in cache, defer to update
	else
	{
		// Update cache buffer data
		EGE_MEM_CPY( mCacheBuffer + mCacheBufferOffset, buffer, size );

		// Update the cache offset of buffer
		mCacheBufferOffset += size;
	}
}

_void CacheBuffer::Flush( )
{
	// Skip for empty cache buffer
	if ( mCacheBufferOffset == 0 )
		return;

	// Resize buffer
	_dword new_size = GetOffset( );
	if ( new_size > mBufferSize )
		Resize( new_size );

	// Flush buffer
	mNotifier->OnUpdateBuffer( mBufferOffset, mCacheBufferOffset, mCacheBuffer );

	// Update buffer offset
	mBufferOffset += mCacheBufferOffset;

	// Reset cache buffer data
	mCacheBufferOffset = 0;
}

_void CacheBuffer::Reset( )
{
	mBufferOffset = 0;
}