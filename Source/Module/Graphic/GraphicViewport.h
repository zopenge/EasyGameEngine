//! @file     GraphicViewport.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicViewport
//----------------------------------------------------------------------------

class GraphicViewport : public TObject< IGraphicViewport >
{
private:
	//!	The viewport resource
	ViewportRHIRef			mViewportRHI;

	//!	The scene
	IGraphicSceneRef		mScene;

	//!	The back surface
	IGraphicBackSurfaceRef	mBackSurface;

	//!	The main viewport clear buffers operations, if we begin to render back surface, we need to save it
	GraphicClearBuffersInfo	mClearBuffersInfo;

public:
	GraphicViewport( ViewportRHI* viewport_rhi );
	virtual ~GraphicViewport( );

public:
	//!	Initialize.
	_ubool Initialize( );

// IGraphicDrawer Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_DRAWER_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames { Return mScene->Name Parameters; }
	#include "Module/Graphic/Methods/GraphicDrawerMethods.h"
	#undef DEFINE_DRAWER_METHOD

// IGraphicScene Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_SCENE_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Module/Graphic/Methods/GraphicSceneMethods.h"
	#undef DEFINE_SCENE_METHOD

// IGraphicViewport Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_VIEWPORT_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Module/Graphic/Methods/GraphicViewportMethods.h"
	#undef DEFINE_VIEWPORT_METHOD
};

//----------------------------------------------------------------------------
// GraphicViewport Implementation
//----------------------------------------------------------------------------

}