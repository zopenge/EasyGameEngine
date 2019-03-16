//! @file     Triangle2D.cpp
//! @author   foreven
//! @version  1.1
//! @date     2012.11.27
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Triangle Implementation
//----------------------------------------------------------------------------

_ubool Triangle2D::PointInTriangle( const Vector2& point ) const
{
  Vector2 v1 = mVector1 - point;
  Vector2 v2 = mVector2 - point;
  Vector2 v3 = mVector3 - point;
 
  _float cross1 = Vector2::Cross( v1, v2 );
  _float cross2 = Vector2::Cross( v2, v3 );
  _float cross3 = Vector2::Cross( v3, v1 );
 
  if ( cross1 * cross2 < 0 )
   return _false;
 
  if ( cross1 * cross3 < 0 )
   return _false;
 
  if ( cross2 * cross3 < 0 )
   return _false;
 
  return _true;
}

_float Triangle2D::GetArea( )
{
 Vector2 v1 = mVector2 - mVector1;
 Vector2 v2 = mVector3 - mVector1;
 _float cross = Vector2::Cross( v1, v2 );
 return Math::Abs( cross ) * 0.5f;
}

_ubool Triangle2D::IsValid( )
{
 if ( mVector1 == mVector2 )
  return _false;

 if ( mVector2 == mVector3 )
  return _false;

 if ( mVector1 == mVector3 )
  return _false;

 Vector2 v1 = mVector2 - mVector1;
 Vector2 v2 = mVector3 - mVector1;
 if (  Vector2::Cross( v1, v2 ) == 0.0f )
  return _false;

 return _true;
}