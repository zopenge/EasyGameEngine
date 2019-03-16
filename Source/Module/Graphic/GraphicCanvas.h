//! @file     GraphicCanvas.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicCanvas
//----------------------------------------------------------------------------

class GraphicCanvas : public TObject< IGraphicCanvas >
{
private:
	//!	The canvas size ( render target and depth stencil have the same size )
	PointU				mSize;

	//!	The scene
	IGraphicSceneRef	mScene;

	//!	The pixels buffer to read from render target
	_byte*				mRenderTargetLockedPixels;
	//!	The color surface
	IGraphicSurfaceRef	mRenderTarget;
	//!	The depth surface
	IGraphicSurfaceRef	mDepthStencil;

private:
	//!	Check the surfaces.
	_ubool CheckSurfaces( IGraphicSurface* render_target, IGraphicSurface* depth_stencil ) const;

public:
	GraphicCanvas( );
	virtual ~GraphicCanvas( );

public:
	//!	Initialize.
	_ubool Initialize( IGraphicSurface* render_target, IGraphicSurface* depth_stencil );
	_ubool Initialize( IGraphicScene* scene, IGraphicSurface* render_target, IGraphicSurface* depth_stencil );

// IGraphicDrawer Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_DRAWER_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames { Return mScene->Name Parameters; }
	#include "Module/Graphic/Methods/GraphicDrawerMethods.h"
	#undef DEFINE_DRAWER_METHOD

// IGraphicScene Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_SCENE_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames { Return mScene->Name Parameters; }
	#define CUSTOM_PRESENT_RENDER_BUFFERS
	#include "Module/Graphic/Methods/GraphicSceneMethods.h"
	#undef DEFINE_SCENE_METHOD

	virtual _void PresentRenderBuffers( ) override;

// IGraphicCanvas Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_CANVAS_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Module/Graphic/Methods/GraphicCanvasMethods.h"
	#undef DEFINE_CANVAS_METHOD
};

//----------------------------------------------------------------------------
// GraphicCanvas Implementation
//----------------------------------------------------------------------------

}