//! @file     Vector3.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

class Matrix3;
class Matrix3x4;
class Matrix4;
class Quaternion;
class Transform3D;

//----------------------------------------------------------------------------
// Vector3
//----------------------------------------------------------------------------

//! This class represents a 3D vector.
class Vector3
{
public:
	//! X-component of the vector.
	_float	x;
	//! Y-component of the vector.
	_float	y;
	//! Z-component of the vector.
	_float	z;

public:
	//! The origin vector.
	static const Vector3 cOrigin;
	//! The identity vector.
	static const Vector3 cIdentity;
	//! The x-axis vector.
	static const Vector3 cXAxis;
	//! The y-axis vector.
	static const Vector3 cYAxis;
	//! The z-axis vector.
	static const Vector3 cZAxis;
	//! The maximal vector.
	static const Vector3 cMaxVector;
	//! The minimal vector.
	static const Vector3 cMinVector;

public:
	//! Constructor, create a vector without sets x, y, z components.
	//! @param		none
	Vector3( );
	//! Constructor, create a vector and sets x, y, z components.
	//! @param		xx			X-component of the vector.
	//! @param		yy			Y-component of the vector.
	//! @param		zz			Z-component of the vector.
	Vector3( _float xx, _float yy, _float zz );

	//! Get positive vector.
	//! @param		none
	//! @return		The positive vector.
	Vector3 operator + ( ) const;
	//! Get negative vector.
	//! @param		none
	//! @return		The negative vector.
	Vector3 operator - ( ) const;

	//! Add a vector to current vector, and save result in current one.
	//! @param		vector		The vector to add.
	//! @return		The result vector of addition.
	Vector3& operator += ( const Vector3& vector );
	//! Subtract a vector from current vector, and save result in current one.
	//! @param		vector		The vector to subtract.
	//! @return		The result vector of subtraction.
	Vector3& operator -= ( const Vector3& vector );
	//! Multiply a scalar to current vector, and save result in current one.
	//! @param		scalar		The scalar to multiply.
	//! @return		The result vector of multiplication.
	Vector3& operator *= ( _float scalar );
	//! Multiply a vector to current vector, and save result in current one.
	//! @param		vector		The vector to multiply.
	//! @return		The result vector of multiplication.
	Vector3& operator *= ( const Vector3& vector );
	//! Divide a scalar to current vector, and save result in current one.
	//! @param		scalar		The scalar to divide.
	//! @return		The result vector of division.
	Vector3& operator /= ( _float scalar );
	//! Divide a vector to current vector, and save result in current one.
	//! @param		vector		The vector to divide.
	//! @return		The result vector of division.
	Vector3& operator /= ( const Vector3& vector );

	//! Multiply a matrix to current vector, and save result in current one.
	//! @param		matrix		The matrix to multiply.
	//! @return		The result vector of multiplication.
	Vector3& operator *= ( const Matrix3& matrix );
	//! Multiply a matrix to current vector, and save result in current one.
	//! @param		matrix		The matrix to multiply.
	//! @return		The result vector of multiplication.
	Vector3& operator *= ( const Matrix3x4& matrix );
	//! Multiply a matrix to current vector, and save result in current one.
	//! @param		matrix		The matrix to multiply.
	//! @return		The result vector of multiplication.
	Vector3& operator *= ( const Matrix4& matrix );
	//! Multiply a quaternion to current vector, and save result in current one.
	//! @param		matrix		The quaternion to multiply.
	//! @return		The result vector of multiplication.
	Vector3& operator *= ( const Quaternion& quaternion );
	//! Multiply a transform to current vector, and save result in current one.
	//! @param		transform	The transform to multiply.
	//! @return		The result vector of multiplication.
	Vector3& operator *= ( const Transform3D& transform );

	//! Add a vector to current vector, return a new vector to save result.
	//! @param		vector		The vector to add.
	//! @return		The result vector of addition.
	Vector3 operator + ( const Vector3& vector ) const;
	//! Subtract a vector from current vector, return a new vector to save result.
	//! @param		vector		The vector to subtract.
	//! @return		The result vector of subtraction.
	Vector3 operator - ( const Vector3& vector ) const;
	//! Multiply a scalar to current vector, return a new vector to save result.
	//! @param		scalar		The scalar to multiply.
	//! @return		The result vector of multiplication.
	Vector3 operator * ( _float scalar ) const;
	//! Multiply a vector to current vector, return a new vector to save result.
	//! @param		vector		The vector to multiply.
	//! @return		The result vector of multiplication.
	Vector3 operator * ( const Vector3& vector ) const;
	//! Divide a scalar to current vector, return a new vector to save result.
	//! @param		scalar		The scalar to divide.
	//! @return		The result vector of division.
	Vector3 operator / ( _float scalar ) const;
	//! Divide a vector to current vector, return a new vector to save result.
	//! @param		vector		The vector to divide.
	//! @return		The result vector of division.
	Vector3 operator / ( const Vector3& vector ) const;

	//! Compare two vectors.
	//! @param		vector		The vector to compare with.
	//! @return		True if they are identical, false otherwise.
	_ubool operator == ( const Vector3& vector ) const;
	//! Compare two vectors.
	//! @param		vector		The vector to compare with.
	//! @return		True if they are not identical, false otherwise.
	_ubool operator != ( const Vector3& vector ) const;

	//! Multiply a matrix to current vector, return a new vector to save result.
	//! @param		matrix		The matrix to multiply.
	//! @return		The result vector of multiplication.
	Vector3 operator * ( const Matrix3& matrix ) const;
	//! Multiply a matrix to current vector, return a new vector to save result.
	//! @param		matrix		The matrix to multiply.
	//! @return		The result vector of multiplication.
	Vector3 operator * ( const Matrix3x4& matrix ) const;
	//! Multiply a matrix to current vector, return a new vector to save result.
	//! @param		matrix		The matrix to multiply.
	//! @return		The result vector of multiplication.
	Vector3 operator * ( const Matrix4& matrix ) const;
	//! Multiply a matrix to current vector, return a new vector to save result.
	//! @param		matrix		The matrix to multiply.
	//! @return		The result vector of multiplication.
	Vector3 operator * ( const Quaternion& quaternion ) const;
	//! Multiply a Transform3D to current vector, return a new vector to save result.
	//! @param		transform		The Transform3D to multiply.
	//! @return		The result vector of multiplication.
	Vector3 operator * ( const Transform3D& transform ) const;

	//! Compare two vectors with error margin.
	//! @param		vector		The vector to compare with.
	//! @param		margin		The margin that allows some error.
	//! @return		True if they are identical, false otherwise.
	_ubool Equal( const Vector3& vector, _float margin = Math::cFloatEpsilon ) const;

	//! Make the current vector absolute, that all coordinates are nonnegative.
	//! @param		none
	//! @return		The absolute vector.
	Vector3& Absolute( );
	//! Make the current vector normalized, that has one unit magnitude.
	//! @param		none
	//! @return		The normalized vector.
	Vector3& Normalize( );

	//! Make the current vector normalized by bounding box, that x, y, z is from 0 ~ 1
	//! @param		none
	//! @return		The normalized vector.
	Vector3& NormalizeByBoundingBox( const Vector3& bounding_min, const Vector3& bounding_max );

	//! Convert vector from cartesian to spherical coordinates.
	//! @param		none
	//! The spherical coordinates vector, in rho, phi, theta format.
	Vector3& Cartesian2Spherical( );
	//! Convert vector from spherical to cartesian coordinates.
	//! @param		none
	//! The spherical coordinates vector, in x, y, z format.
	Vector3& Spherical2Cartesian( );

	//! Calculates vector magnitude.
	//! @param		none
	//! @return		The magnitude of vector.
	_float Magnitude( ) const;
	//! Calculates the square of vector magnitude, this function is faster than Magnitude.
	//! @param		none
	//! @return		The square of magnitude of vector.
	_float MagnitudeSquared( ) const;

public:
	//! Get min vector of two vectors.
	//! @param		vector1		Source vector 1.
	//! @param		vector2		Source vector 2.
	//! @return		The min vector result.
	static Vector3 Min( const Vector3& vector1, const Vector3& vector2 );
	//! Get max vector of two vectors.
	//! @param		vector1		Source vector 1.
	//! @param		vector2		Source vector 2.
	//! @return		The max vector result.
	static Vector3 Max( const Vector3& vector1, const Vector3& vector2 );
	//! Clamp value into the range specified by min and max.
	//! @param		value		Integer value to be clamped.
	//! @param		min			Minimal value of the range.
	//! @param		max			Maximal value of the range.
	//! @return		The clamped value.
	static Vector3 Clamp( const Vector3& vector, const Vector3& min, const Vector3& max );

	//! Calculates dot product of two vectors.
	//! @param		vector1		Source vector 1.
	//! @param		vector2		Source vector 2.
	//! @return		The dot product result.
	static _float Dot( const Vector3& vector1, const Vector3& vector2 );
	//! Calculates cross product of two vectors.
	//! @param		vector1		Source vector 1.
	//! @param		vector2		Source vector 2.
	//! @return		The cross product result.
	static Vector3 Cross( const Vector3& vector1, const Vector3& vector2 );
	//! Calculates vector by project one vector to another.
	//! @param		vector1		The vector to be projected.
	//! @param		vector2		The project reference vector.
	//! @return		The projected vector, that has same direction of vector2.
	static Vector3 Project( const Vector3& vector1, const Vector3& vector2 );
	//! Calculates vector by plumb one vector to another.
	//! @param		vector1		The vector to be projected.
	//! @param		vector2		The project reference vector.
	//! @return		The plumbed vector, that is vertical of vector2.
	static Vector3 Plumb( const Vector3& vector1, const Vector3& vector2 );
	//! Calculates linear interpolation of two vectors.
	//! @param		vector1		Source vector 1.
	//! @param		vector2		Source vector 2.
	//! @param		factor		The interpolation factor, will clamp to between 0 to 1.
	//! @return		The result vector of interpolation, vector1 + ( vector2 - vector1 ) * factor.
	static Vector3 Lerp( const Vector3& vector1, const Vector3& vector2, _float factor );

	//! Calculates angle vector1 rotate to vector2;
	//! @param		vector1		rotation begin vector;
	//! @param		vector2		rotation end vector;
	//! @return		The angle vector1 rotate to vector2;
	static _float GetAngle( const Vector3& vector1, const Vector3& vector2 );

	//!	Get the position of a 3D point on screen.
	//!	@param		point		The 3D point.
	//!	@return		The position on screen.
	static Vector2 Convert3DTo2D( const PointU& viewport_size, const Vector3& point );

	static _ubool IsNegative( const Vector3& srcvector, const Vector3& desvector );
};

//----------------------------------------------------------------------------
// Vector3 Implementation
//----------------------------------------------------------------------------

inline Vector3::Vector3( )
{
}

inline Vector3::Vector3( _float xx, _float yy, _float zz ) : x( xx ), y( yy ), z( zz )
{
}

inline Vector3 Vector3::operator + ( ) const
{
	return Vector3( x, y, z );
}

inline Vector3 Vector3::operator - ( ) const
{
	return Vector3( -x, -y, -z );
}

inline Vector3& Vector3::operator += ( const Vector3& vector )
{
	x += vector.x;
	y += vector.y;
	z += vector.z;

	return *this;
}

inline Vector3& Vector3::operator -= ( const Vector3& vector )
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;

	return *this;
}

inline Vector3& Vector3::operator *= ( _float scalar )
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

inline Vector3& Vector3::operator *= ( const Vector3& vector )
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;

	return *this;
}

inline Vector3& Vector3::operator /= ( _float scalar )
{
	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

inline Vector3& Vector3::operator /= ( const Vector3& vector )
{
	x /= vector.x;
	y /= vector.y;
	z /= vector.z;

	return *this;
}

inline Vector3 Vector3::operator + ( const Vector3& vector ) const
{
	return Vector3( x + vector.x, y + vector.y, z + vector.z );
}

inline Vector3 Vector3::operator - ( const Vector3& vector ) const
{
	return Vector3( x - vector.x, y - vector.y, z - vector.z );
}

inline Vector3 Vector3::operator * ( _float scalar ) const
{
	return Vector3( x * scalar, y * scalar, z * scalar );
}

inline Vector3 Vector3::operator * ( const Vector3& vector ) const
{
	return Vector3( x * vector.x, y * vector.y, z * vector.z );
}

inline Vector3 Vector3::operator / ( _float scalar ) const
{
	return Vector3( x / scalar, y / scalar, z / scalar );
}

inline Vector3 Vector3::operator / ( const Vector3& vector ) const
{
	return Vector3( x / vector.x, y / vector.y, z / vector.z );
}

inline _ubool Vector3::operator == ( const Vector3& vector ) const
{
	return x == vector.x && y == vector.y && z == vector.z;
}

inline _ubool Vector3::operator != ( const Vector3& vector ) const
{
	return x != vector.x || y != vector.y || z != vector.z;
}

inline _ubool Vector3::Equal( const Vector3& vector, _float margin ) const
{
	if ( Math::Abs( x - vector.x ) > margin )
		return _false;

	if ( Math::Abs( y - vector.y ) > margin )
		return _false;

	if ( Math::Abs( z - vector.z ) > margin )
		return _false;

	return _true;
}

inline _float Vector3::Magnitude( ) const
{
	return Math::Sqrt( x * x + y * y + z * z );
}

inline _float Vector3::MagnitudeSquared( ) const
{
	return x * x + y * y + z * z;
}

inline Vector3 Vector3::Min( const Vector3& vector1, const Vector3& vector2 )
{
	Vector3 vector;
	vector.x = Math::Min( vector1.x, vector2.x );
	vector.y = Math::Min( vector1.y, vector2.y );
	vector.z = Math::Min( vector1.z, vector2.z );

	return vector;
}

inline Vector3 Vector3::Max( const Vector3& vector1, const Vector3& vector2 )
{
	Vector3 vector;
	vector.x = Math::Max( vector1.x, vector2.x );
	vector.y = Math::Max( vector1.y, vector2.y );
	vector.z = Math::Max( vector1.z, vector2.z );

	return vector;
}

inline Vector3 Vector3::Clamp( const Vector3& vector, const Vector3& min, const Vector3& max )
{
	_float x = Math::Clamp( vector.x, min.x, max.x );
	_float y = Math::Clamp( vector.x, min.y, max.y );
	_float z = Math::Clamp( vector.x, min.z, max.z );
	return Vector3( x, y, z );
}

inline Vector3& Vector3::Absolute( )
{
	if ( x < 0.0f )
		x = -x;

	if ( y < 0.0f )
		y = -y;

	if ( z < 0.0f )
		z = -z;

	return *this;
}

inline Vector3& Vector3::Normalize( )
{
#if (_USE_NEON_ == 1)
	_float v[] = { x, y, z };
	normalize3_neon( v, (_float*) this );
#else
	_float magnitude = Magnitude( );

	if ( magnitude > 0.0f )
	{
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
	}
	else
	{
		x = 1.0f;
		y = 0.0f;
		z = 0.0f;
	}
#endif

	return *this;
}

inline Vector3& Vector3::NormalizeByBoundingBox( const Vector3& bounding_min, const Vector3& bounding_max )
{
	Vector3 bounding_size = bounding_max - bounding_min;

	x = bounding_size.x == 0.0f ? 0.0f : ( ( x - bounding_min.x ) / bounding_size.x );
	y = bounding_size.y == 0.0f ? 0.0f : ( ( y - bounding_min.y ) / bounding_size.y );
	z = bounding_size.z == 0.0f ? 0.0f : ( ( z - bounding_min.z ) / bounding_size.z );

	return *this;
}

inline _float Vector3::Dot( const Vector3& vector1, const Vector3& vector2 )
{
#if (_USE_NEON_ == 1)
	return dot3_neon( (_float*) &vector1, (_float*) &vector2 );
#else
	return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
#endif
}

inline Vector3 Vector3::Cross( const Vector3& vector1, const Vector3& vector2 )
{
#if (_USE_NEON_ == 1)
	Vector3 cross_vec3;
	cross3_neon( (_float*) &vector1, (_float*) &vector2, (_float*) &cross_vec3 );
	return cross_vec3;
#else
	return Vector3(
		vector1.y * vector2.z - vector1.z * vector2.y,
		vector1.z * vector2.x - vector1.x * vector2.z,
		vector1.x * vector2.y - vector1.y * vector2.x );
#endif
}

inline Vector3 Vector3::Project( const Vector3& vector1, const Vector3& vector2 )
{
	Vector3 normal = vector2;
	normal.Normalize( );

	return normal * Dot( vector1, normal );
}

inline Vector3 Vector3::Plumb( const Vector3& vector1, const Vector3& vector2 )
{
	return vector1 - Vector3::Project( vector1, vector2 );
}

inline Vector3 Vector3::Lerp( const Vector3& vector1, const Vector3& vector2, _float factor )
{
	return vector1 + ( vector2 - vector1 ) * factor;
}

inline Vector2 Vector3::Convert3DTo2D( const PointU& viewport_size, const Vector3& point )
{
	return Vector2( ( 1.0f + point.x ) * viewport_size.x * 0.5f, ( 1.0f - point.y ) * viewport_size.y * 0.5f );
}

}