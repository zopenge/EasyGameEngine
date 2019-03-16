//! @file     Vector4.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

const Vector4 Vector4::cOrigin( 0.0f, 0.0f, 0.0f, 0.0f );
const Vector4 Vector4::cIdentity( 1.0f, 1.0f, 1.0f, 1.0f );
const Vector4 Vector4::cXAxis( 1.0f, 0.0f, 0.0f, 0.0f );
const Vector4 Vector4::cYAxis( 0.0f, 1.0f, 0.0f, 0.0f );
const Vector4 Vector4::cZAxis( 0.0f, 0.0f, 1.0f, 0.0f );
const Vector4 Vector4::cWAxis( 0.0f, 0.0f, 0.0f, 1.0f );
const Vector4 Vector4::cMaxVector( 3.402823466e+38f, 3.402823466e+38f, 3.402823466e+38f, 3.402823466e+38f );
const Vector4 Vector4::cMinVector( -3.402823466e+38f, -3.402823466e+38f, -3.402823466e+38f, -3.402823466e+38f );

//----------------------------------------------------------------------------
// Vector4 Implementation
//----------------------------------------------------------------------------

Vector4& Vector4::operator *= ( const Matrix4& matrix )
{
	_float xx = x, yy = y, zz = z, ww = w;

	x = xx * matrix.m[0][0] + yy * matrix.m[1][0] + zz * matrix.m[2][0] + ww * matrix.m[3][0];
	y = xx * matrix.m[0][1] + yy * matrix.m[1][1] + zz * matrix.m[2][1] + ww * matrix.m[3][1];
	z = xx * matrix.m[0][2] + yy * matrix.m[1][2] + zz * matrix.m[2][2] + ww * matrix.m[3][2];
	w = xx * matrix.m[0][3] + yy * matrix.m[1][3] + zz * matrix.m[2][3] + ww * matrix.m[3][3];

	return *this;
}

Vector4 Vector4::operator * ( const Matrix4& matrix ) const
{
	Vector4 returnvector( *this );

	return returnvector *= matrix;
}
