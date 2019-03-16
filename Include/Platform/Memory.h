//! @file     Memory.h
//! @author   LiCode
//! @version  1.1.0.547
//! @date     2011/01/07
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// MemoryAllocation
//----------------------------------------------------------------------------

//! This class represents memory allocation information, used for memory track.
struct MemoryAllocation
{
	//! The memory referenced ID
	_dword				mReferencedID;
	//! The memory block size.
	_dword				mSize;

	//! The line number of memory allocation
	_dword				mLineNumber;
	//! The file name of memory allocation in ANSI
	const _chara*		mFileNameANSI;

	//! The frame number of callstack
	_dword				mFrameNumber;
	//! The full callstack
	ASrcFileLineInfo*	mSrcFileLines;

	//! We use the size as key when we need to sort it
	operator _dword( ) const
		{ return mSize; }
};

//----------------------------------------------------------------------------
// MemoryBlockAllocation
//----------------------------------------------------------------------------

struct MemoryBlockAllocation
{
	_dword	mBlockNumber;
	_dword	mSize;
	_dword	mLineNumber;
	_chara*	mFileName;

	operator _dword( ) const
		{ return mBlockNumber; }

	MemoryBlockAllocation( )
	{
		mBlockNumber	= 0;
		mSize			= 0;
		mLineNumber		= 0;
		mFileName		= _null;
	}
};

//----------------------------------------------------------------------------
// Memory
//----------------------------------------------------------------------------

//! This class trace memory allocation to detect memory leak and allocate times etc.
class Memory
{
public:
	//! It's singleton class.
	SINGLETON( Memory )

private:
	typedef Link< MemoryAllocation > AllocationLink;
	typedef Array< MemoryBlockAllocation > BlockAllocationArray;

private:
	//! The default max frame number of callstack
	enum
	{
		_DEFAULT_MIN_FRAME_NUMBER = 4,
		_DEFAULT_MAX_FRAME_NUMBER = 16
	};

	//! The max file name length
	enum 
	{
		_MAX_FILE_NAME_LENGTH = 255,
	};

private:
	//! Locker
	Lock					mLocker;

	//! The memory referenced ID
	_dword					mReferencedID;

	//! True indicates use the full callstack check
	_ubool					mIsUseFullCallstackCheck;
	//! The max frame number
	_dword					mMaxFrameNumber;
	//! The line number filter
	_dword					mLineNumberFilter;
	//! The file name filter
	_chara					mFileNameFilter[ _MAX_FILE_NAME_LENGTH ];

	//! The current allocation number
	_dword					mCurAllocNumber;
	//! The current allocation total size in number of bytes.
	_dword					mCurAllocSize;

	//! The allocated memory block list
	AllocationLink			mMemoryAllocation;
	//! The block array
	BlockAllocationArray	mBlockAllocations;

private:
	//! When dump the allocation info.
	typedef _void (*OnOutputString)( _dword id, const _byte* address, const MemoryAllocation& allocation, const QwordParameters2& parameters );

	//! When output string.
	static _void OnOutputStringCallback( _dword id, const _byte* address, const MemoryAllocation& allocation, const QwordParameters2& parameters );

	//! Alloc/Free tail of memory block.
	static _void LockTailOfMemoryBlock( _byte* object, _dword allocedsize );
	static _void UnlockTailOfMemoryBlock( _byte* object, _dword allocedsize );

private:
	//! Check whether enable full callstack check.
	_ubool IsEnableFullCallstackCheck( _dword line_number, const _chara* file_name ) const;

	//! Dump allocations.
	_void DumpAllocations( _dword min_size, OnOutputString funcpointer, const AllocationLink& allocations, const QwordParameters2& parameters );
	_void DumpAllocations( _dword min_size, OnOutputString funcpointer, const BlockAllocationArray& allocations, const QwordParameters2& parameters );

public:
	//! Initialize.
	//! @param		none.
	//! @return		True indicates successful, otherwise indicates failure.
	_ubool Initialize( );
	//! Finalize.
	//! @param		none.
	//! @return		none.
	_void Finalize( );

	//! Enable/Disable full callstack check.
	//! @param		enable			True indicates enable full callstack check.
	//! @return		none.
	_void EnableFullCallstackCheck( _ubool enable );
	//! Set the max frame number of full callstack check.
	//! @param		max_frame_number	The max frame number of full callstack check.
	//! @return		none.
	_void SetMaxFrameNumberOfFullCallstackCheck( _dword max_frame_number );
	//! Set the file name filter of full callstack check.
	//! @param		filter				The file name filter of full callstack check.
	//! @return		none.
	_void SetFileNameFilterOfFullCallstackCheck( const _chara* filter );
	//! Set the line number filter of full callstack check.
	//! @param		line_number			The line number filter of full callstack check.
	//! @return		none.
	_void SetLineNumberFilterOfFullCallstackCheck( _dword line_number );

	//! Allocate block memory from heap and trace the allocation information.
	//! @param		block_number	The block number.
	//! @param		size			The size of memory will be allocated in number of bytes.
	//! @param		filename		The filename of allocated cpp module.
	//! @param		linenumber		The line number of allocated cpp module.
	//! @return		none.
	_void AllocBlock( _dword block_number, _dword size, const _chara* filename, _dword linenumber );
	//! Allocate block memory from heap and trace the allocation information.
	//! @param		prev_block_number	The previous block number.
	//! @param		block_number		The block number.
	//! @param		size				The size of memory will be allocated in number of bytes.
	//! @param		filename			The filename of allocated cpp module.
	//! @param		linenumber			The line number of allocated cpp module.
	//! @return		none.
	_void ReallocBlock( _dword prev_block_number, _dword block_number, _dword size, const _chara* filename, _dword linenumber );
	//! Frees a block memory block allocated and remove allocation information.
	//! @param		block_number	The block number.
	//! @return		none.
	_void FreeBlock( _dword block_number );

	//! Allocate memory from heap and trace the allocation information.
	//! @param		size		The size of memory will be allocated in number of bytes.
	//! @param		filename	The filename of allocated cpp module.
	//! @param		linenumber	The line number of allocated cpp module.
	//! @return		The pointer to the allocated memory block.
	_void* Alloc( _dword size, const _chara* filename, _dword linenumber );
	//! Reallocate memory from heap and trace the allocation information.
	//! @param		buffer		The original buffer pointer.
	//! @param		size		The size of memory will be allocated in number of bytes.
	//! @param		filename	The filename of allocated cpp module.
	//! @param		linenumber	The line number of allocated cpp module.
	//! @return		The pointer to the allocated memory block.
	_void* Realloc( _void* buffer, _dword size, const _chara* filename, _dword linenumber );
	//! Frees a memory block allocated and remove allocation information.
	//! @param		pointer		The pointer to the memory block to be freed.
	//! @param		filename	The filename of allocated cpp module.
	//! @param		linenumber	The line number of allocated cpp module.
	//! @return		none.
	_void Free( _void* pointer, const _chara* filename, _dword linenumber );

	//! Allocate ANSI string from heap.
	//! @param		string		The ANSI string.
	//! @param		filename	The filename of allocated cpp module.
	//! @param		linenumber	The line number of allocated cpp module.
	//! @return		The pointer to the allocated memory block.
	_chara* AllocStr( const _chara* string, const _chara* filename, _dword linenumber );
	//! Allocate UTF-16 string from heap.
	//! @param		string		The UTF-16 string.
	//! @param		filename	The filename of allocated cpp module.
	//! @param		linenumber	The line number of allocated cpp module.
	//! @return		The pointer to the allocated memory block.
	_charw* AllocStr( const _charw* string, const _chara* filename, _dword linenumber );

	//! Get current allocation number.
	//! @param		none.
	//! @return		The current allocation number.
	_dword GetCurAllocNumber( ) const;
	//! Clear current allocation number.
	//! @param		none.
	//! @return		none.
	_void ClearCurAllocNumber( );
	//! Get current allocation total size in number of bytes.
	//! @param		none.
	//! @return		The current allocation total size in number of bytes.
	_dword GetCurAllocSize( ) const;
	//! Get total allocation number.
	//! @param		none.
	//! @return		The current allocation number.
	_dword GetTotalAllocNumber( ) const;

	//! Create referenced buffer.
	//! @param		size		The size of memory will be allocated in number of bytes.
	//! @return		The pointer to the allocated memory block.
	_void* CreateReferencedBuffer( _dword size );
	//! Reserve referenced buffer.
	//! @param		pointer		The pointer to the memory block to be reserved.
	//! @return		The pointer to the reserved memory block.
	_void* ReserveReferencedBuffer( _void* buffer );
	//! Release referenced buffer.
	//! @param		pointer		The pointer to the memory block to be released.
	//! @return		True if the buffer is really released, or false if the buffer is just dereferenced.
	_ubool ReleaseReferencedBuffer( _void* buffer );
	//! Check if it's referenced buffer or not.
	//! @param		pointer		The pointer to the memory block to be checked.
	//! @return		True indicates it's referenced buffer.
	_ubool IsReferencedBuffer( _void* buffer );

	//! Dump allocations.
	//! @param		min_size	The min size in byte.
	//! @return		none.
	_void Dump( _dword min_size, OnOutputString funcpointer, const QwordParameters2& parameters );
	//! Dump the current leak memory info.
	//! @param		none.
	//! @return		none.
	_void DumpLeakInfo( );
};

}