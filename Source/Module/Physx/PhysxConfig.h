//! @file     PhysxConfig.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

// Windows platform
#ifdef _PLATFORM_WINDOWS_
	// Use bullet library
	#define _PHYSX_USE_BULLET_ 1
// Android platform
#elif _PLATFORM_ANDROID_
	// Use bullet library
	#define _PHYSX_USE_BULLET_ 0
// IOS platform
#elif _PLATFORM_IOS_
	// Use bullet library
	#define _PHYSX_USE_BULLET_ 0
// Chrome platform
#elif _PLATFORM_CHROME_
	// Use bullet library
	#define _PHYSX_USE_BULLET_ 0
#endif

#if (_PHYSX_USE_BULLET_) == 0
	// Use dummy library
	#define _PHYSX_USE_DUMMY_ 1
#elif (_PHYSX_USE_BULLET_) > 1
	#error "We only can use 1 physx system in the same time"
#endif
