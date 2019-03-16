//! @file     IGUIComponentState.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGUIComponentState
//----------------------------------------------------------------------------

class IGUIComponentState : public IGUIComponent
{
public:
	CLASS_NAME_DECL( IGUIComponentState )

public:
	//!	Set the state.
	//!	@param		state	The object state.
	//!	@return		none.
	virtual _void SetState( _GUI_OBJECT_STATE state ) PURE;
	//!	Get the state.
	//!	@param		none.
	//!	@return		The object state.
	virtual _GUI_OBJECT_STATE GetState( ) const PURE;
	//!	state1 is state2's base state.
	//!	@param		none.
	//!	@return		The state1 is state2's base state.
	virtual _ubool IsBaseGUIState( _GUI_OBJECT_STATE state1, _GUI_OBJECT_STATE state2 ) const PURE;

	virtual _ubool ReplayOnChangedState( AStringPtr component_name, _GUI_OBJECT_STATE prev_state, _GUI_OBJECT_STATE curr_state ) const PURE;

	//!	Access the extend states.
	//!	@param		none.
	//!	@return		The object extend states, @see _GUI_OBJECT_STATE_EX.
	virtual FlagsObject& GetStatesEx( ) PURE;
	//!	Get the extend states.
	//!	@param		none.
	//!	@return		The object extend states, @see _GUI_OBJECT_STATE_EX.
	virtual const FlagsObject& GetStatesEx( ) const PURE;

	//!	Access the attributes.
	//!	@param		none.
	//!	@return		The object attributes, @see _GUI_ATTRIBUTE.
	virtual FlagsObject& GetAttributes( ) PURE;
	//!	Get the attributes.
	//!	@param		none.
	//!	@return		The object attributes, @see _GUI_ATTRIBUTE.
	virtual const FlagsObject& GetAttributes( ) const PURE;

	//!	Enable.
	//!	@param		enable		enable or not.
	//!	@return		none.
	virtual _void Enable( _ubool enable = _true, _ubool deep = _false ) PURE;
	//!	Check whether it's active or not.
	//!	@param		none.
	//!	@return		True indicates it's active.
	virtual _ubool IsEnable( ) const PURE;

	//!	Show/Hide.
	//!	@param		show		True indicates show it, otherwise hide it.
	//!	@param		force		True indicates make sure it will be seen, Only works with show operation ( it will show all parent GUI objects ).
	//!	@return		none.
	virtual _void SetVisible( _ubool show, _ubool force = _false, _ubool deep = _false ) PURE;
	//!	Check whether it is visible or not.
	//!	@param		none.
	//!	@return		True indicates it's visible.
	virtual _ubool IsVisiable( ) const PURE;

	//!	Check on/ check off.
	//!	@param		check		True indicates check on it, otherwise check off it.
	//!	@return		none.
	virtual _void Check( _ubool check, _ubool handle_event = _false, _ubool force = _false ) PURE;
	//!	Check whether it is checked or not.
	//!	@param		none.
	//!	@return		True indicates checked.
	virtual _ubool IsCheck( ) const PURE;

	//!	Set modal status.
	//!	@param		checkable	True indicates it's checkable.
	//!	@return		none.
	virtual _void SetCheckable( _ubool checkable ) PURE;
	//!	Check whether it is checkable.
	//!	@param		none.
	//!	@return		True indicates 's checkable.
	virtual _ubool IsCheckable( ) const PURE;

	//!	Set radio status.
	//!	@param		radio	True indicates it's radio.
	//!	@return		none.
	virtual _void SetRadio( _ubool radio ) PURE;
	//!	Check whether it is radio.
	//!	@param		none.
	//!	@return		True indicates it's radio.
	virtual _ubool IsRadio( ) const PURE;

	//!	Set modal status.
	//!	@param		modal		True indicates it's modal.
	//!	@return		none.
	virtual _void SetModal( _ubool modal ) PURE;
	//!	Check whether it is modal.
	//!	@param		none.
	//!	@return		True indicates is modal.
	virtual _ubool IsModal( ) const PURE;
	virtual _void SetTempModal( _ubool modal ) PURE;
	virtual _ubool IsTempModal( ) const PURE;

	virtual _void SetEditBox( _ubool edit ) PURE;
	//!	Check whether it is edit box or not.
	//!	@param		none.
	//!	@return		True indicates edit box.
	virtual _ubool IsEditBox( ) const PURE;

	//!	Set delay load.
	//!	@param		delay	True indicates it's delay load.
	//!	@return		none.
	virtual _void DelayLoad( _ubool delay ) PURE;
	//!	Check whether it is DelayLoad.
	//!	@param		none.
	//!	@return		True indicates delay load.
	virtual _ubool IsDelayLoad( ) const PURE;

	//!	Pause.
	//!	@param		pause		True indicates it's pause.
	//!	@return		none.
	virtual _void Pause( _ubool pause ) PURE;
	//!	Check whether it's pausing.
	//!	@param		none.
	//!	@return		True indicates it's pausing.
	virtual _ubool IsPausing( ) const PURE;

	//!	Set cancel button.
	//!	@param		modal		True indicates it's cancel button.
	//!	@return		none.
	virtual _void SetCancelButton( _ubool cancel ) PURE;
	//!	Check whether it is cancel button.
	//!	@param		none.
	//!	@return		True indicates is cancel button.
	virtual _ubool IsCancelButton( ) const PURE;
	//!	Set default button.
	//!	@param		modal		True indicates it's default button.
	//!	@return		none.
	virtual _void SetDefaultButton( _ubool isdefault ) PURE;
	//!	Check whether it is default button.
	//!	@param		none.
	//!	@return		True indicates is default button.
	virtual _ubool IsDefaultButton( ) const PURE;

	virtual _void Set3DGUIObjectInUI( _ubool is3d ) PURE;
	virtual _ubool Is3DGUIObjectInUI( ) const PURE;
	virtual _void Set3DGUIObjectInScene( _ubool is3d ) PURE;
	virtual _ubool Is3DGUIObjectInScene( ) const PURE;
	virtual _void SetTestPointAlways( _ubool check ) PURE;
	virtual _ubool IsTestPointAlways( ) const PURE;
	virtual _void SetManualCheck(_ubool manualcheck) PURE;
	virtual _ubool IsManualCheck() const PURE;
};

}