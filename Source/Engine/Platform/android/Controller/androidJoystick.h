//! @file     androidJoystick.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// androidJoystick
//----------------------------------------------------------------------------

class androidJoystick : public TJoystick< IJoystick >
{
private:
	typedef TJoystick< IJoystick > BaseClass;

private:
	JNIObject&	mJNIController;

// TJoystick Interface
private:
	virtual _ubool	OnDispatchKeyEvent( _handle key_event ) override;
	virtual _ubool	OnDispatchGenericMotionEvent( _handle key_event ) override;
	virtual _void	OnMove( const PointI& pos ) override;
	virtual _void	OnZMove( _int z_pos ) override;
	virtual _void	OnButtonUp( _dword flags ) override;
	virtual _void	OnButtonDown( _dword flags ) override;

public:
	androidJoystick( _dword id, const DwordRange& x_range, const DwordRange& y_range, JNIObject& jni_controller );
	virtual ~androidJoystick( );

// IJoystick Interface
public:
};

}