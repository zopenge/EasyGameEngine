//! @file     EGE_Events.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! @brief    Globals enumerations and structure
//! Copyright ...

#pragma once

// The event ID start value
#define EGE_EVENT_OFFSET 1
#include "EGE_EventMacros.h"

//----------------------------------------------------------------------------
// Global Event
//----------------------------------------------------------------------------

EGE_EVENT_SESSION_BEGIN( EGE, Events )

//!	The base event structure
struct EventBase
{
	//!	The event ID
	mutable _dword		mEventID;
	//!	The result of event
	_qword				mRet;
	//!	True indicates this event had been handled
	_ubool				mHandled;

	//!	Clone event
	virtual EventBase* CloneTo( ) const PURE;

	EventBase( _dword eventid )
	{
		mEventID	= eventid;
		mRet		= 0;
		mHandled	= _false;
	}
	virtual ~EventBase( )
	{

	}
};

//!	The handled event structure easy-do when we will handle it.
template< typename Type >
struct HandledEvent
{
	EventBase& mEvent;

	HandledEvent( EventBase& event ) : mEvent( event )
	{
		mEvent.mHandled = _true;
	}

	operator Type& ( )
	{
		return (Type&)mEvent;
	}
	operator const Type& ( ) const
	{
		return (const Type&)mEvent;
	}
};

//!	Init file system event
EGE_EVENT_0( EventInitFileSystem, _EVENT_INIT_FILE_SYSTEM )
EGE_EVENT_END( )

//!	Open directory event
EGE_EVENT_1( EventOpenDir, _EVENT_OPEN_DIR, 
	//!	The directory path
	WString, mPath )
EGE_EVENT_END( )

//!	Close directory event
EGE_EVENT_1( EventCloseDir, _EVENT_CLOSE_DIR,
	//!	The directory handle
	_handle, mDirHandle )
EGE_EVENT_END( )

//!	Read directory event
EGE_EVENT_2( EventReadDir, _EVENT_READ_DIR,
		//!	The directory handle
		_handle, mDirHandle, 
		//!	The file data to feedback
		FileFinderData*, mFinderData )
EGE_EVENT_END( )

//!	Open file event
EGE_EVENT_4( EventOpenFile, _EVENT_OPEN_FILE,
	//!	The file name
	WString, mFileName,
	//!	The file create flag.
	_FILE_CREATE_FLAG, mCreateFlag,
	//!	The file operation flag, @see _FILE_OPERATION_FLAG.
	_dword, mOperationFlag,
	//!	The share flag.
	_dword, mShareFlags )
EGE_EVENT_END( )

//!	Get file attributes.
EGE_EVENT_2( EventGetFileAttributes, _EVENT_GET_FILE_ATTRIBUTES,
	//!	The file name
	WString, mFileName,
	//!	The file attributes, @see _FILE_ATTRIBUTE.
	_dword*, mAttributes )
EGE_EVENT_END( )

//!	Close file event
EGE_EVENT_1( EventCloseFile, _EVENT_CLOSE_FILE,
	//!	The file handle
	_handle, mFileHandle )
EGE_EVENT_END( )

//!	Set end of file event
EGE_EVENT_1( EventSetEndOfFile, _EVENT_SET_END_OF_FILE,
	//!	The file handle
	_handle, mFileHandle )
EGE_EVENT_END( )

//!	Get file size event
EGE_EVENT_1( EventGetFileSize, _EVENT_GET_FILE_SIZE, 
	//!	The file handle
	_handle, mFileHandle )
EGE_EVENT_END( )

//!	Seek file event
EGE_EVENT_3( EventSeekFile, _EVENT_SEEK_FILE,
	//!	The file handle
	_handle, mFileHandle,
	//!	The seek flag.
	_SEEK, mFlag,
	//!	The seek distance in bytes
	_int, mDistance )
EGE_EVENT_END( )

//!	Peek file event
EGE_EVENT_4( EventPeekFile, _EVENT_PEEK_FILE,
	//! The file handle.
	_handle, mFileHandle,
	//!	The offset in bytes.
	_dword, mOffset,
	//!	The buffer data.
	_void*, mBufferData,
	//!	The buffer size.
	_dword,	mBufferSize )
EGE_EVENT_END( )

//!	Read file event
EGE_EVENT_4( EventReadFile, _EVENT_READ_FILE,
	//! The file handle.
	_handle, mFileHandle,
	//!	The buffer data.
	_void*,	mBufferData,
	//!	The buffer size.
	_dword,	mBufferSize,
	//!	The read bytes.
	_dword*, mBytesRead )
EGE_EVENT_END( )

//!	Write file event
EGE_EVENT_4( EventWriteFile, _EVENT_WRITE_FILE,
	//! The file handle.
	_handle, mFileHandle, 
	//!	The buffer data.
	const _void*, mBufferData, 
	//!	The buffer size.
	_dword, mBufferSize, 
	//!	The write bytes.
	_dword*, mBytesWrite )
EGE_EVENT_END( )

//!	Create directory event.
EGE_EVENT_1( EventCreateDirectory, _EVENT_CREATE_DIRECTORY,
	//! The path.
	WString, mPath )
EGE_EVENT_END( )

//!	Create sub-process event
EGE_EVENT_3( EventCreateProcess, _EVENT_CREATE_PROCESS,
	//!	The process ID
	_dword, mID, 
	//!	The process handle
	_handle, mHandle, 
	//!	The image base of process
	_void*, mImageBase )
EGE_EVENT_END( )

//!	Exit sub-process event
EGE_EVENT_2( EventExitProcess, _EVENT_EXIT_PROCESS,
	//!	The process ID
	_dword, mID,
	//!	The exit code
	_dword, mExitCode )
EGE_EVENT_END( )

//!	Create thread event
EGE_EVENT_2( EventCreateThread, _EVENT_CREATE_THREAD,
	//!	The thread ID
	_dword, mID,
	//!	The thread handle
	_handle, mHandle )
EGE_EVENT_END( )

//!	Exit thread event
EGE_EVENT_2( EventExitThread, _EVENT_EXIT_THREAD,
	//!	The thread ID
	_dword, mID,
	//!	The exit code
	_dword, mExitCode )
EGE_EVENT_END( )

//!	Load DLL event
EGE_EVENT_3( EventLoadDLL, _EVENT_LOAD_DLL,
	//!	The process ID
	_dword, mProcessID,
	//!	The base address
	const _void*, mBaseAddress,
	// The DLL file name
	WString, mFileName )
EGE_EVENT_END( )

//!	Unload DLL event
EGE_EVENT_2( EventUnloadDLL, _EVENT_UNLOAD_DLL,
	//!	The process ID
	_dword, mProcessID, 
	//!	The base address
	const _void*, mBaseAddress )
EGE_EVENT_END( )

//!	Exception occurred event
EGE_EVENT_1( EventException, _EVENT_EXCEPTION,
	//!	The exception code ID
	_dword, mCodeID )
EGE_EVENT_END( )

//!	Output string event
EGE_EVENT_5( EventOutputString, _EVENT_OUTPUT_STRING,
	//! The type of event
	_LOG, mType,
	//! The category of event
	WString, mCategory,
	//! The string of event
	WString, mString,
	//!	The optional file name
	WString, mFileName,
	//!	The optional line number in file
	_dword,	mLineNumber )
EGE_EVENT_END( )

//!	The client size changed event
EGE_EVENT_2( EventClientSizeChanged, _EVENT_CLIENT_SIZE_CHANGED,
	//!	The client size in pixel
	PointU, mClientSize,
	//!	The ratio
	Ratio, mRatio )

	//!	Get the size by ratio.
	PointF GetClientSize( ) const
	{
		return Ratio::FixSizeF( mRatio, mClientSize );
	}
EGE_EVENT_END( )

//!	The client size is changing
EGE_EVENT( EventClientSizeChanging, _EVENT_CLIENT_SIZE_CHANGING )
	//!	The size changing type
	enum _TYPE
	{
		_TYPE_LEFT           = 1,
		_TYPE_RIGHT          = 2,
		_TYPE_TOP            = 3,
		_TYPE_TOPLEFT        = 4,
		_TYPE_TOPRIGHT       = 5,
		_TYPE_BOTTOM         = 6,
		_TYPE_BOTTOMLEFT     = 7,
		_TYPE_BOTTOMRIGHT    = 8,
	};

	// Update the client region by size
	_void UpdateSize( _int width, _int height )
	{
		switch ( mType )
		{
			case _TYPE_LEFT: 
				mClientRegion->l = mClientRegion->r - width;
				break;

			case _TYPE_RIGHT: 
				mClientRegion->r = mClientRegion->l + width;
				break;

			case _TYPE_TOP:
				mClientRegion->t = mClientRegion->b - height;
				break;

			case _TYPE_BOTTOM: 
				mClientRegion->b = mClientRegion->t + height;
				break;

			case _TYPE_TOPLEFT:
				mClientRegion->l = mClientRegion->r - width;
				mClientRegion->t = mClientRegion->b - height;
				break;

			case _TYPE_TOPRIGHT:
				mClientRegion->t = mClientRegion->b - height;
				mClientRegion->r = mClientRegion->l + width;
				break;
		
			case _TYPE_BOTTOMLEFT:
				mClientRegion->b = mClientRegion->t + height;
				mClientRegion->l = mClientRegion->r - width;
				break;

			case _TYPE_BOTTOMRIGHT:
				mClientRegion->b = mClientRegion->t + height;
				mClientRegion->r = mClientRegion->l + width;
				break;
		}
	}
EGE_EVENT_END_2( EventClientSizeChanging, _EVENT_CLIENT_SIZE_CHANGING,
	//!	The changing type, @see _TYPE
	_TYPE, mType,
	//!	The client region in pixel
	RectI*, mClientRegion )

//!	The surface create
EGE_EVENT_0( EventSurfaceCreate, _EVENT_SURFACE_CREATE )
EGE_EVENT_END( )

//!	The application before launch message
EGE_EVENT_0( EventBeforeLaunchApp, _EVENT_BEFORE_LAUNCH_APP )
EGE_EVENT_END( )

//!	The application after launch message
EGE_EVENT_0( EventAfterLaunchApp, _EVENT_AFTER_LAUNCH_APP )
EGE_EVENT_END( )

//!	The application before load message
EGE_EVENT_0( EventBeforeLoadApp, _EVENT_BEFORE_LOAD_APP )
EGE_EVENT_END( )

//!	The application after load message
EGE_EVENT_0( EventAfterLoadApp, _EVENT_AFTER_LOAD_APP )
EGE_EVENT_END( )

//! The application enter background
EGE_EVENT_0( EventEnterBackground, _EVENT_ENTER_BACKGROUND )
EGE_EVENT_END( )

//! The application enter foreground
EGE_EVENT_0( EventEnterForeground, _EVENT_ENTER_FOREGROUND )
EGE_EVENT_END( )

//! The application activity pause
EGE_EVENT_0( EventActivityPause, _EVENT_ACTIVITY_PAUSE )
EGE_EVENT_END( )

//! The application activity resume
EGE_EVENT_0( EventActivityResume, _EVENT_ACTIVITY_RESUME )
EGE_EVENT_END( )

//! The application activity stop
EGE_EVENT_0( EventActivityStop, _EVENT_ACTIVITY_STOP )
EGE_EVENT_END( )

//! The application activity restart
EGE_EVENT_0( EventActivityRestart, _EVENT_ACTIVITY_RESTART )
EGE_EVENT_END( )

//! The application activity start
EGE_EVENT_0( EventActivityStart, _EVENT_ACTIVITY_START )
EGE_EVENT_END( )

//! The application exit
EGE_EVENT_0( EventExitApplication, _EVENT_EXIT_APPLICATION )
EGE_EVENT_END( )

//! The application open URL
EGE_EVENT_1( EventApplicationOpenUrl, _EVENT_APPLICATION_OPEN_URL,
	WString, mURL )
EGE_EVENT_END( )

//! The application register for push notification result
EGE_EVENT_2( EventApplicationRegisterForPushNotification, _EVENT_APPLICATION_REGISTER_FOR_PUSH_NOTIFICATION,
    _ubool, mSuccess,
    WString, mResult )
EGE_EVENT_END( )

//!	The application key up message
EGE_EVENT_1( EventKeyUp, _EVENT_KEY_UP,
	//!	The key code, @see _KEY.
	_dword, mKeyCode )
EGE_EVENT_END( )

//!	The application key down message
EGE_EVENT_1( EventKeyDown, _EVENT_KEY_DOWN,
	//!	The key code, @see _KEY.
	_dword, mKeyCode )
EGE_EVENT_END( )

//!	The application char message
EGE_EVENT_1( EventChar, _EVENT_CHAR,
	//!	The key code, @see _KEY.
	_dword, mKeyCode )
EGE_EVENT_END( )

//!	The application dispatched key message
EGE_EVENT_1( EventDispatchedKey, _EVENT_DISPATCHED_KEY,
	_handle, mEvent )
EGE_EVENT_END( )

//!	The application dispatched generic motion message
EGE_EVENT_1( EventDispatchedGenericMotion, _EVENT_DISPATCHED_GENERIC_MOTION,
	_handle, mEvent )
EGE_EVENT_END( )

//!	The application enum resource file message
EGE_EVENT_2( EventEnumResFile, _EVENT_ENUM_RES_FILE,
	Platform::OnEnumResNameProc, mEnumResNameProc,
	_void*, mParameter )
EGE_EVENT_END( )

//!	The application mouse move message
EGE_EVENT_3( EventMouseMove, _EVENT_MOUSE_MOVE,
	//!	The button type
	_MOUSE_BUTTON, mButton,
	//!	The current mouse position
	PointI, mPosition,
	//!	The delta mouse position
	PointI, mDeltaPosition )
EGE_EVENT_END( )

//!	The application mouse button up message
EGE_EVENT_3( EventMouseButtonUp, _EVENT_MOUSE_BUTTON_UP,
	//!	The button type
	_MOUSE_BUTTON, mButton, 
	//!	The current mouse position
	PointI, mPosition, 
	//!	The delta mouse position
	PointI, mDeltaPosition )
EGE_EVENT_END( )

//!	The application mouse button down message
EGE_EVENT_3( EventMouseButtonDown, _EVENT_MOUSE_BUTTON_DOWN,
	//!	The button type
	_MOUSE_BUTTON, mButton,
	//!	The current mouse position
	PointI, mPosition,
	//!	The delta mouse position
	PointI, mDeltaPosition )
EGE_EVENT_END( )

//!	The application mouse button double click message
EGE_EVENT_3( EventMouseButtonDoubleClick, _EVENT_MOUSE_BUTTON_DOUBLE_CLICK,
	//!	The button type
	_MOUSE_BUTTON, mButton,
	//!	The current mouse position
	PointI, mPosition,
	//!	The delta mouse position
	PointI, mDeltaPosition )
EGE_EVENT_END( )

//!	The application mouse scroll wheel message
EGE_EVENT_1( EventMouseWheel, _EVENT_MOUSE_WHEEL,
	//!	The wheel value, > 0 indicates scroll up, otherwise scroll down
	_int, mWheel )
EGE_EVENT_END( )

//!	The accelerometer sensor changed message
EGE_EVENT_4( EventAccelerometerSensor, _EVENT_ACCELEROMETER_SNESOR,
	_dword, mTimestamp,
    _float, mX,
    _float, mY,
    _float, mZ )
EGE_EVENT_END( )

//!	The gyroscope sensor changed message
EGE_EVENT_4( EventGyroscopeSensor, _EVENT_GYROSCOPE_SNESOR,
	_dword, mTimestamp,
	_float, mX,
	_float, mY,
	_float, mZ )
EGE_EVENT_END( )

//!	The orientation sensor changed message
EGE_EVENT_4( EventOrientationSensor, _EVENT_ORIENTATION_SNESOR,
	_dword, mTimestamp,
    _float, mX,
    _float, mY,
    _float, mZ )
EGE_EVENT_END( )

//!	The acceleration sensor changed message
EGE_EVENT_4( EventAcceleration, _EVENT_ACCELERATION_SNESOR,
	_dword, mTimestamp,
    _float, mX,
    _float, mY,
    _float, mZ )
EGE_EVENT_END( )

//!	The application touch message
EGE_EVENT( EventTouch, _EVENT_TOUCH )
	//!	The touch event
	enum _EVENT
	{
		_EVENT_BEGAN,
		_EVENT_MOVED,
		_EVENT_ENDED,
	};

	//!	Get the delta position.
	PointF GetDeltaPos( ) const
	{
		return mLocation - mPrevLocation;
	}
EGE_EVENT_END_6( EventTouch, _EVENT_TOUCH,
	//! The index
	_dword, mIndex,
	//! The unique touch id
	_dword, mTouchID,
	//!	The touch event ID, @see _EVENT
	_EVENT, mEvent,
	//!	The time when the touch occurred or when it was last mutated.
	_dword, mTimestamp,
	//!	The previous location of the receiver in the coordinate system of the given view.
	PointF, mPrevLocation,
	//!	The current location of the receiver in the coordinate system of the given view.
	PointF, mLocation )

//!	The application pinch gesture recognizer message
EGE_EVENT( EventPinchGesture, _EVENT_PINCH_GESTURE )
	//!	The gesture state
	enum _STATE
	{
		_STATE_POSSIBLE,   // the recognizer has not yet recognized its gesture, but may be evaluating touch events. this is the default state
		
		_STATE_BEGAN,      // the recognizer has received touches recognized as the gesture. the action method will be called at the next turn of the run loop
		_STATE_CHANGED,    // the recognizer has received touches recognized as a change to the gesture. the action method will be called at the next turn of the run loop
		_STATE_ENDED,      // the recognizer has received touches recognized as the end of the gesture. the action method will be called at the next turn of the run loop and the recognizer will be reset to UIGestureRecognizerStatePossible
		_STATE_CANCELLED,  // the recognizer has received touches resulting in the cancellation of the gesture. the action method will be called at the next turn of the run loop. the recognizer will be reset to UIGestureRecognizerStatePossible
		
		_STATE_FAILED,     // the recognizer has received a touch sequence that can not be recognized as the gesture. the action method will not be called and the recognizer will be reset to UIGestureRecognizerStatePossible
		
		// Discrete Gestures ¨C gesture recognizers that recognize a discrete event but do not report changes (for example, a tap) do not transition through the Began and Changed states and can not fail or be cancelled
		_STATE_RECOGNIZED = _STATE_ENDED // the recognizer has received touches recognized as the gesture. the action method will be called at the next turn of the run loop and the recognizer will be reset to UIGestureRecognizerStatePossible
	};

	//!	The zoom operation flag
	enum _ZOOM_FLAG
	{
		_ZOOM_UNKNOWN,
		_ZOOM_IN,
		_ZOOM_OUT,
	};
EGE_EVENT_END_3( EventPinchGesture, _EVENT_PINCH_GESTURE,
	//!	The gesture state, @see _STATE
	_STATE, mState,
	//!	The zoom flag, @see _ZOOM_FLAG
	_ZOOM_FLAG, mZoomFlag,
	//!	The scale factor
	_float, mScaleFactor )

//!	The application touch message
EGE_EVENT( EventShakeMotion, _EVENT_SHAKE_MOTION )
	//!	The touch event
	enum _EVENT
	{
		_EVENT_BEGAN,
		_EVENT_ENDED,
		_EVENT_CANCELLED,
	};
EGE_EVENT_END_2( EventShakeMotion, _EVENT_SHAKE_MOTION,
	//!	The touch event ID, @see _EVENT
	_EVENT, mEvent,
	//!	The time when the touch occurred or when it was last mutated.
	_dword, mTimestamp )

//!	The system command message
EGE_EVENT( EventSysCommand, _EVENT_SYSCOMMAND )
	//!	System Menu Command Values
	enum _SYSTEM_COMMAND
	{
		_SC_SIZE         = 0xF000,
		_SC_MOVE         = 0xF010,
		_SC_DRAGMOVE     = 0xF012,
		_SC_MINIMIZE     = 0xF020,
		_SC_MAXIMIZE     = 0xF030,
		_SC_NEXTWINDOW   = 0xF040,
		_SC_PREVWINDOW   = 0xF050,
		_SC_CLOSE        = 0xF060,
		_SC_VSCROLL      = 0xF070,
		_SC_HSCROLL      = 0xF080,
		_SC_MOUSEMENU    = 0xF090,
		_SC_KEYMENU      = 0xF100,
		_SC_ARRANGE      = 0xF110,
		_SC_RESTORE      = 0xF120,
		_SC_TASKLIST     = 0xF130,
		_SC_SCREENSAVE   = 0xF140,
		_SC_HOTKEY       = 0xF150,
	};
EGE_EVENT_END_2( EventSysCommand, _EVENT_SYSCOMMAND,
	//!	http://msdn.microsoft.com/en-us/library/ms646360(v=vs.85).aspx
	//!	@see _SYSTEM_COMMAND.
	_SYSTEM_COMMAND, mCommandID,
	_dword, mParam )

//!	The command message
EGE_EVENT_2( EventCommand, _EVENT_COMMAND,
	//!	The parameters
	_dword, wParam,
	_dword, lParam )
EGE_EVENT_END( )

//!	The tray message
EGE_EVENT( EventTray, _EVENT_TRAY )
	//!	Notification Events
	enum _NOTIFICATION_EVENT
	{
		 _NE_BALLOONSHOW		= 0x0400 + 2,
		 _NE_BALLOONHIDE		= 0x0400 + 3,
		 _NE_BALLOONTIMEOUT     = 0x0400 + 4,
		 _NE_BALLOONUSERCLICK   = 0x0400 + 5,
		 _NE_POPUPOPEN			= 0x0400 + 6,
		 _NE_POPUPCLOSE     	= 0x0400 + 7,
		 _NE_CONTEXTMENU		= 0x007B,
		 _NE_LBUTTONDOWN		= 0x0201,
		 _NE_RBUTTONDOWN		= 0x0204,
	};
EGE_EVENT_END_2( EventTray, _EVENT_TRAY,
	//!	The notification event, @see _NOTIFICATION_EVENT
	_NOTIFICATION_EVENT, mEvent,
	//!	The icon ID.
	_dword, mIconID )

//!	The low memory message
EGE_EVENT_0( EventLowMemory, _EVENT_LOW_MEMORY )
EGE_EVENT_END( )  

//!	The begin reset resources message
EGE_EVENT_0( EventBeginResetResources, _EVENT_BEGIN_RESET_RESOURCES )
EGE_EVENT_END( )  

//!	The end reset resources message
EGE_EVENT_0( EventEndResetResources, _EVENT_END_RESET_RESOURCES )
EGE_EVENT_END( )  

//!	The begin unload resources message
EGE_EVENT_0( EventBeginUnloadResources, _EVENT_BEGIN_UNLOAD_RESOURCES )
EGE_EVENT_END( )  

//!	The end unload resources message
EGE_EVENT_0( EventEndUnloadResources, _EVENT_END_UNLOAD_RESOURCES )
EGE_EVENT_END( )  

//!	The joystick move message.
EGE_EVENT_2( EventJoystickMove, _EVENT_JOYSTICK_MOVE,
	_dword, mID,
	PointI, mPosition )
EGE_EVENT_END( )  

//!	The joystick z-move message.
EGE_EVENT_2( EventJoystickZMove, _EVENT_JOYSTICK_ZMOVE,
	_dword, mID, 
	_int, mZPosition )
EGE_EVENT_END( )  

//!	The joystick button up message.
EGE_EVENT_2( EventJoystickButtonUp, _EVENT_JOYSTICK_BUTTON_UP,
	_dword, mID,
	_dword, mFlags )
EGE_EVENT_END( )  

//!	The joystick button down message.
EGE_EVENT_2( EventJoystickButtonDown, _EVENT_JOYSTICK_BUTTON_DOWN,
	_dword, mID,
	_dword, mFlags )
EGE_EVENT_END( )  

EGE_EVENT_SESSION_END( )
#undef EGE_EVENT_OFFSET