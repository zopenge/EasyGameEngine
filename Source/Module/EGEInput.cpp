//! @file     EGEInput.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEInput.h"

JoystickDeviceArray	gJoystickDeviceArray;
IKeyboardDevice*	gKeyboardDevice	= &sNullKeyboardDevice;
IMouseDevice*		gMouseDevice	= &sNullMouseDevice;
IInputModule*		gInputModule	= &sNullInputModule;

//----------------------------------------------------------------------------
// DllMain Implementation
//----------------------------------------------------------------------------

#ifdef _EGE_DLL

_long __stdcall DllMain( _handle instance, _dword reason, _void* reserved )
{
	return 1;
}

#endif

//----------------------------------------------------------------------------
// Interface Accessors Implementation
//----------------------------------------------------------------------------

#undef GetInputModule
EGE_EXTERN_DLL_OUT_FUNC IInputModule* GetInputModule( )
{
	return gInputModule;
}

#undef GetMouseDevice
EGE_EXTERN_DLL_OUT_FUNC IMouseDevice* GetMouseDevice( )
{
	return gMouseDevice;
}

#undef GetKeyboardDevice
EGE_EXTERN_DLL_OUT_FUNC IKeyboardDevice* GetKeyboardDevice( )
{
	return gKeyboardDevice;
}

#undef GetJoystickDeviceNumber
EGE_EXTERN_DLL_OUT_FUNC _dword GetJoystickDeviceNumber( )
{
	return gJoystickDeviceArray.Number( );
}

#undef GetJoystickDeviceByIndex
EGE_EXTERN_DLL_OUT_FUNC IJoystickDevice* GetJoystickDeviceByIndex( _dword index )
{
	if ( index >= gJoystickDeviceArray.Number( ) )
		return _null;

	return gJoystickDeviceArray[ index ];
}

#undef CreateInputModule
EGE_EXTERN_DLL_OUT_FUNC _ubool CreateInputModule( _handle app_handle )
{
#ifdef _PLATFORM_IOS_
	return _false;
#else
	// Create module
	typedef PassRefPtr< InputModule > InputModulePassRef;
	InputModulePassRef module = new InputModule( );

	// Register it to module manager
	GetModuleManager( )->RegisterModule( module.GetPtr( ), EGE_INPUT_MODULE_PRIORIY );

	// Update the global module
	gInputModule = module.GetPtr( );

	// Initialize module
	return module->Initialize( app_handle );
#endif
}