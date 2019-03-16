//! @file     GUIComponentEventHooker.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGUI.h"

//----------------------------------------------------------------------------
// GUIComponentEventHooker Implementation
//----------------------------------------------------------------------------

GUIComponentEventHooker::GUIComponentEventHooker( IGUIObject* gui_object ) : BaseClass( gui_object )
{
	mGUIEventUpdate			= _null;
	mGUIEventRenderBegin	= _null;
	mGUIEventRenderEnd		= _null;
	mGUIEventAfterRender	= _null;
}

GUIComponentEventHooker::~GUIComponentEventHooker( )
{
	ClearAllHookerFunc( _false );
}

template< typename EventType >
_void GUIComponentEventHooker::RegisterInternalEvent( EventType*& event_info, _dword event_id, const GUIEventHooker& hooker, const QwordParameters2& parameters )
{
	if ( event_info == _null )
		event_info = new EventType( );

	event_info->mHooker		= hooker;
	event_info->mParameters	= parameters;
}

IObject* GUIComponentEventHooker::CloneTo( _void* arguments ) const
{
	IGUIObject* gui_object = (IGUIObject*)arguments;
	EGE_ASSERT( gui_object != _null );

	GUIComponentEventHooker* component = new GUIComponentEventHooker( gui_object );
	component->CopyFrom( this );

	return component;
}

_ubool GUIComponentEventHooker::Import( ISerializableNode* node )
{
	return _true;
}

_ubool GUIComponentEventHooker::Export( ISerializableNode* node ) const
{
	return _true;
}

_ubool GUIComponentEventHooker::IsResident( ) const
{
	return _true;
}

_ubool GUIComponentEventHooker::HandleEvent( const EventBase& event, const FlagsObject& flags )
{
	if ( flags.HasFlags( _GUI_MESSAGE_SKIP_HOOKER ) )
		return _false;

	// Search for the registered hooker
	const GUIEventHookerInfo* hooker_info = mGUIEventHookerMap.Search( event.mEventID );
	if ( hooker_info == _null )
		return _false;

	return hooker_info->mHooker.Invoke( mGUIObject, event, hooker_info->mParameters );
}

_void GUIComponentEventHooker::ClearAllHookerFunc( _ubool deep )
{
	for ( GUIEventHookerMap::Iterator it = mGUIEventHookerMap.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		GUIEventHookerInfo& hooker_info = it.GetObject( );

		hooker_info.mHooker.Clear( );
	}

	mGUIEventHookerMap.Clear( );

	// Delete internal event info
	EGE_DELETE( mGUIEventUpdate );
	EGE_DELETE( mGUIEventRenderBegin );
	EGE_DELETE( mGUIEventRenderEnd );
	EGE_DELETE( mGUIEventAfterRender );

	if ( deep )
	{
		for ( IGUIObject* child = mGUIObject->FirstChildObject( ); child != _null; child = child->NextObject( ) )
			child->GetComponentEventHooker( )->ClearAllHookerFunc( deep );
	}
}

_void GUIComponentEventHooker::RegisterHookerFunc( _dword event_id, const GUIEventHooker& hooker, const QwordParameters2& parameters )
{
	GUIEventHookerInfo& hooker_info = mGUIEventHookerMap[ event_id ];

	hooker_info.mHooker.Clear( );
	hooker_info.mHooker		= hooker;
	hooker_info.mParameters	= parameters;

	// Update the internal event info
	switch ( event_id )
	{
		case _GUI_EVENT_UPDATE:			RegisterInternalEvent( mGUIEventUpdate, event_id, hooker, parameters ); break;
		case _GUI_EVENT_RENDER_BEGIN:	RegisterInternalEvent( mGUIEventRenderBegin, event_id, hooker, parameters ); break;
		case _GUI_EVENT_RENDER_END:		RegisterInternalEvent( mGUIEventRenderEnd, event_id, hooker, parameters ); break;
		case _GUI_EVENT_AFTER_RENDER:	RegisterInternalEvent( mGUIEventAfterRender, event_id, hooker, parameters ); break;
		default:
			break;
	}
}

_void GUIComponentEventHooker::UnregisterHookerFunc( _dword event_id )
{
	GUIEventHookerInfo* hooker_info = mGUIEventHookerMap.Search( event_id );
	if ( hooker_info == _null )
		return;

	hooker_info->mHooker.Clear( );

	mGUIEventHookerMap.Remove( event_id );

	// Delete the internal event info
	switch ( event_id )
	{
		case _GUI_EVENT_UPDATE:			EGE_DELETE( mGUIEventUpdate ); break;
		case _GUI_EVENT_RENDER_BEGIN:	EGE_DELETE( mGUIEventRenderBegin ); break;
		case _GUI_EVENT_RENDER_END:		EGE_DELETE( mGUIEventRenderEnd ); break;
		case _GUI_EVENT_AFTER_RENDER:	EGE_DELETE( mGUIEventAfterRender ); break;
		default:
			break;
	}
}

_ubool GUIComponentEventHooker::InvokeStateChangedFunc( _GUI_OBJECT_STATE prev_state )
{
	GUIEventStateChanged event;
	event.mPrevState = prev_state;

	return HandleEvent( event, FlagsObject( ) );
}

_ubool GUIComponentEventHooker::InvokeTickFunc( _dword elapse )
{
	if ( mGUIEventUpdate == _null )
		return _false;

	mGUIEventUpdate->mEvent.mElapse = elapse;

	return mGUIEventUpdate->mHooker.Invoke( mGUIObject, mGUIEventUpdate->mEvent, mGUIEventUpdate->mParameters );
}

_ubool GUIComponentEventHooker::InvokeBeginRenderFunc( const Matrix3& transform, const Color& color, const RectF& clip_rect )
{
	if ( mGUIEventRenderBegin == _null )
		return _false;

	mGUIEventRenderBegin->mEvent.mWorldTransform	= transform;
	mGUIEventRenderBegin->mEvent.mColor				= color;
	mGUIEventRenderBegin->mEvent.mClipRect			= clip_rect;

	return mGUIEventRenderBegin->mHooker.Invoke( mGUIObject, mGUIEventRenderBegin->mEvent, mGUIEventRenderBegin->mParameters );
}

_ubool GUIComponentEventHooker::InvokeEndRenderFunc( const Matrix3& transform, const Color& color )
{
	if ( mGUIEventRenderEnd == _null )
		return _false;

	mGUIEventRenderEnd->mEvent.mWorldTransform		= transform;
	mGUIEventRenderEnd->mEvent.mColor				= color;

	return mGUIEventRenderEnd->mHooker.Invoke( mGUIObject, mGUIEventRenderEnd->mEvent, mGUIEventRenderEnd->mParameters );
}

_ubool GUIComponentEventHooker::InvokeAfterRenderFunc( const Matrix3& transform, const Color& color )
{
	if ( mGUIEventAfterRender == _null )
		return _false;

	mGUIEventAfterRender->mEvent.mWorldTransform	= transform;
	mGUIEventAfterRender->mEvent.mColor				= color;

	return mGUIEventAfterRender->mHooker.Invoke( mGUIObject, mGUIEventAfterRender->mEvent, mGUIEventAfterRender->mParameters );
}

const GUIComponentEventHooker::GUIEventHookerInfo* GUIComponentEventHooker::GetHookerFunc( _dword event_id ) const
{
	return mGUIEventHookerMap.Search( event_id );
}

_ubool GUIComponentEventHooker::IsHandleEvent( _dword event_id ) const
{
	return _false;
}