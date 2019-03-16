//! @file     Vector3.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

const Vector3 Vector3::cOrigin( 0.0f, 0.0f, 0.0f );
const Vector3 Vector3::cIdentity( 1.0f, 1.0f, 1.0f );
const Vector3 Vector3::cXAxis( 1.0f, 0.0f, 0.0f );
const Vector3 Vector3::cYAxis( 0.0f, 1.0f, 0.0f );
const Vector3 Vector3::cZAxis( 0.0f, 0.0f, 1.0f );
const Vector3 Vector3::cMaxVector( 3.402823466e+38f, 3.402823466e+38f, 3.402823466e+38f );
const Vector3 Vector3::cMinVector( -3.402823466e+38f, -3.402823466e+38f, -3.402823466e+38f );

//----------------------------------------------------------------------------
// Vector3 Implementation
//----------------------------------------------------------------------------

Vector3& Vector3::operator *= ( const Matrix3& matrix )
{
	_float xx = x, yy = y, zz = z;

	x = xx * matrix.m[0][0] + yy * matrix.m[1][0] + zz * matrix.m[2][0];
	y = xx * matrix.m[0][1] + yy * matrix.m[1][1] + zz * matrix.m[2][1];
	z = xx * matrix.m[0][2] + yy * matrix.m[1][2] + zz * matrix.m[2][2];

	return *this;
}

Vector3& Vector3::operator *= ( const Matrix3x4& matrix )
{
	_float xx = x, yy = y, zz = z;

	x = xx * matrix.m[0][0] + yy * matrix.m[0][1] + zz * matrix.m[0][2] + matrix.m[3][0];
	y = xx * matrix.m[1][0] + yy * matrix.m[1][1] + zz * matrix.m[1][2] + matrix.m[3][1];
	z = xx * matrix.m[2][0] + yy * matrix.m[2][1] + zz * matrix.m[2][2] + matrix.m[3][2];

	return *this;
}

Vector3& Vector3::operator *= ( const Matrix4& matrix )
{
	_float xx = x, yy = y, zz = z;

	_float w = xx * matrix.m[0][3] + yy * matrix.m[1][3] + zz * matrix.m[2][3] + matrix.m[3][3];

	x = xx * matrix.m[0][0] + yy * matrix.m[1][0] + zz * matrix.m[2][0] + matrix.m[3][0];
	y = xx * matrix.m[0][1] + yy * matrix.m[1][1] + zz * matrix.m[2][1] + matrix.m[3][1];
	z = xx * matrix.m[0][2] + yy * matrix.m[1][2] + zz * matrix.m[2][2] + matrix.m[3][2];

	if ( w != 0.0f )
	{
		x /= w;
		y /= w;
		z /= w;
	}

	return *this;
}

Vector3& Vector3::operator *= ( const Quaternion& quaternion )
{
	Quaternion tempquaternion = -quaternion;
	tempquaternion *= Quaternion( x, y, z, 0.0f );
	tempquaternion *= quaternion;

	x = tempquaternion.x;
	y = tempquaternion.y;
	z = tempquaternion.z;

	return *this;
}

Vector3& Vector3::operator *= ( const Transform3D& transform )
{
	*this *= transform.mRotation;
	*this += transform.mTranslate;
	return *this;
}

Vector3 Vector3::operator * ( const Matrix3& matrix ) const
{
	Vector3 returnvector( *this );

	return returnvector *= matrix;
}

Vector3 Vector3::operator * ( const Matrix3x4& matrix ) const
{
	Vector3 returnvector( *this );

	return returnvector *= matrix;
}

Vector3 Vector3::operator * ( const Matrix4& matrix ) const
{
	Vector3 returnvector( *this );

	return returnvector *= matrix;
}

Vector3 Vector3::operator * ( const Quaternion& quaternion ) const
{
	Vector3 returnvector( *this );

	return returnvector *= quaternion;
}

Vector3 Vector3::operator * ( const Transform3D& matrix ) const
{
	Vector3 returnvector( *this );

	return returnvector *= matrix;
}

Vector3& Vector3::Cartesian2Spherical( )
{
	_float xx = Math::Sqrt( x * x + y * y + z * z );
	_float yy = Math::Acos( z / xx );
	_float zz = Math::Asin( y / Math::Sqrt( x * x + y * y ) );

	if ( x < 0.0f )
		zz = Math::cPi - zz;

	if ( zz < 0.0f )
		zz += Math::c2Pi;

	x = xx;
	y = yy;
	z = zz;

	return *this;
}

Vector3& Vector3::Spherical2Cartesian( )
{
	_float sincos_y[2];
	Math::SinCos( y, sincos_y );

	_float sincos_z[2];
	Math::SinCos( z, sincos_z );

	_float xx = x * sincos_y[0] * sincos_z[1];
	_float yy = x * sincos_y[0] * sincos_z[0];
	_float zz = x * sincos_y[1];

	x = xx;
	y = yy;
	z = zz;

	return *this;
}

_float Vector3::GetAngle( const Vector3& vector1, const Vector3& vector2 )
{
	Vector3 v1 = vector1;
	Vector3 v2 = vector2;
	v1.Normalize();
	v2.Normalize();
	_float dot = Vector3::Dot( v1, v2 );
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
	}
	return angle;
}

_ubool Vector3::IsNegative( const Vector3& srcvector, const Vector3& desvector )
{
	Vector3 vector1 = srcvector;
	vector1.Normalize( );

	Vector3 vector2 = desvector;
	vector2.Normalize( );

	_float dotvalue = Vector3::Dot( vector1, vector2 );

	if ( dotvalue <= Math::cFloatEpsilon - 1.0f )
		return _true;

	return _false;
}
