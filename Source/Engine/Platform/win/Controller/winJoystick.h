//! @file     winJoystick.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// winJoystick
//----------------------------------------------------------------------------

class winJoystick : public TJoystick< IJoystick >
{
private:
	typedef TJoystick< IJoystick > BaseClass;

private:
	//!	The last button states
	_dword	mLastButtonStates;
	//! The last pov
	_dword	mLastPOV;

private:
	//!	Handle key.
	_void HandleKey( _dword buttons, _dword flag, _dword key_code );

// TJoystick Interface
private:
	virtual _ubool	OnDispatchKeyEvent( _handle key_event ) override;
	virtual _ubool	OnDispatchGenericMotionEvent( _handle key_event ) override;
	virtual _void	OnMove( const PointI& pos ) override;
	virtual _void	OnZMove( _int z_pos ) override;
	virtual _void	OnButtonUp( _dword flags ) override;
	virtual _void	OnButtonDown( _dword flags ) override;

public:
	winJoystick( _dword id, const DwordRange& x_range, const DwordRange& y_range );
	virtual ~winJoystick( );

// IJoystick Interface
public:
};

}