//! @file     Camera.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

const Camera Camera::cNull( Vector3( 0.0f, 0.0f, 0.0f ), Vector3( 0.0f, 0.0f, 0.0f ), Vector3( 0.0f, 0.0f, 0.0f ), 0.0f );

//----------------------------------------------------------------------------
// Camera Implementation
//----------------------------------------------------------------------------

Camera::Camera( )
{
 mPosition = Vector3( 100.0f, 100.0f, 100.0f );
 mLook  = Vector3::cOrigin;
 mUp   = Vector3::cZAxis;
 mRight  = Vector3::Cross( mLook - mPosition, mUp ).Normalize( );
 mFOVDegree = 45.0f;
}

Camera::Camera( const ThirdPersonCamera& camera )
{
 mLook.x  = camera.mTargetX;
 mLook.y  = camera.mTargetY;
 mLook.z  = camera.mZOffset;

 EulerAngles angle( camera.mRoll, camera.mAoA, camera.mRotation );
 Quaternion rotation;
 Math::EulerAngles2Quaternion( angle, rotation );

 mPosition = Vector3( -camera.mRange, 0.0f, 0.0f ) * rotation + mLook;

 if ( Math::Abs( mPosition.x ) < 1.0e-6 )
  mPosition.x = 0.0f;
 if ( Math::Abs( mPosition.y ) < 1.0e-6 )
  mPosition.y = 0.0f;
 if ( Math::Abs( mPosition.z ) < 1.0e-6 )
  mPosition.z = 0.0f;

 mUp   = ( Vector3::cZAxis * rotation ).Normalize( );
 mRight  = Vector3::Cross( mLook - mPosition, mUp ).Normalize( );
  
 mFOVDegree = camera.mFOV;
}

Camera::Camera( const FirstPersonCamera& camera )
{
 mPosition.x = camera.mEyeX;
 mPosition.y = camera.mEyeY;
 mPosition.z = camera.mEyeZ;

 Quaternion rot( camera.mQuatX, camera.mQuatY, camera.mQuatZ, camera.mQuatW );
 mLook = mPosition + Vector3::cYAxis * rot;
 mUp = ( Vector3::cZAxis * rot ).Normalize( );
 mRight  = Vector3::Cross( mLook - mPosition, mUp ).Normalize( );

 mFOVDegree = camera.mFOV;
}

Camera::Camera( const Vector3& position, const Vector3& look, const Vector3& up, _float fovdegree )
{
 mPosition = position;
 mLook  = look;
 mUp   = up;
 mRight  = Vector3::Cross( mLook - mPosition, mUp ).Normalize( );
 mFOVDegree = fovdegree;// 58.0 / 1.3 ~= PI / 4( old value )
}

/*
AdvanceCamera Camera::ToAdvanceCamera( ) const
{
 AdvanceCamera camera;

 camera.mTargetX = mLook.x;
 camera.mTargetY = mLook.y;
 camera.mZOffset = mLook.z;

 camera.mRange = ( mPosition - mLook ).Magnitude( );
 camera.mFOV  = mFOVDegree;

 Quaternion rotation = Quaternion( ).Rotation( -Vector3::cXAxis, mPosition - mLook );
 EulerAngles angle;
 Math::Quaternion2EulerAngles( rotation, angle );
 camera.mRotation = angle.mBank;
 camera.mAoA   = angle.mHeading;
 camera.mRoll  = angle.mPitch;
 
 return camera;
}
*/
_void Camera::LookAt( const Vector3& look )
{
 Vector3 temp = mLook;

 mLook  = look;
 mPosition = mLook + ( mPosition - temp );
 mRight  = Vector3::Cross( mLook - mPosition, mUp ).Normalize( );
}

_void Camera::Strafe( _float units )
{
 mLook  += mRight * units;
 mPosition += mRight * units;
}

_void Camera::Fly( _float units )
{
 mLook  += mUp * units;
 mPosition += mUp * units;
}

_void Camera::Radius( _float units )
{
 Vector3 direction = mPosition - mLook;
 Vector3 position = mPosition + direction.Normalize( ) * units;

 // Avoid #ind value
 if ( position.Equal( mLook ) )
  return;

 if ( Vector3::Dot( mPosition - mLook, position - mLook ) > 0.0f )
  mPosition = position;
}

_void Camera::Phi( _float radian )
{
 mPosition *= Matrix4( ).Translation( - mLook ) *
  Matrix4( ).Rotation( mUp, radian ) * Matrix4( ).Translation( mLook );

 mRight  = Vector3::Cross( mLook - mPosition, mUp ).Normalize( );
}

_void Camera::Theta( _float radian )
{
 Vector3 vector1 = Vector3::Cross( mPosition - mLook, mRight );

 mPosition *= Matrix4( ).Translation( - mLook ) *
  Matrix4( ).Rotation( mRight, radian ) * Matrix4( ).Translation( mLook );

 Vector3 vector2 = Vector3::Cross( mPosition - mLook, mRight );

 if ( Vector3::Dot( vector1, mUp ) * Vector3::Dot( vector2, mUp ) < 0.0f )
  mUp = - mUp;
}

_void Camera::PhiReverse( _float radian )
{
 mLook *= Matrix4( ).Translation( - mPosition ) *
  Matrix4( ).Rotation( mUp, radian ) * Matrix4( ).Translation( mPosition );

 mRight  = Vector3::Cross( mLook - mPosition, mUp ).Normalize( );
}

_void Camera::ThetaReverse( _float radian )
{
 Vector3 vector1 = Vector3::Cross( mLook - mPosition , mRight );

 mLook *= Matrix4( ).Translation( - mPosition ) *
  Matrix4( ).Rotation( mRight, radian ) * Matrix4( ).Translation( mPosition );

 Vector3 vector2 = Vector3::Cross( mLook - mPosition, mRight );

 if ( Vector3::Dot( vector1, mUp ) * Vector3::Dot( vector2, mUp ) < 0.0f )
  mUp = - mUp;
}

_float Camera::GetFOVRadian( ) const
{
 return Math::Degree2Radian( mFOVDegree );
}

_void Camera::SetFOVRadian( _float radian )
{
 mFOVDegree = Math::Radian2Degree( radian );
}

Camera& Camera::operator *= ( const Matrix4& transform )
{
 Vector3 translation;
 Matrix3 rotation;
 transform.ToTranslationRotation( translation, rotation );

 mPosition *= transform;
 mLook  *= transform;
 mUp   *= rotation;
 mRight  = Vector3::Cross( mLook - mPosition, mUp ).Normalize( );

 return *this;
}

Camera Camera::operator * ( const Matrix4& transform ) const
{
 Camera returncamera = *this;

 return returncamera *= transform;
}


ThirdPersonCamera Camera::Lerp( const ThirdPersonCamera& camera1, const ThirdPersonCamera& camera2, _float alpha )
{
 ThirdPersonCamera camera;

 camera.mTargetX = Math::Lerp( camera1.mTargetX, camera2.mTargetX, alpha );
 camera.mTargetY = Math::Lerp( camera1.mTargetY, camera2.mTargetY, alpha );
 camera.mZOffset = Math::Lerp( camera1.mZOffset, camera2.mZOffset, alpha );
 camera.mRange = Math::Lerp( camera1.mRange, camera2.mRange, alpha );
 camera.mFOV = Math::Lerp( camera1.mFOV, camera2.mFOV, alpha );

 Quaternion r1, r2;
 Math::EulerAngles2Quaternion( EulerAngles( camera1.mRoll, camera1.mAoA, camera1.mRotation ), r1 );
 Math::EulerAngles2Quaternion( EulerAngles( camera2.mRoll, camera2.mAoA, camera2.mRotation ), r2 );
 Quaternion result_r = Quaternion::Slerp( r1, r2, alpha );
 EulerAngles result_angle;
 Math::Quaternion2EulerAngles( result_r, result_angle );

 camera.mRoll = result_angle.mPitch;
 camera.mAoA = result_angle.mHeading;
 camera.mRotation = result_angle.mBank;

 return camera;
}