//! @file     Matrix4.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Matrix4
//----------------------------------------------------------------------------

//! This class represents a 4D Matrix.
class Matrix4
{
public:
	//! The component of the matrix.
	_float	m[4][4];

public:
	//! The zero matrix.
	static const Matrix4 cZero;
	//! The identity matrix.
	static const Matrix4 cIdentity;
	//! The clip space to image space matrix.
	static const Matrix4 cClip2Image;

public:
	//! Constructor, create a matrix without sets components.
	//! @param		none
	Matrix4( );
	//! Constructor, create a matrix and sets components.
	//! @param		m00~m33		The component of the matrix.
	Matrix4( _float m00, _float m01, _float m02, _float m03, _float m10, _float m11, _float m12, _float m13,
		_float m20, _float m21, _float m22, _float m23, _float m30, _float m31, _float m32, _float m33 );
	//! Constructor, create a matrix and sets components.
	//! @param		m		The matrix create from.
	Matrix4( const Matrix3x4& matrix );
	//! Copy Constructor, create a matrix and sets components by a given matrix.
	//! @param		m		The matrix create from.
	Matrix4( const Matrix4& matrix );

	//! Copy components from another matrix.
	//! @param		m		The other matrix.
	//! @return		The reference of current matrix.
	Matrix4& operator = ( const Matrix4& matrix );

	//! Get positive matrix.
	//! @param		none
	//! @return		The positive matrix.
	Matrix4 operator + ( ) const;
	//! Get negative matrix.
	//! @param		none
	//! @return		The negative matrix.
	Matrix4 operator - ( ) const;

	//! Get a row from matrix.
	//! @param		row			Rom number of the matrix.
	//! @return		The row vector.
	Vector4 GetRow( _dword row ) const;
	//! Get a column from matrix.
	//! @param		column		Column number of the matrix.
	//! @return		The column vector.
	Vector4 GetColumn( _dword column ) const;

	//! Get the rotation matrix, without translation.
	//! @param		none
	//! @return		The rotation matrix.
	Matrix3 GetRotationMatrix( ) const;

	//! Get the scaling vector. may be not right
	//! @param		none
	//! @return		The scaling vector.
	Vector3 GetScalingVector( ) const;
	//! Get the translation vector, without rotation.
	//! @param		none
	//! @return		The translation vector.
	Vector3 GetTranslationVector( ) const;
	Matrix4& SetTranslationVector( const Vector3& translation );
	Matrix4& SetTranslationVector( _float x, _float y, _float z );

	//! Get the up vector in view matrix.
	Vector3 GetUpVector( ) const;
	//! Get the right vector in view matrix.
	Vector3 GetRightVector( ) const;
	//! Get the forward vector in view matrix.
	Vector3 GetForwardVector( ) const;

	//! Add a matrix to current matrix, and save result in current one.
	//! @param		matrix		The matrix to add.
	//! @return		The result matrix of addition.
	Matrix4& operator += ( const Matrix4& matrix );
	//! Subtract a matrix to current matrix, and save result in current one.
	//! @param		matrix		The matrix to subtract.
	//! @return		The result matrix of subtraction.
	Matrix4& operator -= ( const Matrix4& matrix );
	//! Multiply a matrix to current matrix, and save result in current one.
	//! @param		matrix		The matrix to multiply.
	//! @return		The result matrix of multiplication.
	Matrix4& operator *= ( const Matrix2& matrix );
	//! Multiply a matrix to current matrix, and save result in current one.
	//! @param		matrix		The matrix to multiply.
	//! @return		The result matrix of multiplication.
	Matrix4& operator *= ( const Matrix3x4& matrix );
	//! Multiply a matrix to current matrix, and save result in current one.
	//! @param		matrix		The matrix to multiply.
	//! @return		The result matrix of multiplication.
	Matrix4& operator *= ( const Matrix4& matrix );
	//! Multiply a scalar to current matrix, and save result in current one.
	//! @param		scalar		The scalar to multiply.
	//! @return		The result matrix of multiplication.
	Matrix4& operator *= ( _float scalar );
	//! Divide a scalar to current matrix, and save result in current one.
	//! @param		scalar		The scalar to divide.
	//! @return		The result quaternion of division.
	Matrix4& operator /= ( _float scalar );

	//! Add a matrix to current matrix, return a new matrix to save result.
	//! @param		matrix		The matrix to add.
	//! @return		The result matrix of addition.
	Matrix4 operator + ( const Matrix4& matrix ) const;
	//! Subtract a matrix to current matrix, return a new matrix to save result.
	//! @param		matrix		The matrix to subtract.
	//! @return		The result matrix of subtraction.
    Matrix4 operator - ( const Matrix4& matrix ) const;
	//! Multiply a matrix to current matrix, return a new matrix to save result.
	//! @param		matrix		The matrix to multiply.
	//! @return		The result matrix of multiplication.
	Matrix4 operator * ( const Matrix2& matrix ) const;
	//! Multiply a matrix to current matrix, return a new matrix to save result.
	//! @param		matrix		The matrix to multiply.
	//! @return		The result matrix of multiplication.
	Matrix4 operator * ( const Matrix3x4& matrix ) const;
	//! Multiply a matrix to current matrix, return a new matrix to save result.
	//! @param		matrix		The matrix to multiply.
	//! @return		The result matrix of multiplication.
    Matrix4 operator * ( const Matrix4& matrix ) const;
	//! Multiply a scalar to current matrix, return a new matrix to save result.
	//! @param		scalar		The scalar to multiply.
	//! @return		The result matrix of multiplication.
    Matrix4 operator * ( _float scalar ) const;
	//! Divide a scalar to current matrix, return a new matrix to save result.
	//! @param		scalar		The scalar to divide.
	//! @return		The result quaternion of division.
    Matrix4 operator / ( _float scalar ) const;

	//! Compare two matrix.
	//! @param		matrix		The matrix to compare with.
	//! @return		True if they are identical, false otherwise.
	_ubool operator == ( const Matrix4& matrix ) const;
	//! Compare two matrix.
	//! @param		matrix		The matrix to compare with.
	//! @return		True if they are not identical, false otherwise.
	_ubool operator != ( const Matrix4& matrix ) const;

	//! Compare two matrix with error margin.
	//! @param		matrix		The matrix to compare with.
	//! @param		margin		The margin that allows some error.
	//! @return		True if they are identical, false otherwise.
	_ubool Equal( const Matrix4& matrix, _float margin = Math::cFloatEpsilon ) const;

	//! If a matrix has only translation.
	//! @param		none
	//! @return		True if matrix has only translation, false otherwise.
	_ubool OnlyTranslation( ) const;

	//! Calculates the determinant of the matrix.
	//! @param		none
	//! @return		The determinant of the matrix.
	_float Determinant( ) const;

	//! Calculates identity matrix, and save result in current one.
	//! @param		none
	//! @return		The identity matrix.
	Matrix4& Identity( );
	//! Calculates transpose matrix, and save result in current one.
	//! @param		none
	//! @return		The transpose matrix.
	Matrix4& Transpose( );
	//! Calculates inverse matrix, and save result in current one.
	//! @param		none
	//! @return		The inverse matrix.
	Matrix4& Inverse( );
	//! Calculates adjoint matrix, and save result in current one.
	//! @param		none
	//! @return		The adjoint matrix.
	Matrix4& Adjoint( );

	//! Translate.
	//! @param		x			The x-component of translation.
	//! @param		y			The y-component of translation.
	//! @param		z			The z-component of translation.
	//! @return		The translation matrix.
	Matrix4& Translate( _float x, _float y, _float z );
	//! Translate.
	//! @param		vector		The translation vector.
	//! @return		The translation matrix.
	Matrix4& Translate( const Vector3& vector );

	//! Create a translation matrix.
	//! @param		x			The x-component of translation.
	//! @param		y			The y-component of translation.
	//! @param		z			The z-component of translation.
	//! @return		The translation matrix.
	Matrix4& Translation( _float x, _float y, _float z );
	//! Create a translation matrix.
	//! @param		vector		The translation vector.
	//! @return		The translation matrix.
	Matrix4& Translation( const Vector3& vector );

	//! Create a scaling matrix.
	//! @param		x			The x-component of scaling.
	//! @param		y			The y-component of scaling.
	//! @param		z			The z-component of scaling.
	//! @return		The scaling matrix.
	Matrix4& Scaling( _float x, _float y, _float z );
	//! Create a scaling matrix.
	//! @param		vector		The scaling vector.
	//! @return		The scaling matrix.
	Matrix4& Scaling( const Vector3& vector );
	//! Create a scaling matrix by scale in an arbitrary direction.
	//! @param		vector		The normal vector defines the direction of scale.
	//! @param		factor		The scale factor.
	//! @return		The scaling matrix.
	Matrix4& Scaling( const Vector3& vector, _float factor );

	//! Create a rotation matrix by rotate around x-axis.
	//! @param		radian		The angle of rotation in radian.
	//! @return		The rotation matrix.
	Matrix4& RotationX( _float radian );
	//! Create a rotation matrix by rotate around y-axis.
	//! @param		radian		The angle of rotation in radian.
	//! @return		The rotation matrix.
	Matrix4& RotationY( _float radian );
	//! Create a rotation matrix by rotate around z-axis.
	//! @param		radian		The angle of rotation in radian.
	//! @return		The rotation matrix.
	Matrix4& RotationZ( _float radian );
	//! Create a rotation matrix by rotate around an arbitrary axis.
	//! @param		axis		The axis to rotate around.
	//! @param		radian		The angle of rotation in radian.
	//! @return		The rotation matrix.
	Matrix4& Rotation( const Vector3& axis, _float radian );
	//! Create a rotation matrix that rotate one vector into another.
	//! @param		srcvector	The source vector to be rotated.
	//! @param		desvector	The target vector to rotate into.
	//! @return		The rotation matrix.
	Matrix4& Rotation( const Vector3& srcvector, const Vector3& desvector );
	//! Create a rotation matrix from a quaternion.
	//! @param		rotation	The quaternion of rotation.
	//! @return		The rotation matrix.
	Matrix4& Rotation( const Quaternion& rotation );
	//! Create a rotation matrix from a euler angles.
	//! @param		eulerangles	The euler angles of rotation.
	//! @return		The rotation matrix.
	Matrix4& Rotation( const EulerAngles& eulerangles );
	//! Create a rotation quaternion that rotate one coordinate into another.
	//! @param		src_coordinate_axis1	The one axis of source coordinate system to be rotated.
	//! @param		src_coordinate_axis2	The another axis of source coordinate system to be rotated.
	//! @param		des_coordinate_axis1	The one axis of the target coordinate system to rotate into.
	//! @param		des_coordinate_axis2	The another axis of the target coordinate system to rotate into.
	//! @return		The rotation quaternion.
	Matrix4& Rotation( const Vector3& src_coordinate_axis1, const Vector3& src_coordinate_axis2, const Vector3& des_coordinate_axis1, const Vector3& des_coordinate_axis2 );


	//! Create a projection matrix by project onto xy-plane.
	//! @param		none
	//! @return		The projection matrix.
	Matrix4& ProjectXY( );
	//! Create a projection matrix by project onto yz-plane.
	//! @param		none
	//! @return		The projection matrix.
	Matrix4& ProjectYZ( );
	//! Create a projection matrix by project onto zx-plane.
	//! @param		none
	//! @return		The projection matrix.
	Matrix4& ProjectZX( );
	//! Create a projection matrix by project onto an arbitrary plane.
	//! @param		vector		The normal vector defines the project plane.
	//! @return		The projection matrix.
	Matrix4& Project( const Vector3& vector );

	//! Create a reflection matrix by flip around xy-plane.
	//! @param		none
	//! @return		The reflection matrix.
	Matrix4& RefectionXY( );
	//! Create a reflection matrix by flip around yz-plane.
	//! @param		none
	//! @return		The reflection matrix.
	Matrix4& RefectionYZ( );
	//! Create a reflection matrix by flip around zx-plane.
	//! @param		none
	//! @return		The reflection matrix.
	Matrix4& RefectionZX( );
	//! Create a reflection matrix by flip around an arbitrary plane.
	//! @param		vector		The normal vector defines the reflect plane.
	//! @return		The reflection matrix.
	Matrix4& Refection( const Vector3& vector );

	//! Create a matrix from a matrix and a vector.
	//!	@remark		The (m[3][0], m[3][1], m[3][2]) will be the translation position from matrix 3x3.
	//! @param		matrix		The matrix of rotation and translation.
	//! @return		The reference of current matrix.
	Matrix4& FromTranslationRotation( const Matrix3& matrix );
	//! Create a matrix from a matrix and a vector.
	//! @param		translation	The vector of translation.
	//! @param		rotation	The matrix of rotation.
	//! @return		The reference of current matrix.
	Matrix4& FromTranslationRotation( const Vector3& translation, const Matrix3& rotation );
	//! Get the translation vector and rotation matrix from current matrix.
	//! @param		translation	The vector of translation, get from this function.
	//! @param		rotation	The matrix of rotation, get from this function.
	_void ToTranslationRotation( Vector3& translation, Matrix3& rotation ) const;

	//! Create a matrix from a quaternion and a vector.
	//! @param		translation	The vector of translation.
	//! @param		rotation	The quaternion of rotation.
	//! @return		The reference of current matrix.
	Matrix4& FromTranslationRotation( const Vector3& translation, const Quaternion& rotation );
	//! Get the translation vector and rotation quaternion from current matrix.
	//! @param		translation	The vector of translation, get from this function.
	//! @param		rotation	The quaternion of rotation, get from this function.
	_void ToTranslationRotation( Vector3& translation, Quaternion& rotation ) const;

	Matrix4& FromTranslationRotationScale( const Vector3& translation, const Quaternion& rotation, const Vector3& scale );

	//! Builds a right-handed orthogonal projection matrix.
	//! @param		width		Width of the view volume.
	//! @param		height		Height of the view volume.
	//! @param		znear		Z-value of the near view plane.
	//! @param		zfar		Z-value of the far view plane.
	//! @return		The right-handed orthogonal projection matrix.
	static Matrix4 CreateOrthoRH( _float width, _float height, _float znear, _float zfar );

	//! Builds a right-handed orthogonal projection matrix.
	//! @param		left		Minimum x-value of the view volume.
	//! @param		right		Maximum x-value of the view volume.
	//! @param		bottom		Minimum y-value of the view volume.
	//! @param		top			Maximum y-value of the view volume.
	//! @param		znear		Minimum z-value of the view volume.
	//! @param		zfar		Maximum z-value of the view volume.
	//! @return		The right-handed orthogonal projection matrix.
	static Matrix4 CreateOrthoOffCenterRH( _float left, _float right, _float bottom, _float top, _float znear, _float zfar );

	//! Builds a right-handed perspective projection matrix.
	//! @param		width		Width of the view volume at the near view-plane.
	//! @param		height		Height of the view volume at the near view-plane.
	//! @param		znear		Z-value of the near view plane.
	//! @param		zfar		Z-value of the far view plane.
	//! @return		The right-handed perspective projection matrix.
	static Matrix4 CreatePerspectiveRH( _float width, _float height, _float znear, _float zfar );

	//! Builds a right-handed perspective projection matrix.
	//! @param		fovy		Field of view in the y direction, in radians.
	//! @param		aspect		Aspect ratio, defined as view space width divided by height.
	//! @param		znear		Z-value of the near view plane.
	//! @param		zfar		Z-value of the far view plane.
	//! @return		The right-handed perspective projection matrix.
	static Matrix4 CreatePerspectiveFovRH( _float fovy, _float aspect, _float znear, _float zfar );

	//! Builds a right-handed perspective projection matrix.
	//! @param		left		Minimum x-value of the view volume.
	//! @param		right		Maximum x-value of the view volume.
	//! @param		bottom		Minimum y-value of the view volume.
	//! @param		top			Maximum y-value of the view volume.
	//! @param		znear		Minimum z-value of the view volume.
	//! @param		zfar		Maximum z-value of the view volume.
	//! @return		The right-handed perspective projection matrix.
	static Matrix4 CreatePerspectiveOffCenterRH( _float left, _float right, _float bottom, _float top, _float znear, _float zfar );

	//Builds a right-handed look-at matrix.
	//! @param		eye			The eye point.
	//! @param		lookat		The camera look-at target.
	//! @param		upaxis		The current world's up ( not the camera's up ).
	//! @return		The right-handed look-at matrix.
	static Matrix4 CreateLookAtRH( const Vector3& eye, const Vector3& lookat, const Vector3& upaxis );

	//! Builds a right-handed perspective projection matrix.
	//! @param		left		left tangent of the view volume.
	//! @param		right		right tangent of the view volume.
	//! @param		up			up tangent of the view volume.
	//! @param		down		down tangent of the view volume.
	//! @param		znear		Minimum z-value of the view volume.
	//! @param		zfar		Maximum z-value of the view volume.
	//! @return		The right-handed perspective projection matrix.
	static Matrix4 CreatePerspectiveProjectionRH( _float left_tan, _float right_tan, _float up_tan, _float down_tan, _float znear, _float zfar );

	static Matrix4 IncreaseDimension( const Matrix3& mat );
};

//----------------------------------------------------------------------------
// Matrix4 Implementation
//----------------------------------------------------------------------------

inline Matrix4::Matrix4( )
{
}

inline Matrix4::Matrix4( _float m00, _float m01, _float m02, _float m03, _float m10, _float m11, _float m12, _float m13,
	_float m20, _float m21, _float m22, _float m23, _float m30, _float m31, _float m32, _float m33 )
{
	m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
	m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
	m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
	m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
}

inline Matrix4::Matrix4( const Matrix3x4& matrix )
{
	m[0][0] = matrix.m[0][0]; m[0][1] = matrix.m[0][1]; m[0][2] = matrix.m[0][2]; m[0][3] = 0.0f;
	m[1][0] = matrix.m[1][0]; m[1][1] = matrix.m[1][1]; m[1][2] = matrix.m[1][2]; m[1][3] = 0.0f;
	m[2][0] = matrix.m[2][0]; m[2][1] = matrix.m[2][1]; m[2][2] = matrix.m[2][2]; m[2][3] = 0.0f;
	m[3][0] = matrix.m[3][0]; m[3][1] = matrix.m[3][1]; m[3][2] = matrix.m[3][2]; m[3][3] = 1.0f;
}

inline Matrix4::Matrix4( const Matrix4& matrix )
{
	m[0][0] = matrix.m[0][0]; m[0][1] = matrix.m[0][1]; m[0][2] = matrix.m[0][2]; m[0][3] = matrix.m[0][3];
	m[1][0] = matrix.m[1][0]; m[1][1] = matrix.m[1][1]; m[1][2] = matrix.m[1][2]; m[1][3] = matrix.m[1][3];
	m[2][0] = matrix.m[2][0]; m[2][1] = matrix.m[2][1]; m[2][2] = matrix.m[2][2]; m[2][3] = matrix.m[2][3];
	m[3][0] = matrix.m[3][0]; m[3][1] = matrix.m[3][1]; m[3][2] = matrix.m[3][2]; m[3][3] = matrix.m[3][3];
}

inline Matrix4& Matrix4::operator = ( const Matrix4& matrix )
{
	m[0][0] = matrix.m[0][0]; m[0][1] = matrix.m[0][1]; m[0][2] = matrix.m[0][2]; m[0][3] = matrix.m[0][3];
	m[1][0] = matrix.m[1][0]; m[1][1] = matrix.m[1][1]; m[1][2] = matrix.m[1][2]; m[1][3] = matrix.m[1][3];
	m[2][0] = matrix.m[2][0]; m[2][1] = matrix.m[2][1]; m[2][2] = matrix.m[2][2]; m[2][3] = matrix.m[2][3];
	m[3][0] = matrix.m[3][0]; m[3][1] = matrix.m[3][1]; m[3][2] = matrix.m[3][2]; m[3][3] = matrix.m[3][3];

	return *this;
}

inline Matrix4 Matrix4::operator + ( ) const
{
	return Matrix4( m[0][0], m[0][1], m[0][2], m[0][3], m[1][0], m[1][1], m[1][2], m[1][3],
		m[2][0], m[2][1], m[2][2], m[2][3], m[3][0], m[3][1], m[3][2], m[3][3] );
}

inline Matrix4 Matrix4::operator - ( ) const
{
	return Matrix4( -m[0][0], -m[0][1], -m[0][2], -m[0][3], -m[1][0], -m[1][1], -m[1][2], -m[1][3],
		-m[2][0], -m[2][1], -m[2][2], -m[2][3], -m[3][0], -m[3][1], -m[3][2], -m[3][3] );
}

inline _ubool Matrix4::operator == ( const Matrix4& matrix ) const
{
	if ( m[0][0] != matrix.m[0][0] ) return _false;
	if ( m[0][1] != matrix.m[0][1] ) return _false;
	if ( m[0][2] != matrix.m[0][2] ) return _false;
	if ( m[0][3] != matrix.m[0][3] ) return _false;

	if ( m[1][0] != matrix.m[1][0] ) return _false;
	if ( m[1][1] != matrix.m[1][1] ) return _false;
	if ( m[1][2] != matrix.m[1][2] ) return _false;
	if ( m[1][3] != matrix.m[1][3] ) return _false;

	if ( m[2][0] != matrix.m[2][0] ) return _false;
	if ( m[2][1] != matrix.m[2][1] ) return _false;
	if ( m[2][2] != matrix.m[2][2] ) return _false;
	if ( m[2][3] != matrix.m[2][3] ) return _false;

	if ( m[3][0] != matrix.m[3][0] ) return _false;
	if ( m[3][1] != matrix.m[3][1] ) return _false;
	if ( m[3][2] != matrix.m[3][2] ) return _false;
	if ( m[3][3] != matrix.m[3][3] ) return _false;

	return _true;
}

inline _ubool Matrix4::operator != ( const Matrix4& matrix ) const
{
	if ( m[0][0] != matrix.m[0][0] ) return _true;
	if ( m[0][1] != matrix.m[0][1] ) return _true;
	if ( m[0][2] != matrix.m[0][2] ) return _true;
	if ( m[0][3] != matrix.m[0][3] ) return _true;

	if ( m[1][0] != matrix.m[1][0] ) return _true;
	if ( m[1][1] != matrix.m[1][1] ) return _true;
	if ( m[1][2] != matrix.m[1][2] ) return _true;
	if ( m[1][3] != matrix.m[1][3] ) return _true;

	if ( m[2][0] != matrix.m[2][0] ) return _true;
	if ( m[2][1] != matrix.m[2][1] ) return _true;
	if ( m[2][2] != matrix.m[2][2] ) return _true;
	if ( m[2][3] != matrix.m[2][3] ) return _true;

	if ( m[3][0] != matrix.m[3][0] ) return _true;
	if ( m[3][1] != matrix.m[3][1] ) return _true;
	if ( m[3][2] != matrix.m[3][2] ) return _true;
	if ( m[3][3] != matrix.m[3][3] ) return _true;

	return _false;
}

inline Vector4 Matrix4::GetRow( _dword row ) const
{
	EGE_ASSERT( row < 4 )

	return Vector4( m[ row ][0], m[ row ][1], m[ row ][2], m[ row ][3] );
}

inline Vector4 Matrix4::GetColumn( _dword column ) const
{
	EGE_ASSERT( column < 4 )

	return Vector4( m[0][ column ], m[1][ column ], m[2][ column ], m[3][ column ] );
}

inline Matrix3 Matrix4::GetRotationMatrix( ) const
{
	return Matrix3(
		m[0][0], m[0][1], m[0][2],
		m[1][0], m[1][1], m[1][2],
		m[2][0], m[2][1], m[2][2] );
}

inline Vector3 Matrix4::GetScalingVector( ) const
{
	return Vector3( m[0][0], m[1][1], m[2][2] );
}

inline Vector3 Matrix4::GetTranslationVector( ) const
{
	return Vector3( m[3][0], m[3][1], m[3][2] );
}

inline Matrix4& Matrix4::SetTranslationVector( const Vector3& translation )
{
	m[3][0] = translation.x;
	m[3][1] = translation.y;
	m[3][2] = translation.z;
	return *this;
}

inline Matrix4& Matrix4::SetTranslationVector( _float x, _float y, _float z )
{
	m[3][0] = x;
	m[3][1] = y;
	m[3][2] = z;
	return *this;
}

inline Vector3 Matrix4::GetUpVector( ) const
{
	return Vector3( m[0][1], m[1][1], m[2][1] );
}

inline Vector3 Matrix4::GetRightVector( ) const
{
	return Vector3( m[0][0], m[1][0], m[2][0] );
}

inline Vector3 Matrix4::GetForwardVector( ) const
{
	return Vector3( m[0][2], m[1][2], m[2][2] );
}

}