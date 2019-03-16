//! @file     GraphicVRDeviceSoftware.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

#if (_ENABLE_VR_SOFTWARE == 1)

namespace EGE
{

class GraphicVRDevice;

//----------------------------------------------------------------------------
// GraphicVREyeSceneView
//----------------------------------------------------------------------------

class GraphicVREyeSceneView : public TObject< IGraphicSceneView >
{
private:
	IGraphicSceneViewRef	mSceneView;

	_dword					mEyeIndex;
	Camera					mCamera;
	GraphicVRDevice*		mVRDevice;

private:
	_void UpdateCamera( const Camera& camera );

public:
	GraphicVREyeSceneView( _dword eye_index, GraphicVRDevice* device );
	virtual ~GraphicVREyeSceneView( );

// IGraphicSceneView Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_SCENE_VIEW_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Module/Graphic/Methods/GraphicSceneViewMethods.h"
	#undef DEFINE_SCENE_VIEW_METHOD
};

//----------------------------------------------------------------------------
// GraphicVRDeviceSceneView
//----------------------------------------------------------------------------

class GraphicVRDeviceSceneView : public TObject< IGraphicSceneView >
{
private:
	IGraphicSceneViewRef	mSceneView;

	GraphicVREyeSceneView*	mEyeSceneViews[2];

public:
	GraphicVRDeviceSceneView( GraphicVRDevice* device );
	virtual ~GraphicVRDeviceSceneView( );

public:
	//!	Get the eye scene view.
	GraphicVREyeSceneView* GetEyeSceneView( _dword index );

// IGraphicSceneView Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_SCENE_VIEW_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Module/Graphic/Methods/GraphicSceneViewMethods.h"
	#undef DEFINE_SCENE_VIEW_METHOD
};

//----------------------------------------------------------------------------
// GraphicVRDevice
//----------------------------------------------------------------------------

class GraphicVRDevice : public TObject< IGraphicVRDevice >
{
private:
	Vector3						mGyroscopeSensorInfo;
	Vector3						mOrientationSensorInfo;
	GraphicVRDeviceSceneView*	mSceneView;
	mutable _dword				mCurEyeIndex;
	PointU						mCanvasSize;
	IGraphicCanvasRef			mCanvas[2];

	IGraphicSceneRef			mSceneFromMainViewport;

private:
	//!	Create canvas.
	_ubool CreateCanvas( const PointU& client_size );

public:
	GraphicVRDevice( );
	virtual ~GraphicVRDevice( );

// IGraphicDrawer Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_DRAWER_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Module/Graphic/Methods/GraphicDrawerMethods.h"
	#undef DEFINE_DRAWER_METHOD

// IGraphicScene Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_SCENE_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Module/Graphic/Methods/GraphicSceneMethods.h"
	#undef DEFINE_SCENE_METHOD
	
// IGraphicVRDevice Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_VRDEVICE_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Module/Graphic/Methods/GraphicVRDeviceMethods.h"
	#undef DEFINE_VRDEVICE_METHOD
};

}

#endif