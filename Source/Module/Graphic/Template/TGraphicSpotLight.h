//! @file     TGraphicSpotLight.h
//! @author   LiCode
//! @version  1.1
//! @date     2015.06
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TGraphicSpotLight
//----------------------------------------------------------------------------

template< typename Type >
class TGraphicSpotLight : public TGraphicLight< Type >
{
public:
	typedef TGraphicLight< Type >	TBassClass;
protected:
	Camera							mCamera;
	_float							mAspect;
	Frustum							mViewFrustum;
	Matrix4							mProjTextureMatrix;
public:
	TGraphicSpotLight( );
	virtual ~TGraphicSpotLight( );

private:
	_float							GetNear( _float f );

public:
	virtual _void					SetAspect( _float aspect ) override;
	virtual _float					GetAspect( ) const override;
	virtual _void					SetSpotAngle( _float fov ) override;
	virtual _float					GetSpotAngle( ) const override;
	virtual _void					SetCamera( const Camera& camera ) override;
	virtual const Camera&			GetCamera( ) const override;
	virtual _void					SetInfo( const Camera& camera, _float aspect, _float f ) override;
	virtual const Frustum&			GetViewFrustum( ) const override;
	virtual const Matrix4&			GetProjTextureMatrix( ) const override;

	virtual _void					SetPosition( const Vector3& position ) override;
	virtual _void					SetRange( _float range ) override;

	virtual _void					Update( );
};

//----------------------------------------------------------------------------
// TGraphicSpotLight Implementation
//----------------------------------------------------------------------------

template< typename Type >
TGraphicSpotLight< Type >::TGraphicSpotLight( )
{
	this->mCamera				= Camera( Vector3::cIdentity* 100.0f, Vector3::cOrigin, Vector3::cZAxis );
	this->mAspect				= 1.2f;

	this->mProjTextureMatrix	= Matrix4::cIdentity;
	this->mViewFrustum			= Frustum( Matrix4::cIdentity, Matrix4::cIdentity );
}

template< typename Type >
TGraphicSpotLight< Type >::~TGraphicSpotLight( )
{
}

template< typename Type >
_float TGraphicSpotLight< Type >::GetNear( _float f )
{
	if ( f < 1000.0f )
		return f * 0.001f;

	return 1.0f;
}

template< typename Type >
_void TGraphicSpotLight< Type >::SetAspect( _float aspect )
{
	if ( this->mAspect == aspect )
		return;

	this->mAspect = aspect;

	Update( );
}

template< typename Type >
_void TGraphicSpotLight< Type >::SetSpotAngle( _float fov )
{
	if ( this->mCamera.GetFOVDegree( ) == fov )
		return;

	this->mCamera.SetFOVDegree( fov );

	Update( );
}

template< typename Type >
_void TGraphicSpotLight< Type >::SetCamera( const Camera& camera )
{
	if ( this->mCamera == camera )
		return;

	this->mCamera = camera;

	Update( );
}

template< typename Type >
_void TGraphicSpotLight< Type >::SetInfo( const Camera& camera, _float aspect, _float f )
{
	this->mCamera	= camera;
	this->mAspect	= aspect;
	TBassClass::SetPosition( camera.mPosition );
	TBassClass::SetRange( f );

	Update( );
}

template< typename Type >
_void TGraphicSpotLight< Type >::SetPosition( const Vector3& position )
{
	TBassClass::SetPosition( position );
	
	if ( this->mCamera.mPosition == position )
		return;

	this->mCamera.mPosition = position;

	Update( );
}

template< typename Type >
_void TGraphicSpotLight< Type >::SetRange( _float range )
{
	if ( this->mRange == range )
		return;

	TBassClass::SetRange( range );

	Update( );
}

template< typename Type >
_void TGraphicSpotLight< Type >::Update( )
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
	_float fov = this->mCamera.GetFOVRadian( );

	Matrix4 view_transform			= Matrix4::CreateLookAtRH( this->mCamera.mPosition, this->mCamera.mLook, this->mCamera.mUp );
	Matrix4 projection_transform	= Matrix4::CreatePerspectiveFovRH( fov, this->mAspect, GetNear( this->mRange ), this->mRange );
	
	// Update depth transform
	this->mProjTextureMatrix  = view_transform;
	this->mProjTextureMatrix *= projection_transform; 
	this->mProjTextureMatrix *= bias;

	// Update view frustum
	this->mViewFrustum = Frustum( view_transform, projection_transform );
}

template< typename Type >
_float TGraphicSpotLight< Type >::GetAspect( ) const
{
	return this->mAspect;
}

template< typename Type >
_float TGraphicSpotLight< Type >::GetSpotAngle( ) const
{
	return this->mCamera.GetFOVDegree( );
}

template< typename Type >
const Camera& TGraphicSpotLight< Type >::GetCamera( ) const
{
	return this->mCamera;
}

template< typename Type >
const Frustum& TGraphicSpotLight< Type >::GetViewFrustum( ) const
{
	return this->mViewFrustum;
}

template< typename Type >
const Matrix4& TGraphicSpotLight< Type >::GetProjTextureMatrix( ) const
{
	return this->mProjTextureMatrix;
}

}