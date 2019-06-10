#pragma once

// Windows Platform
#if defined _PLATFORM_WINDOWS_

// IOS Platform
#elif defined _PLATFORM_IOS_

#	import <targetconditionals.h>

#	if (TARGET_IPHONE_SIMULATOR == 1)
#		define _TARGET_OS_SIMULATOR_ 1
#	else
#		define _TARGET_OS_SIMULATOR_ 0
#	endif

// Android Platform
#elif defined _PLATFORM_ANDROID_

#	define _TARGET_OS_SIMULATOR_ 0

// Auto-Detect Platform
#else

// Define our windows macro if it's windows platform
#	if defined(WIN32) && !defined(_PLATFORM_WINDOWS_)
#		define _PLATFORM_WINDOWS_
#	endif

#	define _TARGET_OS_SIMULATOR_ 0

#endif

// Turn off STL debug iterators in release build
#ifndef _DEBUG
#	define _SECURE_SCL 0
#endif

// 64 Bits platform check
#if defined(_PLATFORM_ANDROID_)
#	if defined(__aarch64__) || defined(__x86_64__)
#		define _PLATFORM_ARCH_64 1
#	else
#		define _PLATFORM_ARCH_32 1
#	endif
#elif defined(_PLATFORM_IOS_)
#	if defined(__LP64__) || defined(__arm64__) || defined(__x86_64__)
#		define _PLATFORM_ARCH_64 1
#	else
#		define _PLATFORM_ARCH_32 1
#	endif
#elif defined(_PLATFORM_WINDOWS_)
#	if defined(_WIN64)
#		define _PLATFORM_ARCH_64 1
#	else
#		define _PLATFORM_ARCH_32 1
#	endif
#endif
