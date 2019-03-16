//! @file     GUIEvents.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2010 LiCode's Union.

#pragma once

EGE_BEGIN_NAMESPACE_2( EGE, GUIEvents )

DECLARE_COUNTER;

//----------------------------------------------------------------------------
// GUIEvents
//----------------------------------------------------------------------------

// GUI event hooker register
#define EGE_GUI_EVENT_HOOKER_REGISTER( object, event_id, func ) \
	object->GetComponentEventHooker( )->RegisterHookerFunc( event_id, GUIEventHooker( func, this ), QwordParameters2::cNull )
#define EGE_GUI_EVENT_HOOKER_REGISTER_WITH_PARS_1( object, event_id, func, p1 ) \
	object->GetComponentEventHooker( )->RegisterHookerFunc( event_id, GUIEventHooker( func, this ), QwordParameters2( (_qword) p1, _null ) )
#define EGE_GUI_EVENT_HOOKER_REGISTER_WITH_PARS_2( object, event_id, func, p1, p2 ) \
	object->GetComponentEventHooker( )->RegisterHookerFunc( event_id, GUIEventHooker( func, this ), QwordParameters2( (_qword) p1, (_qword) p2 ) )

// GUI
#define EGE_GUI_EVENT_OFFSET 1000
#define EGE_GUI_EVENT_BEGIN( struct_name, id_value ) \
	EGE_USER_EVENT_BEGIN( struct_name, id_value, EGE_GUI_EVENT_OFFSET )

//----------------------------------------------------------------------------
// GUI Outside Usage Event Classes 
//----------------------------------------------------------------------------

//!	The GUI control state changed event
EGE_GUI_EVENT_BEGIN( GUIEventStateChanged, _GUI_EVENT_STATE_CHANGED )
	//!	The previous state
	_GUI_OBJECT_STATE	mPrevState;
	EGE_EVENT_CLONE_1( GUIEventStateChanged, mPrevState )
EGE_EVENT_END( )

//!	The GUI control update event
EGE_GUI_EVENT_BEGIN( GUIEventUpdate, _GUI_EVENT_UPDATE )
	//!	The elapsed time in milliseconds.
	_dword	mElapse;
	EGE_EVENT_CLONE_1( GUIEventUpdate, mElapse )
EGE_EVENT_END( )

//!	The GUI control begin to render event
EGE_GUI_EVENT_BEGIN( GUIEventRenderBegin, _GUI_EVENT_RENDER_BEGIN )
	//!	The GUI object world transform.
	Matrix3	mWorldTransform;
	//!	The GUI object color
	Color	mColor;
	//!	The GUI object clip rect
	RectF	mClipRect;
	EGE_EVENT_CLONE_3( GUIEventRenderBegin, mWorldTransform, mColor, mClipRect )
EGE_EVENT_END( )

//!	The GUI control end to render event
EGE_GUI_EVENT_BEGIN( GUIEventRenderEnd, _GUI_EVENT_RENDER_END )
	//!	The GUI object world transform.
	Matrix3	mWorldTransform;
	Color	mColor;
	EGE_EVENT_CLONE_2( GUIEventRenderEnd, mWorldTransform, mColor )
EGE_EVENT_END( )

EGE_GUI_EVENT_BEGIN( GUIEventAfterRender, _GUI_EVENT_AFTER_RENDER )
	//!	The GUI object world transform.
	Matrix3	mWorldTransform;
	Color	mColor;
	EGE_EVENT_CLONE_2( GUIEventAfterRender, mWorldTransform, mColor )
EGE_EVENT_END( )

//!	The GUI control state changed event
EGE_GUI_EVENT_BEGIN( GUIEventFocusOn, _GUI_EVENT_FOCUS_ON )
	EGE_EVENT_CLONE_0( GUIEventFocusOn )
EGE_EVENT_END( )

//!	The GUI control state changed event
EGE_GUI_EVENT_BEGIN( GUIEventFocusOff, _GUI_EVENT_FOCUS_OFF )
	EGE_EVENT_CLONE_0( GUIEventFocusOff )
EGE_EVENT_END( )

//!	The GUI control show event
EGE_GUI_EVENT_BEGIN( GUIEventShow, _GUI_EVENT_SHOW )
	EGE_EVENT_CLONE_0( GUIEventShow )
EGE_EVENT_END( )

//!	The GUI control hide event
EGE_GUI_EVENT_BEGIN( GUIEventHide, _GUI_EVENT_HIDE )
	EGE_EVENT_CLONE_0( GUIEventHide )
EGE_EVENT_END( )

EGE_GUI_EVENT_BEGIN( GUIEventAnimationPlayed, _GUI_EVENT_ANIMATION_PLAYED )
	EGE_EVENT_CLONE_0( GUIEventAnimationPlayed )
EGE_EVENT_END( )
EGE_GUI_EVENT_BEGIN( GUIEventAnimationStopped, _GUI_EVENT_ANIMATION_STOPPED )
	EGE_EVENT_CLONE_0( GUIEventAnimationStopped )
EGE_EVENT_END( )

//! The GUI control checked on
EGE_GUI_EVENT_BEGIN( GUIEventCheckOn, _GUI_EVENT_CHECK_ON )
	EGE_EVENT_CLONE_0( GUIEventCheckOn )
EGE_EVENT_END( )

//! The GUI control checked off
EGE_GUI_EVENT_BEGIN( GUIEventCheckOff, _GUI_EVENT_CHECK_OFF )
	EGE_EVENT_CLONE_0( GUIEventCheckOff )
EGE_EVENT_END( )

EGE_GUI_EVENT_BEGIN( GUIEventEditBoxClickToOpen, _GUI_EVENT_EDITBOX_CLICK_TO_OPEN )
	EGE_EVENT_CLONE_0( GUIEventEditBoxClickToOpen )
EGE_EVENT_END( )

EGE_GUI_EVENT_BEGIN( GUIEventEditBoxOpen, _GUI_EVENT_EDITBOX_OPEN )
	IEditBoxRef	mEditBox;
	EGE_EVENT_CLONE_1( GUIEventEditBoxOpen, mEditBox )
EGE_EVENT_END( )

EGE_GUI_EVENT_BEGIN( GUIEventEditBoxReturn, _GUI_EVENT_EDITBOX_RETURN )
	WString		mText;
	IEditBoxRef	mEditBox;
	EGE_EVENT_CLONE_2( GUIEventEditBoxReturn, mText, mEditBox )
EGE_EVENT_END( )

EGE_GUI_EVENT_BEGIN( GUIEventVisible, _GUI_EVENT_VISIBLE )
	EGE_EVENT_CLONE_0( GUIEventVisible )
EGE_EVENT_END( )
EGE_GUI_EVENT_BEGIN( GUIEventInvisible, _GUI_EVENT_INVISIBLE )
	EGE_EVENT_CLONE_0( GUIEventInvisible )
EGE_EVENT_END( )

//----------------------------------------------------------------------------
// GUI Inside/Outside Usage Event Classes 
//----------------------------------------------------------------------------

//!	The GUI mouse move event
EGE_GUI_EVENT_BEGIN( GUIEventMouseMove, _GUI_EVENT_MOUSE_MOVE )
	//!	The button type
	_MOUSE_BUTTON	mButton;
	//!	The mouse position
	Vector2			mPosition;
	//!	The delta mouse position
	Vector2			mDeltaPosition;
	EGE_EVENT_CLONE_3( GUIEventMouseMove, mButton, mPosition, mDeltaPosition )
EGE_EVENT_END( )

//!	The GUI mouse button up event
EGE_GUI_EVENT_BEGIN( GUIEventMouseButtonUp, _GUI_EVENT_MOUSE_BUTTON_UP )
	//!	The button type
	_MOUSE_BUTTON	mButton;
	//!	The mouse position
	Vector2			mPosition;
	//!	The delta mouse position
	Vector2			mDeltaPosition;
	EGE_EVENT_CLONE_3( GUIEventMouseButtonUp, mButton, mPosition, mDeltaPosition )
EGE_EVENT_END( )

//!	The GUI mouse button down event
EGE_GUI_EVENT_BEGIN( GUIEventMouseButtonDown, _GUI_EVENT_MOUSE_BUTTON_DOWN )
	//!	The button type
	_MOUSE_BUTTON	mButton;
	//!	The mouse position
	Vector2			mPosition;
	//!	The delta mouse position
	Vector2			mDeltaPosition;
	EGE_EVENT_CLONE_3( GUIEventMouseButtonDown, mButton, mPosition, mDeltaPosition )
EGE_EVENT_END( )

//!	The GUI mouse button double click message
EGE_GUI_EVENT_BEGIN( GUIEventMouseButtonDoubleClick, _GUI_EVENT_MOUSE_BUTTON_DOUBLE_CLICK )
	//!	The button type
	_MOUSE_BUTTON	mButton;
	//!	The mouse position
	Vector2			mPosition;
	//!	The delta mouse position
	Vector2			mDeltaPosition;
	EGE_EVENT_CLONE_3( GUIEventMouseButtonDoubleClick, mButton, mPosition, mDeltaPosition )
EGE_MESSAGE_END( )

//!	The GUI mouse scroll wheel event
EGE_GUI_EVENT_BEGIN( GUIEventMouseWheel, _GUI_EVENT_MOUSE_WHEEL )
	//!	The wheel value, > 0 indicates scroll up, otherwise scroll down
	_long	mWheel;
	EGE_EVENT_CLONE_1( GUIEventMouseWheel, mWheel )
EGE_EVENT_END( )

//!	The GUI key up event
EGE_GUI_EVENT_BEGIN( GUIEventKeyUp, _GUI_EVENT_KEY_UP )
	//!	The key code
	_dword	mKeyCode;
	EGE_EVENT_CLONE_1( GUIEventKeyUp, mKeyCode )
EGE_EVENT_END( )

//!	The GUI key down event
EGE_GUI_EVENT_BEGIN( GUIEventKeyDown, _GUI_EVENT_KEY_DOWN )
	//!	The key code
	_dword	mKeyCode;
	EGE_EVENT_CLONE_1( GUIEventKeyDown, mKeyCode )
EGE_EVENT_END( )

//!	The GUI scene resize event
EGE_GUI_EVENT_BEGIN( GUIEventSceneResize, _GUI_EVENT_SCENE_RESIZE )
	EGE_EVENT_CLONE_0( GUIEventSceneResize )
EGE_EVENT_END( )

//!	The GUI control set focus event
EGE_GUI_EVENT_BEGIN( GUIEventSetFocus, _GUI_EVENT_SET_FOCUS )
	EGE_EVENT_CLONE_0( GUIEventSetFocus )
EGE_EVENT_END( )

//!	The GUI control kill focus event
EGE_GUI_EVENT_BEGIN( GUIEventKillFocus, _GUI_EVENT_KILL_FOCUS )
	EGE_EVENT_CLONE_0( GUIEventKillFocus )
EGE_EVENT_END( )

//!	The GUI command event
EGE_GUI_EVENT_BEGIN( GUIEventCommand, _GUI_EVENT_COMMAND )
	//!	The command string
	WString	mCommand;
	//!	The argument string
	WString	mArgument;
	EGE_EVENT_CLONE_2( GUIEventCommand, mCommand, mArgument )
EGE_EVENT_END( )

//!	The GUI touch begin event
EGE_GUI_EVENT_BEGIN( GUIEventTouchBegin, _GUI_EVENT_TOUCH_BEGIN )
	//!	The time when the touch occurred or when it was last mutated.
	_qword	mTimestamp;
	//!	The current location of the receiver in the coordinate system of the given view.
	Vector2	mLocation;
	//! The unique touch id
	_dword	mTouchId;
	Vector2	mGUIObjectTouchOffset;
	EGE_EVENT_CLONE_4( GUIEventTouchBegin, mTimestamp, mLocation, mTouchId, mGUIObjectTouchOffset )
EGE_EVENT_END( )

//!	The GUI touch move event
EGE_GUI_EVENT_BEGIN( GUIEventTouchMove, _GUI_EVENT_TOUCH_MOVE )
	//!	The time when the touch occurred or when it was last mutated.
	_qword	mTimestamp;
	//!	The current location of the receiver in the coordinate system of the given view.
	Vector2	mLocation;
	//! The unique touch id
	_dword	mTouchId;
	Vector2 mPrevLocation;
	//! Get the delta position.
	Vector2 GetDeltaPos( ) const 
		{ return mLocation - mPrevLocation; }
	EGE_EVENT_CLONE_4( GUIEventTouchMove, mTimestamp, mLocation, mTouchId, mPrevLocation )
EGE_EVENT_END( )

//!	The GUI touch end event
EGE_GUI_EVENT_BEGIN( GUIEventTouchEnd, _GUI_EVENT_TOUCH_END )
	//!	The time when the touch occurred or when it was last mutated.
	_qword	mTimestamp;
	//!	The current location of the receiver in the coordinate system of the given view.
	Vector2	mLocation;
	//! The unique touch id
	_dword	mTouchId;
	EGE_EVENT_CLONE_3( GUIEventTouchEnd, mTimestamp, mLocation, mTouchId )
EGE_EVENT_END( )

EGE_GUI_EVENT_BEGIN( GUIEventParentHSizeChanged, _GUI_EVENT_PERENT_HSIZE_CHANGED )
	_float	mSize;
	EGE_EVENT_CLONE_1( GUIEventParentHSizeChanged, mSize )
EGE_EVENT_END( )

EGE_GUI_EVENT_BEGIN( GUIEventParentVSizeChanged, _GUI_EVENT_PERENT_VSIZE_CHANGED )
	_float	mSize;
	EGE_EVENT_CLONE_1( GUIEventParentVSizeChanged, mSize )
EGE_EVENT_END( )

EGE_GUI_EVENT_BEGIN( GUIEventHSizeChanged, _GUI_EVENT_HSIZE_CHANGED )
	_float	mSize;
	EGE_EVENT_CLONE_1( GUIEventHSizeChanged, mSize )
EGE_EVENT_END( )

EGE_GUI_EVENT_BEGIN( GUIEventVSizeChanged, _GUI_EVENT_VSIZE_CHANGED )
	_float	mSize;
	EGE_EVENT_CLONE_1( GUIEventVSizeChanged, mSize )
EGE_EVENT_END( )

//!	The GUI control start drop event
EGE_GUI_EVENT_BEGIN( GUIEventDropStart, _GUI_EVENT_DROP_START )
	//!	The touch message info
	GUIEventTouchBegin	mTouchInfo;
	EGE_EVENT_CLONE_1( GUIEventDropStart, mTouchInfo )
EGE_EVENT_END( )

//!	The GUI control is dropping event
EGE_GUI_EVENT_BEGIN( GUIEventDropping, _GUI_EVENT_DROPPING )
	//!	The touch message info
	GUIEventTouchMove	mTouchInfo;
	EGE_EVENT_CLONE_1( GUIEventDropping, mTouchInfo )
EGE_EVENT_END( )

//!	The GUI control end drop event
EGE_GUI_EVENT_BEGIN( GUIEventDropEnd, _GUI_EVENT_DROP_END )
	//!	The touch message info
	GUIEventTouchEnd	mTouchInfo;
	EGE_EVENT_CLONE_1( GUIEventDropEnd, mTouchInfo )
EGE_EVENT_END( )

EGE_GUI_EVENT_BEGIN( GUIEventSliderSliding, _GUI_EVENT_SLIDER_SLIDING )
	EGE_EVENT_CLONE_0( GUIEventSliderSliding )
EGE_EVENT_END( );

//!	The GUI control end drop event
EGE_GUI_EVENT_BEGIN( GUIEventScrollbarSlide, _GUI_EVENT_SCROLLBAR_SLIDE )
	//!	The touch message info
	_float				mValue;
	EGE_EVENT_CLONE_1( GUIEventScrollbarSlide, mValue )
EGE_EVENT_END( )

//! The touch point is not in the modal GUI application when touch begin
EGE_GUI_EVENT_BEGIN( GUIEventTouchModalOutside, _GUI_EVENT_TOUCH_MODAL_OUTSIDE )
	EGE_EVENT_CLONE_0( GUIEventTouchModalOutside )
EGE_EVENT_END( )

//!	The GUI control click event
EGE_GUI_EVENT_BEGIN( GUIEventClick, _GUI_EVENT_CLICK )
	EGE_EVENT_CLONE_0( GUIEventClick )
EGE_EVENT_END( )

EGE_GUI_EVENT_BEGIN( GUIEventSlideAnimationEnd, _GUI_EVENT_SLIDE_ANIMATION_END )
	EGE_EVENT_CLONE_0( GUIEventSlideAnimationEnd )
EGE_EVENT_END( )

//!	The GUI control attraction event
EGE_GUI_EVENT_BEGIN( GUIEventAttraction, _GUI_EVENT_ATTRACTION )
	//!	The GUI object what to be attracted
	IGUIObjectRef		mAttractedObject;
	//!	The GUI container what attract it
	IGUIContainerRef	mAttractContainer;
	EGE_EVENT_CLONE_2( GUIEventAttraction, mAttractedObject, mAttractContainer )
EGE_EVENT_END( )

EGE_GUI_EVENT_BEGIN( GUIEventParticlePlayerStopped, _GUI_EVENT_PARTICLE_STOPPED )
	EGE_EVENT_CLONE_0( GUIEventParticlePlayerStopped )
EGE_EVENT_END( )

EGE_GUI_EVENT_BEGIN( GUIEventEnterBackground, _GUI_EVENT_ENTER_BACKGROUND )
	EGE_EVENT_CLONE_0( GUIEventEnterBackground )
EGE_EVENT_END( )

EGE_GUI_EVENT_BEGIN( GUIEventEnterForeground, _GUI_EVENT_ENTER_FOREGROUND )
	EGE_EVENT_CLONE_0( GUIEventEnterForeground )
EGE_EVENT_END( )

EGE_GUI_EVENT_BEGIN( GUIWebViewPageFinished, _GUI_EVENT_WEB_VIEW_PAGE_FINISHED )
	WString	mURL;
	EGE_EVENT_CLONE_1( GUIWebViewPageFinished, mURL )
EGE_EVENT_END( )
EGE_GUI_EVENT_BEGIN( GUIWebViewProgressChanged, _GUI_EVENT_WEB_VIEW_PROGRESS_CHANGED )
	_dword	mProgress;
	EGE_EVENT_CLONE_1( GUIWebViewProgressChanged, mProgress )
EGE_EVENT_END( )
EGE_GUI_EVENT_BEGIN( GUIWebViewReceivedError, _GUI_EVENT_WEB_VIEW_RECEIVED_ERROR )
	_dword	mErrCode;
	WString	mDescription;
	WString	mURL;
	EGE_EVENT_CLONE_3( GUIWebViewReceivedError, mErrCode, mDescription, mURL )
EGE_EVENT_END( )

EGE_GUI_EVENT_BEGIN( GUIEventFlip, _GUI_EVENT_FLIP )
	EGE_EVENT_CLONE_0( GUIEventFlip )
EGE_EVENT_END( )

EGE_GUI_EVENT_BEGIN( GUIEventAnimationFlash, _GUI_EVENT_ANIMATION_FLASH )
	EGE_EVENT_CLONE_0( GUIEventAnimationFlash )
EGE_EVENT_END( )

EGE_END_NAMESPACE_2( )