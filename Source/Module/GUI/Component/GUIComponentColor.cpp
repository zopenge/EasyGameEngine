//! @file     GUIComponentColor.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGUI.h"

//----------------------------------------------------------------------------
// GUIComponentColor Implementation
//----------------------------------------------------------------------------

GUIComponentColor::GUIComponentColor( IGUIObject* gui_object ) : BaseClass( gui_object )
{
}

GUIComponentColor::~GUIComponentColor( )
{
}

IObject* GUIComponentColor::CloneTo( _void* arguments ) const
{
	IGUIObject* gui_object = (IGUIObject*)arguments;
	EGE_ASSERT( gui_object != _null );

	GUIComponentColor* component	= new GUIComponentColor( gui_object );
	component->CopyFrom( this );
	component->mColor				= mColor;

	return component;
}

_ubool GUIComponentColor::Import( ISerializableNode* node )
{
	if ( node == _null )
		return _false;

	node->Read( L"r", L"g", L"b", L"a", mColor );
	node->Read( L"color", mColor );

	return _true;
}

_ubool GUIComponentColor::Export( ISerializableNode* node ) const
{
	if ( node == _null )
		return _false;

	if ( node->Write( L"color", mColor ) == _false )
		return _false;

	return _true;
}

_ubool GUIComponentColor::IsResident( ) const
{
	return _true;
}

_ubool GUIComponentColor::HandleEvent( const EventBase& event, const FlagsObject& flags )
{
	return _false;
}
