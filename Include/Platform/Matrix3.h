//! @file     Matrix3.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Matrix3
//----------------------------------------------------------------------------

//! This class represents a 3D Matrix.
class Matrix3
{
public:
	//! The component of the matrix.
	_float	m[3][3];

public:
	//! The zero matrix.
	static const Matrix3 cZero;
	//! The identity matrix.
	static const Matrix3 cIdentity;

public:
	//! Constructor, create a matrix without sets components.
	//! @param		none
	Matrix3( );
	//! Constructor, create a matrix and sets components.
	//! @param		position	The position.
	//! @param		scale		The scale factor.
	//! @param		rotation	The rotation radian.
	Matrix3( const Vector2& position, const Vector2& scale, _float radian );
	//! Constructor, create a matrix and sets components.
	//! @param		m00~m22		The component of the matrix.
	Matrix3( _float m00, _float m01, _float m02, _float m10, _float m11, _float m12, _float m20, _float m21, _float m22 );

	//! Get positive matrix.
	//! @param		none
	//! @return		The positive matrix.
	Matrix3 operator + ( ) const;
	//! Get negative matrix.
	//! @param		none
	//! @return		The negative matrix.
	Matrix3 operator - ( ) const;

	//! Get a row from matrix.
	//! @param		row			Rom number of the matrix.
	//! @return		The row vector.
	Vector3 GetRow( _dword row ) const;
	//! Get a column from matrix.
	//! @param		column		Column number of the matrix.
	//! @return		The column vector.
	Vector3 GetColumn( _dword column ) const;

	//! Get the translation vector, without rotation.
	//! @param		none
	//! @return		The translation vector.
	Vector2 GetTranslationVector( ) const;

	//! Add a matrix to current matrix, and save result in current one.
	//! @param		matrix		The matrix to add.
	//! @return		The result matrix of addition.
	Matrix3& operator += ( const Matrix3& matrix );
	//! Subtract a matrix to current matrix, and save result in current one.
	//! @param		matrix		The matrix to subtract.
	//! @return		The result matrix of subtraction.
	Matrix3& operator -= ( const Matrix3& matrix );
	//! Multiply a matrix to current matrix, and save result in current one.
	//! @param		matrix		The matrix to multiply.
	//! @return		The result matrix of multiplication.
	Matrix3& operator *= ( const Matrix3& matrix );
	//! Multiply a scalar to current matrix, and save result in current one.
	//! @param		scalar		The scalar to multiply.
	//! @return		The result matrix of multiplication.
	Matrix3& operator *= ( _float scalar );
	//! Divide a scalar to current matrix, and save result in current one.
	//! @param		scalar		The scalar to divide.
	//! @return		The result quaternion of division.
	Matrix3& operator /= ( _float scalar );

	//! Add a matrix to current matrix, return a new matrix to save result.
	//! @param		matrix		The matrix to add.
	//! @return		The result matrix of addition.
	Matrix3 operator + ( const Matrix3& matrix ) const;
	//! Subtract a matrix to current matrix, return a new matrix to save result.
	//! @param		matrix		The matrix to subtract.
	//! @return		The result matrix of subtraction.
    Matrix3 operator - ( const Matrix3& matrix ) const;
	//! Multiply a matrix to current matrix, return a new matrix to save result.
	//! @param		matrix		The matrix to multiply.
	//! @return		The result matrix of multiplication.
    Matrix3 operator * ( const Matrix3& matrix ) const;
	//! Multiply a scalar to current matrix, return a new matrix to save result.
	//! @param		scalar		The scalar to multiply.
	//! @return		The result matrix of multiplication.
    Matrix3 operator * ( _float scalar ) const;
	//! Divide a scalar to current matrix, return a new matrix to save result.
	//! @param		scalar		The scalar to divide.
	//! @return		The result quaternion of division.
    Matrix3 operator / ( _float scalar ) const;

	//! Compare two matrix.
	//! @param		matrix		The matrix to compare with.
	//! @return		True if they are identical, false otherwise.
	_ubool operator == ( const Matrix3& matrix ) const;
	//! Compare two matrix.
	//! @param		matrix		The matrix to compare with.
	//! @return		True if they are not identical, false otherwise.
	_ubool operator != ( const Matrix3& matrix ) const;

	//! Calculates the determinant of the matrix.
	//! @param		none
	//! @return		The determinant of the matrix.
	_float Determinant( ) const;

	//! Calculates identity matrix, and save result in current one.
	//! @param		none
	//! @return		The identity matrix.
	Matrix3& Identity( );
	//! Calculates transpose matrix, and save result in current one.
	//! @param		none
	//! @return		The transpose matrix.
	Matrix3& Transpose( );
	//! Calculates inverse matrix, and save result in current one.
	//! @param		none
	//! @return		The inverse matrix.
	Matrix3& Inverse( );
	//! Calculates adjoint matrix, and save result in current one.
	//! @param		none
	//! @return		The adjoint matrix.
	Matrix3& Adjoint( );

	//! Get rotation quaternion from current matrix.
	//! @param		rotation	The quaternion of rotation, get from this function.
	_void ToRotation( Quaternion& rotation ) const;
	//! Create a matrix from a quaternion
	//! @param		rotation	The quaternion of rotation.
	//! @return		The reference of current matrix.
	Matrix3& FromRotation( const Quaternion& rotation );

	//! Parse position, scale and radian from it.
	_void AnalysisMatrix( Vector2& position, Vector2& scale, _float& radian ) const;

public:
	//! Create a translation matrix.
	//! @param		x			The x-component of translation.
	//! @param		y			The y-component of translation.
	//! @return		The translation matrix.
	static Matrix3 CreateTranslation( _float x, _float y );
	//! Create a translation matrix.
	//! @param		vector		The translation vector.
	//! @return		The translation matrix.
	static Matrix3 CreateTranslation( const Vector2& vector );

	//! Create a scaling matrix.
	//! @param		x			The x-component of scaling.
	//! @param		y			The y-component of scaling.
	//! @param		z			The z-component of scaling.
	//! @return		The scaling matrix.
	static Matrix3 CreateScaling( _float x, _float y, _float z );
	//! Create a scaling matrix.
	//! @param		vector		The scaling vector.
	//! @return		The scaling matrix.
	static Matrix3 CreateScaling( const Vector3& vector );
	//! Create a scaling matrix by scale in an arbitrary direction.
	//! @param		vector		The normal vector defines the direction of scale.
	//! @param		factor		The scale factor.
	//! @return		The scaling matrix.
	static Matrix3 CreateScaling( const Vector3& vector, _float factor );

	//! Create a rotation matrix by rotate around origin, same as matrix2
	//! @param		radian		The angle of rotation in radian.
	//! @return		The rotation matrix.
	static Matrix3 CreateRotation( _float radian );
	//! Create a rotation matrix by rotate around x-axis.
	//! @param		radian		The angle of rotation in radian.
	//! @return		The rotation matrix.
	static Matrix3 CreateRotationX( _float radian );
	//! Create a rotation matrix by rotate around y-axis.
	//! @param		radian		The angle of rotation in radian.
	//! @return		The rotation matrix.
	static Matrix3 CreateRotationY( _float radian );
	//! Create a rotation matrix by rotate around z-axis.
	//! @param		radian		The angle of rotation in radian.
	//! @return		The rotation matrix.
	static Matrix3 CreateRotationZ( _float radian );
	//! Create a rotation matrix by rotate around an arbitrary axis.
	//! @param		axis		The axis to rotate around.
	//! @param		radian		The angle of rotation in radian.
	//! @return		The rotation matrix.
	static Matrix3 CreateRotation( const Vector3& axis, _float radian );

	//! Create a projection matrix by project onto xy-plane.
	//! @param		none
	//! @return		The projection matrix.
	static Matrix3 CreateProjectXY( );
	//! Create a projection matrix by project onto yz-plane.
	//! @param		none
	//! @return		The projection matrix.
	static Matrix3 CreateProjectYZ( );
	//! Create a projection matrix by project onto zx-plane.
	//! @param		none
	//! @return		The projection matrix.
	static Matrix3 CreateProjectZX( );
	//! Create a projection matrix by project onto an arbitrary plane.
	//! @param		vector		The normal vector defines the project plane.
	//! @return		The projection matrix.
	static Matrix3 CreateProject( const Vector3& vector );

	//! Create a reflection matrix by flip around xy-plane.
	//! @param		none
	//! @return		The reflection matrix.
	static Matrix3 CreateRefectionXY( );
	//! Create a reflection matrix by flip around yz-plane.
	//! @param		none
	//! @return		The reflection matrix.
	static Matrix3 CreateRefectionYZ( );
	//! Create a reflection matrix by flip around zx-plane.
	//! @param		none
	//! @return		The reflection matrix.
	static Matrix3 CreateRefectionZX( );
	//! Create a reflection matrix by flip around an arbitrary plane.
	//! @param		vector		The normal vector defines the reflect plane.
	//! @return		The reflection matrix.
	static Matrix3 CreateRefection( const Vector3& vector );

	//! Build transform by region.
	static Matrix3 CreateFromRegion( const RectF& region );
	//! Build transform by region and size.
	static Matrix3 CreateFromRegion( const RectF& region, const Vector2& size );
	//! Build transform by region, size and offset.
	static Matrix3 CreateFromRegion( const RectF& region, const Vector2& size, const Vector2& base_offset );
};

//----------------------------------------------------------------------------
// Matrix3 Implementation
//----------------------------------------------------------------------------

inline Matrix3::Matrix3( )
{
}

inline Matrix3::Matrix3( const Vector2& position, const Vector2& scale, _float radian )
{
	_float sinvalue, cosvalue;
	Math::SinCos( radian, sinvalue, cosvalue );

	m[0][0]	= scale.x * cosvalue;	m[0][1] = scale.x * sinvalue; 	m[0][2] = 0.0f;
	m[1][0] = scale.y * -sinvalue;	m[1][1] = scale.y * cosvalue; 	m[1][2] = 0.0f;
	m[2][0] = position.x;			m[2][1] = position.y;			m[2][2] = 1.0f;
}

inline Matrix3::Matrix3( _float m00, _float m01, _float m02, _float m10, _float m11, _float m12, _float m20, _float m21, _float m22 )
{
	m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
	m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
	m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
}

inline Matrix3 Matrix3::operator + ( ) const
{
	return Matrix3( m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2] );
}

inline Matrix3 Matrix3::operator - ( ) const
{
	return Matrix3( -m[0][0], -m[0][1], -m[0][2], -m[1][0], -m[1][1], -m[1][2], -m[2][0], -m[2][1], -m[2][2] );
}

inline _ubool Matrix3::operator == ( const Matrix3& matrix ) const
{
	if ( m[0][0] != matrix.m[0][0] ) return _false;
	if ( m[0][1] != matrix.m[0][1] ) return _false;
	if ( m[0][2] != matrix.m[0][2] ) return _false;

	if ( m[1][0] != matrix.m[1][0] ) return _false;
	if ( m[1][1] != matrix.m[1][1] ) return _false;
	if ( m[1][2] != matrix.m[1][2] ) return _false;

	if ( m[2][0] != matrix.m[2][0] ) return _false;
	if ( m[2][1] != matrix.m[2][1] ) return _false;
	if ( m[2][2] != matrix.m[2][2] ) return _false;

	return _true;
}

inline _ubool Matrix3::operator != ( const Matrix3& matrix ) const
{
	if ( m[0][0] != matrix.m[0][0] ) return _true;
	if ( m[0][1] != matrix.m[0][1] ) return _true;
	if ( m[0][2] != matrix.m[0][2] ) return _true;

	if ( m[1][0] != matrix.m[1][0] ) return _true;
	if ( m[1][1] != matrix.m[1][1] ) return _true;
	if ( m[1][2] != matrix.m[1][2] ) return _true;

	if ( m[2][0] != matrix.m[2][0] ) return _true;
	if ( m[2][1] != matrix.m[2][1] ) return _true;
	if ( m[2][2] != matrix.m[2][2] ) return _true;

	return _false;
}

inline Vector3 Matrix3::GetRow( _dword row ) const
{
	EGE_ASSERT( row < 3 )

	return Vector3( m[ row ][0], m[ row ][1], m[ row ][2] );
}

inline Vector3 Matrix3::GetColumn( _dword column ) const
{
	EGE_ASSERT( column < 3 )

	return Vector3( m[0][ column ], m[1][ column ], m[2][ column ] );
}

inline Vector2 Matrix3::GetTranslationVector( ) const
{
	return Vector2( m[2][0], m[2][1] );
}

}