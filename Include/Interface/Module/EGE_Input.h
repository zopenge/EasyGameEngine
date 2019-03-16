//! @file     EGE_Input.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

namespace EGE
{

// Input Interface
REF_OBJECT_DECL(IInputDevice);
REF_OBJECT_DECL(IKeyboardDevice);
REF_OBJECT_DECL(IMouseDevice);
REF_OBJECT_DECL(IJoystickDevice);
REF_OBJECT_DECL(IInputModule);

}

// Module-Input Interface Files
#include "Interface/Module/Input/IInputDevice.h"
#include "Interface/Module/Input/IKeyboardDevice.h"
#include "Interface/Module/Input/IMouseDevice.h"
#include "Interface/Module/Input/IJoystickDevice.h"
#include "Interface/Module/Input/IInputModule.h"
#include "Interface/Module/Entries/EGE_InputEntry.h"