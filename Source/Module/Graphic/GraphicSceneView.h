//! @file     GraphicSceneView.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicSceneView
//----------------------------------------------------------------------------

class GraphicSceneView : public INTERFACE_OBJECT_IMPL( IGraphicSceneView )
{
private:
	typedef CallbackFunc< OnTransformChanged, _void, QwordParameters2 > TransformChangedFunc;

private:
	//!	The camera and projection info
	struct CameraAndProjectionInfo
	{
		//!	The camera
		Camera	mCamera;

		//!	The projection info
		_float	mAspect;
		_float	mZNear;
		_float	mZFar;

		CameraAndProjectionInfo( )
		{
			mCamera	= Camera::cNull;

			mAspect	= 1.0f;
			mZNear	= 1.0f;
			mZFar	= 500.0f;
		}
	};
	typedef Stack< CameraAndProjectionInfo > CameraAndProjectionInfoStack;

private:
	//!	The camera and projection info stack
	CameraAndProjectionInfoStack	mCameraAndProjections;

	//! The view transform (right-hand)
	Matrix4							mViewTransformRH;
	//!	The projection transform (right-hand)
	Matrix4							mProjectionTransformRH;
	//!	The view * projection transform (right-hand)
	Matrix4							mViewProjectionTransformRH;
	//!	The view frustum (right-hand)
	Frustum							mViewFrustumRH;

	//!	The transform changed callback function
	TransformChangedFunc			mTransformChangedFunc;

	//! Is the ortho mode
	_ubool							mOrthoMode;
	Vector2							mOrthoViewSize;
	_float							mOrthoScaleFactor;

	//!	The observer scene view
	IGraphicSceneViewRef			mObserverSceneView;

private:
	//!	Update projection transform.
	_void UpdateProjectionTransform( );

	//!	Update camera.
	_void UpdateCamera( );

public:
	GraphicSceneView( );
	virtual ~GraphicSceneView( );

// IGraphicSceneView Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_SCENE_VIEW_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Module/Graphic/Methods/GraphicSceneViewMethods.h"
	#undef DEFINE_SCENE_VIEW_METHOD
};

//----------------------------------------------------------------------------
// GraphicSceneView Implementation
//----------------------------------------------------------------------------

}