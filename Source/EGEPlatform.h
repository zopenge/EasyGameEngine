//! @file     EGEPlatform.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#ifndef _EGE_PLATFORM_PCH_
#define _EGE_PLATFORM_PCH_

// Standard Files
#include <cstdint>
#include <limits>
#include <math.h>
#include <wchar.h>

// CRT dbg Files
#ifdef _PLATFORM_WINDOWS_
#	include "dbgint.h"
#endif

// Nedmalloc Files On Windows Platform
#ifdef _PLATFORM_WINDOWS_
#	define NO_NED_NAMESPACE
#	define NEDMALLOCDEPRECATED // Disable deprecated warning for ned-malloc SDK
#	include "nedmalloc/nedmalloc.h"
#endif

extern "C" {
// Unicode Char Files
#include "uchar/uchar.h"

// pthread Files
//#define USE_PTHREAD 1
#if (USE_PTHREAD == 1)
#	include "pthread.h"
#endif
}

// Win32 Platform
#if defined _PLATFORM_WINDOWS_

// Windows Header Files
#	include "Platform/OS/windows/Win32Headers.h"
// System Files
#	include <dbghelp.h>
#	include <iptypes.h>
#	include <lm.h>
#	include <mmsystem.h>
#	include <objbase.h>
#	include <tlhelp32.h>
#	include <ws2tcpip.h>
// Redefined Windows Variables and Functions
#	include "Platform/OS/windows/Win32Macros.h"

// Libraries Files
#	pragma comment(lib, "version")
#	pragma comment(lib, "wininet")
#	pragma comment(lib, "netapi32")
#	pragma comment(lib, "winmm")
#	pragma comment(lib, "Iphlpapi")
#	pragma comment(lib, "ws2_32.lib")

// Some rename functions
#	define strtoull _strtoui64

#	if (USE_PTHREAD == 1)
typedef int (*__pthread_attr_init)(pthread_attr_t* attr);
typedef int (*__pthread_create)(pthread_t* tid, const pthread_attr_t* attr,
                                void*(PTW32_CDECL* start)(void*), void* arg);
typedef int (*__pthread_detach)(pthread_t tid);
typedef int (*__pthread_attr_setdetachstate)(pthread_attr_t* attr,
                                             int detachstate);
typedef int (*__pthread_attr_destroy)(pthread_attr_t* attr);
typedef pthread_t (*__pthread_self)(void);
typedef int (*__pthread_attr_setschedpolicy)(pthread_attr_t*, int);
typedef int (*__pthread_attr_setschedparam)(pthread_attr_t* attr,
                                            const struct sched_param* param);
typedef int (*__pthread_kill)(pthread_t thread, int sig);
typedef int (*__pthread_join)(pthread_t thread, void** value_ptr);

extern __pthread_attr_init _pthread_attr_init;
extern __pthread_create _pthread_create;
extern __pthread_detach _pthread_detach;
extern __pthread_attr_setdetachstate _pthread_attr_setdetachstate;
extern __pthread_attr_destroy _pthread_attr_destroy;
extern __pthread_self _pthread_self;
extern __pthread_attr_setschedpolicy _pthread_attr_setschedpolicy;
extern __pthread_attr_setschedparam _pthread_attr_setschedparam;
extern __pthread_kill _pthread_kill;
extern __pthread_join _pthread_join;
#	endif

// IOS Platform
#elif defined _PLATFORM_IOS_

// Use pthread
#	ifndef USE_PTHREAD
#		define USE_PTHREAD 1
#	endif

// Foundation Files
#	ifdef __OBJC__
#		import <Availability.h>
#		import <Foundation/Foundation.h>
#	endif

// System Files
#	import <cerrno>
#	import <dirent.h>
#	import <fcntl.h>
#	import <mach/mach.h>
#	import <pthread.h>
#	import <sys/mman.h>
#	import <sys/signal.h>
#	import <sys/stat.h>
#	import <sys/time.h>
#	import <sys/types.h>
#	import <unistd.h>

// Android Platform
#elif defined _PLATFORM_ANDROID_

// Use pthread
#	ifndef USE_PTHREAD
#		define USE_PTHREAD 1
#	endif

// System Files
#	include <cerrno>
#	include <dirent.h>
#	include <fcntl.h>
#	include <pthread.h>
#	include <signal.h>
#	include <sys/stat.h>
#	include <sys/time.h>
#	include <sys/wait.h>
#	include <unistd.h>
//	#include <locale.h>

// NDK Files
#	include <android/asset_manager.h>
#	include <android/asset_manager_jni.h>
#	include <android/log.h>

// NDK-Tools Files
#	include "cpufeatures/cpu-features.h"

// Quit application
extern "C" void QuitAndroidCurProcess();
// Get the android SDK version.
extern "C" int GetAndroidSDKVersion();
// Get the android internal path.
extern "C" const char* GetAndroidInternalPath();
// Get the android external path.
extern "C" const char* GetAndroidExternalPath();
// Get the android package name.
extern "C" const char* GetAndroidPackageName();
// Get the android asset manager.
extern "C" AAssetManager* GetAndroidAssetManager();
// Check whether the debugger is present.
extern "C" bool IsAndroidDebuggerPresent();
// Enumerate resource files.
extern "C" bool EnumAndroidResFiles(const wchar_t* sub_dir_name, void* funcpointer, void* parameter);

// OSX Platform
#elif defined _PLATFORM_OSX_

// Use static library to link pthread SDK
#	define PTW32_STATIC_LIB
// Use pthread
#	ifndef USE_PTHREAD
#		define USE_PTHREAD 1
#	endif
#	include <pthread.h>

#endif

#if defined(_PLATFORM_WINDOWS_)
extern "C" {
int gettimeofday(struct timeval* tp, struct timezone* tzp);
}
#endif

#if defined(_PLATFORM_IOS_) || defined(_PLATFORM_ANDROID_)
// Implementation of standard C functions
extern "C" {
char* __ege_itoa__(int value, char* result, int base);
char* __ege_utoa__(unsigned int value, char* result, int base);
char* __ege_i64toa__(signed long long value, char* result, int base);
char* __ege_u64toa__(unsigned long long value, char* result, int base);
wchar_t* __ege_itow__(int value, wchar_t* result, int base);
wchar_t* __ege_utow__(unsigned int value, wchar_t* result, int base);
wchar_t* __ege_i64tow__(signed long long value, wchar_t* result, int base);
wchar_t* __ege_u64tow__(unsigned long long value, wchar_t* result, int base);
}
#	define itoa __ege_itoa__
#	define utoa __ege_utoa__

#endif

#if (USE_PTHREAD == 1)
#	define _pthread_attr_init pthread_attr_init
#	define _pthread_create pthread_create
#	define _pthread_detach pthread_detach
#	define _pthread_attr_setdetachstate pthread_attr_setdetachstate
#	define _pthread_attr_destroy pthread_attr_destroy
#	define _pthread_self pthread_self
#	define _pthread_attr_setschedpolicy pthread_attr_setschedpolicy
#	define _pthread_attr_setschedparam pthread_attr_setschedparam
#	define _pthread_kill pthread_kill
#	define _pthread_join pthread_join
#	define _pthread_setname_np pthread_setname_np
#endif

// Network OS Header
#include "Platform/OS/NetworkOSHeader.h"

// EasyGameEngine Headers
#include "EGE_Always.h"

// Any-Platform Files
#include "Platform/anyPlatform.h"
#include "Platform/anyPlatformCPU.h"
#include "Platform/anyPlatformConverter.h"
#include "Platform/anyPlatformEndian.h"
#include "Platform/anyPlatformIO.h"
#include "Platform/anyPlatformKernel.h"
#include "Platform/anyPlatformLanguage.h"
#include "Platform/anyPlatformMemory.h"
#include "Platform/anyPlatformNetwork.h"
#include "Platform/anyPlatformProcess.h"
#include "Platform/anyPlatformString.h"
#include "Platform/anyPlatformTime.h"

// IOS Platform
#if defined _PLATFORM_IOS_

// Objective-C Files
#	import "Platform/ios/NSPlatform.h"
#	ifdef __OBJC__
#		import "Platform/ios/NSMappedFile.h"
#	endif

// Some header files must be included after the namespace using declaration,
// otherwise compile failed
#	import <net/if_dl.h>
#	import <sys/sysctl.h>

#endif

namespace EGE {

//! The main thread ID
extern _thread_id gMainThreadID;
//! The performance data.
extern PerformanceData gPerformanceData;
//! The CPU data.
extern CPUData gCPUData;
//! The OS data.
extern OSData gOSData;

} // namespace EGE

using namespace EGE;

#endif // _EGE_PLATFORM_PCH_
