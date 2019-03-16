//! @file     Polygon2D.h
//! @author   foreven
//! @version  1.1
//! @date     2012.12.5
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Polygon2D
//----------------------------------------------------------------------------

class Polygon2D
{
public:
	Array< Vector2 >	mVertexArray;

private:
	enum _VERTEX_TYPE
	{
		_CONVEX,
		_CONCAVE,
		_FLAT,
	};

private:
	struct MinDistanceInfo 
	{
		_float			mDistance;
		_dword			mVertexIndex;
	};

private:
	_VERTEX_TYPE	GetVertexType( _dword vertex_index ) const;
	_ubool			IsTriangleValid( _dword v1_index, _dword v2_index, _dword v3_index ) const;

public:
	inline Polygon2D( );
	inline Polygon2D( const Array< Vector2 >& vertex_array );

public:
	inline Polygon2D& operator *= ( const Matrix3& matrix );
	inline Polygon2D  operator * ( const Matrix3& matrix ) const;

public:
	Vector2 MiddleVector( ) const;
	_void ToTriangleArray( Array< Triangle2D >& triangles ) const;
	_ubool DividePolygon( const Array<Vector2>& divide_line, Polygon2D& polygon1, Polygon2D& polygon2 );
	_void FixPolygon( );

	_ubool IsPointIn( const Vector2& point );

public:
	static _ubool GetCircleProgressPolygon( const Vector2& pos, const Vector2& size, const FloatRange& angle_range, Polygon2D& polygon );
	static _ubool GetCircleProgressPolygon( const Vector2& pos, const Vector2& size, const FloatRange& angle_range, Array< Triangle2D >& triangles );
};

//----------------------------------------------------------------------------
// Polygon2D Implementation
//----------------------------------------------------------------------------

Polygon2D::Polygon2D( )
{
}

Polygon2D::Polygon2D( const Array< Vector2 >& vertex_array )
{
	mVertexArray = vertex_array;
}

Polygon2D& Polygon2D::operator *= ( const Matrix3& matrix )
{
	for ( _dword i = 0; i < mVertexArray.Number( ); ++ i )
	{
		mVertexArray[i] *= matrix;
	}

	return *this;
}

Polygon2D Polygon2D::operator * ( const Matrix3& matrix ) const
{
	Polygon2D polygon = *this;
	polygon *= matrix;
	return polygon;
}

}