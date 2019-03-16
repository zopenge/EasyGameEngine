//! @file     GraphicFlatMirror.h
//! @author   LiCode
//! @version  1.0
//! @date     2015.6
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicFlatMirror
//----------------------------------------------------------------------------

class GraphicFlatMirror : public TObject< IGraphicFlatMirror >
{
private:
	//!	The attenuation distance
	_float				mAttenuationDistance;

	//! The mirror plane
	Plane				mReflectionPlane;
	//!	The mirror plane transform
	Matrix4				mReflectionPlaneTransform;

	//!	The canvas
	IGraphicCanvasRef	mCanvas;

	//!	The mirror viewport
	Viewport			mMirrorViewport;

public:
	GraphicFlatMirror( );
	virtual ~GraphicFlatMirror( );

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

// IGraphicFlatMirror Interface
public:
	virtual _void			SetAttenuationDistance( _float distance ) override;
	virtual _float			GetAttenuationDistance( ) const override;

	virtual _void			SetPlane( const Plane& plane ) override;
	virtual const Plane&	GetPlane( ) const override;
};

}