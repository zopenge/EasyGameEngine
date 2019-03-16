//! @file     ScriptLibraryConfig.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

// Windows platform
#ifdef _PLATFORM_WINDOWS_
	// Use python library
	#define _SCRIPT_USE_PYTHON_ 0
	// Use java script core library
	#define _SCRIPT_USE_JAVA_SCRIPT_CORE_ 0
	// Use google v8 library
	#define _SCRIPT_USE_GOOGLE_V8_ 0
	// Use spider monkey
	#define _SCRIPT_USE_SPIDER_MONKEY_ 0
	// Use lua
	#define _SCRIPT_USE_LUA_ 1
// Android platform
#elif _PLATFORM_ANDROID_
	// Use python library
	#define _SCRIPT_USE_PYTHON_ 0
	// Use java script core library
	#define _SCRIPT_USE_JAVA_SCRIPT_CORE_ 0
	// Use google v8 library
	#define _SCRIPT_USE_GOOGLE_V8_ 0
	// Use spider monkey
	#define _SCRIPT_USE_SPIDER_MONKEY_ 0
	// Use lua
	#define _SCRIPT_USE_LUA_ 1
// IOS platform
#elif _PLATFORM_IOS_
	// Use python library
	#define _SCRIPT_USE_PYTHON_ 0
	// Use java script core library
	#define _SCRIPT_USE_JAVA_SCRIPT_CORE_ 0
	// Use google v8 library
	#define _SCRIPT_USE_GOOGLE_V8_ 0
	// Use spider monkey
	#define _SCRIPT_USE_SPIDER_MONKEY_ 0
	// Use lua
	#define _SCRIPT_USE_LUA_ 1
// OSX platform
#elif _PLATFORM_OSX_
	// Use python library
	#define _SCRIPT_USE_PYTHON_ 0
	// Use java script core library
	#define _SCRIPT_USE_JAVA_SCRIPT_CORE_ 0
	// Use google v8 library
	#define _SCRIPT_USE_GOOGLE_V8_ 0
	// Use spider monkey
	#define _SCRIPT_USE_SPIDER_MONKEY_ 0
	// Use lua
	#define _SCRIPT_USE_LUA_ 1
// Chrome platform
#elif _PLATFORM_CHROME_
	// Use python library
	#define _SCRIPT_USE_PYTHON_ 0
	// Use java script core library
	#define _SCRIPT_USE_JAVA_SCRIPT_CORE_ 0
	// Use google v8 library
	#define _SCRIPT_USE_GOOGLE_V8_ 0
	// Use spider monkey
	#define _SCRIPT_USE_SPIDER_MONKEY_ 0
	// Use lua
	#define _SCRIPT_USE_LUA_ 1
#endif

// We use java script
#if (_SCRIPT_USE_JAVA_SCRIPT_CORE_ == 1) || (_SCRIPT_USE_GOOGLE_V8_ == 1) || (_SCRIPT_USE_SPIDER_MONKEY_ == 1)
	#define _SCRIPT_USE_JS_ 1
#endif

#if (_SCRIPT_USE_PYTHON_ + _SCRIPT_USE_JAVA_SCRIPT_CORE_ + _SCRIPT_USE_GOOGLE_V8_ + _SCRIPT_USE_SPIDER_MONKEY_ + _SCRIPT_USE_LUA_) == 0
	#error "We must use 1 script system at least"
#elif (_SCRIPT_USE_PYTHON_ + _SCRIPT_USE_JAVA_SCRIPT_CORE_ + _SCRIPT_USE_GOOGLE_V8_ + _SCRIPT_USE_SPIDER_MONKEY_ + _SCRIPT_USE_LUA_) > 1
	#error "We only can use 1 script system in the same time"
#endif

// Use the old spider monkey
#if defined(_SCRIPT_USE_SPIDER_MONKEY_) && defined(_PLATFORM_ANDROID_)
	#define _SCRIPT_USE_OLD_SPIDER_MONKEY_
#endif