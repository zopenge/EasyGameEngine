//! @file     SoundBufferQueue.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGESound.h"

//----------------------------------------------------------------------------
// SoundBufferQueue Implementation
//----------------------------------------------------------------------------

SoundBufferQueue::SoundBufferQueue( SourceSHI* source ) : mSourceSHI( source )
{
	mDecodeBufferSize	= 0;
	mDecodeBuffer		= _null;
}

SoundBufferQueue::~SoundBufferQueue( )
{
	UnqueueBuffers( );

	for ( _dword i = 0; i < _MAX_SOUND_BUFFER_QUEUE_NUMBER; i ++ )
		mBuffers[i].Clear( );

	EGE_DELETE_ARRAY( mDecodeBuffer );
	mDecodeBufferSize = 0;
}

_dword SoundBufferQueue::GetDecodeBufferSize( const SoundHeaderInfo& info )
{
	// Get the total bytes in 0.25 second to determine the buffer size
	_dword decode_size = info.GetTotalBytesInOneSecond( ) / 4;

	// Arrange decode size
	return Math::UpperArrange( decode_size, info.GetBytesFromFormat( ) );
}

_ubool SoundBufferQueue::PushInitialBuffers( ISoundFile* sound_file )
{
	// Decode the sound stream
	_dword decode_size = sound_file->Decode( mDecodeBuffer, mDecodeBufferSize );
	if ( decode_size == 0 )
		return _false;

	// Get the sound file header info
	const SoundHeaderInfo& sound_header_info = sound_file->GetHeaderInfo( );

	// Check whether can split it into buffers
	_dword element_size_in_btyes	= sound_header_info.mSampleBitSize / 8;
	_dword min_size					= element_size_in_btyes * _MAX_SOUND_BUFFER_QUEUE_NUMBER;
	if ( decode_size < min_size )
		return _false;

	// Check alignment
	if ( decode_size % element_size_in_btyes )
		return _false;

	// Get the buffer size
	_dword offset		= 0;
	_dword remain_size	= decode_size;
	_dword buf_size		= decode_size / _MAX_SOUND_BUFFER_QUEUE_NUMBER;

	// Start to push initial buffers
	for ( _dword i = 0; i < _MAX_SOUND_BUFFER_QUEUE_NUMBER; i ++ )
	{
		_dword size = Math::UpperArrange( Math::Min( remain_size, buf_size ), element_size_in_btyes );

		// Update the sound buffer data
		if ( gDynamicSHI->SetBufferData( mBuffers[i], mDecodeBuffer + offset, size, sound_header_info.mFormat, sound_header_info.mSampleRate ) == _false )
		{
			WLOG_ERROR( L"Push buffer failed, due to set sound buffer data failed" );
			return _false;
		}

		// Add into queue ( if it's loop playing mode then force to sync buffers )
		gDynamicSHI->SourceQueueBuffer( mSourceSHI, mBuffers[i] );

		// Update remain size and offset
		remain_size -= size;
		offset		+= size;
	}

	EGE_ASSERT( remain_size == 0 );

	return _true;
}

SoundBufferQueue::_PUSH_BUFFER_RET SoundBufferQueue::PushBuffer( ISoundFile* sound_file, BufferSHI* buffer, _ubool& perform_loop_op )
{
	// Decode the sound stream
	_dword decode_size = sound_file->Decode( mDecodeBuffer, mDecodeBufferSize );
	if ( decode_size == 0 )
	{
		// Loop play
		if ( mFlags.HasFlags( _FLAG_IS_LOOP ) )
		{
			perform_loop_op = _true;

			sound_file->TimeSeek( _SEEK_BEGIN, 0.0 );

			return _PUSH_BUFFER_RET_ROLLBACK;
		}
		// Stop to play, but skip for streaming sound
		else if ( sound_file->IsStreaming( ) == _false )
		{
			Stop( );
		}

		return _PUSH_BUFFER_RET_DO_NOTHING;
	}
	else
	{
		// Get the sound file header info
		const SoundHeaderInfo& sound_header_info = sound_file->GetHeaderInfo( );

		// Update the sound buffer data
		if ( gDynamicSHI->SetBufferData( buffer, mDecodeBuffer, decode_size, sound_header_info.mFormat, sound_header_info.mSampleRate ) == _false )
		{
			WLOG_ERROR( L"Push buffer failed, due to set sound buffer data failed" );
			return _PUSH_BUFFER_RET_FAILED;
		}

		// Add into queue ( if it's loop playing mode then force to sync buffers )
		gDynamicSHI->SourceQueueBuffer( mSourceSHI, buffer );

		return _PUSH_BUFFER_RET_PUSHED;
	}
}

_void SoundBufferQueue::PushBuffers( ISoundFile* sound_file, _dword number, BufferSHI* buffers[] )
{
    if ( sound_file == _null )
        return;
    
	// True indicates perform the loop operation
	_ubool perform_loop_op = _false;

	// Push buffers
	for ( _dword i = 0; i < number; i ++ )
	{
		BufferSHI* buffer = buffers[i];
		EGE_ASSERT( buffer != _null );
        
		// Push buffer
		_PUSH_BUFFER_RET ret = PushBuffer( sound_file, buffer, perform_loop_op );
		if ( ret == _PUSH_BUFFER_RET_ROLLBACK )
			i --;
	}

	// Play the sound if we perform loop
	if ( perform_loop_op )
		gDynamicSHI->SourcePlay( mSourceSHI );
}

_void SoundBufferQueue::PushBuffers( ISoundFile* sound_file )
{
	EGE_ASSERT( sound_file != _null );

	if ( mFlags.HasFlags( _FLAG_WAIT_FOR_INITIAL_BUFFERS ) )
	{
		if ( PushInitialBuffers( sound_file ) )
			mFlags.ClearFlags( _FLAG_WAIT_FOR_INITIAL_BUFFERS );
	}
	else
	{
		// Get the number of buffers what had been processed
		_dword processed_number = gDynamicSHI->GetSourceAttributei( mSourceSHI, _SSA_BUFFERS_PROCESSED );
		if ( processed_number != 0 )
		{
			// Unqueue buffers
			BufferSHI* buffers[_MAX_SOUND_BUFFER_QUEUE_NUMBER] = {0};
			gDynamicSHI->SourceUnqueueBuffers( mSourceSHI, 1, buffers );

			// Push buffers
			PushBuffers( sound_file, 1, buffers );
		}
	}
}

_ubool SoundBufferQueue::Initialize( _AUDIO_FORMAT format )
{
	// Create sound buffers
	for ( _dword i = 0; i < _MAX_SOUND_BUFFER_QUEUE_NUMBER; i ++ )
	{
		mBuffers[i] = gDynamicSHI->CreateBuffer( );
		if ( mBuffers[i].IsNull( ) )
			return _false;
	}

	return _true;
}

_void SoundBufferQueue::UnqueueBuffers( )
{
	// Unqueue buffers
	gDynamicSHI->SourceUnqueueBuffers( mSourceSHI, _MAX_SOUND_BUFFER_QUEUE_NUMBER );
}

_ubool SoundBufferQueue::IsPlaying( ) const
{
	if ( mFlags.HasFlags( _FLAG_IS_LOOP ) )
		return _true;

	if ( mFlags.HasFlags( _FLAG_HAS_STOPPED ) == _false )
		return _true;

	return _false;
}

_void SoundBufferQueue::Update( ISoundFile* sound_file )
{
	if ( mFlags.HasFlags( _FLAG_HAS_STOPPED ) )
		return;

	// Push buffers from sound file
	PushBuffers( sound_file );

	// Make sure we are playing now, sometimes the sound could break due to update thread is slow
	if ( gDynamicSHI->GetSourceState( mSourceSHI ) != _SSS_PLAYING )
		gDynamicSHI->SourcePlay( mSourceSHI );
}

_void SoundBufferQueue::Play( ISoundFile* sound_file, _ubool append, _ubool loop, _ubool force_stop )
{
	if ( sound_file == _null )
		return;

	// Get the sound info
	const SoundHeaderInfo& sound_header_info = sound_file->GetHeaderInfo( );

	// Get the decode buffer size
	_dword decode_buffer_size = GetDecodeBufferSize( sound_header_info );
	EGE_ASSERT( decode_buffer_size != 0 );
	
	// Create decode buffer
	if ( mDecodeBufferSize != decode_buffer_size )
	{
		EGE_DELETE_ARRAY( mDecodeBuffer );

		mDecodeBufferSize	= decode_buffer_size;
		mDecodeBuffer		= new _byte[ mDecodeBufferSize ];
		EGE_MEM_SET( mDecodeBuffer, 0, mDecodeBufferSize );
	}

	mFlags.EnableFlags( _FLAG_IS_LOOP, loop );
	mFlags.EnableFlags( _FLAG_HAS_STOPPED, _false );

	if ( append )
	{
		// Reset the sound file time offset
		sound_file->TimeSeek( _SEEK_BEGIN, 0.0 );
	}
	else
	{
		// Stop it first then wait for playing
		if ( force_stop )
			gDynamicSHI->SourceStop( mSourceSHI );

		// Clear the old buffers
		UnqueueBuffers( );

		// Reset the sound file time offset
		sound_file->TimeSeek( _SEEK_BEGIN, 0.0 );

		// Push initial buffers
		mFlags.EnableFlags( _FLAG_WAIT_FOR_INITIAL_BUFFERS, _true );
		if ( PushInitialBuffers( sound_file ) )
			mFlags.ClearFlags( _FLAG_WAIT_FOR_INITIAL_BUFFERS );
	}

	// Start to play
	gDynamicSHI->SourcePlay( mSourceSHI );
}

_void SoundBufferQueue::Stop( )
{
	mFlags.EnableFlags( _FLAG_IS_LOOP, _false );
	mFlags.EnableFlags( _FLAG_HAS_STOPPED, _true );

	UnqueueBuffers( );
}