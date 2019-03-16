//! @file     winSoundRecorder.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// winSoundRecorderThread
//----------------------------------------------------------------------------

class winSoundRecorderThread : public Thread
{
private:

// Thread Interface
private:
	virtual _dword	OnRunThread( const QwordParameters2& parameters ) override;
	virtual _void	OnCloseThread( _dword exitcode, const QwordParameters2& parameters ) override;

public:
	winSoundRecorderThread( );
	virtual ~winSoundRecorderThread( );
};

//----------------------------------------------------------------------------
// winSoundRecorder
//----------------------------------------------------------------------------

class winSoundRecorder : public TSoundRecorder< ISoundRecorder >
{
private:
	_dword					mHeaderNumber;
	WAVEHDR*				mWavHeaders;

	HWAVEIN					mMICDevice;

	_dword					mSampleRate;
	_dword					mSampleBitSize;

	winSoundRecorderThread	mThread;

private:
	//!	Open MIC device.
	_ubool OpenMICDevice( _dword block_align_size, _dword channels, _dword sample_rate, _dword sample_bit_size );

	//!	Prepare record buffer.
	_ubool PrepareRecordBuffer( _dword block_align_size, _dword sample_rate, _dword sample_bit_size, _dword number );

	//!	Start record.
	_ubool StartRecord( );

public:
	winSoundRecorder( );
	virtual ~winSoundRecorder( );

public:
	EGE_GET_ACCESSOR( _dword, HeaderNumber )
	EGE_GET_ACCESSOR( _dword, SampleRate )
	EGE_GET_ACCESSOR( _dword, SampleBitSize )

public:
	//!	Initialize.
	_ubool Initialize( ISoundRecorderNotifier* notifier );

// ISoundRecorder Interface
public:
	virtual _ubool	Start( ) override;
	virtual _ubool	Start( _dword sample_rate, _dword sample_bit_size ) override;
	virtual _void	Stop( ) override;
};

//----------------------------------------------------------------------------
// winSoundRecorder Implementation
//----------------------------------------------------------------------------

}