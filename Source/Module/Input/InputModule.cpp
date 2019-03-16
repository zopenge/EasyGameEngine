//! @file     InputModule.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEInput.h"

//----------------------------------------------------------------------------
// InputModule Implementation
//----------------------------------------------------------------------------

InputModule::InputModule( ) : BaseClass( L"InputModule", Version( INPUT_FILEVER ) )
{
}

InputModule::~InputModule( )
{
	Finalize( );
}

_ubool InputModule::Initialize( _handle app_handle )
{
	if ( app_handle == _null )
		return _false;

	WLOG_TRACE( L"Create input module ..." );

	// Initialize keyboard
	gKeyboardDevice = new KeyboardDevice( );
	if ( ( (KeyboardDevice*) gKeyboardDevice )->Initialize( ) == _false )
		return _false;

	// Initialize mouse
	gMouseDevice = new MouseDevice( app_handle );
	if ( ( (MouseDevice*) gMouseDevice )->Initialize( ) == _false )
		return _false;

	WLOG_TRACE( L"Create input module DONE" );

	return _true;
}

_void InputModule::Finalize( )
{
	WLOG_TRACE( L"Release input module ..." );

	// Release all joystick devices
	for ( _dword i = 0; i < gJoystickDeviceArray.Number( ); i ++ )
		EGE_RELEASE( gJoystickDeviceArray[i] );

	// Release global modules
	EGE_RELEASE( gKeyboardDevice );
	EGE_RELEASE( gMouseDevice );

	WLOG_TRACE( L"Release input module DONE" );

	// Clear global modules
	gKeyboardDevice = &sNullKeyboardDevice;
	gMouseDevice	= &sNullMouseDevice;
	gInputModule	= &sNullInputModule;
}

_void InputModule::Tick( _time_t tick, _dword elapse )
{
	( (KeyboardDevice*) gKeyboardDevice )->Tick( tick, elapse );
	( (MouseDevice*) gMouseDevice )->Tick( tick, elapse );

	// Update all joysticks
	for ( _dword i = 0; i < gJoystickDeviceArray.Number( ); i ++ )
		( (JoystickDevice*) gJoystickDeviceArray[i] )->Tick( tick, elapse );
}

_void InputModule::HandleMessage( MessageBase& message )
{
	( (KeyboardDevice*) gKeyboardDevice )->HandleMessage( message );
	( (MouseDevice*) gMouseDevice )->HandleMessage( message );

	// Handle all joysticks message
	for ( _dword i = 0; i < gJoystickDeviceArray.Number( ); i ++ )
		( (JoystickDevice*) gJoystickDeviceArray[i] )->HandleMessage( message );
}