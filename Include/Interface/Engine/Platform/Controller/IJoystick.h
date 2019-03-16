//! @file     IJoystick.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IJoystickNotifier
//----------------------------------------------------------------------------

class IJoystickNotifier : public IObject
{
public:
	//!	The key code
	enum _KEYCODE
	{
		_KEYCODE_UNKNOWN,
		_KEYCODE_BUTTON_A,
		_KEYCODE_BUTTON_B,
		_KEYCODE_BUTTON_C,
		_KEYCODE_BUTTON_BACK,
		_KEYCODE_BUTTON_ENTER,
		_KEYCODE_BUTTON_HOME,
		_KEYCODE_BUTTON_L1,
		_KEYCODE_BUTTON_L2,
		_KEYCODE_BUTTON_R1,
		_KEYCODE_BUTTON_R2,
		_KEYCODE_BUTTON_SELECT,
		_KEYCODE_BUTTON_START,
		_KEYCODE_BUTTON_THUMBL,
		_KEYCODE_BUTTON_THUMBR,
		_KEYCODE_BUTTON_VOL_DOWN,
		_KEYCODE_BUTTON_VOL_UP,
		_KEYCODE_BUTTON_X,
		_KEYCODE_BUTTON_Y,
		_KEYCODE_BUTTON_Z,
		_KEYCODE_DOWN,
		_KEYCODE_DOWN_LEFT,
		_KEYCODE_DOWN_RIGHT,
		_KEYCODE_LEFT,
		_KEYCODE_RIGHT, 
		_KEYCODE_UP,
		_KEYCODE_UP_LEFT,
		_KEYCODE_UP_RIGHT,
		_KEYCODE_POV_FORWARD,
		_KEYCODE_POV_RIGHT,
		_KEYCODE_POV_BACKWARD,
		_KEYCODE_POV_LEFT,
	};

public:
	//!	When combined key event start.
	//!	@param		token	The token string.
	//!	@param		id		The joystick ID.
	//!	@return		none.
	virtual _void OnCombKeyEventStart( AStringPtr token, _dword id ) PURE;
	//!	When combined key event end.
	//!	@param		token	The token string.
	//!	@param		id		The joystick ID.
	//!	@return		none.
	virtual _void OnCombKeyEventEnd( AStringPtr token, _dword id ) PURE;

	//!	When key up.
	//!	@param		id			The joystick ID.
	//!	@param		key_code	The key code.
	//!	@return		none.
	virtual _void OnKeyUp( _dword id, _dword key_code ) PURE;
	//!	When key down.
	//!	@param		id			The joystick ID.
	//!	@param		key_code	The key code.
	//!	@return		none.
	virtual _void OnKeyDown( _dword id, _dword key_code ) PURE;

	//!	When left stick changed.
	//!	@param		id			The joystick ID.
	//!	@param		pos			The stick position.
	//!	@return		none.
	virtual _void OnLeftStickChanged( _dword id, const PointF& pos ) PURE;
	//!	When right stick changed.
	//!	@param		id			The joystick ID.
	//!	@param		pos			The stick position.
	//!	@return		none.
	virtual _void OnRightStickChanged( _dword id, const PointF& pos ) PURE;

	virtual _void OnZMoved( _dword id, _float pos ) PURE;
};

//----------------------------------------------------------------------------
// IJoystick
//----------------------------------------------------------------------------

class IJoystick : public IObserver
{
public:
	//!	Get the ID.
	//!	@param		none.
	//!	@return		The ID.
	virtual _dword GetID( ) const PURE;

	//!	Set the notifier.
	//!	@param		notifier	The notifier.
	//!	@return		none.
	virtual _void SetNotifier( IJoystickNotifier* notifier ) PURE;
	//!	Get the notifier.
	//!	@param		none.
	//!	@return		The notifier.
	virtual IJoystickNotifierRef GetNotifier( ) PURE;
};

//----------------------------------------------------------------------------
// IControllerManager
//----------------------------------------------------------------------------

class IControllerManager : public IObject
{
public:
	//!	Initialize.
	//!	@param		application		The application.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Initialize( IViewBasedApp* application ) PURE;
	//!	Finalize.
	//!	@param		none.
	//! @return		none.
	virtual _void Finalize( ) PURE;

	//!	Pause.
	//!	@param		none.
	//!	@return		none.
	virtual _void Pause( ) PURE;
	//!	Resume.
	//!	@param		none.
	//!	@return		none.
	virtual _void Resume( ) PURE;

	//!	Get the joysticks number.
	//!	@param		none.
	//!	@return		The joysticks number.
	virtual _dword GetJoystickNumber( ) const PURE;
	//!	Get the joystick by index.
	//!	@param		index		The index of joystick.
	//!	@return		The joystick.
	virtual IJoystickRef GetJoystickByIndex( _dword index ) const PURE;
	//!	Get the joystick by ID.
	//!	@param		ID			The ID of joystick.
	//!	@return		The joystick.
	virtual IJoystickRef GetJoystickByID( _dword id ) const PURE;
};

}