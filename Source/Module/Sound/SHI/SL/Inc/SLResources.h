//! @file     SLResources.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// SLEffect
//----------------------------------------------------------------------------

class SLEffect : public TDynamicSHIResource< _SRT_EFFECT >
{
private:

public:
	SLEffect( );
	virtual ~SLEffect( );
};

//----------------------------------------------------------------------------
// SLBuffer
//----------------------------------------------------------------------------

class SLBuffer : public TDynamicSHIResource< _SRT_BUFFER >
{
private:
	_byte*			mData;
	_dword			mSize;
	_AUDIO_FORMAT	mFormat;
	_dword			mSampleRate;

public:
	SLBuffer( );
	virtual ~SLBuffer( );

public:
	EGE_GET_ACCESSOR( const _byte*, Data )
	EGE_GET_ACCESSOR( _dword, Size )
	EGE_GET_ACCESSOR( _AUDIO_FORMAT, Format )
	EGE_GET_ACCESSOR( _dword, SampleRate )

public:
	//!	Get the buffer data.
	const _byte* GetData( ) const;
	//!	Get the buffer size.
	_dword GetSize( ) const;

	//!	Copy buffer data.
	_ubool Copy( const _void* data, _dword size, _AUDIO_FORMAT format, _dword sample_rate );
};

//----------------------------------------------------------------------------
// SLSource
//----------------------------------------------------------------------------

class SLSource : public TDynamicSHIResource< _SRT_SOURCE >
{
private:
	typedef Queue< BufferSHIRef, BufferSHI* > BufferSHIQueue;

private:
	SLObjectItf						mPlayerObject;
	SLPlayItf						mPlayerPlay;
	SLAndroidSimpleBufferQueueItf	mPlayerBufferQueue;
	SLEffectSendItf					mPlayerEffectSend;
	SLVolumeItf						mPlayerVolume;
	SLPlaybackRateItf				mPlayerPlaybackRate;

	BufferSHIQueue					mBuffersQueue;
	volatile _dword					mProcessedBuffersNumber;

	_float							mVolume;
	SLpermille						mPitch;

private:
	//!	When queue buffers.
	static void OnSimpleBufferQueueCallback( SLAndroidSimpleBufferQueueItf caller, void* context );

	//!	Convert gain to attenuation.
	static _float Gain2Attenuation( float gain );

private:
	//!	Clear buffer queue.
	_void ClearBufferQueue( );

	//!	Create internal components.
	_ubool CreateInternalComponents( );

public:
	SLSource( );
	virtual ~SLSource( );

public:
	EGE_GET_ACCESSOR( _dword, ProcessedBuffersNumber )
	EGE_GET_ACCESSOR( _float, Volume )
	EGE_GET_ACCESSOR( _float, Pitch )

public:
	//!	Initialize.
	_ubool InitPCM( const SoundHeaderInfo& info, SLEngineItf engine, SLObjectItf output_mix_object );
	_ubool InitMIDI( const _byte* buffer, _dword size, SLEngineItf engine, SLObjectItf output_mix_object );

	//!	Set volume.
	_ubool SetVolume( _float volume );
	//!	Set pitch.
	_ubool SetPitch( _float pitch );

	//!	Get the unprocessed queue number
	_dword GetUnprocessedQueueNumber( ) const;
	//!	Queue/Unqueue buffers.
	_ubool QueueBuffers( _dword number, BufferSHI** buffers );
	_void UnqueueBuffers( _dword number, BufferSHI** buffers );

	//!	Set player state.
	_ubool SetPlayerState( SLuint32 state );
	SLuint32 GetPlayerState( );
};

}