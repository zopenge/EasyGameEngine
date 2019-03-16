//! @file     EGESound.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#ifndef _EGE_SOUND_PCH_
#define _EGE_SOUND_PCH_

// Windows Platform
#if defined _PLATFORM_WINDOWS_

	#include "Platform/OS/windows/Win32Headers.h"
	#include <mmsystem.h>

	// OpenAL SDK
	extern "C" {
	#include "AL/al.h"
	#include "AL/alc.h"
	#include "AL/alext.h"
	}
	
    #define _USE_OPENAL_        1
    #define _USE_OPENAL_EXT_    0

// IOS Platform
#elif defined _PLATFORM_IOS_

	// Audio SDK
	#ifdef __OBJC__
		#import <Availability.h>
		#import <Foundation/Foundation.h>
		#import <AVFoundation/AVFoundation.h>
		#import <AudioToolbox/AudioToolbox.h>
        #import <UIKit/UIKit.h>
	#endif
	
	// OpenAL SDK
	#import <OpenAL/al.h>
	#import <OpenAL/alc.h>

	#define _USE_OPENAL_        1
    #define _USE_OPENAL_EXT_    0

// OSX Platform
#elif defined _PLATFORM_OSX_

// Android Platform
#elif defined _PLATFORM_ANDROID_

    #define _USE_OPENAL_        1
    #define _USE_OPENAL_EXT_    0
//	#define _USE_OPENSL_ 1

	// NDK Files
#if (_USE_OPENAL_ == 1)
	extern "C" {
	#include "AL/al.h"
	#include "AL/alc.h"
	#include "AL/alext.h"
	#include "AL/efx.h"
	}
#elif (_USE_OPENSL_ == 1)
	#include <SLES/OpenSLES.h>
	#include <SLES/OpenSLES_Android.h>

	#ifndef SL_PLAYSTATE_INITIAL
		#define SL_PLAYSTATE_INITIAL 0
	#endif
#endif

// Chrome Platform
#elif defined _PLATFORM_CHROME_

    #define _USE_PPB_	1

	// PPAPI SDK Files
	#include <ppapi/c/ppb_audio.h>
#endif

// (MSC, Mobile Speech Client) SDK
#ifdef _PLATFORM_WINDOWS_
#include "qisr.h"
#include "qtts.h"
#include "msp_cmn.h"
#include "msp_errors.h"
#endif

// This is a macro that casts a dynamically bound SHI reference to the appropriate OpenAL type
#define DYNAMIC_CAST_ALRESOURCE(Type,Name) \
	AL##Type* al_##Name = static_cast< AL##Type* >( (Type##SHI*) Name ); \
	EGE_ASSERT( al_##Name != _null )
// This is a macro that casts a dynamically bound SHI reference to the appropriate OpenSL type
#define DYNAMIC_CAST_SLRESOURCE(Type,Name) \
	SL##Type* sl_##Name = static_cast< SL##Type* >( (Type##SHI*) Name ); \
	EGE_ASSERT( sl_##Name != _null )

// Get the SHI resource
#define GET_SHI_RESOURCE(var_type,var_name) \
	( (var_name) ? ( (var_type*) (var_name) )->GetResource( ) : _null )

// EasyGameEngine Headers
#include "EGE_Always.h"
#include "EGE_Engine.h"
#include "EGE_Modules.h"
#include "Interface/Module/EGE_Sound.h"

// Log Files
#undef DEFINE_MODULE 
#define DEFINE_MODULE gSoundModule->
#include "EGE_Logs.h"

// SDK Files
#include "Module/Sound/SDK/MSC/MSCSDK.h"

// Null Classes
#include "Module/Sound/SoundNullClasses.h"

// Global variables
extern EGE::IDynamicSHI*			gDynamicSHI;
extern EGE::ISoundResourceManager*	gSoundResourceManager;
extern EGE::ISoundModule*			gSoundModule;

#if (_USE_OPENAL_ == 1)
	#include "Module/Sound/SHI/AL/Inc/ALAPI.h"
	#include "Module/Sound/SHI/AL/Inc/ALResources.h"
	#include "Module/Sound/SHI/AL/Inc/ALDrv.h"
#elif (_USE_OPENSL_ == 1)
	#include "Module/Sound/SHI/SL/Inc/SLAPI.h"
	#include "Module/Sound/SHI/SL/Inc/SLResources.h"
	#include "Module/Sound/SHI/SL/Inc/SLDrv.h"
#elif (_USE_PPB_ == 1)
	#include "Module/Sound/SHI/PPB/Inc/PPBResources.h"
	#include "Module/Sound/SHI/PPB/Inc/PPBDrv.h"
#endif

// Template Files
#include "Module/Sound/Template/TSoundRecorder.h"

// Sound Files
#include "Module/Sound/SoundVersion.h"
#ifdef _PLATFORM_WINDOWS_
#include "Module/Sound/SoundRecorder/win/winSoundRecorder.h"
#elif _PLATFORM_ANDROID_
#include "Module/Sound/SoundRecorder/android/androidSoundRecorder.h"
#elif _PLATFORM_IOS_
#include "Module/Sound/SoundRecorder/ios/iosSoundRecorder.h"
#endif
#include "Module/Sound/SoundRecognizer.h"
#include "Module/Sound/SoundBufferQueue.h"
#include "Module/Sound/SoundSource.h"
#include "Module/Sound/SoundResourceManager.h"
#include "Module/Sound/SoundModule.h"

// Using namespace here to prevent some name conflict 
using namespace EGE;

// Link external libraries
#if defined _PLATFORM_WINDOWS_
	#pragma comment( lib, "advapi32.lib" )
	#pragma comment( lib, "winmm.lib" )
	#pragma comment( lib, "libopenal.lib" )
#elif defined _PLATFORM_IOS_

#elif defined _PLATFORM_ANDROID_
#endif

#endif // _EGE_SOUND_PCH_