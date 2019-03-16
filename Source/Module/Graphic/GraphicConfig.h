//! @file     GraphicConfig.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

// Enable VR in OVR(Oculus Virtual Real) SDK
#define _ENABLE_VR_OVR_SDK 0
// Enable VR in software mode
#define _ENABLE_VR_SOFTWARE 0

#if defined(_ENABLE_VR_OVR_SDK) || defined(_ENABLE_VR_SOFTWARE)
	#define _ENABLE_VR_DEVICE 1
	#if (_ENABLE_VR_OVR_SDK + _ENABLE_VR_SOFTWARE) > 1
		#error "We only can use 1 VR system in the same time"
	#endif
#endif

// If we enable OVR SDK then need to disable GLEW SDK
#if (_ENABLE_VR_OVR_SDK == 1)
	#define _DISABLE_GLEW_SDK 1
#endif

// Enable/Disable GL features
#ifdef _DEBUG
    #define _DISABLE_GL_ERROR_CHECK			0
    #define _DISABLE_GL_API_CALL_COUNTER	0
#else
    #define _DISABLE_GL_ERROR_CHECK			1
    #define _DISABLE_GL_API_CALL_COUNTER	1
#endif

// Enable GL device manager
#if defined(_PLATFORM_ANDROID_)
	#define _ENABLE_GL_DEVICE_MANAGER 1
#elif defined(_PLATFORM_IOS_)
	#define _ENABLE_GL_DEVICE_MANAGER 0
#elif defined(_PLATFORM_OSX_)
	#define _ENABLE_GL_DEVICE_MANAGER 0
#elif defined(_PLATFORM_WINDOWS_)
    #define _ENABLE_GL_DEVICE_MANAGER 1
#endif

// Enable redundant check
#if defined(_PLATFORM_WINDOWS_)
	#define _ENABLE_REDUNDANT_CHECK 1
#endif

// Enable GL debug
#if defined(_PLATFORM_WINDOWS_)
	#define _ENABLE_GL_DEBUG 0
#else
	#define _ENABLE_GL_DEBUG 0
#endif