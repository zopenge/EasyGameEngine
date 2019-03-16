//! @file     SLResources.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGESound.h"

#if (_USE_OPENSL_ == 1)

//----------------------------------------------------------------------------
// SLEffect Implementation
//----------------------------------------------------------------------------

SLEffect::SLEffect( )
{
}

SLEffect::~SLEffect( )
{
}

//----------------------------------------------------------------------------
// SLBuffer Implementation
//----------------------------------------------------------------------------

SLBuffer::SLBuffer( )
{
	mData		= _null;
	mSize		= 0;
	mFormat		= _AF_UNKNOWN;
	mSampleRate	= 0;
}

SLBuffer::~SLBuffer( )
{
	EGE_DELETE_ARRAY( mData );
}

_ubool SLBuffer::Copy( const _void* data, _dword size, _AUDIO_FORMAT format, _dword sample_rate )
{
	if ( data == _null || size == 0 )
		return _false;

	if ( mSize < size )
	{
		EGE_DELETE_ARRAY( mData );
		mData = new _byte[ size ];
	}

	EGE_MEM_CPY( mData, data, size );

	mSize		= size;
	mFormat		= format;
	mSampleRate	= sample_rate;

	return _true;
}

//----------------------------------------------------------------------------
// SLSource Implementation
//----------------------------------------------------------------------------

SLSource::SLSource( )
{
	mPlayerObject			= _null;
	mPlayerPlay				= _null;
	mPlayerBufferQueue		= _null;
	mPlayerEffectSend		= _null;
	mPlayerVolume			= _null;
	mPlayerPlaybackRate		= _null;
	
	mProcessedBuffersNumber	= 0;

	mVolume					= 0.0f;
	mPitch					= 1000;
}

SLSource::~SLSource( )
{
	// Stop it
	SetPlayerState( SL_PLAYSTATE_STOPPED );

	// Release source
	if ( mPlayerObject != _null )
	{
		WLOG_TRACE_1( L"Destroy '0x%.8x' sound source", (_dword) mPlayerObject );
		(*mPlayerObject)->Destroy( mPlayerObject );
	}
}

void SLSource::OnSimpleBufferQueueCallback( SLAndroidSimpleBufferQueueItf caller, void* context )
{
	SLSource* sl_source = (SLSource*) context;
	EGE_ASSERT( sl_source != _null );

	// Update processed buffer number
	sl_source->mProcessedBuffersNumber ++;
}

_float SLSource::Gain2Attenuation( float gain )
{
	// Referenced from: http://vec3.ca/getting-started-with-opensl-on-android/ Thanks for sharing code
	return gain < 0.01F ? -96.0F : 20 * log10( gain );
}

_void SLSource::ClearBufferQueue( )
{
	mProcessedBuffersNumber = 0;
	mBuffersQueue.Clear( );

	(*mPlayerBufferQueue)->Clear( mPlayerBufferQueue );
}

_ubool SLSource::CreateInternalComponents( )
{
	SLresult result;

	// Get the play interface
	result = (*mPlayerObject)->GetInterface(mPlayerObject, SL_IID_PLAY, &mPlayerPlay);
	SL_CHECK_RESULT_BOOL( "Get OpenSL player interface object" );

	// Get the effect send interface
	result = (*mPlayerObject)->GetInterface(mPlayerObject, SL_IID_EFFECTSEND, &mPlayerEffectSend);
	SL_CHECK_RESULT_BOOL( "Register OpenSL effect send interface" );

	// Get the volume interface
	result = (*mPlayerObject)->GetInterface(mPlayerObject, SL_IID_VOLUME, &mPlayerVolume);
	SL_CHECK_RESULT_BOOL( "Register OpenSL volume interface" );

	// Get the playback rate interface
	result = (*mPlayerObject)->GetInterface(mPlayerObject, SL_IID_PLAYBACKRATE, &mPlayerPlaybackRate);
	SL_CHECK_RESULT_BOOL( "Register OpenSL playback rate interface" );

	return _true;
}

_ubool SLSource::InitPCM( const SoundHeaderInfo& info, SLEngineItf engine, SLObjectItf output_mix_object )
{
	SLresult result;

	// Configure audio buffer queue
	SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {0};
	loc_bufq.locatorType							= SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE;
	loc_bufq.numBuffers								= _MAX_SOUND_BUFFER_QUEUE_NUMBER;

	// Configure audio source format
	SLDataFormat_PCM format_pcm = {0};
	format_pcm.formatType		= SL_DATAFORMAT_PCM;
	format_pcm.numChannels		= info.mChannels;
	format_pcm.samplesPerSec	= info.mSampleRate * 1000;
	format_pcm.bitsPerSample	= SL_PCMSAMPLEFORMAT_FIXED_16;
	format_pcm.containerSize	= SL_PCMSAMPLEFORMAT_FIXED_16;
	format_pcm.channelMask		= info.mChannels == 1 ? SL_SPEAKER_FRONT_CENTER : SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
	format_pcm.endianness		= SL_BYTEORDER_LITTLEENDIAN;
	SLDataSource audioSrc = {&loc_bufq, &format_pcm};

	// Configure audio sink
	SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, output_mix_object};
	SLDataSink audioSnk = {&loc_outmix, NULL};

	// Create audio player
	const SLInterfaceID ids[] = {SL_IID_ANDROIDSIMPLEBUFFERQUEUE, SL_IID_EFFECTSEND, SL_IID_VOLUME, SL_IID_PLAYBACKRATE};
	const SLboolean req[] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
	result = (*engine)->CreateAudioPlayer(engine, &mPlayerObject, &audioSrc, &audioSnk, 4, ids, req);
	if ( result != SL_RESULT_SUCCESS )
	{
		WLOG_ERROR_3( L"Create audio player object failed(channel:%d, sample_rate:%d), ret:%d", info.mChannels, info.mSampleRate, result );
		return _false;
	}

	// Realize the player
	result = (*mPlayerObject)->Realize(mPlayerObject, SL_BOOLEAN_FALSE);
	if ( result != SL_RESULT_SUCCESS )
	{
		WLOG_ERROR_3( L"Realize audio player object failed(channel:%d, sample_rate:%d), ret:%d", info.mChannels, info.mSampleRate, result );
		return _false;
	}

	// Get the buffer queue interface
	result = (*mPlayerObject)->GetInterface(mPlayerObject, SL_IID_ANDROIDSIMPLEBUFFERQUEUE, &mPlayerBufferQueue);
	SL_CHECK_RESULT_BOOL( "Get OpenSL simple buffer queue interface object" );

	// Register callback on the buffer queue
	result = (*mPlayerBufferQueue)->RegisterCallback(mPlayerBufferQueue, OnSimpleBufferQueueCallback, this );
	SL_CHECK_RESULT_BOOL( "Register OpenSL simple buffer queue callback function" );

	// Create internal components
	if ( CreateInternalComponents( ) == _false )
		return _false;

	WLOG_TRACE_2( L"Create audio player object OK(channel:%d, sample_rate:%d)", info.mChannels, info.mSampleRate );

	return _true;
}

_ubool SLSource::InitMIDI( const _byte* buffer, _dword size, SLEngineItf engine, SLObjectItf output_mix_object )
{
	if ( buffer == _null || size == 0 )
		return _false;

	SLresult result;
	
	// Initialize SL data locator and format
	SLDataLocator_Address	file_loc = { SL_DATALOCATOR_ADDRESS, (_void*) buffer, size };
	SLDataFormat_MIME		file_fmt = { SL_DATAFORMAT_MIME, (SLchar*) "audio/midi", SL_CONTAINERTYPE_SMF };

	// Initialize file data source
	SLDataSource file_src;
	file_src.pFormat	= &file_fmt;
	file_src.pLocator	= &file_loc;

	// Initialize SL output
	SLDataSink				aud_out_snk;
	SLDataLocator_OutputMix aud_out_loc;
	aud_out_loc.locatorType = SL_DATALOCATOR_OUTPUTMIX;
	aud_out_loc.outputMix	= output_mix_object;
	aud_out_snk.pFormat		= _null;
	aud_out_snk.pLocator	= &aud_out_loc;

	// The interface features
	const SLboolean		required_interfaces[]			= {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
	const SLInterfaceID	required_interfaces_states[]	= {SL_IID_PLAY, SL_IID_SEEK, SL_IID_VOLUME, SL_IID_PITCH};

	// Create MIDI player
	result = (*engine)->CreateMidiPlayer( engine, &mPlayerObject, &file_src, _null, &aud_out_snk, _null, _null, 4, required_interfaces_states, required_interfaces );
	SL_CHECK_RESULT_BOOL( "Create OpenSL MIDI player" );

	// Create internal components
	if ( CreateInternalComponents( ) == _false )
		return _false;

	return _true;
}

_ubool SLSource::SetVolume( _float volume )
{
	SLmillibel value = (SLmillibel)( Gain2Attenuation( volume ) * 100.0f );

	SLresult result = (*mPlayerVolume)->SetVolumeLevel( mPlayerVolume, value );
	if ( result != SL_RESULT_SUCCESS )
	{
		WLOG_ERROR_2( L"Set player volume to '%d' failed, ret:%d", (_int) value, result );
		return _false;
	}

	mVolume = volume;

	return _true;
}

_ubool SLSource::SetPitch( _float pitch )
{
	SLpermille pitch_in_mille = (SLpermille)(pitch * 1000.0f);

	SLresult result = (*mPlayerPlaybackRate)->SetRate( mPlayerPlaybackRate, pitch_in_mille );
	if ( result != SL_RESULT_SUCCESS )
	{
		WLOG_ERROR_2( L"Set player's pitch to '%d' failed, ret:%d", pitch_in_mille, result );
		return _false;
	}

	mPitch = pitch_in_mille;

	return _true;
}

_dword SLSource::GetUnprocessedQueueNumber( ) const
{
	EGE_ASSERT( mBuffersQueue.Number( ) >= mProcessedBuffersNumber );

	return mBuffersQueue.Number( ) - mProcessedBuffersNumber;
}

_ubool SLSource::QueueBuffers( _dword number, BufferSHI** buffers )
{
	if ( number == 0 )
		return _false;

	for ( _dword i = 0; i < number; i ++ )
	{
		SLBuffer* buffer = static_cast< SLBuffer* >( buffers[i] );
		if ( buffer == _null )
			continue;

		// Queue buffer
		SLresult result = (*mPlayerBufferQueue)->Enqueue( mPlayerBufferQueue, buffer->GetData( ), buffer->GetSize( ) );
		SL_CHECK_RESULT_BOOL( "Enqueue buffer" );

		mBuffersQueue.Append( buffer );
	}

	return _true;
}

_void SLSource::UnqueueBuffers( _dword number, BufferSHI** buffers )
{
	// Get the total number of buffers what we will remove
	_dword total_number = Math::Min( mBuffersQueue.Number( ), Math::Min( number, mProcessedBuffersNumber ) );

	// Remove buffers
	for ( _dword i = 0; i < total_number; i ++ )
	{
		buffers[i] = mBuffersQueue.Front( );
		mBuffersQueue.Remove( );
	}

	// Decrease the processed buffers number
	mProcessedBuffersNumber -= total_number;
}

_ubool SLSource::SetPlayerState( SLuint32 state )
{
	// Set the playing state
	SLresult result = (*mPlayerPlay)->SetPlayState(mPlayerPlay, state);
	if ( result != SL_RESULT_SUCCESS )
	{
		ALOG_ERROR_2( "Set player state to '%d' failed, ret:%d", state, result );
		return _false;
	}

	// Stop
	if ( state == SL_PLAYSTATE_STOPPED )
		ClearBufferQueue( );

	return _true;
}

SLuint32 SLSource::GetPlayerState( )
{
	// If we don't have any buffers to play then indicates it's stop
	if ( mBuffersQueue.Number( ) == 0 )
		return SL_PLAYSTATE_STOPPED;

	// In android, GetPlayState() interface could dead-lock between main and background threads, fuck the OpenSL implementation ....
	SLuint32 state = SL_PLAYSTATE_STOPPED;

	SLresult result = (*mPlayerPlay)->GetPlayState(mPlayerPlay, &state);
	if ( result != SL_RESULT_SUCCESS )
	{
		WLOG_ERROR_1( L"Get player state failed, ret:%d", result );
		return SL_PLAYSTATE_STOPPED;
	}

	return state;
}

#endif