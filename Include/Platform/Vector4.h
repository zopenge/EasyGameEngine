//! @file     Vector4.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

class Matrix4;

//----------------------------------------------------------------------------
// Vector4
//----------------------------------------------------------------------------

//! This class represents a 4D vector.
class Vector4
{
public:
	//! X-component of the vector.
	_float	x;
	//! Y-component of the vector.
	_float	y;
	//! Z-component of the vector.
	_float	z;
	//! W-component of the vector.
	_float	w;

public:
	//! The origin vector.
	static const Vector4 cOrigin;
	//! The identity vector.
	static const Vector4 cIdentity;
	//! The x-axis vector.
	static const Vector4 cXAxis;
	//! The y-axis vector.
	static const Vector4 cYAxis;
	//! The z-axis vector.
	static const Vector4 cZAxis;
	//! The w-axis vector.
	static const Vector4 cWAxis;
	//! The maximal vector.
	static const Vector4 cMaxVector;
	//! The minimal vector.
	static const Vector4 cMinVector;

public:
	//! Constructor, create a vector without sets x, y, z, w components.
	//! @param		none
	Vector4( );
	//! Constructor, create a vector and sets x, y, z components.
	//! @param		xx			X-component of the vector.
	//! @param		yy			Y-component of the vector.
	//! @param		zz			Z-component of the vector.
	Vector4( _float xx, _float yy, _float zz, _float ww );
	//! Constructor, create a 4D vector from a 3D vector and a w-component.
	//! @param		vector		The 3D vector, used to set x, y, z components.
	//! @param		ww			W-component of the vector.
	Vector4( const Vector3& vector, _float ww );
	//! Copy Constructor, create a vector and sets components by a given vector.
	//! @param		m		The vector create from.
	Vector4( const Vector4 &v );

	//! Copy components from another vector.
	//! @param		m		The other vector.
	//! @return		The reference of current vector.
	Vector4& operator = ( const Vector3 &v );
	//! Copy components from another vector.
	//! @param		m		The other vector.
	//! @return		The reference of current vector.
	Vector4& operator = ( const Vector4 &v );

	//! Type conversion, get the 3D vector from x, y, z components.
	//! @param		none
	//! @return		The 3D vector.
	operator Vector3 ( ) const;

	//! Get positive vector.
	//! @param		none
	//! @return		The positive vector.
	Vector4 operator + ( ) const;
	//! Get negative vector.
	//! @param		none
	//! @return		The negative vector.
	Vector4 operator - ( ) const;

	//! Add a vector to current vector, and save result in current one.
	//! @param		vector		The vector to add.
	//! @return		The result vector of addition.
	Vector4& operator += ( const Vector4& vector );
	//! Subtract a vector from current vector, and save result in current one.
	//! @param		vector		The vector to subtract.
	//! @return		The result vector of subtraction.
	Vector4& operator -= ( const Vector4& vector );
	//! Multiply a scalar to current vector, and save result in current one.
	//! @param		scalar		The scalar to multiply.
	//! @return		The result vector of multiplication.
	Vector4& operator *= ( _float scalar );
	//! Multiply a vector to current vector, and save result in current one.
	//! @param		vector		The vector to multiply.
	//! @return		The result vector of multiplication.
	Vector4& operator *= ( const Vector4& vector );
	//! Divide a scalar to current vector, and save result in current one.
	//! @param		scalar		The scalar to divide.
	//! @return		The result vector of division.
	Vector4& operator /= ( _float scalar );
	//! Divide a vector to current vector, and save result in current one.
	//! @param		vector		The vector to divide.
	//! @return		The result vector of division.
	Vector4& operator /= ( const Vector4& vector );

	//! Multiply a matrix to current vector, and save result in current one.
	//! @param		matrix		The matrix to multiply.
	//! @return		The result vector of multiplication.
	Vector4& operator *= ( const Matrix4& matrix );

	//! Add a vector to current vector, return a new vector to save result.
	//! @param		vector		The vector to add.
	//! @return		The result vector of addition.
	Vector4 operator + ( const Vector4& vector ) const;
	//! Subtract a vector from current vector, return a new vector to save result.
	//! @param		vector		The vector to subtract.
	//! @return		The result vector of subtraction.
	Vector4 operator - ( const Vector4& vector ) const;
	//! Multiply a scalar to current vector, return a new vector to save result.
	//! @param		scalar		The scalar to multiply.
	//! @return		The result vector of multiplication.
	Vector4 operator * ( _float scalar ) const;
	//! Multiply a vector to current vector, return a new vector to save result.
	//! @param		vector		The vector to multiply.
	//! @return		The result vector of multiplication.
	Vector4 operator * ( const Vector4& vector ) const;
	//! Divide a scalar to current vector, return a new vector to save result.
	//! @param		scalar		The scalar to divide.
	//! @return		The result vector of division.
	Vector4 operator / ( _float scalar ) const;
	//! Divide a vector to current vector, return a new vector to save result.
	//! @param		vector		The vector to divide.
	//! @return		The result vector of division.
	Vector4 operator / ( const Vector4& vector ) const;

	//! Compare two vectors.
	//! @param		vector		The vector to compare with.
	//! @return		True if they are identical, false otherwise.
	_ubool operator == ( const Vector4& vector ) const;
	//! Compare two vectors.
	//! @param		vector		The vector to compare with.
	//! @return		True if they are not identical, false otherwise.
	_ubool operator != ( const Vector4& vector ) const;

	//! Multiply a matrix to current vector, return a new vector to save result.
	//! @param		matrix		The matrix to multiply.
	//! @return		The result vector of multiplication.
	Vector4 operator * ( const Matrix4& matrix ) const;

	//! Compare two vectors with error margin.
	//! @param		vector		The vector to compare with.
	//! @param		margin		The margin that allows some error.
	//! @return		True if they are identical, false otherwise.
	_ubool Equal( const Vector4& vector, _float margin = Math::cFloatEpsilon ) const;

	//! Make the current vector absolute, that all coordinates are nonnegative.
	//! @param		none
	//! @return		The absolute vector.
	Vector4& Absolute( );
	//! Make the current vector normalized, that has one unit magnitude.
	//! @param		none
	//! @return		The normalized vector.
	Vector4& Normalize( );

	//! Calculates vector magnitude.
	//! @param		none
	//! @return		The magnitude of vector.
	_float Magnitude( ) const;
	//! Calculates the square of vector magnitude, this function is faster than Magnitude.
	//! @param		none
	//! @return		The square of magnitude of vector.
	_float MagnitudeSquared( ) const;

public:
	//! Calculates dot product of two vectors.
	//! @param		vector1		Source vector 1.
	//! @param		vector2		Source vector 2.
	//! @return		The dot product result.
	static _float Dot( const Vector4& vector1, const Vector4& vector2 );
	//! Calculates vector by project one vector to another.
	//! @param		vector1		The vector to be projected.
	//! @param		vector2		The project reference vector.
	//! @return		The projected vector, that has same direction of vector2.
	static Vector4 Project( const Vector4& vector1, const Vector4& vector2 );
	//! Calculates vector by plumb one vector to another.
	//! @param		vector1		The vector to be projected.
	//! @param		vector2		The project reference vector.
	//! @return		The plumbed vector, that is vertical of vector2.
	static Vector4 Plumb( const Vector4& vector1, const Vector4& vector2 );
	//! Calculates linear interpolation of two vectors.
	//! @param		vector1		Source vector 1.
	//! @param		vector2		Source vector 2.
	//! @param		factor		The interpolation factor, will clamp to between 0 to 1.
	//! @return		The result vector of interpolation, vector1 + ( vector2 - vector1 ) * factor.
	static Vector4 Lerp( const Vector4& vector1, const Vector4& vector2, _float factor );
};

//----------------------------------------------------------------------------
// Vector4 Implementation
//----------------------------------------------------------------------------

inline Vector4::Vector4( )
{
}

inline Vector4::Vector4( _float xx, _float yy, _float zz, _float ww )
	: x( xx ), y( yy ), z( zz ), w( ww )
{
}

inline Vector4::Vector4( const Vector3& vector, _float ww )
	: x( vector.x ), y( vector.y ), z( vector.z ), w( ww )
{
}

inline Vector4::Vector4( const Vector4 &v )
{
	x = v.x; y = v.y; z = v.z, w = v.w;
}

inline Vector4& Vector4::operator = ( const Vector3 &v )
{
	x = v.x; y = v.y; z = v.z, w = 0.0f;

	return *this;
}

inline Vector4& Vector4::operator = ( const Vector4 &v )
{
	x = v.x; y = v.y; z = v.z, w = v.w;

	return *this;
}

inline Vector4::operator Vector3 ( ) const
{
	return Vector3( x, y, z );
}

inline Vector4 Vector4::operator + ( ) const
{
	return Vector4( x, y, z, w );
}

inline Vector4 Vector4::operator - ( ) const
{
	return Vector4( -x, -y, -z, -w );
}

inline Vector4& Vector4::operator += ( const Vector4& vector )
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	w += vector.w;

	return *this;
}

inline Vector4& Vector4::operator -= ( const Vector4& vector )
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	w -= vector.w;

	return *this;
}

inline Vector4& Vector4::operator *= ( _float scalar )
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;

	return *this;
}

inline Vector4& Vector4::operator *= ( const Vector4& vector )
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
	w *= vector.w;

	return *this;
}

inline Vector4& Vector4::operator /= ( _float scalar )
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;

	return *this;
}

inline Vector4& Vector4::operator /= ( const Vector4& vector )
{
	x /= vector.x;
	y /= vector.y;
	z /= vector.z;
	w /= vector.w;

	return *this;
}

inline Vector4 Vector4::operator + ( const Vector4& vector ) const
{
	Vector4 result;

	result.x = x + vector.x;
	result.y = y + vector.y;
	result.z = z + vector.z;
	result.w = w + vector.w;

	return result;
}

inline Vector4 Vector4::operator - ( const Vector4& vector ) const
{
	Vector4 result;

	result.x = x - vector.x;
	result.y = y - vector.y;
	result.z = z - vector.z;
	result.w = w - vector.w;

	return result;
}

inline Vector4 Vector4::operator * ( _float scalar ) const
{
	Vector4 result;

	result.x = x * scalar;
	result.y = y * scalar;
	result.z = z * scalar;
	result.w = w * scalar;

	return result;
}

inline Vector4 Vector4::operator * ( const Vector4& vector ) const
{
	Vector4 result;

	result.x = x * vector.x;
	result.y = y * vector.y;
	result.z = z * vector.z;
	result.w = w * vector.w;

	return result;
}

inline Vector4 Vector4::operator / ( _float scalar ) const
{
	Vector4 result;

	result.x = x / scalar;
	result.y = y / scalar;
	result.z = z / scalar;
	result.w = w / scalar;

	return result;
}

inline Vector4 Vector4::operator / ( const Vector4& vector ) const
{
	Vector4 result;

	result.x = x / vector.x;
	result.y = y / vector.y;
	result.z = z / vector.z;
	result.w = w / vector.w;

	return result;
}

inline _ubool Vector4::operator == ( const Vector4& vector ) const
{
	return x == vector.x && y == vector.y && z == vector.z && w == vector.w;
}

inline _ubool Vector4::operator != ( const Vector4& vector ) const
{
	return x != vector.x || y != vector.y || z != vector.z || w != vector.w;
}

inline _ubool Vector4::Equal( const Vector4& vector, _float margin ) const
{
	if ( Math::Abs( x - vector.x ) > margin )
		return _false;

	if ( Math::Abs( y - vector.y ) > margin )
		return _false;

	if ( Math::Abs( z - vector.z ) > margin )
		return _false;

	if ( Math::Abs( w - vector.w ) > margin )
		return _false;

	return _true;
}

inline Vector4& Vector4::Absolute( )
{
	if ( x < 0.0f )
		x = -x;

	if ( y < 0.0f )
		y = -y;

	if ( z < 0.0f )
		z = -z;

	if ( w < 0.0f )
		w = -w;

	return *this;
}

inline Vector4& Vector4::Normalize( )
{
#if (_USE_NEON_ == 1)
	_float v[] = { x, y, z, w };
	normalize4_neon( v, (_float*) this );
#else
	_float magnitude = Magnitude( );

	if ( magnitude > 0.0f )
	{
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
		w /= magnitude;
	}
	else
	{
		x = 1.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}
#endif

	return *this;
}

inline _float Vector4::Magnitude( ) const
{
	return Math::Sqrt( Dot( *this, *this ) );
}

inline _float Vector4::MagnitudeSquared( ) const
{
	return Dot( *this, *this );
}

inline _float Vector4::Dot( const Vector4& vector1, const Vector4& vector2 )
{
#if (_USE_NEON_ == 1)
	return dot4_neon( (_float*) &vector1, (_float*) &vector2 );
#else
	return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z + vector1.w * vector2.w;
#endif
}

inline Vector4 Vector4::Project( const Vector4& vector1, const Vector4& vector2 )
{
	Vector4 normal = vector2;
	normal.Normalize( );

	return normal * Dot( vector1, normal );
}

inline Vector4 Vector4::Plumb( const Vector4& vector1, const Vector4& vector2 )
{
	return vector1 - Vector4::Project( vector1, vector2 );
}

inline Vector4 Vector4::Lerp( const Vector4& vector1, const Vector4& vector2, _float factor )
{
	return vector1 + ( vector2 - vector1 ) * factor;
}

}