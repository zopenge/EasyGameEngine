//! @file     GUIModuleMessageHandler.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGUI.h"

//----------------------------------------------------------------------------
// GUIModule Implementation
//----------------------------------------------------------------------------

_ubool GUIModule::RootAppHandleGUIEvent( const EventBase& event, const FlagsObject& flags )
{
	if ( mRootGUIApplication->HandleEvent( event, flags ) )
		return _true;

	return GetGUIModule( )->GetApplicationNotifier( )->OnHandleEvent( mRootGUIApplication, event, flags );
}

_ubool GUIModule::HandleClientSizeChangedMsg( const MessageClientSizeChanged& msg )
{
	mIsUpdateSize		= _true;
	mLastScreenSize.x	= (_float)msg.mClientSize.x;
	mLastScreenSize.y	= (_float)msg.mClientSize.y;

	return _false;
}

_ubool GUIModule::HandleKeyUpMsg( const MessageKeyUp& msg )
{
	GUIEventKeyUp gui_event;
	gui_event.mKeyCode = msg.mKeyCode;

	return RootAppHandleGUIEvent( gui_event, FlagsObject( _GUI_MESSAGE_DELIVER_CHILD ) );
}

_ubool GUIModule::HandleKeyDownMsg( const MessageKeyDown& msg )
{
	GUIEventKeyDown gui_event;
	gui_event.mKeyCode = msg.mKeyCode;

	return RootAppHandleGUIEvent( gui_event, FlagsObject( _GUI_MESSAGE_DELIVER_CHILD ) );
}

_ubool GUIModule::HandleMouseMoveMsg( const MessageMouseMove& msg )
{
	GUIEventMouseMove gui_event;
	gui_event.mButton			= msg.mButton;
	gui_event.mPosition			= Vector2( (_float) msg.mPosition.x, (_float) msg.mPosition.y );
	gui_event.mDeltaPosition	= Vector2( (_float) msg.mDeltaPosition.x, (_float) msg.mDeltaPosition.y );

	return RootAppHandleGUIEvent( gui_event, FlagsObject( _GUI_MESSAGE_DELIVER_CHILD ) );
}

_ubool GUIModule::HandleMouseButtonUpMsg( const MessageMouseButtonUp& msg )
{
	GUIEventMouseButtonUp gui_event;
	gui_event.mButton			= msg.mButton;
	gui_event.mPosition			= Vector2( (_float) msg.mPosition.x, (_float) msg.mPosition.y );
	gui_event.mDeltaPosition	= Vector2( (_float) msg.mDeltaPosition.x, (_float) msg.mDeltaPosition.y );

	return RootAppHandleGUIEvent( gui_event, FlagsObject( _GUI_MESSAGE_DELIVER_CHILD ) );
}

_ubool GUIModule::HandleMouseButtonDownMsg( const MessageMouseButtonDown& msg )
{
	GUIEventMouseButtonDown gui_event;
	gui_event.mButton			= msg.mButton;
	gui_event.mPosition			= Vector2( (_float) msg.mPosition.x, (_float) msg.mPosition.y );
	gui_event.mDeltaPosition	= Vector2( (_float) msg.mDeltaPosition.x, (_float) msg.mDeltaPosition.y );

	return RootAppHandleGUIEvent( gui_event, FlagsObject( _GUI_MESSAGE_DELIVER_CHILD ) );
}

_ubool GUIModule::HandleMouseButtonDoubleClickMsg( const MessageMouseButtonDoubleClick& msg )
{
	GUIEventMouseButtonDoubleClick gui_event;
	gui_event.mButton			= msg.mButton;
	gui_event.mPosition			= Vector2( (_float) msg.mPosition.x, (_float) msg.mPosition.y );
	gui_event.mDeltaPosition	= Vector2( (_float) msg.mDeltaPosition.x, (_float) msg.mDeltaPosition.y );

	return RootAppHandleGUIEvent( gui_event, FlagsObject( _GUI_MESSAGE_DELIVER_CHILD ) );
}

_ubool GUIModule::HandleMouseWheelMsg( const MessageMouseWheel& msg )
{
	GUIEventMouseWheel gui_event;
	gui_event.mWheel = msg.mWheel;

	return RootAppHandleGUIEvent( gui_event, FlagsObject( _GUI_MESSAGE_DELIVER_CHILD ) );
}

_ubool GUIModule::HandleTouchMsg( const MessageTouch& msg )
{
	Vector2 location_pos( msg.mLocation.x, msg.mLocation.y );

	switch ( msg.mEvent )
	{
		// Touch begin
		case MessageTouch::_EVENT_BEGAN:
		{
			// Record touch trace
			IInputRecordTraceRef trace = mInputRecorder->Record( msg );
			if ( trace.IsValid( ) )
			{
				m3DUITestPointInfoStack.Clear( );

				GUIEventTouchBegin gui_event;
				gui_event.mLocation		= location_pos;
				gui_event.mTimestamp	= msg.mTimestamp;
				gui_event.mTouchId		= msg.mTouchID;

				IGUIApplicationRef modal_application = GetTopReceiveModal( );

				if ( modal_application.IsNull( ) )
				{
					// Send touch begin event to control what receive this message
					Vector2 relative_position;
					IGUIObject* gui_object = mRootGUIApplication->TestPoint( gui_event.mLocation, gui_event.mLocation, Matrix3::cIdentity, FlagsObject( _GUI_TESTPOINT_CLICKABLE ), &relative_position );
					if ( gui_object != _null )
					{
						gui_event.mGUIObjectTouchOffset = relative_position;
						return gui_object->HandleEvent( gui_event, FlagsObject( ) );
					}
					else
					{
						// Let the user to handle it
						return GetGUIModule( )->GetApplicationNotifier( )->OnHandleEvent( mRootGUIApplication, gui_event, FlagsObject( ) );
					}
				}
				else
				{
					// Build the world transform
					Matrix3 world_transform_forchild = mRootGUIApplication->GetChildRelativeTransform( );					
					IGUIComponentState* modal_state = modal_application->GetComponentState( );

					modal_state->SetModal( _false );

					Vector2 relative_position;
					IGUIObject* gui_object = modal_application->TestPoint( gui_event.mLocation, gui_event.mLocation, world_transform_forchild, FlagsObject( _GUI_TESTPOINT_CLICKABLE ), &relative_position );

					modal_state->SetModal( _true );

					if ( gui_object != _null )
					{
						gui_event.mGUIObjectTouchOffset = relative_position;
						return gui_object->HandleEvent( gui_event, FlagsObject( ) );
					}
					else
					{
						if ( modal_application->PointInControl( gui_event.mLocation, world_transform_forchild, _null ) == _GTRT_OUT )
						{
							modal_application->HandleEvent( GUIEventTouchModalOutside( ), FlagsObject( ) );
						}
					}
				}
			}
		}
		break;

		// Touch moved
		case MessageTouch::_EVENT_MOVED:
		{
			// Record touch trace
			IInputRecordTraceRef trace = mInputRecorder->Record( msg );
			if ( trace.IsValid( ) )
			{
				GUIEventTouchMove gui_event;
				gui_event.mLocation		= location_pos;
				gui_event.mPrevLocation = Vector2( msg.mPrevLocation.x, msg.mPrevLocation.y );
				gui_event.mTimestamp	= msg.mTimestamp;
				gui_event.mTouchId		= msg.mTouchID;

				// Get the record and let the capture control handle this message
				IGUIObject* gui_object = trace->GetObject( ).cast_static< IGUIObject >( );
				if ( gui_object != _null )
				{
					if ( gui_object->IsCaptureMoveObject( ) )
						return gui_object->HandleEvent( gui_event, FlagsObject( ) );
					else
						return gui_object->HandleEvent( gui_event, FlagsObject( _GUI_MESSAGE_DELIVER_PARENT ) );
				}
				else
				{
					// Let the user to handle it
					return GetGUIModule( )->GetApplicationNotifier( )->OnHandleEvent( mRootGUIApplication, gui_event, FlagsObject( ) );
				}
			}
		}
		break;

		// Touch ended
		case MessageTouch::_EVENT_ENDED:
		{
			// Record touch trace
			IInputRecordTraceRef trace = mInputRecorder->Record( msg );
			if ( trace.IsValid( ) )
			{
				GUIEventTouchEnd gui_event;
				gui_event.mLocation		= location_pos;
				gui_event.mTimestamp	= msg.mTimestamp;
				gui_event.mTouchId		= msg.mTouchID;

				// Get the record and let the capture control handle this message
				IGUIObject* gui_object = trace->GetObject( ).cast_static< IGUIObject >( );
				if ( gui_object != _null )
				{
					return gui_object->HandleEvent( gui_event, FlagsObject( _GUI_MESSAGE_DELIVER_PARENT ) );
				}
				else
				{
					// Let the user to handle it
					return GetGUIModule( )->GetApplicationNotifier( )->OnHandleEvent( mRootGUIApplication, gui_event, FlagsObject( ) );
				}
			}
		}
		break;
	}

	return _false;
}

_ubool GUIModule::HandleEnterBackgroundMsg( const MessageEnterBackground& msg )
{
	ReleaseAllInput( );

	GUIEventEnterBackground gui_event;
	return RootAppHandleGUIEvent( gui_event, FlagsObject( _GUI_MESSAGE_DELIVER_CHILD ) );
}

_ubool GUIModule::HandleEnterForegroundMsg( const MessageEnterForeground& msg )
{
	ReleaseAllInput( );

	GUIEventEnterForeground gui_event;
	return RootAppHandleGUIEvent( gui_event, FlagsObject( _GUI_MESSAGE_DELIVER_CHILD ) );
}
