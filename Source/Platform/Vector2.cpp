//! @file     Vector2.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Vector2 Implementation
//----------------------------------------------------------------------------

const Vector2 Vector2::cOrigin( 0.0f, 0.0f );
const Vector2 Vector2::cIdentity( 1.0f, 1.0f );
const Vector2 Vector2::cXAxis( 1.0f, 0.0f );
const Vector2 Vector2::cYAxis( 0.0f, 1.0f );
const Vector2 Vector2::cMaxVector( 3.402823466e+38f, 3.402823466e+38f );
const Vector2 Vector2::cMinVector( -3.402823466e+38f, -3.402823466e+38f );

Vector2& Vector2::operator *= ( const Matrix2& matrix )
{
	_float xx = x, yy = y;

	x = xx * matrix.m[0][0] + yy * matrix.m[1][0];
	y = xx * matrix.m[0][1] + yy * matrix.m[1][1];

	return *this;
}

Vector2& Vector2::operator *= ( const Matrix3& matrix )
{
	_float xx = x, yy = y;

	x = xx * matrix.m[0][0] + yy * matrix.m[1][0] + matrix.m[2][0];
	y = xx * matrix.m[0][1] + yy * matrix.m[1][1] + matrix.m[2][1];

	return *this;
}

Vector2 Vector2::operator * ( const Matrix2& matrix ) const
{
	Vector2 returnvector( *this );

	return returnvector *= matrix;
}

Vector2 Vector2::operator * ( const Matrix3& matrix ) const
{
	Vector2 returnvector( *this );

	return returnvector *= matrix;
}

Vector2 Vector2::Project( const Vector2& vector1, const Vector2& vector2 )
{
	Vector2 normal = vector2;
	normal.Normalize( );

	return normal * Dot( vector1, normal );
}

Vector2 Vector2::Plumb( const Vector2& vector1, const Vector2& vector2 )
{
	return vector1 - Vector2::Project( vector1, vector2 );
}

Vector2 Vector2::Lerp( const Vector2& vector1, const Vector2& vector2, _float factor )
{
	return vector1 + ( vector2 - vector1 ) * factor;
}

_float Vector2::Radian( const Vector2& vector1, const Vector2& vector2 )
{
	Vector2 v1 = vector1;
	Vector2 v2 = vector2;
	v1.Normalize( );
	v2.Normalize( );

	_float cross	= Vector2::Cross( v1, v2 );
	_float dot		= Vector2::Dot( v1, v2 );

	return Math::Atan( cross, dot );
}

_float Vector2::GetRotateAngle( const Vector2& vector1, const Vector2& vector2 )
{
	Vector2 v1 = vector1;
	Vector2 v2 = vector2;
	v1.Normalize();
	v2.Normalize();
	_float dot = Vector2::Dot( v1, v2 );
	_float angle = 0;
	if ( Math::Abs( dot - 1.0f ) <= 1.0e-6 )
	{
		angle = 0;
	}
	else if ( Math::Abs( dot + 1.0f ) <= 1.0e-6 )
	{
		angle = Math::cPi;
	}
	else
	{
		angle = Math::Acos( dot );
		if ( Vector2::Cross( v1, v2 ) < 0 )
		{
			angle = -angle;
		}
	}
	return angle;
}
