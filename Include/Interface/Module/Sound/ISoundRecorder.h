//! @file     ISoundRecorder.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ISoundRecorderNotifier
//----------------------------------------------------------------------------

class ISoundRecorderNotifier : public IObject
{
public:
	//!	When start to record.
	//!	@param		none.
	//! @return		none.
	virtual _void OnStart( _dword sample_rate, _dword sample_bit_size ) PURE;
	//!	When receive sound data.
	//!	@param		size	The buffer size.
	//!	@param		buffer	The buffer data.
	//! @return		none.
	virtual _void OnRecv( _dword size, const _byte* buffer ) PURE;
	//!	When stop to record.
	//!	@param		none.
	//! @return		none.
	virtual _void OnStop( ) PURE;
};

//----------------------------------------------------------------------------
// ISoundRecorder
//----------------------------------------------------------------------------

class ISoundRecorder : public IObject
{
public:
	//!	Get the notifier.
	//!	@param		none.
	//!	@return		The notifier.
	virtual ISoundRecorderNotifier* GetNotifier( ) PURE;

	//!	Get the state.
	//!	@param		none.
	//!	@return		The state.
	virtual _SOUND_RECORDER_STATE GetState( ) const PURE;

	//!	Start.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Start( ) PURE;
	//!	Start.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Start( _dword sample_rate, _dword sample_bit_size ) PURE;
	//!	Stop.
	//!	@param		none.
	//!	@return		none.
	virtual _void Stop( ) PURE;
};

}