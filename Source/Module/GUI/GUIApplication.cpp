//! @file     GUIApplication.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGUI.h"

//----------------------------------------------------------------------------
// GUIApplication Implementation
//----------------------------------------------------------------------------

GUIApplication::GUIApplication( )
{
	this->CreateComponentT< IGUIComponent3DRender >( );
}

GUIApplication::~GUIApplication( )
{
	GetGUIModule( )->GetApplicationNotifier( )->OnBeforeUnload( this );
}

_ubool GUIApplication::IsApplication( ) const
{
	return _true;
}

_void GUIApplication::Tick( _time_t tick, _dword elapse )
{
	// It's hide
	if ( IsHidden( ) )
		return;

	BaseClass::Tick( tick, elapse );
}

_GUI_TESTPOINT_RESULT_TYPE GUIApplication::PointInControl( const Vector2& position, const Matrix3& transform, Vector2* relative_position )
{
	return _GTRT_IN;
}

_ubool GUIApplication::RegionInControl( const RectF& region, const Matrix3& transform )
{
	return _true;
}

_void GUIApplication::Render( IObject* viewport, const Matrix3& transform, const Color& color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test )
{
	// Skip for all model controls, all will be draw mModalGUIApplications of GUIModule
	if ( GetStatesEx( ).HasFlags( _GUI_STATE_EX_MODAL ) )
		return;

	BaseClass::Render( viewport, transform, color, clip_rect, in_clip_state, skip_region_test );
}

_ubool GUIApplication::DoTick( ) const
{
	// It's hide
	if ( IsHidden( ) )
		return _false;

	return BaseClass::DoTick( );
}

_ubool GUIApplication::SetControlModal( WStringPtr name )
{
	IGUIObject* gui_object = SearchControlByName( name, _false, _false );
	if ( gui_object == _null )
		return _false;

	gui_object->GetComponentState( )->SetModal( _true );

	return _true;
}

_void GUIApplication::ShowControl( WStringPtr name, _ubool show )
{
	IGUIObject* gui_object = SearchControlByName( name, _false, _false );
	if ( gui_object != _null )
		gui_object->GetComponentState( )->SetVisible( show, _false, show );
}

_void GUIApplication::ShowControlExclusively( WStringPtr name, _ubool skip_model )
{
	for ( IGUIObject* gui_object = FirstChildObject( ); gui_object != _null; gui_object = gui_object->NextObject( ) )
	{
		if ( skip_model && gui_object->GetComponentState( )->IsModal( ) )
			continue;

		if ( gui_object->GetResName( ) == name )
			gui_object->GetComponentState( )->SetVisible( _true, _false, _true );
		else
			gui_object->GetComponentState( )->SetVisible( _false, _false, _false );
	}
}

_void GUIApplication::HideAllChildControls( _ubool skip_model ) 
{
	for ( IGUIObject* gui_object = FirstChildObject( ); gui_object != _null; gui_object = gui_object->NextObject( ) )
	{
		if ( skip_model && gui_object->GetComponentState( )->IsModal( ) )
			continue;

		gui_object->GetComponentState( )->SetVisible( _false, _false, _false );
	}
}

_ubool GUIApplication::MoveControl( WStringPtr name, WStringPtr parent_name )
{
	IGUIObject* src_obj = SearchControlByName( name, _false, _false );
	if ( src_obj == _null )
		return _false;

	IGUIObject* target_parent_obj = SearchControlByName( parent_name, _false, _false );
	if ( target_parent_obj == _null )
		return _false;

	target_parent_obj->InsertNextObject( src_obj );

	return _true;
}

_ubool GUIApplication::MoveControlToTail( WStringPtr name )
{
	IGUIObject* gui_object = SearchControlByName( name, _false, _false );
	if ( gui_object == _null )
		return _false;

	gui_object->MoveToTail( );

	return _true;
}
