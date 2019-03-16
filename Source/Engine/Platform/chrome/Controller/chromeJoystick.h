//! @file     chromeJoystick.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// chromeJoystick
//----------------------------------------------------------------------------

class chromeJoystick : public TJoystick< IJoystick >
{
private:
	typedef TJoystick< IJoystick > BaseClass;

// TJoystick Interface
private:
	virtual _ubool	OnDispatchKeyEvent( _handle key_event ) override;
	virtual _ubool	OnDispatchGenericMotionEvent( _handle key_event ) override;
	virtual _void	OnMove( const PointI& pos ) override;
	virtual _void	OnZMove( _int z_pos ) override;
	virtual _void	OnButtonUp( _dword flags ) override;
	virtual _void	OnButtonDown( _dword flags ) override;

public:
	chromeJoystick( _dword id, const DwordRange& x_range, const DwordRange& y_range );
	virtual ~chromeJoystick( );

// IJoystick Interface
public:
};

}