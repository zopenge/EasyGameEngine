//! @file     EGE_Compile.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! @brief    Configure
//! Copyright ...

#pragma once

// Windows Platform
#if defined _PLATFORM_WINDOWS_

// IOS Platform
#elif defined _PLATFORM_IOS_

    #import <targetconditionals.h>

    #if (TARGET_IPHONE_SIMULATOR == 1)
        #define _TARGET_OS_SIMULATOR_ 1
    #else
        #define _TARGET_OS_SIMULATOR_ 0
    #endif

// OSX Platform
#elif defined _PLATFORM_OSX_

	#define _TARGET_OS_SIMULATOR_ 0

// Android Platform
#elif defined _PLATFORM_ANDROID_

	#define _TARGET_OS_SIMULATOR_ 0

// Chrome Platform
#elif defined _PLATFORM_CHROME_

	#define _TARGET_OS_SIMULATOR_ 0

// Auto-Detect Platform
#else

	// Define our windows macro if it's windows platform
	#if defined(WIN32) && !defined(_PLATFORM_WINDOWS_)
	#define _PLATFORM_WINDOWS_
	#endif

	#define _TARGET_OS_SIMULATOR_ 0

#endif

// _EGE_COMPACT_ : True indicates use the minimal compile mode
#if defined(_PLATFORM_ANDROID_) || defined(_PLATFORM_IOS_) || defined(_PLATFORM_CHROME_)
	#define _EGE_COMPACT_ 1
#endif

// Disable some modules when it's compact mode
#if (_EGE_COMPACT_ == 1)
	// Engine
	#define _EGE_DISABLE_FLAC_FILE_ // Disable FLAC file
	#define _EGE_DISABLE_MIDI_FILE_ // Disable MIDI file
	#define _EGE_DISABLE_CSV_FILE_ // Disable CSV file
	#define _EGE_DISABLE_SPEEX_FILE_ // Disable SPEEX file
	#define _EGE_DISABLE_HTML_FILE_ // Disable HTML file
#endif

// Turn off STL debug iterators in release build
#ifndef _DEBUG
	#define _SECURE_SCL 0
#endif

// The log features
#ifdef _DEBUG
	#define _ENABLE_LOG_DEBUG 1
	#define _ENABLE_LOG_TRACE 1
	#define _ENABLE_LOG_WARNING 1
	#define _ENABLE_LOG_ERROR 1
	#define _ENABLE_LOG_FATAL 1
	#define _ENABLE_DEBUG_STRING 1
#else
	#define _ENABLE_LOG_DEBUG 1
	#define _ENABLE_LOG_TRACE 1
	#define _ENABLE_LOG_WARNING 1
	#define _ENABLE_LOG_ERROR 1
	#define _ENABLE_LOG_FATAL 1
	#define _ENABLE_DEBUG_STRING 1
#endif

// Some features on platforms
#if _PLATFORM_ANDROID_
	#define _ANDROID_SKIP_CRACKER_CHECK 0
#endif

// 64 Bits platform check
#if defined(_PLATFORM_ANDROID_)
	#if defined(__aarch64__) || defined(__x86_64__)
		#define _PLATFORM_ARCH_64 1
	#else
		#define _PLATFORM_ARCH_32 1
	#endif
#elif defined(_PLATFORM_IOS_)
	#if defined(__LP64__) || defined(__arm64__) || defined(__x86_64__)
		#define _PLATFORM_ARCH_64 1
	#else
		#define _PLATFORM_ARCH_32 1
	#endif
#elif defined(_PLATFORM_OSX_)
#elif defined(_PLATFORM_WINDOWS_)
	#if defined(_WIN64)
		#define _PLATFORM_ARCH_64 1
	#else
		#define _PLATFORM_ARCH_32 1
	#endif
#endif
