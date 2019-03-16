//! @file     Timer.cpp
//! @author   foreven
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

const Transform3D Transform3D::cZero( Quaternion( 0.0f, 0.0f, 0.0f, 1.0f ), Vector3( 0.0f, 0.0f, 0.0f ) );

//----------------------------------------------------------------------------
// Transform3D Implementation
//----------------------------------------------------------------------------

Transform3D& Transform3D::operator *= ( const Transform3D& transform )
{
	mRotation *= transform.mRotation;
	mTranslate *= transform.mRotation;
	mTranslate += transform.mTranslate;
	return *this;
}

Transform3D Transform3D::operator * ( const Transform3D& transform ) const
{
	Transform3D returntransform( *this );
	return returntransform *= transform;
}

Transform3D& Transform3D::Inverse( )
{
	mTranslate = (-mTranslate) * -mRotation;
	mRotation = -mRotation;
	return *this;
}

Transform3D Transform3D::Lerp( const Transform3D& transform1, const Transform3D& transform2, _float factor )
{
	Transform3D transform;
	transform.mRotation = Quaternion::Slerp( transform1.mRotation, transform2.mRotation, factor );
	transform.mTranslate = Vector3::Lerp( transform1.mTranslate, transform2.mTranslate, factor );
	return transform;
}

Matrix4 Transform3D::ToMatrix( ) const
{
	return Matrix4( ).FromTranslationRotation( mTranslate, mRotation );
}