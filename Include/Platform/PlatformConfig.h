//! @file     PlatformConfig.h
//! @author   LiCode
//! @version  1.1.0.695
//! @date     2011/02/13
//! Copyright ...

#pragma once

// Win32 Platform
#if defined _PLATFORM_WINDOWS_

// IOS Platform
#elif defined _PLATFORM_IOS_

// OSX Platform
#elif defined _PLATFORM_OSX_

// Android Platform
#elif defined _PLATFORM_ANDROID_

#define NS_EXPORT

extern "C" {
/*
 * To work around http://code.google.com/p/android/issues/detail?id=23203
 * we don't link with the crt objects. In some configurations, this means
 * a lack of the __dso_handle symbol because it is defined there, and
 * depending on the android platform and ndk versions used, it may or may
 * not be defined in libc.so. In the latter case, we fail to link. Defining
 * it here as weak makes us provide the symbol when it's not provided by
 * the crt objects, making the change transparent for future NDKs that
 * would fix the original problem. On older NDKs, it is not a problem
 * either because the way __dso_handle was used was already broken (and
 * the custom linker works around it).
 */
NS_EXPORT __attribute__((weak)) void *__dso_handle;
}

#endif