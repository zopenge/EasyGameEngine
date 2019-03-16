//! @file     EasyGameEngine.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

// Core Headers
#include "EGE_Always.h"
#include "EGE_Engine.h"
#include "EGE_Modules.h"

// Module Files
#include "Interface/Module/EGE_Storage.h" 
#include "Interface/Module/EGE_Network.h" 
#include "Interface/Module/EGE_Database.h" 
#include "Interface/Module/EGE_Physx.h" 
#include "Interface/Module/EGE_Graphic.h" 
#include "Interface/Module/EGE_Sound.h" 
#include "Interface/Module/EGE_Script.h" 

// Platform Main Configure
#if defined _PLATFORM_WINDOWS_
	#include "Main/Windows/EGE_WindowsMain.h"
#elif defined _PLATFORM_IOS_
	#include "Main/IOS/EGE_IOSMain.h"
#elif defined _PLATFORM_OSX_
	#include "Main/OSX/EGE_OSXMain.h"
#elif defined _PLATFORM_ANDROID_
	#include "Main/Android/EGE_AndroidMain.h"
#elif defined _PLATFORM_CHROME_
	#include "Main/Chrome/EGE_ChromeMain.h"
#endif

using namespace EGE;

#ifdef _PLATFORM_WINDOWS_

// Output some useful information
#if (_ENABLE_LOG_DEBUG == 1)
#pragma message( ">>> Enable log debug" )
#else
#pragma message( ">>> Disable log debug" )
#endif

#if (_ENABLE_LOG_TRACE == 1)
#pragma message( ">>> Enable log trace" )
#else
#pragma message( ">>> Disable log trace" )
#endif

#if (_ENABLE_LOG_ERROR == 1)
#pragma message( ">>> Enable log error" )
#else
#pragma message( ">>> Disable log error" )
#endif

#if (_ENABLE_LOG_WARNING == 1)
#pragma message( ">>> Enable log warning" )
#else
#pragma message( ">>> Disable log warning" )
#endif

#endif