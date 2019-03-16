//! @file     IGUIComponentAnimation.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGUIComponentAnimation
//----------------------------------------------------------------------------

class IGUIComponentAnimation : public IAnimationTrack< IGUIComponent, GUIAniKeyFrameInfo >
{
public:
	CLASS_NAME_DECL( IGUIComponentAnimation )

public:
	//! PauseInput
	//! @param		pause			The pause.
	//! @return		none.
	virtual _void PauseInput( _ubool pause ) PURE;
	//! ResumeInput
	//! @param		none.
	//! @return		none.
	virtual _void ResumeInput( ) PURE;

	//! ProcessDelayAnimation
	//! @param		delay			The delay time.
	//! @return		none.
	virtual _void ProcessDelayAnimation( _dword delay ) PURE;

	//!	Play animation.
	//! @param		delay			The delay time.
	//!	@param		res_name		The skeleton animation resource name.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool PlayAnimation( _dword delay, WStringPtr res_name, _ubool pause_input, _ubool hide_ui = _false ) PURE;
	virtual _ubool AppendAnimation( _dword delay, WStringPtr res_name, _ubool pause_input, _ubool hide_ui = _false ) PURE;
	virtual _ubool PlayAnimation( _dword delay, WStringPtr show_ani, _dword duration, WStringPtr hide_ani, _ubool pause_input, _ubool hide_ui = _true ) PURE;
	//!	Shake.
	//! @param		delay			The delay time.
	//!	@param		duration		The duration in milliseconds.
	//!	@param		random_range	The object's position will be affect by generating delta-position in [-random_range, random_range] bounds for each key frame.
	//!	@param		period			The period of duration in milliseconds.
	//!	@return		none.
	virtual _void Shake( _dword delay, _dword duration, _ubool pause_input, _float random_range, _dword period = 15 ) PURE;

	//!	Scale in (lerp to the original size).
	//! @param		delay			The delay time.
	//!	@param		duration		The duration in milliseconds.
	//!	@return		none.
	virtual _void ScaleIn( _dword delay, _dword duration, _ubool pause_input, _INTERPOLATOR_TYPE ipl = _INTERPOLATOR_LINEAR ) PURE;
	//!	Scale out (lerp to zero size).
	//! @param		delay			The delay time.
	//!	@param		duration		The duration in milliseconds.
	//!	@return		none.
	virtual _void ScaleOut( _dword delay, _dword duration, _ubool pause_input, _INTERPOLATOR_TYPE ipl = _INTERPOLATOR_LINEAR ) PURE;
	//!	Scale.
	//! @param		delay			The delay time.
	//!	@param		duration		The duration in milliseconds.
	//!	@param		scale			The scale factor.
	//!	@return		none.
	virtual _void ScaleTo( _dword delay, _dword duration, _ubool pause_input, const Vector2& scale, _INTERPOLATOR_TYPE ipl = _INTERPOLATOR_LINEAR ) PURE;
	//!	Move.
	//! @param		delay			The delay time.
	//!	@param		duration		The duration in milliseconds.
	//!	@param		offset			The move offset.
	//!	@return		none.
	virtual _void OffsetTo( _dword delay, _dword duration, _ubool pause_input, const Vector2& offset, _INTERPOLATOR_TYPE ipl = _INTERPOLATOR_LINEAR ) PURE;
	//!	Move.
	//! @param		delay			The delay time.
	//!	@param		duration		The duration in milliseconds.
	//!	@param		offset			The move offset.
	//!	@return		none.
	virtual _void MoveTo( _dword delay, _dword duration, _ubool pause_input, const Vector2& offset, _INTERPOLATOR_TYPE ipl = _INTERPOLATOR_LINEAR ) PURE;
	virtual _void MoveFrom( _dword delay, _dword duration, _ubool pause_input, const Vector2& offset, _INTERPOLATOR_TYPE ipl = _INTERPOLATOR_LINEAR ) PURE;

	virtual _void FlipX( _dword delay, _dword duration, _ubool clockwise, _ubool pause_input, _INTERPOLATOR_TYPE ipl = _INTERPOLATOR_LINEAR ) PURE;
	virtual _void FlipY( _dword delay, _dword duration, _ubool clockwise, _ubool pause_input, _INTERPOLATOR_TYPE ipl = _INTERPOLATOR_LINEAR ) PURE;

	virtual _void FlashScreenTransition( const Color& base_color, _dword delay, _dword duration, _ubool pause_input, _INTERPOLATOR_TYPE ipl = _INTERPOLATOR_LINEAR ) PURE;

	//!	Fade in.
	//!	@param		duration	The duration time in milliseconds.
	//!	@return		none.
	virtual _void FadeIn( _dword delay, _dword duration, _ubool pause_input, _INTERPOLATOR_TYPE ipl = _INTERPOLATOR_LINEAR ) PURE;
	//!	Fade out.
	//!	@param		duration	The duration time in milliseconds.
	//!	@return		none.
	virtual _void FadeOut( _dword delay, _dword duration, _ubool pause_input, _INTERPOLATOR_TYPE ipl = _INTERPOLATOR_LINEAR ) PURE;
};

}