//! @file     EGEStorage.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#ifndef _EGE_STORAGE_PCH_
#define _EGE_STORAGE_PCH_

// Windows Platform
#if defined _PLATFORM_WINDOWS_

	#include "Platform/OS/windows/Win32Headers.h"
	#include "Platform/OS/windows/Win32Macros.h"

// IOS Platform
#elif defined _PLATFORM_IOS_

#endif

// EasyGameEngine Headers
#include "EGE_Always.h"
#include "EGE_Engine.h"
#include "EGE_Modules.h"
#include "Interface/Module/EGE_Storage.h"

// Log Files
#undef DEFINE_MODULE 
#define DEFINE_MODULE gStorageModule->
#include "EGE_Logs.h"

// Outside Function Implementations
#include "EGEExterns.h"

// Null Classes
#include "Module/Storage/StorageNullClasses.h"

// Global variables
extern EGE::IStorageModule*	gStorageModule;

// Storage Files
#include "Module/Storage/StorageVersion.h"
#include "Module/Storage/StorageModule.h"

// Using namespace here to prevent some name conflict 
using namespace EGE;

#endif // _EGE_STORAGE_PCH_