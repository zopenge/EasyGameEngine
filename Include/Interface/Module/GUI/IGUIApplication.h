//! @file     IGUIApplication.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGUIApplication
//----------------------------------------------------------------------------

class IGUIApplication : public IGUIContainer
{
public:
	//!	Set the control's modal flag.
	//! @param		name		The control name.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool SetControlModal( WStringPtr name ) PURE;

	//! Show/Hide control.
	//!	@param		name		The control name.
	//! @param		show		True indicates show it, otherwise indicates hide it.
	//! @return		none.
	virtual _void ShowControl( WStringPtr name, _ubool show ) PURE;
	//! Show control, but hide all its brother controls.
	//!	@param		name		The control name.
	//!	@param		skip_model	True indicates skip all model controls.
	//! @return		none.
	virtual _void ShowControlExclusively( WStringPtr name, _ubool skip_model = _true ) PURE;
	//!	Hide all child controls.
	//!	@param		skip_model	True indicates skip all model controls.
	//!	@return		none.
	virtual _void HideAllChildControls( _ubool skip_model = _true ) PURE;

	//! Move control.
	//! @param		name		The control name.
	//! @param		parent_name	The target parent control name.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool MoveControl( WStringPtr name, WStringPtr parent_name ) PURE;
	//! Move control to tail.
	//! @param		name		The control name.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool MoveControlToTail( WStringPtr name ) PURE;

};

}