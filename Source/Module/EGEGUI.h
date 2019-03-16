//! @file     EGEGUI.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#ifndef _EGE_GUI_PCH_
#define _EGE_GUI_PCH_

// Windows Platform
#if defined _PLATFORM_WINDOWS_

	#include "Platform/OS/windows/Win32Headers.h"
	#include "Platform/OS/windows/Win32Macros.h"

// IOS Platform
#elif defined _PLATFORM_IOS_

// Android Platform
#elif defined _PLATFORM_ANDROID_

#endif

#include "EGE_Always.h"
#include "EGE_Engine.h"
#include "EGE_Modules.h"
#include "Interface/Module/EGE_GUI.h"

// Log Files
#undef DEFINE_MODULE 
#define DEFINE_MODULE gGUIModule->
#include "EGE_Logs.h"

// Null Classes
#include "Module/GUI/GUINullClasses.h"

// Global variables
extern EGE::IGUIModule*				gGUIModule;
extern EGE::IGUIResourceManager*	gGUIResourceManager;

// GUI Component Files
#include "Module/GUI/Component/GUIComponentState.h"
#include "Module/GUI/Component/GUIComponent3DRender.h"
#include "Module/GUI/Component/GUIComponentColor.h"
#include "Module/GUI/Component/GUILocationInfo.h"
#include "Module/GUI/Component/GUIComponentPosition.h"
#include "Module/GUI/Component/GUIComponentEventHooker.h"
#include "Module/GUI/Component/GUIComponentAnimation.h"
#include "Module/GUI/Component/GUIComponentClick.h"
#include "Module/GUI/Component/GUIComponentGroup.h"

// GUI Files
#include "Module/GUI/GUIVersion.h"
#include "Module/GUI/GUIComponentUtils.h"
#include "Module/GUI/GUIApplication.h"
#include "Module/GUI/GUIResourceManager.h"
#include "Module/GUI/GUIRenderer.h"
#include "Module/GUI/GUIModule.h"

// Using namespace here to prevent some name conflict 
using namespace EGE;

#endif // _EGE_GUI_PCH_