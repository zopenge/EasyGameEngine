//! @file     winSoundRecorder.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGESound.h"

//----------------------------------------------------------------------------
// winSoundRecorderThread Implementation
//----------------------------------------------------------------------------

winSoundRecorderThread::winSoundRecorderThread( )
{
}

winSoundRecorderThread::~winSoundRecorderThread( )
{
}

_dword winSoundRecorderThread::OnRunThread( const QwordParameters2& parameters )
{
	winSoundRecorder* recorder = (winSoundRecorder*) parameters[0];
	EGE_ASSERT( recorder != _null );

	// Trigger the message queue generator
	MSG msg;
	PeekMessage( &msg, _null, WM_USER, WM_USER, PM_NOREMOVE );

	// Start to record
	while ( _true )
	{
		BOOL ret = GetMessage( &msg, _null, 0, 0 );
		if ( ret == 0 )
		{
			recorder->GetNotifier( )->OnStop( );
			break;
		}

		if ( ret == -1 )
			continue;

		switch ( msg.message ) 
		{
			case MM_WIM_OPEN:
			{
				recorder->GetNotifier( )->OnStart( recorder->GetSampleRate( ), recorder->GetSampleBitSize( ) );
			}
			break;

			case MM_WIM_CLOSE: 
			{
				recorder->GetNotifier( )->OnStop( );

				PostQuitMessage( 0 );
			}
			break;

			case MM_WIM_DATA:
			{
				HWAVEIN	 whdl = (HWAVEIN) msg.wParam;
				WAVEHDR* buf  = (WAVEHDR*) msg.lParam;

				// Check buffer range
				if ( buf->dwUser > recorder->GetHeaderNumber( ) )
					break;

				// Feedback the audio data
				recorder->GetNotifier( )->OnRecv( buf->dwBytesRecorded, (const _byte*)buf->lpData );

				// Check whether need to feedback device
				_SOUND_RECORDER_STATE state = recorder->GetState( );
				if ( state == _SOUND_RECORDER_RECORDING )
				{
					// After copied, put it into the queue of driver again.
					waveInAddBuffer( whdl, buf, sizeof( WAVEHDR ) );
				}
				else
				{
					buf->dwUser = 0;
				}
			}
			break;
	
			default:
				break;
		}
	}

	return EXIT_SUCCESS;
}

_void winSoundRecorderThread::OnCloseThread( _dword exitcode, const QwordParameters2& parameters )
{

}

//----------------------------------------------------------------------------
// winSoundRecorder Implementation
//----------------------------------------------------------------------------

winSoundRecorder::winSoundRecorder( )
{
	mHeaderNumber	= 0;
	mWavHeaders		= _null;

	mMICDevice		= _null;

	mSampleRate		= 0;
	mSampleBitSize	= 0;
}

winSoundRecorder::~winSoundRecorder( )
{
	Stop( );

	// Free header buffer
	if ( mWavHeaders != _null )
	{
		for ( _dword i = 0; i < mHeaderNumber; i ++ ) 
		{
			WAVEHDR* header = &mWavHeaders[i];
			EGE_ASSERT( header != _null );

			if ( header->lpData != _null )
			{
				if ( WHDR_PREPARED & header->dwFlags )
					waveInUnprepareHeader( mMICDevice, mWavHeaders + i, sizeof( WAVEHDR ) );

				free( header->lpData );
			}
		}

		EGE_DELETE_ARRAY( mWavHeaders );
	}

	// Close MIC device
	if ( mMICDevice != _null )
		waveInClose( mMICDevice );
}

_ubool winSoundRecorder::OpenMICDevice( _dword block_align_size, _dword channels, _dword sample_rate, _dword sample_bit_size )
{
	if ( sample_rate == 0 || sample_bit_size == 0 )
		return _false;

	// Check MIC device number
	if ( ::waveInGetNumDevs( ) == 0 )
		return _false;

	// Initialize wave format to receive
	WAVEFORMATEX wavfmt = 
	{
		WAVE_FORMAT_PCM,
		(WORD)channels,
		sample_rate,
		sample_rate * (sample_bit_size >> 3),
		(WORD)block_align_size,
		(WORD)sample_bit_size,
		(WORD)sizeof( WAVEFORMATEX )
	};

	// Open MIC device
	MMRESULT ret = ::waveInOpen( (LPHWAVEIN)&mMICDevice, 0, &wavfmt, (DWORD_PTR)mThread.GetThreadID( ), (DWORD_PTR)0, CALLBACK_THREAD );
	if ( ret != MMSYSERR_NOERROR )
		return _false;

	return _true;
}

_ubool winSoundRecorder::PrepareRecordBuffer( _dword block_align_size, _dword sample_rate, _dword sample_bit_size, _dword number )
{
	if ( number < 2 )
		return _false;

	// Get the buffer size (I don't know why div 50 ...)
	const _dword buf_size = block_align_size * ( sample_rate / 50 ) * 10; // 200ms
	if ( buf_size == 0 )
		return _false;

	// Save the header number
	mHeaderNumber = number;

	// Create WAV header buffer
	mWavHeaders = new WAVEHDR[mHeaderNumber];
	EGE_MEM_SET( mWavHeaders, 0, sizeof( WAVEHDR ) * mHeaderNumber );

	// Initialize WAV header buffers
	for ( _dword i = 0; i < mHeaderNumber; i ++ )
	{
		WAVEHDR* header = &mWavHeaders[i];
		EGE_ASSERT( header != _null );

		header->lpData = (LPSTR) malloc( buf_size );
		if ( header->lpData == _null )
			return _false;

		header->dwBufferLength	= buf_size;
		header->dwFlags			= 0;
		header->dwUser			= i + 1; // The index + 1 of this block, 0 indicates no-usage

		MMRESULT ret = waveInPrepareHeader( mMICDevice, header, sizeof( WAVEHDR ) );
		if ( ret != MMSYSERR_NOERROR )
			return _false;
	}

	return _true;
}

_ubool winSoundRecorder::StartRecord( )
{
	for ( _dword i = 0; i < mHeaderNumber; i ++ )
	{
		WAVEHDR* header = &mWavHeaders[i];
		EGE_ASSERT( header != _null );

		if ( header->dwFlags & WHDR_INQUEUE )
			continue;

		// The index + 1 of this block, 0 indicates no-usage
		header->dwUser = i + 1; 

		// Add WAV buffer
		MMRESULT ret = waveInAddBuffer( mMICDevice, header, sizeof( WAVEHDR ) );
		if ( ret != MMSYSERR_NOERROR )
		{
			waveInReset( mMICDevice );
			return _false;
		}
	}

	MMRESULT ret = waveInStart( mMICDevice );
	if ( ret != MMSYSERR_NOERROR )
	{
		waveInReset( mMICDevice );
		return _false;
	}

	return _true;
}

_ubool winSoundRecorder::Initialize( ISoundRecorderNotifier* notifier )
{
	if ( notifier == _null )
		return _false;

	mNotifier = notifier;

	return _true;
}

_ubool winSoundRecorder::Start( )
{
	return Start( 16000, 16 );
}

_ubool winSoundRecorder::Start( _dword sample_rate, _dword sample_bit_size )
{
	mSampleRate		= sample_rate;
	mSampleBitSize	= sample_bit_size;

	// Create thread
	if ( mThread.Create( 0, _false, L"SoundRecorderThread", QwordParameters2( (_qword)this, _null ) ) == _false )
		return _false;

	// The block align of wave format
	const _dword block_align_size = sample_bit_size / 8;

	// Open MIC device
	if ( OpenMICDevice( block_align_size, 1, sample_rate, sample_bit_size ) == _false )
		return _false;
	
	// The header number
	const _dword header_number = 4;

	// Prepare the record buffer
	if ( PrepareRecordBuffer( block_align_size, sample_rate, sample_bit_size, header_number ) == _false )
		return _false;

	// Start to record
	if ( StartRecord( ) == _false )
		return _false;

	mState = _SOUND_RECORDER_RECORDING;

	return _true;
}

_void winSoundRecorder::Stop( )
{
	// Stopping
	mState = _SOUND_RECORDER_STOPPING;

	// Close thread
	::PostThreadMessage( (DWORD)mThread.GetThreadID( ), WM_QUIT, 0, 0 );

	// Stop recording
	waveInReset( mMICDevice );

	// Wait thread close
	mThread.Close( );

	// Stopped
	mState = _SOUND_RECORDER_STOPPED;
}
