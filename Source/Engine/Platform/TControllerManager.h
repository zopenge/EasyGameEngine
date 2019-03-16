//! @file     TControllerManager.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TControllerManager
//----------------------------------------------------------------------------

template< typename Type >
class TControllerManager : public TObject< Type >
{
protected:
	typedef Array< IJoystickPassRef > JoystickArray;

protected:
	//!	The viewbased application
	IViewBasedApp*	mApplication;

	//!	The joysticks
	JoystickArray	mJoysticks;

protected:
	//!	Append joystick.
	_void AppendJoystick( IJoystick* joystick );

protected:
	TControllerManager( );
	virtual ~TControllerManager( );

// IControllerManager Interface
public:
	virtual _void			Finalize( ) override;

	virtual _dword			GetJoystickNumber( ) const override;
	virtual IJoystickRef	GetJoystickByIndex( _dword index ) const override;
	virtual IJoystickRef	GetJoystickByID( _dword id ) const override;
};

//----------------------------------------------------------------------------
// TControllerManager Implementation
//----------------------------------------------------------------------------

template< typename Type >
TControllerManager< Type >::TControllerManager( )
{
	mApplication = _null;
}

template< typename Type >
TControllerManager< Type >::~TControllerManager( )
{
	Finalize( );
}

template< typename Type >
_void TControllerManager< Type >::AppendJoystick( IJoystick* joystick )
{
	WLOG_TRACE_2( L"Add '0x%.8x' joystick(%d)", (_dword) (size_t)joystick, joystick->GetID( ) );

	GetModuleManager( )->RegisterObserver( joystick );

	mJoysticks.Append( joystick );
}

template< typename Type >
_void TControllerManager< Type >::Finalize( )
{
	for ( _dword i = 0; i < mJoysticks.Number( ); i ++ )
		GetModuleManager( )->UnregisterObserver( mJoysticks[i].GetPtr( ) );

	mJoysticks.Clear( _true );
}

template< typename Type >
_dword TControllerManager< Type >::GetJoystickNumber( ) const
{
	return mJoysticks.Number( );
}

template< typename Type >
IJoystickRef TControllerManager< Type >::GetJoystickByIndex( _dword index ) const
{
	return mJoysticks[ index ];
}

template< typename Type >
IJoystickRef TControllerManager< Type >::GetJoystickByID( _dword id ) const
{
	for ( _dword i = 0; i < mJoysticks.Number( ); i ++ )
	{
		if ( mJoysticks[i]->GetID( ) == id )
			return mJoysticks[i];
	}

	return _null;
}

}