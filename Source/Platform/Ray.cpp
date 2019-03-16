//! @file     Ray.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

const Ray Ray::cNull;

//----------------------------------------------------------------------------
// Ray Implementation
//----------------------------------------------------------------------------

Ray::Ray( )
{
}

Ray::Ray( _float x, _float y, _float z, _float i, _float j, _float k )
 : mOrigin( x, y, z ), mDirection( i, j, k )
{
}

Ray::Ray( const Vector3& origin, const Vector3& direction )
 : mOrigin( origin ), mDirection( direction )
{
}

Ray::Ray( _float x, _float y, const Matrix4& viewtransform, const Matrix4& projectiontransform )
{
 Matrix4 viewinverse = viewtransform;
 viewinverse.Inverse( );

 mOrigin.x  = viewinverse.m[3][0];
 mOrigin.y  = viewinverse.m[3][1];
 mOrigin.z  = viewinverse.m[3][2];

 Vector4 ray_clip = Vector4( x, y, 1.0f, 1.0f );
 Vector4 ray_eye = ray_clip * Matrix4( projectiontransform ).Inverse( );
 Vector4 ray_world = ray_eye * viewinverse;
 if ( ray_world.w != 0.0f )
  ray_world /= ray_world.w;

 mDirection.x = ray_world.x - mOrigin.x;
 mDirection.y = ray_world.y - mOrigin.y;
 mDirection.z = ray_world.z - mOrigin.z;

 mDirection.Normalize( );
}

Ray Ray::GetPickRay( _int x, _int y, const PointU& viewport_size, const Matrix4& view_transform, const Matrix4& projection_transform )
{
 return Ray( 2.0f * x / viewport_size.x - 1.0f, 1.0f - 2.0f * y / viewport_size.y, view_transform, projection_transform );
}

Ray Ray::GetPickRay( _float x, _float y, _float sizex, _float sizey, const Matrix4& view_transform, const Matrix4& projection_transform )
{
 return Ray( 2.0f * x / sizex - 1.0f, 1.0f - 2.0f * y / sizey, view_transform, projection_transform );
}