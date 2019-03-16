//! @file     Timer.cpp
//! @author   foreven
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

const Transform2D Transform2D::cZero;

//----------------------------------------------------------------------------
// Transform2D Implementation
//----------------------------------------------------------------------------

_ubool Transform2D::operator == ( const Transform2D& transform ) const
{
 if ( mPosition != transform.mPosition )
  return _false;

 if ( mScale != transform.mScale )
  return _false;

 if ( Math::Equal( mRadian, transform.mRadian ) == _false )
  return _false;

 return _true;
}

_ubool Transform2D::operator != ( const Transform2D& transform ) const
{
 if ( mPosition != transform.mPosition )
  return _true;

 if ( mScale != transform.mScale )
  return _true;

 if ( Math::Equal( mRadian, transform.mRadian ) == _false )
  return _true;

 return _false;
}

Transform2D Transform2D::Lerp( const Transform2D& transform1, const Transform2D& transform2, _float factor )
{
 Transform2D transform;
 transform.mPosition = Vector2::Lerp( transform1.mPosition, transform2.mPosition, factor );
 transform.mScale = Vector2::Lerp( transform1.mScale, transform2.mScale, factor );
 transform.mRadian = Math::Lerp( transform1.mRadian, transform2.mRadian, factor );

 return transform;
}
