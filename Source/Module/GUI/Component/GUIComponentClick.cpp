//! @file     GUIComponentClick.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGUI.h"

//----------------------------------------------------------------------------
// GUIComponentClick Implementation
//----------------------------------------------------------------------------

GUIComponentClick::GUIComponentClick( IGUIObject* gui_object ) : BaseClass( gui_object )
{
	mTouchBeginRelativeOffset = Vector2::cOrigin;
}

GUIComponentClick::~GUIComponentClick( )
{
}

IObject* GUIComponentClick::CloneTo( _void* arguments ) const
{
	IGUIObject* gui_object = (IGUIObject*)arguments;
	EGE_ASSERT( gui_object != _null );

	GUIComponentClick* component			= new GUIComponentClick( gui_object );
	component->CopyFrom( this );
	component->mTouchBeginRelativeOffset	= Vector2::cOrigin;

	return component;
}

_ubool GUIComponentClick::Import( ISerializableNode* node )
{
	return _true;
}

_ubool GUIComponentClick::Export( ISerializableNode* node ) const
{
	return _true;
}

_ubool GUIComponentClick::HandleEvent( const EventBase& event, const FlagsObject& flags )
{
	switch ( event.mEventID )
	{
	case _GUI_EVENT_TOUCH_BEGIN:
		{
			const GUIEventTouchBegin& touch_msg = (const GUIEventTouchBegin&) event;
			IInputRecordTraceRef ti = GetGUIModule( )->GetInputRecorder( )->GetRecordTraceByObject( mGUIObject );
			if ( ti.IsValid( ) )
				return _false;

			IInputRecordTraceRef traceinfo = GetGUIModule( )->GetInputRecorder( )->GetRecordTraceByChannelID( touch_msg.mTouchId );
			traceinfo->SetObject( mGUIObject );
			mGUIObject->Focus( _true );

			mTouchBeginRelativeOffset		= touch_msg.mGUIObjectTouchOffset;

			return _true;
		}
		break;
	case _GUI_EVENT_TOUCH_MOVE:
		{
			//const GUIEventTouchMove& touch_msg = (const GUIEventTouchMove&) event;

			return _false;
		}
		break;
	case _GUI_EVENT_TOUCH_END:
		{
			const GUIEventTouchEnd& touch_msg = (const GUIEventTouchEnd&) event;
			IInputRecordTraceRef traceinfo = GetGUIModule( )->GetInputRecorder( )->GetRecordTraceByChannelID( touch_msg.mTouchId );

			if ( traceinfo.IsValid( ) )
			{
				if ( traceinfo->GetObject( ) == mGUIObject )
				{
					// touch begin location
					Vector2 touch_begin_pos	= traceinfo->GetInputRecords( ).GetHeadElement( ).GetPosition( );
					// current guiobject location
					Vector2 gui_position	= mGUIObject->GetWorldTransform( ).GetTranslationVector( );
					// touch end location
					Vector2 touch_end_pos	= gui_position + mTouchBeginRelativeOffset + touch_msg.mLocation - touch_begin_pos;

					if ( mGUIObject->RelativePointInControl( touch_end_pos ) )
						Click( );

					mGUIObject->Focus( _false );

					traceinfo->SetObject( _null );

					return _true;
				}			
			}
			else
			{
				WLOG_ERROR_2( L"The touch end event is invalid, touchID: %d, control name: '%s' ", touch_msg.mTouchId, mGUIObject->GetResName( ).Str( ) );
				mGUIObject->Focus( _false );
				return _true;
			}
		}
		break;
	default:
		break;
	}
	
	return _false;
}

_ubool GUIComponentClick::IsHandleEvent( _dword event_id ) const
{
	switch ( event_id )
	{
	case _GUI_EVENT_TOUCH_BEGIN:
		{
			return mGUIObject->GetComponentState( )->IsEnable( );
		}
		break;
	case _GUI_EVENT_CLICK:
		{
			return mGUIObject->GetComponentState( )->IsEnable( );
		}
		break;
	}

	return _false;
}

_void GUIComponentClick::Click( )
{
	// Send click event
	mGUIObject->HandleEvent( GUIEventClick( ), FlagsObject::cNull );

	// Exchange check status
	if ( !mGUIObject->GetComponentState()->IsManualCheck() )
		mGUIObject->GetComponentState()->Check(!mGUIObject->GetComponentState()->IsCheck(), _true);

	// open edit box.
	if ( mGUIObject->GetComponentState( )->IsEditBox( ) )
		mGUIObject->HandleEvent( GUIEventEditBoxClickToOpen( ), FlagsObject::cNull );
}
