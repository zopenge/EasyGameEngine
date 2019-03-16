//! @file     TJoystick.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TJoystick
//----------------------------------------------------------------------------

template< typename Type >
class TJoystick : public INTERFACE_OBSERVER_IMPL( Type )
{
protected:
	//!	The joystick ID
	_dword					mID;

	//!	The ranges
	DwordRange				mXRange;
	DwordRange				mYRange;

	//!	The notifier
	IJoystickNotifierRef	mNotifier;

protected:
	//!	When dispatch key event.
	virtual _ubool OnDispatchKeyEvent( _handle key_event ) PURE;
	//!	When dispatch generic motion event.
	virtual _ubool OnDispatchGenericMotionEvent( _handle key_event ) PURE;
	//!	When move.
	virtual _void OnMove( const PointI& pos ) PURE;
	//!	When z-move.
	virtual _void OnZMove( _int z_pos ) PURE;
	//!	When button up.
	virtual _void OnButtonUp( _dword flags ) PURE;
	//!	When button down.
	virtual _void OnButtonDown( _dword flags ) PURE;

protected:
	TJoystick( _dword id, const DwordRange& x_range, const DwordRange& y_range );
	virtual ~TJoystick( );

// IObserver Interface
public:
	virtual _void					Notify( const EventBase& event, const IObject* object, const IObservable* generator ) override;

// IJoystick Interface
public:
	virtual _dword					GetID( ) const override;

	virtual _void					SetNotifier( IJoystickNotifier* notifier ) override;
	virtual IJoystickNotifierRef	GetNotifier( ) override;
};

//----------------------------------------------------------------------------
// TJoystick Implementation
//----------------------------------------------------------------------------

template< typename Type >
TJoystick< Type >::TJoystick( _dword id, const DwordRange& x_range, const DwordRange& y_range )
{
	mID			= id;

	mXRange		= x_range;
	mYRange		= y_range;

	mNotifier	= &NullEngine::GetInstance( ).GetJoystickNotifier( );
}

template< typename Type >
TJoystick< Type >::~TJoystick( )
{

}

template< typename Type >
_void TJoystick< Type >::Notify( const EventBase& event, const IObject* object, const IObservable* generator )
{
	switch ( event.mEventID )
	{
		case _EVENT_DISPATCHED_KEY:
		{
			const EventDispatchedKey& msg = (const EventDispatchedKey&) event;

			// Force to modify it
			((EventDispatchedKey&) msg).mHandled = OnDispatchKeyEvent( msg.mEvent );
		}
		break;

		case _EVENT_DISPATCHED_GENERIC_MOTION:
		{
			const EventDispatchedGenericMotion& msg = (const EventDispatchedGenericMotion&) event;

			// Force to modify it
			((EventDispatchedGenericMotion&) msg).mHandled = OnDispatchGenericMotionEvent( msg.mEvent );
		}
		break;

		case _EVENT_JOYSTICK_MOVE:
		{
			const EventJoystickMove& msg = (const EventJoystickMove&) event;

			if ( msg.mID == mID )
				OnMove( msg.mPosition );
		}
		break;

		case _EVENT_JOYSTICK_ZMOVE:
		{
			const EventJoystickZMove& msg = (const EventJoystickZMove&) event;

			if ( msg.mID == mID )
				OnZMove( msg.mZPosition );
		}
		break;

		case _EVENT_JOYSTICK_BUTTON_UP:
		{
			const EventJoystickButtonUp& msg = (const EventJoystickButtonUp&) event;

			if ( msg.mID == mID )
				OnButtonUp( msg.mFlags );
		}
		break;

		case _EVENT_JOYSTICK_BUTTON_DOWN:
		{
			const EventJoystickButtonDown& msg = (const EventJoystickButtonDown&) event;

			if ( msg.mID == mID )
				OnButtonDown( msg.mFlags );
		}
		break;

		default:
			break;
	}
}

template< typename Type >
_dword TJoystick< Type >::GetID( ) const
{
	return mID;
}

template< typename Type >
_void TJoystick< Type >::SetNotifier( IJoystickNotifier* notifier )
{
	if ( notifier == _null )
		mNotifier = &NullEngine::GetInstance( ).GetJoystickNotifier( );
	else
		mNotifier = notifier;
}

template< typename Type >
IJoystickNotifierRef TJoystick< Type >::GetNotifier( )
{
	return mNotifier;

}

}