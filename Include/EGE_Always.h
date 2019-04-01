#pragma once

// Platform Config Files
#include "Platform/PlatformConfig.h"

// Standard Files
#if defined(_PLATFORM_WINDOWS_)
#	include "Platform/OS/windows/Win32Headers.h"
#	include "Platform/OS/windows/Win32Macros.h"
#elif defined(_PLATFORM_IOS_)
// Only work for OBJ-C mode.
#	ifdef __OBJC__
#		import <Availability.h>
#		import <Foundation/Foundation.h>
#	endif
#elif defined(_PLATFORM_ANDROID_)
#	include <jni.h>
#endif
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <typeinfo>

// External Files
#include "External/auto_index_MACROS.h"

// EasyGameEngine Configures
#include "EGE_Compile.h"
#include "EGE_Config.h"

// Type Define Headers
#include "EGE_Typedef.h"

// EasyGameEngine Basic Headers
#include "EGE_Const.h"
#include "EGE_Template.h"
// EasyGameEngine Structure Headers
#include "EGE_Struct.h"

// Network OS Header
#include "Platform/OS/NetworkOSHeader.h"

// The Platform Files
#include "EGE_Platform.h"
