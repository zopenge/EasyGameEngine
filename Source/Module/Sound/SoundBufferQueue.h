//! @file     SoundBufferQueue.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// SoundBufferQueue
//----------------------------------------------------------------------------

class SoundBufferQueue
{
private:
	typedef Array< BufferSHIRef > BufferRefArray;

private:
	enum
	{
		_MAX_SOUND_BUFFER_QUEUE_NUMBER = 2
	};

	enum _FLAG
	{
		//!	True indicates play in loop way
		_FLAG_IS_LOOP					= 1 << 0,
		//!	True indicates stopped
		_FLAG_HAS_STOPPED				= 1 << 1,
		//!	True indicates still wait for pushing initial buffers
		_FLAG_WAIT_FOR_INITIAL_BUFFERS	= 1 << 2,
	};

	enum _PUSH_BUFFER_RET
	{
		_PUSH_BUFFER_RET_DO_NOTHING,
		_PUSH_BUFFER_RET_PUSHED,
		_PUSH_BUFFER_RET_ROLLBACK,
		_PUSH_BUFFER_RET_FAILED,
	};

private:
	//!	The source flags
	FlagsObject		mFlags;
	//!	The source resource
	SourceSHIRef	mSourceSHI;

	//!	The decode buffer size in bytes.
	_dword			mDecodeBufferSize;
	//!	The decode buffer
	_byte*			mDecodeBuffer;

	//!	The sound buffer resource
	BufferSHIRef	mBuffers[ _MAX_SOUND_BUFFER_QUEUE_NUMBER ];

private:
	//!	Get the decode buffer size.
	static _dword GetDecodeBufferSize( const SoundHeaderInfo& info );

private:
	//!	Push initial buffers
	_ubool PushInitialBuffers( ISoundFile* sound_file );
	//!	Push buffer.
	_PUSH_BUFFER_RET PushBuffer( ISoundFile* sound_file, BufferSHI* buffer, _ubool& perform_loop_op );
	//!	Push buffers into queue.
	_void PushBuffers( ISoundFile* sound_file, _dword number, BufferSHI* buffers[] );
	_void PushBuffers( ISoundFile* sound_file );

public:
	SoundBufferQueue( SourceSHI* source );
	~SoundBufferQueue( );

public:
	//!	Initialize.
	_ubool Initialize( _AUDIO_FORMAT format );

	//!	Unqueue the buffers.
	_void UnqueueBuffers( );

	//!	Check whether it's playing.
	_ubool IsPlaying( ) const;

	//!	Update.
	_void Update( ISoundFile* sound_file );
	//!	Play from file.
	_void Play( ISoundFile* sound_file, _ubool append, _ubool loop, _ubool force_stop );
	//!	Stop.
	_void Stop( );
};

//----------------------------------------------------------------------------
// SoundBufferQueue Implementation
//----------------------------------------------------------------------------

}