//! @file     Camera.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Camera
//----------------------------------------------------------------------------

class Camera
{
public:
	static const Camera cNull;

public:
	Vector3	mPosition;
	Vector3	mLook;
	Vector3	mUp;
	Vector3	mRight;

private:
	_float  mFOVDegree;

public:
	Camera( );
	Camera( const ThirdPersonCamera& camera );
	Camera( const FirstPersonCamera& camera );
	Camera( const Vector3& position, const Vector3& look, const Vector3& up, _float fovdegree = 58.0f );

public:
	EGE_GET_SET_ACCESSOR_CONST( _float, FOVDegree )

public:
	_void LookAt( const Vector3& look );

	_void Strafe( _float units );
	_void Fly( _float units );

	_void Radius( _float units );
	_void Phi( _float radian );
	_void Theta( _float radian );

	_void PhiReverse( _float radian );
	_void ThetaReverse( _float radian );

	_float GetFOVRadian( ) const;
	_void SetFOVRadian( _float radian );

	//AdvanceCamera ToAdvanceCamera( ) const;

	Camera& operator *= ( const Matrix4& transform );
	Camera operator * ( const Matrix4& transform ) const;

	inline _ubool operator == ( const Camera& camera ) const;
	inline _ubool operator != ( const Camera& camera ) const;

	static ThirdPersonCamera Lerp( const ThirdPersonCamera& camera1, const ThirdPersonCamera& camera2, _float alpha );
};

//----------------------------------------------------------------------------
// Camera Implementation
//----------------------------------------------------------------------------

_ubool Camera::operator == ( const Camera& camera ) const
{
	return mPosition == camera.mPosition && mLook == camera.mLook && mUp == camera.mUp && mRight == camera.mRight && mFOVDegree == camera.mFOVDegree;
}

_ubool Camera::operator != ( const Camera& camera ) const
{
	return mPosition != camera.mPosition || mLook != camera.mLook || mUp != camera.mUp || mRight != camera.mRight || mFOVDegree != camera.mFOVDegree;
}

}