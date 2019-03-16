//! @file     GraphicSphereMirror.h
//! @author   LiCode
//! @version  1.0
//! @date     2015.6
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicSphereMirror
//----------------------------------------------------------------------------

class GraphicSphereMirror : public TObject< IGraphicSphereMirror >
{
private:
	//! The environment map scene view
	IGraphicSceneViewRef	mEnvironmentMapSceneView;

	//!	The canvas
	IGraphicCanvasRef		mCanvas;
	Viewport				mMirrorViewport;

public:
	GraphicSphereMirror( );
	virtual ~GraphicSphereMirror( );

public:
	//!	Initialize.
	_ubool Initialize( const PointU& size );

// IGraphicDrawer Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_DRAWER_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames { Return mCanvas->Name Parameters; }
	#define CUSTOM_DRAW_MESH
	#include "Module/Graphic/Methods/GraphicDrawerMethods.h"
	#undef DEFINE_DRAWER_METHOD

	virtual _void DrawMeshGeometry( IGraphicEffect* effect, const GraphicMeshGeometryInfo& geometry_info ) override;

// IGraphicScene Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_SCENE_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames { Return mCanvas->Name Parameters; }
	#include "Module/Graphic/Methods/GraphicSceneMethods.h"
	#undef DEFINE_SCENE_METHOD

// IGraphicCanvas Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_CANVAS_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames { Return mCanvas->Name Parameters; }
	#include "Module/Graphic/Methods/GraphicCanvasMethods.h"
	#undef DEFINE_CANVAS_METHOD

// IGraphicMirror Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_MIRROR_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Module/Graphic/Methods/GraphicMirrorMethods.h"
	#undef DEFINE_MIRROR_METHOD

// IGraphicSphereMirror Interface
public:
	virtual IGraphicSceneView* GetEnvironmentMapSceneView( ) override;
};

}