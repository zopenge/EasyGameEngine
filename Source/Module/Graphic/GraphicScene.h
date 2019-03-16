//! @file     GraphicScene.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicScene
//----------------------------------------------------------------------------

class GraphicScene : public TObject< IGraphicScene >
{
private:
	//!	The scissor rect info
	typedef Stack< RectF > RectFStack;

	//!	The overlay transform info.
	struct OverlayTransformInfo
	{
		Matrix3	mTransform;
		Matrix3	mInversedTransform;

		OverlayTransformInfo( )
		{
			mTransform			= Matrix3::cIdentity;
			mInversedTransform	= Matrix3::cIdentity;
		}
		OverlayTransformInfo( const Matrix3& transform )
		{
			mTransform			= transform;
			mInversedTransform	= transform;
			mInversedTransform.Inverse( );
		}
	};
	typedef Stack< OverlayTransformInfo > OverlayTransformInfoStack;

private:
	//!	The client size
	PointU						mClientSize;
	//!	The client ratio
	Ratio						mClientRatio;

	//!	The viewport of ratio
	Viewport					mViewport;

	//!	The scissor rect stack
	RectFStack					mScissorRectStack;
	//!	The overlay transform
	OverlayTransformInfoStack	mOverlayTransformStack;
	//!	The overlay world transform
	Matrix4Stack				mUserOrthoTransformStack;
	//!	The offset transform
	Matrix4Stack				mOffsetTransformStack;

	//!	The scene view
	IGraphicSceneViewRef		mSceneView;

	//!	Clear buffers operations
	GraphicClearBuffersInfo		mClearBuffersInfo;

	//!	The geometry cache
	GraphicGeometryBuilder*		mGeometryBuilder;
	//!	The geometry processor
	GraphicGeometryProcessor*	mGeometryProcessor;

	//!	The mask layer
	GraphicMaskLayer*			mMaskLayer;

private:
	//!	When scene view transform changed.
	static _void OnSceneViewTransformChangedCallback( const QwordParameters2& parameters );

private:
	//!	Reset clear buffers operations.
	_void ResetClearBuffersOperations( );

	//!	Update transforms.
	_void UpdateTransforms( );

	//!	Render character.
	_void RenderCharacter( IGraphicFont* font, _dword prev_code, _dword code, const Vector2& start_position, Vector2& position, const FontColorRHI& font_color, const Matrix3& transform, IGraphicEffect* effect );

public:
	GraphicScene( );
	virtual ~GraphicScene( );

public:
	//!	Initialize.
	_ubool Initialize( );

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
};

//----------------------------------------------------------------------------
// GraphicScene Implementation
//----------------------------------------------------------------------------

}