//! @file     GUIComponentAnimation.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GUIComponentAnimation
//----------------------------------------------------------------------------

class GUIComponentAnimation : public TGUIComponent< TAnimationTrack< INTERFACE_OBJECT_IMPL( IGUIComponentAnimation ), GUIAniKeyFrameInfo > >
{
public:
	RTTI_CLASS_WITH_ARGUMENTS_DECL( GUIComponentAnimation, IGUIComponentAnimation, IGUIObject* )

public:
	_GUICOMPONENT_ENABLE_TICK( )
	_GUICOMPONENT_ENABLE_HANDLE_EVENT( )

private:
	typedef TAnimationTrack< INTERFACE_OBJECT_IMPL( IGUIComponentAnimation ), GUIAniKeyFrameInfo > _TAnimationTrack;
	typedef TGUIComponent< _TAnimationTrack > BaseClass;

	struct UpdateFrameEventInfo
	{
		_ubool	mFlag;
		_ubool	mProcessed;
		UpdateFrameEventInfo( )
		{
			mFlag = _false;
			mProcessed = _false;
		}
		_void Clear( )
		{
			mFlag = _false;
			mProcessed = _false;
		}
		_void Init( )
		{
			mFlag = _true;
			mProcessed = _false;
		}
	};

private:
	_ubool	mInputPausing;
	_ubool	mIsAnimation;
	_ubool	mWillHide;
	UpdateFrameEventInfo	mFlipEvent;
	UpdateFrameEventInfo	mFlashEvent;

private:
	//!	Lerp position/scale/rotation/color.
	_void LerpPosition( _float alpha, const GUIAniKeyFrameInfo& cur_key_frame_info, const GUIAniKeyFrameInfo& next_key_frame_info );
	_void LerpScale( _float alpha, const GUIAniKeyFrameInfo& cur_key_frame_info, const GUIAniKeyFrameInfo& next_key_frame_info );
	_void LerpRotation( _float alpha, const GUIAniKeyFrameInfo& cur_key_frame_info, const GUIAniKeyFrameInfo& next_key_frame_info );
	_void LerpColor( _float alpha, const GUIAniKeyFrameInfo& cur_key_frame_info, const GUIAniKeyFrameInfo& next_key_frame_info );
	_void Lerp3D( _float alpha, const GUIAniKeyFrameInfo& cur_key_frame_info, const GUIAniKeyFrameInfo& next_key_frame_info );

	_void	OnStart( );
	_void	OnEnd( );
	_void	InitFlipEvent( );
	_void	InitFlashEvent( );
	_void	ClearUpdateFrameEvent( );
// TAnimationController Interface
private:
	virtual _void	OnPlayed( ) override;
	virtual _void	OnStopped( ) override;
	virtual _void	OnPaused( ) override;
	virtual _void	OnResumed( ) override;
	virtual _void	OnReset( ) override;
	virtual _void	OnTick( _time_t tick, _dword elapse ) override;
	virtual _void	OnUpdateCurrentKeyFrameIndex( _dword prev_index ) override;

public:
	GUIComponentAnimation( IGUIObject* gui_object );
	virtual ~GUIComponentAnimation( );

// IObject Interface
public:
	virtual IObject*	CloneTo( _void* arguments ) const override;

	virtual _void		Tick( _time_t tick, _dword elapse ) override;

// ISerializable Interface
public:
	virtual _ubool		Import( ISerializableNode* node ) override;
	virtual _ubool		Export( ISerializableNode* node ) const override;

// IGUIComponent Interface
public:
	virtual _ubool		IsResident( ) const override;

	virtual _ubool		HandleEvent( const EventBase& event, const FlagsObject& flags ) override;

// IGUIComponentAnimation Interface
public:
	virtual _void		PauseInput( _ubool pause ) override;
	virtual _void		ResumeInput( ) override;

	virtual _void		ProcessDelayAnimation( _dword delay ) override;

	virtual _ubool		PlayAnimation( _dword delay, WStringPtr res_name, _ubool pause_input, _ubool hide_ui = _false ) override;
	virtual _ubool		AppendAnimation( _dword delay, WStringPtr res_name, _ubool pause_input, _ubool hide_ui = _false ) override;
	virtual _ubool		PlayAnimation( _dword delay, WStringPtr show_ani, _dword duration, WStringPtr hide_ani, _ubool pause_input, _ubool hide_ui = _true ) override;

	virtual _void		Shake( _dword delay, _dword duration, _ubool pause_input, _float random_range, _dword period = 15 ) override;

	virtual _void		ScaleIn( _dword delay, _dword duration, _ubool pause_input, _INTERPOLATOR_TYPE ipl = _INTERPOLATOR_LINEAR ) override;
	virtual _void		ScaleOut( _dword delay, _dword duration, _ubool pause_input, _INTERPOLATOR_TYPE ipl = _INTERPOLATOR_LINEAR ) override;
	virtual _void		ScaleTo( _dword delay, _dword duration, _ubool pause_input, const Vector2& scale, _INTERPOLATOR_TYPE ipl = _INTERPOLATOR_LINEAR ) override;

	virtual _void		OffsetTo( _dword delay, _dword duration, _ubool pause_input, const Vector2& offset, _INTERPOLATOR_TYPE ipl = _INTERPOLATOR_LINEAR ) override;
	virtual _void		MoveTo( _dword delay, _dword duration, _ubool pause_input, const Vector2& offset, _INTERPOLATOR_TYPE ipl = _INTERPOLATOR_LINEAR ) override;
	virtual _void		MoveFrom( _dword delay, _dword duration, _ubool pause_input, const Vector2& offset, _INTERPOLATOR_TYPE ipl = _INTERPOLATOR_LINEAR ) override;

	virtual _void		FlipX( _dword delay, _dword duration, _ubool clockwise, _ubool pause_input, _INTERPOLATOR_TYPE ipl = _INTERPOLATOR_LINEAR ) override;
	virtual _void		FlipY( _dword delay, _dword duration, _ubool clockwise, _ubool pause_input, _INTERPOLATOR_TYPE ipl = _INTERPOLATOR_LINEAR ) override;
	virtual _void		FlashScreenTransition( const Color& base_color, _dword delay, _dword duration, _ubool pause_input, _INTERPOLATOR_TYPE ipl = _INTERPOLATOR_LINEAR ) override;
	virtual _void		FadeIn( _dword delay, _dword duration, _ubool pause_input, _INTERPOLATOR_TYPE ipl = _INTERPOLATOR_LINEAR ) override;
	virtual _void		FadeOut( _dword delay, _dword duration, _ubool pause_input, _INTERPOLATOR_TYPE ipl = _INTERPOLATOR_LINEAR ) override;
};

//----------------------------------------------------------------------------
// GUIComponentAnimation Implementation
//----------------------------------------------------------------------------

}