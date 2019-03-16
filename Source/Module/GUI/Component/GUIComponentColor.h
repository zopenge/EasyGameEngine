//! @file     GUIComponentColor.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GUIComponentColor
//----------------------------------------------------------------------------

class GUIComponentColor : public TGUIComponent< TColorObject< IGUIComponentColor > >
{
public:
	RTTI_CLASS_WITH_ARGUMENTS_DECL( GUIComponentColor, IGUIComponentColor, IGUIObject* )

public:
	typedef TGUIComponent< TColorObject< IGUIComponentColor > > BaseClass;

public:
	GUIComponentColor( IGUIObject* gui_object );
	virtual ~GUIComponentColor( );

// IObject Interface
public:
	virtual IObject*	CloneTo( _void* arguments ) const override;

// ISerializable Interface
public:
	virtual _ubool		Import( ISerializableNode* node ) override;
	virtual _ubool		Export( ISerializableNode* node ) const override;

// IGUIComponent Interface
public:
	virtual _ubool		IsResident( ) const override;

	virtual _ubool		HandleEvent( const EventBase& event, const FlagsObject& flags ) override;

// IGUIComponentColor Interface
public:
	
};

//----------------------------------------------------------------------------
// GUIComponentColor Implementation
//----------------------------------------------------------------------------

}