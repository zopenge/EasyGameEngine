#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Transforms3D Implementation
//----------------------------------------------------------------------------

Transforms3D& Transforms3D::operator *= ( const Transforms3D& transform )
{
	mRotation *= transform.mRotation;
	mTranslate *= transform.mRotation;
	mTranslate += transform.mTranslate;
	return *this;
}

Transforms3D Transforms3D::operator * ( const Transforms3D& transform ) const
{
	Transforms3D returntransform( *this );
	return returntransform *= transform;
}
