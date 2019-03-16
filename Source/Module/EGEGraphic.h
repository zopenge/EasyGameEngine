//! @file     EGEGraphic.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#ifndef _EGE_GRAPHIC_PCH_
#define _EGE_GRAPHIC_PCH_

// Enable/Disable EGL
#define _ENABLE_EGL_ 0

// OpenGLES
#if (_ENABLE_EGL_ == 1)
	#define _OPENGLES_ 1 // Use EGL as OpenGLES emulator
#endif

// Graphic Config File
#include "Module/Graphic/GraphicConfig.h"

// GLSL Optimizer SDK
#include "glsl_optimizer.h"

// Windows Platform
#if defined _PLATFORM_WINDOWS_

	#pragma warning( disable:4005 )

	// Windows Header Files
	#include "Platform/OS/windows/Win32Headers.h"
	#include "Platform/OS/windows/Win32Macros.h"
	#include <unknwn.h>

	// OVR SDK
	#if (_ENABLE_VR_OVR_SDK == 1)
		#include <GL/CAPI_GLE.h>
		#include <Extras/OVR_Math.h>
		#include <Kernel/OVR_System.h>
		#include <OVR_CAPI_GL.h>
	#else
		// OpenGLES
		#if (_OPENGLES_ == 1)
			// OpenGLES Emulator SDK Configure
			#define _OPENGLES_USE_POWERVR_SDK_	0
			#define _OPENGLES_USE_ADRENO_SDK_	1
			#if ((_OPENGLES_USE_POWERVR_SDK_ + _OPENGLES_USE_ADRENO_SDK_) != 1)
			#error "You must enable only 1 SDK for OpenGLES emulator"
			#else
			#define _OPENGLES_USE_EMULATOR_		1
			#endif

			// Use the OpenGL extensions
			#ifndef GL_GLEXT_PROTOTYPES
			#define GL_GLEXT_PROTOTYPES
			#endif
			// OpenGLES SDK
			#include "EGL/egl.h"
			#include "GLES2/gl2.h"
			#include "GLES2/gl2ext.h"
			#include "GLES3/gl31.h"

		// OpenGL
		#else
			// GLEW SDK
			#if (_DISABLE_GLEW_SDK == 0)
			#include "GL/glew.h"
			#include "GL/wglew.h"
			#endif
		#endif
	#endif

// IOS Platform
#elif defined _PLATFORM_IOS_

	#import <OpenGLES/ES2/gl.h>
	#import <OpenGLES/ES2/glext.h>

	// Foundation Files
	#ifdef __OBJC__
		#import <Availability.h>
		#import <Foundation/Foundation.h>
		#import <QuartzCore/QuartzCore.h>
		#import <UIKit/UIKit.h>
	#endif

	// Run in OpenGLES mode
	#define _OPENGLES_				1
	#define _OPENGLES_USE_EMULATOR_	0

// Android Platform
#elif defined _PLATFORM_ANDROID_

	// We dynamic load interfaces on android platform
	#undef GL_GLEXT_PROTOTYPES

	// NDK Files
	#include <EGL/egl.h>
	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>

	// Run in OpenGLES mode
	#define _OPENGLES_				1
	#define _OPENGLES_USE_EMULATOR_	0

	// Get the android SDK version.
	extern "C" int GetAndroidSDKVersion( );

// Chrome Platform
#elif defined _PLATFORM_CHROME_

	// Use the OpenGL extensions
	#ifndef GL_GLEXT_PROTOTYPES
	#define GL_GLEXT_PROTOTYPES
	#endif

	// GLES SDK Files
	#include <ppapi/c/pp_errors.h>
	#include <ppapi/c/pp_resource.h>
	#include <ppapi/c/ppb_core.h>
	#include <ppapi/c/ppb_instance.h>
	#include <ppapi/c/ppb_graphics_3d.h>
	#include <ppapi/lib/gl/gles2/gl2ext_ppapi.h>
	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>

	// Run in OpenGLES mode
	#define _OPENGLES_				1
	#define _OPENGLES_USE_EMULATOR_	0

#endif

// This is a macro that casts a dynamically bound RHI reference to the appropriate OpenGL type
#define DYNAMIC_CAST_GLRESOURCE(Type, Name) \
	GL##Type* gl_##Name = static_cast< GL##Type* >( Name )
#define DYNAMIC_CAST_GLRESOURCE_CONST(Type, Name) \
	const GL##Type* gl_##Name = static_cast< const GL##Type* >( Name )

// EasyGameEngine Headers
#include "EGE_Always.h"
#include "EGE_Engine.h"
#include "EGE_Modules.h"
#include "Interface/Module/EGE_Graphic.h"

// Log Files
#undef DEFINE_MODULE 
#define DEFINE_MODULE gGraphicModule->
#include "EGE_Logs.h"

// Null Classes
#include "Module/Graphic/GraphicNullClasses.h"

// Global variables
extern EGE::IDynamicRHI*				gDynamicRHI;
extern EGE::ViewportRHI*				gSharedViewportRHI;
extern EGE::IResourceManagerRHI*		gResourceManagerRHI;
extern EGE::IGraphicViewport*			gGraphicViewport;
extern EGE::IGraphicResourceManager*	gGraphicResourceManager;
extern EGE::IGraphicVRDevice*			gGraphicVRDevice;
extern EGE::IGraphicModule*				gGraphicModule;

// Graphic Basic Files
#include "Module/Graphic/GraphicVersion.h"
#include "Module/Graphic/Utils/RenderUtils.h"
#include "Module/Graphic/Utils/RenderFontTextureSet.h"
#include "Module/Graphic/Utils/GLSLOptimizer.h"
#include "Module/Graphic/Utils/ShaderParser.h"

// OpenGL Files
#if (_OPENGLES_ == 1) && (defined(_PLATFORM_WINDOWS_) || defined(_PLATFORM_ANDROID_))
#include "Module/Graphic/RHI/GL/Inc/GLESContext.h"
#endif
#include "Module/Graphic/RHI/GL/Inc/EGLAPI.h"
#include "Module/Graphic/RHI/GL/Inc/GLEnums.h"
#include "Module/Graphic/RHI/GL/Inc/GLHelper.h"
#include "Module/Graphic/RHI/GL/Inc/GLContext.h"
#include "Module/Graphic/RHI/GL/Inc/GLPlatform.h"
#include "Module/Graphic/RHI/GL/Inc/GLState.h"
#include "Module/Graphic/RHI/GL/Inc/GLResources.h"
#include "Module/Graphic/RHI/GL/Inc/GLRenderTarget.h"
#include "Module/Graphic/RHI/GL/Inc/GLFramebuffer.h"
#include "Module/Graphic/RHI/GL/Inc/GLFramebufferCache.h"
#include "Module/Graphic/RHI/GL/Inc/GLViewport.h"
#include "Module/Graphic/RHI/GL/Inc/GLSLProgram.h"
#include "Module/Graphic/RHI/GL/Inc/GLResourceManager.h"
#include "Module/Graphic/RHI/GL/Inc/GLDebug.h"
#include "Module/Graphic/RHI/GL/Inc/GLInfo.h"
#include "Module/Graphic/RHI/GL/Inc/GLDrv.h"

// RHI Stats Files
#ifndef _EGE_DISABLE_RHI_STATS_
#include "Module/Graphic/RHI/RHIStats/Inc/RHIStatsBase.h"
#include "Module/Graphic/RHI/RHIStats/Inc/RHIStatsIndexBuffer.h"
#include "Module/Graphic/RHI/RHIStats/Inc/RHIStatsVertexBuffer.h"
#include "Module/Graphic/RHI/RHIStats/Inc/RHIStatsVertexDeclaration.h"
#include "Module/Graphic/RHI/RHIStats/Inc/RHIStatsPixelShader.h"
#include "Module/Graphic/RHI/RHIStats/Inc/RHIStatsVertexShader.h"
#include "Module/Graphic/RHI/RHIStats/Inc/RHIStatsBoundShader.h"
#include "Module/Graphic/RHI/RHIStats/Inc/RHIStatsViewport.h"
#include "Module/Graphic/RHI/RHIStats/Inc/RHIStatsFont.h"
#include "Module/Graphic/RHI/RHIStats/Inc/RHIStatsTexture.h"
#include "Module/Graphic/RHI/RHIStats/Inc/RHIStatsTexture2D.h"
#include "Module/Graphic/RHI/RHIStats/Inc/RHIStatsTextureCube.h"
#include "Module/Graphic/RHI/RHIStats/Inc/RHIStatsSurface.h"
#include "Module/Graphic/RHI/RHIStats/Inc/RHIStatsDrv.h"
#endif

// Graphic Files
#include "Module/Graphic/GraphicResourceManager.h"
#include "Module/Graphic/GraphicFont.h"
#include "Module/Graphic/GraphicFlatMirror.h"
#include "Module/Graphic/GraphicSphereMirror.h"
#include "Module/Graphic/GraphicGeometryBuilder.h"
#include "Module/Graphic/GraphicGeometry.h"
#include "Module/Graphic/GraphicVAOGroup.h"
#include "Module/Graphic/GraphicMirrorGroup.h"
#include "Module/Graphic/GraphicGeometryGroup.h"
#include "Module/Graphic/GraphicGeometryProcessor.h"
#include "Module/Graphic/GraphicMaskLayer.h"
#include "Module/Graphic/GraphicScene.h"
#include "Module/Graphic/GraphicCanvas.h"
#include "Module/Graphic/GraphicSceneView.h"
#include "Module/Graphic/GraphicMesh.h"
#include "Module/Graphic/GraphicEffect.h"
#include "Module/Graphic/GraphicLight.h"
#include "Module/Graphic/GraphicVertexDeclaration.h"
#include "Module/Graphic/GraphicVertexBuffer.h"
#include "Module/Graphic/GraphicIndexBuffer.h"
#include "Module/Graphic/GraphicVertexArray.h"
#include "Module/Graphic/GraphicSurface.h"
#include "Module/Graphic/GraphicTexture2D.h"
#include "Module/Graphic/GraphicTextureCube.h"
#include "Module/Graphic/GraphicSubTexture2D.h"
#include "Module/Graphic/GraphicTexture2DImageFiller.h"
#include "Module/Graphic/GraphicTexture2DSet.h"
#include "Module/Graphic/GraphicBackSurface.h"
#include "Module/Graphic/GraphicViewport.h"
#include "Module/Graphic/GraphicSharedViewport.h"
#include "Module/Graphic/GraphicVRDevice.h"
#include "Module/Graphic/GraphicVRDeviceSoftware.h"
#include "Module/Graphic/GraphicModule.h"

// Windows Platform
#if defined _PLATFORM_WINDOWS_

	// OpenGL
	#pragma comment( lib, "opengl32" )
	#pragma comment( lib, "libGLSLOptimizer.lib" )

	// OVR SDK
	#if (_ENABLE_VR_OVR_SDK == 1)
		#pragma comment( lib, "LibOVR.lib" )
		#pragma comment( lib, "LibOVRKernel.lib" )
	#endif

	// OpenGLES SDK
	#if (_OPENGLES_USE_ADRENO_SDK_ == 1)
		// The release DLL of AdrenoSDK is missing some export functions, so we always use the debug version instead of it.
		#pragma comment( lib, "libEGL_d.lib" )
		#pragma comment( lib, "libGLESv2_d.lib" )
		#pragma comment( lib, "TextureConverter_d.lib" )
	#endif

// IOS Platform
#elif defined _PLATFORM_IOS_

#endif

// Using namespace here to prevent some name conflict 
using namespace EGE;
using namespace EGE::GraphicEvents;

#endif // _EGE_GRAPHIC_PCH_
