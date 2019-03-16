//! @file     Matrix4Adjustor.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Matrix4Adjustor Implementation
//----------------------------------------------------------------------------

Matrix4Adjustor::Matrix4Adjustor( )
{
 mTranslation   = Vector3::cOrigin;
 mTranslationDuration = 0;
 mTranslationTickCount = 0;

 mScaling    = Vector3::cIdentity;
 mScalingDuration  = 0;
 mScalingTickCount  = 0;

 mRotation    = Vector3::cOrigin;
 mRotationDuration  = 0;
 mRotationTickCount  = 0;

 mHeight     = 0.0f;
 mHeightDuration   = 0;
 mHeightTickCount  = 0;
}

_void Matrix4Adjustor::Translation( _float x, _float y, _float z, _dword duration )
{
 Translation( Vector3( x, y, z ), duration );
}

_void Matrix4Adjustor::Translation( const Vector3& vector, _dword duration )
{
 mTranslation = vector;

 mTranslationDuration  = duration;
 mTranslationTickCount = 0;
}

_void Matrix4Adjustor::Scaling( _float x, _float y, _float z, _dword duration )
{
 Scaling( Vector3( x, y, z ), duration );
}

_void Matrix4Adjustor::Scaling( const Vector3& vector, _dword duration )
{
 mScaling = vector;

 mScalingDuration  = duration;
 mScalingTickCount = 0;
}

_void Matrix4Adjustor::Rotation( _float x, _float y, _float z, _dword duration )
{
 Rotation( Vector3( x, y, z ), duration );
}

_void Matrix4Adjustor::Rotation( const Vector3& vector, _dword duration )
{
 mRotation = vector;

 mRotationDuration  = duration;
 mRotationTickCount = 0;
}

_void Matrix4Adjustor::Height( _float height, _dword duration )
{
 mHeight = height;

 mHeightDuration  = duration;
 mHeightTickCount = 0;
}

_void Matrix4Adjustor::Tick( _dword elapse )
{
 if ( mTranslationDuration > 0 )
 {
  mTranslationTickCount += elapse;

  if ( mTranslationTickCount >= mTranslationDuration )
  {
   mTranslation   = Vector3::cOrigin;
   mTranslationDuration = 0;
   mTranslationTickCount = 0;
  }
 }

 if ( mScalingDuration > 0 )
 {
  mScalingTickCount += elapse;

  if ( mScalingTickCount >= mScalingDuration )
  {
   mScaling    = Vector3::cIdentity;
   mScalingDuration  = 0;
   mScalingTickCount  = 0;
  }
 }

 if ( mRotationDuration > 0 )
 {
  mRotationTickCount += elapse;

  if ( mRotationTickCount >= mRotationDuration )
  {
   mRotation    = Vector3::cOrigin;
   mRotationDuration  = 0;
   mRotationTickCount  = 0;
  }
 }

 if ( mHeightDuration > 0 )
 {
  mHeightTickCount += elapse;

  if ( mHeightTickCount >= mHeightDuration )
  {
   mHeight     = 0.0f;
   mHeightDuration   = 0;
   mHeightTickCount  = 0;
  }
 }
}

Matrix4 Matrix4Adjustor::AdjustMatrix( const Matrix4& matrix ) const
{
 if ( mTranslationTickCount == mTranslationDuration &&
   mScalingTickCount  == mScalingDuration &&
   mRotationTickCount  == mRotationDuration &&
   mHeightTickCount  == mHeightDuration )
 {
  return matrix;
 }

 _float translationalpha = GetTranslationProgress( );
 _float scalingalpha  = GetScalingProgress( );
 _float rotationalpha = GetRotationProgress( );
 _float heightalpha  = GetHeightProgress( );

 Matrix4 result = matrix;

 // Scaling.
 if ( scalingalpha > 0.0f )
 {
  scalingalpha *= scalingalpha;

  result = Matrix4( ).Scaling( mScaling * scalingalpha ) * result;
 }

 // Rotation.
 if ( rotationalpha > 0.0f )
 {
  rotationalpha *= rotationalpha;

  if ( mRotation.x != 0.0f )
   result = Matrix4( ).RotationZ( mRotation.x * rotationalpha ) * result;

  if ( mRotation.y != 0.0f )
   result = Matrix4( ).RotationY( mRotation.y * rotationalpha ) * result;

  if ( mRotation.z != 0.0f )
   result = Matrix4( ).RotationZ( mRotation.z * rotationalpha ) * result;
 }

 // Translation.
 if ( translationalpha > 0.0f )
 {
  translationalpha *= translationalpha;

  result.m[3][0] += mTranslation.x * translationalpha;
  result.m[3][1] += mTranslation.y * translationalpha;
  result.m[3][2] += mTranslation.z * translationalpha;
 }

 // Height.
 if ( heightalpha > 0.0f )
  result.m[3][2] += mHeight * heightalpha;

 return result;
}