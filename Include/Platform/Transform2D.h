
#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Transform2D
//----------------------------------------------------------------------------

class Transform2D
{
public:
	//! The position
	Vector2	mPosition;
	//! The scale factor
	Vector2	mScale;
	//! The rotation radian
	_float	mRadian;
		
public:
	//! The identity Transform2D.
	static const Transform2D cZero;

public:
	//! Constructor.
	//! @param		none
	inline Transform2D( );
	//! Constructor.
	//! @param		translate	translate component of the Transform2D.
	//! @param		scale		scale component of the Transform2D.
	//! @param		rotation	rotation component of the Transform2D.
	inline Transform2D( const Vector2& translate, const Vector2& scale, _float radian );

public:
	//! Multiply a matrix to current Transform2D, return a new Transform2D to save result.
	//! @param		transform		The transform to multiply.
	//! @return		The result Transform2D of multiplication.
	inline Matrix3 operator * ( const Matrix3& transform ) const;

	//! Compare two Transform2D.
	//! @param		transform	The Transform2D to compare with.
	//! @return		True if they are identical, false otherwise.
	inline _ubool operator == ( const Transform2D& transform ) const;
	//! Compare two Transform2D.
	//! @param		transform		The Transform2D to compare with.
	//! @return		True if they are not identical, false otherwise.
	inline _ubool operator != ( const Transform2D& transform ) const;

	//! Calculates inverse Transform2D, and save result in current one.
	//! @param		none
	//! @return		The inverse Transform2D.
	inline Matrix3 Inverse( );

	//! Calculates transform matrix.
	//! @param		none.
	//! @return		The transform matrix.
	inline Matrix3 ToMatrix( ) const;
	//! Calculates transform matrix.
	//! @param		offset	The translate offset.
	//! @return		The transform matrix.
	inline Matrix3 ToMatrix( const Vector2& offset ) const;
	//! Calculates transform matrix.
	//! @param		offset	The translate offset.
	//! @param		scale	The scale.
	//! @return		The transform matrix.
	inline Matrix3 ToMatrix( const Vector2& offset, const Vector2& scale ) const;

	//! Calculates linear interpolation of two Transform2D.
	//! @param		transform1	Source transform 1.
	//! @param		transform2	Source transform 2.
	//! @param		factor		The interpolation factor, will clamp to between 0 to 1.
	//! @return		The result transform of interpolation, transform1 + ( transform2 - transform1 ) * factor.
	static Transform2D Lerp( const Transform2D& transform1, const Transform2D& transform2, _float factor );
};

//----------------------------------------------------------------------------
// Transform2D Implementation
//----------------------------------------------------------------------------

Transform2D::Transform2D( )
{
	mPosition	= Vector2::cOrigin;
	mScale		= Vector2( 1.0f, 1.0f );
	mRadian		= 0.0f;
}

Transform2D::Transform2D( const Vector2& translate, const Vector2& scale, _float radian )
{
	mPosition	= translate;
	mScale		= scale;
	mRadian		= radian;
}

Matrix3 Transform2D::operator * ( const Matrix3& transform ) const
{
	return ToMatrix( ) * transform;
}

Matrix3 Transform2D::Inverse( )
{
	return ToMatrix( ).Inverse( );
}

Matrix3 Transform2D::ToMatrix( ) const
{
	return Matrix3( mPosition, mScale, mRadian );
}

Matrix3 Transform2D::ToMatrix( const Vector2& offset ) const
{
	return Matrix3( mPosition + offset, mScale, mRadian );
}

Matrix3 Transform2D::ToMatrix( const Vector2& offset, const Vector2& scale ) const
{
	return Matrix3( mPosition + offset, mScale * scale, mRadian );
}

}