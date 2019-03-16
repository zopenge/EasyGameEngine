//! @file     GraphicVRDevice.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

#if (_ENABLE_VR_SOFTWARE == 1)

//----------------------------------------------------------------------------
// GraphicVREyeSceneView Implementation
//----------------------------------------------------------------------------

GraphicVREyeSceneView::GraphicVREyeSceneView( _dword eye_index, GraphicVRDevice* device )
{
	mSceneView	= GetGraphicResourceManager( )->CreateSceneView( );

	mEyeIndex	= eye_index;
	mCamera		= Camera::cNull;
	mVRDevice	= device;
}

GraphicVREyeSceneView::~GraphicVREyeSceneView( )
{

}

_void GraphicVREyeSceneView::UpdateCamera( const Camera& camera )
{
	mCamera = camera;

	_float distance = mVRDevice->GetEyeDistance( mEyeIndex );
	mCamera.Strafe( -distance );
}

_void GraphicVREyeSceneView::SetTransformChangedFunc( OnTransformChanged funcpointer, const QwordParameters2& parameters )
{
	mSceneView->SetTransformChangedFunc( funcpointer, parameters );
}

_void GraphicVREyeSceneView::SetCamera( const Camera& camera )
{
	UpdateCamera( camera );

	mSceneView->SetCamera( mCamera );
}

const Camera& GraphicVREyeSceneView::GetCamera( ) const
{
	return mCamera;
}

_float GraphicVREyeSceneView::GetDistanceFromCamera( const Vector3& pos ) const
{
	return mSceneView->GetDistanceFromCamera( pos );
}

const Matrix4& GraphicVREyeSceneView::GetViewTransform( ) const
{
	return mSceneView->GetViewTransform( );
}

const Frustum& GraphicVREyeSceneView::GetViewFrustum( ) const
{
	return mSceneView->GetViewFrustum( );
}

_float GraphicVREyeSceneView::GetFovY( ) const
{
	return mSceneView->GetFovY( );
}

_void GraphicVREyeSceneView::SetFovY( _float fovy )
{
	mSceneView->SetFovY( fovy );
}

_float GraphicVREyeSceneView::GetAspect( ) const
{
	return mSceneView->GetAspect( );
}

void GraphicVREyeSceneView::SetAspect( _float aspect )
{
	mSceneView->SetAspect( aspect );
}

_float GraphicVREyeSceneView::GetZNear( ) const
{
	return mSceneView->GetZNear( );
}

_void GraphicVREyeSceneView::SetZNear( _float znear )
{
	mSceneView->SetZNear( znear );
}

_float GraphicVREyeSceneView::GetZFar( ) const
{
	return mSceneView->GetZFar( );
}

_void GraphicVREyeSceneView::SetZFar( _float zfar )
{
	mSceneView->SetZFar( zfar );
}

_void GraphicVREyeSceneView::SetProjectionTransform( _float aspect, _float znear, _float zfar )
{
	mSceneView->SetProjectionTransform( aspect, znear, zfar );
}

const Matrix4& GraphicVREyeSceneView::GetProjectionTransform( ) const
{
	return mSceneView->GetProjectionTransform( );
}

const Matrix4& GraphicVREyeSceneView::GetViewProjectionTransform( ) const
{
	return mSceneView->GetViewProjectionTransform( );
}

_void GraphicVREyeSceneView::SetOrthoMode( _ubool ortho )
{
	mSceneView->SetOrthoMode( ortho );
}

_ubool GraphicVREyeSceneView::GetOrthoMode( ) const
{
	return mSceneView->GetOrthoMode( );
}

_void GraphicVREyeSceneView::SetOrthoViewHeight( _float height )
{
	mSceneView->SetOrthoViewHeight( height );
}

_void GraphicVREyeSceneView::SetOrthoScaleFactor( _float factor )
{
	mSceneView->SetOrthoScaleFactor( factor );
}

_void GraphicVREyeSceneView::PushCameraAndProjectionTransform( const Camera& camera, _float aspect, _float znear, _float zfar )
{
	UpdateCamera( camera );

	mSceneView->PushCameraAndProjectionTransform( mCamera, aspect, znear, zfar );
}

_void GraphicVREyeSceneView::PopCameraAndProjectionTransform( )
{
	mSceneView->PopCameraAndProjectionTransform( );

	mCamera = mSceneView->GetCamera( );
}

_void GraphicVREyeSceneView::SetCameraAndProjectionTransform( const Camera& camera, _float aspect, _float znear, _float zfar )
{
	UpdateCamera( camera );

	mSceneView->SetCameraAndProjectionTransform( mCamera, aspect, znear, zfar );
}

_void GraphicVREyeSceneView::SetViewAndProjectionTransform( const FirstPersonCamera& fpc, _float znear, _float zfar )
{
	VREyeRHI eye_info = mVRDevice->GetEyeInfo( mEyeIndex );

	// Get the eye info
	FirstPersonCamera ovr_camera = fpc;
	Quaternion eye_rot = Quaternion( ).RotationY( Math::cPi * 0.5f ) * Quaternion( ).RotationX( -Math::cPi * 0.5f )  * Quaternion( eye_info.mTransform.mRotation.x, eye_info.mTransform.mRotation.y, eye_info.mTransform.mRotation.z, eye_info.mTransform.mRotation.w );
	Vector3 eye_pos = eye_info.mTransform.mTranslate * Quaternion( ovr_camera.mQuatX, ovr_camera.mQuatY, ovr_camera.mQuatZ, ovr_camera.mQuatW );

	Quaternion camera_rot = eye_rot * Quaternion( ovr_camera.mQuatX, ovr_camera.mQuatY, ovr_camera.mQuatZ, ovr_camera.mQuatW );

	ovr_camera.mEyeX += eye_pos.x;
	ovr_camera.mEyeY += eye_pos.y;
	ovr_camera.mEyeZ += eye_pos.z;
	ovr_camera.mQuatX = camera_rot.x;
	ovr_camera.mQuatY = camera_rot.y;
	ovr_camera.mQuatZ = camera_rot.z;
	ovr_camera.mQuatW = camera_rot.w;

	Camera ovr_eye_camera = ovr_camera;
	ovr_eye_camera.Strafe( mVRDevice->GetEyeDistance( mEyeIndex ) );
	Matrix4 view_transform = Matrix4::CreateLookAtRH( ovr_eye_camera.mPosition, ovr_eye_camera.mLook, ovr_eye_camera.mRight );
	Matrix4 proj_transform = Matrix4::CreatePerspectiveProjectionRH( eye_info.mDefaultEyeFov.mLeftTan, eye_info.mDefaultEyeFov.mRightTan, eye_info.mDefaultEyeFov.mUpTan, eye_info.mDefaultEyeFov.mDownTan, znear, zfar );

	mSceneView->SetCameraAndProjectionTransform( ovr_eye_camera, mSceneView->GetAspect( ), znear, zfar );
	mSceneView->SetFovY( ovr_camera.mFOV );
}

Vector2	GraphicVREyeSceneView::Convert3DTo2D( const PointU& size, const Vector3& point, _float* zsort )
{
	return mSceneView->Convert3DTo2D( size, point, zsort );
}

Ray GraphicVREyeSceneView::GetPickRay( const PointU& size, _int x, _int y )
{
	return mSceneView->GetPickRay( size, x, y );
}

_void GraphicVREyeSceneView::SetObserverSceneView( IGraphicSceneView* scene_view )
{
	mSceneView->SetObserverSceneView( scene_view );
}

IGraphicSceneView* GraphicVREyeSceneView::GetObserverSceneView( ) const
{
	return mSceneView->GetObserverSceneView( );
}

//----------------------------------------------------------------------------
// GraphicVRDeviceSceneView Implementation
//----------------------------------------------------------------------------

GraphicVRDeviceSceneView::GraphicVRDeviceSceneView( GraphicVRDevice* device )
{
	mSceneView			= GetGraphicResourceManager( )->CreateSceneView( );

	mEyeSceneViews[0]	= new GraphicVREyeSceneView( 0, device );
	mEyeSceneViews[1]	= new GraphicVREyeSceneView( 1, device );
}

GraphicVRDeviceSceneView::~GraphicVRDeviceSceneView( )
{
	EGE_RELEASE( mEyeSceneViews[0] );
	EGE_RELEASE( mEyeSceneViews[1] );
}

GraphicVREyeSceneView* GraphicVRDeviceSceneView::GetEyeSceneView( _dword index )
{
	return mEyeSceneViews[ index ];
}

_void GraphicVRDeviceSceneView::SetTransformChangedFunc( OnTransformChanged funcpointer, const QwordParameters2& parameters )
{
	mSceneView->SetTransformChangedFunc( funcpointer, parameters );
}

_void GraphicVRDeviceSceneView::SetCamera( const Camera& camera )
{
	mSceneView->SetCamera( camera );

	mEyeSceneViews[0]->SetCamera( camera );
	mEyeSceneViews[1]->SetCamera( camera );
}

const Camera& GraphicVRDeviceSceneView::GetCamera( ) const
{
	return mSceneView->GetCamera( );
}

_float GraphicVRDeviceSceneView::GetDistanceFromCamera( const Vector3& pos ) const
{
	return mSceneView->GetDistanceFromCamera( pos );
}

const Matrix4& GraphicVRDeviceSceneView::GetViewTransform( ) const
{
	return mSceneView->GetViewTransform( );
}

const Frustum& GraphicVRDeviceSceneView::GetViewFrustum( ) const
{
	return mSceneView->GetViewFrustum( );
}

_float GraphicVRDeviceSceneView::GetFovY( ) const
{
	return mSceneView->GetFovY( );
}

_void GraphicVRDeviceSceneView::SetFovY( _float fovy )
{
	mSceneView->SetFovY( fovy );

	mEyeSceneViews[0]->SetFovY( fovy );
	mEyeSceneViews[1]->SetFovY( fovy );
}

_float GraphicVRDeviceSceneView::GetAspect( ) const
{
	return mSceneView->GetAspect( );
}

void GraphicVRDeviceSceneView::SetAspect( _float aspect )
{
	mSceneView->SetAspect( aspect );

	mEyeSceneViews[0]->SetAspect( aspect );
	mEyeSceneViews[1]->SetAspect( aspect );
}

_float GraphicVRDeviceSceneView::GetZNear( ) const
{
	return mSceneView->GetZNear( );
}

_void GraphicVRDeviceSceneView::SetZNear( _float znear )
{
	mSceneView->SetZNear( znear );

	mEyeSceneViews[0]->SetZNear( znear );
	mEyeSceneViews[1]->SetZNear( znear );
}

_float GraphicVRDeviceSceneView::GetZFar( ) const
{
	return mSceneView->GetZFar( );
}

_void GraphicVRDeviceSceneView::SetZFar( _float zfar )
{
	mSceneView->SetZFar( zfar );

	mEyeSceneViews[0]->SetZFar( zfar );
	mEyeSceneViews[1]->SetZFar( zfar );
}

_void GraphicVRDeviceSceneView::SetProjectionTransform( _float aspect, _float znear, _float zfar )
{
	mSceneView->SetProjectionTransform( aspect, znear, zfar );

	mEyeSceneViews[0]->SetProjectionTransform( aspect, znear, zfar );
	mEyeSceneViews[1]->SetProjectionTransform( aspect, znear, zfar );
}

const Matrix4& GraphicVRDeviceSceneView::GetProjectionTransform( ) const
{
	return mSceneView->GetProjectionTransform( );
}

const Matrix4& GraphicVRDeviceSceneView::GetViewProjectionTransform( ) const
{
	return mSceneView->GetViewProjectionTransform( );
}

_void GraphicVRDeviceSceneView::SetOrthoMode( _ubool ortho )
{
	mSceneView->SetOrthoMode( ortho );

	mEyeSceneViews[0]->SetOrthoMode( ortho );
	mEyeSceneViews[1]->SetOrthoMode( ortho );
}

_ubool GraphicVRDeviceSceneView::GetOrthoMode( ) const
{
	return mSceneView->GetOrthoMode( );
}

_void GraphicVRDeviceSceneView::SetOrthoViewHeight( _float height )
{
	mSceneView->SetOrthoViewHeight( height );

	mEyeSceneViews[0]->SetOrthoViewHeight( height );
	mEyeSceneViews[1]->SetOrthoViewHeight( height );
}

_void GraphicVRDeviceSceneView::SetOrthoScaleFactor( _float factor )
{
	mSceneView->SetOrthoScaleFactor( factor );

	mEyeSceneViews[0]->SetOrthoScaleFactor( factor );
	mEyeSceneViews[1]->SetOrthoScaleFactor( factor );
}

_void GraphicVRDeviceSceneView::PushCameraAndProjectionTransform( const Camera& camera, _float aspect, _float znear, _float zfar )
{
	mSceneView->PushCameraAndProjectionTransform( camera, aspect, znear, zfar );

	mEyeSceneViews[0]->PushCameraAndProjectionTransform( camera, aspect, znear, zfar );
	mEyeSceneViews[1]->PushCameraAndProjectionTransform( camera, aspect, znear, zfar );
}

_void GraphicVRDeviceSceneView::PopCameraAndProjectionTransform( )
{
	mSceneView->PopCameraAndProjectionTransform( );

	mEyeSceneViews[0]->PopCameraAndProjectionTransform( );
	mEyeSceneViews[1]->PopCameraAndProjectionTransform( );
}

_void GraphicVRDeviceSceneView::SetCameraAndProjectionTransform( const Camera& camera, _float aspect, _float znear, _float zfar )
{
	mSceneView->SetCameraAndProjectionTransform( camera, aspect, znear, zfar );

	mEyeSceneViews[0]->SetCameraAndProjectionTransform( camera, aspect, znear, zfar );
	mEyeSceneViews[1]->SetCameraAndProjectionTransform( camera, aspect, znear, zfar );
}

_void GraphicVRDeviceSceneView::SetViewAndProjectionTransform( const FirstPersonCamera& fpc, _float znear, _float zfar )
{
	mSceneView->SetViewAndProjectionTransform( fpc, znear, zfar );

	mEyeSceneViews[0]->SetViewAndProjectionTransform( fpc, znear, zfar );
	mEyeSceneViews[1]->SetViewAndProjectionTransform( fpc, znear, zfar );
}

Vector2	GraphicVRDeviceSceneView::Convert3DTo2D( const PointU& size, const Vector3& point, _float* zsort )
{
	return mSceneView->Convert3DTo2D( size, point, zsort );
}

Ray GraphicVRDeviceSceneView::GetPickRay( const PointU& size, _int x, _int y )
{
	return mSceneView->GetPickRay( size, x, y );
}

_void GraphicVRDeviceSceneView::SetObserverSceneView( IGraphicSceneView* scene_view )
{
	mSceneView->SetObserverSceneView( scene_view );

	mEyeSceneViews[0]->SetObserverSceneView( scene_view );
	mEyeSceneViews[1]->SetObserverSceneView( scene_view );
}

IGraphicSceneView* GraphicVRDeviceSceneView::GetObserverSceneView( ) const
{
	return mSceneView->GetObserverSceneView( );
}

//----------------------------------------------------------------------------
// GraphicVRDevice Implementation
//----------------------------------------------------------------------------

GraphicVRDevice::GraphicVRDevice( )
{
	mGyroscopeSensorInfo	= Vector3::cOrigin;
	mOrientationSensorInfo	= Vector3::cOrigin;
	mCurEyeIndex			= 0;
	mCanvasSize				= PointU::cZeroPoint;
	mSceneView				= new GraphicVRDeviceSceneView( this );
}

GraphicVRDevice::~GraphicVRDevice( )
{
	EGE_RELEASE( mSceneView );

	for ( _dword i = 0; i < EGE_ARRAY_NUMBER( mCanvas ); i ++ )
		mCanvas[i].Clear( );
}

_ubool GraphicVRDevice::CreateCanvas( const PointU& client_size )
{
	// Set the canvas size
	mCanvasSize.x = Math::UpperBoundPowerOf2( client_size.x );
	mCanvasSize.y = Math::UpperBoundPowerOf2( client_size.y );

	// Create canvas
	for ( _dword i = 0; i < 2; i ++ )
	{
		// Create canvas
		mCanvas[i] = GetGraphicResourceManager( )->CreateCanvas( mCanvasSize.x, mCanvasSize.y, _GRAPHIC_SURFACE_ALL );
		if ( mCanvas[i].IsNull( ) )
		{
			WLOG_ERROR_2( L"Create VR canvas (%dx%d) failed", mCanvasSize.x, mCanvasSize.y );
			return _false;
		}

		// Use the viewport's ratio to create ratio of canvas
		PointU canvas_client_size = mSceneFromMainViewport->GetClientRatio( ).FixSizeU( mCanvasSize );

		// Set the ratio of canvas
		mCanvas[i]->SetClientSize( canvas_client_size );

		// Bind the scene view
		mCanvas[i]->SetSceneView( mSceneView->GetEyeSceneView( i ) );

		// Set the VR texture size and ID
		gDynamicRHI->SetVRRenderTargetTexID( i, mCanvas[i]->GetRenderTarget( )->GetTexture2DResID( ), mCanvasSize );
	}

	// Syn eye scene view with the current main viewport's
	IGraphicSceneView* scene_view_from_main_viewport = mSceneFromMainViewport->GetSceneView( );
	mSceneView->SetCameraAndProjectionTransform( 
		scene_view_from_main_viewport->GetCamera( ), 
		scene_view_from_main_viewport->GetAspect( ), 
		scene_view_from_main_viewport->GetZNear( ), 
		scene_view_from_main_viewport->GetZFar( ) );

	return _true;
}

_void GraphicVRDevice::DrawPoint( const Vector2& position, const Color& color )
{
	mCanvas[0]->DrawPoint( position, color );
	mCanvas[1]->DrawPoint( position, color );
}

_void GraphicVRDevice::DrawPoint( const Vector3& position, const Color& color )
{
	mCanvas[0]->DrawPoint( position, color );
	mCanvas[1]->DrawPoint( position, color );
}

_void GraphicVRDevice::DrawLine( const Vector2& start, const Vector2& end, const Color& color, _float width )
{
	mCanvas[0]->DrawLine( start, end, color, width );
	mCanvas[1]->DrawLine( start, end, color, width );
}

_void GraphicVRDevice::DrawLine( const Vector2& start, const Vector2& end, const Color& color_start, const Color& color_end, _float width )
{
	mCanvas[0]->DrawLine( start, end, color_start, color_end, width );
	mCanvas[1]->DrawLine( start, end, color_start, color_end, width );
}

_void GraphicVRDevice::DrawLine( const Vector3& start, const Vector3& end, const Color& color, _float width )
{
	mCanvas[0]->DrawLine( start, end, color, width );
	mCanvas[1]->DrawLine( start, end, color, width );
}

_void GraphicVRDevice::DrawLine( const Vector3& start, const Vector3& end, const Color& color_start, const Color& color_end, _float width )
{
	mCanvas[0]->DrawLine( start, end, color_start, width );
	mCanvas[1]->DrawLine( start, end, color_start, width );
}

_void GraphicVRDevice::DrawLine( const Line2D& line, const Color& color, _float width )
{
	mCanvas[0]->DrawLine( line, color, width );
	mCanvas[1]->DrawLine( line, color, width );
}

_void GraphicVRDevice::DrawLine( const Line3D& line, const Color& color, _float width )
{
	mCanvas[0]->DrawLine( line, color, width );
	mCanvas[1]->DrawLine( line, color, width );
}

_void GraphicVRDevice::DrawLines( const Line2DArray& lines, const Color& color, _float width )
{
	mCanvas[0]->DrawLines( lines, color, width );
	mCanvas[1]->DrawLines( lines, color, width );
}

_void GraphicVRDevice::DrawLines( const Line3DArray& lines, const Color& color, _float width )
{
	mCanvas[0]->DrawLines( lines, color, width );
	mCanvas[1]->DrawLines( lines, color, width );
}

_void GraphicVRDevice::FillTriangles( const TriangleArray& triangles, const Color& color )
{
	mCanvas[0]->FillTriangles( triangles, color );
	mCanvas[1]->FillTriangles( triangles, color );
}

_void GraphicVRDevice::DrawRectangle( const RectF& rect, const Color& color, _float width )
{
	mCanvas[0]->DrawRectangle( rect, color, width );
	mCanvas[1]->DrawRectangle( rect, color, width );
}

_void GraphicVRDevice::FillRectangle( const RectF& rect, const Color& color )
{
	mCanvas[0]->FillRectangle( rect, color );
	mCanvas[1]->FillRectangle( rect, color );
}

_void GraphicVRDevice::DrawCircle( const Vector2& center, _float radius, _dword segments, const Color& color )
{
	mCanvas[0]->DrawCircle( center, radius, segments, color );
	mCanvas[1]->DrawCircle( center, radius, segments, color );
}

_void GraphicVRDevice::FillCircle( const Vector2& center, _float radius, _dword segments, const Color& color )
{
	mCanvas[0]->FillCircle( center, radius, segments, color );
	mCanvas[1]->FillCircle( center, radius, segments, color );
}

_void GraphicVRDevice::DrawOrientedBox( const OrientedBox2D& box, const Color& color, _float width )
{
	mCanvas[0]->DrawOrientedBox( box, color, width );
	mCanvas[1]->DrawOrientedBox( box, color, width );
}

_void GraphicVRDevice::DrawAxisAlignedBox( const AxisAlignedBox& box, const Color& color, _float width )
{
	mCanvas[0]->DrawAxisAlignedBox( box, color, width );
	mCanvas[1]->DrawAxisAlignedBox( box, color, width );
}

_void GraphicVRDevice::DrawBox( const Box& box, const Color& color, _float width )
{
	mCanvas[0]->DrawBox( box, color, width );
	mCanvas[1]->DrawBox( box, color, width );
}

_void GraphicVRDevice::FillBox( const Box& box, const Color& color )
{
	mCanvas[0]->FillBox( box, color );
	mCanvas[1]->FillBox( box, color );
}

_void GraphicVRDevice::DrawXYAxis( const Vector2& origin, _float length, _float width )
{
	mCanvas[0]->DrawXYAxis( origin, length, width );
	mCanvas[1]->DrawXYAxis( origin, length, width );
}

_void GraphicVRDevice::DrawXYZAxis( const Vector3& origin, _float length, _float width )
{
	mCanvas[0]->DrawXYZAxis( origin, length, width );
	mCanvas[1]->DrawXYZAxis( origin, length, width );
}

_void GraphicVRDevice::DrawSphere( const Vector3& origin, _float radius, _float latitude, _float longitude )
{
	mCanvas[0]->DrawSphere( origin, radius, latitude, longitude );
	mCanvas[1]->DrawSphere( origin, radius, latitude, longitude );
}

_void GraphicVRDevice::DrawFrustum( const Frustum& frustum, const Color& near_plane_color, const Color& far_plane_color, const Color& line_color, _float width )
{
	mCanvas[0]->DrawFrustum( frustum, near_plane_color, far_plane_color, line_color, width );
	mCanvas[1]->DrawFrustum( frustum, near_plane_color, far_plane_color, line_color, width );
}

_void GraphicVRDevice::DrawPolygon( const Polygon2D& polygon, const Color& color, _float width )
{
	mCanvas[0]->DrawPolygon( polygon, color, width );
	mCanvas[1]->DrawPolygon( polygon, color, width );
}

_void GraphicVRDevice::DrawTriangles( const Triangle2DArray& triangles, const Color& color, _float width )
{
	mCanvas[0]->DrawTriangles( triangles, color, width );
	mCanvas[1]->DrawTriangles( triangles, color, width );
}

_void GraphicVRDevice::FillTriangles( const Triangle2DArray& triangles, const Color& color )
{
	mCanvas[0]->FillTriangles( triangles, color );
	mCanvas[1]->FillTriangles( triangles, color );
}

_void GraphicVRDevice::FillPolygon( const Polygon2D& polygon, const Color& color )
{
	mCanvas[0]->FillPolygon( polygon, color );
	mCanvas[1]->FillPolygon( polygon, color );
}

_void GraphicVRDevice::DrawSprite( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Vector2& offset, const Matrix3& transform, const Vector2& size, const GraphicUVInfo& uv_info, const Color& color )
{
	mCanvas[0]->DrawSprite( sprite, effect, vertex_offsets, offset, transform, size, uv_info, color );
	mCanvas[1]->DrawSprite( sprite, effect, vertex_offsets, offset, transform, size, uv_info, color );
}

_void GraphicVRDevice::DrawSpriteInMaskMode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Matrix3& transform, const Vector2& offset, const Vector2& size, const GraphicUVInfo& uv_info, const Color& color, IGraphicTexture2D* mask_sprite, const Matrix3& mask_transform, const Vector2& mask_offset, const Vector2& mask_size, const GraphicMaskUVInfo& mask_uv_info )
{
	mCanvas[0]->DrawSpriteInMaskMode( sprite, effect, transform, offset, size, uv_info, color, mask_sprite, mask_transform, mask_offset, mask_size, mask_uv_info );
	mCanvas[1]->DrawSpriteInMaskMode( sprite, effect, transform, offset, size, uv_info, color, mask_sprite, mask_transform, mask_offset, mask_size, mask_uv_info );
}

_void GraphicVRDevice::DrawSpriteInTriangleMode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Triangle2D& vertexs, const Triangle2D& uvs, const Color& color )
{
	mCanvas[0]->DrawSpriteInTriangleMode( sprite, effect, vertexs, uvs, color );
	mCanvas[1]->DrawSpriteInTriangleMode( sprite, effect, vertexs, uvs, color );
}

_void GraphicVRDevice::DrawSpriteInTriangleStripeMode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector3* pos_list, const Vector2* uv_list, const Color* color_list, _dword vertices_number )
{
	mCanvas[0]->DrawSpriteInTriangleStripeMode( sprite, effect, pos_list, uv_list, color_list, vertices_number );
	mCanvas[1]->DrawSpriteInTriangleStripeMode( sprite, effect, pos_list, uv_list, color_list, vertices_number );
}

_void GraphicVRDevice::DrawSpriteInQuadMode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector3* pos_list, const Color* color_list, const Vector2* uv_list, _dword vertices_number )
{
	mCanvas[0]->DrawSpriteInQuadMode( sprite, effect, pos_list, color_list, uv_list, vertices_number );
	mCanvas[1]->DrawSpriteInQuadMode( sprite, effect, pos_list, color_list, uv_list, vertices_number );
}

_void GraphicVRDevice::DrawSpriteIn3x3Mode( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2& offset, const Vector2& size, const RectU& block_region, const Matrix3& transform, const GraphicUVInfo& uv_info, const Color& color )
{
	mCanvas[0]->DrawSpriteIn3x3Mode( sprite, effect, offset, size, block_region, transform, uv_info, color );
	mCanvas[1]->DrawSpriteIn3x3Mode( sprite, effect, offset, size, block_region, transform, uv_info, color );
}

_void GraphicVRDevice::DrawScreenAlignedBillboard( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color )
{
	mCanvas[0]->DrawScreenAlignedBillboard( sprite, effect, vertex_offsets, transform, position, uv_info, color );
	mCanvas[1]->DrawScreenAlignedBillboard( sprite, effect, vertex_offsets, transform, position, uv_info, color );
}

_void GraphicVRDevice::DrawViewpointOrientedBillboard( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color )
{
	mCanvas[0]->DrawViewpointOrientedBillboard( sprite, effect, vertex_offsets, transform, position, uv_info, color );
	mCanvas[1]->DrawViewpointOrientedBillboard( sprite, effect, vertex_offsets, transform, position, uv_info, color );
}

_void GraphicVRDevice::DrawAxialBillboard( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const Vector3* scaling, const Vector3& axis, const GraphicUVInfo& uv_info, const Color& color )
{
	mCanvas[0]->DrawAxialBillboard( sprite, effect, vertex_offsets, transform, position, scaling, axis, uv_info, color );
	mCanvas[1]->DrawAxialBillboard( sprite, effect, vertex_offsets, transform, position, scaling, axis, uv_info, color );
}

_void GraphicVRDevice::DrawRectBillboard( IGraphicTexture2D* sprite, IGraphicEffect* effect, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color )
{
	mCanvas[0]->DrawRectBillboard( sprite, effect, vertex_offsets, transform, position, uv_info, color );
	mCanvas[1]->DrawRectBillboard( sprite, effect, vertex_offsets, transform, position, uv_info, color );
}

_void GraphicVRDevice::DrawSurface( const RectF& region, IGraphicSurface* surface, IGraphicEffect* effect )
{
	mCanvas[0]->DrawSurface( region, surface, effect );
	mCanvas[1]->DrawSurface( region, surface, effect );
}

_void GraphicVRDevice::DrawSurface( const RectF& region, const Vector2& uv1, const Vector2& uv2, IGraphicSurface* surface, IGraphicEffect* effect )
{
	mCanvas[0]->DrawSurface( region, uv1, uv2, surface, effect );
	mCanvas[1]->DrawSurface( region, uv1, uv2, surface, effect );
}

_void GraphicVRDevice::DrawSurface( const Vector2& position, IGraphicSurface* surface, IGraphicEffect* effect )
{
	mCanvas[0]->DrawSurface( position, surface, effect );
	mCanvas[1]->DrawSurface( position, surface, effect );
}

_void GraphicVRDevice::DrawSurface( const Vector2& position, const Vector2& size, IGraphicSurface* surface, IGraphicEffect* effect )
{
	mCanvas[0]->DrawSurface( position, size, surface, effect );
	mCanvas[1]->DrawSurface( position, size, surface, effect );
}

_void GraphicVRDevice::DrawSurface( const Vector2& position, const Vector2& size, const Vector2& uv1, const Vector2& uv2, IGraphicSurface* surface, IGraphicEffect* effect )
{
	mCanvas[0]->DrawSurface( position, size, uv2, uv2, surface, effect );
	mCanvas[1]->DrawSurface( position, size, uv2, uv2, surface, effect );
}

_void GraphicVRDevice::DrawSurface( const Matrix3& transform, const Vector2& offset, IGraphicSurface* surface, IGraphicEffect* effect )
{
	mCanvas[0]->DrawSurface( transform, offset, surface, effect );
	mCanvas[1]->DrawSurface( transform, offset, surface, effect );
}

_void GraphicVRDevice::DrawText( const Vector2& position, WStringPtr string, IGraphicFont* font, const FontColorRHI& font_color )
{
	mCanvas[0]->DrawText( position, string, font, font_color );
	mCanvas[1]->DrawText( position, string, font, font_color );
}

_void GraphicVRDevice::DrawText( const Vector2& position, WStringPtr string, IGraphicFont* font, const FontColorRHI& font_color, const Matrix3& transform )
{
	mCanvas[0]->DrawText( position, string, font, font_color, transform );
	mCanvas[1]->DrawText( position, string, font, font_color, transform );
}

_void GraphicVRDevice::DrawText( const Vector2& position, WStringPtr string, IGraphicFont* font, const FontColorRHI& font_color, const Matrix3& transform, const FontColorRHI& bk_font_color, const Vector2& bk_offset )
{
	mCanvas[0]->DrawText( position, string, font, font_color, transform, bk_font_color, bk_offset );
	mCanvas[1]->DrawText( position, string, font, font_color, transform, bk_font_color, bk_offset );
}

_void GraphicVRDevice::DrawMeshGeometry( IGraphicEffect* effect, const GraphicMeshGeometryInfo& geometry_info )
{
	mCanvas[0]->DrawMeshGeometry( effect, geometry_info );
	mCanvas[1]->DrawMeshGeometry( effect, geometry_info );
}

_void GraphicVRDevice::PushScissorRect( const RectF& rect )
{
	mCanvas[0]->PushScissorRect( rect );
	mCanvas[1]->PushScissorRect( rect );

	mSceneFromMainViewport->PushScissorRect( rect );
}

_void GraphicVRDevice::PopScissorRect( )
{
	mCanvas[0]->PopScissorRect( );
	mCanvas[1]->PopScissorRect( );

	mSceneFromMainViewport->PopScissorRect( );
}

_void GraphicVRDevice::SetScissorRect( const RectF& rect )
{
	mCanvas[0]->SetScissorRect( rect );
	mCanvas[1]->SetScissorRect( rect );

	mSceneFromMainViewport->SetScissorRect( rect );
}

const RectF& GraphicVRDevice::GetScissorRect( ) const
{
	return mSceneFromMainViewport->GetScissorRect( );
}

_void GraphicVRDevice::PushOverlayTransform( const Matrix3& transform )
{
	mCanvas[0]->PushOverlayTransform( transform );
	mCanvas[1]->PushOverlayTransform( transform );

	mSceneFromMainViewport->PushOverlayTransform( transform );
}

_void GraphicVRDevice::PopOverlayTransform( )
{
	mCanvas[0]->PopOverlayTransform( );
	mCanvas[1]->PopOverlayTransform( );

	mSceneFromMainViewport->PopOverlayTransform( );
}

_void GraphicVRDevice::SetOverlayTransform( const Matrix3& transform )
{
	mCanvas[0]->SetOverlayTransform( transform );
	mCanvas[1]->SetOverlayTransform( transform );

	mSceneFromMainViewport->SetOverlayTransform( transform );
}

const Matrix3& GraphicVRDevice::GetOverlayTransform( ) const
{
	return mSceneFromMainViewport->GetOverlayTransform( );
}

_void GraphicVRDevice::PushUserOrthoTransform( const Matrix4& transform )
{
	mCanvas[0]->PushUserOrthoTransform( transform );
	mCanvas[1]->PushUserOrthoTransform( transform );

	mSceneFromMainViewport->PushUserOrthoTransform( transform );
}

_void GraphicVRDevice::PopUserOrthoTransform( )
{
	mCanvas[0]->PopUserOrthoTransform( );
	mCanvas[1]->PopUserOrthoTransform( );

	mSceneFromMainViewport->PopUserOrthoTransform( );
}

_void GraphicVRDevice::SetUserOrthoTransform( const Matrix4& transform )
{
	mCanvas[0]->SetUserOrthoTransform( transform );
	mCanvas[1]->SetUserOrthoTransform( transform );

	mSceneFromMainViewport->SetUserOrthoTransform( transform );
}

const Matrix4& GraphicVRDevice::GetUserOrthoTransform( ) const
{
	return mSceneFromMainViewport->GetUserOrthoTransform( );
}

_void GraphicVRDevice::PushOffsetTransform( const Matrix4& transform )
{
	mCanvas[0]->PushOffsetTransform( transform );
	mCanvas[1]->PushOffsetTransform( transform );

	mSceneFromMainViewport->PushOffsetTransform( transform );
}

_void GraphicVRDevice::PopOffsetTransform( )
{
	mCanvas[0]->PopOffsetTransform( );
	mCanvas[1]->PopOffsetTransform( );

	mSceneFromMainViewport->PopOffsetTransform( );
}

_void GraphicVRDevice::SetOffsetTransform( const Matrix4& transform )
{
	mCanvas[0]->SetOffsetTransform( transform );
	mCanvas[1]->SetOffsetTransform( transform );

	mSceneFromMainViewport->SetOffsetTransform( transform );
}

const Matrix4& GraphicVRDevice::GetOffsetTransform( ) const
{
	return mSceneFromMainViewport->GetOffsetTransform( );
}

_void GraphicVRDevice::SetViewport( const Viewport& viewport )
{
	mCanvas[0]->SetViewport( viewport );
	mCanvas[1]->SetViewport( viewport );

	mSceneFromMainViewport->SetViewport( viewport );
}

const Viewport& GraphicVRDevice::GetViewport( ) const
{
	return mSceneFromMainViewport->GetViewport( );
}

_void GraphicVRDevice::SetClientSize( const PointU& size )
{
	mCanvas[0]->SetClientSize( size );
	mCanvas[1]->SetClientSize( size );

	mSceneFromMainViewport->SetClientSize( size );
}

const PointU& GraphicVRDevice::GetClientSize( ) const
{
	return mSceneFromMainViewport->GetClientSize( );
}

const Ratio& GraphicVRDevice::GetClientRatio( ) const
{
	return mSceneFromMainViewport->GetClientRatio( );
}

_void GraphicVRDevice::FlushBuffers( )
{
	mCanvas[0]->FlushBuffers( );
	mCanvas[1]->FlushBuffers( );

	mSceneFromMainViewport->FlushBuffers( );
}

_void GraphicVRDevice::ClearCaches( )
{
	mCanvas[0]->ClearCaches( );
	mCanvas[1]->ClearCaches( );

	mSceneFromMainViewport->ClearCaches( );
}

const Matrix4& GraphicVRDevice::GetViewTransform( ) const 
{
	return mSceneFromMainViewport->GetViewTransform( );
}

const Matrix4& GraphicVRDevice::GetVPTransform( ) const 
{
	return mSceneFromMainViewport->GetVPTransform( );
}

_void GraphicVRDevice::ClearRenderBuffers( _ubool clearcolor, const Color& color, _ubool cleardepth, _float depth, _ubool clearstencil, _dword stencil )
{
	mCanvas[0]->ClearRenderBuffers( clearcolor, color, cleardepth, depth, clearstencil, stencil );
	mCanvas[1]->ClearRenderBuffers( clearcolor, color, cleardepth, depth, clearstencil, stencil );

	mSceneFromMainViewport->ClearRenderBuffers( clearcolor, color, cleardepth, depth, clearstencil, stencil );
}

_void GraphicVRDevice::PresentRenderBuffers( )
{
	mCanvas[0]->PresentRenderBuffers( );
	mCanvas[1]->PresentRenderBuffers( );

	mSceneFromMainViewport->PresentRenderBuffers( );
}

_void GraphicVRDevice::PresentRenderBuffers( IGraphicCanvas* canvas )
{
	mCanvas[0]->PresentRenderBuffers( canvas );
	mCanvas[1]->PresentRenderBuffers( canvas );

	mSceneFromMainViewport->PresentRenderBuffers( canvas );
}

_void GraphicVRDevice::SetSceneView( IGraphicSceneView* view )
{
	mCanvas[0]->SetSceneView( view );
	mCanvas[1]->SetSceneView( view );

	mSceneFromMainViewport->SetSceneView( view );
}

IGraphicSceneView* GraphicVRDevice::GetSceneView( ) const
{
	return mSceneView;
}

const Viewport* GraphicVRDevice::GetLastViewport( ) 
{
	return mCanvas[ mCurEyeIndex ]->GetLastViewport( );
}

_ubool GraphicVRDevice::PickMeshes( const Ray& ray, _ubool bound_box_only, IGraphicMeshRefArray& meshes )
{
	return mSceneFromMainViewport->PickMeshes( ray, bound_box_only, meshes );
}

_ubool GraphicVRDevice::PickMeshes( const AxisAlignedBox& box, _ubool bound_box_only, IGraphicMeshRefArray& meshes )
{
	return mSceneFromMainViewport->PickMeshes( box, bound_box_only, meshes );
}

IGraphicMeshPassRef	GraphicVRDevice::AddMesh( IGeometryMeshChunk* mesh_chunk )
{
	return mSceneFromMainViewport->AddMesh( mesh_chunk );
}

Vector2 GraphicVRDevice::Convert3DTo2D( const Vector3& point, _float* zsort )
{
	return mSceneFromMainViewport->Convert3DTo2D( point, zsort );
}

Vector2 GraphicVRDevice::Convert3DTo2D( const PointU& size, const Vector3& point, _float* zsort )
{
	return mSceneFromMainViewport->Convert3DTo2D( size, point, zsort );
}

Ray GraphicVRDevice::GetPickRay( _int x, _int y )
{
	return mSceneFromMainViewport->GetPickRay( x, y );
}

Ray GraphicVRDevice::GetPickRay( const PointU& size, _int x, _int y )
{
	return mSceneFromMainViewport->GetPickRay( size, x, y );
}

_ubool GraphicVRDevice::Initialize( )
{
	// Save the scene from main viewport
	mSceneFromMainViewport = GetGraphicViewport( )->GetSceneProxy( );
	if ( mSceneFromMainViewport.IsNull( ) )
		return _false;

	// Replace the scene of main viewport
	GetGraphicViewport( )->SetSceneProxy( this );

	// Create canvas 
	if ( CreateCanvas( GetMainViewBasedApp( )->GetSize( ) ) == _false )
		return _false;

	return _true;
}

_void GraphicVRDevice::HandleEvent( EventBase& event )
{
	switch ( event.mEventID )
	{
		case _EVENT_CLIENT_SIZE_CHANGED:
		{
			const EventClientSizeChanged& msg = (const EventClientSizeChanged&)event;
			
			// Get the half of client region
			PointU half_client_size = msg.mClientSize;
			half_client_size.x /= 2;

			// Create canvas
			CreateCanvas( half_client_size );
		}
		break;

		case _EVENT_GYROSCOPE_SNESOR:
		{
			const EventGyroscopeSensor& msg = (const EventGyroscopeSensor&) event;

			mGyroscopeSensorInfo.x = msg.mX;
			mGyroscopeSensorInfo.y = msg.mY;
			mGyroscopeSensorInfo.z = msg.mZ;
		}
		break;

		case _EVENT_ORIENTATION_SNESOR:
		{
			const EventOrientationSensor& msg = (const EventOrientationSensor&) event;

			mOrientationSensorInfo.x = msg.mX;
			mOrientationSensorInfo.y = msg.mY;
			mOrientationSensorInfo.z = msg.mZ;
		}
		break;

		default:
			break;
	}
}

_void GraphicVRDevice::Present( )
{
	// Present canvas
	mCanvas[0]->PresentRenderBuffers( );
	mCanvas[1]->PresentRenderBuffers( );

//#if 1
//	static _ubool sSave = _false;
//	if ( sSave )
//	{
//		mCanvas[0]->GetRenderTarget( )->SaveToFile( _FF_PNG, L"canvas_left.png", _true, _false );
//		mCanvas[1]->GetRenderTarget( )->SaveToFile( _FF_PNG, L"canvas_right.png", _true, _false );
//	}
//#endif

	// Set the client size
	PointU client_size = GetMainViewBasedApp( )->GetClientSize( );
	mSceneFromMainViewport->SetClientSize( client_size );

	// The draw regions
	const RectF draw_regions[2] =
	{
		RectF( ).InitWithSize( 0.0f,							0.0f, (_float)client_size.x / 2.0f, (_float)client_size.y ),
		RectF( ).InitWithSize( (_float)client_size.x / 2.0f,	0.0f, (_float)client_size.x / 2.0f, (_float)client_size.y ),
	};

	// Get the viewport (canvas has the viewport info, so use each of them is all right)
	const Viewport& viewport = mCanvas[0]->GetViewport( );

	// Update the viewport size
	_dword canvas_width		= (_dword)(viewport.x * 2.0f + viewport.w);
	_dword canvas_height	= (_dword)(viewport.y * 2.0f + viewport.h);

	// Get the UVs
	_float u = Math::Min< _float >( 1.0f, EGE_RATIO( canvas_width, mCanvasSize.x ) );
	_float v = Math::Min< _float >( 1.0f, EGE_RATIO( canvas_height, mCanvasSize.y ) );

	// Build the UVs
	Vector2 uv_1( 0.0f, v );
	Vector2 uv_2( u, 0.0f );

	// Get the effect
	IGraphicEffectRef effect = GetGraphicResourceManager( )->CreateEffectFromResName( WSTROBJ( eTex0 ) );

	// Draw the surfaces
	mSceneFromMainViewport->DrawSurface( draw_regions[0], uv_1, uv_2, mCanvas[0]->GetRenderTarget( ), effect );
	mSceneFromMainViewport->DrawSurface( draw_regions[1], uv_1, uv_2, mCanvas[1]->GetRenderTarget( ), effect );

	// Draw center vert line to screen
	_float center_x = (_float)(mSceneFromMainViewport->GetClientSize( ).x) / 2.0f;
	mSceneFromMainViewport->DrawLine( Vector2( center_x, 0.0f ), Vector2( center_x, (_float)mSceneFromMainViewport->GetClientSize( ).y ), Color::cWhite, 1.0f );
}

_float GraphicVRDevice::GetEyeDistance( _dword index ) const
{
	EGE_ASSERT( index < 2 );

	static const _float sDistances[2] = {0.032f, -0.032f};
	return sDistances[index];
}

VREyeRHI GraphicVRDevice::GetEyeInfo( _dword index ) const
{
	_float distance = GetEyeDistance( index );

	// Get the current sensor info
	_float x = mOrientationSensorInfo.x;
	_float y = mOrientationSensorInfo.y;
	_float z = mOrientationSensorInfo.z;
	_float w = 1.0f;

	// Get the rotation
	Quaternion quat( x, y, z, w );
	quat *= Quaternion( ).RotationX( Math::cPi * 0.5f );

	// Get the offset
	Vector3 offset( distance, 0.0f, 0.0f );
	offset *= Quaternion( ).RotationX( Math::cPi * 0.5f );

	// Update eye info
	VREyeRHI eye_info;
	eye_info			= gDynamicRHI->GetVREyeInfo( index );
	eye_info.mTransform	= Transform3D( quat, offset );

	return eye_info;
}

#endif