//! @file     GUIComponentState.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGUI.h"

//----------------------------------------------------------------------------
// GUIComponentState Implementation
//----------------------------------------------------------------------------

GUIComponentState::GUIComponentState( IGUIObject* gui_object ) : BaseClass( gui_object )
{
	mState = _GUI_STATE_NORMAL;
}

GUIComponentState::~GUIComponentState( )
{
}

IObject* GUIComponentState::CloneTo( _void* arguments ) const
{
	IGUIObject* gui_object = (IGUIObject*) arguments;
	EGE_ASSERT( gui_object != _null );

	GUIComponentState* component	= new GUIComponentState( gui_object );
	component->CopyFrom( this );
	component->mState				= GetState( );
	component->mStatesEx			= GetStatesEx( );
	component->mAttributes			= GetAttributes( );

	return component;
}

_ubool GUIComponentState::Import( ISerializableNode* node )
{
	if ( node == _null )
		return _false;

	node->ReadFlag( L"clip", _GUI_ATTRIBUTE_CLIPCHILD, mAttributes );
	node->ReadFlag( L"dont_clip_self", _GUI_ATTRIBUTE_DONT_CLIPSELF, mAttributes );
	node->ReadFlag( L"checkable", _GUI_ATTRIBUTE_CHECKABLE, mAttributes );
	node->ReadFlag( L"radio", _GUI_ATTRIBUTE_RADIO, mAttributes );
	node->ReadFlag( L"editbox", _GUI_ATTRIBUTE_EDITBOX, mAttributes );
	node->ReadFlag( L"cancel", _GUI_ATTRIBUTE_CANCEL, mAttributes );
	node->ReadFlag( L"default", _GUI_ATTRIBUTE_DEFAULT, mAttributes );
	node->ReadFlag( L"ui3d", _GUI_ATTRIBUTE_UI3D, mAttributes );
	node->ReadFlag( L"test_point_always", _GUI_ATTRIBUTE_TEST_POINT_ALWAYS, mAttributes );
	node->ReadFlag( L"manual_check", _GUI_ATTRIBUTE_MANUAL_CHECK, mAttributes );

	return _true;
}

_ubool GUIComponentState::Export( ISerializableNode* node ) const
{
	if ( node == _null )
		return _false;

	if ( node->WriteFlag( L"clip", _GUI_ATTRIBUTE_CLIPCHILD, mAttributes ) == _false )
		return _false;

	if ( node->WriteFlag( L"dont_clip_self", _GUI_ATTRIBUTE_DONT_CLIPSELF, mAttributes ) == _false )
		return _false;

	if ( node->WriteFlag( L"checkable", _GUI_ATTRIBUTE_CHECKABLE, mAttributes ) == _false )
		return _false;

	if ( node->WriteFlag( L"radio", _GUI_ATTRIBUTE_RADIO, mAttributes ) == _false )
		return _false;

	if ( node->WriteFlag( L"editbox", _GUI_ATTRIBUTE_EDITBOX, mAttributes ) == _false )
		return _false;

	if ( node->WriteFlag( L"cancel", _GUI_ATTRIBUTE_CANCEL, mAttributes ) == _false )
		return _false;

	if ( node->WriteFlag( L"default", _GUI_ATTRIBUTE_DEFAULT, mAttributes ) == _false )
		return _false;
	if ( node->WriteFlag( L"ui3d", _GUI_ATTRIBUTE_UI3D, mAttributes ) == _false )
		return _false;

	if ( node->WriteFlag( L"test_point_always", _GUI_ATTRIBUTE_TEST_POINT_ALWAYS, mAttributes ) == _false )
		return _false;

	if (node->WriteFlag(L"manual_check", _GUI_ATTRIBUTE_MANUAL_CHECK, mAttributes) == _false)
		return _false;

	return _true;
}

_ubool GUIComponentState::IsResident( ) const
{
	return _true;
}

_ubool GUIComponentState::HandleEvent( const EventBase& event, const FlagsObject& flags )
{
	_dword event_id = event.mEventID;

	if ( IsEnable( ) == _false )
	{
		SetState( _GUI_STATE_DISABLE );
	}
	else if ( event_id == _GUI_EVENT_SHOW || event_id == _GUI_EVENT_FOCUS_OFF || event_id == _GUI_EVENT_CHECK_ON )
	{
		if ( IsCheck( ) )
			SetState( _GUI_STATE_CHECKED );
		else
			SetState( _GUI_STATE_NORMAL );
	}
	else if ( event_id == _GUI_EVENT_FOCUS_ON )
	{
		if ( IsCheck( ) )
			SetState( _GUI_STATE_CHECKED_FOCUS );
		else
			SetState( _GUI_STATE_FOCUS );
	}
	else
	{
		return _false;
	}

	return _true;
}

_void GUIComponentState::SetState( _GUI_OBJECT_STATE state )
{
	if ( mState == state )
		return;

	GUIEventStateChanged event;
	event.mPrevState = mState;

	mState = state;

	mGUIObject->HandleEvent( event, FlagsObject( ) );
}

_GUI_OBJECT_STATE GUIComponentState::GetState( ) const
{
	return mState;
}

_ubool GUIComponentState::IsBaseGUIState( _GUI_OBJECT_STATE state1, _GUI_OBJECT_STATE state2 ) const
{
	if ( state1 == state2 )
		return _true;

	if ( state2 == _GUI_STATE_NORMAL )
		return _false;

	_GUI_OBJECT_STATE state2_base_state = state2;
	if ( state2 & 0xFFFFFF00 )
		state2_base_state = (_GUI_OBJECT_STATE) ( ( (_dword) state2 & 0x0000FF00 ) >> 8 );
	else
		state2_base_state = _GUI_STATE_NORMAL; // Default state as base

	return IsBaseGUIState( state1, state2_base_state );
}

_ubool GUIComponentState::ReplayOnChangedState( AStringPtr component_name, _GUI_OBJECT_STATE prev_state, _GUI_OBJECT_STATE curr_state ) const
{
	IGUIComponent* prev_component = mGUIObject->FindComponent( prev_state, component_name );
	IGUIComponent* curr_component = mGUIObject->FindComponent( curr_state, component_name );

	if ( prev_component != curr_component )
	{
		if ( prev_component != _null )
		{
			if ( curr_component != _null )
				return _true;
		}
		else
		{
			if ( curr_component != _null && IsBaseGUIState( prev_state, curr_state ) )
				return _true;
		}
	}

	return _false;
}

FlagsObject& GUIComponentState::GetStatesEx( )
{
	return mStatesEx;
}

const FlagsObject& GUIComponentState::GetStatesEx( ) const
{
	return mStatesEx;
}

FlagsObject& GUIComponentState::GetAttributes( )
{
	return mAttributes;
}

const FlagsObject& GUIComponentState::GetAttributes( ) const
{
	return mAttributes;
}

_void GUIComponentState::Enable( _ubool enable, _ubool deep )
{
	if ( enable )
	{
		if ( IsCheck( ) )
			SetState( _GUI_STATE_CHECKED );
		else
			SetState( _GUI_STATE_NORMAL );
	}
	else
	{
		if ( IsCheck( ) )
			SetState( _GUI_STATE_CHECKED_DISABLE );
		else
			SetState( _GUI_STATE_DISABLE );
	}

	if ( deep )
	{
		for ( IGUIObject* it = mGUIObject->FirstChildObject( ); it != _null; it = it->NextObject( ) )
		{
			it->GetComponentState( )->Enable( enable, deep );
		}
	}
}

_ubool GUIComponentState::IsEnable( ) const
{
	return mState != _GUI_STATE_DISABLE && mState != _GUI_STATE_CHECKED_DISABLE;
}

_void GUIComponentState::SetVisible( _ubool show, _ubool force, _ubool deep )
{
	// Show all parent objects
	if ( show && force )
	{
		for ( IGUIObject* parent_object = mGUIObject->ParentObject( ); parent_object != _null; parent_object = parent_object->ParentObject( ) )
			parent_object->GetComponentState( )->SetVisible( show, _false, _false );
	}

	// Process show event
	if ( show )
	{
		mStatesEx.CombineFlags( _GUI_STATE_EX_SHOW );

		GUIEventShow show_event;
		mGUIObject->HandleEvent( show_event, FlagsObject( ) );
	}
	// Process hide event
	else
	{
		mStatesEx.ClearFlags( _GUI_STATE_EX_SHOW );
		GUIEventHide hide_event;
		mGUIObject->HandleEvent( hide_event, FlagsObject( ) );

		if ( deep == _false )
		{
			for ( IGUIObject* it = mGUIObject->FirstChildObject( ); it != _null; it = it->NextObject( ) )
				it->HandleEvent( hide_event, FlagsObject( _GUI_MESSAGE_DELIVER_CHILD ) );
		}
	}

	// Deliver to child objects
	if ( deep )
	{
		for ( IGUIObject* it = mGUIObject->FirstChildObject( ); it != _null; it = it->NextObject( ) )
			it->GetComponentState( )->SetVisible( show, _false, deep );
	}
}

_ubool GUIComponentState::IsVisiable( ) const
{
	for ( const IGUIObject* gui_object = mGUIObject; gui_object != _null; gui_object = gui_object->ParentObject( ) )
	{
		if ( gui_object->IsShow( ) == _false )
			return _false;
	}

	return _true;
}

_void GUIComponentState::Check( _ubool check, _ubool handle_event, _ubool force )
{
	if ( mAttributes.HasFlags( _GUI_ATTRIBUTE_CHECKABLE ) == _false )
		return;

	if ( check )
	{
		switch ( mState )
		{
			case _GUI_STATE_NORMAL: SetState( _GUI_STATE_CHECKED ); break;
			case _GUI_STATE_FOCUS: SetState( _GUI_STATE_CHECKED_FOCUS ); break;
			case _GUI_STATE_HOVER: SetState( _GUI_STATE_CHECKED_HOVER ); break;
			case _GUI_STATE_DISABLE: SetState( _GUI_STATE_CHECKED_DISABLE ); break;
			default:
				break;
		}

		if ( mAttributes.HasFlags( _GUI_ATTRIBUTE_RADIO ) )
		{
			for ( IGUIObject* it = mGUIObject->ParentObject( )->FirstChildObject( ); it != _null; it = it->NextObject( ) )
			{
				if ( it == mGUIObject )
					continue;

				it->GetComponentState( )->Check( _false, handle_event, _true );
			}			
		}
	}
	else
	{
		if ( mAttributes.HasFlags( _GUI_ATTRIBUTE_RADIO ) && force == _false )
			return;
		
		switch ( mState )
		{
			case _GUI_STATE_CHECKED: SetState( _GUI_STATE_NORMAL ); break;
			case _GUI_STATE_CHECKED_FOCUS: SetState( _GUI_STATE_FOCUS ); break;
			case _GUI_STATE_CHECKED_HOVER: SetState( _GUI_STATE_HOVER ); break;
			case _GUI_STATE_CHECKED_DISABLE: SetState( _GUI_STATE_DISABLE ); break;
			default:
				break;
		}
	}

	FlagsObject flags;
	flags.EnableFlags( _GUI_MESSAGE_SKIP_HOOKER, !handle_event );

	if ( check )
	{
		GUIEventCheckOn check_on_event;
		mGUIObject->HandleEvent( check_on_event, flags );
	}
	else
	{
		GUIEventCheckOff check_off_event;
		mGUIObject->HandleEvent( check_off_event, flags );
	}
}

_ubool GUIComponentState::IsCheck( ) const
{
	switch ( mState )
	{
		case _GUI_STATE_CHECKED:
		case _GUI_STATE_CHECKED_FOCUS:
		case _GUI_STATE_CHECKED_HOVER:
		case _GUI_STATE_CHECKED_DISABLE:
			return _true;

		default:
			break;
	}

	return _false;
}

_void GUIComponentState::SetCheckable( _ubool checkable )
{
	mAttributes.EnableFlags( _GUI_ATTRIBUTE_CHECKABLE, checkable );
}

_ubool GUIComponentState::IsCheckable( ) const
{
	return mAttributes.HasFlags( _GUI_ATTRIBUTE_CHECKABLE );
}

_void GUIComponentState::SetRadio( _ubool radio )
{
	mAttributes.EnableFlags( _GUI_ATTRIBUTE_RADIO, radio );
}

_ubool GUIComponentState::IsRadio( ) const
{
	return mAttributes.HasFlags( _GUI_ATTRIBUTE_RADIO );
}

_void GUIComponentState::SetModal( _ubool modal )
{
	mStatesEx.EnableFlags( _GUI_STATE_EX_MODAL, modal );
}

_ubool GUIComponentState::IsModal( ) const
{
	return mStatesEx.HasFlags( _GUI_STATE_EX_MODAL );
}

_void GUIComponentState::SetTempModal( _ubool modal )
{
	mStatesEx.EnableFlags( _GUI_STATE_EX_TEMP_MODAL, modal );
}

_ubool GUIComponentState::IsTempModal( ) const
{
	return mStatesEx.HasFlags( _GUI_STATE_EX_TEMP_MODAL );
}

_void GUIComponentState::SetEditBox( _ubool edit )
{
	mAttributes.EnableFlags( _GUI_ATTRIBUTE_EDITBOX, edit );
}

_ubool GUIComponentState::IsEditBox( ) const
{
	return mAttributes.HasFlags( _GUI_ATTRIBUTE_EDITBOX );
}

_void GUIComponentState::DelayLoad( _ubool delay )
{
	mStatesEx.EnableFlags( _GUI_STATE_EX_DELAY_LOAD, delay );
}

_ubool GUIComponentState::IsDelayLoad( ) const
{
	return mStatesEx.HasFlags( _GUI_STATE_EX_DELAY_LOAD );
}

_void GUIComponentState::Pause( _ubool pause )
{
	mStatesEx.EnableFlags( _GUI_STATE_EX_PAUSING, pause );
}

_ubool GUIComponentState::IsPausing( ) const
{
	return mStatesEx.HasFlags( _GUI_STATE_EX_PAUSING );
}

_void GUIComponentState::SetCancelButton( _ubool cancel )
{
	mAttributes.EnableFlags( _GUI_ATTRIBUTE_CANCEL, cancel );
}

_ubool GUIComponentState::IsCancelButton( ) const
{
	return mAttributes.HasFlags( _GUI_ATTRIBUTE_CANCEL );
}

_void GUIComponentState::SetDefaultButton( _ubool isdefault )
{
	mAttributes.EnableFlags( _GUI_ATTRIBUTE_DEFAULT, isdefault );
}

_ubool GUIComponentState::IsDefaultButton( ) const
{
	return mAttributes.HasFlags( _GUI_ATTRIBUTE_DEFAULT );
}

_void GUIComponentState::Set3DGUIObjectInUI( _ubool isdefault )
{
	mAttributes.EnableFlags( _GUI_ATTRIBUTE_UI3D, isdefault );
}

_ubool GUIComponentState::Is3DGUIObjectInUI( ) const
{
	return mAttributes.HasFlags( _GUI_ATTRIBUTE_UI3D );
}

_void GUIComponentState::Set3DGUIObjectInScene( _ubool isdefault )
{
	mAttributes.EnableFlags( _GUI_ATTRIBUTE_SCENE3D, isdefault );
}

_ubool GUIComponentState::Is3DGUIObjectInScene( ) const
{
	return mAttributes.HasFlags( _GUI_ATTRIBUTE_SCENE3D );
}

_void GUIComponentState::SetTestPointAlways( _ubool check )
{
	mAttributes.EnableFlags( _GUI_ATTRIBUTE_TEST_POINT_ALWAYS, check );
}

_ubool GUIComponentState::IsTestPointAlways( ) const
{
	return mAttributes.HasFlags( _GUI_ATTRIBUTE_TEST_POINT_ALWAYS );
}

_void GUIComponentState::SetManualCheck(_ubool checkable)
{
	mAttributes.EnableFlags(_GUI_ATTRIBUTE_MANUAL_CHECK, checkable);
}

_ubool GUIComponentState::IsManualCheck() const
{
	return mAttributes.HasFlags(_GUI_ATTRIBUTE_MANUAL_CHECK);
}
