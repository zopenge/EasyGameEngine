//! @file     OrientedBox2D.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

const OrientedBox2D OrientedBox2D::cNull( Vector2( 0.0f, 0.0f ), 0.0f, 0.0f, 0.0f );

//----------------------------------------------------------------------------
// OrientedBox2D Implementation
//----------------------------------------------------------------------------

OrientedBox2D::OrientedBox2D( )
{
	EGE_INIT_ARRAY( mCorner );
	EGE_INIT_ARRAY( mAxis );
	EGE_INIT_ARRAY( mOrigin );
}

OrientedBox2D::OrientedBox2D( const Vector2& lt, const Vector2& rt, const Vector2& rb, const Vector2& lb )
{
	mCorner[0] = lt;
	mCorner[1] = rt;
	mCorner[2] = rb;
	mCorner[3] = lb;

	ComputeAxes( );
}

OrientedBox2D::OrientedBox2D( const Vector2& center, _float w, _float h, _float radian )
{
	_float sincos_value[2];
	Math::SinCos( radian, sincos_value );

	Vector2 x(   sincos_value[1], sincos_value[0] );
	Vector2 y( - sincos_value[0], sincos_value[1] );

	x *= w / 2.0f;
	y *= h / 2.0f;

	mCorner[0] = center - x - y;
	mCorner[1] = center + x - y;
	mCorner[2] = center + x + y;
	mCorner[3] = center - x + y;

	ComputeAxes( );
}

OrientedBox2D::OrientedBox2D( const OrientedBox2D& box )
{
	EGE_MEM_CPY( mCorner, box.mCorner, sizeof( mCorner ) );
	EGE_MEM_CPY( mAxis, box.mAxis, sizeof( mAxis ) );
	EGE_MEM_CPY( mOrigin, box.mOrigin, sizeof( mOrigin ) );
}

_void OrientedBox2D::ComputeAxes( ) 
{
	mAxis[0] = mCorner[1] - mCorner[0]; 
	mAxis[1] = mCorner[3] - mCorner[0]; 

	// Make the length of each axis 1/edge length so we know any
	// dot product must be less than 1 to fall within the edge.
	for (int a = 0; a < 2; ++a) 
	{
		mAxis[a] /= mAxis[a].MagnitudeSquared( );
		mOrigin[a] = Vector2::Dot( mCorner[0], mAxis[a] );
	}
}

RectF OrientedBox2D::ToRectF( ) const
{
	RectF rect( Math::cMaxFloat, Math::cMaxFloat, Math::cMinFloat, Math::cMinFloat );

	for ( _dword i = 0; i < EGE_ARRAY_NUMBER( mCorner ); i ++ )
	{
		const Vector2& position = mCorner[i];

		if ( rect.l > position.x )
			rect.l = position.x;

		if ( rect.t > position.y )
			rect.t = position.y;

		if ( rect.r < position.x )
			rect.r = position.x;

		if ( rect.b < position.y )
			rect.b = position.y;
	}

	return rect;
}

OrientedBox2D& OrientedBox2D::FromRectF( const RectF& rect )
{
	*this = OrientedBox2D( ConvertPoint2Vector2( rect.GetCenter( ) ), rect.GetWidth( ), rect.GetHeight( ), 0.0f );

	return *this;
}

_void OrientedBox2D::MoveTo( const Vector2& center ) 
{
	Vector2 centroid = (mCorner[0] + mCorner[1] + mCorner[2] + mCorner[3]) / 4;

	Vector2 translation = center - centroid;

	for (int c = 0; c < 4; ++c)
		mCorner[c] += translation;

	ComputeAxes( );
}

_void OrientedBox2D::SetSize( _float width, _float height )
{
	Vector2 center = (mCorner[0] + mCorner[1] + mCorner[2] + mCorner[3]) / 4;

	Vector2 x = ( mCorner[1] - mCorner[0] ).Normalize( ) * ( width * 0.5f );
	Vector2 y = ( mCorner[3] - mCorner[0] ).Normalize( ) * ( height * 0.5f );

	mCorner[0] = center - x - y;
	mCorner[1] = center + x - y;
	mCorner[2] = center + x + y;
	mCorner[3] = center - x + y;

	ComputeAxes( );
}

_ubool OrientedBox2D::Overlaps1Way( const OrientedBox2D& other ) const
{
	for (int a = 0; a < 2; ++a) 
	{
		_float t = Vector2::Dot( other.mCorner[0], mAxis[a] );

		// Find the extent of box 2 on axis a
		_float tMin = t;
		_float tMax = t;

		for (int c = 1; c < 4; ++c) 
		{
			t = Vector2::Dot( other.mCorner[c], mAxis[a] );

			if (t < tMin)
				tMin = t;
			else if (t > tMax)
				tMax = t;
		}

		// We have to subtract off the origin

		// See if [tMin, tMax] intersects [0, 1]
		if ((tMin > 1 + mOrigin[a]) || (tMax < mOrigin[a])) 
		{
			// There was no intersection along this dimension;
			// the boxes cannot possibly overlap.
			return _false;
		}
	}

	// There was no dimension along which there is no intersection.
	// Therefore the boxes overlap.
	return _true;
}

_ubool OrientedBox2D::PointInOrientedBox( const Vector2& point ) const
{
	Vector2 v1 = mCorner[0] - point;
	Vector2 v2 = mCorner[1] - point;
	Vector2 v3 = mCorner[2] - point;
	Vector2 v4 = mCorner[3] - point;

	_float cross1 = Vector2::Cross( v1, v2 );
	_float cross2 = Vector2::Cross( v2, v3 );
	_float cross3 = Vector2::Cross( v3, v4 );
	_float cross4 = Vector2::Cross( v4, v1 );

	if ( cross1 * cross2 < 0 )
		return _false;

	if ( cross1 * cross3 < 0 )
		return _false;

	if ( cross1 * cross4 < 0 )
		return _false;

	if ( cross2 * cross3 < 0 )
		return _false;

	if ( cross2 * cross4 < 0 )
		return _false;

	if ( cross3 * cross4 < 0 )
		return _false;

	return _true;
}

OrientedBox2D OrientedBox2D::operator * ( const Matrix3& matrix ) const
{
	OrientedBox2D returnbox( *this );

	return returnbox *= matrix;
}

OrientedBox2D& OrientedBox2D::operator *= ( const Matrix3& transform )
{
	mCorner[0] *= transform;
	mCorner[1] *= transform;
	mCorner[2] *= transform;
	mCorner[3] *= transform;

	ComputeAxes( );

	return *this;
}