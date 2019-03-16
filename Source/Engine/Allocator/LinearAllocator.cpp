//! @file     LinearAllocator.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

// --------------------------------------------------------------------------------------------------------------
// LinearAllocator Implementation
// --------------------------------------------------------------------------------------------------------------

LinearAllocator::LinearAllocator( _dword arrange_size ) : BaseClass( arrange_size )
{
	mBuffer		= _null;
	mBufferSize	= 0;
}

LinearAllocator::~LinearAllocator( )
{
#ifdef _DEBUG
	// Check memory leak
	for ( _dword i = 0; i < mUsedChunks.Number( ); i ++ )
	{
		const UsedChunkInfo& used_chunk_info = mUsedChunks[i];

		EGE_ASSERT( used_chunk_info.mRefCount == 1 );
	}
#endif
}

_ubool LinearAllocator::Create( _byte* buffer, _dword size )
{
	mBuffer		= buffer;
	mBufferSize	= size;

	mFreeChunks.Append( FreeChunkInfo( 0, mBufferSize ) );

	return _true;
}

_void LinearAllocator::Cleanup( )
{
	_ubool need_resort = _false;

	for ( _dword i = 0; i < mFreeChunks.Number( ); i ++ )
	{
		FreeChunkInfo& chunk1 = mFreeChunks[i];

		for ( _dword j = i + 1; j < mFreeChunks.Number( ); j ++ )
		{
			FreeChunkInfo& chunk2 = mFreeChunks[j];

			// Get the continuous chunk type
			_CHUNK_CONTINUOUS_TYPE type = GetChunkContinuousType( chunk1, chunk2 );
			switch ( type )
			{
				case _CHUNK_CONTINUOUS_TYPE_NONE:
					break;

				case _CHUNK_CONTINUOUS_TYPE_1_TO_2:
					need_resort = _true;
					chunk1.mStartBytes  = chunk2.mStartBytes;
					chunk1.mTotalBytes += chunk2.mTotalBytes;
					mFreeChunks.RemoveByIndex( j -- );
					break;

				case _CHUNK_CONTINUOUS_TYPE_2_TO_1:
					need_resort = _true;
					chunk1.mTotalBytes += chunk2.mTotalBytes;
					mFreeChunks.RemoveByIndex( j -- );
					break;

				default:
					break;
			}
		}
	}

	if ( need_resort )
		mFreeChunks.SortDescending( );
}

_ubool LinearAllocator::CanAlloc( _dword size ) const
{
	// Arrange size
	size = Math::UpperArrange( size, mArrangeSize );

	// It's full
	if ( mFreeChunks.Number( ) == 0 )
		return _false;

	// Test the first big free block
	if ( size > mFreeChunks[0].mTotalBytes )
		return _false;

	return _true;
}

_byte* LinearAllocator::Alloc( _dword size )
{
	// Arrange size
	size = Math::UpperArrange( size, mArrangeSize );

	// Check size
	if ( size == 0 || size > mBufferSize )
		return _null;

	for ( _dword i = 0; i < mFreeChunks.Number( ); i ++ )
	{
		FreeChunkInfo& chunk = mFreeChunks[i];

		// Check buffer size, because the chunk sort from big->low, so we can break here ...
		if ( chunk.mTotalBytes < size )
			break;

		// Get address
		_byte* address = mBuffer + chunk.mStartBytes;

		// Insert to used chunks
		mUsedChunks.InsertAscending( UsedChunkInfo( chunk.mStartBytes, size ) );

		// Decrease the chunk size
		chunk.mTotalBytes -= size;
		// Update the start bytes
		chunk.mStartBytes += size;

		// We can remove this chunk because it's full
		if ( chunk.mTotalBytes == 0 )
		{
			mFreeChunks.RemoveByIndex( i );
		}
		// We just decrease the free space of it, but need to re-sort the free chunks array
		else if ( i != mFreeChunks.Number( ) - 1 ) // If it's last chunk then we do not need to sort it
		{
			// Must be lower than the next chunk size, otherwise resort it
			if ( chunk.mTotalBytes < mFreeChunks[ i + 1 ].mTotalBytes ) 
				mFreeChunks.SortDescending( );
		}

		return address;
	}

	// All the free chunks can't allocate buffer with specified size
	return _null;
}

_void LinearAllocator::Free( _void* pointer )
{
	// Get the start bytes
	_dword start_bytes = (_dword)((_byte*) pointer - mBuffer);

	FreeByStartBytes( start_bytes );
}

_ubool LinearAllocator::RelocateBufferAddress( _byte* buffer )
{
	// The buffer can be null, if it's null then indicates just use the offset
	mBuffer = buffer;

	return _true;
}

_dword LinearAllocator::ReserveBufferByStartBytes( _dword start_bytes )
{
	// Search for the used chunk
	UsedChunkInfoArray::Iterator it = mUsedChunks.SearchAscending( start_bytes );
	if ( it.IsValid( ) == _false )
		return 0;

	UsedChunkInfo& info = it;
	info.mRefCount ++;

	return info.mRefCount;
}

_dword LinearAllocator::FreeByStartBytes( _dword start_bytes )
{
	// Search for the used chunk
	UsedChunkInfoArray::Iterator it = mUsedChunks.SearchAscending( start_bytes );
	if ( it.IsValid( ) == _false )
		return 0;

	UsedChunkInfo& info = it;

	// We can free this chunk now
	if ( info.mRefCount == 1 )
	{
		// Insert it into free chunks
		mFreeChunks.InsertDescending( FreeChunkInfo( info.mStartBytes, info.mTotalBytes ) );

		// Remove it from used chunks
		mUsedChunks.Remove( it );

		return 0;
	}
	else
	{
		// It's reserved chunk, just decrease referenced count
		EGE_ASSERT( info.mRefCount != 0 );
		info.mRefCount --;

		return info.mRefCount;
	}
}

_void LinearAllocator::FreeAll( )
{
	mFreeChunks.Clear( );
	mFreeChunks.Append( FreeChunkInfo( 0, mBufferSize ) );
}