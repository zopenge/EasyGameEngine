//! @file     GUIComponentClick.h
//! @author   Foreven
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GUIComponentClick
//----------------------------------------------------------------------------

class GUIComponentClick : public TGUIComponent< IGUIComponentClick >
{
public:
	RTTI_CLASS_WITH_ARGUMENTS_DECL( GUIComponentClick, IGUIComponentClick, IGUIObject* )

public:
	_GUICOMPONENT_ENABLE_HANDLE_EVENT( )
	_GUICOMPONENT_ENABLE_IS_HANDLE_EVENT( )

public:
	typedef TGUIComponent< IGUIComponentClick > BaseClass;

public:
	GUIComponentClick( IGUIObject* gui_object );
	virtual ~GUIComponentClick( );

protected:
	Vector2			mTouchBeginRelativeOffset;

// IObject Interface
public:
	virtual IObject*	CloneTo( _void* arguments ) const override;

// ISerializable Interface
public:
	virtual _ubool		Import( ISerializableNode* node ) override;
	virtual _ubool		Export( ISerializableNode* node ) const override;

// IGUIComponent Interface
public:
	virtual _ubool		HandleEvent( const EventBase& event, const FlagsObject& flags ) override;

	virtual _ubool		IsHandleEvent( _dword event_id ) const override;

// IFGUIComponent2DGraphic Interface
public:
	virtual	_void		Click( ) override;
};

}