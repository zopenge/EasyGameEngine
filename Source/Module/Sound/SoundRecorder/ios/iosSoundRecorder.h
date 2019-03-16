//! @file     iosSoundRecorder.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// iosSoundRecorder
//----------------------------------------------------------------------------

class iosSoundRecorder : public TSoundRecorder< ISoundRecorder >
{
private:

private:

public:
	iosSoundRecorder( );
	virtual ~iosSoundRecorder( );

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
// iosSoundRecorder Implementation
//----------------------------------------------------------------------------

}