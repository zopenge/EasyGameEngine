//! @file     androidSoundRecorder.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// androidSoundRecorder
//----------------------------------------------------------------------------

class androidSoundRecorder : public TSoundRecorder< ISoundRecorder >
{
private:
	IInvokerRef	mJNIObject;

private:

public:
	androidSoundRecorder( );
	virtual ~androidSoundRecorder( );

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
// androidSoundRecorder Implementation
//----------------------------------------------------------------------------

}