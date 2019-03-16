//! @file     EGEInput.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#ifndef _EGE_INPUT_PCH_
#define _EGE_INPUT_PCH_

// Standard Files
#include <math.h>

// Windows Platform
#if defined _PLATFORM_WINDOWS_

	#include "Platform/OS/windows/Win32Headers.h"

// IOS Platform
#elif defined _PLATFORM_IOS_

#endif

// EasyGameEngine Headers
#include "EGE_Always.h"
#include "EGE_Engine.h"
#include "Interface/Module/EGE_Input.h"

// Log Files
#undef DEFINE_MODULE 
#define DEFINE_MODULE gInputModule->
#include "EGE_Logs.h"

//!	The joystick devices declaration
enum { _MAX_JOYSTICK_NUMBER = 4 };
typedef EGE::FixedArray< EGE::IJoystickDevice*, _MAX_JOYSTICK_NUMBER > JoystickDeviceArray;

//!	The global variables
extern JoystickDeviceArray		gJoystickDeviceArray;
extern EGE::IKeyboardDevice*	gKeyboardDevice;
extern EGE::IMouseDevice*		gMouseDevice;
extern EGE::IInputModule*		gInputModule;

// Input Template Files
#include "Module/Input/Template/TInputDevice.h"

// Input Files
#include "Module/Input/InputVersion.h"
#include "Module/Input/KeyboardDevice.h"
#include "Module/Input/MouseDevice.h"
#include "Module/Input/JoystickDevice.h"
#include "Module/Input/InputModule.h"

// Null Classes
#include "Module/Input/InputNullClasses.h"

// The null and dummy global variables
static EGE::NullKeyboardDevice	sNullKeyboardDevice;
static EGE::NullMouseDevice		sNullMouseDevice;
static EGE::NullInputModule		sNullInputModule;

// Using namespace here to prevent some name conflict 
using namespace EGE;

#endif // _EGE_INPUT_PCH_