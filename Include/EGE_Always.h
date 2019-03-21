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
#include "EGE_Values.h"

// Type Define Headers
#include "EGE_Typedef.h"
// Type Define Checker Headers
#include "EGE_TypeChecker.h"

// EasyGameEngine Basic Headers
#include "EGE_Enums.h"
#include "EGE_Memory.h"
#include "EGE_Structs.h"
#include "EGE_Template.h"

// Network OS Header
#include "Platform/OS/NetworkOSHeader.h"

// The Platform Files
#include "EGE_Platform.h"

// Global messages and events
#include "EGE_Events.h"
using namespace EGE::Events;

// Here we make sure the 'wchar_t' is 2 bytes
#ifdef _DEBUG
STATIC_ASSERT(sizeof(wchar_t) == 2, "We use UTF-16 as wchar_t, not UTF-32");
#endif
