//! @file     GUIComponentState.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GUIComponentState
//----------------------------------------------------------------------------

class GUIComponentState : public TGUIComponent< IGUIComponentState >
{
public:
	RTTI_CLASS_WITH_ARGUMENTS_DECL( GUIComponentState, IGUIComponentState, IGUIObject* )

public:
	_GUICOMPONENT_ENABLE_EXPORT( )

public:
	typedef TGUIComponent< IGUIComponentState > BaseClass;

private:
	//!	The object state
	_GUI_OBJECT_STATE	mState;

	//!	The object extend states
	FlagsObject			mStatesEx;
	//!	The object attributes
	FlagsObject			mAttributes;

public:
	GUIComponentState( IGUIObject* gui_object );
	virtual ~GUIComponentState( );

// IObject Interface
public:
	virtual IObject*			CloneTo( _void* arguments ) const override;

// ISerializable Interface
public:
	virtual _ubool				Import( ISerializableNode* node ) override;
	virtual _ubool				Export( ISerializableNode* node ) const override;

// IGUIComponent Interface
public:
	virtual _ubool				IsResident( ) const override;

	virtual _ubool				HandleEvent( const EventBase& event, const FlagsObject& flags ) override;

// IGUIComponentState Interface
public:
	virtual _void				SetState( _GUI_OBJECT_STATE state ) override;
	virtual _GUI_OBJECT_STATE	GetState( ) const override;

	virtual _ubool				IsBaseGUIState( _GUI_OBJECT_STATE state1, _GUI_OBJECT_STATE state2 ) const override;
	virtual _ubool				ReplayOnChangedState( AStringPtr component_name, _GUI_OBJECT_STATE prev_state, _GUI_OBJECT_STATE curr_state ) const override;

	virtual FlagsObject&		GetStatesEx( ) override;
	virtual const FlagsObject&	GetStatesEx( ) const override;
	virtual FlagsObject&		GetAttributes( ) override;
	virtual const FlagsObject&	GetAttributes( ) const override;

	virtual _void				Enable( _ubool enable = _true, _ubool deep = _false ) override;
	virtual _ubool				IsEnable( ) const override;

	virtual _void				SetVisible( _ubool show, _ubool force = _false, _ubool deep = _false ) override;
	virtual _ubool				IsVisiable( ) const override;

	virtual _void				Check( _ubool check, _ubool handle_event = _false, _ubool force = _false ) override;
	virtual _ubool				IsCheck( ) const override;

	virtual _void				SetCheckable( _ubool checkable ) override;
	virtual _ubool				IsCheckable( ) const override;

	virtual _void				SetRadio( _ubool radio ) override;
	virtual _ubool				IsRadio( ) const override;

	virtual _void				SetModal( _ubool modal ) override;
	virtual _ubool				IsModal( ) const override;
	virtual _void				SetTempModal( _ubool modal ) override;
	virtual _ubool				IsTempModal( ) const override;

	virtual _void				SetEditBox( _ubool edit ) override;
	virtual _ubool				IsEditBox( ) const override;

	virtual _void				DelayLoad( _ubool delay ) override;
	virtual _ubool				IsDelayLoad( ) const override;

	virtual _void				Pause( _ubool pause ) override;
	virtual _ubool				IsPausing( ) const override;

	virtual _void				SetCancelButton( _ubool cancel ) override;
	virtual _ubool				IsCancelButton( ) const override;
	virtual _void				SetDefaultButton( _ubool isdefault ) override;
	virtual _ubool				IsDefaultButton( ) const override;
	virtual _void				Set3DGUIObjectInUI( _ubool is3d ) override;
	virtual _ubool				Is3DGUIObjectInUI( ) const override;
	virtual _void				Set3DGUIObjectInScene( _ubool is3d ) override;
	virtual _ubool				Is3DGUIObjectInScene( ) const override;
	virtual _void				SetTestPointAlways( _ubool check ) override;
	virtual _ubool				IsTestPointAlways( ) const override;
	virtual _void				SetManualCheck(_ubool manualcheck) override;
	virtual _ubool				IsManualCheck() const override;
};

//----------------------------------------------------------------------------
// GUIComponentState Implementation
//----------------------------------------------------------------------------

}