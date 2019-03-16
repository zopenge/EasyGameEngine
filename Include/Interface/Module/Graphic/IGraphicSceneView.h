//! @file     IGraphicSceneView.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicSceneView
//----------------------------------------------------------------------------

class IGraphicSceneView : public IObject
{
public:
	//!	When the transform changed.
	//!	@param		parameters	The user defined parameters.
	//!	@return		none.
	typedef _void (*OnTransformChanged)( const QwordParameters2& parameters );

public:
	//!	Set the transform changed callback function.
	//!	@param		funcpointer	The callback functions.
	//!	@param		parameters	The user defined parameters.
	//!	@return		none.
	virtual _void SetTransformChangedFunc( OnTransformChanged funcpointer, const QwordParameters2& parameters ) PURE;

	//!	Set camera.
	//!	@param		camera		The camera.
	//!	@return		none.
	virtual _void SetCamera( const Camera& camera ) PURE;
	//!	Get camera.
	//!	@param		none.
	//!	@return		The camera.
	virtual const Camera& GetCamera( ) const PURE;
	//!	Get the distance from camera.
	//!	@param		pos		The position.
	//!	@return		The distance from position to camera.
	virtual _float GetDistanceFromCamera( const Vector3& pos ) const PURE;

	//!	Get the view frustum.
	//!	@param		none.
	//!	@return		The view frustum.
	virtual const Frustum& GetViewFrustum( ) const PURE;
	//!	Get the view transform.
	//!	@param		none.
	//!	@return		The view transform.
	virtual const Matrix4& GetViewTransform( ) const PURE;

	//!	Get FovY.
	//!	@param		none.
	//!	@return		The FovY.
	virtual _float GetFovY( ) const PURE;
	//!	Set FovY.
	//!	@param		fovy		The FovY.
	//!	@return		none.
	virtual _void SetFovY( _float fovy ) PURE;

	//!	Get aspect.
	//!	@param		none.
	//!	@return		The aspect.
	virtual _float GetAspect( ) const PURE;
	//!	Set aspect.
	//!	@param		aspect		The aspect.
	//!	@return		none.
	virtual _void SetAspect( _float aspect ) PURE;

	//!	Get znear.
	//!	@param		none.
	//!	@return		The znear.
	virtual _float GetZNear( ) const PURE;
	//!	Set znear.
	//!	@param		znear		The znear.
	//!	@return		none.
	virtual _void SetZNear( _float znear ) PURE;

	//!	Get zfar.
	//!	@param		none.
	//!	@return		The zfar.
	virtual _float GetZFar( ) const PURE;
	//!	Set zfar.
	//!	@param		zfar		The zfar.
	//!	@return		none.
	virtual _void SetZFar( _float zfar ) PURE;

	//!	Set the projection transform.
	//! @param		aspect		The projection aspect.
	//! @param		znear		The projection z-near.
	//! @param		zfar		The projection z-far.
	//!	@return		none.
	virtual _void SetProjectionTransform( _float aspect, _float znear, _float zfar ) PURE;
	//!	Get the projection transform.
	//!	@param		none.
	//!	@return		The projection transform.
	virtual const Matrix4& GetProjectionTransform( ) const PURE;

	//!	Get the view * projection transform.
	//!	@param		none.
	//!	@return		The view * projection transform.
	virtual const Matrix4& GetViewProjectionTransform( ) const PURE;

	//! Set the projection is ortho mode
	//! @param		ortho		is ortho mode.
	//! @return		none.
	virtual _void SetOrthoMode( _ubool ortho ) PURE;
	//! Get the projection is ortho mode
	//! @param		none.
	//! @return		Is ortho mode.
	virtual _ubool GetOrthoMode( ) const PURE;
	//! Set ortho height
	//! @param		height		height.
	//! @return		none.
	virtual _void SetOrthoViewHeight( _float height ) PURE;
	//! Set ortho scale factor
	//! @param		factor		factor.
	//! @return		none.
	virtual _void SetOrthoScaleFactor( _float factor ) PURE;

	//!	Push the camera and projection transform.
	//!	@param		camera		The camera.
	//! @param		aspect		The projection aspect.
	//! @param		znear		The projection z-near.
	//! @param		zfar		The projection z-far.
	//!	@return		none.
	virtual _void PushCameraAndProjectionTransform( const Camera& camera, _float aspect, _float znear, _float zfar ) PURE;
	//!	Pop the camera and projection transform.
	//!	@param		none.
	//!	@return		none.
	virtual _void PopCameraAndProjectionTransform( ) PURE;
	//!	Set the camera and projection transform.
	//!	@param		camera		The camera.
	//! @param		aspect		The projection aspect.
	//! @param		znear		The projection z-near.
	//! @param		zfar		The projection z-far.
	//!	@return		none.
	virtual _void SetCameraAndProjectionTransform( const Camera& camera, _float aspect, _float znear, _float zfar ) PURE;
	//!	Set the view and projection transform.
	//!	@param		camera		The camera.
	//!	@return		none.
	virtual _void SetViewAndProjectionTransform( const FirstPersonCamera& camera, _float znear, _float zfar ) PURE;

	//!	Get the position of a 3d point on screen
	//!	@param		size		The viewport size.
	//!	@param		point		The 3d point.
	//!	@param		zsort		The zsort distance.
	//!	@return		The position on screen.
	virtual Vector2 Convert3DTo2D( const PointU& size, const Vector3& point, _float* zsort ) PURE;
	//! Get the pick ray
	//!	@param		size		The viewport size.
	//! @param		x			The x position.
	//! @param		y			The y position.
	//! @return		The pick ray.
	virtual Ray GetPickRay( const PointU& size, _int x, _int y ) PURE;

	//!	Set observer scene view.
	//!	@param		scene_view	The scene view what to be observed.
	//!	@return		none.
	virtual _void SetObserverSceneView( IGraphicSceneView* scene_view ) PURE;
	//!	Get observer scene view.
	//!	@param		none.
	//!	@return		The scene view.
	virtual IGraphicSceneView* GetObserverSceneView( ) const PURE;
};

}