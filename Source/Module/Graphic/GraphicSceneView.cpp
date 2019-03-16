//! @file     GraphicSceneView.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicSceneView Implementation
//----------------------------------------------------------------------------

GraphicSceneView::GraphicSceneView( )
{
	mViewTransformRH			= Matrix4::cIdentity;
	mProjectionTransformRH		= Matrix4::cIdentity;
	mViewProjectionTransformRH	= Matrix4::cIdentity;
	mViewFrustumRH				= Frustum( Matrix4::cIdentity, Matrix4::cIdentity );

	mOrthoMode					= _false;
	mOrthoViewSize				= Vector2( 1024, 1024 );
	mOrthoScaleFactor			= 1000.0f;

	mCameraAndProjections.Push( CameraAndProjectionInfo( ) );
}

GraphicSceneView::~GraphicSceneView( )
{
}

_void GraphicSceneView::UpdateProjectionTransform( )
{
	const CameraAndProjectionInfo& info = mCameraAndProjections.Top( );

	if ( mOrthoMode )
	{
		mOrthoViewSize.x = mOrthoViewSize.y * info.mAspect;

		_float cdistance = (info.mCamera.mLook - info.mCamera.mPosition).Magnitude( );
		_float czoom = 0.0f;
		if ( cdistance > Math::cFloatEpsilon )
			czoom = mOrthoScaleFactor / cdistance;

		mProjectionTransformRH = Matrix4::CreateOrthoRH( mOrthoViewSize.x, mOrthoViewSize.y, info.mZNear, info.mZFar );
		mProjectionTransformRH *= Matrix4( ).Scaling( czoom, czoom, 1.0f );
	}
	else
	{
		mProjectionTransformRH = Matrix4::CreatePerspectiveFovRH( info.mCamera.GetFOVRadian( ), info.mAspect, info.mZNear, info.mZFar );
	}

	mViewFrustumRH = Frustum( mViewTransformRH, mProjectionTransformRH );

	mViewProjectionTransformRH = mViewTransformRH * mProjectionTransformRH;

	// Notify outside we have changed transforms
	mTransformChangedFunc.Invoke( );
}

_void GraphicSceneView::UpdateCamera( )
{
	const CameraAndProjectionInfo& info = mCameraAndProjections.Top( );

	mViewTransformRH = Matrix4::CreateLookAtRH( info.mCamera.mPosition, info.mCamera.mLook, info.mCamera.mUp );
}

_void GraphicSceneView::SetTransformChangedFunc( OnTransformChanged funcpointer, const QwordParameters2& parameters )
{
	mTransformChangedFunc.Init( funcpointer, parameters );
}

_void GraphicSceneView::SetCamera( const Camera& camera )
{
	CameraAndProjectionInfo& info = mCameraAndProjections.Top( );

	if ( info.mCamera == camera )
		return;

	info.mCamera = camera;

	UpdateCamera( );
	UpdateProjectionTransform( );
}

const Camera& GraphicSceneView::GetCamera( ) const
{
	const CameraAndProjectionInfo& info = mCameraAndProjections.Top( );

	return info.mCamera;
}

_float GraphicSceneView::GetDistanceFromCamera( const Vector3& pos ) const
{
	return Vector3( pos - GetCamera( ).mPosition ).MagnitudeSquared( );
}

const Matrix4& GraphicSceneView::GetViewTransform( ) const
{
	return mViewTransformRH;
}

const Frustum& GraphicSceneView::GetViewFrustum( ) const
{
	return mViewFrustumRH;
}

_float GraphicSceneView::GetFovY( ) const
{
	const CameraAndProjectionInfo& info = mCameraAndProjections.Top( );

	return info.mCamera.GetFOVRadian( );
}

_void GraphicSceneView::SetFovY( _float fovy )
{
	CameraAndProjectionInfo& info = mCameraAndProjections.Top( );

	if ( Math::Equal( info.mCamera.GetFOVRadian( ), fovy ) )
		return;

	info.mCamera.SetFOVRadian( fovy );

	UpdateProjectionTransform( );
}

_float GraphicSceneView::GetAspect( ) const
{
	const CameraAndProjectionInfo& info = mCameraAndProjections.Top( );

	return info.mAspect;
}

_void GraphicSceneView::SetAspect( _float aspect )
{
	CameraAndProjectionInfo& info = mCameraAndProjections.Top( );

	if ( Math::Equal( info.mAspect, aspect ) )
		return;

	info.mAspect = aspect;

	UpdateProjectionTransform( );
}

_float GraphicSceneView::GetZNear( ) const
{
	const CameraAndProjectionInfo& info = mCameraAndProjections.Top( );

	return info.mZNear;
}

_void GraphicSceneView::SetZNear( _float znear )
{
	CameraAndProjectionInfo& info = mCameraAndProjections.Top( );

	if ( Math::Equal( info.mZNear, znear ) )
		return;

	info.mZNear = znear;

	UpdateProjectionTransform( );
}

_float GraphicSceneView::GetZFar( ) const
{
	const CameraAndProjectionInfo& info = mCameraAndProjections.Top( );

	return info.mZFar;
}

_void GraphicSceneView::SetZFar( _float zfar )
{
	CameraAndProjectionInfo& info = mCameraAndProjections.Top( );

	if ( Math::Equal( info.mZFar, zfar ) )
		return;

	info.mZFar = zfar;

	UpdateProjectionTransform( );
}

_void GraphicSceneView::SetProjectionTransform( _float aspect, _float znear, _float zfar )
{
	CameraAndProjectionInfo& info = mCameraAndProjections.Top( );

	if ( Math::Equal( info.mAspect, aspect ) && Math::Equal( info.mZNear, znear ) && Math::Equal( info.mZFar, zfar ) )
		return;

	info.mAspect	= aspect;
	info.mZNear		= znear;
	info.mZFar		= zfar;

	UpdateProjectionTransform( );
}

const Matrix4& GraphicSceneView::GetProjectionTransform( ) const
{
	return mProjectionTransformRH;
}

const Matrix4& GraphicSceneView::GetViewProjectionTransform( ) const
{
	return mViewProjectionTransformRH;
}

_void GraphicSceneView::SetOrthoMode( _ubool ortho )
{
	if ( mOrthoMode == ortho )
		return;

	mOrthoMode = ortho;

	UpdateProjectionTransform( );
}

_ubool GraphicSceneView::GetOrthoMode( ) const
{
	return mOrthoMode;
}

_void GraphicSceneView::SetOrthoViewHeight( _float height )
{
	if ( Math::Equal( mOrthoViewSize.y, height ) )
		return;

	mOrthoViewSize.y = height;

	UpdateProjectionTransform( );
}

_void GraphicSceneView::SetOrthoScaleFactor( _float factor )
{
	if ( Math::Equal( mOrthoScaleFactor, factor ) )
		return;

	mOrthoScaleFactor = factor;

	UpdateProjectionTransform( );
}

_void GraphicSceneView::PushCameraAndProjectionTransform( const Camera& camera, _float aspect, _float znear, _float zfar )
{
	CameraAndProjectionInfo info;
	info.mCamera	= camera;
	info.mAspect	= aspect;
	info.mZNear		= znear;
	info.mZFar		= zfar;

	mCameraAndProjections.Push( info );

	UpdateCamera( );
	UpdateProjectionTransform( );
}

_void GraphicSceneView::PopCameraAndProjectionTransform( )
{
	if ( mCameraAndProjections.Number( ) == 1 )
		return;

	mCameraAndProjections.Pop( );

	UpdateCamera( );
	UpdateProjectionTransform( );
}

_void GraphicSceneView::SetCameraAndProjectionTransform( const Camera& camera, _float aspect, _float znear, _float zfar )
{
	CameraAndProjectionInfo& info = mCameraAndProjections.Top( );

	_ubool update_camera		= info.mCamera != camera;
	_ubool update_projection	= !Math::Equal( info.mAspect, aspect ) || !Math::Equal( info.mZNear, znear ) || !Math::Equal( info.mZFar, zfar );

	if ( update_camera )
	{
		info.mCamera = camera;

		UpdateCamera( );

		if ( update_projection == _false )
			UpdateProjectionTransform( );
	}

	if ( update_projection )
	{
		info.mAspect	= aspect;
		info.mZNear		= znear;
		info.mZFar		= zfar;

		UpdateProjectionTransform( );
	}
}

_void GraphicSceneView::SetViewAndProjectionTransform( const FirstPersonCamera& fpc, _float znear, _float zfar )
{
	Camera first_camera = fpc;

	CameraAndProjectionInfo& info = mCameraAndProjections.Top( );

	_ubool update_camera		= info.mCamera != first_camera;
	_ubool update_projection	= !Math::Equal( info.mZNear, znear ) || !Math::Equal( info.mZFar, zfar );

	if ( update_camera )
	{
		info.mCamera = first_camera;

		UpdateCamera( );

		if ( update_projection == _false )
			UpdateProjectionTransform( );
	}

	if ( update_projection )
	{
		info.mZNear	= znear;
		info.mZFar	= zfar;

		UpdateProjectionTransform( );
	}
}

Vector2	GraphicSceneView::Convert3DTo2D( const PointU& size, const Vector3& point, _float* zsort )
{
	Vector3 final = point * GetViewProjectionTransform( );
	if ( zsort != _null )
		*zsort = final.z;

	return Vector3::Convert3DTo2D( size, final );
}

Ray GraphicSceneView::GetPickRay( const PointU& size, _int x, _int y )
{
	const Matrix4& view_transform = GetViewTransform( );
	const Matrix4& project_transform = GetProjectionTransform( );

	return Ray::GetPickRay( x, y, size, view_transform, project_transform );
}

_void GraphicSceneView::SetObserverSceneView( IGraphicSceneView* scene_view )
{
	mObserverSceneView = scene_view;
}

IGraphicSceneView* GraphicSceneView::GetObserverSceneView( ) const
{
	return mObserverSceneView.GetPtr( );
}
