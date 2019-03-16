//! @file     GraphicLight.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicLight Implementation
//----------------------------------------------------------------------------

GraphicLight::GraphicLight( )
{
	mRange					= 100.0f;
	mAttenuation			= 0.0f;
	mColor					= Color::cWhite;

	mCamera					= Camera( Vector3::cIdentity* 100.0f, Vector3::cOrigin, Vector3::cZAxis );
	mAspect					= 1.2f;

	mProjTextureTransform	= Matrix4::cIdentity;
	mViewFrustum			= Frustum( Matrix4::cIdentity, Matrix4::cIdentity );

	mProjectiveTexturePower = 1.0f;
}

GraphicLight::~GraphicLight( )
{
}

_float GraphicLight::GetNear( _float f ) const
{
	if ( f < 1000.0f )
		return f * 0.001f;

	return 1.0f;
}

_void GraphicLight::Update( )
{
	// This is matrix transform every coordinate x,y,z
	// x = x* 0.5 + 0.5 
	// y = y* 0.5 + 0.5 
	// z = z* 0.5 + 0.5 
	// Moving from unit cube [-1,1] to [0,1] 
	static Matrix4 bias(
		0.5f, 0.0f, 0.0f, 0.0f, 
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f );

	// Compute the MVP matrix from the light's point of view
	_float fov = mCamera.GetFOVRadian( );

	Matrix4 view_transform			= Matrix4::CreateLookAtRH( mCamera.mPosition, mCamera.mLook, mCamera.mUp );
	Matrix4 projection_transform	= Matrix4::CreatePerspectiveFovRH( fov, mAspect, GetNear( mRange ), mRange );
	
	// Update depth transform
	mProjTextureTransform  = view_transform;
	mProjTextureTransform *= projection_transform; 
	mProjTextureTransform *= bias;

	// Update view frustum
	mViewFrustum = Frustum( view_transform, projection_transform );
}

IObject* GraphicLight::CloneTo( _ubool standalone ) const
{
	GraphicLight* light				= new GraphicLight( );
	light->mRange					= mRange;
	light->mAttenuation				= mAttenuation;
	light->mColor					= mColor;
	light->mCamera					= mCamera;					
	light->mAspect					= mAspect;
	light->mViewFrustum				= mViewFrustum;
	light->mProjTextureTransform	= mProjTextureTransform;
	light->mProjectiveTexturePower	= mProjectiveTexturePower;
	light->mProjectiveTexture		= mProjectiveTexture;

	return light;
}

_void GraphicLight::SetPosition( const Vector3& position )
{
	if ( mCamera.mPosition == position )
		return;

	mCamera.mPosition = position;

	Update( );
}

const Vector3& GraphicLight::GetPosition( ) const
{
	return mCamera.mPosition;
}

_void GraphicLight::SetRange( _float range )
{
	if ( mRange == range )
		return;

	mRange = range;

	Update( );
}

_float GraphicLight::GetRange( ) const
{
	return mRange;
}

_void GraphicLight::SetAspect( _float aspect )
{
	if ( mAspect == aspect )
		return;

	mAspect = aspect;

	Update( );	
}

_float GraphicLight::GetAspect( ) const
{
	return mAspect;
}

_void GraphicLight::SetFovDegree( _float fov )
{
	if ( mCamera.GetFOVDegree( ) == fov )
		return;

	mCamera.SetFOVDegree( fov );

	Update( );
}

_float GraphicLight::GetFovDegree( ) const
{
	return mCamera.GetFOVDegree( );
}

_void GraphicLight::SetColor( const Color& color )
{
	mColor = color;
}

const Color& GraphicLight::GetColor( ) const
{
	return mColor;
}

_void GraphicLight::SetAttenuation( _float value )
{
	mAttenuation = value;
}

_float GraphicLight::GetAttenuation( ) const
{
	return mAttenuation;
}

_void GraphicLight::SetCamera( const Camera& camera )
{
	if ( mCamera == camera )
		return;

	mCamera = camera;

	Update( );
}

_void GraphicLight::SetCamera( const Camera& camera, _float aspect, _float range )
{
	mCamera	= camera;
	mAspect	= aspect;
	SetPosition( camera.mPosition );
	SetRange( range );

	Update( );
}

const Camera& GraphicLight::GetCamera( ) const
{
	return mCamera;
}

const Frustum& GraphicLight::GetViewFrustum( ) const
{
	return mViewFrustum;
}

const Matrix4& GraphicLight::GetProjTextureTransform( ) const
{
	return mProjTextureTransform;
}

_void GraphicLight::SetProjectiveTexture( IGraphicTexture2D* texture )
{
	mProjectiveTexture = texture;
}

IGraphicTexture2D* GraphicLight::GetProjectiveTexture( ) const
{
	return mProjectiveTexture.GetPtr( );
}

_void GraphicLight::SetProjTexturePower( _float power )
{
	mProjectiveTexturePower = power;
}

_float GraphicLight::GetProjTexturePower( ) const
{
	return mProjectiveTexturePower;
}