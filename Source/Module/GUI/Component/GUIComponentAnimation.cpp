//! @file     GUIComponentAnimation.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGUI.h"

//----------------------------------------------------------------------------
// GUIComponentAnimation Implementation
//----------------------------------------------------------------------------

GUIComponentAnimation::GUIComponentAnimation( IGUIObject* gui_object ) : BaseClass( gui_object )
{
	mInputPausing	= _false;
	mIsAnimation	= _false;
	mWillHide		= _false;
}

GUIComponentAnimation::~GUIComponentAnimation( )
{
	ResumeInput( );
	OnEnd( );
}

_void GUIComponentAnimation::PauseInput( _ubool lock )
{
	ResumeInput( );

	mInputPausing = lock;
	if ( mInputPausing )
	{
		GetGUIModule( )->GetInputRecorder( )->Pause( );
	}
}

_void GUIComponentAnimation::ResumeInput( )
{
	if ( mInputPausing )
	{
		GetGUIModule( )->GetInputRecorder( )->Resume( );
		mInputPausing = _false;
	}
}

_void GUIComponentAnimation::OnStart( )
{
	OnEnd( );

	if ( mGUIObject->DoTick( ) )
	{
		mIsAnimation = _true;
		GetGUIModule( )->StartAnimation( mGUIObject );
	}
}

_void GUIComponentAnimation::OnEnd( )
{
	if ( mIsAnimation )
	{
		GetGUIModule( )->EndAnimation( mGUIObject );
		mIsAnimation = _false;
	}
}

_void GUIComponentAnimation::LerpPosition( _float alpha, const GUIAniKeyFrameInfo& cur_key_frame_info, const GUIAniKeyFrameInfo& next_key_frame_info )
{
	const IInterpolator* offset_x_ipl	= cur_key_frame_info.mInterpolators[ _GUI_INTERPOLATOR_OFFSET_X ];
	const IInterpolator* offset_y_ipl	= cur_key_frame_info.mInterpolators[ _GUI_INTERPOLATOR_OFFSET_Y ];

	Vector2 position;
	// Lerp position
	if ( offset_x_ipl != _null )
		position.x = Math::Lerp( cur_key_frame_info.mTransform.mPosition.x, next_key_frame_info.mTransform.mPosition.x, offset_x_ipl->Calculate( alpha ) );
	else
		position.x = Math::Lerp( cur_key_frame_info.mTransform.mPosition.x, next_key_frame_info.mTransform.mPosition.x, alpha );

	if ( offset_y_ipl != _null )
		position.y = Math::Lerp( cur_key_frame_info.mTransform.mPosition.y, next_key_frame_info.mTransform.mPosition.y, offset_y_ipl->Calculate( alpha ) );
	else
		position.y = Math::Lerp( cur_key_frame_info.mTransform.mPosition.y, next_key_frame_info.mTransform.mPosition.y, alpha );

	mGUIObject->GetComponentPosition( )->SetOffset( position );
}

_void GUIComponentAnimation::LerpScale( _float alpha, const GUIAniKeyFrameInfo& cur_key_frame_info, const GUIAniKeyFrameInfo& next_key_frame_info )
{
	const IInterpolator* scale_x_ipl	= cur_key_frame_info.mInterpolators[ _GUI_INTERPOLATOR_SCALE_X ];
	const IInterpolator* scale_y_ipl	= cur_key_frame_info.mInterpolators[ _GUI_INTERPOLATOR_SCALE_Y ];

	Vector2 scale;

	if ( scale_x_ipl != _null )
		scale.x = Math::Lerp( cur_key_frame_info.mTransform.mScale.x, next_key_frame_info.mTransform.mScale.x, scale_x_ipl->Calculate( alpha ) );
	else
		scale.x = Math::Lerp( cur_key_frame_info.mTransform.mScale.x, next_key_frame_info.mTransform.mScale.x, alpha );

	if ( scale_y_ipl != _null )
		scale.y = Math::Lerp( cur_key_frame_info.mTransform.mScale.y, next_key_frame_info.mTransform.mScale.y, scale_y_ipl->Calculate( alpha ) );
	else
		scale.y = Math::Lerp( cur_key_frame_info.mTransform.mScale.y, next_key_frame_info.mTransform.mScale.y, alpha );

	mGUIObject->GetComponentPosition( )->SetScale( scale );
}

_void GUIComponentAnimation::LerpRotation( _float alpha, const GUIAniKeyFrameInfo& cur_key_frame_info, const GUIAniKeyFrameInfo& next_key_frame_info )
{
	const IInterpolator* radian_ipl	= cur_key_frame_info.mInterpolators[ _GUI_INTERPOLATOR_RADIAN ];

	_float radian;
	if ( radian_ipl != _null )
		radian = Math::Lerp( cur_key_frame_info.mTransform.mRadian, next_key_frame_info.mTransform.mRadian, radian_ipl->Calculate( alpha ) );
	else
		radian = Math::Lerp( cur_key_frame_info.mTransform.mRadian, next_key_frame_info.mTransform.mRadian, alpha );

	mGUIObject->GetComponentPosition( )->SetRadian( radian );
}

_void GUIComponentAnimation::LerpColor( _float alpha, const GUIAniKeyFrameInfo& cur_key_frame_info, const GUIAniKeyFrameInfo& next_key_frame_info )
{
	const IInterpolator* color_ipl		= cur_key_frame_info.mInterpolators[ _GUI_INTERPOLATOR_COLOR ];

	Color color;
	if ( color_ipl != _null )
		color = Color::Lerp( cur_key_frame_info.mColor, next_key_frame_info.mColor, color_ipl->Calculate( alpha ) );
	else
		color = Color::Lerp( cur_key_frame_info.mColor, next_key_frame_info.mColor, alpha );

	mGUIObject->GetComponentColor( )->SetColor( color );
}

_void GUIComponentAnimation::Lerp3D( _float alpha, const GUIAniKeyFrameInfo& cur_key_frame_info, const GUIAniKeyFrameInfo& next_key_frame_info )
{
	const IInterpolator* rotation_ipl = cur_key_frame_info.mInterpolators[_GUI_INTERPOLATOR_3DROTATION];

	_float rotation_x, rotation_y;
	if ( rotation_ipl != _null )
	{
		_float ipl_alpha = rotation_ipl->Calculate( alpha );
		rotation_x = Math::Lerp( cur_key_frame_info.mRotationX, next_key_frame_info.mRotationX, ipl_alpha );
		rotation_y = Math::Lerp( cur_key_frame_info.mRotationY, next_key_frame_info.mRotationY, ipl_alpha );
	}
	else
	{
		rotation_x = Math::Lerp( cur_key_frame_info.mRotationX, next_key_frame_info.mRotationX, alpha );
		rotation_y = Math::Lerp( cur_key_frame_info.mRotationY, next_key_frame_info.mRotationY, alpha );
	}

	_float positionz = Math::Lerp( cur_key_frame_info.mPositionZ, next_key_frame_info.mPositionZ, alpha );
	
	mGUIObject->GetComponentPosition( )->SetAnimationXYRotation( rotation_x, rotation_y );
	mGUIObject->GetComponentPosition( )->SetOffsetZ( positionz );
}

_void GUIComponentAnimation::OnPlayed( )
{
	const KeyFrameInfoArray& key_frames = GetKeyFramesList( );
	if ( key_frames.Number( ) == 0 )
		return;

	const GUIAniKeyFrameInfo& head_key_frame = key_frames.GetHeadElement( ).mObject2;

	IGUIComponentPosition* component_position = mGUIObject->GetComponentPosition( );
	IGUIComponentColor* component_color = mGUIObject->GetComponentColor( );

	if ( head_key_frame.mAnimationMask.HasFlags( _GUI_ANIMATION_OFFSET ) )
		component_position->SetOffset( head_key_frame.mTransform.mPosition );

	if ( head_key_frame.mAnimationMask.HasFlags( _GUI_ANIMATION_SCALE ) )
		component_position->SetScale( head_key_frame.mTransform.mScale );

	if ( head_key_frame.mAnimationMask.HasFlags( _GUI_ANIMATION_ROTATION ) )
		component_position->SetRadian( head_key_frame.mTransform.mRadian );

	if ( head_key_frame.mAnimationMask.HasFlags( _GUI_ANIMATION_COLOR ) )
		component_color->SetColor( head_key_frame.mColor );

	if ( head_key_frame.mAnimationMask.HasFlags( _GUI_ANIMATION_3D ) )
	{
		component_position->SetAnimationXYRotation( head_key_frame.mRotationX, head_key_frame.mRotationY );
		component_position->SetOffsetZ( head_key_frame.mPositionZ );
	}		

	// Send event to hooker
	mGUIObject->HandleEvent( GUIEventAnimationPlayed( ), FlagsObject( _GUI_MESSAGE_DELIVER_CHILD ) );
}

_void GUIComponentAnimation::OnStopped( )
{
	OnEnd( );

	const KeyFrameInfoArray& key_frames = GetKeyFramesList( );
	if ( key_frames.Number( ) == 0 )
		return;

	const GUIAniKeyFrameInfo& tail_key_frame = key_frames.GetTailElement( ).mObject2;

	IGUIComponentPosition* component_position = mGUIObject->GetComponentPosition( );
	IGUIComponentColor* component_color = mGUIObject->GetComponentColor( );

	if ( tail_key_frame.mAnimationMask.HasFlags( _GUI_ANIMATION_OFFSET ) )
		component_position->SetOffset( tail_key_frame.mTransform.mPosition );

	if ( tail_key_frame.mAnimationMask.HasFlags( _GUI_ANIMATION_SCALE ) )
		component_position->SetScale( tail_key_frame.mTransform.mScale );

	if ( tail_key_frame.mAnimationMask.HasFlags( _GUI_ANIMATION_ROTATION ) )
		component_position->SetRadian( tail_key_frame.mTransform.mRadian );

	if ( tail_key_frame.mAnimationMask.HasFlags( _GUI_ANIMATION_COLOR ) )
		component_color->SetColor( tail_key_frame.mColor );

	if ( tail_key_frame.mAnimationMask.HasFlags( _GUI_ANIMATION_3D ) )
	{
		component_position->SetAnimationXYRotation( tail_key_frame.mRotationX, tail_key_frame.mRotationY );
		component_position->SetOffsetZ( tail_key_frame.mPositionZ );
	}

	// Send event to hooker
	mGUIObject->HandleEvent( GUIEventAnimationStopped( ), FlagsObject( _GUI_MESSAGE_DELIVER_CHILD ) );

	ResumeInput( );

	if ( mWillHide )
	{
		mGUIObject->Show( _false );
		mWillHide = _false;
	}
}

_void GUIComponentAnimation::OnPaused( )
{

}

_void GUIComponentAnimation::OnResumed( )
{

}

_void GUIComponentAnimation::OnReset( )
{

}

_void GUIComponentAnimation::OnTick( _time_t tick, _dword elapse )
{
	// Get alpha factor
	_float alpha = GetCurAlphaFactor( );

	// Get key frame info
	const GUIAniKeyFrameInfo* cur_key_frame_info	= GetCurrentKeyFrameInfo( );
	const GUIAniKeyFrameInfo* next_key_frame_info	= GetNextKeyFrameInfo( );
	if ( cur_key_frame_info == _null )
		return;

	if ( next_key_frame_info == _null )
		next_key_frame_info = cur_key_frame_info;

	// Lerp
	if ( cur_key_frame_info->mAnimationMask.HasFlags( _GUI_ANIMATION_OFFSET ) )
		LerpPosition( alpha, *cur_key_frame_info, *next_key_frame_info );
	if ( cur_key_frame_info->mAnimationMask.HasFlags( _GUI_ANIMATION_SCALE ) )
		LerpScale( alpha, *cur_key_frame_info, *next_key_frame_info );
	if ( cur_key_frame_info->mAnimationMask.HasFlags( _GUI_ANIMATION_ROTATION ) )
		LerpRotation( alpha, *cur_key_frame_info, *next_key_frame_info );
	if ( cur_key_frame_info->mAnimationMask.HasFlags( _GUI_ANIMATION_COLOR ) )
		LerpColor( alpha, *cur_key_frame_info, *next_key_frame_info );
	if ( cur_key_frame_info->mAnimationMask.HasFlags( _GUI_ANIMATION_3D ) )
		Lerp3D( alpha, *cur_key_frame_info, *next_key_frame_info );
}

_void GUIComponentAnimation::OnUpdateCurrentKeyFrameIndex( _dword prev_index )
{
	if ( mFlipEvent.mFlag && !mFlipEvent.mProcessed )
	{
		if ( this->mCurKeyFrameIndex >= this->GetKeyFramesList( ).Number( ) - 2 )
		{
			mFlipEvent.mProcessed = _true;
			GUIEventFlip gui_event;
			mGUIObject->HandleEvent( gui_event, FlagsObject( ) );
		}
	}

	if ( mFlashEvent.mFlag && !mFlashEvent.mProcessed )
	{
		if ( this->mCurKeyFrameIndex >= this->GetKeyFramesList( ).Number( ) - 2 )
		{
			mFlashEvent.mProcessed = _true;
			GUIEventAnimationFlash gui_event;
			mGUIObject->HandleEvent( gui_event, FlagsObject( ) );
		}
	}
}

_void GUIComponentAnimation::Tick( _time_t tick, _dword elapse )
{
	// prevent frame missing
	if ( elapse > 200 )
		elapse = 15;

	_TAnimationTrack::Tick( tick, elapse );
}

_ubool GUIComponentAnimation::HandleEvent( const EventBase& event, const FlagsObject& flags )
{
	switch ( event.mEventID )
	{
		case _GUI_EVENT_SHOW:
		{
			if ( GetAniStatus( ) != _ANIMATION_STATUS_STOPPED )
				OnStart( );
		}
		break;

		case _GUI_EVENT_HIDE:
		{
			if ( GetAniStatus( ) != _ANIMATION_STATUS_STOPPED )
				Stop( );
		}
		break;

		default:
			break;
	}

	return _false;
}

IObject* GUIComponentAnimation::CloneTo( _void* arguments ) const
{
	IGUIObject* gui_object = (IGUIObject*)arguments;
	EGE_ASSERT( gui_object != _null );

	GUIComponentAnimation* component = new GUIComponentAnimation( gui_object );
	component->CopyFrom( this );

	return component;
}

_ubool GUIComponentAnimation::Import( ISerializableNode* node )
{
	return _true;
}

_ubool GUIComponentAnimation::Export( ISerializableNode* node ) const
{
	return _true;
}

_ubool GUIComponentAnimation::IsResident( ) const
{
	return _true;
}

_void GUIComponentAnimation::ProcessDelayAnimation( _dword delay )
{
	if ( delay == 0 )
		return;

	IGUIComponentAnimation::KeyFrameInfoArray& keyframeArray = mKeyFrames;
	if ( keyframeArray.Number( ) == 0 )
		return;

	SetDuration( GetDuration( ) + delay );
	GUIAniKeyFrameInfo first_keyframe = keyframeArray[0].mObject2;
	for ( _dword i = 0; i < keyframeArray.Number( ); ++ i )
		keyframeArray[i].mObject1 += delay;

	AddKeyFrameInfo( 0, first_keyframe );
}

_ubool GUIComponentAnimation::PlayAnimation( _dword delay, WStringPtr show_ani, _dword duration, WStringPtr hide_ani, _ubool pause_input, _ubool hide_ui )
{
	if ( PlayAnimation( delay, show_ani, pause_input, hide_ui ) == _false )
		return _false;

	return AppendAnimation( duration, hide_ani, pause_input, hide_ui );
}

_ubool GUIComponentAnimation::AppendAnimation( _dword delay, WStringPtr res_name, _ubool pause_input, _ubool hide_ui )
{
	ClearUpdateFrameEvent( );

	if ( GetGUIModule( )->GetProcessor( )->OnAppendGUIObjectAnimation( mGUIObject, delay, res_name ) == _false )
		return _false;

	PauseInput( pause_input );

	OnStart( );

	mWillHide = hide_ui;

	return _true;
}

_ubool GUIComponentAnimation::PlayAnimation( _dword delay, WStringPtr res_name, _ubool pause_input, _ubool hide_ui )
{
	SetDuration( 0 );
	RemoveAllKeyFrames( );

	return AppendAnimation( delay, res_name, pause_input, hide_ui );
}

_void GUIComponentAnimation::Shake( _dword delay, _dword duration, _ubool pause_input, _float random_range, _dword period )
{
	EGE_ASSERT( period != 0 );
	ClearUpdateFrameEvent( );

	RemoveAllKeyFrames( );

	const Transform2D& transform = mGUIObject->GetComponentPosition( )->GetTransform2D( );

	duration = ( duration / period ) * period;
	if ( duration < period )
		duration = period;

	// Alpha current
	for ( _dword i = 0; i < duration; i += period )
	{
		GUIAniKeyFrameInfo key_frame;
		key_frame.mTransform = transform;
		key_frame.mTransform.mPosition.x += Random::Gen( -random_range, random_range );
		key_frame.mTransform.mPosition.y += Random::Gen( -random_range, random_range );
		key_frame.mAnimationMask = _GUI_ANIMATION_OFFSET;
		AddKeyFrameInfo( i, key_frame );
	}

	GUIAniKeyFrameInfo key_frame;
	key_frame.mTransform = transform;
	key_frame.mAnimationMask = _GUI_ANIMATION_OFFSET;
	AddKeyFrameInfo( duration, key_frame );

	// Set duration and reset animation 
	SetDuration( duration );
	Reset( );
	ProcessDelayAnimation( delay );
	Play( );
	PauseInput( pause_input );
	OnStart( );
}

_void GUIComponentAnimation::ScaleIn( _dword delay, _dword duration, _ubool pause_input, _INTERPOLATOR_TYPE ipl )
{
	ScaleTo( delay, duration, pause_input, Vector2::cIdentity, ipl );
}

_void GUIComponentAnimation::ScaleOut( _dword delay, _dword duration, _ubool pause_input, _INTERPOLATOR_TYPE ipl )
{
	ScaleTo( delay, duration, pause_input, Vector2::cOrigin, ipl );
}

_void GUIComponentAnimation::ScaleTo( _dword delay, _dword duration, _ubool pause_input, const Vector2& scale, _INTERPOLATOR_TYPE ipl )
{
	ClearUpdateFrameEvent( );
	RemoveAllKeyFrames( );

	const Transform2D& transform = mGUIObject->GetComponentPosition( )->GetTransform2D( );

	// The first key frame
	{
		GUIAniKeyFrameInfo key_frame;
		key_frame.mTransform = transform;
		key_frame.mAnimationMask = _GUI_ANIMATION_SCALE;
		IInterpolatorRef interpolator = GetInterfaceFactory( )->CreateInterpolator( ipl );
		key_frame.mInterpolators[_GUI_INTERPOLATOR_SCALE_X] = interpolator;
		key_frame.mInterpolators[_GUI_INTERPOLATOR_SCALE_Y] = interpolator;

		AddKeyFrameInfo( 0, key_frame );
	}

	// The second key frame
	{
		GUIAniKeyFrameInfo key_frame;
		key_frame.mTransform = transform;
		key_frame.mTransform.mScale = scale;
		key_frame.mAnimationMask = _GUI_ANIMATION_SCALE;
		AddKeyFrameInfo( duration, key_frame );
	}

	// Set duration and reset animation 
	SetDuration( duration );
	Reset( );
	ProcessDelayAnimation( delay );
	Play( );
	PauseInput( pause_input );
	OnStart( );
}

_void GUIComponentAnimation::OffsetTo( _dword delay, _dword duration, _ubool pause_input, const Vector2& offset, _INTERPOLATOR_TYPE ipl )
{
	ClearUpdateFrameEvent( );
	RemoveAllKeyFrames( );

	const Transform2D& transform = mGUIObject->GetComponentPosition( )->GetTransform2D( );

	// The first key frame
	{
		GUIAniKeyFrameInfo key_frame;
		key_frame.mTransform = transform;
		key_frame.mAnimationMask = _GUI_ANIMATION_OFFSET;
		IInterpolatorRef interpolator = GetInterfaceFactory( )->CreateInterpolator( ipl );
		key_frame.mInterpolators[_GUI_INTERPOLATOR_OFFSET_X] = interpolator;
		key_frame.mInterpolators[_GUI_INTERPOLATOR_OFFSET_Y] = interpolator;

		AddKeyFrameInfo( 0, key_frame );
	}

	// The second key frame
	{
		GUIAniKeyFrameInfo key_frame;
		key_frame.mTransform = transform;
		key_frame.mTransform.mPosition += offset;
		key_frame.mAnimationMask = _GUI_ANIMATION_OFFSET;
		AddKeyFrameInfo( duration, key_frame );
	}

	// Set duration and reset animation 
	SetDuration( duration );
	Reset( );
	ProcessDelayAnimation( delay );
	Play( );
	PauseInput( pause_input );
	OnStart( );
}

_void GUIComponentAnimation::MoveTo( _dword delay, _dword duration, _ubool pause_input, const Vector2& offset, _INTERPOLATOR_TYPE ipl )
{
	ClearUpdateFrameEvent( );
	RemoveAllKeyFrames( );

	const Transform2D& transform = mGUIObject->GetComponentPosition( )->GetTransform2D( );

	// The first key frame
	{
		GUIAniKeyFrameInfo key_frame;
		key_frame.mTransform = transform;
		key_frame.mAnimationMask = _GUI_ANIMATION_OFFSET;
		IInterpolatorRef interpolator = GetInterfaceFactory( )->CreateInterpolator( ipl );
		key_frame.mInterpolators[_GUI_INTERPOLATOR_OFFSET_X] = interpolator;
		key_frame.mInterpolators[_GUI_INTERPOLATOR_OFFSET_Y] = interpolator;

		AddKeyFrameInfo( 0, key_frame );
	}

	// The second key frame
	{
		GUIAniKeyFrameInfo key_frame;
		key_frame.mTransform = transform;
		key_frame.mTransform.mPosition = offset;
		key_frame.mAnimationMask = _GUI_ANIMATION_OFFSET;
		AddKeyFrameInfo( duration, key_frame );
	}

	// Set duration and reset animation 
	SetDuration( duration );
	Reset( );
	ProcessDelayAnimation( delay );
	Play( );
	PauseInput( pause_input );
	OnStart( );
}

_void GUIComponentAnimation::MoveFrom( _dword delay, _dword duration, _ubool pause_input, const Vector2& offset, _INTERPOLATOR_TYPE ipl )
{
	ClearUpdateFrameEvent( );
	RemoveAllKeyFrames( );

	const Transform2D& transform = mGUIObject->GetComponentPosition( )->GetTransform2D( );

	// The first key frame
	{
		GUIAniKeyFrameInfo key_frame;
		key_frame.mTransform = transform;
		key_frame.mTransform.mPosition = offset;
		key_frame.mAnimationMask = _GUI_ANIMATION_OFFSET;
		IInterpolatorRef interpolator = GetInterfaceFactory( )->CreateInterpolator( ipl );
		key_frame.mInterpolators[_GUI_INTERPOLATOR_OFFSET_X] = interpolator;
		key_frame.mInterpolators[_GUI_INTERPOLATOR_OFFSET_Y] = interpolator;

		AddKeyFrameInfo( 0, key_frame );
	}

	// The second key frame
	{
		GUIAniKeyFrameInfo key_frame;
		key_frame.mTransform = transform;
		key_frame.mAnimationMask = _GUI_ANIMATION_OFFSET;		

		AddKeyFrameInfo( duration, key_frame );
	}

	// Set duration and reset animation 
	SetDuration( duration );
	Reset( );
	ProcessDelayAnimation( delay );
	Play( );
	PauseInput( pause_input );
	OnStart( );
}

_void GUIComponentAnimation::FlipX( _dword delay, _dword duration, _ubool clockwise, _ubool pause_input, _INTERPOLATOR_TYPE ipl )
{
	InitFlipEvent( );
	RemoveAllKeyFrames( );

	// The first key frame
	{
		GUIAniKeyFrameInfo key_frame;
		key_frame.mRotationX = 0;
		key_frame.mRotationY = 0;
		key_frame.mAnimationMask = _GUI_ANIMATION_3D;
		IInterpolatorRef interpolator = GetInterfaceFactory( )->CreateInterpolator( ipl );
		key_frame.mInterpolators[_GUI_INTERPOLATOR_3DROTATION] = interpolator;

		AddKeyFrameInfo( 0, key_frame );
	}

	// The second key frame
	{
		GUIAniKeyFrameInfo key_frame;
		if ( clockwise )
			key_frame.mRotationX = - Math::cPi * 0.5f;
		else
			key_frame.mRotationX = Math::cPi * 0.5f;
		key_frame.mRotationY = 0;
		key_frame.mAnimationMask = _GUI_ANIMATION_3D;
		IInterpolatorRef interpolator = GetInterfaceFactory( )->CreateInterpolator( ipl );
		key_frame.mInterpolators[_GUI_INTERPOLATOR_3DROTATION] = interpolator;

		AddKeyFrameInfo( duration / 2, key_frame );
	}

	// The second key frame
	{
		GUIAniKeyFrameInfo key_frame;
		if ( clockwise )
			key_frame.mRotationX = Math::cPi * 0.5f;
		else
			key_frame.mRotationX = - Math::cPi * 0.5f;
		key_frame.mRotationY = 0;
		key_frame.mAnimationMask = _GUI_ANIMATION_3D;
		IInterpolatorRef interpolator = GetInterfaceFactory( )->CreateInterpolator( ipl );
		key_frame.mInterpolators[_GUI_INTERPOLATOR_3DROTATION] = interpolator;

		AddKeyFrameInfo( duration / 2, key_frame );
	}

	// The final key frame
	{
		GUIAniKeyFrameInfo key_frame;
		key_frame.mRotationX = 0;
		key_frame.mRotationY = 0;
		key_frame.mAnimationMask = _GUI_ANIMATION_3D;

		AddKeyFrameInfo( duration, key_frame );
	}

	// Set duration and reset animation 
	SetDuration( duration );
	Reset( );
	ProcessDelayAnimation( delay );
	Play( );
	PauseInput( pause_input );
	OnStart( );
}

_void GUIComponentAnimation::FlipY( _dword delay, _dword duration, _ubool clockwise, _ubool pause_input, _INTERPOLATOR_TYPE ipl )
{
	InitFlipEvent( );
	RemoveAllKeyFrames( );

	// The first key frame
	{
		GUIAniKeyFrameInfo key_frame;
		key_frame.mRotationY = 0;
		key_frame.mRotationX = 0;
		key_frame.mAnimationMask = _GUI_ANIMATION_3D;
		IInterpolatorRef interpolator = GetInterfaceFactory( )->CreateInterpolator( ipl );
		key_frame.mInterpolators[_GUI_INTERPOLATOR_3DROTATION] = interpolator;

		AddKeyFrameInfo( 0, key_frame );
	}

	// The second key frame
	{
		GUIAniKeyFrameInfo key_frame;
		if ( clockwise )
			key_frame.mRotationY = - Math::cPi * 0.5f;
		else
			key_frame.mRotationY = Math::cPi * 0.5f;
		key_frame.mRotationX = 0;
		key_frame.mAnimationMask = _GUI_ANIMATION_3D;
		IInterpolatorRef interpolator = GetInterfaceFactory( )->CreateInterpolator( ipl );
		key_frame.mInterpolators[_GUI_INTERPOLATOR_3DROTATION] = interpolator;

		AddKeyFrameInfo( duration / 2, key_frame );
	}

	// The second key frame
	{
		GUIAniKeyFrameInfo key_frame;
		if ( clockwise )
			key_frame.mRotationY = Math::cPi * 0.5f;
		else
			key_frame.mRotationY = - Math::cPi * 0.5f;
		key_frame.mRotationX = 0;
		key_frame.mAnimationMask = _GUI_ANIMATION_3D;
		IInterpolatorRef interpolator = GetInterfaceFactory( )->CreateInterpolator( ipl );
		key_frame.mInterpolators[_GUI_INTERPOLATOR_3DROTATION] = interpolator;

		AddKeyFrameInfo( duration / 2 + 1, key_frame );
	}

	// The final key frame
	{
		GUIAniKeyFrameInfo key_frame;
		key_frame.mRotationY = 0;
		key_frame.mRotationX = 0;
		key_frame.mAnimationMask = _GUI_ANIMATION_3D;

		AddKeyFrameInfo( duration, key_frame );
	}

	// Set duration and reset animation 
	SetDuration( duration );
	Reset( );
	ProcessDelayAnimation( delay );
	Play( );
	PauseInput( pause_input );
	OnStart( );
}

_void GUIComponentAnimation::FlashScreenTransition( const Color& base_color, _dword delay, _dword duration, _ubool pause_input, _INTERPOLATOR_TYPE ipl )
{
	InitFlashEvent( );
	RemoveAllKeyFrames( );

	// The first key frame
	{
		GUIAniKeyFrameInfo key_frame;
		key_frame.mColor = Color( base_color.Red( ), base_color.Green( ), base_color.Blue( ), 0.0f );
		key_frame.mAnimationMask = _GUI_ANIMATION_COLOR;
		IInterpolatorRef interpolator = GetInterfaceFactory( )->CreateInterpolator( ipl );
		key_frame.mInterpolators[_GUI_INTERPOLATOR_COLOR] = interpolator;

		AddKeyFrameInfo( 0, key_frame );
	}

	// The second key frame
	{
		GUIAniKeyFrameInfo key_frame;
		key_frame.mColor = base_color;
		key_frame.mAnimationMask = _GUI_ANIMATION_COLOR;
		IInterpolatorRef interpolator = GetInterfaceFactory( )->CreateInterpolator( ipl );
		key_frame.mInterpolators[_GUI_INTERPOLATOR_COLOR] = interpolator;

		AddKeyFrameInfo( duration / 2, key_frame );
	}

	// The final key frame
	{
		GUIAniKeyFrameInfo key_frame;
		key_frame.mColor = Color( base_color.Red( ), base_color.Green( ), base_color.Blue( ), 0.0f );
		key_frame.mAnimationMask = _GUI_ANIMATION_COLOR;

		AddKeyFrameInfo( duration, key_frame );
	}

	// Set duration and reset animation 
	SetDuration( duration );
	Reset( );
	ProcessDelayAnimation( delay );
	Play( );
	PauseInput( pause_input );
	OnStart( );
}


_void GUIComponentAnimation::FadeIn( _dword delay, _dword duration, _ubool pause_input, _INTERPOLATOR_TYPE ipl )
{
	ClearUpdateFrameEvent( );
	RemoveAllKeyFrames( );

	// Alpha current
	GUIAniKeyFrameInfo cur_frame;
	cur_frame.mColor = mGUIObject->GetComponentColor( )->GetColor( );
	cur_frame.mColor.a = 0;
	cur_frame.mAnimationMask = _GUI_ANIMATION_COLOR;
	cur_frame.mInterpolators[_GUI_INTERPOLATOR_COLOR] = GetInterfaceFactory( )->CreateInterpolator( ipl );
	AddKeyFrameInfo( 0, cur_frame );

	// Alpha 255
	cur_frame.mColor.a = 255;
	AddKeyFrameInfo( duration, cur_frame );

	// Set duration and reset animation 
	SetDuration( duration );
	Reset( );
	ProcessDelayAnimation( delay );
	Play( );
	PauseInput( pause_input );
	OnStart( );
}

_void GUIComponentAnimation::FadeOut( _dword delay, _dword duration, _ubool pause_input, _INTERPOLATOR_TYPE ipl )
{
	ClearUpdateFrameEvent( );
	IGUIComponentAnimation* animation = mGUIObject->GetComponentAnimation( );
	EGE_ASSERT( animation != _null );
	RemoveAllKeyFrames( );

	// Alpha current
	GUIAniKeyFrameInfo cur_frame;
	cur_frame.mColor = mGUIObject->GetComponentColor( )->GetColor( );
	cur_frame.mColor.a = 255;
	cur_frame.mAnimationMask = _GUI_ANIMATION_COLOR;
	cur_frame.mInterpolators[_GUI_INTERPOLATOR_COLOR] = GetInterfaceFactory( )->CreateInterpolator( ipl );
	AddKeyFrameInfo( 0, cur_frame );

	// Alpha 0
	cur_frame.mColor.a = 0;
	AddKeyFrameInfo( duration, cur_frame );

	// Set duration and reset animation 
	SetDuration( duration );
	Reset( );
	ProcessDelayAnimation( delay );
	Play( );
	PauseInput( pause_input );
	OnStart( );
}


_void GUIComponentAnimation::InitFlipEvent( )
{
	mFlashEvent.Clear( );
	mFlipEvent.Init( );
}

_void GUIComponentAnimation::InitFlashEvent( )
{
	mFlashEvent.Init( );
	mFlipEvent.Clear( );
}

_void GUIComponentAnimation::ClearUpdateFrameEvent( )
{
	mFlipEvent.Clear( );
	mFlashEvent.Clear( );
}