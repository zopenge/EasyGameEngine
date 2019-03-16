//! @file     Math.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

const _float	Math::cZero				=  0.0f;
const _float	Math::cOne				=  1.0f;
const _float	Math::cPi				=  3.141592654f;
const _float	Math::c2Pi				=  6.283185308f;
const _float	Math::cE				=  2.718281828f;
const _float	Math::cMaxFloat			=  3.402823466e+38f;
const _float	Math::cMinFloat			= -3.402823466e+38f;
const _int		Math::cMaxInt			=  0x7FFFFFFF;
const _int		Math::cMinInt			=  0x80000000;
const _dword	Math::cMaxDword			=  4294967295UL;
const _dword	Math::cMinDword			=  0UL;
const _float	Math::cFloatEpsilon		=  0.000001f;
const _double	Math::cDoubleEpsilon	=  0.000000000000001;

//----------------------------------------------------------------------------
// Math Implementation
//----------------------------------------------------------------------------

_void Math::Quaternion2EulerAngles( const Quaternion& quaternion, EulerAngles& angles )
{
	/*

				| q1^2 - q2^2 - q3^2 + q4^2		2 * ( q1 * q2 + q3 * q4 )		2 * ( q1 * q3 - q2 * q4 )	|
	A(q)	=	| 2 * ( q1 * q2 - q3 * q4 )		- q1^2 + q2^2 - q3^2 + q4^2		2 * ( q2 * q3 + q1 * q4 )	|
				| 2 * ( q1 * q3 + q2 * q4 )		2 * ( q2 * q3 - q1 * q4 )		- q1^2 - q2^2 + q3^2 + q4^2	|

	1===============================================================
	-90 < xyz < 90
	z		=	atan( A23 / A33 )
	y		=	asin( -A13 )
	x		=	atan( A12 / A11 )
	1===============================================================

	2===============================================================
	-180 < x < 180			-90 < y < 90			0 < z < 360
	z		=	| atan( A23 / A33 )						A33 < 0
				| Pi * sign A23 + atan( A23 / A33 )		A33 > 0

	y		=	asin( -A13 )

	x		=	| atan( A12 / A11 )						A11 < 0
				| Pi * sign A12 + atan( A12 / A11 )		A11 > 0
	2===============================================================
	*/

	_float sh = 2.0f * ( quaternion.w * quaternion.y - quaternion.x * quaternion.z );
	if ( sh <= -1.0f )
		angles.mHeading = -cPi * 0.5f;
	else if ( sh >= 1.0f )
		angles.mHeading = cPi * 0.5f;
	else
		angles.mHeading = Asin( sh );

	if ( sh > 1.0f - cFloatEpsilon )
	{
		angles.mBank	= 0.0f;
		angles.mPitch	= Atan( 2.0f * ( quaternion.x * quaternion.y - quaternion.w * quaternion.z ), 2.0f * ( quaternion.x * quaternion.z + quaternion.w * quaternion.y ) );
	}
	else
	{
		angles.mBank	= Atan( 2.0f * ( quaternion.x * quaternion.y + quaternion.w * quaternion.z ), 1.0f - 2.0f * ( quaternion.y * quaternion.y + quaternion.z * quaternion.z ) );
		angles.mPitch	= Atan( 2.0f * ( quaternion.y * quaternion.z + quaternion.w * quaternion.x ), 1.0f - 2.0f * ( quaternion.x * quaternion.x + quaternion.y * quaternion.y ) );
	}
	/*
	_float q1q1 = quaternion.x * quaternion.x, q1q2 = quaternion.x * quaternion.y, q1q3 = quaternion.x * quaternion.z, q1q4 = quaternion.x * quaternion.w,
		q2q2 = quaternion.y * quaternion.y, q2q3 = quaternion.y * quaternion.z, q2q4 = quaternion.y * quaternion.w,
		q3q3 = quaternion.z * quaternion.z, q3q4 = quaternion.z * quaternion.w, q4q4 = quaternion.w * quaternion.w;
	_float a11 = q1q1 - q2q2 - q3q3 + q4q4, a12 = 2.0f * ( q1q2 + q3q4 ), a13 = 2.0f * ( q1q3 - q2q4 ),
		a23 = 2.0f * ( q2q3 + q1q4 ), a33 = - q1q1 - q2q2 + q3q3 + q4q4;

	angles.mPitch = Atan( a23, a33 );
	angles.mHeading = Asin( -a13 );	
	angles.mBank = Atan( a12, a11 );

	if ( a33 < 0.0f )
	{
		if ( a23 > 0.0f )
			angles.mPitch += Math::cPi;
		else if ( a23 < 0.0f )
			angles.mPitch -= Math::cPi;
	}

	if ( a11 > 0.0f )
	{
		if ( a12 < 0.0f )
			angles.mBank += Math::c2Pi;
	}
	else if ( a11 < 0.0f )
	{
		angles.mBank += Math::cPi;
	}
	*/
}

_void Math::Matrix2EulerAngles( const Matrix3& matrix, EulerAngles& angles )
{
	_float sh = -matrix.m[0][2];
	if ( sh <= -1.0f )
		angles.mHeading = -cPi * 0.5f;
	else if ( sh >= 1.0f )
		angles.mHeading = cPi * 0.5f;
	else
		angles.mHeading = Asin( sh );

	if ( sh > 1.0f - cFloatEpsilon )
	{
		angles.mBank	= 0.0f;
		angles.mPitch	= Atan( matrix.m[1][0], matrix.m[2][0] );
	}
	else
	{
		angles.mBank	= Atan( matrix.m[0][1], matrix.m[0][0] );
		angles.mPitch	= Atan( matrix.m[1][2], matrix.m[2][2] );
	}
}

_void Math::EulerAngles2Quaternion( const EulerAngles& angle, Quaternion& quaternion )
{
	_float cp = Math::Cos( angle.mPitch / 2.0f );
	_float ch = Math::Cos( angle.mHeading / 2.0f );
	_float cb = Math::Cos( angle.mBank / 2.0f );
	_float sp = Math::Sin( angle.mPitch / 2.0f );
	_float sh = Math::Sin( angle.mHeading / 2.0f );
	_float sb = Math::Sin( angle.mBank / 2.0f );

 	quaternion.w = cp * ch * cb + sp * sh * sb;
 	quaternion.x = sp * ch * cb - cp * sh * sb;
 	quaternion.y = cp * sh * cb + sp * ch * sb;
 	quaternion.z = cp * ch * sb - sp * sh * cb;
}

_void Math::Matrix2Quaternion( const Matrix3& matrix, Quaternion& quaternion )
{
	// Determine which of w, x, y, or z has the largest absolute value.
	_float fourWSquaredMinus1 = matrix.m[0][0] + matrix.m[1][1] + matrix.m[2][2];
	_float fourXSquaredMinus1 = matrix.m[0][0] - matrix.m[1][1] - matrix.m[2][2];
	_float fourYSquaredMinus1 = matrix.m[1][1] - matrix.m[0][0] - matrix.m[2][2];
	_float fourZSquaredMinus1 = matrix.m[2][2] - matrix.m[0][0] - matrix.m[1][1];

	_int biggestIndex = 0;
	_float fourBiggestSquaredMinus1 = fourWSquaredMinus1;

	if ( fourXSquaredMinus1 > fourBiggestSquaredMinus1 )
	{
		fourBiggestSquaredMinus1 = fourXSquaredMinus1;
		biggestIndex = 1;
	}

	if ( fourYSquaredMinus1 > fourBiggestSquaredMinus1 )
	{
		fourBiggestSquaredMinus1 = fourYSquaredMinus1;
		biggestIndex = 2;
	}

	if ( fourZSquaredMinus1 > fourBiggestSquaredMinus1 )
	{
		fourBiggestSquaredMinus1 = fourZSquaredMinus1;
		biggestIndex = 3;
	}

	_float biggestVal = Math::Sqrt( fourBiggestSquaredMinus1 + 1.0f ) * 0.5f;
	_float mult = 0.25f / biggestVal;

	// Apply table to compute quaternion values.
	switch ( biggestIndex )
	{
	case 0:
		quaternion.w = biggestVal;
		quaternion.x = ( matrix.m[1][2] - matrix.m[2][1] ) * mult;
		quaternion.y = ( matrix.m[2][0] - matrix.m[0][2] ) * mult;
		quaternion.z = ( matrix.m[0][1] - matrix.m[1][0] ) * mult;
		break;

	case 1:
		quaternion.x = biggestVal;
		quaternion.w = ( matrix.m[1][2] - matrix.m[2][1] ) * mult;
		quaternion.y = ( matrix.m[0][1] + matrix.m[1][0] ) * mult;
		quaternion.z = ( matrix.m[2][0] + matrix.m[0][2] ) * mult;
		break;

	case 2:
		quaternion.y = biggestVal;
		quaternion.w = ( matrix.m[2][0] - matrix.m[0][2] ) * mult;
		quaternion.x = ( matrix.m[0][1] + matrix.m[1][0] ) * mult;
		quaternion.z = ( matrix.m[1][2] + matrix.m[2][1] ) * mult;
		break;

	case 3:
		quaternion.z = biggestVal;
		quaternion.w = ( matrix.m[0][1] - matrix.m[1][0] ) * mult;
		quaternion.x = ( matrix.m[2][0] + matrix.m[0][2] ) * mult;
		quaternion.y = ( matrix.m[1][2] + matrix.m[2][1] ) * mult;
		break;
	}
}

_void Math::EulerAngles2Matrix( const EulerAngles& angle, Matrix3& matrix )
{
	_float cp = Math::Cos( angle.mPitch );
	_float ch = Math::Cos( angle.mHeading );
	_float cb = Math::Cos( angle.mBank );
	_float sp = Math::Sin( angle.mPitch );
	_float sh = Math::Sin( angle.mHeading );
	_float sb = Math::Sin( angle.mBank );

	matrix.m[0][0] = ch * cb;				matrix.m[0][1] = ch * sb;				matrix.m[0][2] = -sh;
	matrix.m[1][0] = sp * sh * cb - cp * sb;matrix.m[1][1] = sp * sh * sb + cp * cb;matrix.m[1][2] = sp * ch;
	matrix.m[2][0] = cp * sh * cb + sp * sb;matrix.m[2][1] = cp * sh * sb - sp * cb;matrix.m[2][2] = cp * ch;
}

_void Math::Quaternion2Matrix( const Quaternion& quaternion, Matrix3& matrix )
{
	_float xx = quaternion.x * quaternion.x * 2.0f, yy = quaternion.y * quaternion.y * 2.0f, zz = quaternion.z * quaternion.z * 2.0f;
	_float xy = quaternion.x * quaternion.y * 2.0f, zw = quaternion.z * quaternion.w * 2.0f, xz = quaternion.x * quaternion.z * 2.0f;
	_float yw = quaternion.y * quaternion.w * 2.0f, yz = quaternion.y * quaternion.z * 2.0f, xw = quaternion.x * quaternion.w * 2.0f;

	matrix.m[0][0] = 1.0f - yy - zz; matrix.m[0][1] =        xy + zw; matrix.m[0][2] =        xz - yw;
	matrix.m[1][0] =        xy - zw; matrix.m[1][1] = 1.0f - xx - zz; matrix.m[1][2] =        yz + xw;
	matrix.m[2][0] =        xz + yw; matrix.m[2][1] =        yz - xw; matrix.m[2][2] = 1.0f - xx - yy;
}

_void Math::CalculateTangentByNormalUV( const MemSegmentPtr< _word >& index_buffer, const MemSegmentPtr< Vector3 >& position_buffer, const MemSegmentPtr< Vector3 >& normal_buffer, const MemSegmentPtr< Vector2 >& uv_buffer, MemSegmentPtr< Vector4 >& ret_tangent_buffer )
{
	_dword vertex_count = position_buffer.Number( );

	MemArrayPtr< Vector3 > tangent_buffer( vertex_count );
	MemArrayPtr< Vector3 > bitangent_buffer( vertex_count );

	EGE_MEM_SET( tangent_buffer.GetRawRef( ), 0, tangent_buffer.SizeOfBytes( ) );
	EGE_MEM_SET( bitangent_buffer.GetRawRef( ), 0, bitangent_buffer.SizeOfBytes( ) );

	for ( _dword i = 0; i < index_buffer.Number( ); i += 3 )
	{
		_dword index0 = index_buffer[i];
		_dword index1 = index_buffer[i + 1];
		_dword index2 = index_buffer[i + 2];

		Vector3 edgeA = position_buffer[index1] - position_buffer[index0];
		Vector3 edgeB = position_buffer[index2] - position_buffer[index0];
		Vector2 deltaUV1 = uv_buffer[index1] - uv_buffer[index0];
		Vector2 deltaUV2 = uv_buffer[index2] - uv_buffer[index0];

		_float div = Vector2::Cross( deltaUV1, deltaUV2 );
		_float r = div == 0.0f ? 0.0f : 1.0f / div;

		Vector3 tangent = ( edgeA * deltaUV2.y - edgeB * deltaUV1.y ) * r;
		Vector3 bitangent = ( edgeA * deltaUV2.x - edgeB * deltaUV1.x ) * r;

		for ( _dword j = 0; j < 3; ++ j )
		{
			_dword cur_index = index_buffer[i + j];

			tangent_buffer[cur_index] += tangent;
			bitangent_buffer[cur_index] += bitangent;
		}
	}

	for ( _dword i = 0; i < vertex_count; ++ i )
	{
		Vector3 n = normal_buffer[i];
		Vector3 t = tangent_buffer[i];

		Vector3 tangent = ( t - Vector3::Project( t, n ) ).Normalize( );

		ret_tangent_buffer[i].x = tangent.x;
		ret_tangent_buffer[i].y = tangent.y;
		ret_tangent_buffer[i].z = tangent.z;
		ret_tangent_buffer[i].w = ( Vector3::Dot( Vector3::Cross( n, t ), bitangent_buffer[i] ) < 0.0f ) ? -1.0f : 1.0f;
	}
}

Quaternion Math::SLerpToValue( const Quaternion& src, const Quaternion& dst, _float step )
{
	Quaternion result = src;
	if ( step >= 1.0f )
		return result;

	result = Quaternion::Slerp( src, dst, step );
	if ( result.Equal( dst ) )
		result = dst;

	return result;
}
