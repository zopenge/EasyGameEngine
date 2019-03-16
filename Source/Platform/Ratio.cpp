//! @file     Ratio.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

Ratio Ratio::cNull;

//----------------------------------------------------------------------------
// Ratio Implementation
//----------------------------------------------------------------------------

Ratio::Ratio( )
{
 mScale  = 1.0f;
 mBaseSize = PointF::cZeroPoint;
 mOffset  = PointF::cZeroPoint;
}

Ratio::Ratio( const Ratio& ratio )
{
 mScale  = ratio.mScale;
 mBaseSize = ratio.mBaseSize;
 mOffset  = ratio.mOffset;
}

Ratio::Ratio( const Vector2& size )
{
 Init( size.x, size.y );
}

Ratio::Ratio( _float width, _float height )
{
 Init( width, height );
}

_ubool Ratio::operator == ( const Ratio& ratio ) const
{
 if ( Math::Equal( mScale, ratio.mScale ) == _false )
  return _false;

 if ( mBaseSize != ratio.mBaseSize )
  return _false;

 if ( mOffset != ratio.mOffset )
  return _false;

 return _true;
}

_ubool Ratio::operator != ( const Ratio& ratio ) const
{
 if ( Math::Equal( mScale, ratio.mScale ) == _false )
  return _true;

 if ( mBaseSize != ratio.mBaseSize )
  return _true;

 if ( mOffset != ratio.mOffset )
  return _true;

 return _false;
}

_void Ratio::Init( _float width, _float height )
{
 height  = Math::Max< _float >( 1.0f, height );

 mScale  = 1.0f;
 mBaseSize = PointF( width, height );
 mOffset  = PointF::cZeroPoint;

 UpdateSize( width, height );
}

PointF Ratio::UpdateSize( _float width, _float height )
{
 _float ratiow = width / mBaseSize.x;
 _float ratioh = height / mBaseSize.y;

 if ( height > mBaseSize.y * ratiow )
 {
  mScale  = ratiow;
  mOffset.x = 0;
  mOffset.y = ( height - mBaseSize.y * ratiow ) / 2.0f;

  return PointF( width, mBaseSize.y * ratiow );
 }
 else
 {
  mScale  = ratioh;
  mOffset.x = ( width - mBaseSize.x * ratioh ) / 2.0f;
  mOffset.y = 0;

  return PointF( mBaseSize.x * ratioh, height );
 }
}

PointU Ratio::UpdateSize( _dword width, _dword height )
{
 PointF size = UpdateSize( (_float) width, (_float) height );
 return ConvertPointF2PointU( size );
}

Vector2 Ratio::GetBaseSize( ) const
{
 return Vector2( mBaseSize.x, mBaseSize.y );
}

Vector2 Ratio::GetOffset( ) const
{
 return Vector2( mOffset.x, mOffset.y );
}

PointU Ratio::FixSizeU( const PointU& size ) const
{
 return FixSizeU( *this, size );
}

PointF Ratio::FixSizeF( const PointU& size ) const
{
 return FixSizeF( *this, size );
}

PointU Ratio::FixSizeU( const Ratio& ratio, const PointU& size )
{
 PointF fixed_size = FixSizeF( ratio, size );
 return PointU( (_dword)fixed_size.x, (_dword)fixed_size.y );
}

PointF Ratio::FixSizeF( const Ratio& ratio, const PointU& size )
{
 if ( ratio == Ratio::cNull )
 {
  return PointF( (_float)size.x, (_float)size.y );;
 }
 else
 {
  PointF fixed_size = Ratio( ratio ).UpdateSize( (_float) size.x, (_float) size.y );
  return fixed_size;
 }
}

Ratio Ratio::Create( const Ratio& ratio, const PointU& size )
{
 Ratio ratio_tmp = ratio;
 PointF fixed_size = ratio_tmp.UpdateSize( (_float)size.x, (_float)size.y );
 return Ratio( fixed_size.x, fixed_size.y );
}
