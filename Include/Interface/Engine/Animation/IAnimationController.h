//! @file     IAnimationController.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IAnimationController
//----------------------------------------------------------------------------

template< typename Type >
class IAnimationController : public Type
{
public:
	//!	Get the current frame time in milliseconds.
	//!	@param		none.
	//!	@return		The current frame time in milliseconds.
	virtual _dword GetCurrentFrameTime( ) const PURE;
	//!	Set the current frame time in milliseconds.
	//!	@param		time		The current frame time in milliseconds.
	//!	@return		none.
	virtual _void SetCurrentFrameTime( _dword time ) PURE;

	//!	Get the current frame number.
	//!	@param		none.
	//!	@return		The current frame number.
	virtual _dword GetCurrentFrameNumber( ) const PURE;
	//!	Set the current frame number.
	//!	@param		time		The current frame number.
	//!	@return		none.
	virtual _void SetCurrentFrameNumber( _dword number ) PURE;

	//!	Get the status.
	//!	@param		none.
	//!	@return		The animation status.
	virtual _ANIMATION_STATUS GetAniStatus( ) const PURE;
	//!	Get the last tickcount.
	//!	@param		none.
	//!	@return		The last tickcount.
	virtual _dword GetLastTickcount( ) const PURE;

	//!	Get the direction.
	//!	@param		none.
	//!	@return		The animation direction.
	virtual _ANIMATION_DIRECTION GetAniDirection( ) const PURE;
	//!	Set the direction.
	//!	@param		direction	The animation direction.
	//!	@return		none.
	virtual _void SetAniDirection( _ANIMATION_DIRECTION direction ) PURE;

	//!	Get the mode.
	//!	@param		none.
	//!	@return		The animation mode.
	virtual _ANIMATION_MODE GetAniMode( ) const PURE;
	//!	Set the mode.
	//!	@param		mode		The animation mode.
	//!	@return		none.
	virtual _void SetAniMode( _ANIMATION_MODE mode ) PURE;

	//!	Get the duration in milliseconds.
	//!	@param		none.
	//!	@return		The duration in milliseconds.
	virtual _dword GetDuration( ) const PURE;
	//!	Set the duration in milliseconds.
	//!	@param		duration	The duration in milliseconds.
	//!	@return		none.
	virtual _void SetDuration( _dword duration ) PURE;
	//!	Get the total frames number.
	//!	@param		none.
	//!	@return		The total frames number.
	virtual _dword GetTotalFramesNumber( ) const PURE;
	//!	Set the total frames number.
	//!	@param		frames_number	The total frames number.
	//!	@return		none.
	virtual _void SetTotalFramesNumber( _dword frames_number ) PURE;

	//!	Get the FPS.
	//!	@param		none.
	//!	@return		The FPS.
	virtual _float GetFPS( ) const PURE;
	//!	Set the FPS.
	//!	@param		fps		The FPS.
	//!	@return		none.
	virtual _void SetFPS( _float fps ) PURE;

	//!	Get the interval in milliseconds.
	//!	@param		none.
	//!	@return		The interval in milliseconds.
	virtual _dword GetInterval( ) const PURE;
	//!	Set the interval in milliseconds.
	//!	@param		interval	The interval in milliseconds.
	//!	@return		none.
	virtual _void SetInterval( _dword interval ) PURE;

	//!	Play.
	//!	@param		none.
	//!	@return		none.
	virtual _void Play( ) PURE;
	//!	Stop.
	//!	@param		none.
	//!	@return		none.
	virtual _void Stop( ) PURE;
	//!	Pause.
	//!	@param		none.
	//!	@return		none.
	virtual _void Pause( ) PURE;
	//!	Resume.
	//!	@param		none.
	//!	@return		none.
	virtual _void Resume( ) PURE;
	//!	Reset.
	//!	@param		none.
	//!	@return		none.
	virtual _void Reset( ) PURE;
};

}