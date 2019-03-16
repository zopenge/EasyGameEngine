//! @file     LinearAllocator.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// LinearAllocator
//----------------------------------------------------------------------------

class LinearAllocator : public TAllocator< INTERFACE_OBJECT_IMPL( ILinearAllocator ) >
{
private:
	typedef TAllocator< INTERFACE_OBJECT_IMPL( ILinearAllocator ) > BaseClass;

private:
	//!	Get the chunk continuous type.
	enum _CHUNK_CONTINUOUS_TYPE
	{
		_CHUNK_CONTINUOUS_TYPE_NONE,
		_CHUNK_CONTINUOUS_TYPE_1_TO_2,
		_CHUNK_CONTINUOUS_TYPE_2_TO_1,
	};

private:
	//!	The chunk info base
	struct ChunkInfoBase
	{
		_dword	mRefCount;
		_dword	mStartBytes;
		_dword	mTotalBytes;

		ChunkInfoBase( )
		{
			mRefCount	= 1;
			mStartBytes = -1;
			mTotalBytes	= 0;
		}
		ChunkInfoBase( _dword start_bytes, _dword total_bytes )
		{
			mRefCount	= 1;
			mStartBytes = start_bytes;
			mTotalBytes	= total_bytes;
		}
	};

	//!	The used chunk info
	struct UsedChunkInfo : public ChunkInfoBase
	{
		//!	Use the start bytes as key to sort.
		operator _dword( ) const
			{ return mStartBytes; }

		UsedChunkInfo( )
		{
		}
		UsedChunkInfo( _dword start_bytes, _dword total_bytes ) : ChunkInfoBase( start_bytes, total_bytes )
		{
		}
	};
	typedef Array< UsedChunkInfo > UsedChunkInfoArray;

	//!	The free chunk info
	struct FreeChunkInfo : public ChunkInfoBase
	{
		//!	Use the total bytes as key to sort.
		operator _dword( ) const
			{ return mTotalBytes; }

		FreeChunkInfo( )
		{
		}
		FreeChunkInfo( _dword start_bytes, _dword total_bytes ) : ChunkInfoBase( start_bytes, total_bytes )
		{
		}
	};
	typedef Array< FreeChunkInfo > FreeChunkInfoArray;

private:
	//!	The buffer data
	_byte*				mBuffer;
	//!	The buffer size
	_dword				mBufferSize;

	//!	The free chunks
	FreeChunkInfoArray	mFreeChunks;
	//!	The used chunks
	UsedChunkInfoArray	mUsedChunks;

private:
	//!	Get chunk continuous type.
	_CHUNK_CONTINUOUS_TYPE GetChunkContinuousType( const FreeChunkInfo& chunk1, const FreeChunkInfo& chunk2 ) const;

public:
	LinearAllocator( _dword arrange_size );
	virtual ~LinearAllocator( );

public:
	//!	Create.
	_ubool Create( _byte* buffer, _dword size );

// IAllocator Interface
public:
	virtual _void	Cleanup( ) override;

	virtual _ubool	CanAlloc( _dword size ) const override;

	virtual _byte*	Alloc( _dword size ) override;
	virtual _void	Free( _void* pointer ) override;
	virtual _void	FreeAll( ) override;

// ILinearAllocator Interface
public:
	virtual _ubool	RelocateBufferAddress( _byte* buffer ) override;

	virtual _dword	ReserveBufferByStartBytes( _dword start_bytes ) override;
	virtual _dword	FreeByStartBytes( _dword start_bytes ) override;
};

//----------------------------------------------------------------------------
// LinearAllocator Implementation
//----------------------------------------------------------------------------

inline LinearAllocator::_CHUNK_CONTINUOUS_TYPE LinearAllocator::GetChunkContinuousType( const FreeChunkInfo& chunk1, const FreeChunkInfo& chunk2 ) const
{
	if ( chunk1.mStartBytes + chunk1.mTotalBytes == chunk2.mStartBytes )
		return _CHUNK_CONTINUOUS_TYPE_2_TO_1;

	if ( chunk2.mStartBytes + chunk2.mTotalBytes == chunk1.mStartBytes )
		return _CHUNK_CONTINUOUS_TYPE_1_TO_2;

	return _CHUNK_CONTINUOUS_TYPE_NONE;
}

}