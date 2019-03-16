//! @file     EGEDatabase.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#ifndef _EGE_DATABASE_PCH_
#define _EGE_DATABASE_PCH_

// Windows Platform
#if defined _PLATFORM_WINDOWS_

	#include "Platform/OS/windows/Win32Headers.h"
	
	// OTL SDK
	#define OTL_ODBC
	#include "otlv4.h"

// IOS Platform
#elif defined _PLATFORM_IOS_

	#error "We don't support the database module on iphone"

// Android Platform
#elif defined _PLATFORM_ANDROID_

	// OTL SDK
	#define OTL_ODBC_UNIX
	#define OTL_ODBC
	#include "otlv4.h"

#endif

// EasyGameEngine Headers
#include "EGE_Always.h"
#include "EGE_Engine.h"
#include "EGE_Modules.h"
#include "Interface/Module/EGE_Database.h"

// Log Files
#undef DEFINE_MODULE 
#define DEFINE_MODULE gDatabaseModule->
#include "EGE_Logs.h"

// Global variables
extern EGE::IDatabaseModule*	gDatabaseModule;

// Database Files
#include "Module/Database/DatabaseVersion.h"
#include "Module/Database/DatabaseRecord.h"
#include "Module/Database/DatabaseConnection.h"
#include "Module/Database/DatabaseModule.h"

// Null Classes
#include "Module/Database/DatabaseNullClasses.h"

// The null and dummy global variables
static EGE::NullDatabaseModule	sNullDatabaseModule;

// Using namespace here to prevent some name conflict 
using namespace EGE;

#endif _EGE_DATABASE_PCH_